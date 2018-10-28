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

#ifndef SIMD_DETAIL_INSN_CONV_EXTEND_TO_INT64_H
#define SIMD_DETAIL_INSN_CONV_EXTEND_TO_INT64_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/core/i_shift_r.h>
#include <bigmath/simd/core/move_l.h>
#include <bigmath/simd/core/zip_lo.h>
#include <bigmath/simd/core/combine.h>
#include <bigmath/simd/detail/mem_block.h>
#include <bigmath/simd/detail/vector_array_conv_macros.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {

                // -----------------------------------------------------------------------------

                static inline uint64<4> i_to_uint64(const uint32<4> &a) {
#if SIMD_USE_NULL
                    uint64x4 r;
                    r.vec(0).el(0) = uint64_t(a.el(0));
                    r.vec(0).el(1) = uint64_t(a.el(1));
                    r.vec(1).el(0) = uint64_t(a.el(2));
                    r.vec(1).el(1) = uint64_t(a.el(3));
                    return r;
#elif SIMD_USE_AVX2
                    return _mm256_cvtepu32_epi64(a.native());
#elif SIMD_USE_SSE4_1
                    uint64x2 r1, r2;
                    r1 = _mm_cvtepu32_epi64(a.native());
                    r2 = _mm_cvtepu32_epi64(move4_l<2>(a).eval().native());
                    return combine(r1, r2);
#elif SIMD_USE_SSE2 || SIMD_USE_MSA || SIMD_USE_VSX_207
                    return (uint64x4)combine(zip4_lo(a, (uint32x4)make_zero()), zip4_hi(a, (uint32x4)make_zero()));
#elif SIMD_USE_NEON
                    uint64x2 r1, r2;
                    r1 = vmovl_u32(vget_low_u32(a.native()));
                    r2 = vmovl_u32(vget_high_u32(a.native()));
                    return combine(r1, r2);
#elif SIMD_USE_ALTIVEC
                    uint64x4 r;
                    mem_block<uint32x4> b = a;
                    r.vec(0).el(0) = b[0];
                    r.vec(0).el(1) = b[1];
                    r.vec(1).el(0) = b[2];
                    r.vec(1).el(1) = b[3];
                    return r;
#endif
                }

#if SIMD_USE_AVX2
                static inline uint64<8> i_to_uint64(const uint32<8> &a) {
                    uint32<4> a1, a2;
                    uint64<4> r1, r2;
                    split(a, a1, a2);
                    r1 = _mm256_cvtepu32_epi64(a1.native());
                    r2 = _mm256_cvtepu32_epi64(a2.native());
                    return combine(r1, r2);
                }
#endif

#if SIMD_USE_AVX512F
                static inline uint64<16> i_to_uint64(const uint32<16> &a) {
                    uint32<8> a1, a2;
                    uint64<8> r1, r2;
                    split(a, a1, a2);
                    r1 = _mm512_cvtepu32_epi64(a1.native());
                    r2 = _mm512_cvtepu32_epi64(a2.native());
                    return combine(r1, r2);
                }
#endif

                template <unsigned N> inline uint64<N> i_to_uint64(const uint32<N> &a) {
                    SIMD_VEC_ARRAY_IMPL_CONV_INSERT(uint64<N>, i_to_uint64, a)
                }

                // -----------------------------------------------------------------------------

                static inline uint64<8> i_to_uint64(const uint16<8> &a) {
#if SIMD_USE_NULL
                    uint64<8> r;
                    for (unsigned i = 0; i < 8; i++) {
                        r.vec(i / 2).el(i % 2) = uint64_t(a.vec(0).el(i));
                    }
                    return r;
#elif SIMD_USE_AVX512F
                    return _mm512_cvtepu16_epi64(a.native());
#elif SIMD_USE_AVX2
                    uint64<8> r;
                    r.vec(0) = _mm256_cvtepu16_epi64(a.native());
                    r.vec(1) = _mm256_cvtepu16_epi64(move8_l<4>(a).eval().native());
                    return r;
#elif SIMD_USE_SSE4_1
                    uint64<8> r;
                    r.vec(0) = _mm_cvtepu16_epi64(a.native());
                    r.vec(1) = _mm_cvtepu16_epi64(move8_l<2>(a).eval().native());
                    r.vec(2) = _mm_cvtepu16_epi64(move8_l<4>(a).eval().native());
                    r.vec(3) = _mm_cvtepu16_epi64(move8_l<6>(a).eval().native());
                    return r;
#elif SIMD_USE_SSE2 || SIMD_USE_NEON || SIMD_USE_MSA || SIMD_USE_VSX_207
                    return i_to_uint64(i_to_uint32(a));
#elif SIMD_USE_ALTIVEC
                    uint64<8> r;
                    mem_block<uint16<8>> b = a;
                    for (unsigned i = 0; i < 8; i++) {
                        r.vec(i / 2).el(i % 2) = uint64_t(b[i]);
                    }
                    return r;
#endif
                }

#if SIMD_USE_AVX2
                static inline uint64<16> i_to_uint64(const uint16<16> &a) {
#if SIMD_USE_AVX512F
                    uint64<16> r;
                    uint16<8> a0, a1;
                    split(a, a0, a1);
                    r.vec(0) = _mm512_cvtepu16_epi64(a0.native());
                    r.vec(1) = _mm512_cvtepu16_epi64(a1.native());
                    return r;
#else
                    uint64<16> r;
                    uint16<8> a0, a1;
                    split(a, a0, a1);
                    r.vec(0) = _mm256_cvtepu16_epi64(a0.native());
                    r.vec(1) = _mm256_cvtepu16_epi64(move8_l<4>(a0).eval().native());
                    r.vec(2) = _mm256_cvtepu16_epi64(a1.native());
                    r.vec(3) = _mm256_cvtepu16_epi64(move8_l<4>(a1).eval().native());
                    return r;
#endif
                }
#endif

#if SIMD_USE_AVX512F
                static inline uint64<32> i_to_uint64(const uint16<32> &a) {
                    uint64<32> r;
                    uint16<16> a01, a23;
                    uint16<8> a0, a1, a2, a3;
#if SIMD_USE_AVX512BW
                    split(a, a01, a23);
#else
                    a01 = a.vec(0);
                    a23 = a.vec(1);
#endif
                    split(a01, a0, a1);
                    split(a23, a2, a3);

                    r.vec(0) = _mm512_cvtepu16_epi64(a0.native());
                    r.vec(1) = _mm512_cvtepu16_epi64(a1.native());
                    r.vec(2) = _mm512_cvtepu16_epi64(a2.native());
                    r.vec(3) = _mm512_cvtepu16_epi64(a3.native());
                    return r;
                }
#endif

                template <unsigned N> inline uint64<N> i_to_uint64(const uint16<N> &a) {
                    SIMD_VEC_ARRAY_IMPL_CONV_INSERT(uint64<N>, i_to_uint64, a)
                }

                // -----------------------------------------------------------------------------

                static inline uint64<16> i_to_uint64(const uint8<16> &a) {
#if SIMD_USE_NULL
                    uint64<16> r;
                    for (unsigned i = 0; i < 16; i++) {
                        r.vec(i / 2).el(i % 2) = uint64_t(a.vec(0).el(i));
                    }
                    return r;
#elif SIMD_USE_AVX512F
                    uint64<16> r;
                    r.vec(0) = _mm512_cvtepu8_epi64(a.native());
                    r.vec(1) = _mm512_cvtepu8_epi64(move16_l<8>(a).eval().native());
                    return r;
#elif SIMD_USE_AVX2
                    uint64<16> r;
                    r.vec(0) = _mm256_cvtepu8_epi64(a.native());
                    r.vec(1) = _mm256_cvtepu8_epi64(move16_l<4>(a).eval().native());
                    r.vec(2) = _mm256_cvtepu8_epi64(move16_l<8>(a).eval().native());
                    r.vec(3) = _mm256_cvtepu8_epi64(move16_l<12>(a).eval().native());
                    return r;
#elif SIMD_USE_SSE4_1
                    uint64<16> r;
                    r.vec(0) = _mm_cvtepu8_epi64(a.native());
                    r.vec(1) = _mm_cvtepu8_epi64(move16_l<2>(a).eval().native());
                    r.vec(2) = _mm_cvtepu8_epi64(move16_l<4>(a).eval().native());
                    r.vec(3) = _mm_cvtepu8_epi64(move16_l<6>(a).eval().native());
                    r.vec(4) = _mm_cvtepu8_epi64(move16_l<8>(a).eval().native());
                    r.vec(5) = _mm_cvtepu8_epi64(move16_l<10>(a).eval().native());
                    r.vec(6) = _mm_cvtepu8_epi64(move16_l<12>(a).eval().native());
                    r.vec(7) = _mm_cvtepu8_epi64(move16_l<14>(a).eval().native());
                    return r;
#elif SIMD_USE_SSE2 || SIMD_USE_NEON || SIMD_USE_MSA || SIMD_USE_VSX_207
                    return i_to_uint64(i_to_uint32(a));
#elif SIMD_USE_ALTIVEC
                    uint64<16> r;
                    mem_block<uint8<16>> b = a;
                    for (unsigned i = 0; i < 16; i++) {
                        r.vec(i / 2).el(i % 2) = uint64_t(b[i]);
                    }
                    return r;
#endif
                }

#if SIMD_USE_AVX2
                static inline uint64<32> i_to_uint64(const uint8<32> &a) {
#if SIMD_USE_AVX512F
                    uint64<32> r;
                    uint8<16> a0, a1;
                    split(a, a0, a1);
                    r.vec(0) = _mm512_cvtepu8_epi64(a0.native());
                    r.vec(1) = _mm512_cvtepu8_epi64(move16_l<8>(a0).eval().native());
                    r.vec(2) = _mm512_cvtepu8_epi64(a1.native());
                    r.vec(3) = _mm512_cvtepu8_epi64(move16_l<8>(a1).eval().native());
                    return r;
#else
                    uint64<32> r;
                    uint8<16> a0, a1;
                    split(a, a0, a1);
                    r.vec(0) = _mm256_cvtepu8_epi64(a0.native());
                    r.vec(1) = _mm256_cvtepu8_epi64(move16_l<4>(a0).eval().native());
                    r.vec(2) = _mm256_cvtepu8_epi64(move16_l<8>(a0).eval().native());
                    r.vec(3) = _mm256_cvtepu8_epi64(move16_l<12>(a0).eval().native());
                    r.vec(4) = _mm256_cvtepu8_epi64(a1.native());
                    r.vec(5) = _mm256_cvtepu8_epi64(move16_l<4>(a1).eval().native());
                    r.vec(6) = _mm256_cvtepu8_epi64(move16_l<8>(a1).eval().native());
                    r.vec(7) = _mm256_cvtepu8_epi64(move16_l<12>(a1).eval().native());
                    return r;
#endif
                }
#endif

#if SIMD_USE_AVX512F
                static inline uint64<64> i_to_uint64(const uint8<64> &a) {
                    uint64<64> r;
                    uint8<32> a01, a23;
                    uint8<16> a0, a1, a2, a3;
#if SIMD_USE_AVX512BW
                    split(a, a01, a23);
#else
                    a01 = a.vec(0);
                    a23 = a.vec(1);
#endif
                    split(a01, a0, a1);
                    split(a23, a2, a3);

                    r.vec(0) = _mm512_cvtepu8_epi64(a0.native());
                    r.vec(1) = _mm512_cvtepu8_epi64(move16_l<8>(a0).eval().native());
                    r.vec(2) = _mm512_cvtepu8_epi64(a1.native());
                    r.vec(3) = _mm512_cvtepu8_epi64(move16_l<8>(a1).eval().native());
                    r.vec(4) = _mm512_cvtepu8_epi64(a2.native());
                    r.vec(5) = _mm512_cvtepu8_epi64(move16_l<8>(a2).eval().native());
                    r.vec(6) = _mm512_cvtepu8_epi64(a3.native());
                    r.vec(7) = _mm512_cvtepu8_epi64(move16_l<8>(a3).eval().native());
                    return r;
                }
#endif

                template <unsigned N> inline uint64<N> i_to_uint64(const uint8<N> &a) {
                    SIMD_VEC_ARRAY_IMPL_CONV_INSERT(uint64<N>, i_to_uint64, a)
                }

                // -----------------------------------------------------------------------------

                static inline int64<4> i_to_int64(const int32<4> &a) {
#if SIMD_USE_NULL
                    int64<4> r;
                    r.vec(0).el(0) = int64_t(a.el(0));
                    r.vec(0).el(1) = int64_t(a.el(1));
                    r.vec(1).el(0) = int64_t(a.el(2));
                    r.vec(1).el(1) = int64_t(a.el(3));
                    return r;
#elif SIMD_USE_AVX2
                    return _mm256_cvtepi32_epi64(a.native());
#elif SIMD_USE_SSE4_1
                    uint64x2 r1, r2;
                    r1 = _mm_cvtepi32_epi64(a.native());
                    r2 = _mm_cvtepi32_epi64(move4_l<2>(a).eval().native());
                    return combine(r1, r2);
#elif SIMD_USE_SSE2 || SIMD_USE_MSA || SIMD_USE_VSX_207
                    int32x4 sign = shift_r<31>(a);
                    int64x2 lo, hi;
                    lo = zip4_lo(a, sign);
                    hi = zip4_hi(a, sign);
                    return combine(lo, hi);
#elif SIMD_USE_NEON
                    int64x2 r1, r2;
                    r1 = vmovl_s32(vget_low_s32(a.native()));
                    r2 = vmovl_s32(vget_high_s32(a.native()));
                    return combine(r1, r2);
#elif SIMD_USE_ALTIVEC
                    int64x4 r;
                    mem_block<int32x4> b = a;
                    r.vec(0).el(0) = b[0];
                    r.vec(0).el(1) = b[1];
                    r.vec(1).el(0) = b[2];
                    r.vec(1).el(1) = b[3];
                    return r;
#endif
                }

#if SIMD_USE_AVX2
                static inline int64<8> i_to_int64(const int32<8> &a) {
                    int32<4> a1, a2;
                    int64<4> r1, r2;
                    split(a, a1, a2);
                    r1 = _mm256_cvtepi32_epi64(a1.native());
                    r2 = _mm256_cvtepi32_epi64(a2.native());
                    return combine(r1, r2);
                }
#endif

#if SIMD_USE_AVX512F
                static inline int64<16> i_to_int64(const int32<16> &a) {
                    int64<8> r1, r2;
                    r1 = _mm512_cvtepi32_epi64(_mm512_castsi512_si256(a.native()));
                    r2 = _mm512_cvtepi32_epi64(_mm512_extracti64x4_epi64(a.native(), 1));
                    return combine(r1, r2);
                }
#endif

                template <unsigned N> inline int64<N> i_to_int64(const int32<N> &a) {
                    SIMD_VEC_ARRAY_IMPL_CONV_INSERT(int64<N>, i_to_int64, a)
                }

                // -----------------------------------------------------------------------------

                static inline int64<8> i_to_int64(const int16<8> &a) {
#if SIMD_USE_NULL
                    int64<8> r;
                    for (unsigned i = 0; i < 8; i++) {
                        r.vec(i / 2).el(i % 2) = int64_t(a.vec(0).el(i));
                    }
                    return r;
#elif SIMD_USE_AVX512F
                    return _mm512_cvtepi16_epi64(a.native());
#elif SIMD_USE_AVX2
                    int64<8> r;
                    r.vec(0) = _mm256_cvtepi16_epi64(a.native());
                    r.vec(1) = _mm256_cvtepi16_epi64(move8_l<4>(a).eval().native());
                    return r;
#elif SIMD_USE_SSE4_1
                    int64<8> r;
                    r.vec(0) = _mm_cvtepi16_epi64(a.native());
                    r.vec(1) = _mm_cvtepi16_epi64(move8_l<2>(a).eval().native());
                    r.vec(2) = _mm_cvtepi16_epi64(move8_l<4>(a).eval().native());
                    r.vec(3) = _mm_cvtepi16_epi64(move8_l<6>(a).eval().native());
                    return r;
#elif SIMD_USE_SSE2 || SIMD_USE_NEON || SIMD_USE_MSA || SIMD_USE_VSX_207
                    return i_to_int64(i_to_int32(a));
#elif SIMD_USE_ALTIVEC
                    int64<8> r;
                    mem_block<int16<8>> b = a;
                    for (unsigned i = 0; i < 8; i++) {
                        r.vec(i / 2).el(i % 2) = int64_t(b[i]);
                    }
                    return r;
#endif
                }

#if SIMD_USE_AVX2
                static inline int64<16> i_to_int64(const int16<16> &a) {
#if SIMD_USE_AVX512F
                    int64<16> r;
                    int16<8> a0, a1;
                    split(a, a0, a1);
                    r.vec(0) = _mm512_cvtepi16_epi64(a0.native());
                    r.vec(1) = _mm512_cvtepi16_epi64(a1.native());
                    return r;
#else
                    int64<16> r;
                    int16<8> a0, a1;
                    split(a, a0, a1);
                    r.vec(0) = _mm256_cvtepi16_epi64(a0.native());
                    r.vec(1) = _mm256_cvtepi16_epi64(move8_l<4>(a0).eval().native());
                    r.vec(2) = _mm256_cvtepi16_epi64(a1.native());
                    r.vec(3) = _mm256_cvtepi16_epi64(move8_l<4>(a1).eval().native());
                    return r;
#endif
                }
#endif

#if SIMD_USE_AVX512F
                static inline int64<32> i_to_int64(const int16<32> &a) {
                    int64<32> r;
                    int16<16> a01, a23;
                    int16<8> a0, a1, a2, a3;
#if SIMD_USE_AVX512BW
                    split(a, a01, a23);
#else
                    a01 = a.vec(0);
                    a23 = a.vec(1);
#endif
                    split(a01, a0, a1);
                    split(a23, a2, a3);

                    r.vec(0) = _mm512_cvtepi16_epi64(a0.native());
                    r.vec(1) = _mm512_cvtepi16_epi64(a1.native());
                    r.vec(2) = _mm512_cvtepi16_epi64(a2.native());
                    r.vec(3) = _mm512_cvtepi16_epi64(a3.native());
                    return r;
                }
#endif

                template <unsigned N> inline int64<N> i_to_int64(const int16<N> &a) {
                    SIMD_VEC_ARRAY_IMPL_CONV_INSERT(int64<N>, i_to_int64, a)
                }

                // -----------------------------------------------------------------------------

                static inline int64<16> i_to_int64(const int8<16> &a) {
#if SIMD_USE_NULL
                    int64<16> r;
                    for (unsigned i = 0; i < 16; i++) {
                        r.vec(i / 2).el(i % 2) = int64_t(a.vec(0).el(i));
                    }
                    return r;
#elif SIMD_USE_AVX512F
                    int64<16> r;
                    r.vec(0) = _mm512_cvtepi8_epi64(a.native());
                    r.vec(1) = _mm512_cvtepi8_epi64(move16_l<8>(a).eval().native());
                    return r;
#elif SIMD_USE_AVX2
                    int64<16> r;
                    r.vec(0) = _mm256_cvtepi8_epi64(a.native());
                    r.vec(1) = _mm256_cvtepi8_epi64(move16_l<4>(a).eval().native());
                    r.vec(2) = _mm256_cvtepi8_epi64(move16_l<8>(a).eval().native());
                    r.vec(3) = _mm256_cvtepi8_epi64(move16_l<12>(a).eval().native());
                    return r;
#elif SIMD_USE_SSE4_1
                    int64<16> r;
                    r.vec(0) = _mm_cvtepi8_epi64(a.native());
                    r.vec(1) = _mm_cvtepi8_epi64(move16_l<2>(a).eval().native());
                    r.vec(2) = _mm_cvtepi8_epi64(move16_l<4>(a).eval().native());
                    r.vec(3) = _mm_cvtepi8_epi64(move16_l<6>(a).eval().native());
                    r.vec(4) = _mm_cvtepi8_epi64(move16_l<8>(a).eval().native());
                    r.vec(5) = _mm_cvtepi8_epi64(move16_l<10>(a).eval().native());
                    r.vec(6) = _mm_cvtepi8_epi64(move16_l<12>(a).eval().native());
                    r.vec(7) = _mm_cvtepi8_epi64(move16_l<14>(a).eval().native());
                    return r;
#elif SIMD_USE_SSE2 || SIMD_USE_NEON || SIMD_USE_MSA || SIMD_USE_VSX_207
                    return i_to_int64(i_to_int32(a));
#elif SIMD_USE_ALTIVEC
                    int64<16> r;
                    mem_block<int8<16>> b = a;
                    for (unsigned i = 0; i < 16; i++) {
                        r.vec(i / 2).el(i % 2) = int64_t(b[i]);
                    }
                    return r;
#endif
                }

#if SIMD_USE_AVX2
                static inline int64<32> i_to_int64(const int8<32> &a) {
#if SIMD_USE_AVX512F
                    int64<32> r;
                    int8<16> a0, a1;
                    split(a, a0, a1);
                    r.vec(0) = _mm512_cvtepi8_epi64(a0.native());
                    r.vec(1) = _mm512_cvtepi8_epi64(move16_l<8>(a0).eval().native());
                    r.vec(2) = _mm512_cvtepi8_epi64(a1.native());
                    r.vec(3) = _mm512_cvtepi8_epi64(move16_l<8>(a1).eval().native());
                    return r;
#else
                    int64<32> r;
                    int8<16> a0, a1;
                    split(a, a0, a1);
                    r.vec(0) = _mm256_cvtepi8_epi64(a0.native());
                    r.vec(1) = _mm256_cvtepi8_epi64(move16_l<4>(a0).eval().native());
                    r.vec(2) = _mm256_cvtepi8_epi64(move16_l<8>(a0).eval().native());
                    r.vec(3) = _mm256_cvtepi8_epi64(move16_l<12>(a0).eval().native());
                    r.vec(4) = _mm256_cvtepi8_epi64(a1.native());
                    r.vec(5) = _mm256_cvtepi8_epi64(move16_l<4>(a1).eval().native());
                    r.vec(6) = _mm256_cvtepi8_epi64(move16_l<8>(a1).eval().native());
                    r.vec(7) = _mm256_cvtepi8_epi64(move16_l<12>(a1).eval().native());
                    return r;
#endif
                }
#endif

#if SIMD_USE_AVX512F
                static inline int64<64> i_to_int64(const int8<64> &a) {
                    int64<64> r;
                    int8<32> a01, a23;
                    int8<16> a0, a1, a2, a3;
#if SIMD_USE_AVX512BW
                    split(a, a01, a23);
#else
                    a01 = a.vec(0);
                    a23 = a.vec(1);
#endif
                    split(a01, a0, a1);
                    split(a23, a2, a3);

                    r.vec(0) = _mm512_cvtepi8_epi64(a0.native());
                    r.vec(1) = _mm512_cvtepi8_epi64(move16_l<8>(a0).eval().native());
                    r.vec(2) = _mm512_cvtepi8_epi64(a1.native());
                    r.vec(3) = _mm512_cvtepi8_epi64(move16_l<8>(a1).eval().native());
                    r.vec(4) = _mm512_cvtepi8_epi64(a2.native());
                    r.vec(5) = _mm512_cvtepi8_epi64(move16_l<8>(a2).eval().native());
                    r.vec(6) = _mm512_cvtepi8_epi64(a3.native());
                    r.vec(7) = _mm512_cvtepi8_epi64(move16_l<8>(a3).eval().native());
                    return r;
                }
#endif

                template <unsigned N> inline int64<N> i_to_int64(const int8<N> &a) {
                    SIMD_VEC_ARRAY_IMPL_CONV_INSERT(int64<N>, i_to_int64, a)
                }

                // -----------------------------------------------------------------------------

            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
