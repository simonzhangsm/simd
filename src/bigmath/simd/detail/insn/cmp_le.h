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

#ifndef SIMD_DETAIL_INSN_CMP_LE_H
#define SIMD_DETAIL_INSN_CMP_LE_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/core/make_shuffle_bytes_mask.h>
#include <bigmath/simd/detail/null/compare.h>
#include <bigmath/simd/detail/insn/bit_not.h>
#include <bigmath/simd/detail/insn/cmp_gt.h>
#include <bigmath/simd/detail/vector_array_macros.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {

                inline mask_int8<16> i_cmp_le(const int8<16> &a, const int8<16> &b) {
#if SIMD_USE_NULL
                    return detail::null::cmp_le(a, b);
#elif SIMD_USE_AVX512VL
                    return _mm_cmple_epi8_mask(a.native(), b.native());
#elif SIMD_USE_NEON
                    return vcleq_s8(a.native(), b.native());
#elif SIMD_USE_MSA
                    return (v16u8)__msa_cle_s_b(a.native(), b.native());
#else
                    return i_bit_not(i_cmp_gt(a, b));
#endif
                }

#if SIMD_USE_AVX2
                inline mask_int8<32> i_cmp_le(const int8<32> &a, const int8<32> &b) {
#if SIMD_USE_AVX512VL
                    return _mm256_cmple_epi8_mask(a.native(), b.native());
#else
                    return i_bit_not(i_cmp_gt(a, b));
#endif
                }
#endif

#if SIMD_USE_AVX512BW
                inline mask_int8<64> i_cmp_le(const int8<64> &a, const int8<64> &b) {
                    return _mm512_cmple_epi8_mask(a.native(), b.native());
                }
#endif

                // -----------------------------------------------------------------------------

                inline mask_int8<16> i_cmp_le(const uint8<16> &ca, const uint8<16> &cb) {
                    uint8<16> a = ca, b = cb;
#if SIMD_USE_NULL
                    return detail::null::cmp_le(a, b);
#elif SIMD_USE_AVX512VL
                    return _mm_cmple_epu8_mask(a.native(), b.native());
#elif SIMD_USE_XOP && !SIMD_WORKAROUND_XOP_COM
                    return _mm_comle_epu8(a.native(), b.native());
#elif SIMD_USE_NEON
                    return vcleq_u8(a.native(), b.native());
#elif SIMD_USE_MSA
                    return (v16u8)__msa_cle_u_b(a.native(), b.native());
#else
                    return i_bit_not(i_cmp_gt(a, b));
#endif
                }

#if SIMD_USE_AVX2
                inline mask_int8<32> i_cmp_le(const uint8<32> &a, const uint8<32> &b) {
#if SIMD_USE_AVX512VL
                    return _mm256_cmple_epu8_mask(a.native(), b.native());
#else
                    return i_bit_not(i_cmp_gt(a, b));
#endif
                }
#endif

#if SIMD_USE_AVX512BW
                inline mask_int8<64> i_cmp_le(const uint8<64> &a, const uint8<64> &b) {
                    return _mm512_cmple_epu8_mask(a.native(), b.native());
                }
#endif

                // -----------------------------------------------------------------------------

                inline mask_int16<8> i_cmp_le(const int16<8> &a, const int16<8> &b) {
#if SIMD_USE_NULL
                    return detail::null::cmp_le(a, b);
#elif SIMD_USE_AVX512VL
                    return _mm_cmple_epi16_mask(a.native(), b.native());
#elif SIMD_USE_NEON
                    return vcleq_s16(a.native(), b.native());
#elif SIMD_USE_MSA
                    return (v8u16)__msa_cle_s_h(a.native(), b.native());
#else
                    return i_bit_not(i_cmp_gt(a, b));
#endif
                }

#if SIMD_USE_AVX2
                inline mask_int16<16> i_cmp_le(const int16<16> &a, const int16<16> &b) {
#if SIMD_USE_AVX512VL
                    return _mm256_cmple_epi16_mask(a.native(), b.native());
#else
                    return i_bit_not(i_cmp_gt(a, b));
#endif
                }
#endif

#if SIMD_USE_AVX512BW
                inline mask_int16<32> i_cmp_le(const int16<32> &a, const int16<32> &b) {
                    return _mm512_cmple_epi16_mask(a.native(), b.native());
                }
#endif

                // -----------------------------------------------------------------------------

                inline mask_int16<8> i_cmp_le(const uint16<8> &ca, const uint16<8> &cb) {
                    uint16<8> a = ca, b = cb;
#if SIMD_USE_NULL
                    return detail::null::cmp_le(a, b);
#elif SIMD_USE_AVX512VL
                    return _mm_cmple_epu16_mask(a.native(), b.native());
#elif SIMD_USE_XOP && !SIMD_WORKAROUND_XOP_COM
                    return _mm_comle_epu16(a.native(), b.native());
#elif SIMD_USE_NEON
                    return vcleq_u16(a.native(), b.native());
#elif SIMD_USE_MSA
                    return (v8u16)__msa_cle_u_h(a.native(), b.native());
#else
                    return i_bit_not(i_cmp_gt(a, b));
#endif
                }

#if SIMD_USE_AVX2
                inline mask_int16<16> i_cmp_le(const uint16<16> &a, const uint16<16> &b) {
#if SIMD_USE_AVX512VL
                    return _mm256_cmple_epu16_mask(a.native(), b.native());
#else
                    return i_bit_not(i_cmp_gt(a, b));
#endif
                }
#endif

#if SIMD_USE_AVX512BW
                inline mask_int16<32> i_cmp_le(const uint16<32> &a, const uint16<32> &b) {
                    return _mm512_cmple_epu16_mask(a.native(), b.native());
                }
#endif

                // -----------------------------------------------------------------------------

                inline mask_int32<4> i_cmp_le(const int32<4> &a, const int32<4> &b) {
#if SIMD_USE_NULL
                    return detail::null::cmp_le(a, b);
#elif SIMD_USE_AVX512VL
                    return _mm_cmple_epi32_mask(a.native(), b.native());
#elif SIMD_USE_NEON
                    return vcleq_s32(a.native(), b.native());
#elif SIMD_USE_MSA
                    return (v4u32)__msa_cle_s_w(a.native(), b.native());
#else
                    return i_bit_not(i_cmp_gt(a, b));
#endif
                }

#if SIMD_USE_AVX2
                inline mask_int32<8> i_cmp_le(const int32<8> &a, const int32<8> &b) {
#if SIMD_USE_AVX512VL
                    return _mm256_cmple_epi32_mask(a.native(), b.native());
#else
                    return i_bit_not(i_cmp_gt(a, b));
#endif
                }
#endif

#if SIMD_USE_AVX512F
                inline mask_int32<16> i_cmp_le(const int32<16> &a, const int32<16> &b) {
                    return _mm512_cmple_epi32_mask(a.native(), b.native());
                }
#endif

                // -----------------------------------------------------------------------------

                inline mask_int32<4> i_cmp_le(const uint32<4> &ca, const uint32<4> &cb) {
                    uint32<4> a = ca, b = cb;
#if SIMD_USE_NULL
                    return detail::null::cmp_le(a, b);
#elif SIMD_USE_AVX512VL
                    return _mm_cmple_epu32_mask(a.native(), b.native());
#elif SIMD_USE_XOP && !SIMD_WORKAROUND_XOP_COM
                    return _mm_comle_epu32(a.native(), b.native());
#elif SIMD_USE_NEON
                    return vcleq_u32(a.native(), b.native());
#elif SIMD_USE_MSA
                    return (v4u32)__msa_cle_u_w(a.native(), b.native());
#else
                    return i_bit_not(i_cmp_gt(a, b));
#endif
                }

#if SIMD_USE_AVX2
                inline mask_int32<8> i_cmp_le(const uint32<8> &a, const uint32<8> &b) {
#if SIMD_USE_AVX512VL
                    return _mm256_cmple_epu32_mask(a.native(), b.native());
#else
                    return i_bit_not(i_cmp_gt(a, b));
#endif
                }
#endif

#if SIMD_USE_AVX512F
                inline mask_int32<16> i_cmp_le(const uint32<16> &a, const uint32<16> &b) {
                    return _mm512_cmple_epu32_mask(a.native(), b.native());
                }
#endif

                // -----------------------------------------------------------------------------

                inline mask_int64<2> i_cmp_le(const int64<2> &a, const int64<2> &b) {
#if SIMD_USE_NULL
                    return detail::null::cmp_le(a, b);
#elif SIMD_USE_AVX512VL
                    return _mm_cmple_epi64_mask(a.native(), b.native());
#elif SIMD_USE_XOP && !SIMD_WORKAROUND_XOP_COM
                    return _mm_comle_epi64(a.native(), b.native());
#elif SIMD_USE_NEON64
                    return vcleq_s64(a.native(), b.native());
#elif SIMD_USE_MSA
                    return (v2u64)__msa_cle_s_d(a.native(), b.native());
#else
                    return i_bit_not(i_cmp_gt(a, b));
#endif
                }

#if SIMD_USE_AVX2
                inline mask_int64<4> i_cmp_le(const int64<4> &a, const int64<4> &b) {
#if SIMD_USE_AVX512VL
                    return _mm256_cmple_epi64_mask(a.native(), b.native());
#else
                    return i_bit_not(i_cmp_gt(a, b));
#endif
                }
#endif

#if SIMD_USE_AVX512F
                inline mask_int64<8> i_cmp_le(const int64<8> &a, const int64<8> &b) {
                    return _mm512_cmple_epi64_mask(a.native(), b.native());
                }
#endif

                // -----------------------------------------------------------------------------

                inline mask_int64<2> i_cmp_le(const uint64<2> &a, const uint64<2> &b) {
#if SIMD_USE_AVX512VL
                    return _mm_cmple_epu64_mask(a.native(), b.native());
#elif SIMD_USE_XOP && !SIMD_WORKAROUND_XOP_COM
                    return _mm_comle_epu64(a.native(), b.native());
#elif SIMD_USE_NEON64
                    return vcleq_u64(a.native(), b.native());
#elif SIMD_USE_MSA
                    return (v2u64)__msa_cle_u_d(a.native(), b.native());
#elif SIMD_USE_NULL
                    return detail::null::cmp_le(a, b);
#else
                    return i_bit_not(i_cmp_gt(a, b));
#endif
                }

#if SIMD_USE_AVX2
                inline mask_int64<4> i_cmp_le(const uint64<4> &a, const uint64<4> &b) {
#if SIMD_USE_AVX512VL
                    return _mm256_cmple_epu64_mask(a.native(), b.native());
#else
                    return i_bit_not(i_cmp_gt(a, b));
#endif
                }
#endif

#if SIMD_USE_AVX512F
                inline mask_int64<8> i_cmp_le(const uint64<8> &a, const uint64<8> &b) {
                    return _mm512_cmple_epu64_mask(a.native(), b.native());
                }
#endif

                // -----------------------------------------------------------------------------

                static inline mask_float32<4> i_cmp_le(const float32<4> &a, const float32<4> &b) {
#if SIMD_USE_NULL || SIMD_USE_NEON_NO_FLT_SP
                    return detail::null::cmp_le(a, b);
#elif SIMD_USE_AVX512VL
                    return _mm_cmp_ps_mask(a.native(), b.native(), _CMP_LE_OQ);
#elif SIMD_USE_AVX
                    return _mm_cmp_ps(a.native(), b.native(), _CMP_LE_OQ);
#elif SIMD_USE_SSE2
                    return _mm_cmple_ps(a.native(), b.native());
#elif SIMD_USE_NEON
                    return vreinterpretq_f32_u32(vcleq_f32(a.native(), b.native()));
#elif SIMD_USE_ALTIVEC
                    return vec_cmple(a.native(), b.native());
#elif SIMD_USE_MSA
                    return (v4f32)__msa_fcle_w(a.native(), b.native());
#endif
                }

#if SIMD_USE_AVX
                static inline mask_float32<8> i_cmp_le(const float32<8> &a, const float32<8> &b) {
#if SIMD_USE_AVX512VL
                    return _mm256_cmp_ps_mask(a.native(), b.native(), _CMP_LE_OQ);
#else
                    return _mm256_cmp_ps(a.native(), b.native(), _CMP_LE_OQ);
#endif
                }
#endif

#if SIMD_USE_AVX512F
                static inline mask_float32<16> i_cmp_le(const float32<16> &a, const float32<16> &b) {
                    return _mm512_cmp_ps_mask(a.native(), b.native(), _CMP_LE_OQ);
                }
#endif

                // -----------------------------------------------------------------------------

                static inline mask_float64<2> i_cmp_le(const float64<2> &a, const float64<2> &b) {
#if SIMD_USE_AVX512VL
                    return _mm_cmp_pd_mask(a.native(), b.native(), _CMP_LE_OQ);
#elif SIMD_USE_AVX
                    return _mm_cmp_pd(a.native(), b.native(), _CMP_LE_OQ);
#elif SIMD_USE_SSE2
                    return _mm_cmple_pd(a.native(), b.native());
#elif SIMD_USE_NEON64
                    return vreinterpretq_f64_u64(vcleq_f64(a.native(), b.native()));
#elif SIMD_USE_VSX_206
                    return (__vector double)vec_cmple(a.native(), b.native());
#elif SIMD_USE_MSA
                    return (v2f64)__msa_fcle_d(a.native(), b.native());
#elif SIMD_USE_NULL || SIMD_USE_NEON32 || SIMD_USE_ALTIVEC
                    return detail::null::cmp_le(a, b);
#endif
                }

#if SIMD_USE_AVX
                static inline mask_float64<4> i_cmp_le(const float64<4> &a, const float64<4> &b) {
#if SIMD_USE_AVX512VL
                    return _mm256_cmp_pd_mask(a.native(), b.native(), _CMP_LE_OQ);
#else
                    return _mm256_cmp_pd(a.native(), b.native(), _CMP_LE_OQ);
#endif
                }
#endif

#if SIMD_USE_AVX512F
                static inline mask_float64<8> i_cmp_le(const float64<8> &a, const float64<8> &b) {
                    return _mm512_cmp_pd_mask(a.native(), b.native(), _CMP_LE_OQ);
                }
#endif

                // -----------------------------------------------------------------------------

                template <class V> inline typename V::mask_vector_type i_cmp_le(const V &a, const V &b) {
                    SIMD_VEC_ARRAY_IMPL2(typename V::mask_vector_type, i_cmp_le, a, b);
                }


            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
