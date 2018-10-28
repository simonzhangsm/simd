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

#ifndef SIMD_TYPES_FLOAT32X4_H
#define SIMD_TYPES_FLOAT32X4_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/setup_arch.h>
#include <bigmath/simd/capabilities.h>
#include <bigmath/simd/types/fwd.h>
#include <bigmath/simd/types/any.h>
#include <bigmath/simd/types/int32x4.h>
#include <bigmath/simd/core/cast.h>
#include <bigmath/simd/detail/construct_eval.h>
#include <bigmath/simd/detail/array.h>
#include <bigmath/simd/detail/null/mask.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {

        /// Class representing float32x4 vector
        template <> class float32<4, void> : public any_float32<4, float32<4, void>> {
        public:
            static const unsigned type_tag = SIMD_TAG_FLOAT;
            using base_vector_type = float32<4, void>;
            using expr_type = void;

#if SIMD_USE_SSE2
            using native_type = __m128;
#elif SIMD_USE_NEON_FLT_SP
            using native_type = float32x4_t;
#elif SIMD_USE_ALTIVEC
            using native_type = __vector float;
#elif SIMD_USE_MSA
            using native_type = v4f32;
#else // NULL && (NEON && !FLT_SP)
            using native_type = detail::vararray<float, 4>;
#endif

            inline float32<4>() = default;
            inline float32<4>(const float32<4> &) = default;
            inline float32<4> &operator=(const float32<4> &) = default;

            template <class E> inline float32<4>(const float32<4, E> &d) {
                *this = d.eval();
            }
            template <class V> inline explicit float32<4>(const any_vec<16, V> &d) {
                *this = bit_cast<float32<4>>(d.wrapped().eval());
            }
            template <class V> inline float32<4> &operator=(const any_vec<16, V> &d) {
                *this = bit_cast<float32<4>>(d.wrapped().eval());
                return *this;
            }

            /// Construct from the underlying vector type
            inline float32<4>(const native_type &d) : d_(d) {
            }
            inline float32<4> &operator=(const native_type &d) {
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

#if SIMD_USE_NULL || SIMD_USE_NEON_NO_FLT_SP
            inline float &el(unsigned id) {
                return d_[id];
            }
            inline const float &el(unsigned id) const {
                return d_[id];
            }
#endif

            template <class E> inline float32<4>(const expr_vec_construct<E> &e) {
                detail::construct_eval_wrapper(*this, e.expr());
            }
            template <class E> inline float32<4> &operator=(const expr_vec_construct<E> &e) {
                detail::construct_eval_wrapper(*this, e.expr());
                return *this;
            }

            /// Access base vectors
            inline const float32<4> &vec(unsigned) const {
                return *this;
            }
            inline float32<4> &vec(unsigned) {
                return *this;
            }

            inline float32<4> eval() const {
                return *this;
            }

        private:
#if SIMD_ARM && !SIMD_HAS_FLOAT32_SIMD
            // Force alignment to be the same as of the real vector types. Different
            // alignment causes problems when types such as int32<4> are casted to
            // float32<4> or vice-versa - GCC assumes that some data on stack has
            // higher alignment than it really has and uses aligned load or store which
            // causes crashes.
            SIMDALIGN(8) native_type d_;
#else
            native_type d_;
#endif
        };

        /// Class representing possibly optimized mask data for 4x 32-bit floating-point
        /// vector
        template <> class mask_float32<4, void> : public any_float32<4, mask_float32<4, void>> {
        public:
            static const unsigned type_tag = SIMD_TAG_MASK_FLOAT;
            using base_vector_type = mask_float32<4, void>;
            using expr_type = void;

#if SIMD_USE_AVX512VL
            using native_type = __mmask8;
#elif SIMD_USE_SSE2
            using native_type = __m128;
#elif SIMD_USE_NEON_FLT_SP
            using native_type = float32x4_t;
#elif SIMD_USE_ALTIVEC
            using native_type = __vector float;
#elif SIMD_USE_MSA
            using native_type = v4f32;
#else // NULL || (NEON && !FLT_SP)
            using native_type = detail::vararray<uint8_t, 4>;
#endif
            inline mask_float32<4>() = default;
            inline mask_float32<4>(const mask_float32<4> &) = default;
            inline mask_float32<4> &operator=(const mask_float32<4> &) = default;

            inline mask_float32<4>(const native_type &d) : d_(d) {
            }

#if SIMD_USE_ALTIVEC
            inline mask_float32<4>(const __vector __bool int &d) : d_((__vector float)d) {
            }
#endif

#if SIMD_USE_SSE2 && !SIMD_USE_AVX512VL
            inline mask_float32<4>(const float32<4> &d) : d_(d.native()) {
            }
#endif

            template <class E> inline explicit mask_float32<4>(const mask_int32<4, E> &d) {
                *this = bit_cast<mask_float32<4>>(d.eval());
            }
            template <class E> inline mask_float32<4> &operator=(const mask_int32<4, E> &d) {
                *this = bit_cast<mask_float32<4>>(d.eval());
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
            inline float32<4> unmask() const {
#if SIMD_USE_AVX512VL
                return _mm_castsi128_ps(_mm_movm_epi32(d_));
#elif SIMD_USE_NULL || SIMD_USE_NEON_NO_FLT_SP
                return detail::null::unmask_mask<float32<4>>(*this);
#else
                return float32<4>(d_);
#endif
            }

#if SIMD_USE_NULL || SIMD_USE_NEON_NO_FLT_SP
            inline uint8_t &el(unsigned id) {
                return d_[id];
            }
            inline const uint8_t &el(unsigned id) const {
                return d_[id];
            }
#endif

            inline const mask_float32<4> &vec(unsigned) const {
                return *this;
            }
            inline mask_float32<4> &vec(unsigned) {
                return *this;
            }

            inline mask_float32<4> eval() const {
                return *this;
            }

        private:
            native_type d_;
        };

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
