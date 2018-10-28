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

#ifndef SIMD_CORE_BIT_NOT_H
#define SIMD_CORE_BIT_NOT_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/insn/bit_not.h>
#include <bigmath/simd/detail/expr/bit_not.h>
#include <bigmath/simd/detail/get_expr.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {

        /** Computes bitwise NOT of an integer or floating-point vector

            @code
            r = ~a
            @endcode

            @todo icost
        */
        template <unsigned N, class V>
        inline typename detail::get_expr<V, expr_bit_not<V>>::empty bit_not(const any_vec<N, V> &a) {
            typename detail::get_expr_nosign<V>::type ra;
            ra = a.wrapped().eval();
            return detail::insn::i_bit_not(ra);
        }

        /* FIXME
        template<unsigned N, class E> inline
        mask_int32<N, expr_bit_not<mask_int32<N,E>>> bit_not(mask_int32<N,E> a)
        {
            return { { a } };
        }
        template<unsigned N, class E> inline
        mask_int64<N, expr_bit_not<mask_int64<N,E>>> bit_not(mask_int64<N,E> a)
        {
            return { { a } };
        }

        template<unsigned N, class E> inline
        mask_float32<N, expr_bit_not<mask_float32<N,E>>> bit_not(mask_float32<N,E> a)
        {
            return { { a } };
        }
        template<unsigned N, class E> inline
        mask_float64<N, expr_bit_not<mask_float64<N,E>>> bit_not(mask_float64<N,E> a)
        {
            return { { a } };
        }
        */

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
