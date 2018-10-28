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

#ifndef DISPATCH_GET_ARCH_GCC_BUILTIN_CPU_SUPPORTS_H
#define DISPATCH_GET_ARCH_GCC_BUILTIN_CPU_SUPPORTS_H

#if ((__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 8)) && (__i386__ || __amd64__)
#define SIMD_HAS_GET_ARCH_GCC_BUILTIN_CPU_SUPPORTS 1

#include <bigmath/simd/dispatch/arch.h>

namespace simd {

    /** Retrieves supported architecture using GCC __builtin_cpu_supports function.
        Works only on x86.
    */
    inline Arch get_arch_gcc_builtin_cpu_supports() {
        Arch arch_info = Arch::NONE_NULL;
#if (__GNUC__ > 4)
        if (__builtin_cpu_supports("avx512f")) { // since 5.0
            arch_info |= Arch::X86_SSE2;
            arch_info |= Arch::X86_SSE3;
            arch_info |= Arch::X86_SSSE3;
            arch_info |= Arch::X86_SSE4_1;
            arch_info |= Arch::X86_SSE4_2;
            arch_info |= Arch::X86_AVX;
            arch_info |= Arch::X86_AVX2;
            arch_info |= Arch::X86_FMA3;
            arch_info |= Arch::X86_AVX512F;
        } else
#endif
            if (__builtin_cpu_supports("avx2")) {
            arch_info |= Arch::X86_SSE2;
            arch_info |= Arch::X86_SSE3;
            arch_info |= Arch::X86_SSSE3;
            arch_info |= Arch::X86_SSE4_1;
            arch_info |= Arch::X86_SSE4_2;
            arch_info |= Arch::X86_AVX;
            arch_info |= Arch::X86_AVX2;
        } else if (__builtin_cpu_supports("avx")) {
            arch_info |= Arch::X86_SSE2;
            arch_info |= Arch::X86_SSE3;
            arch_info |= Arch::X86_SSSE3;
            arch_info |= Arch::X86_SSE4_1;
            arch_info |= Arch::X86_SSE4_2;
            arch_info |= Arch::X86_AVX;
        } else if (__builtin_cpu_supports("sse4.1")) {
            arch_info |= Arch::X86_SSE2;
            arch_info |= Arch::X86_SSE3;
            arch_info |= Arch::X86_SSSE3;
            arch_info |= Arch::X86_SSE4_1;
        } else if (__builtin_cpu_supports("sse4.2")) {
            arch_info |= Arch::X86_SSE2;
            arch_info |= Arch::X86_SSE3;
            arch_info |= Arch::X86_SSSE3;
            arch_info |= Arch::X86_SSE4_1;
            arch_info |= Arch::X86_SSE4_2;
            arch_info |= Arch::X86_POPCNT_INSN;
        } else if (__builtin_cpu_supports("sse4a")) {
            arch_info |= Arch::X86_SSE2;
            arch_info |= Arch::X86_SSE3;
            arch_info |= Arch::X86_SSSE3;
            arch_info |= Arch::X86_SSE4a;
        } else if (__builtin_cpu_supports("ssse3")) {
            arch_info |= Arch::X86_SSE2;
            arch_info |= Arch::X86_SSE3;
            arch_info |= Arch::X86_SSSE3;
        } else if (__builtin_cpu_supports("sse3")) {
            arch_info |= Arch::X86_SSE3;
            arch_info |= Arch::X86_SSE2;
        } else if (__builtin_cpu_supports("sse2")) {
            arch_info |= Arch::X86_SSE2;
        }
        if (__builtin_cpu_supports("popcnt"))
            arch_info |= Arch::X86_POPCNT_INSN;

        return arch_info;
    }
} // namespace simd

#endif
#endif // DISPATCH_GET_ARCH_GCC_BUILTIN_CPU_SUPPORTS_H
