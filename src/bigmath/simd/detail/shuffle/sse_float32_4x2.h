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

#ifndef SIMD_DETAIL_PERMUTE_SSE_FLOAT32_4x2_H
#define SIMD_DETAIL_PERMUTE_SSE_FLOAT32_4x2_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/setup_arch.h>
#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/shuffle/shuffle_mask.h>

#if SIMD_USE_SSE2

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace sse_shuffle4x2_float32 {

                /*  The code below implements generalized permutations for 2 elements sets
                    within float32 vectors.
                */

                template <unsigned s0, unsigned s1, unsigned s2, unsigned s3> struct impl_selector {

                    // 0 1 2 3
                    // 4 5 6 7
                    static const bool is1_zip_lo1 = (s0 == 0 && s1 == 4 && s2 == 1 && s3 == 5);
                    static const bool is2_zip_lo2 = (s0 == 4 && s1 == 0 && s2 == 5 && s3 == 1);
                    static const bool is3_zip_hi1 = (s0 == 2 && s1 == 6 && s2 == 3 && s3 == 7);
                    static const bool is4_zip_hi2 = (s0 == 6 && s1 == 2 && s2 == 7 && s3 == 3);
#if SIMD_USE_SSE4_1
                    static const bool is5_blend =
                        (s0 == 0 || s0 == 4) && (s1 == 1 || s1 == 5) && (s2 == 2 || s2 == 6) && (s3 == 3 || s3 == 7);
#else
                    static const bool is5_blend = false;
#endif
                    static const bool is6_shuffle1 = s0 < 4 && s1 < 4 && s2 >= 4 && s3 >= 4;
                    static const bool is7_shuffle2 = s0 >= 4 && s1 >= 4 && s2 < 4 && s3 < 4;
#if SIMD_USE_SSE4_1
                    static const bool is8_lobl_shuffle1 = s2 >= 4 && s3 >= 4 && s0 != s1;
                    static const bool is9_lobl_shuffle2 = s2 < 4 && s3 < 4 && s0 != s1;
#else
                    static const bool is8_lobl_shuffle1 = false;
                    static const bool is9_lobl_shuffle2 = false;
#endif
                    static const bool is10_losh_shuffle1 = s2 >= 4 && s3 >= 4;
                    static const bool is11_losh_shuffle2 = s2 < 4 && s3 < 4;
#if SIMD_USE_SSE4_1
                    static const bool is12_hibl_shuffle1 = s0 >= 4 && s1 >= 4 && s2 != s3;
                    static const bool is13_hibl_shuffle2 = s0 < 4 && s1 < 4 && s2 != s3;
#else
                    static const bool is12_hibl_shuffle1 = false;
                    static const bool is13_hibl_shuffle2 = false;
#endif
                    static const bool is14_hish_shuffle1 = s0 >= 4 && s1 >= 4;
                    static const bool is15_hish_shuffle2 = s0 < 4 && s1 < 4;

                    static const int impl =
                        is1_zip_lo1 ? 1 :
                                      is2_zip_lo2 ?
                                      2 :
                                      is3_zip_hi1 ?
                                      3 :
                                      is4_zip_hi2 ?
                                      4 :
                                      is5_blend ?
                                      5 :
                                      is6_shuffle1 ?
                                      6 :
                                      is7_shuffle2 ?
                                      7 :
                                      is8_lobl_shuffle1 ?
                                      8 :
                                      is9_lobl_shuffle2 ?
                                      9 :
                                      is10_losh_shuffle1 ?
                                      10 :
                                      is11_losh_shuffle2 ?
                                      11 :
                                      is12_hibl_shuffle1 ?
                                      12 :
                                      is13_hibl_shuffle2 ? 13 : is14_hish_shuffle1 ? 14 : is15_hish_shuffle2 ? 15 : 16;
                };

                template <unsigned N> struct shuffle_impl {};

                // zip_lo1
                template <> struct shuffle_impl<1> {
                    template <unsigned, unsigned, unsigned, unsigned>
                    static inline float32<4> run(const float32<4> &a, const float32<4> &b) {
                        return _mm_unpacklo_ps(a.native(), b.native());
                    }
#if SIMD_USE_AVX
                    template <unsigned, unsigned, unsigned, unsigned>
                    static inline float32<8> run(const float32<8> &a, const float32<8> &b) {
                        return _mm256_unpacklo_ps(a.native(), b.native());
                    }
#endif
#if SIMD_USE_AVX512F
                    template <unsigned, unsigned, unsigned, unsigned>
                    static inline float32<16> run(const float32<16> &a, const float32<16> &b) {
                        return _mm512_unpacklo_ps(a.native(), b.native());
                    }
#endif
                };

                // zip_lo2
                template <> struct shuffle_impl<2> {
                    template <unsigned, unsigned, unsigned, unsigned, unsigned N>
                    static inline float32<N> run(const float32<N> &a, const float32<N> &b) {
                        return shuffle_impl<1>::run<0, 0, 0, 0>(b, a);
                    }
                };

                // zip_hi1
                template <> struct shuffle_impl<3> {
                    template <unsigned, unsigned, unsigned, unsigned>
                    static inline float32<4> run(const float32<4> &a, const float32<4> &b) {
                        return _mm_unpackhi_ps(a.native(), b.native());
                    }
#if SIMD_USE_AVX
                    template <unsigned, unsigned, unsigned, unsigned>
                    static inline float32<8> run(const float32<8> &a, const float32<8> &b) {
                        return _mm256_unpackhi_ps(a.native(), b.native());
                    }
#endif
#if SIMD_USE_AVX512F
                    template <unsigned, unsigned, unsigned, unsigned>
                    static inline float32<16> run(const float32<16> &a, const float32<16> &b) {
                        return _mm512_unpackhi_ps(a.native(), b.native());
                    }
#endif
                };

                // zip_hi2
                template <> struct shuffle_impl<4> {
                    template <unsigned, unsigned, unsigned, unsigned, unsigned N>
                    static inline float32<N> run(const float32<N> &a, const float32<N> &b) {
                        return shuffle_impl<3>::run<0, 0, 0, 0>(b, a);
                    }
                };

// is5_blend
#if SIMD_USE_SSE4_1
                template <> struct shuffle_impl<5> {
                    template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                    static inline float32<4> run(const float32<4> &a, const float32<4> &b) {
                        return _mm_blend_ps(a.native(),
                                            b.native(),
                                            SIMD_SHUFFLE_MASK_4x2(s0 / 4, s1 / 4, s2 / 4, s3 / 4));
                    }
#if SIMD_USE_AVX
                    template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                    static inline float32<8> run(const float32<8> &a, const float32<8> &b) {
                        return _mm256_blend_ps(a.native(),
                                               b.native(),
                                               SIMD_SHUFFLE_MASK_4x2_2(s0 / 4, s1 / 4, s2 / 4, s3 / 4));
                    }
#endif
#if SIMD_USE_AVX512F
                    template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                    static inline float32<16> run(const float32<16> &a, const float32<16> &b) {
                        return _mm512_mask_blend_ps(SIMD_SHUFFLE_MASK_4x2_4(s0 / 4, s1 / 4, s2 / 4, s3 / 4),
                                                    a.native(),
                                                    b.native());
                    }
#endif
                };
#endif

                // is6_shuffle1
                template <> struct shuffle_impl<6> {
                    template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                    static inline float32<4> run(const float32<4> &a, const float32<4> &b) {
                        return _mm_shuffle_ps(a.native(), b.native(), _MM_SHUFFLE(s3 - 4, s2 - 4, s1, s0));
                    }
#if SIMD_USE_AVX
                    template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                    static inline float32<8> run(const float32<8> &a, const float32<8> &b) {
                        return _mm256_shuffle_ps(a.native(), b.native(), _MM_SHUFFLE(s3 - 4, s2 - 4, s1, s0));
                    }
#endif
#if SIMD_USE_AVX512F
                    template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                    static inline float32<16> run(const float32<16> &a, const float32<16> &b) {
                        return _mm512_shuffle_ps(a.native(), b.native(), _MM_SHUFFLE(s3 - 4, s2 - 4, s1, s0));
                    }
#endif
                };

                // is7_shuffle2
                template <> struct shuffle_impl<7> {
                    template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                    static inline float32<4> run(const float32<4> &a, const float32<4> &b) {
                        return _mm_shuffle_ps(b.native(), a.native(), _MM_SHUFFLE(s3, s2, s1 - 4, s0 - 4));
                    }
#if SIMD_USE_AVX
                    template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                    static inline float32<8> run(const float32<8> &a, const float32<8> &b) {
                        return _mm256_shuffle_ps(b.native(), a.native(), _MM_SHUFFLE(s3, s2, s1 - 4, s0 - 4));
                    }
#endif
#if SIMD_USE_AVX512F
                    template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                    static inline float32<16> run(const float32<16> &a, const float32<16> &b) {
                        return _mm512_shuffle_ps(b.native(), a.native(), _MM_SHUFFLE(s3, s2, s1 - 4, s0 - 4));
                    }
#endif
                };

// selects those elements from b that have positions matching either s0 or s1
#if SIMD_USE_SSE4_1
                template <unsigned s0, unsigned s1>
                inline float32<4> select2_hi(const float32<4> &a, const float32<4> &b) {
                    const unsigned mask = (s0 == 4 || s1 == 4 ? 1 : 0) | (s0 == 5 || s1 == 5 ? 2 : 0)
                                          | (s0 == 6 || s1 == 6 ? 4 : 0) | (s0 == 7 || s1 == 7 ? 8 : 0);
                    return _mm_blend_ps(a.native(), b.native(), mask);
                }
#endif
#if SIMD_USE_AVX
                template <unsigned s0, unsigned s1>
                inline float32<8> select2_hi(const float32<8> &a, const float32<8> &b) {
                    const unsigned mask = (s0 == 4 || s1 == 4 ? 1 : 0) | (s0 == 5 || s1 == 5 ? 2 : 0)
                                          | (s0 == 6 || s1 == 6 ? 4 : 0) | (s0 == 7 || s1 == 7 ? 8 : 0);
                    return _mm256_blend_ps(a.native(), b.native(), mask | mask << 4);
                }
#endif
#if SIMD_USE_AVX512F
                template <unsigned s0, unsigned s1>
                inline float32<16> select2_hi(const float32<16> &a, const float32<16> &b) {
                    const unsigned mask = (s0 == 4 || s1 == 4 ? 1 : 0) | (s0 == 5 || s1 == 5 ? 2 : 0)
                                          | (s0 == 6 || s1 == 6 ? 4 : 0) | (s0 == 7 || s1 == 7 ? 8 : 0);
                    const unsigned mask2 = mask | mask << 4 | mask << 8 | mask << 12;
                    return _mm512_mask_blend_ps(mask2, a.native(), b.native());
                }
#endif

                // is8_lobl_shuffle1 = s2 >= 4 && s3 >= 4 && s0 != s1;
                template <> struct shuffle_impl<8> {
#if SIMD_USE_SSE4_1
                    template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                    static inline float32<4> run(const float32<4> &a, const float32<4> &b) {
                        __m128 ab1 = select2_hi<s0, s1>(a, b).native();
                        return _mm_shuffle_ps(ab1, b.native(), _MM_SHUFFLE(s3 - 4, s2 - 4, s1 % 4, s0 % 4));
                    }
#endif
#if SIMD_USE_AVX
                    template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                    static inline float32<8> run(const float32<8> &a, const float32<8> &b) {
                        __m256 ab1 = select2_hi<s0, s1>(a, b).native();
                        return _mm256_shuffle_ps(ab1, b.native(), _MM_SHUFFLE(s3 - 4, s2 - 4, s1 % 4, s0 % 4));
                    }
#endif
#if SIMD_USE_AVX512F
                    template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                    static inline float32<16> run(const float32<16> &a, const float32<16> &b) {
                        __m512 ab1 = select2_hi<s0, s1>(a, b).native();
                        return _mm512_shuffle_ps(ab1, b.native(), _MM_SHUFFLE(s3 - 4, s2 - 4, s1 % 4, s0 % 4));
                    }
#endif
                };

                // is9_lobl_shuffle2 = s2 <  4 && s3 <  4 && s0 != s1;
                template <> struct shuffle_impl<9> {
#if SIMD_USE_SSE4_1
                    template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                    static inline float32<4> run(const float32<4> &a, const float32<4> &b) {
                        __m128 ab1 = select2_hi<s0, s1>(a, b).native();
                        return _mm_shuffle_ps(ab1, a.native(), _MM_SHUFFLE(s3, s2, s1 % 4, s0 % 4));
                    }
#endif
#if SIMD_USE_AVX
                    template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                    static inline float32<8> run(const float32<8> &a, const float32<8> &b) {
                        __m256 ab1 = select2_hi<s0, s1>(a, b).native();
                        return _mm256_shuffle_ps(ab1, a.native(), _MM_SHUFFLE(s3, s2, s1 % 4, s0 % 4));
                    }
#endif
#if SIMD_USE_AVX512F
                    template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                    static inline float32<16> run(const float32<16> &a, const float32<16> &b) {
                        __m512 ab1 = select2_hi<s0, s1>(a, b).native();
                        return _mm512_shuffle_ps(ab1, a.native(), _MM_SHUFFLE(s3, s2, s1 % 4, s0 % 4));
                    }
#endif
                };

                // is10_losh_shuffle1 = s2 >= 4 && s3 >= 4;
                template <> struct shuffle_impl<10> {
                    template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                    static inline float32<4> run(const float32<4> &a, const float32<4> &b) {
                        __m128 ab1 =
                            _mm_shuffle_ps(a.native(), b.native(), _MM_SHUFFLE(s1 % 4, s0 % 4, s1 % 4, s0 % 4));
                        return _mm_shuffle_ps(ab1,
                                              b.native(),
                                              _MM_SHUFFLE(s3 - 4, s2 - 4, s1 / 4 ? 3 : 1, s0 / 4 ? 2 : 0));
                    }
#if SIMD_USE_AVX
                    template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                    static inline float32<8> run(const float32<8> &a, const float32<8> &b) {
                        __m256 ab1 =
                            _mm256_shuffle_ps(a.native(), b.native(), _MM_SHUFFLE(s1 % 4, s0 % 4, s1 % 4, s0 % 4));
                        return _mm256_shuffle_ps(ab1,
                                                 b.native(),
                                                 _MM_SHUFFLE(s3 - 4, s2 - 4, s1 / 4 ? 3 : 1, s0 / 4 ? 2 : 0));
                    }
#endif
#if SIMD_USE_AVX512F
                    template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                    static inline float32<16> run(const float32<16> &a, const float32<16> &b) {
                        __m512 ab1 =
                            _mm512_shuffle_ps(a.native(), b.native(), _MM_SHUFFLE(s1 % 4, s0 % 4, s1 % 4, s0 % 4));
                        return _mm512_shuffle_ps(ab1,
                                                 b.native(),
                                                 _MM_SHUFFLE(s3 - 4, s2 - 4, s1 / 4 ? 3 : 1, s0 / 4 ? 2 : 0));
                    }
#endif
                };

                // is11_losh_shuffle2 = s2 <  4 && s3 <  4;
                template <> struct shuffle_impl<11> {
                    template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                    static inline float32<4> run(const float32<4> &a, const float32<4> &b) {
                        __m128 ab1 =
                            _mm_shuffle_ps(a.native(), b.native(), _MM_SHUFFLE(s1 % 4, s0 % 4, s1 % 4, s0 % 4));
                        return _mm_shuffle_ps(ab1, a.native(), _MM_SHUFFLE(s3, s2, s1 / 4 ? 3 : 1, s0 / 4 ? 2 : 0));
                    }
#if SIMD_USE_AVX
                    template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                    static inline float32<8> run(const float32<8> &a, const float32<8> &b) {
                        __m256 ab1 =
                            _mm256_shuffle_ps(a.native(), b.native(), _MM_SHUFFLE(s1 % 4, s0 % 4, s1 % 4, s0 % 4));
                        return _mm256_shuffle_ps(ab1, a.native(), _MM_SHUFFLE(s3, s2, s1 / 4 ? 3 : 1, s0 / 4 ? 2 : 0));
                    }
#endif
#if SIMD_USE_AVX512F
                    template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                    static inline float32<16> run(const float32<16> &a, const float32<16> &b) {
                        __m512 ab1 =
                            _mm512_shuffle_ps(a.native(), b.native(), _MM_SHUFFLE(s1 % 4, s0 % 4, s1 % 4, s0 % 4));
                        return _mm512_shuffle_ps(ab1, a.native(), _MM_SHUFFLE(s3, s2, s1 / 4 ? 3 : 1, s0 / 4 ? 2 : 0));
                    }
#endif
                };


                // is12_hibl_shuffle1 = s0 >= 4 && s1 >= 4 && s2 != s3;
                template <> struct shuffle_impl<12> {
#if SIMD_USE_SSE4_1
                    template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                    static inline float32<4> run(const float32<4> &a, const float32<4> &b) {
                        __m128 ab2 = select2_hi<s2, s3>(a, b).native();
                        return _mm_shuffle_ps(b.native(), ab2, _MM_SHUFFLE(s3 % 4, s2 % 4, s1 - 4, s0 - 4));
                    }
#endif
#if SIMD_USE_AVX
                    template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                    static inline float32<8> run(const float32<8> &a, const float32<8> &b) {
                        __m256 ab2 = select2_hi<s2, s3>(a, b).native();
                        return _mm256_shuffle_ps(b.native(), ab2, _MM_SHUFFLE(s3 % 4, s2 % 4, s1 - 4, s0 - 4));
                    }
#endif
#if SIMD_USE_AVX512F
                    template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                    static inline float32<16> run(const float32<16> &a, const float32<16> &b) {
                        __m512 ab2 = select2_hi<s2, s3>(a, b).native();
                        return _mm512_shuffle_ps(b.native(), ab2, _MM_SHUFFLE(s3 % 4, s2 % 4, s1 - 4, s0 - 4));
                    }
#endif
                };

                // is13_hibl_shuffle2 = s0 <  4 && s1 <  4 && s2 != s3;
                template <> struct shuffle_impl<13> {
#if SIMD_USE_SSE4_1
                    template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                    static inline float32<4> run(const float32<4> &a, const float32<4> &b) {
                        __m128 ab2 = select2_hi<s2, s3>(a, b).native();
                        return _mm_shuffle_ps(a.native(), ab2, _MM_SHUFFLE(s3 % 4, s2 % 4, s1, s0));
                    }
#endif
#if SIMD_USE_AVX
                    template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                    static inline float32<8> run(const float32<8> &a, const float32<8> &b) {
                        __m256 ab2 = select2_hi<s2, s3>(a, b).native();
                        return _mm256_shuffle_ps(a.native(), ab2, _MM_SHUFFLE(s3 % 4, s2 % 4, s1, s0));
                    }
#endif
#if SIMD_USE_AVX512F
                    template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                    static inline float32<16> run(const float32<16> &a, const float32<16> &b) {
                        __m512 ab2 = select2_hi<s2, s3>(a, b).native();
                        return _mm512_shuffle_ps(a.native(), ab2, _MM_SHUFFLE(s3 % 4, s2 % 4, s1, s0));
                    }
#endif
                };

                // is14_hish_shuffle1 = s0 >= 4 && s1 >= 4;
                template <> struct shuffle_impl<14> {
                    template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                    static inline float32<4> run(const float32<4> &a, const float32<4> &b) {
                        __m128 ab2 =
                            _mm_shuffle_ps(a.native(), b.native(), _MM_SHUFFLE(s3 % 4, s2 % 4, s3 % 4, s2 % 4));
                        return _mm_shuffle_ps(b.native(),
                                              ab2,
                                              _MM_SHUFFLE(s3 / 4 ? 3 : 1, s2 / 4 ? 2 : 0, s1 - 4, s0 - 4));
                    }
#if SIMD_USE_AVX
                    template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                    static inline float32<8> run(const float32<8> &a, const float32<8> &b) {
                        __m256 ab2 =
                            _mm256_shuffle_ps(a.native(), b.native(), _MM_SHUFFLE(s3 % 4, s2 % 4, s3 % 4, s2 % 4));
                        return _mm256_shuffle_ps(b.native(),
                                                 ab2,
                                                 _MM_SHUFFLE(s3 / 4 ? 3 : 1, s2 / 4 ? 2 : 0, s1 - 4, s0 - 4));
                    }
#endif
#if SIMD_USE_AVX512F
                    template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                    static inline float32<16> run(const float32<16> &a, const float32<16> &b) {
                        __m512 ab2 =
                            _mm512_shuffle_ps(a.native(), b.native(), _MM_SHUFFLE(s3 % 4, s2 % 4, s3 % 4, s2 % 4));
                        return _mm512_shuffle_ps(b.native(),
                                                 ab2,
                                                 _MM_SHUFFLE(s3 / 4 ? 3 : 1, s2 / 4 ? 2 : 0, s1 - 4, s0 - 4));
                    }
#endif
                };

                // is15_hish_shuffle2: s0 <  4 && s1 <  4
                template <> struct shuffle_impl<15> {
                    template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                    static inline float32<4> run(const float32<4> &a, const float32<4> &b) {
                        __m128 ab2 =
                            _mm_shuffle_ps(a.native(), b.native(), _MM_SHUFFLE(s3 % 4, s2 % 4, s3 % 4, s2 % 4));
                        return _mm_shuffle_ps(a.native(), ab2, _MM_SHUFFLE(s3 / 4 ? 3 : 1, s2 / 4 ? 2 : 0, s1, s0));
                    }
#if SIMD_USE_AVX
                    template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                    static inline float32<8> run(const float32<8> &a, const float32<8> &b) {
                        __m256 ab2 =
                            _mm256_shuffle_ps(a.native(), b.native(), _MM_SHUFFLE(s3 % 4, s2 % 4, s3 % 4, s2 % 4));
                        return _mm256_shuffle_ps(a.native(), ab2, _MM_SHUFFLE(s3 / 4 ? 3 : 1, s2 / 4 ? 2 : 0, s1, s0));
                    }
#endif
#if SIMD_USE_AVX512F
                    template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                    static inline float32<16> run(const float32<16> &a, const float32<16> &b) {
                        __m512 ab2 =
                            _mm512_shuffle_ps(a.native(), b.native(), _MM_SHUFFLE(s3 % 4, s2 % 4, s3 % 4, s2 % 4));
                        return _mm512_shuffle_ps(a.native(), ab2, _MM_SHUFFLE(s3 / 4 ? 3 : 1, s2 / 4 ? 2 : 0, s1, s0));
                    }
#endif
                };

                // any
                template <> struct shuffle_impl<16> {
                    template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                    static inline float32<4> run(const float32<4> &a, const float32<4> &b) {
#if SIMD_USE_SSE4_1
                        __m128 ap = _mm_shuffle_ps(a.native(),
                                                   a.native(),
                                                   SIMD_SHUFFLE_MASK_4x4(s0 % 4, s1 % 4, s2 % 4, s3 % 4));
                        __m128 bp = _mm_shuffle_ps(b.native(),
                                                   b.native(),
                                                   SIMD_SHUFFLE_MASK_4x4(s0 % 4, s1 % 4, s2 % 4, s3 % 4));
                        return _mm_blend_ps(ap, bp, SIMD_SHUFFLE_MASK_4x2(s0 / 4, s1 / 4, s2 / 4, s3 / 4));
#else
                        __m128 ab1 =
                            _mm_shuffle_ps(a.native(), b.native(), _MM_SHUFFLE(s1 % 4, s0 % 4, s1 % 4, s0 % 4));
                        __m128 ab2 =
                            _mm_shuffle_ps(a.native(), b.native(), _MM_SHUFFLE(s3 % 4, s2 % 4, s3 % 4, s2 % 4));
                        return _mm_shuffle_ps(
                            ab1, ab2, _MM_SHUFFLE(s3 / 4 ? 3 : 1, s2 / 4 ? 2 : 0, s1 / 4 ? 3 : 1, s0 / 4 ? 2 : 0));
#endif
                    }
#if SIMD_USE_AVX
                    template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                    static inline float32<8> run(const float32<8> &a, const float32<8> &b) {
                        __m256 ap = _mm256_shuffle_ps(a.native(),
                                                      a.native(),
                                                      SIMD_SHUFFLE_MASK_4x4(s0 % 4, s1 % 4, s2 % 4, s3 % 4));
                        __m256 bp = _mm256_shuffle_ps(b.native(),
                                                      b.native(),
                                                      SIMD_SHUFFLE_MASK_4x4(s0 % 4, s1 % 4, s2 % 4, s3 % 4));
                        return _mm256_blend_ps(ap, bp, SIMD_SHUFFLE_MASK_4x2_2(s0 / 4, s1 / 4, s2 / 4, s3 / 4));
                    }
#endif
#if SIMD_USE_AVX512F
                    template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                    static inline float32<16> run(const float32<16> &a, const float32<16> &b) {
                        __m512 ap = _mm512_shuffle_ps(a.native(),
                                                      a.native(),
                                                      SIMD_SHUFFLE_MASK_4x4(s0 % 4, s1 % 4, s2 % 4, s3 % 4));
                        const int mask = SIMD_SHUFFLE_MASK_4x2_4(s0 / 4, s1 / 4, s2 / 4, s3 / 4);
                        return _mm512_mask_shuffle_ps(
                            ap, mask, b.native(), b.native(), SIMD_SHUFFLE_MASK_4x4(s0 % 4, s1 % 4, s2 % 4, s3 % 4));
                    }
#endif
                };

                template <unsigned s0, unsigned s1, unsigned s2, unsigned s3, unsigned N>
                float32<N> do_shuffle(const float32<N> &a, const float32<N> &b) {
                    return shuffle_impl<impl_selector<s0, s1, s2, s3>::impl>::template run<s0, s1, s2, s3>(a, b);
                }

            } // namespace sse_shuffle4x2_float32
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
#endif
