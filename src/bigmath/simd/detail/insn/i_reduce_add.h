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

#ifndef SIMD_DETAIL_INSN_I_REDUCE_ADD_H
#define SIMD_DETAIL_INSN_I_REDUCE_ADD_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/core/extract.h>
#include <bigmath/simd/core/move_l.h>
#include <bigmath/simd/core/make_uint.h>
#include <bigmath/simd/detail/extract128.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {

        // forward declarations
        template <unsigned N, class E> inline int16_t reduce_add(const int8<N, E> &a);
        template <unsigned N, class E> inline uint16_t reduce_add(const uint8<N, E> &a);
        template <unsigned N, class E> inline int32_t reduce_add(const int16<N, E> &a);
        template <unsigned N, class E> inline uint32_t reduce_add(const uint16<N, E> &a);
        template <unsigned N, class E> inline int32_t reduce_add(const int32<N, E> &a);
        template <unsigned N, class E> inline uint32_t reduce_add(const uint32<N, E> &a);
        template <unsigned N, class E> inline int64_t reduce_add(const int64<N, E> &a);
        template <unsigned N, class E> inline uint64_t reduce_add(const uint64<N, E> &a);

        namespace detail {
            namespace insn {

                static inline uint16_t i_reduce_add(const uint8x16 &a) {
#if SIMD_USE_NULL
                    uint16_t r = a.el(0);
                    for (unsigned i = 1; i < a.length; i++) {
                        r += a.el(i);
                    }
                    return r;
#elif SIMD_USE_XOP
                    uint16x8 sum = _mm_haddq_epu8(a.native());
                    return extract<0>(sum) + extract<4>(sum);
#elif SIMD_USE_SSE2
                    uint16x8 sum = _mm_sad_epu8(a.native(), _mm_setzero_si128());
                    return extract<0>(sum) + extract<4>(sum);
#elif SIMD_USE_NEON
                    uint16x8 a2 = vpaddlq_u8(a.native());
                    uint32x4 a3 = vpaddlq_u16(a2.native());
                    uint64x2 a4 = vpaddlq_u32(a3.native());
                    a3 = a4;
                    uint32x2_t r = vadd_u32(vget_low_u32(a3.native()), vget_high_u32(a3.native()));
                    return vget_lane_u32(r, 0);
#elif SIMD_USE_ALTIVEC
                    uint32x4 sum = make_zero();
                    sum = vec_sum4s(a.native(), sum.native());
                    sum = add(sum, move4_l<2>(sum));
                    sum = add(sum, move4_l<1>(sum));
                    return extract<0>(sum);
#elif SIMD_USE_MSA
                    uint16<8> s16 = __msa_hadd_u_h(a.native(), a.native());
                    uint32<4> s32 = __msa_hadd_u_w(s16.native(), s16.native());
                    s32 = (uint64<2>)__msa_hadd_u_d(s32.native(), s32.native());
                    s32 = add(s32, move4_l<2>(s32));
                    return extract<0>(s32);
#endif
                }

#if SIMD_USE_AVX2
                static inline uint16_t i_reduce_add(const uint8x32 &a) {
                    uint16x16 sum2 =
                        _mm256_sad_epu8(a.native(), _mm256_setzero_si256()); // results are in 0,2,4,6 elements
                    uint16x8 sum = add(detail::extract128<0>(sum2), detail::extract128<1>(sum2));
                    return extract<0>(sum) + extract<4>(sum);
                }
#endif

#if SIMD_USE_AVX512BW
                inline uint16_t i_reduce_add(const uint8<64> &a) {
                    uint64<8> sum2 = _mm512_sad_epu8(a.native(), _mm512_setzero_si512());
                    return reduce_add(sum2);
                }
#endif

                template <unsigned N> inline uint16_t i_reduce_add(const uint8<N> &a) {
#if SIMD_USE_NULL
                    uint16_t r = 0;
                    for (unsigned j = 0; j < a.vec_length; ++j) {
                        for (unsigned i = 0; i < a.base_length; i++) {
                            r += a.vec(j).el(i);
                        }
                    }
                    return r;
#elif SIMD_USE_AVX512BW
                    uint64<8> sum2 = make_zero();
                    for (unsigned j = 0; j < a.vec_length; ++j) {
                        uint64<8> sum = _mm512_sad_epu8(a.native(), _mm512_setzero_si512());
                        sum2 = add(sum2, sum);
                    }
                    return reduce_add(sum2);
#elif SIMD_USE_AVX2
                    uint16x16 r = make_zero();
                    for (unsigned j = 0; j < a.vec_length; ++j) {
                        uint16x16 sum = _mm256_sad_epu8(a.vec(j).native(), _mm256_setzero_si256());
                        r = add(r, sum);
                    }
                    uint16x8 rl = add(detail::extract128<0>(r), detail::extract128<1>(r));
                    return extract<0>(rl) + extract<4>(rl);
#elif SIMD_USE_SSE2
                    uint16x8 r = make_zero();
                    for (unsigned j = 0; j < a.vec_length; ++j) {
#if SIMD_USE_XOP
                        uint16x8 sum = _mm_haddq_epu8(a.vec(j).native());
#else
                        uint16x8 sum = _mm_sad_epu8(a.vec(j).native(), _mm_setzero_si128());
#endif
                        r = add(r, sum);
                    }
                    return extract<0>(r) + extract<4>(r);
#elif SIMD_USE_NEON
                    uint16x8 r = make_zero();
                    for (unsigned j = 0; j < a.vec_length; ++j) {
                        uint16x8 sum = vpaddlq_u8(a.vec(j).native());
                        r = add(r, sum);
                    }
                    uint32x4 r2 = vpaddlq_u16(r.native());
                    uint64x2 r3 = vpaddlq_u32(r2.native());
                    r2 = r3;
                    uint32x2_t r4 = vadd_u32(vget_low_u32(r2.native()), vget_high_u32(r2.native()));
                    return vget_lane_u32(r4, 0);
#elif SIMD_USE_ALTIVEC
                    uint32x4 sum = make_zero();
                    for (unsigned j = 0; j < a.vec_length; ++j) {
                        sum = vec_sum4s(a.vec(j).native(), sum.native());
                    }
                    sum = add(sum, move4_l<2>(sum));
                    sum = add(sum, move4_l<1>(sum));
                    return extract<0>(sum);
#elif SIMD_USE_MSA
                    uint16<8> r = make_zero();
                    for (unsigned j = 0; j < a.vec_length; ++j) {
                        uint16x8 sum = __msa_hadd_u_h(a.vec(j).native(), a.vec(j).native());
                        r = add(r, sum);
                    }
                    uint32<4> s32 = __msa_hadd_u_w(r.native(), r.native());
                    s32 = (v4u32)__msa_hadd_u_d(s32.native(), s32.native());
                    s32 = add(s32, move4_l<2>(s32));
                    return extract<0>(s32);
#endif
                }

                // -----------------------------------------------------------------------------

                static inline int16_t i_reduce_add(const int8x16 &a) {
#if SIMD_USE_NULL
                    int16_t r = a.el(0);
                    for (unsigned i = 1; i < a.length; i++) {
                        r += a.el(i);
                    }
                    return r;
#elif SIMD_USE_XOP
                    uint16x8 sum = _mm_haddq_epi8(a.native());
                    return extract<0>(sum) + extract<4>(sum);
#elif SIMD_USE_SSE2
                    return i_reduce_add(uint8x16(bit_xor(a, 0x80))) - a.length * 0x80;
#elif SIMD_USE_NEON
                    int16x8 a2 = vpaddlq_s8(a.native());
                    int32x4 a3 = vpaddlq_s16(a2.native());
                    int64x2 a4 = vpaddlq_s32(a3.native());
                    a3 = a4;
                    int32x2_t r = vadd_s32(vget_low_s32(a3.native()), vget_high_s32(a3.native()));
                    return vget_lane_s32(r, 0);
#elif SIMD_USE_ALTIVEC
                    int32x4 sum = make_zero();
                    sum = vec_sum4s(a.native(), sum.native());
                    sum = add(sum, move4_l<2>(sum));
                    sum = add(sum, move4_l<1>(sum));
                    return extract<0>(sum);
#elif SIMD_USE_MSA
                    int16<8> s16 = __msa_hadd_s_h(a.native(), a.native());
                    int32<4> s32 = __msa_hadd_s_w(s16.native(), s16.native());
                    s32 = (v4i32)__msa_hadd_s_d(s32.native(), s32.native());
                    s32 = add(s32, move4_l<2>(s32));
                    return extract<0>(s32);
#endif
                }

#if SIMD_USE_AVX2
                static inline int16_t i_reduce_add(const int8x32 &a) {
                    return i_reduce_add(uint8x32(bit_xor(a, 0x80))) - a.length * 0x80;
                }
#endif

#if SIMD_USE_AVX512BW
                inline uint16_t i_reduce_add(const int8<64> &a) {
                    return i_reduce_add(uint8<64>(bit_xor(a, 0x80))) - a.length * 0x80;
                }
#endif

                template <unsigned N> inline uint16_t i_reduce_add(const int8<N> &a) {
#if SIMD_USE_NULL
                    uint16_t r = 0;
                    for (unsigned j = 0; j < a.vec_length; ++j) {
                        for (unsigned i = 0; i < a.base_length; i++) {
                            r += a.vec(j).el(i);
                        }
                    }
                    return r;
#elif SIMD_USE_AVX512BW || SIMD_USE_AVX2
                    return i_reduce_add(uint8<N>(bit_xor(a, 0x80))) - a.length * 0x80;
#elif SIMD_USE_XOP
                    int16x8 r = make_zero();
                    for (unsigned j = 0; j < a.vec_length; ++j) {
                        int16x8 sum = _mm_haddq_epi8(a.vec(j).native());
                        r = add(r, sum);
                    }
                    return extract<0>(r) + extract<4>(r);
#elif SIMD_USE_SSE2
                    return i_reduce_add(uint8<N>(bit_xor(a, 0x80))) - a.length * 0x80;
#elif SIMD_USE_NEON
                    int16x8 r = make_zero();
                    for (unsigned j = 0; j < a.vec_length; ++j) {
                        int16x8 sum = vpaddlq_s8(a.vec(j).native());
                        r = add(r, sum);
                    }
                    int32x4 r2 = vpaddlq_s16(r.native());
                    int64x2 r3 = vpaddlq_s32(r2.native());
                    r2 = r3;
                    int32x2_t r4 = vadd_s32(vget_low_s32(r2.native()), vget_high_s32(r2.native()));
                    return vget_lane_s32(r4, 0);
#elif SIMD_USE_ALTIVEC
                    int32x4 sum = make_zero();
                    for (unsigned j = 0; j < a.vec_length; ++j) {
                        sum = vec_sum4s(a.vec(j).native(), sum.native());
                    }
                    sum = add(sum, move4_l<2>(sum));
                    sum = add(sum, move4_l<1>(sum));
                    return extract<0>(sum);
#elif SIMD_USE_MSA
                    int16<8> r = make_zero();
                    for (unsigned j = 0; j < a.vec_length; ++j) {
                        int16x8 sum = __msa_hadd_s_h(a.vec(j).native(), a.vec(j).native());
                        r = add(r, sum);
                    }
                    int32<4> s32 = __msa_hadd_s_w(r.native(), r.native());
                    s32 = (v4i32)__msa_hadd_s_d(s32.native(), s32.native());
                    s32 = add(s32, move4_l<2>(s32));
                    return extract<0>(s32);
#endif
                }

                // -----------------------------------------------------------------------------

                static inline uint32_t i_reduce_add(const uint16x8 &a) {
#if SIMD_USE_NULL
                    uint32_t r = a.el(0);
                    for (unsigned i = 1; i < a.length; i++) {
                        r += a.el(i);
                    }
                    return r;
#elif SIMD_USE_XOP
                    uint32x4 sum = _mm_haddq_epu16(a.native()); // sum in the 0 and 2 elements
                    sum = add(sum, move4_l<2>(sum));
                    return extract<0>(sum);
#elif SIMD_USE_SSE2
                    uint16x8 ones = make_uint(1);
                    uint16x8 ca = bit_xor(a, 0x8000);
                    uint32x4 sum = _mm_madd_epi16(ca.native(), ones.native());
                    // phadd is slower option on intel processors
                    sum = add(sum, move4_l<2>(sum));
                    sum = add(sum, move4_l<1>(sum));
                    return extract<0>(sum) + 0x8000 * a.length;
#elif SIMD_USE_NEON
                    uint32x4 a2 = vpaddlq_u16(a.native());
                    uint64x2 a3 = vpaddlq_u32(a2.native());
                    a2 = a3;
                    uint32x2_t r = vadd_u32(vget_low_u32(a2.native()), vget_high_u32(a2.native()));
                    return vget_lane_u32(r, 0);
#elif SIMD_USE_ALTIVEC
                    int32x4 sum = make_zero();
                    int16x8 ca = bit_xor(a, 0x8000);
                    sum = vec_sum4s(ca.native(), sum.native());
                    sum = add(sum, move4_l<2>(sum));
                    sum = add(sum, move4_l<1>(sum));
                    return extract<0>(sum) + 0x8000 * a.length;
#elif SIMD_USE_MSA
                    uint32<4> s32 = __msa_hadd_u_w(a.native(), a.native());
                    s32 = (v4u32)__msa_hadd_u_d(s32.native(), s32.native());
                    s32 = add(s32, move4_l<2>(s32));
                    return extract<0>(s32);
#endif
                }

#if SIMD_USE_AVX2
                static inline uint32_t i_reduce_add(const uint16x16 &a) {
                    uint16x16 ones = make_uint(1);
                    uint16x16 ca = bit_xor(a, 0x8000);
                    uint32x8 sum = _mm256_madd_epi16(ca.native(), ones.native());
                    return reduce_add(sum) + 0x8000 * a.length;
                }
#endif

#if SIMD_USE_AVX512BW
                inline uint32_t i_reduce_add(const uint16<32> &a) {
                    uint16<32> ones = make_uint(1);
                    uint16<32> ca = bit_xor(a, 0x8000);
                    uint32<16> sum = _mm512_madd_epi16(ca.native(), ones.native());
                    return reduce_add(sum) + 0x8000 * a.length;
                }
#endif

                template <unsigned N> inline uint32_t i_reduce_add(const uint16<N> &a) {
#if SIMD_USE_NULL
                    uint32_t r = 0;
                    for (unsigned j = 0; j < a.vec_length; ++j) {
                        for (unsigned i = 0; i < a.base_length; i++) {
                            r += a.vec(j).el(i);
                        }
                    }
                    return r;
#elif SIMD_USE_AVX512BW
                    uint32<16> sum = make_zero();
                    uint16<32> ones = make_uint(1);
                    for (unsigned j = 0; j < a.vec_length; ++j) {
                        uint16<32> ca = bit_xor(a.vec(j), 0x8000);
                        uint32<16> isum = _mm512_madd_epi16(ca.native(), ones.native());
                        sum = add(sum, isum);
                    }
                    return reduce_add(sum) + 0x8000 * a.length;
#elif SIMD_USE_AVX2
                    uint32x8 sum = make_zero();
                    uint16x16 ones = make_uint(1);
                    for (unsigned j = 0; j < a.vec_length; ++j) {
                        uint16x16 ca = bit_xor(a.vec(j), 0x8000);
                        uint32x8 isum = _mm256_madd_epi16(ca.native(), ones.native());
                        sum = add(sum, isum);
                    }
                    return reduce_add(sum) + 0x8000 * a.length;
#elif SIMD_USE_XOP
                    uint32x4 sum = make_zero();
                    for (unsigned j = 0; j < a.vec_length; ++j) {
                        uint32x4 isum = _mm_haddq_epu16(a.vec(j).native());
                        sum = add(sum, isum);
                    }
                    sum = add(sum, move4_l<2>(sum));
                    return extract<0>(sum);
#elif SIMD_USE_SSE2
                    uint32x4 sum = make_zero();
                    uint16x8 ones = make_uint(1);
                    for (unsigned j = 0; j < a.vec_length; ++j) {
                        uint16x8 ca = bit_xor(a.vec(j), 0x8000);
                        uint32x4 isum = _mm_madd_epi16(ca.native(), ones.native());
                        sum = add(sum, isum);
                    }
                    sum = add(sum, move4_l<2>(sum));
                    sum = add(sum, move4_l<1>(sum));
                    return extract<0>(sum) + 0x8000 * a.length;
#elif SIMD_USE_NEON
                    uint32x4 sum = make_zero();
                    for (unsigned j = 0; j < a.vec_length; ++j) {
                        uint32x4 isum = vpaddlq_u16(a.vec(j).native());
                        sum = add(sum, isum);
                    }
                    uint64x2 sum2 = vpaddlq_u32(sum.native());
                    sum = sum2;
                    uint32x2_t sum3 = vadd_u32(vget_low_u32(sum.native()), vget_high_u32(sum.native()));
                    return vget_lane_u32(sum3, 0);
#elif SIMD_USE_ALTIVEC
                    int32x4 sum = make_zero();
                    for (unsigned j = 0; j < a.vec_length; ++j) {
                        int16x8 ca = bit_xor(a.vec(j), 0x8000);
                        sum = vec_sum4s(ca.native(), sum.native());
                    }
                    sum = add(sum, move4_l<2>(sum));
                    sum = add(sum, move4_l<1>(sum));
                    return extract<0>(sum) + 0x8000 * a.length;
#elif SIMD_USE_MSA
                    uint32<4> r = make_zero();
                    for (unsigned j = 0; j < a.vec_length; ++j) {
                        uint32<4> sum = __msa_hadd_u_w(a.vec(j).native(), a.vec(j).native());
                        r = add(r, sum);
                    }
                    r = (uint64<2>)__msa_hadd_u_d(r.native(), r.native());
                    r = add(r, move4_l<2>(r));
                    return extract<0>(r);
#endif
                }

                // -----------------------------------------------------------------------------

                static inline int32_t i_reduce_add(const int16x8 &a) {
#if SIMD_USE_NULL
                    int32_t r = a.el(0);
                    for (unsigned i = 1; i < a.length; i++) {
                        r += a.el(i);
                    }
                    return r;
#elif SIMD_USE_XOP
                    int32x4 sum = _mm_haddq_epi16(a.native()); // sum in the 0 and 2 elements
                    sum = add(sum, move4_l<2>(sum));
                    return extract<0>(sum);
#elif SIMD_USE_SSE2
                    int16x8 ones = make_uint(1);
                    int32x4 sum = _mm_madd_epi16(a.native(), ones.native());
                    return reduce_add(sum);
#elif SIMD_USE_NEON
                    int32x4 a2 = vpaddlq_s16(a.native());
                    int64x2 a3 = vpaddlq_s32(a2.native());
                    a2 = a3;
                    int32x2_t r = vadd_s32(vget_low_s32(a2.native()), vget_high_s32(a2.native()));
                    return vget_lane_s32(r, 0);
#elif SIMD_USE_ALTIVEC
                    int32x4 sum = make_zero();
                    sum = vec_sum4s(a.native(), sum.native());
                    sum = add(sum, move4_l<2>(sum));
                    sum = add(sum, move4_l<1>(sum));
                    return extract<0>(sum);
#elif SIMD_USE_MSA
                    int32<4> s32 = __msa_hadd_s_w(a.native(), a.native());
                    s32 = (int64<2>)__msa_hadd_s_d(s32.native(), s32.native());
                    s32 = add(s32, move4_l<2>(s32));
                    return extract<0>(s32);
#endif
                }

#if SIMD_USE_AVX2
                static inline int32_t i_reduce_add(const int16x16 &a) {
                    int16x16 ones = make_uint(1);
                    int32x8 sum = _mm256_madd_epi16(a.native(), ones.native());
                    return reduce_add(sum);
                }
#endif

#if SIMD_USE_AVX512BW
                inline int32_t i_reduce_add(const int16<32> &a) {
                    int16<32> ones = make_uint(1);
                    int32<16> sum = _mm512_madd_epi16(a.native(), ones.native());
                    return reduce_add(sum);
                }
#endif

                template <unsigned N> inline int32_t i_reduce_add(const int16<N> &a) {
#if SIMD_USE_NULL
                    int32_t r = 0;
                    for (unsigned j = 0; j < a.vec_length; ++j) {
                        for (unsigned i = 0; i < a.base_length; i++) {
                            r += a.vec(j).el(i);
                        }
                    }
                    return r;
#elif SIMD_USE_AVX512BW
                    int32<16> sum = make_zero();
                    int16<32> ones = make_int(1);
                    for (unsigned j = 0; j < a.vec_length; ++j) {
                        int32<16> isum = _mm512_madd_epi16(a.vec(j).native(), ones.native());
                        sum = add(sum, isum);
                    }
                    return reduce_add(sum);
#elif SIMD_USE_AVX2
                    int32x8 sum = make_zero();
                    int16x16 ones = make_int(1);
                    for (unsigned j = 0; j < a.vec_length; ++j) {
                        int32x8 isum = _mm256_madd_epi16(a.vec(j).native(), ones.native());
                        sum = add(sum, isum);
                    }
                    return reduce_add(sum);
#elif SIMD_USE_XOP
                    int32x4 sum = make_zero();
                    for (unsigned j = 0; j < a.vec_length; ++j) {
                        int32x4 isum = _mm_haddq_epi16(a.vec(j).native());
                        sum = add(sum, isum);
                    }
                    // _mm_haddq_epi16 computes 64-bit results.
                    // 1 and 3 32-bit elements may be nonzero
                    sum = add(sum, move4_l<2>(sum));
                    return extract<0>(sum);
#elif SIMD_USE_SSE2
                    int32x4 sum = make_zero();
                    int16x8 ones = make_int(1);
                    for (unsigned j = 0; j < a.vec_length; ++j) {
                        int32x4 isum = _mm_madd_epi16(a.vec(j).native(), ones.native());
                        sum = add(sum, isum);
                    }
                    return reduce_add(sum);
#elif SIMD_USE_NEON
                    int32x4 sum = make_zero();
                    for (unsigned j = 0; j < a.vec_length; ++j) {
                        int32x4 isum = vpaddlq_s16(a.vec(j).native());
                        sum = add(sum, isum);
                    }
                    return reduce_add(sum);
#elif SIMD_USE_ALTIVEC
                    int32x4 sum = make_zero();
                    for (unsigned j = 0; j < a.vec_length; ++j) {
                        sum = vec_sum4s(a.vec(j).native(), sum.native());
                    }
                    return reduce_add(sum);
#elif SIMD_USE_MSA
                    int32<4> r = make_zero();
                    for (unsigned j = 0; j < a.vec_length; ++j) {
                        int32<4> sum = __msa_hadd_s_w(a.vec(j).native(), a.vec(j).native());
                        r = add(r, sum);
                    }
                    r = (int64<2>)__msa_hadd_s_d(r.native(), r.native());
                    r = add(r, move4_l<2>(r));
                    return extract<0>(r);
#endif
                }

                // -----------------------------------------------------------------------------

                static inline uint32_t i_reduce_add(const uint32x4 &a) {
#if SIMD_USE_NULL
                    uint32_t r = a.el(0);
                    for (unsigned i = 1; i < a.length; i++) {
                        r += a.el(i);
                    }
                    return r;
#elif SIMD_USE_MSA
                    uint32x4 sum = a;
                    sum = (uint64<2>)__msa_hadd_u_d(sum.native(), sum.native());
                    sum = add(sum, move4_l<2>(sum));
                    return extract<0>(sum);
#else
                    uint32x4 sum = a;
                    sum = add(sum, move4_l<2>(sum));
                    sum = add(sum, move4_l<1>(sum));
                    return extract<0>(sum);
#endif
                }

#if SIMD_USE_AVX2
                static inline uint32_t i_reduce_add(const uint32x8 &a) {
                    uint32x4 sum = add(detail::extract128<0>(a), detail::extract128<1>(a));
                    sum = add(sum, move4_l<2>(sum));
                    sum = add(sum, move4_l<1>(sum));
                    return extract<0>(sum);
                }
#endif

#if SIMD_USE_AVX512F
                static inline uint32_t i_reduce_add(const uint32<16> &a) {
                    return i_reduce_add(add(extract256<0>(a), extract256<1>(a)));
                }
#endif

                template <unsigned N> inline uint32_t i_reduce_add(const uint32<N> &a) {
#if SIMD_USE_NULL
                    uint32_t r = 0;
                    for (unsigned j = 0; j < a.vec_length; ++j) {
                        for (unsigned i = 0; i < a.base_length; i++) {
                            r += a.vec(j).el(i);
                        }
                    }
                    return r;
#else
                    uint32v sum = make_zero();
                    for (unsigned j = 0; j < a.vec_length; ++j) {
                        sum = add(sum, a.vec(j));
                    }
                    return i_reduce_add(sum);
#endif
                }

                // -----------------------------------------------------------------------------

                static inline uint64_t i_reduce_add(const uint64x2 &a) {
#if SIMD_USE_NULL
                    uint64_t r = a.el(0);
                    for (unsigned i = 1; i < a.length; i++) {
                        r += a.el(i);
                    }
                    return r;
#elif SIMD_USE_SSE2
                    uint64x2 sum = a;
                    sum = add(sum, move2_l<1>(sum));
                    return extract<0>(sum);
#elif SIMD_USE_NEON
                    uint64x1_t r = vadd_u64(vget_low_u64(a.native()), vget_high_u64(a.native()));
                    return vget_lane_u64(r, 0);
#elif SIMD_USE_ALTIVEC || SIMD_USE_MSA
                    return extract<0>(a) + extract<1>(a);
#endif
                }

#if SIMD_USE_AVX2
                static inline uint64_t i_reduce_add(const uint64x4 &a) {
                    uint64x2 sum = add(detail::extract128<0>(a), detail::extract128<1>(a));
                    sum = add(sum, move2_l<1>(sum));
                    return extract<0>(sum);
                }
#endif

#if SIMD_USE_AVX512F
                static inline uint64_t i_reduce_add(const uint64<8> &a) {
                    return i_reduce_add(add(extract256<0>(a), extract256<1>(a)));
                }
#endif

                template <unsigned N> inline uint64_t i_reduce_add(const uint64<N> &a) {
#if SIMD_USE_NULL || (SIMD_USE_ALTIVEC && !SIMD_USE_VSX_207)
                    uint64_t r = 0;
                    for (unsigned j = 0; j < a.vec_length; ++j) {
                        for (unsigned i = 0; i < a.base_length; i++) {
                            r += a.vec(j).el(i);
                        }
                    }
                    return r;
#else
                    uint64v sum = make_zero();
                    for (unsigned j = 0; j < a.vec_length; ++j) {
                        sum = add(sum, a.vec(j));
                    }
                    return i_reduce_add(sum);
#endif
                }

                // -----------------------------------------------------------------------------


            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
