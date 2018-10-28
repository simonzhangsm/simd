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

#ifndef SIMD_CORE_CMP_EQ_H
#define SIMD_CORE_CMP_EQ_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/insn/cmp_eq.h>
#include <bigmath/simd/core/detail/scalar_arg_impl.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {


        /** Compares 8-bit values for equality.

            @code
            r0 = (a0 == b0) ? 0xff : 0x0
            ...
            rN = (aN == bN) ? 0xff : 0x0
            @endcode

            @par 256-bit version:
            @icost{SSE2-AVX, NEON, ALTIVEC, 2}
        */
        template <unsigned N, class V1, class V2>
        inline mask_int8<N, expr_empty> cmp_eq(const any_int8<N, V1> &a, const any_int8<N, V2> &b) {
            typename detail::get_expr2_nosign<V1, V2>::type ra, rb;
            ra = a.wrapped().eval();
            rb = b.wrapped().eval();
            return detail::insn::i_cmp_eq(ra, rb);
        }

        SIMD_SCALAR_ARG_IMPL_VEC_EXPR(cmp_eq, mask_int8, any_int8)

        /** Compares 16-bit values for equality.

            @code
            r0 = (a0 == b0) ? 0xffff : 0x0
            ...
            rN = (aN == bN) ? 0xffff : 0x0
            @endcode

            @par 256-bit version:
            @icost{SSE2-AVX, NEON, ALTIVEC, 2}
        */
        template <unsigned N, class V1, class V2>
        inline mask_int16<N, expr_empty> cmp_eq(const any_int16<N, V1> &a, const any_int16<N, V2> &b) {
            typename detail::get_expr2_nosign<V1, V2>::type ra, rb;
            ra = a.wrapped().eval();
            rb = b.wrapped().eval();
            return detail::insn::i_cmp_eq(ra, rb);
        }

        SIMD_SCALAR_ARG_IMPL_VEC_EXPR(cmp_eq, mask_int16, any_int16)

        /** Compares the values of two int32x4 vectors for equality

            @code
            r0 = (a0 == b0) ? 0xffffffff : 0x0
            ...
            rN = (aN == bN) ? 0xffffffff : 0x0
            @endcode

            @par 256-bit version:
            @icost{SSE2-AVX, NEON, ALTIVEC, 2}
        */
        template <unsigned N, class V1, class V2>
        inline mask_int32<N, expr_empty> cmp_eq(const any_int32<N, V1> &a, const any_int32<N, V2> &b) {
            typename detail::get_expr2_nosign<V1, V2>::type ra, rb;
            ra = a.wrapped().eval();
            rb = b.wrapped().eval();
            return detail::insn::i_cmp_eq(ra, rb);
        }

        SIMD_SCALAR_ARG_IMPL_VEC_EXPR(cmp_eq, mask_int32, any_int32)

        /** Compares the values of two int64x2 vectors for equality

            @code
            r0 = (a0 == b0) ? 0xffffffffffffffff : 0x0
            ...
            rN = (aN == bN) ? 0xffffffffffffffff : 0x0
            @endcode

            @par 128-bit version:
            @icost{SSE2-SSSE3, 5}
            @icost{XOP, 1}
            @icost{NEON, 3}
            @icost{ALTIVEC, 3-4}

            @par 256-bit version:
            @icost{SSE2-SSSE3, AVX, 10}
            @icost{XOP, SSE4.1, 2}
            @icost{NEON, 6}
            @icost{ALTIVEC, 6-7}
        */
        template <unsigned N, class V1, class V2>
        inline mask_int64<N, expr_empty> cmp_eq(const any_int64<N, V1> &a, const any_int64<N, V2> &b) {
            typename detail::get_expr2_nosign<V1, V2>::type ra, rb;
            ra = a.wrapped().eval();
            rb = b.wrapped().eval();
            return detail::insn::i_cmp_eq(ra, rb);
        }

        SIMD_SCALAR_ARG_IMPL_VEC_EXPR(cmp_eq, mask_int64, any_int64)

        /** Compares the values of two float32x4 vectors for equality

            @code
            r0 = (a0 == b0) ? 0xffffffff : 0x0
            ...
            rN = (aN == bN) ? 0xffffffff : 0x0
            @endcode

            @par 256-bit version:
            @icost{SSE2-SSE4.1, NEON, ALTIVEC, 2}
        */
        template <unsigned N, class V1, class V2>
        inline mask_float32<N, expr_empty> cmp_eq(const any_float32<N, V1> &a, const any_float32<N, V2> &b) {
            return detail::insn::i_cmp_eq(a.wrapped().eval(), b.wrapped().eval());
        }

        SIMD_SCALAR_ARG_IMPL_VEC_EXPR(cmp_eq, mask_float32, any_float32)

        /** Compares the values of two float64x2 vectors for equality

            @code
            r0 = (a0 == b0) ? 0xffffffffffffffff : 0x0
            ...
            rN = (aN == bN) ? 0xffffffffffffffff : 0x0
            @endcode

            @par 128-bit version:
            @novec{NEON, ALTIVEC}

            @par 256-bit version:
            @novec{NEON, ALTIVEC}
            @icost{SSE2-SSE4.1, 2}
        */
        template <unsigned N, class V1, class V2>
        inline mask_float64<N, expr_empty> cmp_eq(const any_float64<N, V1> &a, const any_float64<N, V2> &b) {
            return detail::insn::i_cmp_eq(a.wrapped().eval(), b.wrapped().eval());
        }

        SIMD_SCALAR_ARG_IMPL_VEC_EXPR(cmp_eq, mask_float64, any_float64)


    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
