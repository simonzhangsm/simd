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

#ifndef SIMD_DETAIL_INSN_LOAD_SPLAT_H
#define SIMD_DETAIL_INSN_LOAD_SPLAT_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/core/load_u.h>
#include <bigmath/simd/detail/insn/set_splat.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {

                static inline void i_load_splat(uint8x16 &v, const char *p0) {
                    const uint8_t *v0 = reinterpret_cast<const uint8_t *>(p0);
#if SIMD_USE_NULL
                    v = detail::null::make_vec<uint8x16>(*v0);
#elif SIMD_USE_SSE2 || SIMD_USE_MSA
                    i_set_splat(v, *v0);
#elif SIMD_USE_NEON
                    v = vld1q_dup_u8(v0);
#elif SIMD_USE_ALTIVEC
                    v = altivec::load1_u(v, v0);
                    v = splat<0>(v);
#endif
                }

#if SIMD_USE_AVX2
                static inline void i_load_splat(uint8x32 &v, const char *p0) {
                    i_set_splat(v, *reinterpret_cast<const uint8_t *>(p0));
                }
#endif

#if SIMD_USE_AVX512BW
                inline void i_load_splat(uint8<64> &v, const char *p0) {
                    i_set_splat(v, *reinterpret_cast<const uint8_t *>(p0));
                }
#endif

                // -----------------------------------------------------------------------------

                static inline void i_load_splat(uint16x8 &v, const char *p0) {
                    const uint16_t *v0 = reinterpret_cast<const uint16_t *>(p0);
#if SIMD_USE_NULL
                    v = detail::null::make_vec<uint16x8>(*v0);
#elif SIMD_USE_SSE2 || SIMD_USE_MSA
                    i_set_splat(v, *v0);
#elif SIMD_USE_NEON
                    v = vld1q_dup_u16(v0);
#elif SIMD_USE_ALTIVEC
                    v = altivec::load1_u(v, v0);
                    v = splat<0>(v);
#endif
                }

#if SIMD_USE_AVX2
                static inline void i_load_splat(uint16x16 &v, const char *p0) {
                    i_set_splat(v, *reinterpret_cast<const uint16_t *>(p0));
                }
#endif

#if SIMD_USE_AVX512BW
                inline void i_load_splat(uint16<32> &v, const char *p0) {
                    i_set_splat(v, *reinterpret_cast<const uint16_t *>(p0));
                }
#endif

                // -----------------------------------------------------------------------------

                static inline void i_load_splat(uint32x4 &v, const char *p0) {
                    const uint32_t *v0 = reinterpret_cast<const uint32_t *>(p0);
#if SIMD_USE_NULL
                    v = detail::null::make_vec<uint32x4>(*v0);
#elif SIMD_USE_SSE2
                    v = _mm_cvtsi32_si128(*v0);
                    v = permute4<0, 0, 0, 0>(v);
#elif SIMD_USE_NEON
                    v = vld1q_dup_u32(v0);
#elif SIMD_USE_ALTIVEC
                    v = altivec::load1_u(v, v0);
                    v = splat<0>(v);
#elif SIMD_USE_MSA
                    i_set_splat(v, *v0);
#endif
                }

#if SIMD_USE_AVX2
                static inline void i_load_splat(uint32x8 &v, const char *p0) {
                    i_set_splat(v, *reinterpret_cast<const uint32_t *>(p0));
                }
#endif

#if SIMD_USE_AVX512F
                static inline void i_load_splat(uint32<16> &v, const char *p0) {
                    __m128 x = _mm_load_ss(reinterpret_cast<const float *>(p0));
                    v = _mm512_broadcastd_epi32(_mm_castps_si128(x));
                }
#endif

                // -----------------------------------------------------------------------------

                static inline void i_load_splat(uint64x2 &v, const char *p0) {
                    const uint64_t *v0 = reinterpret_cast<const uint64_t *>(p0);
#if SIMD_USE_SSE2
                    v = _mm_loadl_epi64(reinterpret_cast<const __m128i *>(v0));
                    v = permute2<0, 0>(v);
#elif SIMD_USE_NEON
#if (__GNUC__ == 4) && (__GNUC_MINOR__ == 7)
                    // BUG: GCC 4.7 loads only the first element
                    uint64x1_t x = vld1_dup_u64(v0);
                    v = vdupq_lane_u64(x, 0);
#else
                    v = vld1q_dup_u64(v0);
#endif
#elif SIMD_USE_VSX_207
                    v = load_u(v0);
                    v = splat<0>(v);
#elif SIMD_USE_NULL || SIMD_USE_ALTIVEC
                    v = detail::null::make_vec<uint64x2>(*v0);
#elif SIMD_USE_MSA
                    i_set_splat(v, *v0);
#endif
                }

#if SIMD_USE_AVX2
                static inline void i_load_splat(uint64x4 &v, const char *p0) {
                    __m128i x = _mm_loadl_epi64(reinterpret_cast<const __m128i *>(p0));
                    v = _mm256_broadcastq_epi64(x);
                }
#endif

#if SIMD_USE_AVX512F
                static inline void i_load_splat(uint64<8> &v, const char *p0) {
                    __m128i x = _mm_loadl_epi64(reinterpret_cast<const __m128i *>(p0));
                    v = _mm512_broadcastq_epi64(x);
                }
#endif

                // -----------------------------------------------------------------------------

                static inline void i_load_splat(float32x4 &v, const char *p0) {
                    const float *v0 = reinterpret_cast<const float *>(p0);
#if SIMD_USE_NULL || SIMD_USE_NEON_NO_FLT_SP
                    v = detail::null::make_vec<float32x4>(*v0);
#elif SIMD_USE_AVX
                    v = _mm_broadcast_ss(v0);
#elif SIMD_USE_SSE2
                    v = _mm_load_ss(v0);
                    v = permute4<0, 0, 0, 0>(v);
#elif SIMD_USE_NEON
                    v = vld1q_dup_f32(v0);
#elif SIMD_USE_ALTIVEC
                    v = altivec::load1_u(v, v0);
                    v = splat<0>(v);
#elif SIMD_USE_MSA
                    i_set_splat(v, *v0);
#endif
                }

#if SIMD_USE_AVX
                static inline void i_load_splat(float32x8 &v, const char *p0) {
                    v = _mm256_broadcast_ss(reinterpret_cast<const float *>(p0));
                }
#endif

#if SIMD_USE_AVX512F
                static inline void i_load_splat(float32<16> &v, const char *p0) {
                    __m128 x = _mm_load_ss(reinterpret_cast<const float *>(p0));
                    v = _mm512_broadcastss_ps(x);
                }
#endif

                // -----------------------------------------------------------------------------

                static inline void i_load_splat(float64x2 &v, const char *p0) {
                    const double *v0 = reinterpret_cast<const double *>(p0);

#if SIMD_USE_SSE3
                    v = _mm_loaddup_pd(v0);
#elif SIMD_USE_SSE2
                    v = _mm_load_sd(v0);
                    v = permute2<0, 0>(v);
#elif SIMD_USE_NEON64
                    v = vld1q_dup_f64(v0);
#elif SIMD_USE_VSX_206
                    v = load_u(v0);
                    v = splat<0>(v);
#elif SIMD_USE_MSA
                    i_set_splat(v, *v0);
#elif SIMD_USE_NULL || SIMD_USE_NEON || SIMD_USE_ALTIVEC
                    v = detail::null::make_vec<float64x2>(*v0);
#endif
                }

#if SIMD_USE_AVX
                static inline void i_load_splat(float64x4 &v, const char *p0) {
                    v = _mm256_broadcast_sd(reinterpret_cast<const double *>(p0));
                }
#endif

#if SIMD_USE_AVX512F
                static inline void i_load_splat(float64<8> &v, const char *p0) {
                    __m128d x = _mm_load_sd(reinterpret_cast<const double *>(p0));
                    v = _mm512_broadcastsd_pd(x);
                }
#endif

                // -----------------------------------------------------------------------------

                template <class V> inline void i_load_splat(V &v, const char *p0) {
                    typename V::base_vector_type tv;
                    i_load_splat(tv, p0);
                    for (unsigned i = 0; i < v.vec_length; ++i) {
                        v.vec(i) = tv;
                    }
                }

                // -----------------------------------------------------------------------------

                template <class V> inline V i_load_splat_any(const char *p) {
                    typename detail::remove_sign<V>::type r;
                    i_load_splat(r, p);
                    return V(r);
                }

                // -----------------------------------------------------------------------------
            } // namespace insn

            template <class V> inline void construct_eval(V &v, const expr_vec_load_splat &e) {
                v = insn::i_load_splat_any<V>(e.a);
            }

        } // namespace detail
    }     // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
