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

#ifndef SIMD_TYPES_FLOAT64X4_H
#define SIMD_TYPES_FLOAT64X4_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/setup_arch.h>
#include <bigmath/simd/types/fwd.h>
#include <bigmath/simd/types/any.h>
#include <bigmath/simd/types/int64x4.h>
#include <bigmath/simd/types/float64x2.h>
#include <bigmath/simd/core/cast.h>
#include <bigmath/simd/detail/construct_eval.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {

#if SIMD_USE_AVX

        /// Class representing float64x4 vector
        template <> class float64<4, void> : public any_float64<4, float64<4, void>> {
        public:
            static const unsigned type_tag = SIMD_TAG_FLOAT;
            using element_type = double;
            using base_vector_type = float64<4, void>;
            using expr_type = void;

#if SIMD_USE_AVX
            using native_type = __m256d;
#endif

            inline float64<4>() = default;
            inline float64<4>(const float64<4> &) = default;
            inline float64<4> &operator=(const float64<4> &) = default;

            template <class E> inline float64<4>(const float64<4, E> &d) {
                *this = d.eval();
            }
            template <class V> inline explicit float64<4>(const any_vec<32, V> &d) {
                *this = bit_cast<float64<4>>(d.wrapped().eval());
            }
            template <class V> inline float64<4> &operator=(const any_vec<32, V> &d) {
                *this = bit_cast<float64<4>>(d.wrapped().eval());
                return *this;
            }

            /// Construct from the underlying vector type
            inline float64<4>(const native_type &d) : d_(d) {
            }
            inline float64<4> &operator=(const native_type &d) {
                d_ = d;
                return *this;
            }

            /// Convert to the underlying vector type
#if !SIMD_DISABLE_DEPRECATED_CONVERSION_OPERATOR_TO_NATIVE_TYPES
            inline operator native_type() const SIMD_IMPLICIT_CONVERSION_DEPRECATION_MSG {
                return d_;
            }
#endif
            inline native_type native() const {
                return d_;
            }

            template <class E> inline float64<4>(const expr_vec_construct<E> &e) {
                detail::construct_eval_wrapper(*this, e.expr());
            }
            template <class E> inline float64<4> &operator=(const expr_vec_construct<E> &e) {
                detail::construct_eval_wrapper(*this, e.expr());
                return *this;
            }

            /// Access base vectors
            inline const float64<4> &vec(unsigned) const {
                return *this;
            }
            inline float64<4> &vec(unsigned) {
                return *this;
            }

            inline float64<4> eval() const {
                return *this;
            }

        private:
            native_type d_;
        };


        /// Class representing possibly optimized mask data for 2x 64-bit floating point
        /// vector
        template <> class mask_float64<4, void> : public any_float64<4, mask_float64<4, void>> {
        public:
            static const unsigned type_tag = SIMD_TAG_MASK_FLOAT;
            using base_vector_type = mask_float64<4, void>;
            using expr_type = void;

#if SIMD_USE_AVX512VL
            using native_type = __mmask8;
#elif SIMD_USE_AVX
            using native_type = __m256d;
#endif

            inline mask_float64<4>() = default;
            inline mask_float64<4>(const mask_float64<4> &) = default;
            inline mask_float64<4> &operator=(const mask_float64<4> &) = default;

            inline mask_float64<4>(const native_type &d) : d_(d) {
            }

#if SIMD_USE_AVX && !SIMD_USE_AVX512VL
            inline mask_float64<4>(const float64<4> &d) : d_(d.native()) {
            }
#endif

            template <class E> inline explicit mask_float64<4>(const mask_int64<4, E> &d) {
                *this = bit_cast<mask_float64<4>>(d.eval());
            }
            template <class E> inline mask_float64<4> &operator=(const mask_int64<4, E> &d) {
                *this = bit_cast<mask_float64<4>>(d.eval());
                return *this;
            }

            /// Convert to the underlying vector type
#if !SIMD_DISABLE_DEPRECATED_CONVERSION_OPERATOR_TO_NATIVE_TYPES
            inline operator native_type() const SIMD_IMPLICIT_CONVERSION_DEPRECATION_MSG {
                return d_;
            }
#endif
            inline native_type native() const {
                return d_;
            }

            /// Access the underlying type
            inline float64<4> unmask() const {
#if SIMD_USE_AVX512VL
                return _mm256_castsi256_pd(_mm256_movm_epi64(d_));
#else
                return float64<4>(d_);
#endif
            }

            inline const mask_float64<4> &vec(unsigned) const {
                return *this;
            }
            inline mask_float64<4> &vec(unsigned) {
                return *this;
            }

            inline mask_float64<4> eval() const {
                return *this;
            }

        private:
            native_type d_;
        };

#endif // SIMD_USE_AVX

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
