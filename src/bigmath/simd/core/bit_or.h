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

#ifndef SIMD_CORE_BIT_OR_H
#define SIMD_CORE_BIT_OR_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/insn/bit_or.h>
#include <bigmath/simd/detail/expr/bit_or.h>
#include <bigmath/simd/core/detail/get_expr_bitwise.h>
#include <bigmath/simd/core/detail/scalar_arg_impl.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {

        /** Computes bitwise OR of integer vectors.

            @code
            r0 = a0 | b0
            ...
            rN = aN | bN
            @endcode

            @todo icost
        */
        template <unsigned N, class V1, class V2>
        inline typename detail::get_expr_bit_or<V1, V2>::type bit_or(const any_vec<N, V1> &a, const any_vec<N, V2> &b) {
            return {{a.wrapped(), b.wrapped()}};
        }

        // support scalar arguments
        template <unsigned N, class V>
        inline typename detail::get_expr_bitwise2_and<expr_bit_or, unsigned, V>::type bit_or(const unsigned &a,
                                                                                             const any_vec<N, V> &b) {
            return {{a, b.wrapped()}};
        }
        template <unsigned N, class V>
        inline typename detail::get_expr_bitwise2_and<expr_bit_or, unsigned long, V>::type bit_or(
            const unsigned long &a, const any_vec<N, V> &b) {
            return {{a, b.wrapped()}};
        }
        template <unsigned N, class V>
        inline typename detail::get_expr_bitwise2_and<expr_bit_or, unsigned long long, V>::type bit_or(
            const unsigned long long &a, const any_vec<N, V> &b) {
            return {{a, b.wrapped()}};
        }
        template <unsigned N, class V>
        inline typename detail::get_expr_bitwise2_and<expr_bit_or, int, V>::type bit_or(const int &a,
                                                                                        const any_vec<N, V> &b) {
            return {{a, b.wrapped()}};
        }
        template <unsigned N, class V>
        inline typename detail::get_expr_bitwise2_and<expr_bit_or, long, V>::type bit_or(const long &a,
                                                                                         const any_vec<N, V> &b) {
            return {{a, b.wrapped()}};
        }
        template <unsigned N, class V>
        inline typename detail::get_expr_bitwise2_and<expr_bit_or, long long, V>::type bit_or(const long long &a,
                                                                                              const any_vec<N, V> &b) {
            return {{a, b.wrapped()}};
        }

        template <unsigned N, class V>
        inline typename detail::get_expr_bitwise2_and<expr_bit_or, V, unsigned>::type bit_or(const any_vec<N, V> &a,
                                                                                             const unsigned &b) {
            return {{a.wrapped(), b}};
        }
        template <unsigned N, class V>
        inline typename detail::get_expr_bitwise2_and<expr_bit_or, V, unsigned long>::type bit_or(
            const any_vec<N, V> &a, const unsigned long &b) {
            return {{a.wrapped(), b}};
        }
        template <unsigned N, class V>
        inline typename detail::get_expr_bitwise2_and<expr_bit_or, V, unsigned long long>::type bit_or(
            const any_vec<N, V> &a, const unsigned long long &b) {
            return {{a.wrapped(), b}};
        }
        template <unsigned N, class V>
        inline typename detail::get_expr_bitwise2_and<expr_bit_or, V, int>::type bit_or(const any_vec<N, V> &a,
                                                                                        const int &b) {
            return {{a.wrapped(), b}};
        }
        template <unsigned N, class V>
        inline typename detail::get_expr_bitwise2_and<expr_bit_or, V, long>::type bit_or(const any_vec<N, V> &a,
                                                                                         const long &b) {
            return {{a.wrapped(), b}};
        }
        template <unsigned N, class V>
        inline typename detail::get_expr_bitwise2_and<expr_bit_or, V, long long>::type bit_or(const any_vec<N, V> &a,
                                                                                              const long long &b) {
            return {{a.wrapped(), b}};
        }


    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
