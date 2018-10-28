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

#ifndef DETAIL_EXTRACT128_H
#define DETAIL_EXTRACT128_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {

#if SIMD_USE_AVX2
            template <unsigned s> inline uint8x16 extract128(const uint8x32 &a) {
                return s == 0 ? _mm256_castsi256_si128(a.native()) : _mm256_extracti128_si256(a.native(), 1);
            }

            template <unsigned s> inline uint16x8 extract128(const uint16x16 &a) {
                return (uint16x8)extract128<s>(uint8x32(a));
            }
            template <unsigned s> inline uint32x4 extract128(const uint32x8 &a) {
                return (uint32x4)extract128<s>(uint8x32(a));
            }
            template <unsigned s> inline uint64x2 extract128(const uint64x4 &a) {
                return (uint64x2)extract128<s>(uint8x32(a));
            }

            template <unsigned s> inline int8x16 extract128(const int8x32 &a) {
                return (int8x16)extract128<s>(uint8x32(a));
            }
            template <unsigned s> inline int16x8 extract128(const int16x16 &a) {
                return (int16x8)extract128<s>(uint8x32(a));
            }
            template <unsigned s> inline int32x4 extract128(const int32x8 &a) {
                return (int32x4)extract128<s>(uint8x32(a));
            }
            template <unsigned s> inline int64x2 extract128(const int64x4 &a) {
                return (int64x2)extract128<s>(uint8x32(a));
            }
#endif

#if SIMD_USE_AVX
            template <unsigned s> inline float32x4 extract128(const float32x8 &a) {
                return s == 0 ? _mm256_castps256_ps128(a.native()) : _mm256_extractf128_ps(a.native(), 1);
            }

            template <unsigned s> inline float64x2 extract128(const float64x4 &a) {
                return s == 0 ? _mm256_castpd256_pd128(a.native()) : _mm256_extractf128_pd(a.native(), 1);
            }
#endif

#if SIMD_USE_AVX512BW
            template <unsigned s> inline uint8<16> extract128(const uint8<64> &a) {
                return _mm512_extracti32x4_epi32(a.native(), s);
            }
            template <unsigned s> inline int8<16> extract128(const int8<64> &a) {
                return (int8<16>)extract128<s>(uint8<64>(a));
            }

            template <unsigned s> inline uint16<8> extract128(const uint16<32> &a) {
                return (uint16<8>)extract128<s>(uint8<64>(a));
            }
            template <unsigned s> inline int16<8> extract128(const int16<32> &a) {
                return (int16<8>)extract128<s>(uint8<64>(a));
            }
#endif

#if SIMD_USE_AVX512F
            template <unsigned s> inline uint32x4 extract128(const uint32<16> &a) {
                return _mm512_extracti32x4_epi32(a.native(), s);
            }

            template <unsigned s> inline uint64x2 extract128(const uint64<8> &a) {
                return (uint64x2)extract128<s>(uint32<16>(a));
            }

            template <unsigned s> inline int32x4 extract128(const int32<16> &a) {
                return (int32x4)extract128<s>(uint32<16>(a));
            }
            template <unsigned s> inline int64x2 extract128(const int64<8> &a) {
                return (int64x2)extract128<s>(uint32<16>(a));
            }

            template <unsigned s> inline float32x4 extract128(const float32<16> &a) {
                return _mm512_extractf32x4_ps(a.native(), s);
            }

            template <unsigned s> inline float64x2 extract128(const float64<8> &a) {
                return _mm_castps_pd(_mm512_extractf32x4_ps(_mm512_castpd_ps(a.native()), s));
            }

            template <unsigned s> inline uint32x8 extract256(const uint32<16> &a) {
                return _mm512_extracti64x4_epi64(a.native(), s);
            }

            template <unsigned s> inline uint64x4 extract256(const uint64<8> &a) {
                return (uint64x4)extract256<s>(uint32<16>(a));
            }

            template <unsigned s> inline int32x8 extract256(const int32<16> &a) {
                return (int32x8)extract256<s>(uint32<16>(a));
            }
            template <unsigned s> inline int64x4 extract256(const int64<8> &a) {
                return (int64x4)extract256<s>(uint32<16>(a));
            }

            template <unsigned s> inline float32<8> extract256(const float32<16> &a) {
                return _mm256_castpd_ps(_mm512_extractf64x4_pd(_mm512_castps_pd(a.native()), s));
            }

            template <unsigned s> inline float64<4> extract256(const float64<8> &a) {
                return _mm512_extractf64x4_pd(a.native(), s);
            }
#endif

#if SIMD_USE_AVX512BW
            template <unsigned s> inline uint8<32> extract256(const uint8<64> &a) {
                return _mm512_extracti64x4_epi64(a.native(), s);
            }

            template <unsigned s> inline uint16<16> extract256(const uint16<32> &a) {
                return _mm512_extracti64x4_epi64(a.native(), s);
            }

            template <unsigned s> inline int8<32> extract256(const int8<64> &a) {
                return _mm512_extracti64x4_epi64(a.native(), s);
            }

            template <unsigned s> inline int16<16> extract256(const int16<32> &a) {
                return _mm512_extracti64x4_epi64(a.native(), s);
            }
#endif

        } // namespace detail
    }     // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
