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

#ifndef SIMD_TYPES_ANY_H
#define SIMD_TYPES_ANY_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types/fwd.h>
#include <cstdint>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {

        /** Represents any vector that has @a B bytes of data. The exact vector type is
            @a V.
        */
        template <unsigned B, class V> struct any_vec {
            static const unsigned length_bytes = B;
            using type = V;

            /// Returns the wrapped vector
            inline V &wrapped() {
                return static_cast<V &>(*this);
            }
            inline const V &wrapped() const {
                return static_cast<const V &>(*this);
            }
        };

        template <unsigned N, class V> struct any_vec8 : any_vec<N, V> {
            static const unsigned size_tag = SIMD_TAG_SIZE8;
        };
        template <unsigned N, class V> struct any_vec16 : any_vec<N * 2, V> {
            static const unsigned size_tag = SIMD_TAG_SIZE16;
        };
        template <unsigned N, class V> struct any_vec32 : any_vec<N * 4, V> {
            static const unsigned size_tag = SIMD_TAG_SIZE32;
        };
        template <unsigned N, class V> struct any_vec64 : any_vec<N * 8, V> {
            static const unsigned size_tag = SIMD_TAG_SIZE64;
        };

        template <unsigned N, class V> struct any_float32 : any_vec32<N, V> {
            static const unsigned length = N;
            static const unsigned base_length = SIMD_FAST_FLOAT32_SIZE;
            static const unsigned vec_length = (N + SIMD_FAST_FLOAT32_SIZE - 1) / SIMD_FAST_FLOAT32_SIZE;
            using element_type = float;
            using uint_element_type = uint32_t;
            using int_vector_type = int32<N>;
            using uint_vector_type = uint32<N>;
            using mask_vector_type = mask_float32<N>;
            static const unsigned num_bits = 32;
            static const uint_element_type all_bits = 0xffffffff;
        };

        template <unsigned N, class V> struct any_float64 : any_vec64<N, V> {
            static const unsigned length = N;
            static const unsigned base_length = SIMD_FAST_FLOAT64_SIZE;
            static const unsigned vec_length = (N + SIMD_FAST_FLOAT64_SIZE - 1) / SIMD_FAST_FLOAT64_SIZE;
            using element_type = double;
            using uint_element_type = uint64_t;
            using int_vector_type = int64<N>;
            using uint_vector_type = uint64<N>;
            using mask_vector_type = mask_float64<N>;
            static const unsigned num_bits = 64;
            static const uint_element_type all_bits = 0xffffffffffffffff;
        };

        template <unsigned N, class V> struct any_int8 : any_vec8<N, V> {
            static const unsigned length = N;
            static const unsigned base_length = SIMD_FAST_INT8_SIZE;
            static const unsigned vec_length = (N + SIMD_FAST_INT8_SIZE - 1) / SIMD_FAST_INT8_SIZE;
            using uint_element_type = uint8_t;
            using int_vector_type = int8<N>;
            using uint_vector_type = uint8<N>;
            using mask_vector_type = mask_int8<N>;

            static const unsigned num_bits = 8;
            static const uint_element_type all_bits = 0xff;
        };

        template <unsigned N, class V> struct any_int16 : any_vec16<N, V> {
            static const unsigned length = N;
            static const unsigned base_length = SIMD_FAST_INT16_SIZE;
            static const unsigned vec_length = (N + SIMD_FAST_INT16_SIZE - 1) / SIMD_FAST_INT16_SIZE;
            using uint_element_type = uint16_t;
            using int_vector_type = int16<N>;
            using uint_vector_type = uint16<N>;
            using mask_vector_type = mask_int16<N>;

            static const unsigned num_bits = 16;
            static const uint_element_type all_bits = 0xffff;
        };

        template <unsigned N, class V> struct any_int32 : any_vec32<N, V> {
            static const unsigned length = N;
            static const unsigned base_length = SIMD_FAST_INT32_SIZE;
            static const unsigned vec_length = (N + SIMD_FAST_INT32_SIZE - 1) / SIMD_FAST_INT32_SIZE;
            using uint_element_type = uint32_t;
            using int_vector_type = int32<N>;
            using uint_vector_type = uint32<N>;
            using mask_vector_type = mask_int32<N>;

            static const unsigned num_bits = 32;
            static const uint_element_type all_bits = 0xffffffff;
        };

        template <unsigned N, class V> struct any_int64 : any_vec64<N, V> {
            static const unsigned length = N;
            static const unsigned base_length = SIMD_FAST_INT64_SIZE;
            static const unsigned vec_length = (N + SIMD_FAST_INT64_SIZE - 1) / SIMD_FAST_INT64_SIZE;
            using uint_element_type = uint64_t;
            using int_vector_type = int64<N>;
            using uint_vector_type = uint64<N>;
            using mask_vector_type = mask_int64<N>;

            static const unsigned num_bits = 64;
            static const uint_element_type all_bits = 0xffffffffffffffff;
        };

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
