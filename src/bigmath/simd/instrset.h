/**********************************************************************
 * BIGMATH INSIGHT CONFIDENTIAL
 *
 * Copyright (C) 2016-2018 BIGMATH CORPORATION, All Rights Reserved.
 *
 * @Author: Simon Zhang on 19 Oct 2018
 * @EMail: simon.zhangsm@hotmail.com
 * @Version: $SIMD_LIB_VERSION
 *
 * Description:
 * Header file for various compiler-specific tasks and other common tasks to
 * vector class library:
 * > selects the supported instruction set
 * > defines integer types
 * > defines compiler version macros
 * > undefines certain macros that prevent function overloading
 * > defines template class to represent compile-time integer constant
 * > defines template for compile-time error messages
 *
 * These source codes are subject to the terms and conditions defined
 * in 'LICENSE', which is part of this source code package. Write to
 * LICENSE@BIGMATH.COM for more authorization requirements, or obtain
 * an entire copy of license agreement at http://bigmath.com/license.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * **********************************************************************/

#ifndef INSTRSET_H
#define INSTRSET_H 125

// Detect 64 bit mode
#if (defined(_M_AMD64) || defined(_M_X64) || defined(__amd64)) && !defined(__x86_64__)
#define __x86_64__ 1 // There are many different macros for this, decide on only one
#endif

// Find instruction set from compiler macros if INSTRSET not defined
// Note: Most of these macros are not defined in Microsoft compilers
#ifndef INSTRSET
#if defined(__ARM_NEON__) || defined(__ARM_NEON) || defined(__aarch64__) || defined(__arm__)
#define INSTRSET 12
#elif defined(__MIC__)
#define INSTRSET 11
#elif defined(__ALTIVEC__)
#define INSTRSET 10
#elif defined(__AVX512F__) || defined(__AVX512__)
#define INSTRSET 9
#elif defined(__AVX2__)
#define INSTRSET 8
#elif defined(__AVX__)
#define INSTRSET 7
#elif defined(__SSE4_2__)
#define INSTRSET 6
#elif defined(__SSE4_1__)
#define INSTRSET 5
#elif defined(__SSSE3__)
#define INSTRSET 4
#elif defined(__SSE3__)
#define INSTRSET 3
#elif defined(__SSE2__) || defined(__x86_64__)
#define INSTRSET 2
#elif defined(__SSE__)
#define INSTRSET 1
#elif defined(_M_IX86_FP) // Defined in MS compiler. 1: SSE, 2: SSE2
#define INSTRSET _M_IX86_FP
#else
#define INSTRSET 0
#endif // instruction set defines
#endif // INSTRSET

// Include the appropriate header file for intrinsic functions
#if INSTRSET == 12 // NEON
#include <arm_neon.h>
#elif INSTRSET == 11 // MIC
#include <immintrin.h>
#elif INSTRSET == 10 // ALTIVEC
#include <altivec.h>
#elif INSTRSET > 7 // AVX2 and later
#if defined(__GNUC__) && (!defined(__INTEL_COMPILER) && !defined(__ICL) && !defined(__ICC))
#include <x86intrin.h> // x86intrin.h includes header files for whatever instruction
                       // sets are specified on the compiler command line, such as:
                       // xopintrin.h, fma4intrin.h
#else
#include <immintrin.h> // MS version of immintrin.h covers AVX, AVX2 and FMA3
#endif                 // __GNUC__

#elif INSTRSET == 7
#include <immintrin.h> // AVX
#elif INSTRSET == 6
#include <nmmintrin.h> // SSE4.2
#elif INSTRSET == 5
#include <smmintrin.h> // SSE4.1
#elif INSTRSET == 4
#include <tmmintrin.h> // SSSE3
#elif INSTRSET == 3
#include <pmmintrin.h> // SSE3
#elif INSTRSET == 2
#include <emmintrin.h> // SSE2
#elif INSTRSET == 1
#include <xmmintrin.h> // SSE
#endif                 // INSTRSET

#if INSTRSET >= 8 && !defined(__FMA__)
// Assume that all processors that have AVX2 also have FMA3
#if defined(__GNUC__) && !defined(__INTEL_COMPILER) && !defined(__clang__)
// Prevent error message in g++ when using FMA intrinsics with avx2:
#pragma message "It is recommended to specify also option -mfma when using -mavx2 or higher"
#else
#define __FMA__ 1
#endif
#endif

// AMD  instruction sets
#if defined(__XOP__) || defined(__FMA4__)
#ifdef __GNUC__
#include <x86intrin.h> // AMD XOP (Gnu)
#else
#include <ammintrin.h>   // AMD XOP (Microsoft)
#endif                   //  __GNUC__
#elif defined(__SSE4A__) // AMD SSE4A
#include <ammintrin.h>
#endif // __XOP__

// FMA3 instruction set
#if defined(__FMA__) && (defined(__GNUC__) || defined(__clang__)) && !defined(__INTEL_COMPILER)
#include <fmaintrin.h>
#endif // __FMA__

// FMA4 instruction set
#if defined(__FMA4__) && (defined(__GNUC__) || defined(__clang__))
#include <fma4intrin.h> // must have both x86intrin.h and fma4intrin.h, don't know why
#endif                  // __FMA4__

// Define integer types with known size
#if defined(__GNUC__) || defined(__clang__) || (defined(_MSC_VER) && _MSC_VER >= 1600)
// Compilers supporting C99 or C++0x have stdint.h defining these integer types
#include <stdint.h>
#elif defined(_MSC_VER)
// Older Microsoft compilers have their own definitions
typedef signed __int8 int8_t;
typedef unsigned __int8 uint8_t;
typedef signed __int16 int16_t;
typedef unsigned __int16 uint16_t;
typedef signed __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef signed __int64 int64_t;
typedef unsigned __int64 uint64_t;
#ifndef _INTPTR_T_DEFINED
#define _INTPTR_T_DEFINED
#ifdef __x86_64__
typedef int64_t intptr_t;
#else
typedef int32_t intptr_t;
#endif
#endif
#else
// This works with most compilers
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed short int int16_t;
typedef unsigned short int uint16_t;
typedef signed int int32_t;
typedef unsigned int uint32_t;
typedef long long int64_t;
typedef unsigned long long uint64_t;
#ifdef __x86_64__
typedef int64_t intptr_t;
#else
typedef int32_t intptr_t;
#endif
#endif

#include <stdlib.h> // define abs(int)

#ifdef _MSC_VER     // Microsoft compiler or compatible Intel compiler
#include <intrin.h> // define _BitScanReverse(int), __cpuid(int[4],int), _xgetbv(int)
#endif              // _MSC_VER

// functions in instrset_detect.cpp
namespace CORPORATION_NAMESPACE {
    namespace simd {
        int instrset_detect(void); // tells which instruction sets are supported
        bool hasFMA3(void);        // true if FMA3 instructions supported
        bool hasFMA4(void);        // true if FMA4 instructions supported
        bool hasXOP(void);         // true if XOP  instructions supported
        bool hasAVX512ER(void);    // true if AVX512ER instructions supported
    }                              // namespace simd
} // namespace CORPORATION_NAMESPACE

// GCC version
#if defined(__GNUC__) && !defined(GCC_VERSION) && !defined(__clang__)
#define GCC_VERSION ((__GNUC__)*10000 + (__GNUC_MINOR__)*100 + (__GNUC_PATCHLEVEL__))
#endif

// Clang version
#if defined(__clang__)
#define CLANG_VERSION ((__clang_major__)*10000 + (__clang_minor__)*100 + (__clang_patchlevel__))
// Problem: The version number is not consistent across platforms
// http://llvm.org/bugs/show_bug.cgi?id=12643
// Apple bug 18746972
#endif

// Fix problem with non-overloadable macros named min and max in WinDef.h
#ifdef _MSC_VER
#if defined(_WINDEF_) && defined(min) && defined(max)
#undef min
#undef max
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#endif
// namespace CORPORATION_NAMESPACE {
//    namespace simd {
// Template class to represent compile-time integer constant
template <int32_t n> class Const_int_t {};
// represent compile-time signed integer constant
template <uint32_t n> class Const_uint_t {};
// represent compile-time unsigned integer constant
#define const_int(n) (Const_int_t<n>())   // n must be compile-time integer constant
#define const_uint(n) (Const_uint_t<n>()) // n must be compile-time unsigned integer constant

// Template for compile-time error messages
template <bool> class Static_error_check {
public:
    Static_error_check(){};
};
template <> class Static_error_check<false> { // generate compile-time error if false
private:
    Static_error_check(){};
};
//    } // namespace simd
//} // namespace CORPORATION_NAMESPACE


#endif // INSTRSET_H
