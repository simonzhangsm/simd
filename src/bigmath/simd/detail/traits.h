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

#ifndef SIMD_DETAIL_TRAITS_H
#define SIMD_DETAIL_TRAITS_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {

            /*  Normalizes vector type. Removes sign from a vector type.
             */
            template <class V> struct remove_sign {
                using type = V;
                using expr = V;
            };

            template <unsigned N, class E> struct remove_sign<int8<N, E>> {
                using type = uint8<N>;
                using expr = uint8<N, E>;
            };
            template <unsigned N, class E> struct remove_sign<int16<N, E>> {
                using type = uint16<N>;
                using expr = uint16<N, E>;
            };
            template <unsigned N, class E> struct remove_sign<int32<N, E>> {
                using type = uint32<N>;
                using expr = uint32<N, E>;
            };
            template <unsigned N, class E> struct remove_sign<int64<N, E>> {
                using type = uint64<N>;
                using expr = uint64<N, E>;
            };

            /*  Normalizes vector type. Removes sign from a vector type. Result type is a
                value type, not an expression.
             */
            template <class V> struct remove_mask {
                using type = V;
                using expr = V;
            };

            template <unsigned N, class E> struct remove_mask<mask_int8<N, E>> {
                using type = uint8<N>;
                using expr = uint8<N, E>;
            };
            template <unsigned N, class E> struct remove_mask<mask_int16<N, E>> {
                using type = uint16<N>;
                using expr = uint16<N, E>;
            };
            template <unsigned N, class E> struct remove_mask<mask_int32<N, E>> {
                using type = uint32<N>;
                using expr = uint32<N, E>;
            };
            template <unsigned N, class E> struct remove_mask<mask_int64<N, E>> {
                using type = uint64<N>;
                using expr = uint64<N, E>;
            };
            template <unsigned N, class E> struct remove_mask<mask_float32<N, E>> {
                using type = float32<N>;
                using expr = float32<N, E>;
            };
            template <unsigned N, class E> struct remove_mask<mask_float64<N, E>> {
                using type = float64<N>;
                using expr = float64<N, E>;
            };

        } // namespace detail
    }     // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
