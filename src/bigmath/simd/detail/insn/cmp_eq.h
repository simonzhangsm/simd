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

#ifndef SIMD_DETAIL_INSN_CMP_EQ_H
#define SIMD_DETAIL_INSN_CMP_EQ_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/core/make_shuffle_bytes_mask.h>
#include <bigmath/simd/core/bit_and.h>
#include <bigmath/simd/core/bit_or.h>
#include <bigmath/simd/core/i_shift_r.h>
#include <bigmath/simd/core/i_shift_l.h>
#include <bigmath/simd/core/transpose.h>
#include <bigmath/simd/detail/null/compare.h>
#include <bigmath/simd/detail/vector_array_macros.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {


                static inline mask_int8x16 i_cmp_eq(const uint8x16 &a, const uint8x16 &b) {
#if SIMD_USE_NULL
                    return detail::null::cmp_eq(a, b);
#elif SIMD_USE_AVX512VL
                    return _mm_cmpeq_epi8_mask(a.native(), b.native());
#elif SIMD_USE_SSE2
                    return _mm_cmpeq_epi8(a.native(), b.native());
#elif SIMD_USE_NEON
                    return vceqq_u8(a.native(), b.native());
#elif SIMD_USE_ALTIVEC
                    return vec_cmpeq(a.native(), b.native());
#elif SIMD_USE_MSA
                    return (v16u8)__msa_ceq_b((v16i8)a.native(), (v16i8)b.native());
#endif
                }

#if SIMD_USE_AVX512VL
                static inline mask_int8<16> i_cmp_eq(const mask_int8<16> &a, const mask_int8<16> &b) {
                    return _mm512_kxnor(a.native(), b.native());
                }
#endif

#if SIMD_USE_AVX2
                static inline mask_int8x32 i_cmp_eq(const uint8x32 &a, const uint8x32 &b) {
#if SIMD_USE_AVX512VL
                    return _mm256_cmpeq_epi8_mask(a.native(), b.native());
#else
                    return _mm256_cmpeq_epi8(a.native(), b.native());
#endif
                }
#endif

#if SIMD_USE_AVX512VL
                static inline mask_int8<32> i_cmp_eq(const mask_int8<32> &a, const mask_int8<32> &b) {
                    return _mm512_kxnor(a.native(), b.native());
                }
#endif

#if SIMD_USE_AVX512BW
                inline mask_int8<64> i_cmp_eq(const uint8<64> &a, const uint8<64> &b) {
                    return _mm512_cmpeq_epi8_mask(a.native(), b.native());
                }

                inline mask_int8<64> i_cmp_eq(const mask_int8<64> &a, const mask_int8<64> &b) {
                    return _mm512_kxnor(a.native(), b.native());
                }
#endif

                // -----------------------------------------------------------------------------

                static inline mask_int16x8 i_cmp_eq(const uint16x8 &a, const uint16x8 &b) {
#if SIMD_USE_NULL
                    return detail::null::cmp_eq(a, b);
#elif SIMD_USE_AVX512VL
                    return _mm_cmpeq_epi16_mask(a.native(), b.native());
#elif SIMD_USE_SSE2
                    return _mm_cmpeq_epi16(a.native(), b.native());
#elif SIMD_USE_NEON
                    return vceqq_u16(a.native(), b.native());
#elif SIMD_USE_ALTIVEC
                    return vec_cmpeq(a.native(), b.native());
#elif SIMD_USE_MSA
                    return (v8u16)__msa_ceq_h((v8i16)a.native(), (v8i16)b.native());
#endif
                }

#if SIMD_USE_AVX2
                static inline mask_int16x16 i_cmp_eq(const uint16x16 &a, const uint16x16 &b) {
#if SIMD_USE_AVX512VL
                    return _mm256_cmpeq_epi16_mask(a.native(), b.native());
#else
                    return _mm256_cmpeq_epi16(a.native(), b.native());
#endif
                }
#endif

#if SIMD_USE_AVX512BW
                inline mask_int16<32> i_cmp_eq(const uint16<32> &a, const uint16<32> &b) {
                    return _mm512_cmpeq_epi16_mask(a.native(), b.native());
                }
#endif

                // -----------------------------------------------------------------------------

                static inline mask_int32x4 i_cmp_eq(const uint32x4 &a, const uint32x4 &b) {
#if SIMD_USE_NULL
                    return detail::null::cmp_eq(a, b);
#elif SIMD_USE_AVX512VL
                    return _mm_cmpeq_epi32_mask(a.native(), b.native());
#elif SIMD_USE_SSE2
                    return _mm_cmpeq_epi32(a.native(), b.native());
#elif SIMD_USE_NEON
                    return vceqq_u32(a.native(), b.native());
#elif SIMD_USE_ALTIVEC
                    return vec_cmpeq(a.native(), b.native());
#elif SIMD_USE_MSA
                    return (v4u32)__msa_ceq_w((v4i32)a.native(), (v4i32)b.native());
#endif
                }

#if SIMD_USE_AVX512VL
                static inline mask_int16<8> i_cmp_eq(const mask_int16<8> &a, const mask_int16<8> &b) {
                    return _mm512_kxnor(a.native(), b.native());
                }
#endif

#if SIMD_USE_AVX2
                static inline mask_int32x8 i_cmp_eq(const uint32x8 &a, const uint32x8 &b) {
#if SIMD_USE_AVX512VL
                    return _mm256_cmpeq_epi32_mask(a.native(), b.native());
#else
                    return _mm256_cmpeq_epi32(a.native(), b.native());
#endif
                }
#endif

#if SIMD_USE_AVX512VL
                static inline mask_int16<16> i_cmp_eq(const mask_int16<16> &a, const mask_int16<16> &b) {
                    return _mm512_kxnor(a.native(), b.native());
                }
#endif

#if SIMD_USE_AVX512F
                static inline mask_int32<16> i_cmp_eq(const uint32<16> &a, const uint32<16> &b) {
                    return _mm512_cmpeq_epi32_mask(a.native(), b.native());
                }

                static inline mask_int32<16> i_cmp_eq(const mask_int32<16> &a, const mask_int32<16> &b) {
                    return _mm512_kxnor(a.native(), b.native());
                }
#endif

                // -----------------------------------------------------------------------------

                static inline mask_int64x2 i_cmp_eq(const uint64x2 &a, const uint64x2 &b) {
#if SIMD_USE_XOP && !SIMD_WORKAROUND_XOP_COM
                    return _mm_comeq_epi64(a.native(), b.native());
#elif SIMD_USE_AVX512VL
                    return _mm_cmpeq_epi64_mask(a.native(), b.native());
#elif SIMD_USE_SSE4_1
                    return _mm_cmpeq_epi64(a.native(), b.native());
#elif SIMD_USE_SSE2
                    uint64x2 r32, r32s;
                    r32 = i_cmp_eq(uint32x4(a), uint32x4(b));
                    // swap the 32-bit halves
                    r32s = bit_or(shift_l<32>(r32), shift_r<32>(r32));
                    // combine the results. Each 32-bit half is ANDed with the neighbouring pair
                    r32 = bit_and(r32, r32s);
                    return r32;
#elif SIMD_USE_NEON64
                    return vceqq_u64(a.native(), b.native());
#elif SIMD_USE_NEON32
                    uint32x4 r32, r32s;
                    r32 = i_cmp_eq(uint32x4(a), uint32x4(b));
                    r32s = r32;
                    // swap the 32-bit halves
                    transpose2(r32, r32s);
                    // combine the results. Each 32-bit half is ANDed with the neighbouring pair
                    r32 = bit_and(r32, r32s);
                    return uint64x2(r32);
#elif SIMD_USE_VSX_207
                    return (__vector uint64_t)vec_cmpeq(a.native(), b.native());
#elif SIMD_USE_MSA
                    return (v2u64)__msa_ceq_d((v2i64)a.native(), (v2i64)b.native());
#elif SIMD_USE_NULL || SIMD_USE_ALTIVEC
                    return detail::null::cmp_eq(a, b);
#endif
                }

#if SIMD_USE_AVX512VL
                static inline mask_int64<2> i_cmp_eq(const mask_int64<2> &a, const mask_int64<2> &b) {
                    return _mm512_kxnor(a.native(), b.native());
                }
#endif

#if SIMD_USE_AVX2
                static inline mask_int64x4 i_cmp_eq(const uint64x4 &a, const uint64x4 &b) {
#if SIMD_USE_AVX512VL
                    return _mm256_cmpeq_epi64_mask(a.native(), b.native());
#else
                    return _mm256_cmpeq_epi64(a.native(), b.native());
#endif
                }
#endif

#if SIMD_USE_AVX512VL
                static inline mask_int64<4> i_cmp_eq(const mask_int64<4> &a, const mask_int64<4> &b) {
                    return _mm512_kxnor(a.native(), b.native());
                }
#endif

#if SIMD_USE_AVX512F
                static inline mask_int64<8> i_cmp_eq(const uint64<8> &a, const uint64<8> &b) {
                    return _mm512_cmpeq_epi64_mask(a.native(), b.native());
                }

                static inline mask_int64<8> i_cmp_eq(const mask_int64<8> &a, const mask_int64<8> &b) {
                    return _mm512_kxnor(a.native(), b.native());
                }
#endif

                // -----------------------------------------------------------------------------

                static inline mask_float32x4 i_cmp_eq(const float32x4 &a, const float32x4 &b) {
#if SIMD_USE_NULL || SIMD_USE_NEON_NO_FLT_SP
                    return detail::null::cmp_eq(a, b);
#elif SIMD_USE_AVX512VL
                    return _mm_cmp_ps_mask(a.native(), b.native(), _CMP_EQ_OQ);
#elif SIMD_USE_AVX
                    return _mm_cmp_ps(a.native(), b.native(), _CMP_EQ_OQ);
#elif SIMD_USE_SSE2
                    return _mm_cmpeq_ps(a.native(), b.native());
#elif SIMD_USE_NEON
                    return vreinterpretq_f32_u32(vceqq_f32(a.native(), b.native()));
#elif SIMD_USE_ALTIVEC
                    return vec_cmpeq(a.native(), b.native());
#elif SIMD_USE_MSA
                    return (v4f32)__msa_fceq_w(a.native(), b.native());
#endif
                }

#if SIMD_USE_AVX512VL
                static inline mask_float32<4> i_cmp_eq(const mask_float32<4> &a, const mask_float32<4> &b) {
                    return _mm512_kxnor(a.native(), b.native());
                }
#endif


#if SIMD_USE_AVX
                static inline mask_float32x8 i_cmp_eq(const float32x8 &a, const float32x8 &b) {
#if SIMD_USE_AVX512VL
                    return _mm256_cmp_ps_mask(a.native(), b.native(), _CMP_EQ_OQ);
#else
                    return _mm256_cmp_ps(a.native(), b.native(), _CMP_EQ_OQ);
#endif
                }
#endif

#if SIMD_USE_AVX512VL
                static inline mask_float32<8> i_cmp_eq(const mask_float32<8> &a, const mask_float32<8> &b) {
                    return _mm512_kxnor(a.native(), b.native());
                }
#endif

#if SIMD_USE_AVX512F
                static inline mask_float32<16> i_cmp_eq(const float32<16> &a, const float32<16> &b) {
                    return _mm512_cmp_ps_mask(a.native(), b.native(), _CMP_EQ_OQ);
                }

                static inline mask_float32<16> i_cmp_eq(const mask_float32<16> &a, const mask_float32<16> &b) {
                    return _mm512_kxnor(a.native(), b.native());
                }
#endif

                // -----------------------------------------------------------------------------

                static inline mask_float64x2 i_cmp_eq(const float64x2 &a, const float64x2 &b) {
#if SIMD_USE_AVX512VL
                    return _mm_cmp_pd_mask(a.native(), b.native(), _CMP_EQ_OQ);
#elif SIMD_USE_AVX
                    return _mm_cmp_pd(a.native(), b.native(), _CMP_EQ_OQ);
#elif SIMD_USE_SSE2
                    return _mm_cmpeq_pd(a.native(), b.native());
#elif SIMD_USE_NEON64
                    return vreinterpretq_f64_u64(vceqq_f64(a.native(), b.native()));
#elif SIMD_USE_VSX_206
                    return (__vector double)vec_cmpeq(a.native(), b.native());
#elif SIMD_USE_MSA
                    return (v2f64)__msa_fceq_d(a.native(), b.native());
#elif SIMD_USE_NULL || SIMD_USE_NEON32 || SIMD_USE_ALTIVEC
                    return detail::null::cmp_eq(a, b);
#else
                    return SIMD_NOT_IMPLEMENTED2(a, b);
#endif
                }

#if SIMD_USE_AVX512VL
                static inline mask_float64<2> i_cmp_eq(const mask_float64<2> &a, const mask_float64<2> &b) {
                    return _mm512_kxnor(a.native(), b.native());
                }
#endif


#if SIMD_USE_AVX
                static inline mask_float64x4 i_cmp_eq(const float64x4 &a, const float64x4 &b) {
#if SIMD_USE_AVX512VL
                    return _mm256_cmp_pd_mask(a.native(), b.native(), _CMP_EQ_OQ);
#else
                    return _mm256_cmp_pd(a.native(), b.native(), _CMP_EQ_OQ);
#endif
                }
#endif

#if SIMD_USE_AVX512VL
                static inline mask_float64<4> i_cmp_eq(const mask_float64<4> &a, const mask_float64<4> &b) {
                    return _mm512_kxnor(a.native(), b.native());
                }
#endif

#if SIMD_USE_AVX512F
                static inline mask_float64<8> i_cmp_eq(const float64<8> &a, const float64<8> &b) {
                    return _mm512_cmp_pd_mask(a.native(), b.native(), _CMP_EQ_OQ);
                }

                static inline mask_float64<8> i_cmp_eq(const mask_float64<8> &a, const mask_float64<8> &b) {
                    return _mm512_kxnor(a.native(), b.native());
                }
#endif

                // -----------------------------------------------------------------------------

                template <class V> inline typename V::mask_vector_type i_cmp_eq(const V &a, const V &b) {
                    SIMD_VEC_ARRAY_IMPL2(typename V::mask_vector_type, i_cmp_eq, a, b);
                }

            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
