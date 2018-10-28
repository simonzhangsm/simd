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

#ifndef SIMD_DETAIL_INSN_BROADCAST_W_H
#define SIMD_DETAIL_INSN_BROADCAST_W_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/core/splat_n.h>
#include <bigmath/simd/detail/extract128.h>
#include <bigmath/simd/detail/insn/shuffle128.h>
#include <bigmath/simd/detail/shuffle/shuffle_mask.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {

                // -----------------------------------------------------------------------------

                template <unsigned s> inline uint8x16 i_splat(const uint8x16 &a) {
                    return i_splat16<s>(a);
                }

#if SIMD_USE_AVX2
                template <unsigned s> inline uint8x32 i_splat(const uint8x32 &a) {
                    static_assert(s < 32, "Access out of bounds");
                    uint8x16 lo;
                    lo = s < 16 ? detail::extract128<0>(a) : detail::extract128<1>(a);
                    lo = move16_l<s % 16>(lo);
                    return _mm256_broadcastb_epi8(lo.native());
                }
#endif

#if SIMD_USE_AVX512BW
                template <unsigned s> inline uint8<64> i_splat(const uint8<64> &a) {
                    static_assert(s < 64, "Access out of bounds");
                    uint8<16> lo;
                    lo = detail::extract128<s / 16>(a);
                    lo = move16_l<s % 16>(lo);
                    return _mm512_broadcastb_epi8(lo.native());
                }
#endif

                // -----------------------------------------------------------------------------

                template <unsigned s> inline uint16x8 i_splat(const uint16x8 &a) {
                    return i_splat8<s>(a);
                }

#if SIMD_USE_AVX2
                template <unsigned s> inline uint16x16 i_splat(const uint16x16 &a) {
                    static_assert(s < 16, "Access out of bounds");
                    uint16x8 lo;
                    lo = s < 8 ? detail::extract128<0>(a) : detail::extract128<1>(a);
                    lo = move8_l<s % 8>(lo);
                    return _mm256_broadcastw_epi16(lo.native());
                }
#endif

#if SIMD_USE_AVX512BW
                template <unsigned s> inline uint16<32> i_splat(const uint16<32> &a) {
                    static_assert(s < 32, "Access out of bounds");
                    uint16<8> lo;
                    lo = detail::extract128<s / 8>(a);
                    lo = move8_l<s % 8>(lo);
                    return _mm512_broadcastw_epi16(lo.native());
                }
#endif

                // -----------------------------------------------------------------------------

                template <unsigned s> inline uint32x4 i_splat(const uint32x4 &a) {
                    return i_splat4<s>(a);
                }

#if SIMD_USE_AVX2
                template <unsigned s> inline uint32x8 i_splat(const uint32x8 &ca) {
                    static_assert(s < 8, "Access out of bounds");
                    uint32<8> a = ca;
                    a = permute4<s % 4, s % 4, s % 4, s % 4>(a);
                    a = detail::shuffle1_128<s / 4, s / 4>(a, a);
                    return a;
                }
#endif

#if SIMD_USE_AVX512F
                template <unsigned s> inline uint32<16> i_splat(const uint32<16> &ca) {
                    static_assert(s < 16, "Access out of bounds");
                    uint32<16> a = ca;
                    a = permute4<s % 4, s % 4, s % 4, s % 4>(a);
                    a = detail::shuffle2_128<s / 4, s / 4, s / 4, s / 4>(a, a);
                    return a;
                }
#endif

                // -----------------------------------------------------------------------------

                template <unsigned s> inline uint64x2 i_splat(const uint64x2 &a) {
                    return i_splat2<s>(a);
                }

#if SIMD_USE_AVX2
                template <unsigned s> inline uint64x4 i_splat(const uint64x4 &a) {
                    static_assert(s < 4, "Access out of bounds");
                    return permute4<s, s, s, s>(a);
                }
#endif

#if SIMD_USE_AVX512F
                template <unsigned s> inline uint64<8> i_splat(const uint64<8> &ca) {
                    static_assert(s < 8, "Access out of bounds");
                    uint64<8> a = ca;
                    a = permute2<s % 2, s % 2>(a);
                    a = _mm512_shuffle_i64x2(a.native(),
                                             a.native(),
                                             SIMD_SHUFFLE_MASK_4x4(s / 2, s / 2, s / 2, s / 2)); // TODO extract
                    return a;
                }
#endif

                // -----------------------------------------------------------------------------

                template <unsigned s> inline float32x4 i_splat(const float32x4 &a) {
                    return i_splat4<s>(a);
                }

#if SIMD_USE_AVX
                template <unsigned s> inline float32x8 i_splat(const float32x8 &ca) {
                    static_assert(s < 8, "Access out of bounds");
                    float32<8> a = ca;
                    a = shuffle1_128<s / 4, s / 4>(a, a);
                    return permute4<s % 4, s % 4, s % 4, s % 4>(a);
                }
#endif

#if SIMD_USE_AVX512F
                template <unsigned s> inline float32<16> i_splat(const float32<16> &ca) {
                    static_assert(s < 16, "Access out of bounds");
                    float32<16> a = ca;
                    a = permute4<s % 4, s % 4, s % 4, s % 4>(a);
                    a = _mm512_shuffle_f32x4(a.native(), a.native(), SIMD_SHUFFLE_MASK_4x4(s / 4, s / 4, s / 4, s / 4));
                    return a;
                }
#endif

                // -----------------------------------------------------------------------------

                template <unsigned s> inline float64x2 i_splat(const float64x2 &a) {
                    return i_splat2<s>(a);
                }

#if SIMD_USE_AVX
                template <unsigned s> inline float64x4 i_splat(const float64x4 &a) {
                    static_assert(s < 4, "Access out of bounds");
#if SIMD_USE_AVX2
                    return permute4<s, s, s, s>(a);
#else // SIMD_USE_AVX
                    float64<4> b;
                    b = detail::shuffle1_128<s / 2, s / 2>(a, a);
                    b = permute2<s % 2, s % 2>(b);
                    return b;
#endif
                }
#endif

#if SIMD_USE_AVX512F
                template <unsigned s> inline float64<8> i_splat(const float64<8> &ca) {
                    static_assert(s < 8, "Access out of bounds");
                    float64<8> a = ca;
                    a = permute2<s % 2, s % 2>(a);
                    a = _mm512_shuffle_f64x2(a.native(),
                                             a.native(),
                                             SIMD_SHUFFLE_MASK_4x4(s / 2, s / 2, s / 2, s / 2)); // TODO extract
                    return a;
                }
#endif

                // -----------------------------------------------------------------------------

                template <unsigned s, class V> inline V i_splat(const V &a) {
                    static_assert(s < V::length, "Access out of bounds");

                    using U = typename V::base_vector_type;
                    U one = a.vec(s / U::length);

                    one = i_splat<s % U::length>(one);

                    V r;
                    for (unsigned i = 0; i < V::vec_length; ++i) {
                        r.vec(i) = one;
                    }
                    return r;
                }

            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
