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

#ifndef SIMD_DETAIL_WIDTH_H
#define SIMD_DETAIL_WIDTH_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {

            struct vec128_impl {
                using i8 = int8x16;
                using u8 = uint8x16;
                using i16 = int16x8;
                using u16 = uint16x8;
                using i32 = int32x4;
                using u32 = uint32x4;
                using i64 = int64x2;
                using u64 = uint64x2;
                using f32 = float32x4;
                using f64 = float64x2;
            };

            struct vec256_impl {
                using i8 = int8x32;
                using u8 = uint8x32;
                using i16 = int16x16;
                using u16 = uint16x16;
                using i32 = int32x8;
                using u32 = uint32x8;
                using i64 = int64x4;
                using u64 = uint64x4;
                using f32 = float32x8;
                using f64 = float64x4;
            };

            struct vec512_impl {
                using i8 = int8<64>;
                using u8 = uint8<64>;
                using i16 = int16<32>;
                using u16 = uint16<32>;
                using i32 = int32<16>;
                using u32 = uint32<16>;
                using i64 = int64<8>;
                using u64 = uint64<8>;
                using f32 = float32<16>;
                using f64 = float64<8>;
            };

            template <class T> struct same_width;
            template <> struct same_width<int8x16> : vec128_impl {};
            template <> struct same_width<uint8x16> : vec128_impl {};
            template <> struct same_width<int16x8> : vec128_impl {};
            template <> struct same_width<uint16x8> : vec128_impl {};
            template <> struct same_width<int32x4> : vec128_impl {};
            template <> struct same_width<uint32x4> : vec128_impl {};
            template <> struct same_width<int64x2> : vec128_impl {};
            template <> struct same_width<uint64x2> : vec128_impl {};
            template <> struct same_width<float32x4> : vec128_impl {};
            template <> struct same_width<float64x2> : vec128_impl {};

            template <> struct same_width<int8x32> : vec256_impl {};
            template <> struct same_width<uint8x32> : vec256_impl {};
            template <> struct same_width<int16x16> : vec256_impl {};
            template <> struct same_width<uint16x16> : vec256_impl {};
            template <> struct same_width<int32x8> : vec256_impl {};
            template <> struct same_width<uint32x8> : vec256_impl {};
            template <> struct same_width<int64x4> : vec256_impl {};
            template <> struct same_width<uint64x4> : vec256_impl {};
            template <> struct same_width<float32x8> : vec256_impl {};
            template <> struct same_width<float64x4> : vec256_impl {};

            template <> struct same_width<int8<64>> : vec512_impl {};
            template <> struct same_width<uint8<64>> : vec512_impl {};
            template <> struct same_width<int16<32>> : vec512_impl {};
            template <> struct same_width<uint16<32>> : vec512_impl {};
            template <> struct same_width<int32<16>> : vec512_impl {};
            template <> struct same_width<uint32<16>> : vec512_impl {};
            template <> struct same_width<int64<8>> : vec512_impl {};
            template <> struct same_width<uint64<8>> : vec512_impl {};
            template <> struct same_width<float32<16>> : vec512_impl {};
            template <> struct same_width<float64<8>> : vec512_impl {};

        } // namespace detail
    }     // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
