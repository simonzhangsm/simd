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

#ifndef SIMD_DETAIL_INSN_SHUFFLE2x2_H
#define SIMD_DETAIL_INSN_SHUFFLE2x2_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/core/make_shuffle_bytes_mask.h>
#include <bigmath/simd/core/shuffle_bytes16.h>
#include <bigmath/simd/detail/not_implemented.h>
#include <bigmath/simd/detail/shuffle/neon_int32x4.h>
#include <bigmath/simd/detail/shuffle/neon_int64x2.h>
#include <bigmath/simd/detail/shuffle/shuffle_mask.h>
#include <bigmath/simd/detail/vector_array_macros.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {


                // -----------------------------------------------------------------------------
                // float32

                template <unsigned s0, unsigned s1>
                inline float32<4> i_shuffle2x2(const float32<4> &a, const float32<4> &b) {
                    static_assert(s0 < 4 && s1 < 4, "Selector out of range");
#if SIMD_USE_NULL
                    float32<4> r;
                    r.el(0) = s0 < 2 ? a.el(s0) : b.el(s0 - 2);
                    r.el(1) = s1 < 2 ? a.el(s1) : b.el(s1 - 2);
                    r.el(2) = s0 < 2 ? a.el(s0 + 2) : b.el(s0);
                    r.el(3) = s1 < 2 ? a.el(s1 + 2) : b.el(s1);
                    return r;
#elif SIMD_USE_SSE2
                    if (s0 < 2 && s1 < 2) {
                        return _mm_shuffle_ps(a.native(), a.native(), SIMD_SHUFFLE_MASK_4x4(s0, s1, s0 + 2, s1 + 2));
                    } else if (s0 >= 2 && s1 >= 2) {
                        return _mm_shuffle_ps(b.native(), b.native(), SIMD_SHUFFLE_MASK_4x4(s0 - 2, s1 - 2, s0, s1));
#if SIMD_USE_SSE4_1
                    } else if (s0 == 0 && s1 == 3) {
                        return _mm_blend_ps(a.native(), b.native(), 0xa);
                    } else if (s0 == 2 && s1 == 1) {
                        return _mm_blend_ps(b.native(), a.native(), 0xa);
#endif
                    } else if (s0 < 2) { // s1 >= 2
                        __m128 t =
                            _mm_shuffle_ps(a.native(), b.native(), SIMD_SHUFFLE_MASK_4x4(s0, s0 + 1, s1 - 2, s1 - 1));
                        return _mm_shuffle_ps(t, t, _MM_SHUFFLE(3, 1, 2, 0));
                    } else { // s0 >= 2, s1 < 2
                        __m128 t =
                            _mm_shuffle_ps(b.native(), a.native(), SIMD_SHUFFLE_MASK_4x4(s1, s1 + 1, s0 - 2, s0 - 1));
                        return _mm_shuffle_ps(t, t, _MM_SHUFFLE(3, 1, 2, 0));
                    }
#elif SIMD_USE_NEON
                    return (float32<4>)detail::neon_shuffle_int32x4::shuffle2x2<s0, s1>(float32<4>(a), float32<4>(b));
#elif SIMD_USE_ALTIVEC
                    uint32<4> mask = make_shuffle_bytes16_mask<s0, s1>(mask);
                    return shuffle_bytes16(a, b, mask);
#elif SIMD_USE_MSA
                    const unsigned q0 = s0 < 2 ? s0 : s0 + 2;
                    const unsigned q1 = s1 < 2 ? s1 : s1 + 2;
                    uint32<4> mask = make_uint(q0, q1, q0 + 2, q1 + 2);
                    return (v4f32)__msa_vshf_w((v4i32)mask.native(), (v4i32)b.native(), (v4i32)a.native());
#else
                    return SIMD_NOT_IMPLEMENTED_TEMPLATE2(int64<s0 + 4>, a, b);
#endif
                }

#if SIMD_USE_AVX
                template <unsigned s0, unsigned s1>
                inline float32<8> i_shuffle2x2(const float32<8> &a, const float32<8> &b) {
                    static_assert(s0 < 4 && s1 < 4, "Selector out of range");
                    if (s0 < 2 && s1 < 2) {
                        return _mm256_permute_ps(a.native(), SIMD_SHUFFLE_MASK_4x4(s0, s1, s0 + 2, s1 + 2));
                    } else if (s0 >= 2 && s1 >= 2) {
                        return _mm256_permute_ps(b.native(), SIMD_SHUFFLE_MASK_4x4(s0 - 2, s1 - 2, s0, s1));
                    } else if (s0 == 0 && s1 == 3) {
                        return _mm256_blend_ps(a.native(), b.native(), 0xaa);
                    } else if (s0 == 2 && s1 == 1) {
                        return _mm256_blend_ps(b.native(), a.native(), 0xaa);
                    } else if (s0 < 2) { // s1 >= 2
                        __m256 t = _mm256_shuffle_ps(a.native(),
                                                     b.native(),
                                                     SIMD_SHUFFLE_MASK_4x4(s0, s0 + 1, s1 - 2, s1 - 1));
                        return _mm256_permute_ps(t, _MM_SHUFFLE(3, 1, 2, 0));
                    } else { // s0 >= 2, s1 < 2
                        __m256 t = _mm256_shuffle_ps(b.native(),
                                                     a.native(),
                                                     SIMD_SHUFFLE_MASK_4x4(s1, s1 + 1, s0 - 2, s0 - 1));
                        return _mm256_permute_ps(t, _MM_SHUFFLE(3, 1, 2, 0));
                    }
                }
#endif

#if SIMD_USE_AVX512F
                template <unsigned s0, unsigned s1>
                inline float32<16> i_shuffle2x2(const float32<16> &a, const float32<16> &b) {
                    static_assert(s0 < 4 && s1 < 4, "Selector out of range");
                    if (s0 < 2 && s1 < 2) {
                        return _mm512_permute_ps(a.native(), SIMD_SHUFFLE_MASK_4x4(s0, s1, s0 + 2, s1 + 2));
                    } else if (s0 >= 2 && s1 >= 2) {
                        return _mm512_permute_ps(b.native(), SIMD_SHUFFLE_MASK_4x4(s0 - 2, s1 - 2, s0, s1));
                    } else if (s0 == 0 && s1 == 3) {
                        return _mm512_mask_blend_ps(0xaaaa, a.native(), b.native());
                    } else if (s0 == 2 && s1 == 1) {
                        return _mm512_mask_blend_ps(0xaaaa, b.native(), a.native());
                    } else if (s0 < 2) { // s1 >= 2
                        __m512 t = _mm512_shuffle_ps(a.native(),
                                                     b.native(),
                                                     SIMD_SHUFFLE_MASK_4x4(s0, s0 + 1, s1 - 2, s1 - 1));
                        return _mm512_permute_ps(t, _MM_SHUFFLE(3, 1, 2, 0));
                    } else { // s0 >= 2, s1 < 2
                        __m512 t = _mm512_shuffle_ps(b.native(),
                                                     a.native(),
                                                     SIMD_SHUFFLE_MASK_4x4(s1, s1 + 1, s0 - 2, s0 - 1));
                        return _mm512_permute_ps(t, _MM_SHUFFLE(3, 1, 2, 0));
                    }
                }
#endif

                template <unsigned s0, unsigned s1, unsigned N>
                inline float32<N> i_shuffle2x2(const float32<N> &a, const float32<N> &b) {
                    SIMD_VEC_ARRAY_IMPL2(float32<N>, (i_shuffle2x2<s0, s1>), a, b);
                }

                // float64


                template <unsigned s0, unsigned s1>
                inline float64<2> i_shuffle2x2(const float64<2> &a, const float64<2> &b) {
                    static_assert(s0 < 4 && s1 < 4, "Selector out of range");
#if SIMD_USE_SSE2
                    if (s0 < 2 && s1 < 2) {
                        return _mm_shuffle_pd(a.native(), a.native(), SIMD_SHUFFLE_MASK_2x2(s0, s1));
                    } else if (s0 >= 2 && s1 >= 2) {
                        return _mm_shuffle_pd(b.native(), b.native(), SIMD_SHUFFLE_MASK_2x2(s0 - 2, s1 - 2));
#if SIMD_USE_SSE4_1
                    } else if (s0 == 0 && s1 == 3) {
                        return _mm_blend_pd(a.native(), b.native(), 0x2);
                    } else if (s0 == 2 && s1 == 1) {
                        return _mm_blend_pd(b.native(), a.native(), 0x2);
#endif
                    } else if (s0 < 2) { // s1 >= 2
                        return _mm_shuffle_pd(a.native(), b.native(), SIMD_SHUFFLE_MASK_2x2(s0, s1 - 2));
                    } else { // s0 >= 2, s1 < 2
                        return _mm_shuffle_pd(b.native(), a.native(), SIMD_SHUFFLE_MASK_2x2(s1, s0 - 2));
                    }
#elif SIMD_USE_NEON64
                    return (float64<2>)detail::neon_shuffle_int64x2::shuffle2x2<s0, s1>(uint64<2>(a), uint64<2>(b));
#elif SIMD_USE_VSX_206
                    __vector double da = a.native(), db = b.native();
                    if (s0 < 2 && s1 < 2) {
                        return vec_xxpermdi(da, da, SIMD_VSX_SHUFFLE_MASK_2x2(s0, s1));
                    } else if (s0 >= 2 && s1 >= 2) {
                        return vec_xxpermdi(db, db, SIMD_VSX_SHUFFLE_MASK_2x2(s0 - 2, s1 - 2));
                    } else if (s0 < 2) { // s1 >= 2
                        return vec_xxpermdi(da, db, SIMD_VSX_SHUFFLE_MASK_2x2(s0, s1 - 2));
                    } else { // s0 >= 2, s1 < 2
                        return vec_xxpermdi(db, da, SIMD_VSX_SHUFFLE_MASK_2x2(s1, s0 - 2));
                    }
#elif SIMD_USE_MSA
                    uint64<2> mask = make_uint(s0, s1);
                    return (v2f64)__msa_vshf_d((v2i64)mask.native(), (v2i64)b.native(), (v2i64)a.native());
#elif SIMD_USE_NULL || SIMD_USE_NEON || SIMD_USE_ALTIVEC
                    float64<2> r;
                    r.el(0) = s0 < 2 ? a.el(s0) : b.el(s0 - 2);
                    r.el(1) = s1 < 2 ? a.el(s1) : b.el(s1 - 2);
                    return r;
#else
                    return SIMD_NOT_IMPLEMENTED_TEMPLATE2(int64<s0 + 4>, a, b);
#endif
                }

#if SIMD_USE_AVX
                template <unsigned s0, unsigned s1>
                inline float64<4> i_shuffle2x2(const float64<4> &a, const float64<4> &b) {
                    static_assert(s0 < 4 && s1 < 4, "Selector out of range");
                    if (s0 < 2 && s1 < 2) {
                        return _mm256_shuffle_pd(a.native(), a.native(), SIMD_SHUFFLE_MASK_2x2_2(s0, s1));
                    } else if (s0 >= 2 && s1 >= 2) {
                        return _mm256_shuffle_pd(b.native(), b.native(), SIMD_SHUFFLE_MASK_2x2_2(s0 - 2, s1 - 2));
                    } else if (s0 == 0 && s1 == 3) {
                        return _mm256_blend_pd(a.native(), b.native(), 0xa);
                    } else if (s0 == 2 && s1 == 1) {
                        return _mm256_blend_pd(b.native(), a.native(), 0xa);
                    } else if (s0 < 2) { // s1 >= 2
                        return _mm256_shuffle_pd(a.native(), b.native(), SIMD_SHUFFLE_MASK_2x2_2(s0, s1 - 2));
                    } else { // s0 >= 2, s1 < 2
                        return _mm256_shuffle_pd(b.native(), a.native(), SIMD_SHUFFLE_MASK_2x2_2(s1, s0 - 2));
                    }
                }
#endif

#if SIMD_USE_AVX512F
                template <unsigned s0, unsigned s1>
                inline float64<8> i_shuffle2x2(const float64<8> &a, const float64<8> &b) {
                    static_assert(s0 < 4 && s1 < 4, "Selector out of range");
                    if (s0 < 2 && s1 < 2) {
                        return _mm512_shuffle_pd(a.native(), a.native(), SIMD_SHUFFLE_MASK_2x2_4(s0, s1));
                    } else if (s0 >= 2 && s1 >= 2) {
                        return _mm512_shuffle_pd(b.native(), b.native(), SIMD_SHUFFLE_MASK_2x2_4(s0 - 2, s1 - 2));
                    } else if (s0 == 0 && s1 == 3) {
                        return _mm512_mask_blend_pd(0xaa, a.native(), b.native());
                    } else if (s0 == 2 && s1 == 1) {
                        return _mm512_mask_blend_pd(0xaa, b.native(), a.native());
                    } else if (s0 < 2) { // s1 >= 2
                        return _mm512_shuffle_pd(a.native(), b.native(), SIMD_SHUFFLE_MASK_2x2_4(s0, s1 - 2));
                    } else { // s0 >= 2, s1 < 2
                        return _mm512_shuffle_pd(b.native(), a.native(), SIMD_SHUFFLE_MASK_2x2_4(s1, s0 - 2));
                    }
                }
#endif

                template <unsigned s0, unsigned s1, unsigned N>
                inline float64<N> i_shuffle2x2(const float64<N> &a, const float64<N> &b) {
                    SIMD_VEC_ARRAY_IMPL2(float64<N>, (i_shuffle2x2<s0, s1>), a, b);
                }

                // int32

                template <unsigned s0, unsigned s1>
                inline uint32<4> i_shuffle2x2(const uint32<4> &a, const uint32<4> &b) {
                    static_assert(s0 < 4 && s1 < 4, "Selector out of range");
#if SIMD_USE_NULL
                    uint32<4> r;
                    r.el(0) = s0 < 2 ? a.el(s0) : b.el(s0 - 2);
                    r.el(1) = s1 < 2 ? a.el(s1) : b.el(s1 - 2);
                    r.el(2) = s0 < 2 ? a.el(s0 + 2) : b.el(s0);
                    r.el(3) = s1 < 2 ? a.el(s1 + 2) : b.el(s1);
                    return r;
#elif SIMD_USE_SSE2
                    if (s0 < 2 && s1 < 2) {
                        const unsigned mask = SIMD_SHUFFLE_MASK_4x4(s0, s1, s0 + 2, s1 + 2);
                        return _mm_shuffle_epi32(a.native(), mask);
                    } else if (s0 >= 2 && s1 >= 2) {
                        const unsigned mask = SIMD_SHUFFLE_MASK_4x4(s0 - 2, s1 - 2, s0, s1);
                        return _mm_shuffle_epi32(b.native(), mask);
#if SIMD_USE_SSE4_1
                    } else if (s0 == 0 && s1 == 3) {
                        return _mm_blend_epi16(a.native(), b.native(), 0xcc);
                    } else if (s0 == 2 && s1 == 1) {
                        return _mm_blend_epi16(b.native(), a.native(), 0xcc);
#endif
                    } else if (s0 < 2) { // s1 >= 2
                        float32<4> fa, fb;
                        fa = a, fb = b;
                        __m128 t =
                            _mm_shuffle_ps(fa.native(), fb.native(), SIMD_SHUFFLE_MASK_4x4(s0, s0 + 1, s1 - 2, s1 - 1));
                        return _mm_castps_si128(_mm_shuffle_ps(t, t, _MM_SHUFFLE(3, 1, 2, 0)));
                    } else { // s0 >= 2, s1 < 2
                        float32<4> fa, fb;
                        fa = a, fb = b;
                        __m128 t =
                            _mm_shuffle_ps(fb.native(), fa.native(), SIMD_SHUFFLE_MASK_4x4(s1, s1 + 1, s0 - 2, s0 - 1));
                        return _mm_castps_si128(_mm_shuffle_ps(t, t, _MM_SHUFFLE(3, 1, 2, 0)));
                    }
#elif SIMD_USE_NEON
                    return detail::neon_shuffle_int32x4::shuffle2x2<s0, s1>(a, b);
#elif SIMD_USE_ALTIVEC
                    uint32<4> mask = make_shuffle_bytes16_mask<s0, s1>(mask);
                    return shuffle_bytes16(a, b, mask);
#elif SIMD_USE_MSA
                    const unsigned q0 = s0 < 2 ? s0 : s0 + 2;
                    const unsigned q1 = s1 < 2 ? s1 : s1 + 2;
                    uint32<4> mask = make_uint(q0, q1, q0 + 2, q1 + 2);

                    return (v4u32)__msa_vshf_w((v4i32)(v4u32)mask, (v4i32)(v4u32)b, (v4i32)(v4u32)a);
#else
                    return SIMD_NOT_IMPLEMENTED_TEMPLATE2(int64<s0 + 4>, a, b);
#endif
                }

#if SIMD_USE_AVX2
                template <unsigned s0, unsigned s1>
                inline uint32<8> i_shuffle2x2(const uint32<8> &a, const uint32<8> &b) {
                    static_assert(s0 < 4 && s1 < 4, "Selector out of range");
                    if (s0 < 2 && s1 < 2) {
                        const unsigned mask = SIMD_SHUFFLE_MASK_4x4(s0, s1, s0 + 2, s1 + 2);
                        return _mm256_shuffle_epi32(a.native(), mask);
                    } else if (s0 >= 2 && s1 >= 2) {
                        const unsigned mask = SIMD_SHUFFLE_MASK_4x4(s0 - 2, s1 - 2, s0, s1);
                        return _mm256_shuffle_epi32(b.native(), mask);
                    } else if (s0 == 0 && s1 == 3) {
                        return _mm256_blend_epi32(a.native(), b.native(), 0xa);
                    } else if (s0 == 2 && s1 == 1) {
                        return _mm256_blend_epi32(b.native(), a.native(), 0xa);
                    } else if (s0 < 2) { // s1 >= 2
                        float32<8> fa, fb;
                        fa = a, fb = b;
                        __m256 t = _mm256_shuffle_ps(fa.native(),
                                                     fb.native(),
                                                     SIMD_SHUFFLE_MASK_4x4(s0, s0 + 1, s1 - 2, s1 - 1));
                        return _mm256_castps_si256(_mm256_permute_ps(t, _MM_SHUFFLE(3, 1, 2, 0)));
                    } else { // s0 >= 2, s1 < 2
                        float32<8> fa, fb;
                        fa = a, fb = b;
                        __m256 t = _mm256_shuffle_ps(fb.native(),
                                                     fa.native(),
                                                     SIMD_SHUFFLE_MASK_4x4(s1, s1 + 1, s0 - 2, s0 - 1));
                        return _mm256_castps_si256(_mm256_permute_ps(t, _MM_SHUFFLE(3, 1, 2, 0)));
                    }
                }
#endif

#if SIMD_USE_AVX512F
                template <unsigned s0, unsigned s1>
                inline uint32<16> i_shuffle2x2(const uint32<16> &a, const uint32<16> &b) {
                    static_assert(s0 < 4 && s1 < 4, "Selector out of range");
                    if (s0 < 2 && s1 < 2) {
                        const unsigned mask = SIMD_SHUFFLE_MASK_4x4(s0, s1, s0 + 2, s1 + 2);
                        return _mm512_shuffle_epi32(a.native(), _MM_PERM_ENUM(mask));
                    } else if (s0 >= 2 && s1 >= 2) {
                        const unsigned mask = SIMD_SHUFFLE_MASK_4x4(s0 - 2, s1 - 2, s0, s1);
                        return _mm512_shuffle_epi32(b.native(), _MM_PERM_ENUM(mask));
                    } else if (s0 == 0 && s1 == 3) {
                        return _mm512_mask_blend_epi32(0xaaaa, a.native(), b.native());
                    } else if (s0 == 2 && s1 == 1) {
                        return _mm512_mask_blend_epi32(0xaaaa, b.native(), a.native());
                    } else if (s0 < 2) { // s1 >= 2
                        float32<16> fa, fb;
                        fa = a;
                        fb = b;
                        __m512 t = _mm512_shuffle_ps(fa.native(),
                                                     fb.native(),
                                                     SIMD_SHUFFLE_MASK_4x4(s0, s0 + 1, s1 - 2, s1 - 1));
                        return _mm512_castps_si512(_mm512_permute_ps(t, _MM_SHUFFLE(3, 1, 2, 0)));
                    } else { // s0 >= 2, s1 < 2
                        float32<16> fa, fb;
                        fa = a;
                        fb = b;
                        __m512 t = _mm512_shuffle_ps(fb.native(),
                                                     fa.native(),
                                                     SIMD_SHUFFLE_MASK_4x4(s1, s1 + 1, s0 - 2, s0 - 1));
                        return _mm512_castps_si512(_mm512_permute_ps(t, _MM_SHUFFLE(3, 1, 2, 0)));
                    }
                }
#endif

                template <unsigned s0, unsigned s1, unsigned N>
                inline uint32<N> i_shuffle2x2(const uint32<N> &a, const uint32<N> &b) {
                    SIMD_VEC_ARRAY_IMPL2(uint32<N>, (i_shuffle2x2<s0, s1>), a, b);
                }

                // int64

                template <unsigned s0, unsigned s1>
                inline uint64<2> i_shuffle2x2(const uint64<2> &a, const uint64<2> &b) {
                    static_assert(s0 < 4 && s1 < 4, "Selector out of range");
#if SIMD_USE_SSE2
                    if (s0 < 2 && s1 < 2) {
                        const unsigned mask = SIMD_SHUFFLE_MASK_4x4(s0 * 2, s0 * 2 + 1, s1 * 2, s1 * 2 + 1);
                        return _mm_shuffle_epi32(a.native(), mask);
                    } else if (s0 >= 2 && s1 >= 2) {
                        const unsigned mask = SIMD_SHUFFLE_MASK_4x4(s0 * 2, s0 * 2 + 1, s1 * 2, s1 * 2 + 1);
                        return _mm_shuffle_epi32(b.native(), mask);
                    } else if (s0 == 0 && s1 == 2) {
                        return _mm_unpacklo_epi64(a.native(), b.native());
                    } else if (s0 == 2 && s1 == 0) {
                        return _mm_unpacklo_epi64(b.native(), a.native());
                    } else if (s0 == 1 && s1 == 3) {
                        return _mm_unpackhi_epi64(a.native(), b.native());
                    } else if (s0 == 3 && s1 == 1) {
                        return _mm_unpackhi_epi64(b.native(), a.native());
#if SIMD_USE_SSE4_1
                    } else if (s0 == 0 && s1 == 3) {
                        return _mm_blend_epi16(a.native(), b.native(), 0xf0);
                    } else if (s0 == 2 && s1 == 1) {
                        return _mm_blend_epi16(b.native(), a.native(), 0xf0);
#endif
#if SIMD_USE_SSSE3
                    } else if (s0 == 1 && s1 == 2) {
                        return _mm_alignr_epi8(b.native(), a.native(), 8);
                    } else if (s0 == 3 && s1 == 0) {
                        return _mm_alignr_epi8(a.native(), b.native(), 8);
#endif
                    } else if (s0 < 2) { // s1 >= 2
                        __m128d na = _mm_castsi128_pd(a.native());
                        __m128d nb = _mm_castsi128_pd(b.native());
                        __m128d res = _mm_shuffle_pd(na, nb, SIMD_SHUFFLE_MASK_2x2(s0, s1 - 2));
                        return _mm_castpd_si128(res);
                    } else { // s0 >= 2, s1 < 2
                        __m128d na = _mm_castsi128_pd(a.native());
                        __m128d nb = _mm_castsi128_pd(b.native());
                        __m128d res = _mm_shuffle_pd(nb, na, SIMD_SHUFFLE_MASK_2x2(s1, s0 - 2));
                        return _mm_castpd_si128(res);
                    }
#elif SIMD_USE_NEON
                    return detail::neon_shuffle_int64x2::shuffle2x2<s0, s1>(a, b);
#elif SIMD_USE_VSX_207
                    __vector uint64_t da = a.native(), db = b.native();
                    if (s0 < 2 && s1 < 2) {
                        return vec_xxpermdi(da, da, SIMD_VSX_SHUFFLE_MASK_2x2(s0, s1));
                    } else if (s0 >= 2 && s1 >= 2) {
                        return vec_xxpermdi(db, db, SIMD_VSX_SHUFFLE_MASK_2x2(s0 - 2, s1 - 2));
                    } else if (s0 < 2) { // s1 >= 2
                        return vec_xxpermdi(da, db, SIMD_VSX_SHUFFLE_MASK_2x2(s0, s1 - 2));
                    } else { // s0 >= 2, s1 < 2
                        return vec_xxpermdi(db, da, SIMD_VSX_SHUFFLE_MASK_2x2(s1, s0 - 2));
                    }
#elif SIMD_USE_MSA
                    uint64<2> mask = make_uint(s0, s1);

                    return (v2u64)__msa_vshf_d((v2i64)mask.native(), (v2i64)b.native(), (v2i64)a.native());
#elif SIMD_USE_NULL || SIMD_USE_ALTIVEC
                    uint64<2> r;
                    r.el(0) = s0 < 2 ? a.el(s0) : b.el(s0 - 2);
                    r.el(1) = s1 < 2 ? a.el(s1) : b.el(s1 - 2);
                    return r;
#else
                    return SIMD_NOT_IMPLEMENTED_TEMPLATE2(int64<s0 + 4>, a, b);
#endif
                }

#if SIMD_USE_AVX2
                template <unsigned s0, unsigned s1>
                inline uint64<4> i_shuffle2x2(const uint64<4> &a, const uint64<4> &b) {
                    static_assert(s0 < 4 && s1 < 4, "Selector out of range");
                    if (s0 < 2 && s1 < 2) {
                        const unsigned mask = SIMD_SHUFFLE_MASK_4x4(s0 * 2, s0 * 2 + 1, s1 * 2, s1 * 2 + 1);
                        return _mm256_shuffle_epi32(a.native(), mask);
                    } else if (s0 >= 2 && s1 >= 2) {
                        const unsigned mask = SIMD_SHUFFLE_MASK_4x4(s0 * 2, s0 * 2 + 1, s1 * 2, s1 * 2 + 1);
                        return _mm256_shuffle_epi32(b.native(), mask);
                    } else if (s0 == 0 && s1 == 2) {
                        return _mm256_unpacklo_epi64(a.native(), b.native());
                    } else if (s0 == 2 && s1 == 0) {
                        return _mm256_unpacklo_epi64(b.native(), a.native());
                    } else if (s0 == 1 && s1 == 3) {
                        return _mm256_unpackhi_epi64(a.native(), b.native());
                    } else if (s0 == 3 && s1 == 1) {
                        return _mm256_unpackhi_epi64(b.native(), a.native());
                    } else if (s0 == 0 && s1 == 3) {
                        return _mm256_blend_epi32(a.native(), b.native(), 0xcc);
                    } else if (s0 == 2 && s1 == 1) {
                        return _mm256_blend_epi32(b.native(), a.native(), 0xcc);
                    } else if (s0 == 1 && s1 == 2) {
                        return _mm256_alignr_epi8(b.native(), a.native(), 8);
                    } else { // if (s0 == 3 && s1 == 0)
                        return _mm256_alignr_epi8(a.native(), b.native(), 8);
                    }
                }
#endif

#if SIMD_USE_AVX512F
                template <unsigned s0, unsigned s1>
                inline uint64<8> i_shuffle2x2(const uint64<8> &a, const uint64<8> &b) {
                    static_assert(s0 < 4 && s1 < 4, "Selector out of range");
                    if (s0 < 2 && s1 < 2) {
                        const unsigned mask = SIMD_SHUFFLE_MASK_4x4(s0, s1, s0 + 2, s1 + 2);
                        return _mm512_permutex_epi64(a.native(), mask);
                    } else if (s0 >= 2 && s1 >= 2) {
                        const unsigned mask = SIMD_SHUFFLE_MASK_4x4(s0 - 2, s1 - 2, s0, s1);
                        return _mm512_permutex_epi64(b.native(), mask);
                    } else if (s0 == 0 && s1 == 2) {
                        return _mm512_unpacklo_epi64(a.native(), b.native());
                    } else if (s0 == 2 && s1 == 0) {
                        return _mm512_unpacklo_epi64(b.native(), a.native());
                    } else if (s0 == 1 && s1 == 3) {
                        return _mm512_unpackhi_epi64(a.native(), b.native());
                    } else if (s0 == 3 && s1 == 1) {
                        return _mm512_unpackhi_epi64(b.native(), a.native());
                    } else if (s0 == 0 && s1 == 3) {
                        return _mm512_mask_blend_epi64(0xaa, a.native(), b.native());
                    } else if (s0 == 2 && s1 == 1) {
                        return _mm512_mask_blend_epi64(0xaa, b.native(), a.native());
                    } else if (s0 < 2) { // s1 >= 2
                        __m512d na = _mm512_castsi512_pd(a.native());
                        __m512d nb = _mm512_castsi512_pd(b.native());
                        __m512d res = _mm512_shuffle_pd(na, nb, SIMD_SHUFFLE_MASK_2x2_4(s0, s1 - 2));
                        return _mm512_castpd_si512(res);
                    } else { // s0 >= 2, s1 < 2
                        __m512d na = _mm512_castsi512_pd(a.native());
                        __m512d nb = _mm512_castsi512_pd(b.native());
                        __m512d res = _mm512_shuffle_pd(nb, na, SIMD_SHUFFLE_MASK_2x2_4(s1, s0 - 2));
                        return _mm512_castpd_si512(res);
                    }
                    /* GCC BUG
                    } else if (s0 == 1 && s1 == 2) {
                        return _mm512_alignr_epi8(b.native(), a.native(), 8);
                    } else if (s0 == 3 && s1 == 0) {
                        return _mm512_alignr_epi8(a.native(), b.native(), 8);
                    }*/
                }
#endif

                template <unsigned s0, unsigned s1, unsigned N>
                inline uint64<N> i_shuffle2x2(const uint64<N> &a, const uint64<N> &b) {
                    SIMD_VEC_ARRAY_IMPL2(uint64<N>, (i_shuffle2x2<s0, s1>), a, b);
                }


            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
