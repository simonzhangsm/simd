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

#ifndef SIMD_DETAIL_EXPR_SCALAR_H
#define SIMD_DETAIL_EXPR_SCALAR_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/expr.h>
#include <bigmath/simd/detail/insn/make_const.h>
#include <bigmath/simd/core/detail/scalar_arg_impl.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {

            template <class Int> inline void scalar_convert(Int &d, uint64_t x) {
                d = static_cast<Int>(x);
            }
            static inline void scalar_convert(float &d, uint64_t x) {
                d = bit_cast<float>(uint32_t(x));
            }
            static inline void scalar_convert(double &d, uint64_t x) {
                d = bit_cast<double>(x);
            }

            static inline uint64_t cast_int(const int &x) {
                return (unsigned int)x;
            }
            static inline uint64_t cast_int(const long &x) {
                return (unsigned long)x;
            }
            static inline uint64_t cast_int(const long long &x) {
                return (unsigned long long)x;
            }
            static inline uint64_t cast_int(const unsigned &x) {
                return x;
            }
            static inline uint64_t cast_int(const unsigned long &x) {
                return x;
            }
            static inline uint64_t cast_int(const unsigned long long &x) {
                return x;
            }

            template <class V> inline V make_const_bitwise(uint64_t t) {
                typename detail::remove_sign<V>::type r;
                expr_vec_make_const<typename V::element_type, 1> e;
                scalar_convert(e.a[0], t);
                insn::i_make_const(r, e, 0);
                return V(r);
            }

            template <class R, class EL> inline R expr_eval_scalar(const EL &q) {
                typename detail::remove_sign<R>::type r;
                expr_vec_make_const<typename R::element_type, 1> e;
                e.a[0] = static_cast<typename R::element_type>(q);
                insn::i_make_const(r, e, 0);
                return R(r);
            }

            template <class R, class EL> inline R expr_eval_scalar_bitwise(const EL &q) {
                return make_const_bitwise<R>(cast_int(q));
            }

        } // namespace detail
    }     // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
