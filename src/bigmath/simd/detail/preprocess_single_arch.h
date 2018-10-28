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

/*  This file contains macros that set up information for single architecture
    definition. It's here to reduce duplication. Other files supply appropriate
    definitions of certain input macros and collect the output from the macros
    defined in this file.

    Note that in C++ it's not possible to substitute the nested macros in
    replacement list of a #define at the point of definition of said #define.
    All nested macros will be substituted to the current values at each site of
    use. The consequence is that the resulting macros of this file may only be
    evaluated by #if elsewhere, otherwise the last inclusion of the file will
    effectively overwrite the values.

    The input data may be supplied via two ways:
    1)  If SIMD_ARCH_LIST is not defined, then the instruction sets should
        be supplied via SIMD_ARCH_* macros. If particular macro expands to
        non-zero value then the given instruction set and any subsets are
        enabled. After processing the information supplied via SIMD_ARCH_*
        this file undefines all these macros.

    2)  If SIMD_ARCH_LIST is defined, then it supplies a list of enabled
        instruction sets. The macro should be defined to a comma-separated list
        of identifiers, each equivalent to one of SIMD_ARCH_* macro names.

    Note that if SIMD_ARCH_LIST is defined, then all SIMD_ARCH_* macros
    themselves must not be defined, as they cause unintended expansions within
    tihs file.

    The output data:

    SIMD_ARCH_USE_* - defined depending on whether the particular
        instructions are enabled.

    SIMD_ARCH_NS_USE_* - defined depending on whether the particular
        instructions set id should be included into SIMD_ARCH_NAMESPACE
        definition. The difference from SIMD_ARCH_USE_* is that some
        instruction sets are subsets of other instruction sets, so it makes
        no sense to make the namespace longer. E.g. we use arch_ssse3 instead of
        arch_sse2_sse3_ssse3.
*/

#include <bigmath/simd/detail/preprocessor.h>
#include <bigmath/simd/detail/preprocessor/cat.hpp>
#include <bigmath/simd/detail/preprocessor/facilities/expand.hpp>
#include <bigmath/simd/detail/insn_id.h>

// Undef output macros
#ifdef SIMD_ARCH_ARCH_ID
#undef SIMD_ARCH_ARCH_ID
#endif

#ifdef SIMD_ARCH_USE_NULL
#undef SIMD_ARCH_USE_NULL
#endif

#ifdef SIMD_ARCH_USE_SSE2
#undef SIMD_ARCH_USE_SSE2
#endif

#ifdef SIMD_ARCH_USE_SSE3
#undef SIMD_ARCH_USE_SSE3
#endif

#ifdef SIMD_ARCH_USE_SSSE3
#undef SIMD_ARCH_USE_SSSE3
#endif

#ifdef SIMD_ARCH_USE_SSE4_1
#undef SIMD_ARCH_USE_SSE4_1
#endif

#ifdef SIMD_ARCH_USE_SSE4_2
#undef SIMD_ARCH_USE_SSE4_2
#endif

#ifdef SIMD_ARCH_USE_SSE4A
#undef SIMD_ARCH_USE_SSE4A
#endif

#ifdef SIMD_ARCH_USE_X86_POPCNT_INSN
#undef SIMD_ARCH_USE_X86_POPCNT_INSN
#endif

#ifdef SIMD_ARCH_USE_AVX
#undef SIMD_ARCH_USE_AVX
#endif

#ifdef SIMD_ARCH_USE_AVX2
#undef SIMD_ARCH_USE_AVX2
#endif

#ifdef SIMD_ARCH_USE_AVX512F
#undef SIMD_ARCH_USE_AVX512F
#endif

#ifdef SIMD_ARCH_USE_AVX512BW
#undef SIMD_ARCH_USE_AVX512BW
#endif

#ifdef SIMD_ARCH_USE_AVX512DQ
#undef SIMD_ARCH_USE_AVX512DQ
#endif

#ifdef SIMD_ARCH_USE_AVX512VL
#undef SIMD_ARCH_USE_AVX512VL
#endif

#ifdef SIMD_ARCH_USE_FMA3
#undef SIMD_ARCH_USE_FMA3
#endif

#ifdef SIMD_ARCH_USE_FMA4
#undef SIMD_ARCH_USE_FMA4
#endif

#ifdef SIMD_ARCH_USE_XOP
#undef SIMD_ARCH_USE_XOP
#endif

#ifdef SIMD_ARCH_USE_NEON
#undef SIMD_ARCH_USE_NEON
#endif

#ifdef SIMD_ARCH_USE_NEON_FLT_SP
#undef SIMD_ARCH_USE_NEON_FLT_SP
#endif

#ifdef SIMD_ARCH_USE_ALTIVEC
#undef SIMD_ARCH_USE_ALTIVEC
#endif

#ifdef SIMD_ARCH_USE_VSX_206
#undef SIMD_ARCH_USE_VSX_206
#endif

#ifdef SIMD_ARCH_USE_VSX_207
#undef SIMD_ARCH_USE_VSX_207
#endif

#ifdef SIMD_ARCH_USE_MSA
#undef SIMD_ARCH_USE_MSA
#endif

#ifdef SIMD_ARCH_NS_USE_NULL
#undef SIMD_ARCH_NS_USE_NULL
#endif

#ifdef SIMD_ARCH_NS_USE_SSE2
#undef SIMD_ARCH_NS_USE_SSE2
#endif

#ifdef SIMD_ARCH_NS_USE_SSE3
#undef SIMD_ARCH_NS_USE_SSE3
#endif

#ifdef SIMD_ARCH_NS_USE_SSSE3
#undef SIMD_ARCH_NS_USE_SSSE3
#endif

#ifdef SIMD_ARCH_NS_USE_SSE4_1
#undef SIMD_ARCH_NS_USE_SSE4_1
#endif

#ifdef SIMD_ARCH_NS_USE_SSE4_2
#undef SIMD_ARCH_NS_USE_SSE4_2
#endif

#ifdef SIMD_ARCH_NS_USE_SSE4A
#undef SIMD_ARCH_NS_USE_SSE4A
#endif

#ifdef SIMD_ARCH_NS_USE_POPCNT_INSN
#undef SIMD_ARCH_NS_USE_POPCNT_INSN
#endif

#ifdef SIMD_ARCH_NS_USE_AVX
#undef SIMD_ARCH_NS_USE_AVX
#endif

#ifdef SIMD_ARCH_NS_USE_AVX2
#undef SIMD_ARCH_NS_USE_AVX2
#endif

#ifdef SIMD_ARCH_NS_USE_AVX512F
#undef SIMD_ARCH_NS_USE_AVX512F
#endif

#ifdef SIMD_ARCH_NS_USE_AVX512BW
#undef SIMD_ARCH_NS_USE_AVX512BW
#endif

#ifdef SIMD_ARCH_NS_USE_AVX512DQ
#undef SIMD_ARCH_NS_USE_AVX512DQ
#endif

#ifdef SIMD_ARCH_NS_USE_AVX512VL
#undef SIMD_ARCH_NS_USE_AVX512VL
#endif

#ifdef SIMD_ARCH_NS_USE_FMA3
#undef SIMD_ARCH_NS_USE_FMA3
#endif

#ifdef SIMD_ARCH_NS_USE_FMA4
#undef SIMD_ARCH_NS_USE_FMA4
#endif

#ifdef SIMD_ARCH_NS_USE_XOP
#undef SIMD_ARCH_NS_USE_XOP
#endif

#ifdef SIMD_ARCH_NS_USE_NEON
#undef SIMD_ARCH_NS_USE_NEON
#endif

#ifdef SIMD_ARCH_NS_USE_NEON_FLT_SP
#undef SIMD_ARCH_NS_USE_NEON_FLT_SP
#endif

#ifdef SIMD_ARCH_NS_USE_ALTIVEC
#undef SIMD_ARCH_NS_USE_ALTIVEC
#endif

#ifdef SIMD_ARCH_NS_USE_VSX_206
#undef SIMD_ARCH_NS_USE_VSX_206
#endif

#ifdef SIMD_ARCH_NS_USE_VSX_207
#undef SIMD_ARCH_NS_USE_VSX_207
#endif

#ifdef SIMD_ARCH_NS_USE_MSA
#undef SIMD_ARCH_NS_USE_MSA
#endif

#ifdef SIMD_ARCH_LIST

#define SIMD_ARCH_CREATE_MASK2(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, ...)                       \
    SIMD_CAT(SIMD_PREFIX_, x0) | SIMD_CAT(SIMD_PREFIX_, x1) | SIMD_CAT(SIMD_PREFIX_, x2) | SIMD_CAT(SIMD_PREFIX_, x3) \
        | SIMD_CAT(SIMD_PREFIX_, x4) | SIMD_CAT(SIMD_PREFIX_, x5) | SIMD_CAT(SIMD_PREFIX_, x6)                        \
        | SIMD_CAT(SIMD_PREFIX_, x7) | SIMD_CAT(SIMD_PREFIX_, x8) | SIMD_CAT(SIMD_PREFIX_, x9)                        \
        | SIMD_CAT(SIMD_PREFIX_, x10) | SIMD_CAT(SIMD_PREFIX_, x11) | SIMD_CAT(SIMD_PREFIX_, x12)                     \
        | SIMD_CAT(SIMD_PREFIX_, x13)

#define SIMD_ARCH_CREATE_MASK(...) \
    SIMD_EXPAND(SIMD_ARCH_CREATE_MASK2(__VA_ARGS__, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0))
#define SIMD_ARCH_MASK SIMD_ARCH_CREATE_MASK(SIMD_ARCH_LIST)

#if ((SIMD_ARCH_MASK)&SIMD_INSN_MASK_SSE2) == SIMD_INSN_MASK_SSE2
#define SIMD_ARCH_USE_SSE2 1
#endif

#if ((SIMD_ARCH_MASK)&SIMD_INSN_MASK_SSE3) == SIMD_INSN_MASK_SSE3
#define SIMD_ARCH_USE_SSE3 1
#endif

#if ((SIMD_ARCH_MASK)&SIMD_INSN_MASK_SSSE3) == SIMD_INSN_MASK_SSSE3
#define SIMD_ARCH_USE_SSSE3 1
#endif

#if ((SIMD_ARCH_MASK)&SIMD_INSN_MASK_SSE4_1) == SIMD_INSN_MASK_SSE4_1
#define SIMD_ARCH_USE_SSE4_1 1
#endif

#if ((SIMD_ARCH_MASK)&SIMD_INSN_MASK_SSE4_2) == SIMD_INSN_MASK_SSE4_2
#define SIMD_ARCH_USE_SSE4_2 1
#endif

#if ((SIMD_ARCH_MASK)&SIMD_INSN_MASK_SSE4A) == SIMD_INSN_MASK_SSE4A
#define SIMD_ARCH_USE_SSE4A 1
#endif

#if ((SIMD_ARCH_MASK)&SIMD_INSN_MASK_POPCNT_INSN) == SIMD_INSN_MASK_POPCNT_INSN
#define SIMD_ARCH_USE_X86_POPCNT_INSN 1
#endif

#if ((SIMD_ARCH_MASK)&SIMD_INSN_MASK_AVX) == SIMD_INSN_MASK_AVX
#define SIMD_ARCH_USE_AVX 1
#endif

#if ((SIMD_ARCH_MASK)&SIMD_INSN_MASK_AVX2) == SIMD_INSN_MASK_AVX2
#define SIMD_ARCH_USE_AVX2 1
#endif

#if ((SIMD_ARCH_MASK)&SIMD_INSN_MASK_FMA3) == SIMD_INSN_MASK_FMA3
#define SIMD_ARCH_USE_FMA3 1
#endif

#if ((SIMD_ARCH_MASK)&SIMD_INSN_MASK_FMA4) == SIMD_INSN_MASK_FMA4
#define SIMD_ARCH_USE_FMA4 1
#endif

#if ((SIMD_ARCH_MASK)&SIMD_INSN_MASK_XOP) == SIMD_INSN_MASK_XOP
#define SIMD_ARCH_USE_XOP 1
#endif

#if ((SIMD_ARCH_MASK)&SIMD_INSN_MASK_AVX512F) == SIMD_INSN_MASK_AVX512F
#define SIMD_ARCH_USE_AVX512F 1
#endif

#if ((SIMD_ARCH_MASK)&SIMD_INSN_MASK_AVX512BW) == SIMD_INSN_MASK_AVX512BW
#define SIMD_ARCH_USE_AVX512BW 1
#endif

#if ((SIMD_ARCH_MASK)&SIMD_INSN_MASK_AVX512DQ) == SIMD_INSN_MASK_AVX512DQ
#define SIMD_ARCH_USE_AVX512DQ 1
#endif

#if ((SIMD_ARCH_MASK)&SIMD_INSN_MASK_AVX512VL) == SIMD_INSN_MASK_AVX512VL
#define SIMD_ARCH_USE_AVX512VL 1
#endif

#if ((SIMD_ARCH_MASK)&SIMD_INSN_MASK_NEON) == SIMD_INSN_MASK_NEON
#define SIMD_ARCH_USE_NEON 1
#endif

#if ((SIMD_ARCH_MASK)&SIMD_INSN_MASK_NEON_FLT_SP) == SIMD_INSN_MASK_NEON_FLT_SP
#define SIMD_ARCH_USE_NEON_FLT_SP 1
#endif

#if ((SIMD_ARCH_MASK)&SIMD_INSN_MASK_ALTIVEC) == SIMD_INSN_MASK_ALTIVEC
#define SIMD_ARCH_USE_ALTIVEC 1
#endif

#if ((SIMD_ARCH_MASK)&SIMD_INSN_MASK_VSX_206) == SIMD_INSN_MASK_VSX_206
#define SIMD_ARCH_USE_VSX_206 1
#endif

#if ((SIMD_ARCH_MASK)&SIMD_INSN_MASK_VSX_207) == SIMD_INSN_MASK_VSX_207
#define SIMD_ARCH_USE_VSX_207 1
#endif

#if ((SIMD_ARCH_MASK)&SIMD_INSN_MASK_MSA) == SIMD_INSN_MASK_MSA
#define SIMD_ARCH_USE_MSA 1
#endif

#undef SIMD_ARCH_MASK
#undef SIMD_ARCH_CREATE_MASK2
#undef SIMD_ARCH_CREATE_MASK

#else

#ifdef SIMD_ARCH_X86_SSE2
#define SIMD_ARCH_USE_SSE2 1
#undef SIMD_ARCH_X86_SSE2
#endif
#ifdef SIMD_ARCH_X86_SSE3
#define SIMD_ARCH_USE_SSE3 1
#undef SIMD_ARCH_X86_SSE3
#endif
#ifdef SIMD_ARCH_X86_SSSE3
#define SIMD_ARCH_USE_SSSE3 1
#undef SIMD_ARCH_X86_SSSE3
#endif
#ifdef SIMD_ARCH_X86_SSE4_1
#define SIMD_ARCH_USE_SSE4_1 1
#undef SIMD_ARCH_X86_SSE4_1
#endif
#ifdef SIMD_ARCH_X86_SSE4_2
#define SIMD_ARCH_USE_SSE4_2 1
#undef SIMD_ARCH_X86_SSE4_2
#endif
#ifdef SIMD_ARCH_X86_SSE4A
#define SIMD_ARCH_USE_SSE4A 1
#undef SIMD_ARCH_X86_SSE4A
#endif
#ifdef SIMD_ARCH_X86_POPCNT_INSN
#define SIMD_ARCH_USE_X86_POPCNT_INSN 1
#undef SIMD_ARCH_X86_POPCNT_INSN
#endif
#ifdef SIMD_ARCH_X86_AVX
#define SIMD_ARCH_USE_AVX 1
#undef SIMD_ARCH_X86_AVX
#endif
#ifdef SIMD_ARCH_X86_AVX2
#define SIMD_ARCH_USE_AVX2 1
#undef SIMD_ARCH_X86_AVX2
#endif
#ifdef SIMD_ARCH_X86_FMA3
#define SIMD_ARCH_USE_FMA3 1
#undef SIMD_ARCH_X86_FMA3
#endif
#ifdef SIMD_ARCH_X86_FMA4
#define SIMD_ARCH_USE_FMA4 1
#undef SIMD_ARCH_X86_FMA4
#endif
#ifdef SIMD_ARCH_X86_XOP
#define SIMD_ARCH_USE_XOP 1
#undef SIMD_ARCH_X86_XOP
#endif
#ifdef SIMD_ARCH_X86_AVX512F
#define SIMD_ARCH_USE_AVX512F 1
#undef SIMD_ARCH_X86_AVX512F
#endif
#ifdef SIMD_ARCH_X86_AVX512BW
#define SIMD_ARCH_USE_AVX512BW 1
#undef SIMD_ARCH_X86_AVX512BW
#endif
#ifdef SIMD_ARCH_X86_AVX512DQ
#define SIMD_ARCH_USE_AVX512DQ 1
#undef SIMD_ARCH_X86_AVX512DQ
#endif
#ifdef SIMD_ARCH_X86_AVX512VL
#define SIMD_ARCH_USE_AVX512VL 1
#undef SIMD_ARCH_X86_AVX512VL
#endif
#ifdef SIMD_ARCH_ARM_NEON
#define SIMD_ARCH_USE_NEON 1
#undef SIMD_ARCH_ARM_NEON
#endif
#ifdef SIMD_ARCH_ARM_NEON_FLT_SP
#define SIMD_ARCH_USE_NEON_FLT_SP 1
#undef SIMD_ARCH_ARM_NEON_FLT_SP
#endif
#ifdef SIMD_ARCH_POWER_ALTIVEC
#define SIMD_ARCH_USE_ALTIVEC 1
#undef SIMD_ARCH_POWER_ALTIVEC
#endif
#ifdef SIMD_ARCH_POWER_VSX_206
#define SIMD_ARCH_USE_VSX_206 1
#undef SIMD_ARCH_POWER_VSX_206
#endif
#ifdef SIMD_ARCH_POWER_VSX_207
#define SIMD_ARCH_USE_VSX_207 1
#undef SIMD_ARCH_POWER_VSX_207
#endif
#ifdef SIMD_ARCH_MIPS_MSA
#define SIMD_ARCH_USE_MSA 1
#undef SIMD_ARCH_MIPS_MSA
#endif
#endif

// Define support of instruction sets that are implicitly available when another
// instruction set is available
#if SIMD_ARCH_USE_AVX512VL
#ifndef SIMD_ARCH_USE_AVX512F
#define SIMD_ARCH_USE_AVX512F 1
#endif
#endif

#if SIMD_ARCH_USE_AVX512DQ
#ifndef SIMD_ARCH_USE_AVX512F
#define SIMD_ARCH_USE_AVX512F 1
#endif
#endif

#if SIMD_ARCH_USE_AVX512BW
#ifndef SIMD_ARCH_USE_AVX512F
#define SIMD_ARCH_USE_AVX512F 1
#endif
#endif

#if SIMD_ARCH_USE_AVX512F
#ifndef SIMD_ARCH_USE_AVX2
#define SIMD_ARCH_USE_AVX2 1
#endif
#endif

#if SIMD_ARCH_USE_AVX2
#ifndef SIMD_ARCH_USE_AVX
#define SIMD_ARCH_USE_AVX 1
#endif
#endif

#if SIMD_ARCH_USE_AVX
#ifndef SIMD_ARCH_USE_SSE4_1
#define SIMD_ARCH_USE_SSE4_1 1
#endif
#ifndef SIMD_ARCH_USE_SSE4_2
#define SIMD_ARCH_USE_SSE4_2 1
#endif
#ifndef SIMD_ARCH_USE_SSE4A
#define SIMD_ARCH_USE_SSE4A 1
#endif
#endif

#if SIMD_ARCH_USE_FMA3
#ifndef SIMD_ARCH_USE_SSE3
#define SIMD_ARCH_USE_SSE3 1
#endif
#endif

#if SIMD_ARCH_USE_FMA4
#ifndef SIMD_ARCH_USE_SSE3
#define SIMD_ARCH_USE_SSE3 1
#endif
#endif

#if SIMD_ARCH_USE_XOP
#ifndef SIMD_ARCH_USE_SSE3
#define SIMD_ARCH_USE_SSE3 1
#endif
#endif

#if SIMD_ARCH_USE_SSE4_2
#ifndef SIMD_ARCH_USE_SSE4_1
#define SIMD_ARCH_USE_SSE4_1 1
#endif
#endif

#if SIMD_ARCH_USE_SSE4A
#ifndef SIMD_ARCH_USE_SSSE3
#define SIMD_ARCH_USE_SSSE3 1
#endif
#endif

#if SIMD_ARCH_USE_SSE4_1
#ifndef SIMD_ARCH_USE_SSSE3
#define SIMD_ARCH_USE_SSSE3 1
#endif
#endif

#if SIMD_ARCH_USE_X86_POPCNT_INSN
#ifndef SIMD_ARCH_USE_SSSE3
#define SIMD_ARCH_USE_SSSE3 1
#endif
#endif

#if SIMD_ARCH_USE_SSSE3
#ifndef SIMD_ARCH_USE_SSE3
#define SIMD_ARCH_USE_SSE3 1
#endif
#endif

#if SIMD_ARCH_USE_SSE3
#ifndef SIMD_ARCH_USE_SSE2
#define SIMD_ARCH_USE_SSE2 1
#endif
#endif

#if SIMD_ARCH_USE_NEON_FLT_SP
#ifndef SIMD_ARCH_USE_NEON
#define SIMD_ARCH_USE_NEON 1
#endif
#endif

#if SIMD_ARCH_USE_VSX_207
#ifndef SIMD_ARCH_USE_VSX_206
#define SIMD_ARCH_USE_VSX_206 1
#endif
#endif

#if SIMD_ARCH_USE_VSX_206
#ifndef SIMD_ARCH_USE_ALTIVEC
#define SIMD_ARCH_USE_ALTIVEC 1
#endif
#endif

#if !(SIMD_ARCH_USE_SSE2 || SIMD_ARCH_USE_NEON || SIMD_ARCH_USE_NEON_FLT_SP || SIMD_ARCH_USE_ALTIVEC \
      || SIMD_ARCH_USE_MSA)
#define SIMD_ARCH_USE_NULL 1
#endif

#if SIMD_ARCH_USE_FMA3 && SIMD_ARCH_USE_FMA4
#error "FMA3 and FMA4 can't be used together"
#endif

// To limit the length of the SIMD_ARCH_NAMESPACE and friends, we omit
// instruction sets that are subsets of other enabled instruction sets. For
// example, for SSE3 we generate arch_sse3 instead of arch_sse2_sse3.

#if SIMD_ARCH_USE_NULL
#define SIMD_ARCH_NS_USE_NULL 1
#endif

#if SIMD_ARCH_USE_SSE2 && !SIMD_ARCH_USE_SSE3
#define SIMD_ARCH_NS_USE_SSE2 1
#endif

#if SIMD_ARCH_USE_SSE3 && !SIMD_ARCH_USE_SSSE3 && !SIMD_ARCH_USE_XOP && !SIMD_ARCH_USE_FMA3 && !SIMD_ARCH_USE_FMA4
#define SIMD_ARCH_NS_USE_SSE3 1
#endif

#if SIMD_ARCH_USE_SSSE3 && !SIMD_ARCH_USE_SSE4_1
#define SIMD_ARCH_NS_USE_SSSE3 1
#endif

#if SIMD_ARCH_USE_SSE4_1 && !SIMD_ARCH_USE_SSE4_2 && !SIMD_ARCH_USE_AVX
#define SIMD_ARCH_NS_USE_SSE4_1 1
#endif

#if SIMD_ARCH_USE_SSE4_2 && !SIMD_ARCH_USE_AVX
#define SIMD_ARCH_NS_USE_SSE4_2 1
#endif

#if SIMD_ARCH_USE_SSE4A && !SIMD_ARCH_USE_AVX
#define SIMD_ARCH_NS_USE_SSE4A 1
#endif

#if SIMD_ARCH_USE_X86_POPCNT_INSN
#define SIMD_ARCH_NS_USE_POPCNT_INSN 1
#endif

#if SIMD_ARCH_USE_AVX && !SIMD_ARCH_USE_AVX2
#define SIMD_ARCH_NS_USE_AVX 1
#endif

#if SIMD_ARCH_USE_AVX2 && !SIMD_ARCH_USE_AVX512F
#define SIMD_ARCH_NS_USE_AVX2 1
#endif

#if SIMD_ARCH_USE_AVX512F && !SIMD_ARCH_USE_AVX512BW && !SIMD_ARCH_USE_AVX512DQ && !SIMD_ARCH_USE_AVX512VL
#define SIMD_ARCH_NS_USE_AVX512F 1
#endif

#if SIMD_ARCH_USE_AVX512BW
#define SIMD_ARCH_NS_USE_AVX512BW 1
#endif

#if SIMD_ARCH_USE_AVX512DQ
#define SIMD_ARCH_NS_USE_AVX512DQ 1
#endif

#if SIMD_ARCH_USE_AVX512VL
#define SIMD_ARCH_NS_USE_AVX512VL 1
#endif

#if SIMD_ARCH_USE_FMA3
#define SIMD_ARCH_NS_USE_FMA3 1
#endif

#if SIMD_ARCH_USE_FMA4
#define SIMD_ARCH_NS_USE_FMA4 1
#endif

#if SIMD_ARCH_USE_XOP
#define SIMD_ARCH_NS_USE_XOP 1
#endif

#if SIMD_ARCH_USE_NEON && !SIMD_ARCH_USE_NEON_FLT_SP
#define SIMD_ARCH_NS_USE_NEON 1
#endif

#if SIMD_ARCH_USE_NEON_FLT_SP
#define SIMD_ARCH_NS_USE_NEON_FLT_SP 1
#endif

#if SIMD_ARCH_USE_ALTIVEC && !SIMD_ARCH_USE_VSX_206
#define SIMD_ARCH_NS_USE_ALTIVEC 1
#endif

#if SIMD_ARCH_USE_VSX_206 && !SIMD_ARCH_USE_VSX_207
#define SIMD_ARCH_NS_USE_VSX_206 1
#endif

#if SIMD_ARCH_USE_VSX_207
#define SIMD_ARCH_NS_USE_VSX_207 1
#endif

#if SIMD_ARCH_USE_MSA
#define SIMD_ARCH_NS_USE_MSA 1
#endif
