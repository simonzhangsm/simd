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

#ifndef SIMD_TYPES_INT32X16_H
#define SIMD_TYPES_INT32X16_H

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

#if SIMD_USE_AVX512F

        /** Class representing 8x 32-bit signed integer vector
         */
        template <> class int32<16, void> : public any_int32<16, int32<16, void>> {
        public:
            static const unsigned type_tag = SIMD_TAG_INT;
            using element_type = int32_t;
            using base_vector_type = int32<16, void>;
            using expr_type = void;

#if SIMD_USE_AVX512F
            using native_type = __m512i;
#endif

            inline int32<16>() = default;
            inline int32<16>(const int32<16> &) = default;
            inline int32<16> &operator=(const int32<16> &) = default;

            template <class E> inline int32<16>(const int32<16, E> &d) {
                *this = d.eval();
            }
            template <class E> inline int32<16>(const uint32<16, E> &d) {
                *this = d.eval();
            }
            template <class V> inline explicit int32<16>(const any_vec<64, V> &d) {
                *this = bit_cast<int32<16>>(d.wrapped().eval());
            }
            template <class V> inline int32<16> &operator=(const any_vec<64, V> &d) {
                *this = bit_cast<int32<16>>(d.wrapped().eval());
                return *this;
            }

            /// Construct from the underlying vector type
            inline int32<16>(const native_type &d) : d_(d) {
            }
            inline int32<16> &operator=(const native_type &d) {
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

            template <class E> inline int32<16>(const expr_vec_construct<E> &e) {
                detail::construct_eval_wrapper(*this, e.expr());
            }
            template <class E> inline int32<16> &operator=(const expr_vec_construct<E> &e) {
                detail::construct_eval_wrapper(*this, e.expr());
                return *this;
            }

            /// Access base vectors
            inline const int32<16> &vec(unsigned) const {
                return *this;
            }
            inline int32<16> &vec(unsigned) {
                return *this;
            }

            inline int32<16> eval() const {
                return *this;
            }

        private:
            native_type d_;
        };

        /** Class representing 8x 32-bit unsigned integer vector
         */
        template <> class uint32<16, void> : public any_int32<16, uint32<16, void>> {
        public:
            static const unsigned type_tag = SIMD_TAG_UINT;
            using element_type = uint32_t;
            using base_vector_type = uint32<16, void>;
            using expr_type = void;

#if SIMD_USE_AVX512F
            using native_type = __m512i;
#endif

            inline uint32<16>() = default;
            inline uint32<16>(const uint32<16> &) = default;
            inline uint32<16> &operator=(const uint32<16> &) = default;

            template <class E> inline uint32<16>(const uint32<16, E> &d) {
                *this = d.eval();
            }
            template <class E> inline uint32<16>(const int32<16, E> &d) {
                *this = d.eval();
            }
            template <class V> inline explicit uint32<16>(const any_vec<64, V> &d) {
                *this = bit_cast<uint32<16>>(d.wrapped().eval());
            }
            template <class V> inline uint32<16> &operator=(const any_vec<64, V> &d) {
                *this = bit_cast<uint32<16>>(d.wrapped().eval());
                return *this;
            }

            /// Construct from the underlying vector type
            inline uint32<16>(const native_type &d) : d_(d) {
            }
            inline uint32<16> &operator=(const native_type &d) {
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

            template <class E> inline uint32<16>(const expr_vec_construct<E> &e) {
                detail::construct_eval_wrapper(*this, e.expr());
            }
            template <class E> inline uint32<16> &operator=(const expr_vec_construct<E> &e) {
                detail::construct_eval_wrapper(*this, e.expr());
                return *this;
            }

            /// Access base vectors
            inline const uint32<16> &vec(unsigned) const {
                return *this;
            }
            inline uint32<16> &vec(unsigned) {
                return *this;
            }

            inline uint32<16> eval() const {
                return *this;
            }

        private:
            native_type d_;
        };

        /// Class representing possibly optimized mask data for 4x 32-bit integer
        /// vector
        template <> class mask_int32<16, void> : public any_int32<16, mask_int32<16, void>> {
        public:
            static const unsigned type_tag = SIMD_TAG_MASK_INT;
            using base_vector_type = mask_int32<16, void>;
            using expr_type = void;

#if SIMD_USE_AVX512F
            using native_type = __mmask16;
#endif

            inline mask_int32<16>() = default;
            inline mask_int32<16>(const mask_int32<16> &) = default;
            inline mask_int32<16> &operator=(const mask_int32<16> &) = default;

            inline mask_int32<16>(const native_type &d) : d_(d) {
            }

            template <class E> inline explicit mask_int32<16>(const mask_float32<16, E> &d) {
                *this = bit_cast<mask_int32<16>>(d.eval());
            }
            template <class E> inline mask_int32<16> &operator=(const mask_float32<16, E> &d) {
                *this = bit_cast<mask_int32<16>>(d.eval());
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
            inline uint32<16> unmask() const {
#if SIMD_USE_AVX512DQ
                return _mm512_movm_epi32(d_);
#elif SIMD_USE_AVX512F
                return _mm512_maskz_set1_epi32(d_, 0xffffffff);
#endif
            }

            inline const mask_int32<16> &vec(unsigned) const {
                return *this;
            }
            inline mask_int32<16> &vec(unsigned) {
                return *this;
            }

            inline mask_int32<16> eval() const {
                return *this;
            }

        private:
            native_type d_;
        };

#endif // SIMD_USE_AVX512F

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
