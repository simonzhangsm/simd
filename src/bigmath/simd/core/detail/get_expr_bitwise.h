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

#ifndef SIMD_CORE_DETAIL_GET_EXPR_BITWISE_H
#define SIMD_CORE_DETAIL_GET_EXPR_BITWISE_H

#include <bigmath/simd/detail/get_expr.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {


            /*  We want to reduce the number of overloads that need to be created in order
                to match a specific case of an expression tree containing 'bit_and',
                or 'bit_andnot'. nodes. The following "optimizations"
                are performed:

                  * If the parameters are types have different element sizes then both
                    expression arguments have the same type as the expression itself, except
                    that signed vectors are converted to unsigned vectors.
                  * Otherwise if the expression is of a mask type then both types are the
                    same as the expression itself.
                  * Otherwise both types have the same type as the expression itself, except
                    that signed vectors are converted to unsigned vectors and if the second
                    type is a mask type then it is converted to floating-point mask if the
                    expression is floating-point expression and to integer mask otherwise.

                 So, as a result, the following tuples of types will appear as the arguments
                 of the returned expression:

                  * mask_int8, mask_int8
                  * uint8, mask_int8
                  * uint8, uint8
                  * mask_int16, mask_int16
                  * uint16, mask_int16
                  * uint16, uint16
                  * mask_int32, mask_int32
                  * uint32, mask_int32
                  * uint32, uint32
                  * mask_int64, mask_int64
                  * uint64, mask_int64
                  * uint64, uint64
                  * mask_float32, mask_float32
                  * float32, mask_float32
                  * float32, float32
                  * mask_float64, mask_float64
                  * float64, mask_float64
                  * float64, float64

                The type of the returned expression is governed by the usual rules
                (see simd/types/tag.h)
            */

            template <class V1, class V2> struct get_expr_bitwise2_and_impl {
                using tags = expr2_maybe_scalar_tags<V1, V2>;

                // (size_tag) get the size tag of the resulting expression
                static const unsigned size_tag =
                    tags::v1_size_tag > tags::v2_size_tag ? tags::v1_size_tag : tags::v2_size_tag;

                // (type_tag) get the type tag of the expression. We compute it in the same
                // way get_expr2 computes them, i.e.
                // type_tag == get_expr2<V1,V2>::type::type_tag
                static const unsigned type_tag_t1 =
                    tags::v1_type_tag > tags::v2_type_tag ? tags::v1_type_tag : tags::v2_type_tag;
                static const bool is_mask_op1 = type_tag_t1 == SIMD_TAG_MASK_INT || type_tag_t1 == SIMD_TAG_MASK_FLOAT;
                static const unsigned type_tag =
                    (is_mask_op1 && tags::v1_size_tag != tags::v2_size_tag) ? SIMD_TAG_UINT : type_tag_t1;

                // strip signed integer types
                static const unsigned v1_type_tag = type_tag == SIMD_TAG_INT ? SIMD_TAG_UINT : type_tag;


                static const bool is_v2_mask =
                    tags::v2_type_tag == SIMD_TAG_MASK_INT || tags::v2_type_tag == SIMD_TAG_MASK_FLOAT;
                static const bool is_v1_float = type_tag == SIMD_TAG_FLOAT || type_tag == SIMD_TAG_MASK_FLOAT;

                // if second parameter is a mask, then:
                //    - convert the mask to float mask if the expression is float
                //    - convert the mask to integer mask otherwise
                static const unsigned v2_type_tag =
                    (!is_v2_mask) ? v1_type_tag : is_v1_float ? SIMD_TAG_MASK_FLOAT : SIMD_TAG_MASK_INT;

                using v1_final_type = typename type_of_tag<v1_type_tag + size_tag, tags::length_bytes, void>::type;
                using v2_final_type = typename type_of_tag<v2_type_tag + size_tag, tags::length_bytes, void>::type;
            };

            template <template <class, class> class E, class V1, class V2> struct get_expr_bitwise2_and {
                using impl = get_expr_bitwise2_and_impl<V1, V2>;
                using type =
                    typename type_of_tag<impl::type_tag + impl::size_tag, impl::tags::length_bytes, E<V1, V2>>::type;
            };


            /*  The case with bit_or is similar to bit_and and bit_andnot except that the
                expression types are either leave two masks or none.

                  * Both expression arguments have the same type as the expression itself,
                    except that signed vectors are converted to unsigned vectors.

                 So, as a result, the following tuples of types will appear as the arguments
                 of the returned expression:

                  * mask_int8, mask_int8
                  * uint8, uint8
                  * mask_int16, mask_int16
                  * uint16, uint16
                  * mask_int32, mask_int32
                  * uint32, uint32
                  * mask_int64, mask_int64
                  * uint64, uint64
                  * mask_float32, mask_float32
                  * float32, float32
                  * mask_float64, mask_float64
                  * float64, float64

                The type of the returned expression is governed by the usual rules
                (see simd/types/tag.h)
            */

            template <class V1, class V2> class get_expr_bit_or {

                // (size_tag) get the size tag of the resulting expression
                static const unsigned size_tag = V1::size_tag > V2::size_tag ? V1::size_tag : V2::size_tag;

                // (type_tag) get the type tag of the expression. We compute it in the same
                // way get_expr2 computes them, i.e.
                // type_tag == get_expr2<V1,V2>::type::type_tag
                static const unsigned type_tag_t1 = V1::type_tag > V2::type_tag ? V1::type_tag : V2::type_tag;
                static const bool is_mask_op1 = type_tag_t1 == SIMD_TAG_MASK_INT || type_tag_t1 == SIMD_TAG_MASK_FLOAT;
                static const unsigned type_tag =
                    (is_mask_op1 && V1::size_tag != V2::size_tag) ? SIMD_TAG_UINT : type_tag_t1;

                // strip signed integer types
                static const unsigned v12_type_tag = type_tag == SIMD_TAG_INT ? SIMD_TAG_UINT : type_tag;


            public:
                using v1_final_type = typename type_of_tag<v12_type_tag + size_tag, V1::length_bytes, void>::type;
                using v2_final_type = typename type_of_tag<v12_type_tag + size_tag, V1::length_bytes, void>::type;

                using type = typename type_of_tag<type_tag + size_tag, V1::length_bytes, expr_bit_or<V1, V2>>::type;
            };


        } // namespace detail
    }     // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
