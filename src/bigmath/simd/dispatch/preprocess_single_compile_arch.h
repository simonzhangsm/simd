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

#include <bigmath/simd/dispatch/arch.h>

/*  This file setups this_compile_arch() and create_fn_version() functions
    for a particular architecture.

    The file may be included into other files multiple times, it has been
    extracted to reduce code duplication.

    The file depends on preprocess_single_arch.h being included beforehand and
    its output macros not being overridden yet. Additionally, it depends on
    SIMD_ARCH_THIS_COMPILE_ARCH_NAMESPACE being defined to appropriate
    namespace for the architecture.

    The file also depends on the definition of
    SIMD_ARCH_THIS_COMPILE_ARCH_FOR_DISPATCH. If it is defined to 0, only
    this_compile_arch() is available as
    simd::SIMD_ARCH_THIS_COMPILE_ARCH_NAMESPACE::this_compile_arch().
    If the macro is defined to nonzero, then both this_compile_arch() and
    create_fn_version() are available at
    simd::SIMD_ARCH_THIS_COMPILE_ARCH_NAMESPACE::detail::this_compile_arch() and
    simd::SIMD_ARCH_THIS_COMPILE_ARCH_NAMESPACE::detail::create_fn_version().

    This separation is required because the current architecture and the
    set of dispatched architectures (if enabled) are defined separately, and
    it's hard to figure out whether there's any overlap. If it is, then we need
    to make sure that all functions are defined only once in each namespace.
*/
namespace simd {
    namespace SIMD_ARCH_THIS_COMPILE_ARCH_NAMESPACE {

#if SIMD_ARCH_THIS_COMPILE_ARCH_FOR_DISPATCH
        namespace detail {
#endif

            /** Returns the instruction set flags that will be required by the currently
                compiled code
            */
            static inline Arch this_compile_arch() {
                Arch res = Arch::NONE_NULL;
#if SIMD_ARCH_USE_SSE2
                res |= Arch::X86_SSE2;
#endif

#if SIMD_ARCH_USE_SSE3
                res |= Arch::X86_SSE3;
#endif

#if SIMD_ARCH_USE_SSSE3
                res |= Arch::X86_SSSE3;
#endif

#if SIMD_ARCH_USE_SSE4_1
                res |= Arch::X86_SSE4_1;
#endif

#if SIMD_ARCH_USE_SSE4_2
                res |= Arch::X86_SSE4_2;
#endif

#if SIMD_ARCH_USE_SSE4A
                res |= Arch::X86_SSE4A;
#endif

#if SIMD_ARCH_USE_X86_POPCNT_INSN
                res |= Arch::X86_POPCNT_INSN;
#endif

#if SIMD_ARCH_USE_AVX
                res |= Arch::X86_AVX;
#endif

#if SIMD_ARCH_USE_AVX2
                res |= Arch::X86_AVX2;
#endif

#if SIMD_ARCH_USE_FMA3
                res |= Arch::X86_FMA3;
#endif

#if SIMD_ARCH_USE_FMA4
                res |= Arch::X86_FMA4;
#endif

#if SIMD_ARCH_USE_XOP
                res |= Arch::X86_XOP;
#endif

#if SIMD_ARCH_USE_AVX512F
                res |= Arch::X86_AVX512F;
#endif

#if SIMD_ARCH_USE_AVX512BW
                res |= Arch::X86_AVX512BW;
#endif

#if SIMD_ARCH_USE_AVX512DQ
                res |= Arch::X86_AVX512DQ;
#endif

#if SIMD_ARCH_USE_AVX512VL
                res |= Arch::X86_AVX512VL;
#endif

#if SIMD_ARCH_USE_NEON
                res |= Arch::ARM_NEON;
#endif

#if SIMD_ARCH_USE_NEON_FLT_SP
                res |= Arch::ARM_NEON_FLT_SP;
#endif

#if SIMD_ARCH_USE_ALTIVEC
                res |= Arch::POWER_ALTIVEC;
#endif

#if SIMD_ARCH_USE_VSX_206
                res |= Arch::POWER_VSX_206;
#endif

#if SIMD_ARCH_USE_VSX_207
                res |= Arch::POWER_VSX_207;
#endif

#if SIMD_ARCH_USE_MSA
                res |= Arch::MIPS_MSA;
#endif
                return res;
            }

#if SIMD_ARCH_THIS_COMPILE_ARCH_FOR_DISPATCH
#include <bigmath/simd/detail/preprocessor/stringize.hpp>
#include <bigmath/simd/dispatch/dispatcher.h>

            template <class FunPtr> static inline simd::detail::FnVersion create_fn_version(FunPtr fun_ptr) {
                simd::detail::FnVersion res;
                res.needed_arch = simd::SIMD_ARCH_THIS_COMPILE_ARCH_NAMESPACE::detail::this_compile_arch();
                res.fun_ptr = reinterpret_cast<simd::detail::VoidFunPtr>(fun_ptr);
                res.arch_name = SIMD_STRINGIZE(SIMD_ARCH_THIS_COMPILE_ARCH_NAMESPACE);
                return res;
            }

#endif

#if SIMD_ARCH_THIS_COMPILE_ARCH_FOR_DISPATCH
        }
#endif

    } // namespace SIMD_ARCH_THIS_COMPILE_ARCH_NAMESPACE
} // namespace simd

// this file may be included several times; thus no include guard present
