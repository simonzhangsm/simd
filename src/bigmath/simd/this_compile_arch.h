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

#ifndef SIMD_THIS_COMPILE_ARCH_H
#define SIMD_THIS_COMPILE_ARCH_H

#include <bigmath/simd/dispatch/arch.h>

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif
#include <bigmath/simd/setup_arch.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {

        /** Returns the instruction set flags that will be required by the currently
            compiled code
        */
        inline Arch this_compile_arch() {
            Arch res = Arch::NONE_NULL;
#if SIMD_USE_SSE2
            res |= Arch::X86_SSE2;
#endif
#if SIMD_USE_SSE3
            res |= Arch::X86_SSE3;
#endif
#if SIMD_USE_SSSE3
            res |= Arch::X86_SSSE3;
#endif
#if SIMD_USE_SSE4_1
            res |= Arch::X86_SSE4_1;
#endif
#if SIMD_USE_SSE4_2
            res |= Arch::X86_SSE4_2;
#endif
#if SIMD_USE_SSE4A
            res |= Arch::X86_SSE4A;
#endif
#if SIMD_USE_X86_POPCNT_INSN
            res |= Arch::X86_POPCNT_INSN;
#endif
#if SIMD_USE_AVX
            res |= Arch::X86_AVX;
#endif
#if SIMD_USE_AVX2
            res |= Arch::X86_AVX2;
#endif
#if SIMD_USE_FMA3
            res |= Arch::X86_FMA3;
#endif
#if SIMD_USE_FMA4
            res |= Arch::X86_FMA4;
#endif
#if SIMD_USE_XOP
            res |= Arch::X86_XOP;
#endif
#if SIMD_USE_AVX512F
            res |= Arch::X86_AVX512F;
#endif
#if SIMD_USE_AVX512BW
            res |= Arch::X86_AVX512BW;
#endif
#if SIMD_USE_AVX512DQ
            res |= Arch::X86_AVX512DQ;
#endif
#if SIMD_USE_AVX512VL
            res |= Arch::X86_AVX512VL;
#endif
#if SIMD_USE_NEON
            res |= Arch::ARM_NEON;
#endif
#if SIMD_USE_NEON_FLT_SP
            res |= Arch::ARM_NEON_FLT_SP;
#endif
#if SIMD_USE_ALTIVEC
            res |= Arch::POWER_ALTIVEC;
#endif
#if SIMD_USE_VSX_206
            res |= Arch::POWER_VSX_206;
#endif
#if SIMD_USE_VSX_207
            res |= Arch::POWER_VSX_207;
#endif
#if SIMD_USE_MSA
            res |= Arch::MIPS_MSA;
#endif
            return res;
        }

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
