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

#ifndef SIMD_TYPES_INT32X4_H
#define SIMD_TYPES_INT32X4_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/setup_arch.h>
#include <bigmath/simd/types/fwd.h>
#include <bigmath/simd/types/any.h>
#include <bigmath/simd/core/cast.h>
#include <bigmath/simd/detail/construct_eval.h>
#include <bigmath/simd/detail/array.h>
#include <bigmath/simd/detail/null/mask.h>
#include <cstdint>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {

        /** Class representing 4x 32-bit signed integer vector
         */
        template <> class int32<4, void> : public any_int32<4, int32<4, void>> {
        public:
            static const unsigned type_tag = SIMD_TAG_INT;
            using element_type = int32_t;
            using base_vector_type = int32<4, void>;
            using expr_type = void;

#if SIMD_USE_SSE2
            using native_type = __m128i;
#elif SIMD_USE_NEON
            using native_type = int32x4_t;
#elif SIMD_USE_ALTIVEC
            using native_type = __vector int32_t;
#elif SIMD_USE_MSA
            using native_type = v4i32;
#else
            using native_type = detail::vararray<int32_t, 4>;
#endif

            inline int32<4>() = default;
            inline int32<4>(const int32<4> &) = default;
            inline int32<4> &operator=(const int32<4> &) = default;

            template <class E> inline int32<4>(const int32<4, E> &d) {
                *this = d.eval();
            }
            template <class E> inline int32<4>(const uint32<4, E> &d) {
                *this = d.eval();
            }
            template <class V> inline explicit int32<4>(const any_vec<16, V> &d) {
                *this = bit_cast<int32<4>>(d.wrapped().eval());
            }
            template <class V> inline int32<4> &operator=(const any_vec<16, V> &d) {
                *this = bit_cast<int32<4>>(d.wrapped().eval());
                return *this;
            }

            /// Construct from the underlying vector type
            inline int32<4>(const native_type &d) : d_(d) {
            }
            inline int32<4> &operator=(const native_type &d) {
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

            template <class E> inline int32<4>(const expr_vec_construct<E> &e) {
                detail::construct_eval_wrapper(*this, e.expr());
            }
            template <class E> inline int32<4> &operator=(const expr_vec_construct<E> &e) {
                detail::construct_eval_wrapper(*this, e.expr());
                return *this;
            }

            /// Access base vectors
            inline const int32<4> &vec(unsigned) const {
                return *this;
            }
            inline int32<4> &vec(unsigned) {
                return *this;
            }

            inline int32<4> eval() const {
                return *this;
            }

#if SIMD_USE_NULL
            /// For internal use only
            inline const int32_t &el(unsigned i) const {
                return d_[i];
            }
            inline int32_t &el(unsigned i) {
                return d_[i];
            }
#endif

        private:
            native_type d_;
        };

        /** Class representing 4x 32-bit unsigned integer vector
         */
        template <> class uint32<4, void> : public any_int32<4, uint32<4, void>> {
        public:
            static const unsigned type_tag = SIMD_TAG_UINT;
            using element_type = uint32_t;
            using base_vector_type = uint32<4, void>;
            using expr_type = void;

#if SIMD_USE_SSE2
            using native_type = __m128i;
#elif SIMD_USE_NEON
            using native_type = uint32x4_t;
#elif SIMD_USE_ALTIVEC
            using native_type = __vector uint32_t;
#elif SIMD_USE_MSA
            using native_type = v4u32;
#else
            using native_type = detail::vararray<uint32_t, 4>;
#endif

            inline uint32<4>() = default;
            inline uint32<4>(const uint32<4> &) = default;
            inline uint32<4> &operator=(const uint32<4> &) = default;

            template <class E> inline uint32<4>(const uint32<4, E> &d) {
                *this = d.eval();
            }
            template <class E> inline uint32<4>(const int32<4, E> &d) {
                *this = d.eval();
            }
            template <class V> inline explicit uint32<4>(const any_vec<16, V> &d) {
                *this = bit_cast<uint32<4>>(d.wrapped().eval());
            }
            template <class V> inline uint32<4> &operator=(const any_vec<16, V> &d) {
                *this = bit_cast<uint32<4>>(d.wrapped().eval());
                return *this;
            }

            /// Construct from the underlying vector type
            inline uint32<4>(const native_type &d) : d_(d) {
            }
            inline uint32<4> &operator=(const native_type &d) {
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

            template <class E> inline uint32<4>(const expr_vec_construct<E> &e) {
                detail::construct_eval_wrapper(*this, e.expr());
            }
            template <class E> inline uint32<4> &operator=(const expr_vec_construct<E> &e) {
                detail::construct_eval_wrapper(*this, e.expr());
                return *this;
            }

            /// Access base vectors
            inline const uint32<4> &vec(unsigned) const {
                return *this;
            }
            inline uint32<4> &vec(unsigned) {
                return *this;
            }

            inline uint32<4> eval() const {
                return *this;
            }

#if SIMD_USE_NULL
            /// For uinternal use only
            inline const uint32_t &el(unsigned i) const {
                return d_[i];
            }
            inline uint32_t &el(unsigned i) {
                return d_[i];
            }
#endif

        private:
            native_type d_;
        };

        /// Class representing possibly optimized mask data for 4x 32-bit integer
        /// vector
        template <> class mask_int32<4, void> : public any_int32<4, mask_int32<4, void>> {
        public:
            static const unsigned type_tag = SIMD_TAG_MASK_INT;
            using base_vector_type = mask_int32<4, void>;
            using expr_type = void;

#if SIMD_USE_AVX512VL
            using native_type = __mmask8;
#elif SIMD_USE_SSE2
            using native_type = __m128i;
#elif SIMD_USE_NEON
            using native_type = uint32x4_t;
#elif SIMD_USE_ALTIVEC
            using native_type = __vector uint32_t;
#elif SIMD_USE_MSA
            using native_type = v4u32;
#else
            using native_type = detail::vararray<uint8_t, 4>;
#endif

            inline mask_int32<4>() = default;
            inline mask_int32<4>(const mask_int32<4> &) = default;
            inline mask_int32<4> &operator=(const mask_int32<4> &) = default;

            inline mask_int32<4>(const native_type &d) : d_(d) {
            }

#if SIMD_USE_ALTIVEC
            inline mask_int32<4>(const __vector __bool int &d) : d_((__vector uint32_t)d) {
            }
#endif

#if (SIMD_USE_SSE2 && !SIMD_USE_AVX512VL) || SIMD_USE_NEON || SIMD_USE_ALTIVEC
            inline mask_int32<4>(const uint32<4> &d) : d_(d.native()) {
            }
#endif

            template <class E> inline explicit mask_int32<4>(const mask_float32<4, E> &d) {
                *this = bit_cast<mask_int32<4>>(d.eval());
            }
            template <class E> inline mask_int32<4> &operator=(const mask_float32<4, E> &d) {
                *this = bit_cast<mask_int32<4>>(d.eval());
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
            inline uint32<4> unmask() const {
#if SIMD_USE_NULL
                return detail::null::unmask_mask<uint32<4>>(*this);
#elif SIMD_USE_AVX512VL
                return _mm_movm_epi32(d_);
#else
                return uint32<4>(d_);
#endif
            }

#if SIMD_USE_NULL
            inline uint8_t &el(unsigned id) {
                return d_[id];
            }
            inline const uint8_t &el(unsigned id) const {
                return d_[id];
            }
#endif

            inline const mask_int32<4> &vec(unsigned) const {
                return *this;
            }
            inline mask_int32<4> &vec(unsigned) {
                return *this;
            }

            inline mask_int32<4> eval() const {
                return *this;
            }

        private:
            native_type d_;
        };

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
