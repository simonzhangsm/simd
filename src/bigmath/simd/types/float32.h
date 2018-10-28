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

#ifndef SIMD_TYPES_FLOAT32_H
#define SIMD_TYPES_FLOAT32_H

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

        /** Class representing a @a float32 vector of arbitrary length. The vector
            always contains at least one native vector.
        */
        template <unsigned N> class float32<N, void> : public any_float32<N, float32<N, void>> {
        public:
            static const unsigned type_tag = SIMD_TAG_FLOAT;
            using expr_type = void;
            using element_type = float;
            using base_vector_type = float32v;

            inline float32<N>() = default;
            inline float32<N>(const float32<N> &) = default;
            inline float32<N> &operator=(const float32<N> &) = default;

            template <class E> inline float32<N>(const float32<N, E> &d) {
                *this = d.eval();
            }
            template <class V> inline explicit float32<N>(const any_vec<N * 4, V> &d) {
                *this = bit_cast<float32<N>>(d.wrapped().eval());
            }
            template <class V> inline float32<N> &operator=(const any_vec<N * 4, V> &d) {
                *this = bit_cast<float32<N>>(d.wrapped().eval());
                return *this;
            }

            template <class E> inline float32<N>(const expr_vec_construct<E> &e) {
                detail::construct_eval_wrapper(*this, e.expr());
            }
            template <class E> inline float32<N> &operator=(const expr_vec_construct<E> &e) {
                detail::construct_eval_wrapper(*this, e.expr());
                return *this;
            }

            inline const float32v &vec(unsigned i) const {
                return d_[i];
            }
            inline float32v &vec(unsigned i) {
                return d_[i];
            }

            inline float32<N> eval() const {
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
            static inline float32<N> set_vec(const float32v &v0) {
                float32<N> r;
                for (unsigned i = 0; i < r.vec_length; i++)
                    r.vec(i) = v0;
                return r;
            }

            detail::vararray<float32v, float32::vec_length> d_;
        };


        /// Class representing a mask for 32-bit floating-point vector of arbitrary
        /// length.
        template <unsigned N> class mask_float32<N, void> : public any_float32<N, mask_float32<N, void>> {
        public:
            static const unsigned type_tag = SIMD_TAG_MASK_FLOAT;
            using base_vector_type = mask_float32v;
            using expr_type = void;

            inline mask_float32<N>() = default;
            inline mask_float32<N>(const mask_float32<N> &) = default;
            inline mask_float32<N> &operator=(const mask_float32<N> &) = default;

            template <class E> inline explicit mask_float32<N>(const mask_int32<N, E> &d) {
                *this = bit_cast<mask_float32<N>>(d.eval());
            }
            template <class E> inline mask_float32<N> &operator=(const mask_int32<N, E> &d) {
                *this = bit_cast<mask_float32<N>>(d.eval());
                return *this;
            }

            /// Access the underlying type
            inline float32<N> unmask() const {
                float32<N> r;
                for (unsigned i = 0; i < mask_float32::vec_length; ++i) {
                    r.vec(i) = d_[i].unmask();
                }
                return r;
            }

            inline const mask_float32v &vec(unsigned i) const {
                return d_[i];
            }
            inline mask_float32v &vec(unsigned i) {
                return d_[i];
            }

            inline mask_float32<N> eval() const {
                return *this;
            }

        private:
            detail::vararray<mask_float32v, mask_float32::vec_length> d_;
        };


    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
