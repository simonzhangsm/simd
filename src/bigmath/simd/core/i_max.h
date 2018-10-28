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

#ifndef SIMD_CORE_I_MAX_H
#define SIMD_CORE_I_MAX_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/insn/i_max.h>
#include <bigmath/simd/core/detail/scalar_arg_impl.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {


        /** Computes maximum of the signed 8-bit values.

            @code
            r0 = max(a0, b0)
            ...
            rN = max(aN, bN)
            @endcode

            @par 128-bit version:
            @icost{SSE2-SSSE3, 4}

            @par 256-bit version:
            @icost{SSE2-SSSE3, 8}
            @icost{SSE4.1-AVX, NEON, ALTIVEC, 2}
        */
        template <unsigned N, class E1, class E2>
        inline int8<N, expr_empty> max(const int8<N, E1> &a, const int8<N, E2> &b) {
            return detail::insn::i_max(a.eval(), b.eval());
        }

        SIMD_SCALAR_ARG_IMPL_VEC(max, int8, int8)

        /** Computes maximum of the unsigned 8-bit values.

            @code
            r0 = max(a0, b0)
            ...
            rN = max(aN, bN)
            @endcode

            @par 256-bit version:
            @icost{SSE2-AVX, NEON, ALTIVEC, 2}
        */
        template <unsigned N, class E1, class E2>
        inline uint8<N, expr_empty> max(const uint8<N, E1> &a, const uint8<N, E2> &b) {
            return detail::insn::i_max(a.eval(), b.eval());
        }

        SIMD_SCALAR_ARG_IMPL_VEC(max, uint8, uint8)

        /** Computes maximum of the signed 16-bit values.

            @code
            r0 = max(a0, b0)
            ...
            rN = max(aN, bN)
            @endcode

            @par 256-bit version:
            @icost{SSE2-AVX, NEON, ALTIVEC, 2}
        */
        template <unsigned N, class E1, class E2>
        inline int16<N, expr_empty> max(const int16<N, E1> &a, const int16<N, E2> &b) {
            return detail::insn::i_max(a.eval(), b.eval());
        }

        SIMD_SCALAR_ARG_IMPL_VEC(max, int16, int16)

        /** Computes maximum of the unsigned 16-bit values.

            @code
            r0 = max(a0, b0)
            ...
            rN = max(aN, bN)
            @endcode

            @par 128-bit version:
            @icost{SSE2-SSSE3, 6-7}

            @par 256-bit version:
            @icost{SSE2-SSSE3, 12-13}
            @icost{SSE4.1-AVX, NEON, ALTIVEC, 2}
        */
        template <unsigned N, class E1, class E2>
        inline uint16<N, expr_empty> max(const uint16<N, E1> &a, const uint16<N, E2> &b) {
            return detail::insn::i_max(a.eval(), b.eval());
        }

        SIMD_SCALAR_ARG_IMPL_VEC(max, uint16, uint16)

        /** Computes maximum of the signed 32-bit values.

            @code
            r0 = max(a0, b0)
            ...
            rN = max(aN, bN)
            @endcode

            @par 128-bit version:
            @icost{SSE2-SSSE3, 4}

            @par 256-bit version:
            @icost{SSE2-SSSE3, 8}
            @icost{SSE4.1-AVX, NEON, ALTIVEC, 2}
        */
        template <unsigned N, class E1, class E2>
        inline int32<N, expr_empty> max(const int32<N, E1> &a, const int32<N, E2> &b) {
            return detail::insn::i_max(a.eval(), b.eval());
        }

        SIMD_SCALAR_ARG_IMPL_VEC(max, int32, int32)

        /** Computes maximum of the unsigned 32-bit values.

            @code
            r0 = max(a0, b0)
            ...
            rN = max(aN, bN)
            @endcode

            @par 128-bit version:
            @icost{SSE2-SSSE3, 6-7}

            @par 256-bit version:
            @icost{SSE2-SSSE3, 12-13}
            @icost{SSE4.1-AVX, NEON, ALTIVEC, 2}
        */
        template <unsigned N, class E1, class E2>
        inline uint32<N, expr_empty> max(const uint32<N, E1> &a, const uint32<N, E2> &b) {
            return detail::insn::i_max(a.eval(), b.eval());
        }

        SIMD_SCALAR_ARG_IMPL_VEC(max, uint32, uint32)

        /** Computes maximum of the signed 64-bit values.

            @code
            r0 = max(a0, b0)
            ...
            rN = max(aN, bN)
            @endcode

            Supported since AVX2, NEON64. Not supported on ALTIVEC.
        */
        template <unsigned N, class E1, class E2>
        inline int64<N, expr_empty> max(const int64<N, E1> &a, const int64<N, E2> &b) {
            return detail::insn::i_max(a.eval(), b.eval());
        }

        SIMD_SCALAR_ARG_IMPL_VEC(max, int64, int64)

        /** Computes maximum of the unsigned 64-bit values.

            @code
            r0 = max(a0, b0)
            ...
            rN = max(aN, bN)
            @endcode

            Supported since AVX2, NEON64. Not supported on ALTIVEC.
        */
        template <unsigned N, class E1, class E2>
        inline uint64<N, expr_empty> max(const uint64<N, E1> &a, const uint64<N, E2> &b) {
            return detail::insn::i_max(a.eval(), b.eval());
        }

        SIMD_SCALAR_ARG_IMPL_VEC(max, uint64, uint64)

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
