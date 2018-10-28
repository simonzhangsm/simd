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

#ifndef SIMD_CORE_I_MUL_H
#define SIMD_CORE_I_MUL_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/expr/i_mul.h>
#include <bigmath/simd/core/detail/get_expr_uint.h>
#include <bigmath/simd/core/detail/scalar_arg_impl.h>
#include <bigmath/simd/core/detail/get_expr_uint.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {

        // no 8 bit multiplications in SSE
        /** Multiplies 16-bit values and returns the lower part of the multiplication

            @code
            r0 = low(a0 * b0)
            ...
            rN = low(aN * bN)
            @endcode

            @par 256-bit version:
            @icost{SSE2-AVX, NEON, ALTIVEC, 2}
        */
        template <unsigned N, class V1, class V2>
        inline typename detail::get_expr_uint<expr_mul_lo, V1, V2>::type mul_lo(const any_int16<N, V1> &a,
                                                                                const any_int16<N, V2> &b) {
            return {{a.wrapped(), b.wrapped()}};
        }

        SIMD_SCALAR_ARG_IMPL_INT_UNSIGNED(mul_lo, expr_mul_lo, any_int16, int16)

        /** Multiplies signed 16-bit values and returns the higher half of the result.

            @code
            r0 = high(a0 * b0)
            ...
            rN = high(aN * bN)
            @endcode

            @par 128-bit version:
            @icost{NEON, ALTIVEC, 3}

            @par 256-bit version:
            @icost{SSE2-AVX, 2}
            @icost{NEON, ALTIVEC, 6}
        */
        template <unsigned N, class E1, class E2>
        inline int16<N, expr_mul_hi<int16<N, E1>, int16<N, E2>>> mul_hi(const int16<N, E1> &a, const int16<N, E2> &b) {
            return {{a, b}};
        }

        SIMD_SCALAR_ARG_IMPL_EXPR(mul_hi, expr_mul_hi, int16, int16)

        /** Multiplies unsigned 16-bit values and returns the higher half of the result.

            @code
            r0 = high(a0 * b0)
            ...
            rN = high(aN * bN)
            @endcode

            @par 128-bit version:
            @icost{NEON, ALTIVEC, 3}

            @par 256-bit version:
            @icost{SSE2-AVX, 2}
            @icost{NEON, ALTIVEC, 6}
        */
        template <unsigned N, class E1, class E2>
        inline uint16<N, expr_mul_hi<uint16<N, E1>, uint16<N, E2>>> mul_hi(const uint16<N, E1> &a,
                                                                           const uint16<N, E2> &b) {
            return {{a, b}};
        }

        SIMD_SCALAR_ARG_IMPL_EXPR(mul_hi, expr_mul_hi, uint16, uint16)


        /** Multiplies 32-bit values and returns the lower half of the result.

            @code
            r0 = low(a0 * b0)
            ...
            rN = low(aN * bN)
            @endcode

            @par 128-bit version:
            @icost{SSE2-SSSE3, 6}
            @icost{ALTIVEC, 8}

            @par 256-bit version:
            @icost{SSE2-SSSE3, 12}
            @icost{SSE4.1, AVX, NEON, 2}
            @icost{ALTIVEC, 16}
        */
        template <unsigned N, class V1, class V2>
        inline typename detail::get_expr_uint<expr_mul_lo, V1, V2>::type mul_lo(const any_int32<N, V1> &a,
                                                                                const any_int32<N, V2> &b) {
            return {{a.wrapped(), b.wrapped()}};
        }

        SIMD_SCALAR_ARG_IMPL_INT_UNSIGNED(mul_lo, expr_mul_lo, any_int32, int32)


    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
