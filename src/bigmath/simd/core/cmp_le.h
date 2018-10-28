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

#ifndef SIMD_CORE_CMP_LE_H
#define SIMD_CORE_CMP_LE_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/insn/cmp_le.h>
#include <bigmath/simd/core/detail/scalar_arg_impl.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {

        template <unsigned N, class E1, class E2>
        inline mask_int8<N, expr_empty> cmp_le(const int8<N, E1> &a, const int8<N, E2> &b) {
            return detail::insn::i_cmp_le(a.eval(), b.eval());
        }

        SIMD_SCALAR_ARG_IMPL_VEC(cmp_le, mask_int8, int8)

        template <unsigned N, class E1, class E2>
        inline mask_int8<N, expr_empty> cmp_le(const uint8<N, E1> &a, const uint8<N, E2> &b) {
            return detail::insn::i_cmp_le(a.eval(), b.eval());
        }

        SIMD_SCALAR_ARG_IMPL_VEC(cmp_le, mask_int8, uint8)

        template <unsigned N, class E1, class E2>
        inline mask_int16<N, expr_empty> cmp_le(const int16<N, E1> &a, const int16<N, E2> &b) {
            return detail::insn::i_cmp_le(a.eval(), b.eval());
        }

        SIMD_SCALAR_ARG_IMPL_VEC(cmp_le, mask_int16, int16)

        template <unsigned N, class E1, class E2>
        inline mask_int16<N, expr_empty> cmp_le(const uint16<N, E1> &a, const uint16<N, E2> &b) {
            return detail::insn::i_cmp_le(a.eval(), b.eval());
        }

        SIMD_SCALAR_ARG_IMPL_VEC(cmp_le, mask_int16, uint16)

        template <unsigned N, class E1, class E2>
        inline mask_int32<N, expr_empty> cmp_le(const int32<N, E1> &a, const int32<N, E2> &b) {
            return detail::insn::i_cmp_le(a.eval(), b.eval());
        }

        SIMD_SCALAR_ARG_IMPL_VEC(cmp_le, mask_int32, int32)

        template <unsigned N, class E1, class E2>
        inline mask_int32<N, expr_empty> cmp_le(const uint32<N, E1> &a, const uint32<N, E2> &b) {
            return detail::insn::i_cmp_le(a.eval(), b.eval());
        }

        SIMD_SCALAR_ARG_IMPL_VEC(cmp_le, mask_int32, uint32)

        template <unsigned N, class E1, class E2>
        inline mask_int64<N, expr_empty> cmp_le(const int64<N, E1> &a, const int64<N, E2> &b) {
            return detail::insn::i_cmp_le(a.eval(), b.eval());
        }

        SIMD_SCALAR_ARG_IMPL_VEC(cmp_le, mask_int64, int64)

        template <unsigned N, class E1, class E2>
        inline mask_int64<N, expr_empty> cmp_le(const uint64<N, E1> &a, const uint64<N, E2> &b) {
            return detail::insn::i_cmp_le(a.eval(), b.eval());
        }
        SIMD_SCALAR_ARG_IMPL_VEC(cmp_le, mask_int64, uint64)

        /** Compares the values of two float32x4 vectors for less-than or equal

            @code
            r0 = (a0 <= b0) ? 0xffffffff : 0x0
            ...
            rN = (aN <= bN) ? 0xffffffff : 0x0
            @endcode

            @par 256-bit version:
            @icost{SSE2-AVX, NEON, ALTIVEC, 2}
        */
        template <unsigned N, class E1, class E2>
        inline mask_float32<N, expr_empty> cmp_le(const float32<N, E1> &a, const float32<N, E2> &b) {
            return detail::insn::i_cmp_le(a.eval(), b.eval());
        }

        SIMD_SCALAR_ARG_IMPL_VEC(cmp_le, mask_float32, float32)

        /** Compares the values of two float64x2 vectors for less-than or equal

            @code
            r0 = (a0 <= b0) ? 0xffffffffffffffff : 0x0
            ...
            rN = (aN <= bN) ? 0xffffffffffffffff : 0x0
            @endcode

            @par 128-bit version:
            @novec{NEON, ALTIVEC}

            @par 256-bit version:
            @novec{NEON, ALTIVEC}
            @icost{SSE2-SSE4.1, 2}
        */
        template <unsigned N, class E1, class E2>
        inline mask_float64<N, expr_empty> cmp_le(const float64<N, E1> &a, const float64<N, E2> &b) {
            return detail::insn::i_cmp_le(a.eval(), b.eval());
        }

        SIMD_SCALAR_ARG_IMPL_VEC(cmp_le, mask_float64, float64)

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
