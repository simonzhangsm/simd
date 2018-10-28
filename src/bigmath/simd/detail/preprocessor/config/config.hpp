/**********************************************************************
 * BIGMATH INSIGHT CONFIDENTIAL
 *
 * Copyright (C) 2016-2018 BIGMATH CORPORATION, All Rights Reserved.
 *
 * @Author: Simon Zhang on 19 Oct 2018
 * @EMail: simon.zhangsm@hotmail.com
 * @Version: $BIGMATH_SIMD_LIB_VERSION
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
#ifndef SIMD_PREPROCESSOR_CONFIG_CONFIG_HPP
#define SIMD_PREPROCESSOR_CONFIG_CONFIG_HPP
#
#/* SIMD_CONFIG_FLAGS */
#
#define SIMD_CONFIG_STRICT() 0x0001
#define SIMD_CONFIG_IDEAL() 0x0002
#
#define SIMD_CONFIG_MSVC() 0x0004
#define SIMD_CONFIG_MWCC() 0x0008
#define SIMD_CONFIG_BCC() 0x0010
// not supported
#define SIMD_CONFIG_EDG() 0x0020
// not supported
#define SIMD_CONFIG_DMC() 0x0040
#
#ifndef SIMD_CONFIG_FLAGS
#if defined(__GCCXML__) || defined(__WAVE__) || defined(__MWERKS__) && __MWERKS__ >= 0x3200
#define SIMD_CONFIG_FLAGS() (SIMD_CONFIG_STRICT())
#elif defined(__EDG__) || defined(__EDG_VERSION__)
#if defined(_MSC_VER) && !defined(__clang__) && (defined(__INTELLISENSE__) || __EDG_VERSION__ >= 308)
#define SIMD_CONFIG_FLAGS() (SIMD_CONFIG_MSVC())
#else
#define SIMD_CONFIG_FLAGS() (SIMD_CONFIG_EDG() | SIMD_CONFIG_STRICT())
#endif
#elif defined(_MSC_VER) && defined(__clang__)
#define SIMD_CONFIG_FLAGS() (SIMD_CONFIG_STRICT())
#elif defined(__MWERKS__)
#define SIMD_CONFIG_FLAGS() (SIMD_CONFIG_MWCC())
#elif defined(__DMC__)
#define SIMD_CONFIG_FLAGS() (SIMD_CONFIG_DMC())
#elif defined(__BORLANDC__) && __BORLANDC__ >= 0x581
#define SIMD_CONFIG_FLAGS() (SIMD_CONFIG_STRICT())
#elif defined(__BORLANDC__) || defined(__IBMC__) || defined(__IBMCPP__) || defined(__SUNPRO_CC)
#define SIMD_CONFIG_FLAGS() (SIMD_CONFIG_BCC())
#elif defined(_MSC_VER)
#define SIMD_CONFIG_FLAGS() (SIMD_CONFIG_MSVC())
#else
#define SIMD_CONFIG_FLAGS() (SIMD_CONFIG_STRICT())
#endif
#endif
#
#/* SIMD_CONFIG_EXTENDED_LINE_INFO */
#
#ifndef SIMD_CONFIG_EXTENDED_LINE_INFO
#define SIMD_CONFIG_EXTENDED_LINE_INFO 0
#endif
#
#/* SIMD_CONFIG_ERRORS */
#
#ifndef SIMD_CONFIG_ERRORS
#ifdef NDEBUG
#define SIMD_CONFIG_ERRORS 0
#else
#define SIMD_CONFIG_ERRORS 1
#endif
#endif
#
#/* SIMD_VARIADICS */
#
#define SIMD_VARIADICS_MSVC 0
#if !defined SIMD_VARIADICS
#/* variadic support explicitly disabled for all untested compilers */
#if defined __GCCXML__ || defined __CUDACC__ || defined __PATHSCALE__ || defined __DMC__ || defined __CODEGEARC__ \
    || defined __BORLANDC__ || defined __MWERKS__ || (defined __SUNPRO_CC && __SUNPRO_CC < 0x5120)                \
    || defined __HP_aCC && !defined __EDG__ || defined __MRC__ || defined __SC__ || defined __IBMCPP__            \
    || defined __PGI
#define SIMD_VARIADICS 0
#elif defined(_MSC_VER) && defined(__clang__)
#define SIMD_VARIADICS 1
#/* VC++ (C/C++) and Intel C++ Compiler >= 17.0 with MSVC */
#elif defined _MSC_VER && _MSC_VER >= 1400 \
    && (!defined __EDG__ || defined(__INTELLISENSE__) || defined(__INTEL_COMPILER) && __INTEL_COMPILER >= 1700)
#define SIMD_VARIADICS 1
#undef SIMD_VARIADICS_MSVC
#define SIMD_VARIADICS_MSVC 1
#/* Wave (C/C++), GCC (C++) */
#elif defined __WAVE__ && __WAVE_HAS_VARIADICS__ \
    || defined __GNUC__ && defined __GXX_EXPERIMENTAL_CXX0X__ && __GXX_EXPERIMENTAL_CXX0X__
#define SIMD_VARIADICS 1
#/* EDG-based (C/C++), GCC (C), and unknown (C/C++) */
#elif !defined __cplusplus && __STDC_VERSION__ >= 199901L || __cplusplus >= 201103L
#define SIMD_VARIADICS 1
#else
#define SIMD_VARIADICS 0
#endif
#elif !SIMD_VARIADICS + 1 < 2
#undef SIMD_VARIADICS
#define SIMD_VARIADICS 1
#if defined _MSC_VER && _MSC_VER >= 1400 && !defined(__clang__)                                                      \
    && (defined(__INTELLISENSE__) || (defined(__INTEL_COMPILER) && __INTEL_COMPILER >= 1700)                         \
        || !(defined __EDG__ || defined __GCCXML__ || defined __CUDACC__ || defined __PATHSCALE__ || defined __DMC__ \
             || defined __CODEGEARC__ || defined __BORLANDC__ || defined __MWERKS__ || defined __SUNPRO_CC           \
             || defined __HP_aCC || defined __MRC__ || defined __SC__ || defined __IBMCPP__ || defined __PGI))
#undef SIMD_VARIADICS_MSVC
#define SIMD_VARIADICS_MSVC 1
#endif
#else
#undef SIMD_VARIADICS
#define SIMD_VARIADICS 0
#endif
#
#if SIMD_VARIADICS == 0
#error "This compiler has not been recognized as a supported compiler (lack of variadic support)"
#endif
#
#endif
