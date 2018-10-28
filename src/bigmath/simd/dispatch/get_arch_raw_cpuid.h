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

#ifndef DISPATCH_GET_ARCH_RAW_CPUID_H
#define DISPATCH_GET_ARCH_RAW_CPUID_H

#include <bigmath/simd/setup_arch.h>

#if SIMD_X86 && (__clang__ || __GNUC__ || __INTEL_COMPILER || _MSC_VER)
#define SIMD_HAS_GET_ARCH_RAW_CPUID 1

#include <bigmath/simd/dispatch/arch.h>
#include <cstdint>

#if __GNUC__

#include <cpuid.h>

#else

/* %ecx */
#define bit_SSE3 (1 << 0)
#define bit_PCLMUL (1 << 1)
#define bit_LZCNT (1 << 5)
#define bit_SSSE3 (1 << 9)
#define bit_FMA (1 << 12)
#define bit_CMPXCHG16B (1 << 13)
#define bit_SSE4_1 (1 << 19)
#define bit_SSE4_2 (1 << 20)
#define bit_MOVBE (1 << 22)
#define bit_POPCNT (1 << 23)
#define bit_AES (1 << 25)
#define bit_XSAVE (1 << 26)
#define bit_OSXSAVE (1 << 27)
#define bit_AVX (1 << 28)
#define bit_F16C (1 << 29)
#define bit_RDRND (1 << 30)

/* %edx */
#define bit_CMPXCHG8B (1 << 8)
#define bit_CMOV (1 << 15)
#define bit_MMX (1 << 23)
#define bit_FXSAVE (1 << 24)
#define bit_SSE (1 << 25)
#define bit_SSE2 (1 << 26)

/* Extended Features (%eax == 0x80000001) */
/* %ecx */
#define bit_LAHF_LM (1 << 0)
#define bit_ABM (1 << 5)
#define bit_SSE4a (1 << 6)
#define bit_PRFCHW (1 << 8)
#define bit_XOP (1 << 11)
#define bit_LWP (1 << 15)
#define bit_FMA4 (1 << 16)
#define bit_TBM (1 << 21)
#define bit_MWAITX (1 << 29)

/* %edx */
#define bit_MMXEXT (1 << 22)
#define bit_LM (1 << 29)
#define bit_3DNOWP (1 << 30)
#define bit_3DNOW (1u << 31)

/* %ebx  */
#define bit_CLZERO (1 << 0)
#define bit_WBNOINVD (1 << 9)

/* Extended Features (%eax == 7) */
/* %ebx */
#define bit_FSGSBASE (1 << 0)
#define bit_SGX (1 << 2)
#define bit_BMI (1 << 3)
#define bit_HLE (1 << 4)
#define bit_AVX2 (1 << 5)
#define bit_BMI2 (1 << 8)
#define bit_RTM (1 << 11)
#define bit_MPX (1 << 14)
#define bit_AVX512F (1 << 16)
#define bit_AVX512DQ (1 << 17)
#define bit_RDSEED (1 << 18)
#define bit_ADX (1 << 19)
#define bit_AVX512IFMA (1 << 21)
#define bit_CLFLUSHOPT (1 << 23)
#define bit_CLWB (1 << 24)
#define bit_AVX512PF (1 << 26)
#define bit_AVX512ER (1 << 27)
#define bit_AVX512CD (1 << 28)
#define bit_SHA (1 << 29)
#define bit_AVX512BW (1 << 30)
#define bit_AVX512VL (1u << 31)

/* %ecx */
#define bit_PREFETCHWT1 (1 << 0)
#define bit_AVX512VBMI (1 << 1)
#define bit_PKU (1 << 3)
#define bit_OSPKE (1 << 4)
#define bit_WAITPKG (1 << 5)
#define bit_AVX512VBMI2 (1 << 6)
#define bit_SHSTK (1 << 7)
#define bit_GFNI (1 << 8)
#define bit_VAES (1 << 9)
#define bit_AVX512VNNI (1 << 11)
#define bit_VPCLMULQDQ (1 << 10)
#define bit_AVX512BITALG (1 << 12)
#define bit_AVX512VPOPCNTDQ (1 << 14)
#define bit_RDPID (1 << 22)
#define bit_MOVDIRI (1 << 27)
#define bit_MOVDIR64B (1 << 28)
#define bit_CLDEMOTE (1 << 25)

/* %edx */
#define bit_AVX5124VNNIW (1 << 2)
#define bit_AVX5124FMAPS (1 << 3)
#define bit_IBT (1 << 20)
#define bit_PCONFIG (1 << 18)
/* XFEATURE_ENABLED_MASK register bits (%eax == 13, %ecx == 0) */
#define bit_BNDREGS (1 << 3)
#define bit_BNDCSR (1 << 4)

/* Extended State Enumeration Sub-leaf (%eax == 13, %ecx == 1) */
#define bit_XSAVEOPT (1 << 0)
#define bit_XSAVEC (1 << 1)
#define bit_XSAVES (1 << 3)

#endif

#if _MSC_VER
#include <intrin.h> // __cpuidex on MSVC 2017
#include <immintrin.h>
#endif

namespace simd {
    namespace detail {

        inline void get_cpuid(
            unsigned level, unsigned subleaf, unsigned *eax, unsigned *ebx, unsigned *ecx, unsigned *edx) {
#if __clang__ || (__INTEL_COMPILER && !_MSC_VER)
            // Older versions of clang don't support subleafs, which leads to inability
            // to detect AVX2 for example. On ICC there's no proper cpuid intrinsic.
#if SIMD_32_BITS
            __asm("cpuid" : "=a"(*eax), "=b"(*ebx), "=c"(*ecx), "=d"(*edx) : "0"(level), "2"(subleaf));
#else
            // x86-64 uses %rbx as the base register, so preserve it.
            __asm(
                "xchgq  %%rbx,%q1\n"
                "cpuid\n"
                "xchgq  %%rbx,%q1"
                : "=a"(*eax), "=b"(*ebx), "=c"(*ecx), "=d"(*edx)
                : "0"(level), "2"(subleaf));
#endif
#elif __GNUC__
            __cpuid_count(level, subleaf, *eax, *ebx, *ecx, *edx);
#elif _MSC_VER
            uint32_t regs[4];
            __cpuidex((int *)regs, level, subleaf);
            *eax = regs[0];
            *ebx = regs[1];
            *ecx = regs[2];
            *edx = regs[3];
#else
#error "unsupported compiler"
#endif
        }

        inline uint64_t get_xcr(unsigned level) {
#if (defined(_MSC_FULL_VER) && _MSC_FULL_VER >= 160040000) || (defined(__INTEL_COMPILER) && __INTEL_COMPILER >= 1200)
            return _xgetbv(level);
#elif defined(__GNUC__) || defined(__clang__)
            uint32_t eax, edx;
            __asm("xgetbv" : "=a"(eax), "=d"(edx) : "c"(level) :);
            return eax | (uint64_t(edx) << 32);
#else
            return 0;
#endif
        }

        enum cpu_manufacturer { CPU_INTEL, CPU_AMD, CPU_UNKNOWN };

        static inline cpu_manufacturer get_cpu_manufacturer(uint32_t ebx, uint32_t ecx, uint32_t edx) {
            if (ebx == 0x756E6547 && ecx == 0x6C65746E && edx == 0x49656E69)
                return CPU_INTEL; // "GenuineIntel"
            if (ebx == 0x68747541 && ecx == 0x444D4163 && edx == 0x69746E65)
                return CPU_AMD; // "AuthenticAMD"
            return CPU_UNKNOWN;
        }

    } // namespace detail

    /** Retrieves supported architecture using the CPUID instruction. Works only on
        x86.
    */
    inline Arch get_arch_raw_cpuid() {
        Arch arch_info = Arch::NONE_NULL;

        uint32_t eax, ebx, ecx, edx;
        bool xsave_xrstore_avail = false;

        simd::detail::get_cpuid(0, 0, &eax, &ebx, &ecx, &edx);
        unsigned max_cpuid_level = eax;
        simd::detail::cpu_manufacturer mfg = simd::detail::get_cpu_manufacturer(ebx, ecx, edx);

        simd::detail::get_cpuid(0x80000000, 0, &eax, &ebx, &ecx, &edx);
        unsigned max_ex_cpuid_level = eax;

        if (max_cpuid_level >= 0x00000001) {
            simd::detail::get_cpuid(0x00000001, 0, &eax, &ebx, &ecx, &edx);

            if (edx & bit_SSE2)
                arch_info |= Arch::X86_SSE2;
            if (ecx & bit_SSE3)
                arch_info |= Arch::X86_SSE3;
            if (ecx & bit_SSSE3)
                arch_info |= Arch::X86_SSSE3;
            if (ecx & bit_SSE4_1)
                arch_info |= Arch::X86_SSE4_1;
            if (ecx & bit_SSE4_2) {
                arch_info |= Arch::X86_SSE4_2;
                if (mfg == simd::detail::CPU_INTEL)
                    arch_info |= Arch::X86_POPCNT_INSN; // popcnt is included in SSE4.2 on Intel
            }
            if (ecx & bit_SSE4a)
                arch_info |= Arch::X86_SSE4A;
            if (ecx & bit_POPCNT)
                arch_info |= Arch::X86_POPCNT_INSN;
            if (ecx & bit_FMA)
                arch_info |= Arch::X86_FMA3;
            if (ecx & bit_XSAVE) {
                // XSAVE/XRSTORE available on hardware, now check OS support
                uint64_t xcr = simd::detail::get_xcr(0);
                if ((xcr & 6) == 6)
                    xsave_xrstore_avail = true;
            }

            if (ecx & bit_AVX && xsave_xrstore_avail)
                arch_info |= Arch::X86_AVX;
        }
        if (max_ex_cpuid_level >= 0x80000001) {
            simd::detail::get_cpuid(0x80000001, 0, &eax, &ebx, &ecx, &edx);
            if (ecx & bit_FMA4)
                arch_info |= Arch::X86_FMA4;
            if (ecx & bit_XOP)
                arch_info |= Arch::X86_XOP;
        }

        if (max_cpuid_level >= 0x00000007) {
            simd::detail::get_cpuid(0x00000007, 0, &eax, &ebx, &ecx, &edx);
            if (ebx & bit_AVX2 && xsave_xrstore_avail)
                arch_info |= Arch::X86_AVX2;
            if (ebx & bit_AVX512F && xsave_xrstore_avail)
                arch_info |= Arch::X86_AVX512F;
            if (ebx & bit_AVX512BW && xsave_xrstore_avail)
                arch_info |= Arch::X86_AVX512BW;
            if (ebx & bit_AVX512DQ && xsave_xrstore_avail)
                arch_info |= Arch::X86_AVX512DQ;
            if (ebx & bit_AVX512VL && xsave_xrstore_avail)
                arch_info |= Arch::X86_AVX512VL;
        }

        return arch_info;
    }

} // namespace simd

#endif // #if SIMD_X86 && ...

#endif // DISPATCH_GET_ARCH_RAW_CPUID_H
