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

#ifndef SIMD_DETAIL_INSN_LOAD_H
#define SIMD_DETAIL_INSN_LOAD_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/types/traits.h>
#include <bigmath/simd/detail/align.h>
#include <bigmath/simd/detail/insn/mem_unpack.h>
#include <bigmath/simd/core/transpose.h>
#include <bigmath/simd/detail/null/memory.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {

                static inline void i_load(uint8x16 &a, const char *p) {
                    p = detail::assume_aligned(p, 16);
#if SIMD_USE_NULL
                    detail::null::load(a, p);
#elif SIMD_USE_SSE2
                    a = _mm_load_si128(reinterpret_cast<const __m128i *>(p));
#elif SIMD_USE_NEON
                    a = vreinterpretq_u8_u64(vld1q_u64(reinterpret_cast<const uint64_t *>(p)));
#elif SIMD_USE_ALTIVEC
                    a = vec_ld(0, reinterpret_cast<const uint8_t *>(p));
#elif SIMD_USE_MSA
                    a = (v16u8)__msa_ld_b(p, 0);
#endif
                }

                static inline void i_load(uint16x8 &a, const char *p) {
                    uint8x16 r;
                    i_load(r, p);
                    a = r;
                }
                static inline void i_load(uint32x4 &a, const char *p) {
                    uint8x16 r;
                    i_load(r, p);
                    a = r;
                }

                static inline void i_load(uint64x2 &a, const char *p) {
#if SIMD_USE_NULL || (SIMD_USE_ALTIVEC && !SIMD_USE_VSX_207)
                    p = detail::assume_aligned(p, 16);
                    detail::null::load(a, p);
#else
                    uint8x16 r;
                    i_load(r, p);
                    a = r;
#endif
                }

                static inline void i_load(float32x4 &a, const char *p) {
                    p = detail::assume_aligned(p, 16);
                    const float *q = reinterpret_cast<const float *>(p);
                    (void)q;
#if SIMD_USE_NULL || SIMD_USE_NEON_NO_FLT_SP
                    detail::null::load(a, p);
#elif SIMD_USE_SSE2
                    a = _mm_load_ps(q);
#elif SIMD_USE_NEON
                    a = vld1q_f32(q);
#elif SIMD_USE_ALTIVEC
                    a = vec_ld(0, q);
#elif SIMD_USE_MSA
                    a = (v4f32)__msa_ld_w(q, 0);
#endif
                }

                static inline void i_load(float64x2 &a, const char *p) {
                    p = detail::assume_aligned(p, 16);
                    const double *q = reinterpret_cast<const double *>(p);
                    (void)q;
#if SIMD_USE_SSE2
                    a = _mm_load_pd(q);
#elif SIMD_USE_NEON64
                    a = vld1q_f64(q);
#elif SIMD_USE_VSX_206
                    a = vec_ld(0, reinterpret_cast<const __vector double *>(q));
#elif SIMD_USE_MSA
                    a = (v2f64)__msa_ld_d(q, 0);
#elif SIMD_USE_NULL || SIMD_USE_ALTIVEC || SIMD_USE_NEON32
                    detail::null::load(a, p);
#endif
                }

#if SIMD_USE_AVX2
                static inline void i_load(uint8x32 &a, const char *p) {
                    a = _mm256_load_si256(reinterpret_cast<const __m256i *>(p));
                }
                static inline void i_load(uint16x16 &a, const char *p) {
                    a = _mm256_load_si256(reinterpret_cast<const __m256i *>(p));
                }
                static inline void i_load(uint32x8 &a, const char *p) {
                    a = _mm256_load_si256(reinterpret_cast<const __m256i *>(p));
                }
                static inline void i_load(uint64x4 &a, const char *p) {
                    a = _mm256_load_si256(reinterpret_cast<const __m256i *>(p));
                }
#endif
#if SIMD_USE_AVX
                static inline void i_load(float32x8 &a, const char *p) {
                    a = _mm256_load_ps(reinterpret_cast<const float *>(p));
                }
                static inline void i_load(float64x4 &a, const char *p) {
                    a = _mm256_load_pd(reinterpret_cast<const double *>(p));
                }
#endif

#if SIMD_USE_AVX512BW
                inline void i_load(uint8<64> &a, const char *p) {
                    a = _mm512_load_epi32(p);
                }
                inline void i_load(uint16<32> &a, const char *p) {
                    a = _mm512_load_epi32(p);
                }
#endif

#if SIMD_USE_AVX512F
                static inline void i_load(uint32<16> &a, const char *p) {
                    a = _mm512_load_epi32(p);
                }
                static inline void i_load(uint64<8> &a, const char *p) {
                    a = _mm512_load_epi64(p);
                }
                static inline void i_load(float32<16> &a, const char *p) {
                    a = _mm512_load_ps(reinterpret_cast<const float *>(p));
                }
                static inline void i_load(float64<8> &a, const char *p) {
                    a = _mm512_load_pd(reinterpret_cast<const double *>(p));
                }
#endif

                template <class V> inline void i_load(V &a, const char *p) {
                    const unsigned veclen = V::base_vector_type::length_bytes;

                    for (unsigned i = 0; i < V::vec_length; ++i) {
                        i_load(a.vec(i), p);
                        p += veclen;
                    }
                }

                template <class V> inline V i_load_any(const char *p) {
                    typename detail::remove_sign<V>::type r;
                    i_load(r, p);
                    return V(r);
                }

            } // namespace insn

            template <class V> inline void construct_eval(V &v, const expr_vec_load &e) {
                v = insn::i_load_any<V>(e.a);
            }

        } // namespace detail
    }     // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
