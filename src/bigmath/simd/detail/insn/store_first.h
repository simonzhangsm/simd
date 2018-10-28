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

#ifndef SIMD_DETAIL_INSN_STORE_FIRST_H
#define SIMD_DETAIL_INSN_STORE_FIRST_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/align.h>
#include <bigmath/simd/core/blend.h>
#include <bigmath/simd/core/cmp_gt.h>
#include <bigmath/simd/core/load.h>
#include <bigmath/simd/core/load_u.h>
#include <bigmath/simd/core/store.h>
#include <bigmath/simd/detail/neon/memory_store.h>
#include <bigmath/simd/detail/null/memory.h>
#include <bigmath/simd/detail/extract128.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {

                static inline void i_store_first(char *p, const uint8x16 &a, unsigned n) {
                    p = detail::assume_aligned(p, 16);
#if SIMD_USE_NULL
                    detail::null::store_first(p, a, n);
#elif SIMD_USE_ALTIVEC && SIMD_BIG_ENDIAN
                    uint8x16 mask = vec_lvsr(n, (const uint8_t *)NULL);
                    mask = cmp_lt(mask, 0x10);
                    uint8x16 b = load(p);
                    b = blend(a, b, mask);
                    store(p, b);
#elif SIMD_USE_ALTIVEC && SIMD_LITTLE_ENDIAN
                    uint8<16> mask = make_ones();
                    uint8<16> shift = vec_splats((unsigned char)(n << 3));
                    mask = vec_slo(mask.native(), shift.native());

                    uint8x16 b = load(p);
                    b = blend(b, a, mask);
                    store(p, b);
#elif SIMD_USE_SSE2 || SIMD_USE_NEON || SIMD_USE_MSA
                    // for MSA we can't use __msa_sld_b because it does not work with shift==16
                    static const uint8_t mask_d[32] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                       0xff, 0xff, 0xff, 0xff, 0xff, 0,    0,    0,    0,    0,    0,
                                                       0,    0,    0,    0,    0,    0,    0,    0,    0,    0};

                    uint8x16 mask = load_u(mask_d + 16 - n);
                    uint8x16 b = load(p);
                    b = blend(a, b, mask);
                    store(p, b);
#endif
                }

#if SIMD_USE_AVX2
                static inline void i_store_first(char *p, const uint8x32 &a, unsigned n) {
                    static const uint8_t mask_d[64] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                       0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                       0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0,
                                                       0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                       0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                       0,    0,    0,    0,    0,    0,    0,    0,    0};

                    uint8x32 mask = load_u(mask_d + 32 - n);
                    uint8x32 b = load(p);
                    b = blend(a, b, mask);
                    store(p, b);
                }
#endif

#if SIMD_USE_AVX512BW
                inline void i_store_first(char *p, const uint8<64> &a, unsigned n) {
                    static const uint8_t mask_d[128] = {
                        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                        0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                        0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                        0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                        0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0};

                    uint8<64> mask = load_u(mask_d + 64 - n);
                    uint8<64> b = load(p);
                    b = blend(a, b, mask);
                    store(p, b);
                }
#endif

                // -----------------------------------------------------------------------------

                static inline void i_store_first(char *p, const uint16x8 &a, unsigned n) {
                    p = detail::assume_aligned(p, 16);
#if SIMD_USE_NULL
                    detail::null::store_first(p, a, n);
#elif SIMD_USE_SSE2 || SIMD_USE_NEON || SIMD_USE_ALTIVEC || SIMD_USE_MSA
                    i_store_first(p, (uint8x16)a, n * 2);
#endif
                }

#if SIMD_USE_AVX2
                static inline void i_store_first(char *p, const uint16x16 &a, unsigned n) {
                    i_store_first(p, uint8x32(a), n * 2);
                }
#endif

#if SIMD_USE_AVX512BW
                inline void i_store_first(char *p, const uint16<32> &a, unsigned n) {
                    i_store_first(p, uint8<64>(a), n * 2);
                }
#endif

                // -----------------------------------------------------------------------------

                static inline void i_store_first(char *p, const uint32x4 &a, unsigned n) {
                    p = detail::assume_aligned(p, 16);
#if SIMD_USE_NULL
                    detail::null::store_first(p, a, n);
#elif SIMD_USE_SSE2 || SIMD_USE_NEON || SIMD_USE_ALTIVEC || SIMD_USE_MSA
                    i_store_first(p, (uint8x16)a, n * 4);
#endif
                }

#if SIMD_USE_AVX2
                static inline void i_store_first(char *p, const uint32x8 &a, unsigned n) {
                    static const int32_t mask_d[16] = {-1, -1, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0};
                    uint32<8> mask = load_u(mask_d + 8 - n);
                    _mm256_maskstore_epi32(reinterpret_cast<int *>(p), mask.native(), a.native());
                }
#endif

#if SIMD_USE_AVX512F
                static inline void i_store_first(char *p, const uint32<16> &a, unsigned n) {
                    _mm512_mask_store_epi32(p, 0xffff >> (16 - n), a.native());
                }
#endif

                // -----------------------------------------------------------------------------

                static inline void i_store_first(char *p, const uint64x2 &a, unsigned n) {
                    p = detail::assume_aligned(p, 16);
#if SIMD_USE_SSE2
                    if (n == 1) {
                        _mm_store_sd(reinterpret_cast<double *>(p), _mm_castsi128_pd(a.native()));
                    }
#elif SIMD_USE_NEON
                    if (n == 1) {
                        neon::store_lane<0, 1>(p, a);
                    }
#elif SIMD_USE_VSX_207
                    if (n == 1) {
                        uint64_t *q = reinterpret_cast<uint64_t *>(p);
                        *q = vec_extract(a.native(), 0);
                    }
#elif SIMD_USE_MSA
                    i_store_first(p, uint8<16>(a), n * 8);
#elif SIMD_USE_NULL || SIMD_USE_ALTIVEC
                    detail::null::store_first(p, a, n);
#endif
                }

#if SIMD_USE_AVX2
                static inline void i_store_first(char *p, const uint64x4 &a, unsigned n) {
                    static const int64_t mask_d[8] = {-1, -1, -1, -1, 0, 0, 0, 0};
                    uint64<4> mask = load_u(mask_d + 4 - n);
#if __INTEL_COMPILER
                    _mm256_maskstore_epi64(reinterpret_cast<__int64 *>(p), mask.native(), a.native());
#else
                    _mm256_maskstore_epi64(reinterpret_cast<long long *>(p), mask.native(), a.native());
#endif
                }
#endif

#if SIMD_USE_AVX512F
                static inline void i_store_first(char *p, const uint64<8> &a, unsigned n) {
                    _mm512_mask_store_epi64(p, 0xff >> (8 - n), a.native());
                }
#endif

                // -----------------------------------------------------------------------------

                static inline void i_store_first(char *p, const float32x4 &a, unsigned n) {
                    p = detail::assume_aligned(p, 16);
#if SIMD_USE_NULL || SIMD_USE_ALTIVEC || SIMD_USE_NEON_NO_FLT_SP || SIMD_USE_MSA
                    i_store_first(p, int32x4(a), n);
#elif SIMD_USE_AVX && !SIMD_USE_AMD
                    static const int32_t mask_d[8] = {-1, -1, -1, -1, 0, 0, 0, 0};
                    float32x4 mask = load_u(mask_d + 4 - n);
                    _mm_maskstore_ps(reinterpret_cast<float *>(p), _mm_castps_si128(mask.native()), a.native());
#elif SIMD_USE_SSE2
                    static const int32_t mask_d[8] = {-1, -1, -1, -1, 0, 0, 0, 0};
                    float32x4 mask = load_u(mask_d + 4 - n);
                    float32x4 b = load(p);
                    b = blend(a, b, mask);
                    store(p, b);
#elif SIMD_USE_NEON
                    // + VFP
                    if (n < 1)
                        return;
                    neon::store_lane<0, 1>(p, a);
                    if (n < 2)
                        return;
                    neon::store_lane<1, 1>(p + 4, a);
                    if (n < 3)
                        return;
                    neon::store_lane<2, 1>(p + 8, a);
#endif
                }

#if SIMD_USE_AVX
                static inline void i_store_first(char *p, const float32x8 &a, unsigned n) {
                    static const int32_t mask_d[16] = {-1, -1, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0};

                    float32x8 mask = load_u(mask_d + 8 - n);
#if !SIMD_USE_AMD
                    _mm256_maskstore_ps(reinterpret_cast<float *>(p), _mm256_castps_si256(mask.native()), a.native());
#else
                    float32x8 b = load(p);
                    b = blend(a, b, mask);
                    store(v, b);
#endif
                }
#endif

#if SIMD_USE_AVX512F
                static inline void i_store_first(char *p, const float32<16> &a, unsigned n) {
                    _mm512_mask_store_ps(p, 0xffff >> (16 - n), a.native());
                }
#endif

                // -----------------------------------------------------------------------------

                static inline void i_store_first(char *p, const float64x2 &a, unsigned n) {
                    p = detail::assume_aligned(p, 16);
#if SIMD_USE_SSE2
                    if (n == 1) {
                        _mm_store_sd(reinterpret_cast<double *>(p), a.native());
                    }
#elif SIMD_USE_NEON64
                    if (n == 1) {
                        vst1_f64(reinterpret_cast<double *>(p), vget_low_f64(a.native()));
                    }
#elif SIMD_USE_VSX_206
                    if (n == 1) {
                        double *q = reinterpret_cast<double *>(p);
                        *q = vec_extract(a.native(), 0);
                    }
#elif SIMD_USE_MSA
                    i_store_first(p, (uint64x2)a, n);
#elif SIMD_USE_NULL || SIMD_USE_NEON32 || SIMD_USE_ALTIVEC
                    detail::null::store_first(p, a, n);
#endif
                }

#if SIMD_USE_AVX
                static inline void i_store_first(char *p, const float64x4 &a, unsigned n) {
                    static const int64_t mask_d[16] = {-1, -1, -1, -1, 0, 0, 0, 0};
                    float64x4 mask = load_u(mask_d + 4 - n);
#if !SIMD_USE_AMD
                    _mm256_maskstore_pd(reinterpret_cast<double *>(p), _mm256_castpd_si256(mask.native()), a.native());
#else
                    float64x4 b = load(p);
                    b = blend(a, b, mask);
                    store(v, b);
#endif
                }
#endif

#if SIMD_USE_AVX512F
                static inline void i_store_first(char *p, const float64<8> &a, unsigned n) {
                    _mm512_mask_store_pd(p, 0xff >> (8 - n), a.native());
                }
#endif

                // -----------------------------------------------------------------------------

                template <class V> inline void i_store_first(char *p, const V &ca, unsigned n) {
                    const unsigned veclen = V::base_vector_type::length_bytes;

                    typename detail::remove_sign<V>::type a = ca;
                    p = detail::assume_aligned(p, veclen);

                    unsigned n_full_vec = n / V::base_vector_type::length;
                    unsigned mid_vec_fill_count = n % V::base_vector_type::length;
                    unsigned curr_vec = 0;

                    for (; curr_vec < n_full_vec; ++curr_vec) {
                        store(p, a.vec(curr_vec));
                        p += veclen;
                    }

                    if (mid_vec_fill_count > 0) {
                        i_store_first(p, a.vec(curr_vec), mid_vec_fill_count);
                    }
                }

            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
