/**********************************************************************
 * BIGMATH INSIGHT CONFIDENTIAL
 *
 * Copyright (C) 2016-2018 BIGMATH CORPORATION, All Rights Reserved.
 *
 * @Author: Simon Zhang on 19 Oct 2018
 * @EMail: simon.zhangsm@hotmail.com
 * @Version: $SIMD_LIB_VERSION
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

#ifndef SIMD_SETUP_ARCH_H
#define SIMD_SETUP_ARCH_H

#include <bigmath/simd/config.h>
#include <bigmath/simd/detail/preprocessor.h>
#include <bigmath/simd/detail/preprocessor/stringize.hpp>

// Set up macros for current architecture. Note that this file may be included
// multiple times, more information on the caveats are within the file.
#include <bigmath/simd/detail/preprocess_single_arch.h>

// Set up main feature macros
#if SIMD_ARCH_USE_NULL
#define SIMD_USE_NULL 1
#else
#define SIMD_USE_NULL 0
#endif

#if SIMD_ARCH_USE_SSE2
#define SIMD_USE_SSE2 1
#else
#define SIMD_USE_SSE2 0
#endif

#if SIMD_ARCH_USE_SSE3
#define SIMD_USE_SSE3 1
#else
#define SIMD_USE_SSE3 0
#endif

#if SIMD_ARCH_USE_SSSE3
#define SIMD_USE_SSSE3 1
#else
#define SIMD_USE_SSSE3 0
#endif

#if SIMD_ARCH_USE_SSE4_1
#define SIMD_USE_SSE4_1 1
#else
#define SIMD_USE_SSE4_1 0
#endif

#if SIMD_ARCH_USE_SSE4_2
#define SIMD_USE_SSE4_2 1
#else
#define SIMD_USE_SSE4_2 0
#endif

#if SIMD_ARCH_USE_SSE4A
#define SIMD_USE_SSE4A 1
#else
#define SIMD_USE_SSE4A 0
#endif

#if SIMD_ARCH_USE_X86_POPCNT_INSN
#define SIMD_USE_X86_POPCNT_INSN 1
#else
#define SIMD_USE_X86_POPCNT_INSN 0
#endif

#if SIMD_ARCH_USE_AVX
#define SIMD_USE_AVX 1
#else
#define SIMD_USE_AVX 0
#endif

#if SIMD_ARCH_USE_AVX2
#define SIMD_USE_AVX2 1
#else
#define SIMD_USE_AVX2 0
#endif

#if SIMD_ARCH_USE_FMA3
#define SIMD_USE_FMA3 1
#else
#define SIMD_USE_FMA3 0
#endif

#if SIMD_ARCH_USE_FMA4
#define SIMD_USE_FMA4 1
#else
#define SIMD_USE_FMA4 0
#endif

#if SIMD_ARCH_USE_XOP
#define SIMD_USE_XOP 1
#else
#define SIMD_USE_XOP 0
#endif

#if SIMD_ARCH_USE_AVX512F
#define SIMD_USE_AVX512F 1
#else
#define SIMD_USE_AVX512F 0
#endif

#if SIMD_ARCH_USE_AVX512BW
#define SIMD_USE_AVX512BW 1
#else
#define SIMD_USE_AVX512BW 0
#endif

#if SIMD_ARCH_USE_AVX512DQ
#define SIMD_USE_AVX512DQ 1
#else
#define SIMD_USE_AVX512DQ 0
#endif

#if SIMD_ARCH_USE_AVX512VL
#define SIMD_USE_AVX512VL 1
#else
#define SIMD_USE_AVX512VL 0
#endif

#if SIMD_ARCH_USE_NEON
#define SIMD_USE_NEON 1
#else
#define SIMD_USE_NEON 0
#endif

#if SIMD_ARCH_USE_NEON_FLT_SP
#define SIMD_USE_NEON_FLT_SP 1
#else
#define SIMD_USE_NEON_FLT_SP 0
#endif

#if SIMD_ARCH_USE_ALTIVEC
#define SIMD_USE_ALTIVEC 1
#else
#define SIMD_USE_ALTIVEC 0
#endif

#if SIMD_ARCH_USE_VSX_206
#define SIMD_USE_VSX_206 1
#else
#define SIMD_USE_VSX_206 0
#endif

#if SIMD_ARCH_USE_VSX_207
#define SIMD_USE_VSX_207 1
#else
#define SIMD_USE_VSX_207 0
#endif

#if SIMD_ARCH_USE_MSA
#define SIMD_USE_MSA 1
#else
#define SIMD_USE_MSA 0
#endif

// Generate SIMD_ARCH_NAMESPACE. It's a human-readable identifier depending
// on the enabled instruction sets
#if SIMD_ARCH_NS_USE_NULL
#define SIMD_NS_ID_NULL SIMD_INSN_ID_NULL
#else
#define SIMD_NS_ID_NULL
#endif

#if SIMD_ARCH_NS_USE_SSE2
#define SIMD_NS_ID_SSE2 SIMD_INSN_ID_SSE2
#else
#define SIMD_NS_ID_SSE2
#endif

#if SIMD_ARCH_NS_USE_SSE3
#define SIMD_NS_ID_SSE3 SIMD_INSN_ID_SSE3
#else
#define SIMD_NS_ID_SSE3
#endif

#if SIMD_ARCH_NS_USE_SSSE3
#define SIMD_NS_ID_SSSE3 SIMD_INSN_ID_SSSE3
#else
#define SIMD_NS_ID_SSSE3
#endif

#if SIMD_ARCH_NS_USE_SSE4_1
#define SIMD_NS_ID_SSE4_1 SIMD_INSN_ID_SSE4_1
#else
#define SIMD_NS_ID_SSE4_1
#endif

#if SIMD_ARCH_NS_USE_SSE4_2
#define SIMD_NS_ID_SSE4_2 SIMD_INSN_ID_SSE4_2
#else
#define SIMD_NS_ID_SSE4_2
#endif

#if SIMD_ARCH_NS_USE_SSE4A
#define SIMD_NS_ID_SSE4A SIMD_INSN_ID_SSE4A
#else
#define SIMD_NS_ID_SSE4A
#endif

#if SIMD_ARCH_NS_USE_POPCNT_INSN
#define SIMD_NS_ID_POPCNT_INSN SIMD_INSN_ID_POPCNT_INSN
#else
#define SIMD_NS_ID_POPCNT_INSN
#endif

#if SIMD_ARCH_NS_USE_AVX
#define SIMD_NS_ID_AVX SIMD_INSN_ID_AVX
#else
#define SIMD_NS_ID_AVX
#endif

#if SIMD_ARCH_NS_USE_AVX2
#define SIMD_NS_ID_AVX2 SIMD_INSN_ID_AVX2
#else
#define SIMD_NS_ID_AVX2
#endif

#if SIMD_ARCH_NS_USE_FMA3
#define SIMD_NS_ID_FMA3 SIMD_INSN_ID_FMA3
#else
#define SIMD_NS_ID_FMA3
#endif

#if SIMD_ARCH_NS_USE_FMA4
#define SIMD_NS_ID_FMA4 SIMD_INSN_ID_FMA4
#else
#define SIMD_NS_ID_FMA4
#endif

#if SIMD_ARCH_NS_USE_XOP
#define SIMD_NS_ID_XOP SIMD_INSN_ID_XOP
#else
#define SIMD_NS_ID_XOP
#endif

#if SIMD_ARCH_NS_USE_AVX512F
#define SIMD_NS_ID_AVX512F SIMD_INSN_ID_AVX512F
#else
#define SIMD_NS_ID_AVX512F
#endif

#if SIMD_ARCH_NS_USE_AVX512BW
#define SIMD_NS_ID_AVX512BW SIMD_INSN_ID_AVX512BW
#else
#define SIMD_NS_ID_AVX512BW
#endif

#if SIMD_ARCH_NS_USE_AVX512DQ
#define SIMD_NS_ID_AVX512DQ SIMD_INSN_ID_AVX512DQ
#else
#define SIMD_NS_ID_AVX512DQ
#endif

#if SIMD_ARCH_NS_USE_AVX512VL
#define SIMD_NS_ID_AVX512VL SIMD_INSN_ID_AVX512VL
#else
#define SIMD_NS_ID_AVX512VL
#endif

#if SIMD_ARCH_NS_USE_NEON
#define SIMD_NS_ID_NEON SIMD_INSN_ID_NEON
#else
#define SIMD_NS_ID_NEON
#endif

#if SIMD_ARCH_NS_USE_NEON_FLT_SP
#define SIMD_NS_ID_NEON_FLT_SP SIMD_INSN_ID_NEON_FLT_SP
#else
#define SIMD_NS_ID_NEON_FLT_SP
#endif

#if SIMD_ARCH_NS_USE_ALTIVEC
#define SIMD_NS_ID_ALTIVEC SIMD_INSN_ID_ALTIVEC
#else
#define SIMD_NS_ID_ALTIVEC
#endif

#if SIMD_ARCH_NS_USE_VSX_206
#define SIMD_NS_ID_VSX_206 SIMD_INSN_ID_VSX_206
#else
#define SIMD_NS_ID_VSX_206
#endif

#if SIMD_ARCH_NS_USE_VSX_207
#define SIMD_NS_ID_VSX_207 SIMD_INSN_ID_VSX_207
#else
#define SIMD_NS_ID_VSX_207
#endif

#if SIMD_ARCH_NS_USE_MSA
#define SIMD_NS_ID_MSA SIMD_INSN_ID_MSA
#else
#define SIMD_NS_ID_MSA
#endif

#define SIMD_ARCH_NAMESPACE              \
    SIMD_PASTE24(arch,                   \
                 SIMD_NS_ID_NULL,        \
                 SIMD_NS_ID_SSE2,        \
                 SIMD_NS_ID_SSE3,        \
                 SIMD_NS_ID_SSSE3,       \
                 SIMD_NS_ID_SSE4_1,      \
                 SIMD_NS_ID_SSE4_2,      \
                 SIMD_NS_ID_SSE4A,       \
                 SIMD_NS_ID_POPCNT_INSN, \
                 SIMD_NS_ID_AVX,         \
                 SIMD_NS_ID_AVX2,        \
                 SIMD_NS_ID_AVX512F,     \
                 SIMD_NS_ID_AVX512BW,    \
                 SIMD_NS_ID_AVX512DQ,    \
                 SIMD_NS_ID_AVX512VL,    \
                 SIMD_NS_ID_FMA3,        \
                 SIMD_NS_ID_FMA4,        \
                 SIMD_NS_ID_XOP,         \
                 SIMD_NS_ID_NEON,        \
                 SIMD_NS_ID_NEON_FLT_SP, \
                 SIMD_NS_ID_MSA,         \
                 SIMD_NS_ID_ALTIVEC,     \
                 SIMD_NS_ID_VSX_206,     \
                 SIMD_NS_ID_VSX_207)

#define SIMD_ARCH_THIS_COMPILE_ARCH_NAMESPACE SIMD_ARCH_NAMESPACE
#define SIMD_ARCH_THIS_COMPILE_ARCH_FOR_DISPATCH 0
#include <bigmath/simd/dispatch/preprocess_single_compile_arch.h>
#undef SIMD_ARCH_THIS_COMPILE_ARCH_FOR_DISPATCH
#undef SIMD_ARCH_THIS_COMPILE_ARCH_NAMESPACE

// Include headers relevant for the enabled instruction sets.
#if SIMD_USE_SSE2
#include <xmmintrin.h>
#include <emmintrin.h>
#endif

#if SIMD_USE_SSE3
#include <pmmintrin.h>
#endif

#if SIMD_USE_SSSE3
#include <tmmintrin.h>
#endif

#if SIMD_USE_SSE4_1
#include <smmintrin.h>
#endif

#if SIMD_USE_SSE4_2
#include <nmmintrin.h>
#endif

#if SIMD_USE_SSE4A
#include <ammintrin.h>
#endif

#if SIMD_USE_AVX
#include <immintrin.h>
#endif

#if SIMD_USE_AVX2
#include <immintrin.h>
#endif

#if SIMD_USE_FMA3
#include <immintrin.h>
#endif

#if SIMD_USE_FMA4
#include <x86intrin.h>
#if SIMD_USE_FMA3
#error "X86_FMA3 and X86_FMA4 can't be used together"
#endif
#endif

#if SIMD_USE_XOP
#include <x86intrin.h>
#endif

#if SIMD_USE_AVX512F || SIMD_USE_AVX512BW
#include <immintrin.h>
#endif

#if SIMD_USE_NEON || SIMD_USE_NEON_FLT_SP
#include <arm_neon.h>
#endif

#if SIMD_USE_ALTIVEC
#include <altivec.h>
#undef vector
#undef pixel
#undef bool
#endif

#if SIMD_USE_MSA
#include <msa.h>
#endif

// helper macros
#if __amd64__ || __x86_64__ || _M_AMD64 || __aarch64__ || __powerpc64__
#define SIMD_64_BITS 1
#define SIMD_32_BITS 0
#else
#define SIMD_32_BITS 1
#define SIMD_64_BITS 0
#endif

#if SIMD_USE_NEON && SIMD_64_BITS
#undef SIMD_USE_NEON_FLT_SP
#define SIMD_USE_NEON_FLT_SP 1
#endif

#if SIMD_USE_ALTIVEC
#ifndef __BYTE_ORDER__
#error "Could not determine byte order"
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define SIMD_LITTLE_ENDIAN 1
#define SIMD_BIG_ENDIAN 0
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define SIMD_LITTLE_ENDIAN 0
#define SIMD_BIG_ENDIAN 1
#else
#error "Could not determine byte order"
#endif
#endif

#define SIMD_USE_NEON32 (SIMD_USE_NEON && SIMD_32_BITS)
#define SIMD_USE_NEON64 (SIMD_USE_NEON && SIMD_64_BITS)
#define SIMD_USE_NEON32_FLT_SP (SIMD_USE_NEON_FLT_SP && SIMD_32_BITS)
#define SIMD_USE_NEON_NO_FLT_SP (SIMD_USE_NEON && !SIMD_USE_NEON_FLT_SP)

#if __i386__ || __i386 || _M_IX86 || __amd64__ || __x64_64__ || _M_AMD64 || _M_X64
#define SIMD_X86 1
#elif _M_ARM || __arm__ || __aarch64__
#define SIMD_ARM 1
#elif __powerpc__ || __powerpc64__
#define SIMD_PPC 1
#elif __mips__
#define SIMD_MIPS 1
#endif

/** @def SIMD_ARCH_NAME
    Usable in contexts where a string is required
*/
#define SIMD_ARCH_NAME SIMD_STRINGIZE(SIMD_ARCH_NAMESPACE)

#if defined(__GNUC__) || defined(__clang__)
#define SIMD_DEPRECATED(msg) __attribute__((deprecated(msg)))
#else
#define SIMD_DEPRECATED(msg)
#endif

#define SIMD_LIBRARY_VERSION_CXX11 1
#define SIMD_LIBRARY_VERSION_CXX98 0

#include <bigmath/simd/detail/workarounds.h>
#include <bigmath/simd/deprecations.h>

// #define SIMD_EXPR_DEBUG 1

// FIXME: unused (workarounds for AMD CPUs)
// #define SIMD_USE_AMD

#endif
