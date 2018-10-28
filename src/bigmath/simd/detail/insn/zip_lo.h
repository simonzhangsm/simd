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

#ifndef SIMD_DETAIL_INSN_ZIP_LO_H
#define SIMD_DETAIL_INSN_ZIP_LO_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/core/shuffle_bytes16.h>
#include <bigmath/simd/detail/null/shuffle.h>
#include <bigmath/simd/detail/neon/shuffle.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {

                static inline uint8x16 i_zip16_lo(const uint8x16 &a, const uint8x16 &b) {
#if SIMD_USE_NULL
                    return detail::null::zip16_lo(a, b);
#elif SIMD_USE_SSE2
                    return _mm_unpacklo_epi8(a.native(), b.native());
#elif SIMD_USE_NEON
                    // the compiler will optimize multiple vzip instructions if both zip_lo
                    // and zip_hi are used on the same arguments
                    return vzipq_u8(a.native(), b.native()).val[0];
#elif SIMD_USE_ALTIVEC
                    return vec_mergeh(a.native(), b.native());
#elif SIMD_USE_MSA
                    return (v16u8)__msa_ilvr_b((v16i8)b.native(), (v16i8)a.native());
#endif
                }

#if SIMD_USE_AVX2
                static inline uint8x32 i_zip16_lo(const uint8x32 &a, const uint8x32 &b) {
                    return _mm256_unpacklo_epi8(a.native(), b.native());
                }
#endif

#if SIMD_USE_AVX512BW
                inline uint8<64> i_zip16_lo(const uint8<64> &a, const uint8<64> &b) {
                    return _mm512_unpacklo_epi8(a.native(), b.native());
                }
#endif

                template <unsigned N> inline uint8<N> i_zip16_lo(const uint8<N> &a, const uint8<N> &b) {
                    SIMD_VEC_ARRAY_IMPL2(uint8<N>, i_zip16_lo, a, b)
                }

                // -----------------------------------------------------------------------------

                static inline uint16x8 i_zip8_lo(const uint16x8 &a, const uint16x8 &b) {
#if SIMD_USE_NULL
                    return detail::null::zip8_lo(a, b);
#elif SIMD_USE_SSE2
                    return _mm_unpacklo_epi16(a.native(), b.native());
#elif SIMD_USE_NEON
                    return vzipq_u16(a.native(), b.native()).val[0];
#elif SIMD_USE_ALTIVEC
                    return vec_mergeh(a.native(), b.native());
#elif SIMD_USE_MSA
                    return (v8u16)__msa_ilvr_h((v8i16)b.native(), (v8i16)a.native());
#endif
                }

#if SIMD_USE_AVX2
                static inline uint16x16 i_zip8_lo(const uint16x16 &a, const uint16x16 &b) {
                    return _mm256_unpacklo_epi16(a.native(), b.native());
                }
#endif

#if SIMD_USE_AVX512BW
                inline uint16<32> i_zip8_lo(const uint16<32> &a, const uint16<32> &b) {
                    return _mm512_unpacklo_epi16(a.native(), b.native());
                }
#endif

                template <unsigned N> inline uint16<N> i_zip8_lo(const uint16<N> &a, const uint16<N> &b) {
                    SIMD_VEC_ARRAY_IMPL2(uint16<N>, i_zip8_lo, a, b)
                }

                // -----------------------------------------------------------------------------

                static inline uint32x4 i_zip4_lo(const uint32x4 &a, const uint32x4 &b) {
#if SIMD_USE_NULL
                    return detail::null::zip4_lo(a, b);
#elif SIMD_USE_SSE2
                    return _mm_unpacklo_epi32(a.native(), b.native());
#elif SIMD_USE_NEON
                    return vzipq_u32(a.native(), b.native()).val[0];
#elif SIMD_USE_ALTIVEC
                    return vec_mergeh(a.native(), b.native());
#elif SIMD_USE_MSA
                    return (v4u32)__msa_ilvr_w((v4i32)b.native(), (v4i32)a.native());
#endif
                }

#if SIMD_USE_AVX2
                static inline uint32x8 i_zip4_lo(const uint32x8 &a, const uint32x8 &b) {
                    return _mm256_unpacklo_epi32(a.native(), b.native());
                }
#endif

#if SIMD_USE_AVX512F
                static inline uint32<16> i_zip4_lo(const uint32<16> &a, const uint32<16> &b) {
                    return _mm512_unpacklo_epi32(a.native(), b.native());
                }
#endif

                template <unsigned N> inline uint32<N> i_zip4_lo(const uint32<N> &a, const uint32<N> &b) {
                    SIMD_VEC_ARRAY_IMPL2(uint32<N>, i_zip4_lo, a, b)
                }

                // -----------------------------------------------------------------------------

                static inline uint64x2 i_zip2_lo(const uint64x2 &a, const uint64x2 &b) {
#if SIMD_USE_SSE2
                    return _mm_unpacklo_epi64(a.native(), b.native());
#elif SIMD_USE_NEON
                    return neon::zip2_lo(a, b);
#elif SIMD_USE_VSX_207
                    return vec_mergeh(a.native(), b.native());
#elif SIMD_USE_MSA
                    return (v2u64)__msa_ilvr_d((v2i64)b.native(), (v2i64)a.native());
#elif SIMD_USE_NULL || SIMD_USE_ALTIVEC
                    return detail::null::zip2_lo(a, b);
#endif
                }

#if SIMD_USE_AVX2
                static inline uint64x4 i_zip2_lo(const uint64x4 &a, const uint64x4 &b) {
                    return _mm256_unpacklo_epi64(a.native(), b.native());
                }
#endif

#if SIMD_USE_AVX512F
                static inline uint64<8> i_zip2_lo(const uint64<8> &a, const uint64<8> &b) {
                    return _mm512_unpacklo_epi64(a.native(), b.native());
                }
#endif

                template <unsigned N> inline uint64<N> i_zip2_lo(const uint64<N> &a, const uint64<N> &b) {
                    SIMD_VEC_ARRAY_IMPL2(uint64<N>, i_zip2_lo, a, b)
                }

                // -----------------------------------------------------------------------------

                static inline float32x4 i_zip4_lo(const float32x4 &a, const float32x4 &b) {
#if SIMD_USE_NULL || SIMD_USE_NEON_NO_FLT_SP
                    return detail::null::zip4_lo(a, b);
#elif SIMD_USE_SSE2
                    return _mm_unpacklo_ps(a.native(), b.native());
#elif SIMD_USE_NEON
                    return vzipq_f32(a.native(), b.native()).val[0];
#elif SIMD_USE_ALTIVEC
                    return vec_mergeh(a.native(), b.native());
#elif SIMD_USE_MSA
                    return (v4f32)__msa_ilvr_w((v4i32)b.native(), (v4i32)a.native());
#endif
                }

#if SIMD_USE_AVX
                static inline float32x8 i_zip4_lo(const float32x8 &a, const float32x8 &b) {
                    return _mm256_unpacklo_ps(a.native(), b.native());
                }
#endif

#if SIMD_USE_AVX512F
                static inline float32<16> i_zip4_lo(const float32<16> &a, const float32<16> &b) {
                    return _mm512_unpacklo_ps(a.native(), b.native());
                }
#endif

                template <unsigned N> inline float32<N> i_zip4_lo(const float32<N> &a, const float32<N> &b) {
                    SIMD_VEC_ARRAY_IMPL2(float32<N>, i_zip4_lo, a, b)
                }

                // -----------------------------------------------------------------------------

                static inline float64x2 i_zip2_lo(const float64x2 &a, const float64x2 &b) {
#if SIMD_USE_SSE2
                    return _mm_castps_pd(_mm_movelh_ps(_mm_castpd_ps(a.native()), _mm_castpd_ps(b.native())));
#elif SIMD_USE_NEON64
                    return vtrn1q_f64(a.native(), b.native());
#elif SIMD_USE_VSX_206
                    return (__vector double)vec_mergeh((__vector uint64_t)a.native(), (__vector uint64_t)b.native());
#elif SIMD_USE_MSA
                    return (v2f64)__msa_ilvr_d((v2i64)b.native(), (v2i64)a.native());
#elif SIMD_USE_NULL || SIMD_USE_ALTIVEC || SIMD_USE_NEON
                    return detail::null::zip2_lo(a, b);
#endif
                }

#if SIMD_USE_AVX
                static inline float64x4 i_zip2_lo(const float64x4 &a, const float64x4 &b) {
                    return _mm256_unpacklo_pd(a.native(), b.native());
                }
#endif

#if SIMD_USE_AVX512F
                static inline float64<8> i_zip2_lo(const float64<8> &a, const float64<8> &b) {
                    return _mm512_unpacklo_pd(a.native(), b.native());
                }
#endif

                template <unsigned N> inline float64<N> i_zip2_lo(const float64<N> &a, const float64<N> &b) {
                    SIMD_VEC_ARRAY_IMPL2(float64<N>, i_zip2_lo, a, b)
                }


            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
