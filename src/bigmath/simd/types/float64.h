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

#ifndef SIMD_TYPES_FLOAT64_H
#define SIMD_TYPES_FLOAT64_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/setup_arch.h>
#include <bigmath/simd/types/any.h>
#include <bigmath/simd/types/fwd.h>
#include <bigmath/simd/core/cast.h>
#include <bigmath/simd/detail/array.h>
#include <bigmath/simd/detail/construct_eval.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {

        /** Class representing a @a float64 vector of arbitrary length. The vector
            always contains at least one native vector.
        */
        template <unsigned N> class float64<N, void> : public any_float64<N, float64<N, void>> {
        public:
            static const unsigned type_tag = SIMD_TAG_FLOAT;
            using element_type = double;
            using base_vector_type = float64v;
            using expr_type = void;

            inline float64<N>() = default;
            inline float64<N>(const float64<N> &) = default;
            inline float64<N> &operator=(const float64<N> &) = default;

            template <class E> inline float64<N>(const float64<N, E> &d) {
                *this = d.eval();
            }
            template <class V> inline explicit float64<N>(const any_vec<N * 8, V> &d) {
                *this = bit_cast<float64<N>>(d.wrapped().eval());
            }
            template <class V> inline float64<N> &operator=(const any_vec<N * 8, V> &d) {
                *this = bit_cast<float64<N>>(d.wrapped().eval());
                return *this;
            }

            template <class E> inline float64<N>(const expr_vec_construct<E> &e) {
                detail::construct_eval_wrapper(*this, e.expr());
            }
            template <class E> inline float64<N> &operator=(const expr_vec_construct<E> &e) {
                detail::construct_eval_wrapper(*this, e.expr());
                return *this;
            }

            inline const float64v &vec(unsigned i) const {
                return d_[i];
            }
            inline float64v &vec(unsigned i) {
                return d_[i];
            }

            inline float64<N> eval() const {
                return *this;
            }

        private:
            /** Creates a float vector from a native vector

                @code
                r0 = v0
                ...
                rN = v0
                @endcode
            */
            static inline float64<N> set_vec(const float64v &v0) {
                float64<N> r;
                for (unsigned i = 0; i < r.vec_length; i++)
                    r.vec(i) = v0;
                return r;
            }

            detail::vararray<float64v, float64::vec_length> d_;
        };

        /// Class representing possibly optimized mask data for 2x 64-bit floating point
        /// vector
        template <unsigned N> class mask_float64<N, void> : public any_float64<N, mask_float64<N, void>> {
        public:
            static const unsigned type_tag = SIMD_TAG_MASK_FLOAT;
            using base_vector_type = mask_float64v;
            using expr_type = void;

            inline mask_float64<N>() = default;
            inline mask_float64<N>(const mask_float64<N> &) = default;
            inline mask_float64<N> &operator=(const mask_float64<N> &) = default;

            template <class E> inline explicit mask_float64<N>(const mask_int64<N, E> &d) {
                *this = bit_cast<mask_float64<N>>(d.eval());
            }
            template <class E> inline mask_float64<N> &operator=(const mask_int64<N, E> &d) {
                *this = bit_cast<mask_float64<N>>(d.eval());
                return *this;
            }

            /// Access the underlying type
            inline float64<N> unmask() const {
                float64<N> r;
                for (unsigned i = 0; i < mask_float64::vec_length; ++i) {
                    r.vec(i) = d_[i].unmask();
                }
                return r;
            }

            inline const mask_float64v &vec(unsigned i) const {
                return d_[i];
            }
            inline mask_float64v &vec(unsigned i) {
                return d_[i];
            }

            inline mask_float64<N> eval() const {
                return *this;
            }

        private:
            detail::vararray<mask_float64v, mask_float64::vec_length> d_;
        };

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
