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

#ifndef SIMD_TYPES_TRAITS_H
#define SIMD_TYPES_TRAITS_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <type_traits>
namespace simd {
    namespace SIMD_ARCH_NAMESPACE {

        /// Allows detection whether specific type is a simd vector
        template <class T> struct is_vector : std::false_type {};

        template <unsigned N, class E> struct is_vector<float32<N, E>> : std::true_type {};
        template <unsigned N, class E> struct is_vector<float64<N, E>> : std::true_type {};
        template <unsigned N, class E> struct is_vector<int8<N, E>> : std::true_type {};
        template <unsigned N, class E> struct is_vector<int16<N, E>> : std::true_type {};
        template <unsigned N, class E> struct is_vector<int32<N, E>> : std::true_type {};
        template <unsigned N, class E> struct is_vector<int64<N, E>> : std::true_type {};
        template <unsigned N, class E> struct is_vector<uint8<N, E>> : std::true_type {};
        template <unsigned N, class E> struct is_vector<uint16<N, E>> : std::true_type {};
        template <unsigned N, class E> struct is_vector<uint32<N, E>> : std::true_type {};
        template <unsigned N, class E> struct is_vector<uint64<N, E>> : std::true_type {};
        template <unsigned N, class E> struct is_vector<mask_int8<N, E>> : std::true_type {};
        template <unsigned N, class E> struct is_vector<mask_int16<N, E>> : std::true_type {};
        template <unsigned N, class E> struct is_vector<mask_int32<N, E>> : std::true_type {};
        template <unsigned N, class E> struct is_vector<mask_int64<N, E>> : std::true_type {};
        template <unsigned N, class E> struct is_vector<mask_float32<N, E>> : std::true_type {};
        template <unsigned N, class E> struct is_vector<mask_float64<N, E>> : std::true_type {};

        /// Allows detection whether specific type is a simd value (i.e. not expression) vector
        template <class V> struct is_value_vector : std::false_type {};

        template <unsigned N> struct is_value_vector<float32<N>> : std::true_type {};
        template <unsigned N> struct is_value_vector<float64<N>> : std::true_type {};
        template <unsigned N> struct is_value_vector<int8<N>> : std::true_type {};
        template <unsigned N> struct is_value_vector<int16<N>> : std::true_type {};
        template <unsigned N> struct is_value_vector<int32<N>> : std::true_type {};
        template <unsigned N> struct is_value_vector<int64<N>> : std::true_type {};
        template <unsigned N> struct is_value_vector<uint8<N>> : std::true_type {};
        template <unsigned N> struct is_value_vector<uint16<N>> : std::true_type {};
        template <unsigned N> struct is_value_vector<uint32<N>> : std::true_type {};
        template <unsigned N> struct is_value_vector<uint64<N>> : std::true_type {};
        template <unsigned N> struct is_value_vector<mask_int8<N>> : std::true_type {};
        template <unsigned N> struct is_value_vector<mask_int16<N>> : std::true_type {};
        template <unsigned N> struct is_value_vector<mask_int32<N>> : std::true_type {};
        template <unsigned N> struct is_value_vector<mask_int64<N>> : std::true_type {};
        template <unsigned N> struct is_value_vector<mask_float32<N>> : std::true_type {};
        template <unsigned N> struct is_value_vector<mask_float64<N>> : std::true_type {};

        /// Allows detection whether specific type is a simd mask
        template <class T> struct is_mask : std::false_type {};

        template <unsigned N, class E> struct is_mask<mask_int8<N, E>> : std::true_type {};
        template <unsigned N, class E> struct is_mask<mask_int16<N, E>> : std::true_type {};
        template <unsigned N, class E> struct is_mask<mask_int32<N, E>> : std::true_type {};
        template <unsigned N, class E> struct is_mask<mask_int64<N, E>> : std::true_type {};
        template <unsigned N, class E> struct is_mask<mask_float32<N, E>> : std::true_type {};
        template <unsigned N, class E> struct is_mask<mask_float64<N, E>> : std::true_type {};

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
