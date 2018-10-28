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

#ifndef SIMD_TYPES_GENERIC_H
#define SIMD_TYPES_GENERIC_H

#include <bigmath/simd/setup_arch.h>
#include <bigmath/simd/types.h>
#include <type_traits>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {

        // -----------------------------------------------------------------------------

        /*
            Note: the name of the expression vector type only identifies the target
            type. In various cases we want to change the target type, thus the arbitrary
            conversions have been added.

            Expression types are not meant to be used by the user, thus all constructors
            are implicit.
        */

        // -----------------------------------------------------------------------------
        // float32

        template <unsigned N, class E> class float32 : public any_float32<N, float32<N, E>> {
        public:
            static const unsigned type_tag = SIMD_TAG_FLOAT;
            using expr_type = E;
            E e;

            inline float32(const E &a) : e(a) {
            }
            template <template <unsigned, class> class V, unsigned N2>
            inline float32(const any_vec<N * 4, V<N2, E>> &a) : e(a.wrapped().e) {
            }

            inline operator float32<N>() const {
                return eval();
            }
            inline float32<N> eval() const {
                return detail::expr_eval_wrapper<float32<N>, expr_type>::eval(e);
            }
        };

        template <unsigned N, class E> class mask_float32 : public any_float32<N, mask_float32<N, E>> {
        public:
            static const unsigned type_tag = SIMD_TAG_MASK_FLOAT;
            using expr_type = E;
            E e;

            inline mask_float32(const E &a) : e(a) {
            }

            inline operator mask_float32<N>() const {
                return eval();
            }
            inline operator float32<N>() const {
                return eval();
            }
            inline mask_float32<N> eval() const {
                return detail::expr_eval_wrapper<mask_float32<N>, expr_type>::eval(e);
            }
        };

        // -----------------------------------------------------------------------------
        // float64

        template <unsigned N, class E> class float64 : public any_float64<N, float64<N, E>> {
        public:
            static const unsigned type_tag = SIMD_TAG_FLOAT;
            using expr_type = E;
            E e;

            inline float64(const E &a) : e(a) {
            }
            template <template <unsigned, class> class V, unsigned N2>
            inline float64(const any_vec<N * 8, V<N2, E>> &a) : e(a.wrapped().e) {
            }

            inline operator float64<N>() const {
                return eval();
            }
            inline float64<N> eval() const {
                return detail::expr_eval_wrapper<float64<N>, expr_type>::eval(e);
            }
        };

        template <unsigned N, class E> class mask_float64 : public any_float64<N, mask_float64<N, E>> {
        public:
            static const unsigned type_tag = SIMD_TAG_MASK_FLOAT;
            using expr_type = E;
            E e;

            inline mask_float64(const E &a) : e(a) {
            }

            inline operator mask_float64<N>() const {
                return eval();
            }
            inline operator float64<N>() const {
                return eval();
            }
            inline mask_float64<N> eval() const {
                return detail::expr_eval_wrapper<mask_float64<N>, expr_type>::eval(e);
            }
        };

        // -----------------------------------------------------------------------------
        // uint8<N>
        template <unsigned N, class E> class int8 : public any_int8<N, int8<N, E>> {
        public:
            static const unsigned type_tag = SIMD_TAG_INT;
            using expr_type = E;
            E e;

            inline int8(const E &a) : e(a) {
            }

            template <template <unsigned, class> class V, unsigned N2>
            inline int8(const any_vec<N, V<N2, E>> &a) : e(a.wrapped().e) {
            }

            inline operator int8<N>() const {
                return eval();
            }
            inline int8<N> eval() const {
                return detail::expr_eval_wrapper<int8<N>, expr_type>::eval(e);
            }
        };


        template <unsigned N, class E> class uint8 : public any_int8<N, uint8<N, E>> {
        public:
            static const unsigned type_tag = SIMD_TAG_UINT;
            using expr_type = E;
            E e;

            inline uint8(const E &a) : e(a) {
            }

            template <template <unsigned, class> class V, unsigned N2>
            inline uint8(const any_vec<N, V<N2, E>> &a) : e(a.wrapped().e) {
            }

            inline operator uint8<N>() const {
                return eval();
            }
            inline uint8<N> eval() const {
                return detail::expr_eval_wrapper<uint8<N>, expr_type>::eval(e);
            }
        };

        template <unsigned N, class E> class mask_int8 : public any_int8<N, mask_int8<N, E>> {
        public:
            static const unsigned type_tag = SIMD_TAG_MASK_INT;
            using expr_type = E;
            E e;

            inline mask_int8(const E &a) : e(a) {
            }

            inline operator mask_int8<N>() const {
                return eval();
            }
            inline operator uint8<N>() const {
                return eval();
            }
            inline mask_int8<N> eval() const {
                return detail::expr_eval_wrapper<mask_int8<N>, expr_type>::eval(e);
            }
        };

        // -----------------------------------------------------------------------------
        // uint16<N>
        template <unsigned N, class E> class int16 : public any_int16<N, int16<N, E>> {
        public:
            static const unsigned type_tag = SIMD_TAG_INT;
            using expr_type = E;
            E e;

            inline int16(const E &a) : e(a) {
            }
            template <template <unsigned, class> class V, unsigned N2>
            inline int16(const any_vec<N * 2, V<N2, E>> &a) : e(a.wrapped().e) {
            }

            inline operator int16<N>() const {
                return eval();
            }
            inline int16<N> eval() const {
                return detail::expr_eval_wrapper<int16<N>, expr_type>::eval(e);
            }
        };


        template <unsigned N, class E> class uint16 : public any_int16<N, uint16<N, E>> {
        public:
            static const unsigned type_tag = SIMD_TAG_UINT;
            using expr_type = E;
            E e;

            inline uint16(const E &a) : e(a) {
            }
            template <template <unsigned, class> class V, unsigned N2>
            inline uint16(const any_vec<N * 2, V<N2, E>> &a) : e(a.wrapped().e) {
            }

            inline operator uint16<N>() const {
                return eval();
            }
            inline uint16<N> eval() const {
                return detail::expr_eval_wrapper<uint16<N>, expr_type>::eval(e);
            }
        };

        template <unsigned N, class E> class mask_int16 : public any_int16<N, mask_int16<N, E>> {
        public:
            static const unsigned type_tag = SIMD_TAG_MASK_INT;
            using expr_type = E;
            E e;

            inline mask_int16(const E &a) : e(a) {
            }

            inline operator mask_int16<N>() const {
                return eval();
            }
            inline operator uint16<N>() const {
                return eval();
            }
            inline mask_int16<N> eval() const {
                return detail::expr_eval_wrapper<mask_int16<N>, expr_type>::eval(e);
            }
        };

        // -----------------------------------------------------------------------------
        // uint32<N>
        template <unsigned N, class E> class int32 : public any_int32<N, int32<N, E>> {
        public:
            static const unsigned type_tag = SIMD_TAG_INT;
            using expr_type = E;
            E e;

            inline int32(const E &a) : e(a) {
            }
            template <template <unsigned, class> class V, unsigned N2>
            inline int32(const any_vec<N * 4, V<N2, E>> &a) : e(a.wrapped().e) {
            }

            inline operator int32<N>() const {
                return eval();
            }
            inline int32<N> eval() const {
                return detail::expr_eval_wrapper<int32<N>, expr_type>::eval(e);
            }
        };


        template <unsigned N, class E> class uint32 : public any_int32<N, uint32<N, E>> {
        public:
            static const unsigned type_tag = SIMD_TAG_UINT;
            using expr_type = E;
            E e;

            inline uint32(const E &a) : e(a) {
            }
            template <template <unsigned, class> class V, unsigned N2>
            inline uint32(const any_vec<N * 4, V<N2, E>> &a) : e(a.wrapped().e) {
            }

            inline operator uint32<N>() const {
                return eval();
            }
            inline uint32<N> eval() const {
                return detail::expr_eval_wrapper<uint32<N>, expr_type>::eval(e);
            }
        };

        template <unsigned N, class E> class mask_int32 : public any_int32<N, mask_int32<N, E>> {
        public:
            static const unsigned type_tag = SIMD_TAG_MASK_INT;
            using expr_type = E;
            E e;

            inline mask_int32(const E &a) : e(a) {
            }

            inline operator mask_int32<N>() const {
                return eval();
            }
            inline operator uint32<N>() const {
                return eval();
            }
            inline mask_int32<N> eval() const {
                return detail::expr_eval_wrapper<mask_int32<N>, expr_type>::eval(e);
            }
        };

        // -----------------------------------------------------------------------------
        // int64<N>

        template <unsigned N, class E> class int64 : public any_int64<N, int64<N, E>> {
        public:
            static const unsigned type_tag = SIMD_TAG_INT;
            using expr_type = E;
            E e;

            inline int64(const E &a) : e(a) {
            }
            template <template <unsigned, class> class V, unsigned N2>
            inline int64(const any_vec<N * 8, V<N2, E>> &a) : e(a.wrapped().e) {
            }

            inline operator int64<N>() const {
                return eval();
            }
            inline int64<N> eval() const {
                return detail::expr_eval_wrapper<int64<N>, expr_type>::eval(e);
            }
        };


        template <unsigned N, class E> class uint64 : public any_int64<N, uint64<N, E>> {
        public:
            static const unsigned type_tag = SIMD_TAG_UINT;
            using expr_type = E;
            E e;

            inline uint64(const E &a) : e(a) {
            }
            template <template <unsigned, class> class V, unsigned N2>
            inline uint64(const any_vec<N * 8, V<N2, E>> &a) : e(a.wrapped().e) {
            }

            inline operator uint64<N>() const {
                return eval();
            }
            inline uint64<N> eval() const {
                return detail::expr_eval_wrapper<uint64<N>, expr_type>::eval(e);
            }
        };


        template <unsigned N, class E> class mask_int64 : public any_int64<N, mask_int64<N, E>> {
        public:
            static const unsigned type_tag = SIMD_TAG_MASK_INT;
            using expr_type = E;
            E e;

            inline mask_int64(const E &a) : e(a) {
            }

            inline operator mask_int64<N>() const {
                return eval();
            }
            inline operator uint64<N>() const {
                return eval();
            }
            inline mask_int64<N> eval() const {
                return detail::expr_eval_wrapper<mask_int64<N>, expr_type>::eval(e);
            }
        };

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
