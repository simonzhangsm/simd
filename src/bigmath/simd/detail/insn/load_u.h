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

#ifndef SIMD_DETAIL_INSN_LOAD_U_H
#define SIMD_DETAIL_INSN_LOAD_U_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/core/transpose.h>
#include <bigmath/simd/detail/align.h>
#include <bigmath/simd/detail/not_implemented.h>
#include <bigmath/simd/detail/insn/mem_unpack.h>
#include <bigmath/simd/detail/null/memory.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {

                // -----------------------------------------------------------------------------

                // Each integer type is handled separately because higher aligment guarantees
                // offer better performance on e.g. ARM. Note, we don't use LDDQU on SSE,
                // because it has usage restrictions and offers improved performance only on
                // Pentium 4 era processors.
                static inline void i_load_u(uint8x16 &a, const char *p) {
#if SIMD_USE_NULL
                    detail::null::load(a, p);
#elif SIMD_USE_SSE2
                    a = _mm_loadu_si128(reinterpret_cast<const __m128i *>(p));
#elif SIMD_USE_NEON
                    a = vld1q_u8(reinterpret_cast<const uint8_t *>(p));
#elif SIMD_USE_VSX_206
                    const uint8_t *q = reinterpret_cast<const uint8_t *>(p);
                    a = vec_vsx_ld(0, q);
#elif SIMD_USE_ALTIVEC
                    const uint8_t *q = reinterpret_cast<const uint8_t *>(p);
                    uint8x16 l1, l2, mask;
                    l1 = vec_ld(0, q);
                    l2 = vec_ld(16, q);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated"
                    mask = vec_lvsl(0, q);
#pragma GCC diagnostic pop
                    a = vec_perm(l1.native(), l2.native(), mask.native());
#elif SIMD_USE_MSA
                    a = (v16u8)__msa_ld_b(p, 0);
#endif
                }

                static inline void i_load_u(uint16x8 &a, const char *p) {
#if SIMD_USE_NULL
                    detail::null::load(a, p);
#elif SIMD_USE_SSE2 || SIMD_USE_ALTIVEC
                    uint8x16 b;
                    i_load_u(b, p);
                    a = b;
#elif SIMD_USE_NEON
                    a = vld1q_u16(reinterpret_cast<const uint16_t *>(p));
#elif SIMD_USE_MSA
                    a = (v8u16)__msa_ld_h(p, 0);
#endif
                }

                static inline void i_load_u(uint32x4 &a, const char *p) {
#if SIMD_USE_NULL
                    detail::null::load(a, p);
#elif SIMD_USE_VSX_206
                    a = vec_vsx_ld(0, reinterpret_cast<const uint32_t *>(p));
#elif SIMD_USE_SSE2 || SIMD_USE_ALTIVEC
                    uint8x16 b;
                    i_load_u(b, p);
                    a = b;
#elif SIMD_USE_NEON
                    a = vld1q_u32(reinterpret_cast<const uint32_t *>(p));
#elif SIMD_USE_MSA
                    a = (v4u32)__msa_ld_w(p, 0);
#endif
                }

                static inline void i_load_u(uint64x2 &a, const char *p) {
#if SIMD_USE_NULL
                    detail::null::load(a, p);
#elif SIMD_USE_SSE2
                    uint8x16 b;
                    i_load_u(b, p);
                    a = b;
#elif SIMD_USE_VSX_207
#if SIMD_64_BITS
                    a = (__vector uint64_t)vec_vsx_ld(0, reinterpret_cast<const uint64_t *>(p));
#else
                    // BUG: GCC does not support vec_vsx_ld in 32-bit mode even when
                    // VSX 2.07 is enabled
                    uint8x16 r;
                    i_load_u(r, p);
                    a = r;
#endif
#elif SIMD_USE_ALTIVEC
                    detail::null::load(a, p);
#elif SIMD_USE_NEON
                    a = vld1q_u64(reinterpret_cast<const uint64_t *>(p));
#elif SIMD_USE_MSA
                    a = (v2u64)__msa_ld_d(p, 0);
#endif
                }

                static inline void i_load_u(float32x4 &a, const char *p) {
                    const float *q = reinterpret_cast<const float *>(p);
                    (void)q;
#if SIMD_USE_NULL || SIMD_USE_NEON_NO_FLT_SP
                    detail::null::load(a, p);
#elif SIMD_USE_SSE2
                    a = _mm_loadu_ps(q);
#elif SIMD_USE_NEON
                    a = vld1q_f32(q);
#elif SIMD_USE_VSX_206
                    a = vec_vsx_ld(0, q);
#elif SIMD_USE_ALTIVEC
                    uint32x4 b;
                    (void)q;
                    i_load_u(b, p);
                    a = b;
#elif SIMD_USE_MSA
                    a = (v4f32)__msa_ld_w(q, 0);
#endif
                }

                static inline void i_load_u(float64x2 &a, const char *p) {
                    const double *q = reinterpret_cast<const double *>(p);
                    (void)q;
#if SIMD_USE_SSE2
                    a = _mm_loadu_pd(q);
#elif SIMD_USE_NEON64
                    a = vld1q_f64(q);
#elif SIMD_USE_VSX_206
                    a = vec_vsx_ld(0, q);
#elif SIMD_USE_MSA
                    a = (v2f64)__msa_ld_d(q, 0);
#elif SIMD_USE_NULL || SIMD_USE_ALTIVEC || SIMD_USE_NEON
                    detail::null::load(a, p);
#else
                    SIMD_NOT_IMPLEMENTED2(a, p);
#endif
                }

#if SIMD_USE_AVX2
                static inline void i_load_u(uint8x32 &a, const char *p) {
                    a = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(p));
                }
                static inline void i_load_u(uint16x16 &a, const char *p) {
                    a = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(p));
                }
                static inline void i_load_u(uint32x8 &a, const char *p) {
                    a = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(p));
                }
                static inline void i_load_u(uint64x4 &a, const char *p) {
                    a = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(p));
                }
#endif
#if SIMD_USE_AVX
                static inline void i_load_u(float32x8 &a, const char *p) {
                    a = _mm256_loadu_ps(reinterpret_cast<const float *>(p));
                }
                static inline void i_load_u(float64x4 &a, const char *p) {
                    a = _mm256_loadu_pd(reinterpret_cast<const double *>(p));
                }
#endif

#if __INTEL_COMPILER && SIMD_USE_AVX && !SIMD_USE_AVX512F
                // BUG: Certain versions of ICC don't like vectors larger than native vector
                // (e.g. float32<16> and float64<8>) on AVX and AVX2. Two xmm vmovaps aligned
                // loads are emitted for each 32-byte load even though the argument is clearly
                // unaligned (e.g. p + 1). The code below results in the same output except
                // that correct vmovups unaligned load instructions are used.
                template <unsigned N> inline void i_load_u(float32<N> &a, const char *p) {
                    for (unsigned i = 0; i < float32<N>::vec_length; ++i) {
                        __m128 lo, hi;
                        lo = _mm_loadu_ps(reinterpret_cast<const float *>(p));
                        hi = _mm_loadu_ps(reinterpret_cast<const float *>(p + 16));
                        a.vec(i) = _mm256_insertf128_ps(_mm256_castps128_ps256(lo), hi, 1);
                        p += 32;
                    }
                }

                template <unsigned N> inline void i_load_u(float64<N> &a, const char *p) {
                    for (unsigned i = 0; i < float64<N>::vec_length; ++i) {
                        __m128d lo, hi;
                        lo = _mm_loadu_pd(reinterpret_cast<const double *>(p));
                        hi = _mm_loadu_pd(reinterpret_cast<const double *>(p + 16));
                        a.vec(i) = _mm256_insertf128_pd(_mm256_castpd128_pd256(lo), hi, 1);
                        p += 32;
                    }
                }
#endif

#if __INTEL_COMPILER && SIMD_USE_AVX2 && !SIMD_USE_AVX512BW
                template <unsigned N> inline void i_load_u(uint8<N> &a, const char *p) {
                    for (unsigned i = 0; i < uint8<N>::vec_length; ++i) {
                        __m128i lo, hi;
                        lo = _mm_loadu_si128(reinterpret_cast<const __m128i *>(p));
                        hi = _mm_loadu_si128(reinterpret_cast<const __m128i *>(p + 16));
                        a.vec(i) = _mm256_inserti128_si256(_mm256_castsi128_si256(lo), hi, 1);
                        p += 32;
                    }
                }

                template <unsigned N> inline void i_load_u(uint16<N> &a, const char *p) {
                    for (unsigned i = 0; i < uint16<N>::vec_length; ++i) {
                        __m128i lo, hi;
                        lo = _mm_loadu_si128(reinterpret_cast<const __m128i *>(p));
                        hi = _mm_loadu_si128(reinterpret_cast<const __m128i *>(p + 16));
                        a.vec(i) = _mm256_inserti128_si256(_mm256_castsi128_si256(lo), hi, 1);
                        p += 32;
                    }
                }
#endif

#if __INTEL_COMPILER && SIMD_USE_AVX2 && !SIMD_USE_AVX512F
                template <unsigned N> inline void i_load_u(uint32<N> &a, const char *p) {
                    for (unsigned i = 0; i < uint32<N>::vec_length; ++i) {
                        __m128i lo, hi;
                        lo = _mm_loadu_si128(reinterpret_cast<const __m128i *>(p));
                        hi = _mm_loadu_si128(reinterpret_cast<const __m128i *>(p + 16));
                        a.vec(i) = _mm256_inserti128_si256(_mm256_castsi128_si256(lo), hi, 1);
                        p += 32;
                    }
                }

                template <unsigned N> inline void i_load_u(uint64<N> &a, const char *p) {
                    for (unsigned i = 0; i < uint64<N>::vec_length; ++i) {
                        __m128i lo, hi;
                        lo = _mm_loadu_si128(reinterpret_cast<const __m128i *>(p));
                        hi = _mm_loadu_si128(reinterpret_cast<const __m128i *>(p + 16));
                        a.vec(i) = _mm256_inserti128_si256(_mm256_castsi128_si256(lo), hi, 1);
                        p += 32;
                    }
                }
#endif

#if SIMD_USE_AVX512BW
                inline void i_load_u(uint8<64> &a, const char *p) {
                    a = _mm512_loadu_si512(p);
                }
                inline void i_load_u(uint16<32> &a, const char *p) {
                    a = _mm512_loadu_si512(p);
                }
#endif

#if SIMD_USE_AVX512F
                static inline void i_load_u(uint32<16> &a, const char *p) {
                    a = _mm512_loadu_si512(p);
                }
                static inline void i_load_u(uint64<8> &a, const char *p) {
                    a = _mm512_loadu_si512(p);
                }
                static inline void i_load_u(float32<16> &a, const char *p) {
                    a = _mm512_loadu_ps(reinterpret_cast<const float *>(p));
                }
                static inline void i_load_u(float64<8> &a, const char *p) {
                    a = _mm512_loadu_pd(reinterpret_cast<const double *>(p));
                }
#endif

                // -----------------------------------------------------------------------------

                template <class V> inline void i_load_u(V &a, const char *p) {
                    const unsigned veclen = V::base_vector_type::length_bytes;
                    for (unsigned i = 0; i < V::vec_length; ++i) {
                        i_load_u(a.vec(i), p);
                        p += veclen;
                    }
                }

                template <class V> V i_load_u_any(const char *p) {
                    typename detail::remove_sign<V>::type r;
                    i_load_u(r, p);
                    return V(r);
                }

            } // namespace insn

            template <class V> inline void construct_eval(V &v, const expr_vec_load_u &e) {
                v = insn::i_load_u_any<V>(e.a);
            }

        } // namespace detail
    }     // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
