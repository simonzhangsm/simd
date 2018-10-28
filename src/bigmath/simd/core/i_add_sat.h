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

#ifndef SIMD_CORE_I_ADD_SAT_H
#define SIMD_CORE_I_ADD_SAT_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/expr/i_add_sat.h>
#include <bigmath/simd/core/detail/scalar_arg_impl.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {


        /** Adds and saturates signed 8-bit integer values.

            @code
            r0 = signed_saturate(a0 + b0)
            ...
            rN = signed_saturate(aN + bN)
            @endcode

            @par 256-bit version:
            @icost{SSE2-AVX, NEON, ALTIVEC, 2}
        */
        template <unsigned N, class E1, class E2>
        inline int8<N, expr_iadd_sat<int8<N, E1>, int8<N, E2>>> add_sat(const int8<N, E1> &a, const int8<N, E2> &b) {
            return {{a, b}};
        }

        SIMD_SCALAR_ARG_IMPL_EXPR(add_sat, expr_iadd_sat, int8, int8)

        /** Adds and saturates signed 16-bit integer values.

            @code
            r0 = signed_saturate(a0 + b0)
            ...
            rN = signed_saturate(aN + bN)
            @endcode

            @par 256-bit version:
            @icost{SSE2-AVX, NEON, ALTIVEC, 2}
        */
        template <unsigned N, class E1, class E2>
        inline int16<N, expr_iadd_sat<int16<N, E1>, int16<N, E2>>> add_sat(const int16<N, E1> &a,
                                                                           const int16<N, E2> &b) {
            return {{a, b}};
        }

        SIMD_SCALAR_ARG_IMPL_EXPR(add_sat, expr_iadd_sat, int16, int16)

        /** Adds and saturates unsigned 8-bit integer values.

            @code
            r0 = unsigned_saturate(a0 + b0)
            ...
            rN = unsigned_saturate(aN + bN)
            @endcode

            @par 256-bit version:
            @icost{SSE2-AVX, NEON, ALTIVEC, 2}
        */
        template <unsigned N, class E1, class E2>
        inline uint8<N, expr_iadd_sat<uint8<N, E1>, uint8<N, E2>>> add_sat(const uint8<N, E1> &a,
                                                                           const uint8<N, E2> &b) {
            return {{a, b}};
        }

        SIMD_SCALAR_ARG_IMPL_EXPR(add_sat, expr_iadd_sat, uint8, uint8)

        /** Adds and saturates unsigned 16-bit integer values.

            @code
            r0 = unsigned_saturate(a0 + b0)
            ...
            rN = unsigned_saturate(aN + bN)
            @endcode

            @par 256-bit version:
            @icost{SSE2-AVX, NEON, ALTIVEC, 2}
        */
        template <unsigned N, class E1, class E2>
        inline uint16<N, expr_iadd_sat<uint16<N, E1>, uint16<N, E2>>> add_sat(const uint16<N, E1> &a,
                                                                              const uint16<N, E2> &b) {
            return {{a, b}};
        }

        SIMD_SCALAR_ARG_IMPL_EXPR(add_sat, expr_iadd_sat, uint16, uint16)

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
