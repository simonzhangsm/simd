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

#ifndef SIMD_DETAIL_INSN_SET_SPLAT_H
#define SIMD_DETAIL_INSN_SET_SPLAT_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/core/load.h>
#include <bigmath/simd/core/zip_lo.h>
#include <bigmath/simd/detail/altivec/load1.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {

                static inline void i_set_splat(uint32x4 &, uint32_t);

                static inline void i_set_splat(uint8x16 &v, uint8_t v0) {
#if SIMD_USE_NULL
                    v = detail::null::make_vec<uint8x16>(v0);
#elif SIMD_USE_AVX2
                    uint32_t u0 = v0;
                    v = _mm_cvtsi32_si128(u0);
                    v = _mm_broadcastb_epi8(v.native());
#elif SIMD_USE_SSE2
                    uint32_t u0;
                    u0 = v0 * 0x01010101;
                    uint32x4 u;
                    i_set_splat(u, u0);
                    v = u;
#elif SIMD_USE_NEON
                    v = vdupq_n_u8(v0);
#elif SIMD_USE_ALTIVEC
                    SIMDALIGN(16) uint8_t rv[16];
                    rv[0] = v0;
                    v = altivec::load1(v, rv);
                    v = splat<0>(v);
#elif SIMD_USE_MSA
                    v = (v16u8)__msa_fill_b(v0);
#endif
                }

#if SIMD_USE_AVX2
                static inline void i_set_splat(uint8x32 &v, uint8_t v0) {
                    uint8x16 a = _mm_cvtsi32_si128(v0);
                    v = _mm256_broadcastb_epi8(a.native());
                }
#endif

#if SIMD_USE_AVX512BW
                inline void i_set_splat(uint8<64> &v, uint8_t v0) {
                    uint8x16 a = _mm_cvtsi32_si128(v0);
                    v = _mm512_broadcastb_epi8(a.native());
                }
#endif

                template <unsigned N> inline void i_set_splat(uint8<N> &v, uint8_t v0) {
                    uint8v tv;
                    i_set_splat(tv, v0);
                    for (unsigned i = 0; i < v.vec_length; ++i) {
                        v.vec(i) = tv;
                    }
                }

                // -----------------------------------------------------------------------------

                static inline void i_set_splat(uint16x8 &v, uint16_t v0) {
#if SIMD_USE_NULL
                    v = detail::null::make_vec<uint16x8>(v0);
#elif SIMD_USE_AVX2
                    uint32_t u0 = v0;
                    v = _mm_cvtsi32_si128(u0);
                    v = _mm_broadcastw_epi16(v.native());
#elif SIMD_USE_SSE2
                    uint32_t u0;
                    u0 = v0 | v0 << 16;
                    uint32x4 u;
                    i_set_splat(u, u0);
                    v = u;
#elif SIMD_USE_NEON
                    v = vdupq_n_u16(v0);
#elif SIMD_USE_ALTIVEC
                    SIMDALIGN(16) uint16_t rv[8];
                    rv[0] = v0;
                    v = altivec::load1(v, rv);
                    v = splat<0>(v);
#elif SIMD_USE_MSA
                    v = (v8u16)__msa_fill_h(v0);
#endif
                }

#if SIMD_USE_AVX2
                static inline void i_set_splat(uint16x16 &v, uint16_t v0) {
                    uint16x8 a = _mm_cvtsi32_si128(v0);
                    v = _mm256_broadcastw_epi16(a.native());
                }
#endif

#if SIMD_USE_AVX512BW
                inline void i_set_splat(uint16<32> &v, uint16_t v0) {
                    uint16x8 a = _mm_cvtsi32_si128(v0);
                    v = _mm512_broadcastw_epi16(a.native());
                }
#endif

                template <unsigned N> inline void i_set_splat(uint16<N> &v, uint16_t v0) {
                    uint16v tv;
                    i_set_splat(tv, v0);
                    for (unsigned i = 0; i < v.vec_length; ++i) {
                        v.vec(i) = tv;
                    }
                }

                // -----------------------------------------------------------------------------

                static inline void i_set_splat(uint32x4 &v, uint32_t v0) {
#if SIMD_USE_NULL
                    v = detail::null::make_vec<uint32x4>(v0);
#elif SIMD_USE_AVX2
                    v = _mm_cvtsi32_si128(v0);
                    v = _mm_broadcastd_epi32(v.native());
#elif SIMD_USE_SSE2
                    v = _mm_cvtsi32_si128(v0);
                    v = permute4<0, 0, 0, 0>(v);
#elif SIMD_USE_NEON
                    v = vdupq_n_u32(v0);
#elif SIMD_USE_ALTIVEC
                    SIMDALIGN(16) uint32_t rv[4];
                    rv[0] = v0;
                    v = altivec::load1(v, rv);
                    v = splat<0>(v);
#elif SIMD_USE_MSA
                    v = (v4u32)__msa_fill_w(v0);
#endif
                }

#if SIMD_USE_AVX2
                static inline void i_set_splat(uint32x8 &v, uint32_t v0) {
                    uint32x4 a = _mm_cvtsi32_si128(v0);
                    v = _mm256_broadcastd_epi32(a.native());
                }
#endif

#if SIMD_USE_AVX512F
                static inline void i_set_splat(uint32<16> &v, uint32_t v0) {
                    v = _mm512_set1_epi32(v0);
                }
#endif

                template <unsigned N> inline void i_set_splat(uint32<N> &v, uint32_t v0) {
                    uint32v tv;
                    i_set_splat(tv, v0);
                    for (unsigned i = 0; i < v.vec_length; ++i) {
                        v.vec(i) = tv;
                    }
                }

                // -----------------------------------------------------------------------------

                static inline void i_set_splat(uint64x2 &v, uint64_t v0) {
#if SIMD_USE_SSE2
#if SIMD_32_BITS
                    uint32x4 va = _mm_cvtsi32_si128(uint32_t(v0));
                    uint32x4 vb = _mm_cvtsi32_si128(uint32_t(v0 >> 32));
                    v = zip4_lo(va, vb);
                    v = permute2<0, 0>(v);
#else
                    v = _mm_cvtsi64_si128(v0);
                    v = permute2<0, 0>(v);
#endif
#elif SIMD_USE_NEON
                    v = vdupq_n_u64(v0);
#elif SIMD_USE_VSX_207
                    SIMDALIGN(16) uint64_t rv[2];
                    rv[0] = v0;
                    v = vec_ld(0, reinterpret_cast<const __vector uint64_t *>(rv));
                    v = splat<0>(v);
#elif SIMD_USE_MSA
#if SIMD_64_BITS
                    v = (v2u64)__msa_fill_d(v0.native());
#else
                    uint32_t v0lo = v0;
                    uint32_t v0hi = v0 >> 32;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wuninitialized"
                    v4i32 vr;
                    vr = __msa_insert_w(vr, 0, v0lo);
                    vr = __msa_insert_w(vr, 1, v0hi);
#pragma GCC diagnostic pop
                    v = (int32<4>)vr;
                    v = (v2u64)__msa_splat_d((v2i64)v.native(), 0);
#endif
#elif SIMD_USE_NULL || SIMD_USE_ALTIVEC
                    v = detail::null::make_vec<uint64x2>(v0);
#endif
                }

#if SIMD_USE_AVX2
                static inline void i_set_splat(uint64x4 &v, uint64_t v0) {
#if SIMD_32_BITS
                    uint32x4 va = _mm_cvtsi32_si128(uint32_t(v0));
                    uint32x4 vb = _mm_cvtsi32_si128(uint32_t(v0 >> 32));
                    uint64x2 a = (uint64x2)zip4_lo(va, vb);
                    v = _mm256_broadcastq_epi64(a.native());
#else
                    uint64x2 a = _mm_cvtsi64_si128(v0);
                    v = _mm256_broadcastq_epi64(a.native());
#endif
                }
#endif

#if SIMD_USE_AVX512F
                static inline void i_set_splat(uint64<8> &v, uint64_t v0) {
                    v = _mm512_set1_epi64(v0);
                }
#endif

                template <unsigned N> inline void i_set_splat(uint64<N> &v, uint64_t v0) {
                    uint64v tv;
                    i_set_splat(tv, v0);
                    for (unsigned i = 0; i < v.vec_length; ++i) {
                        v.vec(i) = tv;
                    }
                }

                // -----------------------------------------------------------------------------

                static inline void i_set_splat(float32x4 &v, float v0) {
#if SIMD_USE_NULL || SIMD_USE_NEON_NO_FLT_SP
                    v = detail::null::make_vec<float32x4>(v0);
#elif SIMD_USE_SSE2
                    v = _mm_set1_ps(v0); // likely in a SSE register anyway
#elif SIMD_USE_NEON
                    v = vdupq_n_f32(v0);
#elif SIMD_USE_ALTIVEC
                    SIMDALIGN(16) float rv[4];
                    rv[0] = v0;
                    v = altivec::load1(v, rv);
                    v = splat<0>(v);
#elif SIMD_USE_MSA
                    SIMDALIGN(16) float rv[4];
                    rv[0] = v0;
                    v = (v4f32)__msa_ld_w(rv, 0);
                    v = (v4f32)__msa_splat_w((v4i32)v.native(), 0);
#endif
                }

#if SIMD_USE_AVX
                static inline void i_set_splat(float32x8 &v, float v0) {
                    v = _mm256_broadcast_ss(&v0);
                }
#endif

#if SIMD_USE_AVX512F
                static inline void i_set_splat(float32<16> &v, float v0) {
                    float32<4> a;
                    i_set_splat(a, v0);
                    v = _mm512_broadcast_f32x4(a.native());
                }
#endif

                template <unsigned N> inline void i_set_splat(float32<N> &v, float v0) {
#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wuninitialized"
#endif
                    // GCC thinks tv is not initialized
                    float32v tv;
                    i_set_splat(tv, v0);
                    for (unsigned i = 0; i < v.vec_length; ++i) {
                        v.vec(i) = tv;
                    }
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif
                }

                // -----------------------------------------------------------------------------

                static inline void i_set_splat(float64x2 &v, double v0) {
#if SIMD_USE_SSE2
                    v = _mm_set1_pd(v0); // likely in a SSE register anyway
#elif SIMD_USE_NEON64
                    v = vdupq_n_f64(v0);
#elif SIMD_USE_VSX_206
                    SIMDALIGN(16) double rv[2];
                    rv[0] = v0;
                    v = vec_ld(0, reinterpret_cast<const __vector double *>(rv));
                    v = splat<0>(v);
#elif SIMD_USE_MSA
                    SIMDALIGN(16) double rv[2];
                    rv[0] = v0;
                    v = (v2f64)__msa_ld_d(rv, 0);
                    v = (v2f64)__msa_splat_d((v2i64)v.native(), 0);
#elif SIMD_USE_NULL || SIMD_USE_NEON || SIMD_USE_ALTIVEC
                    v = detail::null::make_vec<float64x2>(v0);
#endif
                }

#if SIMD_USE_AVX
                static inline void i_set_splat(float64x4 &v, double v0) {
                    v = _mm256_broadcast_sd(&v0);
                }
#endif

#if SIMD_USE_AVX512F
                static inline void i_set_splat(float64<8> &v, double v0) {
                    float64<4> v1;
                    i_set_splat(v1, v0);
                    v = _mm512_broadcast_f64x4(v1.native());
                }
#endif

                template <unsigned N> inline void i_set_splat(float64<N> &v, double v0) {
                    float64v tv;
                    i_set_splat(tv, v0);
                    for (unsigned i = 0; i < v.vec_length; ++i) {
                        v.vec(i) = tv;
                    }
                }

                // -----------------------------------------------------------------------------

                template <class V, class VE> inline V i_splat_any(const VE &x) {
#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wuninitialized"
#endif
                    // GCC thinks r is not initialized
                    typename detail::remove_sign<V>::type r;
                    insn::i_set_splat(r, x);
                    return V(r);
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif
                }

            } // namespace insn

            template <class V, class VE> inline void construct_eval(V &v, const expr_vec_set_splat<VE> &e) {
                v = insn::i_splat_any<V>(e.a);
            }

            template <class V, class VE> inline V splat_impl(const VE &x) {
                static_assert(is_vector<V>::value && !is_mask<V>::value, "V must be a non-mask vector");
                return insn::i_splat_any<V>(x);
            }

        } // namespace detail
    }     // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
