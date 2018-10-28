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

#ifndef SIMD_TYPES_EMPTY_EXPR_H
#define SIMD_TYPES_EMPTY_EXPR_H

#include <bigmath/simd/setup_arch.h>
#include <bigmath/simd/types.h>
#include <bigmath/simd/expr.h>
#include <type_traits>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {

        // -----------------------------------------------------------------------------
        // float32

        template <unsigned N> class float32<N, expr_empty> : public any_float32<N, float32<N, expr_empty>> {
        public:
            static const unsigned type_tag = SIMD_TAG_FLOAT;
            using expr_type = expr_empty;
            float32<N> e;

            inline float32(const float32<N> &a) : e(a) {
            }
            template <template <unsigned, class> class V, unsigned N2>
            inline float32(const any_vec<N * 4, V<N2, void>> &a) : e(a.wrapped()) {
            }

            inline operator float32<N>() const {
                return e;
            }
            inline float32<N> eval() const {
                return e;
            }
        };

        template <unsigned N> class mask_float32<N, expr_empty> : public any_float32<N, mask_float32<N, expr_empty>> {
        public:
            static const unsigned type_tag = SIMD_TAG_MASK_FLOAT;
            using expr_type = expr_empty;
            mask_float32<N> e;

            inline mask_float32(const mask_float32<N> &a) : e(a) {
            }

            inline operator mask_float32<N>() const {
                return e;
            }
            inline operator float32<N>() const {
                return e;
            }
            inline mask_float32<N> eval() const {
                return e;
            }
        };

        // -----------------------------------------------------------------------------
        // float64

        template <unsigned N> class float64<N, expr_empty> : public any_float64<N, float64<N, expr_empty>> {
        public:
            static const unsigned type_tag = SIMD_TAG_FLOAT;
            using expr_type = expr_empty;
            float64<N> e;

            inline float64(const float64<N> &a) : e(a) {
            }
            template <template <unsigned, class> class V, unsigned N2>
            inline float64(const any_vec<N * 8, V<N2, void>> &a) : e(a.wrapped()) {
            }

            inline operator float64<N>() const {
                return e;
            }
            inline float64<N> eval() const {
                return e;
            }
        };

        template <unsigned N> class mask_float64<N, expr_empty> : public any_float64<N, mask_float64<N, expr_empty>> {
        public:
            static const unsigned type_tag = SIMD_TAG_MASK_FLOAT;
            using expr_type = expr_empty;
            mask_float64<N> e;

            inline mask_float64(const mask_float64<N> &a) : e(a) {
            }

            inline operator mask_float64<N>() const {
                return e;
            }
            inline operator float64<N>() const {
                return e;
            }
            inline mask_float64<N> eval() const {
                return e;
            }
        };

        // -----------------------------------------------------------------------------
        // uint8<N>
        template <unsigned N> class int8<N, expr_empty> : public any_int8<N, int8<N, expr_empty>> {
        public:
            static const unsigned type_tag = SIMD_TAG_INT;
            using expr_type = expr_empty;
            int8<N> e;

            inline int8(const int8<N> &a) : e(a) {
            }
            template <template <unsigned, class> class V, unsigned N2>
            inline int8(const any_vec<N, V<N2, void>> &a) : e(a.wrapped()) {
            }

            inline operator int8<N>() const {
                return e;
            }
            inline int8<N> eval() const {
                return e;
            }
        };


        template <unsigned N> class uint8<N, expr_empty> : public any_int8<N, uint8<N, expr_empty>> {
        public:
            static const unsigned type_tag = SIMD_TAG_UINT;
            using expr_type = expr_empty;
            uint8<N> e;

            inline uint8(const uint8<N> &a) : e(a) {
            }
            template <template <unsigned, class> class V, unsigned N2>
            inline uint8(const any_vec<N, V<N2, void>> &a) : e(a.wrapped()) {
            }

            inline operator uint8<N>() const {
                return e;
            }
            inline uint8<N> eval() const {
                return e;
            }
        };

        template <unsigned N> class mask_int8<N, expr_empty> : public any_int8<N, mask_int8<N, expr_empty>> {
        public:
            static const unsigned type_tag = SIMD_TAG_MASK_INT;
            using expr_type = expr_empty;
            mask_int8<N> e;

            inline mask_int8(const mask_int8<N> &a) : e(a) {
            }

            inline operator mask_int8<N>() const {
                return e;
            }
            inline operator uint8<N>() const {
                return e;
            }
            inline mask_int8<N> eval() const {
                return e;
            }
        };

        // -----------------------------------------------------------------------------
        // uint16<N>
        template <unsigned N> class int16<N, expr_empty> : public any_int16<N, int16<N, expr_empty>> {
        public:
            static const unsigned type_tag = SIMD_TAG_INT;
            using expr_type = expr_empty;
            int16<N> e;

            inline int16(const int16<N> &a) : e(a) {
            }
            template <template <unsigned, class> class V, unsigned N2>
            inline int16(const any_vec<N * 2, V<N2, void>> &a) : e(a.wrapped()) {
            }

            inline operator int16<N>() const {
                return e;
            }
            inline int16<N> eval() const {
                return e;
            }
        };


        template <unsigned N> class uint16<N, expr_empty> : public any_int16<N, uint16<N, expr_empty>> {
        public:
            static const unsigned type_tag = SIMD_TAG_UINT;
            using expr_type = expr_empty;
            uint16<N> e;

            inline uint16(const uint16<N> &a) : e(a) {
            }
            template <template <unsigned, class> class V, unsigned N2>
            inline uint16(const any_vec<N * 2, V<N2, void>> &a) : e(a.wrapped()) {
            }

            inline operator uint16<N>() const {
                return e;
            }
            inline uint16<N> eval() const {
                return e;
            }
        };

        template <unsigned N> class mask_int16<N, expr_empty> : public any_int16<N, mask_int16<N, expr_empty>> {
        public:
            static const unsigned type_tag = SIMD_TAG_MASK_INT;
            using expr_type = expr_empty;
            mask_int16<N> e;

            inline mask_int16(const mask_int16<N> &a) : e(a) {
            }

            inline operator mask_int16<N>() const {
                return e;
            }
            inline operator uint16<N>() const {
                return e;
            }
            inline mask_int16<N> eval() const {
                return e;
            }
        };

        // -----------------------------------------------------------------------------
        // uint32<N>
        template <unsigned N> class int32<N, expr_empty> : public any_int32<N, int32<N, expr_empty>> {
        public:
            static const unsigned type_tag = SIMD_TAG_INT;
            using expr_type = expr_empty;
            int32<N> e;

            inline int32(const int32<N> &a) : e(a) {
            }
            template <template <unsigned, class> class V, unsigned N2>
            inline int32(const any_vec<N * 4, V<N2, void>> &a) : e(a.wrapped()) {
            }

            inline operator int32<N>() const {
                return e;
            }
            inline int32<N> eval() const {
                return e;
            }
        };


        template <unsigned N> class uint32<N, expr_empty> : public any_int32<N, uint32<N, expr_empty>> {
        public:
            static const unsigned type_tag = SIMD_TAG_UINT;
            using expr_type = expr_empty;
            uint32<N> e;

            inline uint32(const uint32<N> &a) : e(a) {
            }
            template <template <unsigned, class> class V, unsigned N2>
            inline uint32(const any_vec<N * 4, V<N2, void>> &a) : e(a.wrapped()) {
            }

            inline operator uint32<N>() const {
                return e;
            }
            inline uint32<N> eval() const {
                return e;
            }
        };

        template <unsigned N> class mask_int32<N, expr_empty> : public any_int32<N, mask_int32<N, expr_empty>> {
        public:
            static const unsigned type_tag = SIMD_TAG_MASK_INT;
            using expr_type = expr_empty;
            mask_int32<N> e;

            inline mask_int32(const mask_int32<N> &a) : e(a) {
            }

            inline operator mask_int32<N>() const {
                return e;
            }
            inline operator uint32<N>() const {
                return e;
            }
            inline mask_int32<N> eval() const {
                return e;
            }
        };

        // -----------------------------------------------------------------------------
        // int64<N>

        template <unsigned N> class int64<N, expr_empty> : public any_int64<N, int64<N, expr_empty>> {
        public:
            static const unsigned type_tag = SIMD_TAG_INT;
            using expr_type = expr_empty;
            int64<N> e;

            inline int64(const int64<N> &a) : e(a) {
            }
            template <template <unsigned, class> class V, unsigned N2>
            inline int64(const any_vec<N * 8, V<N2, void>> &a) : e(a.wrapped()) {
            }

            inline operator int64<N>() const {
                return e;
            }
            inline int64<N> eval() const {
                return e;
            }
        };


        template <unsigned N> class uint64<N, expr_empty> : public any_int64<N, uint64<N, expr_empty>> {
        public:
            static const unsigned type_tag = SIMD_TAG_UINT;
            using expr_type = expr_empty;
            uint64<N> e;

            inline uint64(const uint64<N> &a) : e(a) {
            }
            template <template <unsigned, class> class V, unsigned N2>
            inline uint64(const any_vec<N * 8, V<N2, void>> &a) : e(a.wrapped()) {
            }

            inline operator uint64<N>() const {
                return e;
            }
            inline uint64<N> eval() const {
                return e;
            }
        };


        template <unsigned N> class mask_int64<N, expr_empty> : public any_int64<N, mask_int64<N, expr_empty>> {
        public:
            static const unsigned type_tag = SIMD_TAG_MASK_INT;
            using expr_type = expr_empty;
            mask_int64<N> e;

            inline mask_int64(const mask_int64<N> &a) : e(a) {
            }

            inline operator mask_int64<N>() const {
                return e;
            }
            inline operator uint64<N>() const {
                return e;
            }
            inline mask_int64<N> eval() const {
                return e;
            }
        };

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
