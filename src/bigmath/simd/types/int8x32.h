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

#ifndef SIMD_TYPES_INT8X32_H
#define SIMD_TYPES_INT8X32_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/setup_arch.h>
#include <bigmath/simd/types/fwd.h>
#include <bigmath/simd/types/any.h>
#include <bigmath/simd/detail/construct_eval.h>
#include <cstdint>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {

#if SIMD_USE_AVX2

        /** Class representing 32x 8-bit signed integer vector
         */
        template <> class int8<32, void> : public any_int8<32, int8<32, void>> {
        public:
            static const unsigned type_tag = SIMD_TAG_INT;
            using element_type = int8_t;
            using base_vector_type = int8<32>;
            using expr_type = void;

#if SIMD_USE_AVX2
            using native_type = __m256i;
#endif

            inline int8<32>() = default;
            inline int8<32>(const int8<32> &) = default;
            inline int8<32> &operator=(const int8<32> &) = default;

            template <class E> inline int8<32>(const int8<32, E> &d) {
                *this = d.eval();
            }
            template <class E> inline int8<32>(const uint8<32, E> &d) {
                *this = d.eval();
            }
            template <class V> inline explicit int8<32>(const any_vec<32, V> &d) {
                *this = bit_cast<int8<32>>(d.wrapped().eval());
            }
            template <class V> inline int8<32> &operator=(const any_vec<32, V> &d) {
                *this = bit_cast<int8<32>>(d.wrapped().eval());
                return *this;
            }

            /// Construct from the underlying vector type
            inline int8<32>(const native_type &d) : d_(d) {
            }
            inline int8<32> &operator=(const native_type &d) {
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

            template <class E> inline int8<32>(const expr_vec_construct<E> &e) {
                detail::construct_eval_wrapper(*this, e.expr());
            }
            template <class E> inline int8<32> &operator=(const expr_vec_construct<E> &e) {
                detail::construct_eval_wrapper(*this, e.expr());
                return *this;
            }

            /// Access base vectors
            inline const int8<32> &vec(unsigned) const {
                return *this;
            }
            inline int8<32> &vec(unsigned) {
                return *this;
            }

            inline int8<32> eval() const {
                return *this;
            }

        private:
            native_type d_;
        };

        /** Class representing 32x 8-bit unsigned integer vector
         */
        template <> class uint8<32, void> : public any_int8<32, uint8<32, void>> {
        public:
            static const unsigned type_tag = SIMD_TAG_UINT;
            using element_type = uint8_t;
            using base_vector_type = uint8<32>;
            using expr_type = void;

#if SIMD_USE_AVX2
            using native_type = __m256i;
#endif

            inline uint8<32>() = default;
            inline uint8<32>(const uint8<32> &) = default;
            inline uint8<32> &operator=(const uint8<32> &) = default;

            template <class E> inline uint8<32>(const uint8<32, E> &d) {
                *this = d.eval();
            }
            template <class E> inline uint8<32>(const int8<32, E> &d) {
                *this = d.eval();
            }
            template <class V> inline explicit uint8<32>(const any_vec<32, V> &d) {
                *this = bit_cast<uint8<32>>(d.wrapped().eval());
            }
            template <class V> inline uint8<32> &operator=(const any_vec<32, V> &d) {
                *this = bit_cast<uint8<32>>(d.wrapped().eval());
                return *this;
            }

            /// Construct from the underlying vector type
            inline uint8<32>(const native_type &d) : d_(d) {
            }
            inline uint8<32> &operator=(const native_type &d) {
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

            template <class E> inline uint8<32>(const expr_vec_construct<E> &e) {
                detail::construct_eval_wrapper(*this, e.expr());
            }
            template <class E> inline uint8<32> &operator=(const expr_vec_construct<E> &e) {
                detail::construct_eval_wrapper(*this, e.expr());
                return *this;
            }

            /// Access base vectors
            inline const uint8<32> &vec(unsigned) const {
                return *this;
            }
            inline uint8<32> &vec(unsigned) {
                return *this;
            }

            inline uint8<32> eval() const {
                return *this;
            }

        private:
            native_type d_;
        };

        /// Class representing possibly optimized mask data for 16x 8-bit integer
        /// vector
        template <> class mask_int8<32, void> : public any_int8<32, mask_int8<32, void>> {
        public:
            static const unsigned type_tag = SIMD_TAG_MASK_INT;
            using base_vector_type = mask_int16v;
            using expr_type = void;

#if SIMD_USE_AVX512VL
            using native_type = __mmask32;
#elif SIMD_USE_AVX2
            using native_type = __m256i;
#endif

            inline mask_int8<32>() = default;
            inline mask_int8<32>(const mask_int8<32> &) = default;
            inline mask_int8<32> &operator=(const mask_int8<32> &) = default;

            inline mask_int8<32>(const native_type &d) : d_(d) {
            }

#if (SIMD_USE_AVX2 && !SIMD_USE_AVX512VL)
            inline mask_int8<32>(const uint8<32> &d) : d_(d.native()) {
            }
#endif

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
            inline uint8<32> unmask() const {
#if SIMD_USE_AVX512VL
                return _mm256_movm_epi8(d_);
#elif SIMD_USE_AVX2
                return uint8<32>(d_);
#endif
            }

            inline const mask_int8<32> &vec(unsigned) const {
                return *this;
            }
            inline mask_int8<32> &vec(unsigned) {
                return *this;
            }

            inline mask_int8<32> eval() const {
                return *this;
            }

        private:
            native_type d_;
        };

#endif // SIMD_USE_AVX2

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
