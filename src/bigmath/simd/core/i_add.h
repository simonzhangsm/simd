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

#ifndef SIMD_CORE_I_ADD_H
#define SIMD_CORE_I_ADD_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/expr/i_add.h>
#include <bigmath/simd/core/detail/get_expr_uint.h>
#include <bigmath/simd/core/detail/scalar_arg_impl.h>
#include <bigmath/simd/core/detail/get_expr_uint.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {


        /** Adds 8-bit integer values.

            @code
            r0 = a0 + b0
            ...
            rN = aN + bN
            @endcode

            @par 256-bit version:
            @icost{SSE2-AVX, NEON, ALTIVEC, 2}
        */
        template <unsigned N, class V1, class V2>
        inline typename detail::get_expr_uint<expr_iadd, V1, V2>::type add(const any_int8<N, V1> &a,
                                                                           const any_int8<N, V2> &b) {
            return {{a.wrapped(), b.wrapped()}};
        }

        SIMD_SCALAR_ARG_IMPL_INT_UNSIGNED(add, expr_iadd, any_int8, int8)

        /** Adds 16-bit integer values.

            @code
            r0 = a0 + b0
            ...
            rN = aN + bN
            @endcode

            @par 256-bit version:
            @icost{SSE2-AVX, NEON, ALTIVEC, 2}
        */
        template <unsigned N, class V1, class V2>
        inline typename detail::get_expr_uint<expr_iadd, V1, V2>::type add(const any_int16<N, V1> &a,
                                                                           const any_int16<N, V2> &b) {
            return {{a.wrapped(), b.wrapped()}};
        }

        SIMD_SCALAR_ARG_IMPL_INT_UNSIGNED(add, expr_iadd, any_int16, int16)

        /** Adds 32-bit integer values.

            @code
            r0 = a0 + b0
            ...
            rN = aN + bN
            @endcode

            @par 256-bit version:
            @icost{SSE2-AVX, NEON, ALTIVEC, 2}
        */
        template <unsigned N, class V1, class V2>
        inline typename detail::get_expr_uint<expr_iadd, V1, V2>::type add(const any_int32<N, V1> &a,
                                                                           const any_int32<N, V2> &b) {
            return {{a.wrapped(), b.wrapped()}};
        }

        SIMD_SCALAR_ARG_IMPL_INT_UNSIGNED(add, expr_iadd, any_int32, int32)

        /** Adds 64-bit integer values.

            @code
            r0 = a0 + b0
            ...
            rN = aN + bN
            @endcode

            @par 128-bit version:
            @icost{ALTIVEC, 5-6}

            @par 256-bit version:
            @icost{SSE2-AVX, NEON, 2}
            @icost{ALTIVEC, 10-11}
        */
        template <unsigned N, class V1, class V2>
        inline typename detail::get_expr_uint<expr_iadd, V1, V2>::type add(const any_int64<N, V1> &a,
                                                                           const any_int64<N, V2> &b) {
            return {{a.wrapped(), b.wrapped()}};
        }

        SIMD_SCALAR_ARG_IMPL_INT_UNSIGNED(add, expr_iadd, any_int64, int64)

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
