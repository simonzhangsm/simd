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

#ifndef DISPATCH_ARCH_H
#define DISPATCH_ARCH_H

#include <cstdint>

namespace simd {

    /** Identifies supported instruction set. This type is a bitmask type

        Note: the exact values may change release to release.
    */
    /*  The values are assigned in such a way that the result of comparison of two
        ORed flag sets is likely identify which instruction set the binary is more
        likely to run faster on.

        detail::select_version depends on this.
    */
    enum class Arch : std::uint32_t {
        /// Indicates that no SIMD instructions are supported
        NONE_NULL = 0x00000000,
        /// Indicates x86 SSE2 support
        X86_SSE2 = 0x00000002,
        /// Indicates x86 SSE3 support
        X86_SSE3 = 0x00000004,
        /// Indicates x86 SSSE3 support
        X86_SSSE3 = 0x00000008,
        /// Indicates x86 SSE4.1 support
        X86_SSE4_1 = 0x00000010,
        /// Indicates x86 SSE4.2 support
        X86_SSE4_2 = 0x00000020,
        /// Indicates x86 SSE4A support
        X86_SSE4A = 0x00000040,
        /// Indicates x86 popcnt instruction support (Note: this is not equivalent
        /// to the ABM CPUID flag, Intel includes the instruction into SSE 4.2)
        X86_POPCNT_INSN = 0x00000080,
        /// Indicates x86 AVX support
        X86_AVX = 0x00000100,
        /// Indicates x86 AVX2 support
        X86_AVX2 = 0x00000200,
        /// Indicates x86 FMA3 (Intel) support
        X86_FMA3 = 0x00000400,
        /// Indicates x86 FMA4 (AMD) support
        X86_FMA4 = 0x00000800,
        /// Indicates x86 XOP (AMD) support
        X86_XOP = 0x00001000,
        /// Indicates x86 AVX-512F suppotr
        X86_AVX512F = 0x00002000,
        /// Indicates x86 AVX-512BW suppotr
        X86_AVX512BW = 0x00004000,
        /// Indicates x86 AVX-512DQ suppotr
        X86_AVX512DQ = 0x00008000,
        /// Indicates x86 AVX-512VL suppotr
        X86_AVX512VL = 0x00010000,

        /// Indicates ARM NEON support (SP and DP floating-point math is executed
        /// on VFP)
        ARM_NEON = 0x00020000,
        /// Indicates ARM NEON support (SP floating-point math is executed on NEON,
        /// DP floating-point math is executed on VFP)
        ARM_NEON_FLT_SP = 0x00040000,

        /// Indicates POWER ALTIVEC support.
        POWER_ALTIVEC = 0x00080000,

        /// Indicates POWER VSX support available since Power ISA 2.06
        POWER_VSX_206 = 0x00100000,

        /// Indicates POWER VSX support available since Power ISA 2.07
        POWER_VSX_207 = 0x00200000,

        /// Indicates MIPS MSA support
        MIPS_MSA = 0x00400000
    };

    /// Bitwise operators for @c Arch
    inline Arch &operator|=(Arch &x, const Arch &y) {
        using T = std::uint32_t;
        x = static_cast<Arch>(static_cast<T>(x) | static_cast<T>(y));
        return x;
    }

    inline Arch &operator&=(Arch &x, const Arch &y) {
        using T = std::uint32_t;
        x = static_cast<Arch>(static_cast<T>(x) & static_cast<T>(y));
        return x;
    }

    inline Arch operator|(const Arch &x, const Arch &y) {
        using T = std::uint32_t;
        return static_cast<Arch>(static_cast<T>(x) | static_cast<T>(y));
    }

    inline Arch operator&(const Arch &x, const Arch &y) {
        using T = std::uint32_t;
        return static_cast<Arch>(static_cast<T>(x) & static_cast<T>(y));
    }

    inline Arch operator~(const Arch &x) {
        using T = std::uint32_t;
        return static_cast<Arch>(~static_cast<T>(x));
    }

    /// Checks if the bits set in @a required is a subset of bits set in @a current.
    inline bool test_arch_subset(Arch current, Arch required) {
        if ((~current & required) == Arch::NONE_NULL) {
            return true;
        }
        return false;
    }

} // namespace simd

#endif
