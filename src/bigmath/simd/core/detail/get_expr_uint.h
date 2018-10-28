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

#ifndef SIMD_CORE_DETAIL_GET_EXPR_UINT_H
#define SIMD_CORE_DETAIL_GET_EXPR_UINT_H

#include <bigmath/simd/detail/get_expr.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {


            /*  We want to reduce the number of overloads that need to be created in order
                to match a specific case of an expression tree containing various integer
                operation nodes, such as add(int), mul_lo(int), etc. For particular
                vector size each of these operations are equivalent regardless of the
                argument types. Thus we simply convert the arguments of the expression to
                uint expressions of certain configuration.

                As a result, the following tuples of types will appear as the arguments
                 of the returned expression:

                  * uint8, uint8
                  * uint16, uint16
                  * uint32, uint32
                  * uint64, uint64
            */

            template <class V1, class V2> struct expr2_uint_maybe_scalar_tags {
                static const unsigned v1_type_tag = V1::type_tag;
                static const unsigned v1_size_tag = V1::size_tag;
                static const unsigned v2_type_tag = V2::type_tag;
                static const unsigned v2_size_tag = V2::size_tag;
                static const unsigned length_bytes = V1::length_bytes;
            };

            template <class V2> struct expr2_uint_maybe_scalar_tags<int, V2> {
                static const unsigned v1_type_tag = SIMD_TAG_INT;
                static const unsigned v1_size_tag = V2::size_tag;
                static const unsigned v2_type_tag = V2::type_tag;
                static const unsigned v2_size_tag = V2::size_tag;
                static const unsigned length_bytes = V2::length_bytes;
            };

            template <class V2> struct expr2_uint_maybe_scalar_tags<long, V2> {
                static const unsigned v1_type_tag = SIMD_TAG_INT;
                static const unsigned v1_size_tag = V2::size_tag;
                static const unsigned v2_type_tag = V2::type_tag;
                static const unsigned v2_size_tag = V2::size_tag;
                static const unsigned length_bytes = V2::length_bytes;
            };

            template <class V2> struct expr2_uint_maybe_scalar_tags<long long, V2> {
                static const unsigned v1_type_tag = SIMD_TAG_INT;
                static const unsigned v1_size_tag = V2::size_tag;
                static const unsigned v2_type_tag = V2::type_tag;
                static const unsigned v2_size_tag = V2::size_tag;
                static const unsigned length_bytes = V2::length_bytes;
            };

            template <class V2> struct expr2_uint_maybe_scalar_tags<unsigned, V2> {
                static const unsigned v1_type_tag = SIMD_TAG_UINT;
                static const unsigned v1_size_tag = V2::size_tag;
                static const unsigned v2_type_tag = V2::type_tag;
                static const unsigned v2_size_tag = V2::size_tag;
                static const unsigned length_bytes = V2::length_bytes;
            };

            template <class V2> struct expr2_uint_maybe_scalar_tags<unsigned long, V2> {
                static const unsigned v1_type_tag = SIMD_TAG_UINT;
                static const unsigned v1_size_tag = V2::size_tag;
                static const unsigned v2_type_tag = V2::type_tag;
                static const unsigned v2_size_tag = V2::size_tag;
                static const unsigned length_bytes = V2::length_bytes;
            };

            template <class V2> struct expr2_uint_maybe_scalar_tags<unsigned long long, V2> {
                static const unsigned v1_type_tag = SIMD_TAG_UINT;
                static const unsigned v1_size_tag = V2::size_tag;
                static const unsigned v2_type_tag = V2::type_tag;
                static const unsigned v2_size_tag = V2::size_tag;
                static const unsigned length_bytes = V2::length_bytes;
            };

            template <class V2> struct expr2_uint_maybe_scalar_tags<float, V2> {
                static const unsigned v1_type_tag = SIMD_TAG_INT;
                static const unsigned v1_size_tag = V2::size_tag;
                static const unsigned v2_type_tag = V2::type_tag;
                static const unsigned v2_size_tag = V2::size_tag;
                static const unsigned length_bytes = V2::length_bytes;
            };

            template <class V2> struct expr2_uint_maybe_scalar_tags<double, V2> {
                static const unsigned v1_type_tag = SIMD_TAG_INT;
                static const unsigned v1_size_tag = V2::size_tag;
                static const unsigned v2_type_tag = V2::type_tag;
                static const unsigned v2_size_tag = V2::size_tag;
                static const unsigned length_bytes = V2::length_bytes;
            };


            template <class V1> struct expr2_uint_maybe_scalar_tags<V1, int> {
                static const unsigned v1_type_tag = V1::type_tag;
                static const unsigned v1_size_tag = V1::size_tag;
                static const unsigned v2_type_tag = SIMD_TAG_INT;
                static const unsigned v2_size_tag = V1::size_tag;
                static const unsigned length_bytes = V1::length_bytes;
            };

            template <class V1> struct expr2_uint_maybe_scalar_tags<V1, long> {
                static const unsigned v1_type_tag = V1::type_tag;
                static const unsigned v1_size_tag = V1::size_tag;
                static const unsigned v2_type_tag = SIMD_TAG_INT;
                static const unsigned v2_size_tag = V1::size_tag;
                static const unsigned length_bytes = V1::length_bytes;
            };

            template <class V1> struct expr2_uint_maybe_scalar_tags<V1, long long> {
                static const unsigned v1_type_tag = V1::type_tag;
                static const unsigned v1_size_tag = V1::size_tag;
                static const unsigned v2_type_tag = SIMD_TAG_INT;
                static const unsigned v2_size_tag = V1::size_tag;
                static const unsigned length_bytes = V1::length_bytes;
            };

            template <class V1> struct expr2_uint_maybe_scalar_tags<V1, unsigned> {
                static const unsigned v1_type_tag = V1::type_tag;
                static const unsigned v1_size_tag = V1::size_tag;
                static const unsigned v2_type_tag = SIMD_TAG_UINT;
                static const unsigned v2_size_tag = V1::size_tag;
                static const unsigned length_bytes = V1::length_bytes;
            };

            template <class V1> struct expr2_uint_maybe_scalar_tags<V1, unsigned long> {
                static const unsigned v1_type_tag = V1::type_tag;
                static const unsigned v1_size_tag = V1::size_tag;
                static const unsigned v2_type_tag = SIMD_TAG_UINT;
                static const unsigned v2_size_tag = V1::size_tag;
                static const unsigned length_bytes = V1::length_bytes;
            };

            template <class V1> struct expr2_uint_maybe_scalar_tags<V1, unsigned long long> {
                static const unsigned v1_type_tag = V1::type_tag;
                static const unsigned v1_size_tag = V1::size_tag;
                static const unsigned v2_type_tag = SIMD_TAG_UINT;
                static const unsigned v2_size_tag = V1::size_tag;
                static const unsigned length_bytes = V1::length_bytes;
            };

            template <class V1> struct expr2_uint_maybe_scalar_tags<V1, float> {
                static const unsigned v1_type_tag = V1::type_tag;
                static const unsigned v1_size_tag = V1::size_tag;
                static const unsigned v2_type_tag = SIMD_TAG_INT;
                static const unsigned v2_size_tag = V1::size_tag;
                static const unsigned length_bytes = V1::length_bytes;
            };

            template <class V1> struct expr2_uint_maybe_scalar_tags<V1, double> {
                static const unsigned v1_type_tag = V1::type_tag;
                static const unsigned v1_size_tag = V1::size_tag;
                static const unsigned v2_type_tag = SIMD_TAG_INT;
                static const unsigned v2_size_tag = V1::size_tag;
                static const unsigned length_bytes = V1::length_bytes;
            };

            template <class V1, class V2> struct get_expr_uint_impl {
                using tags = expr2_uint_maybe_scalar_tags<V1, V2>;

#if SIMD_EXPR_DEBUG
                static_assert(tags::v1_size_tag == tags::v2_size_tag, "Mismatching vector sizes");
                static_assert(tags::v1_type_tag == SIMD_TAG_MASK_INT || tags::v1_type_tag == SIMD_TAG_UINT
                                  || tags::v1_type_tag == SIMD_TAG_INT,
                              "Incorrect type parameter");
                static_assert(tags::v2_type_tag == SIMD_TAG_MASK_INT || tags::v2_type_tag == SIMD_TAG_UINT
                                  || tags::v2_type_tag == SIMD_TAG_INT,
                              "Incorrect type parameter");
#endif

                // the size tag of the expression
                static const unsigned size_tag = tags::v1_size_tag;

                // (type_tag) get the type tag of the expression. Pretty much the same as
                // get_expr2_nomask does
                static const unsigned type_tag_t1 =
                    tags::v1_type_tag > tags::v2_type_tag ? tags::v1_type_tag : tags::v2_type_tag;
                static const unsigned type_tag = (type_tag_t1 == SIMD_TAG_MASK_INT) ? SIMD_TAG_UINT : type_tag_t1;

                // strip signed integer types and masks
                static const unsigned v1_type_tag = SIMD_TAG_UINT;
                static const unsigned v2_type_tag = SIMD_TAG_UINT;

                using v1_final_type = typename type_of_tag<v1_type_tag + size_tag, tags::length_bytes, void>::type;
                using v2_final_type = typename type_of_tag<v2_type_tag + size_tag, tags::length_bytes, void>::type;
            };

            template <template <class, class> class E, class V1, class V2> struct get_expr_uint {
                using impl = get_expr_uint_impl<V1, V2>;

                using type =
                    typename type_of_tag<impl::type_tag + impl::size_tag, impl::tags::length_bytes, E<V1, V2>>::type;
            };

        } // namespace detail
    }     // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
