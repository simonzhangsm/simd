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

#ifndef SIMD_DETAIL_INSN_STORE_MASKED_H
#define SIMD_DETAIL_INSN_STORE_MASKED_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/core/load.h>
#include <bigmath/simd/core/store.h>
#include <bigmath/simd/detail/null/memory.h>
#include <bigmath/simd/detail/align.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {

                static inline void i_store_masked(char *p, const uint32<4> &a, const mask_int32<4> &mask) {
#if SIMD_USE_NULL
                    null::store_masked(p, a, mask);
#elif SIMD_USE_AVX512VL
                    _mm_mask_store_epi32(p, mask.native(), a.native());
#elif SIMD_USE_AVX2
                    _mm_maskstore_epi32(reinterpret_cast<int *>(p), mask.native(), a.native());
#elif SIMD_USE_AVX
                    _mm_maskstore_ps(reinterpret_cast<float *>(p), mask.native(), _mm_castsi128_ps(a.native()));
#elif SIMD_USE_SSE2 || SIMD_USE_NEON || SIMD_USE_ALTIVEC || SIMD_USE_MSA
                    uint32<4> b = load(p);
                    b = blend(a, b, mask);
                    store(p, b);
#endif
                }

#if SIMD_USE_AVX2
                static inline void i_store_masked(char *p, const uint32<8> &a, const mask_int32<8> &mask) {
#if SIMD_USE_AVX512VL
                    _mm256_mask_store_epi32(p, mask.native(), a.native());
#else
                    _mm256_maskstore_epi32(reinterpret_cast<int *>(p), mask.native(), a.native());
#endif
                }
#endif

#if SIMD_USE_AVX512F
                static inline void i_store_masked(char *p, const uint32<16> &a, const mask_int32<16> &mask) {
                    _mm512_mask_store_epi32(reinterpret_cast<int *>(p), mask.native(), a.native());
                }
#endif

                // -----------------------------------------------------------------------------

                static inline void i_store_masked(char *p, const uint64<2> &a, const mask_int64<2> &mask) {
#if SIMD_USE_AVX512VL
#if __INTEL_COMPILER
                    _mm_mask_store_epi64(reinterpret_cast<__int64 *>(p), mask.native(), a.native());
#else
                    _mm_mask_store_epi64(reinterpret_cast<long long *>(p), mask.native(), a.native());
#endif
#elif SIMD_USE_AVX2
#if __INTEL_COMPILER
                    _mm_maskstore_epi64(reinterpret_cast<__int64 *>(p), mask.native(), a.native());
#else
                    _mm_maskstore_epi64(reinterpret_cast<long long *>(p), mask.native(), a.native());
#endif
#elif SIMD_USE_AVX
                    _mm_maskstore_pd(reinterpret_cast<double *>(p), mask.native(), _mm_castsi128_pd(a.native()));
#elif SIMD_USE_SSE2 || SIMD_USE_NEON || SIMD_USE_VSX_207 || SIMD_USE_MSA
                    uint64<2> b = load(p);
                    b = blend(a, b, mask);
                    store(p, b);
#elif SIMD_USE_NULL || SIMD_USE_ALTIVEC
                    null::store_masked(p, a, mask);
#endif
                }

#if SIMD_USE_AVX2
                static inline void i_store_masked(char *p, const uint64<4> &a, const mask_int64<4> &mask) {
#if SIMD_USE_AVX512VL
#if __INTEL_COMPILER
                    _mm256_mask_store_epi64(reinterpret_cast<__int64 *>(p), mask.native(), a.native());
#else
                    _mm256_mask_store_epi64(reinterpret_cast<long long *>(p), mask.native(), a.native());
#endif
#else
#if __INTEL_COMPILER
                    _mm256_maskstore_epi64(reinterpret_cast<__int64 *>(p), mask.native(), a.native());
#else
                    _mm256_maskstore_epi64(reinterpret_cast<long long *>(p), mask.native(), a.native());
#endif
#endif
                }
#endif

#if SIMD_USE_AVX512F
                static inline void i_store_masked(char *p, const uint64<8> &a, const mask_int64<8> &mask) {
#if __INTEL_COMPILER
                    _mm512_mask_store_epi64(reinterpret_cast<__int64 *>(p), mask.native(), a.native());
#else
                    _mm512_mask_store_epi64(reinterpret_cast<long long *>(p), mask.native(), a.native());
#endif
                }
#endif

                // -----------------------------------------------------------------------------

                static inline void i_store_masked(char *p, const float32<4> &a, const mask_float32<4> &mask) {
#if SIMD_USE_NULL
                    null::store_masked(p, a, mask);
#elif SIMD_USE_AVX512VL
                    _mm_mask_store_ps(reinterpret_cast<float *>(p), mask.native(), a.native());
#elif SIMD_USE_AVX
                    _mm_maskstore_ps(reinterpret_cast<float *>(p), _mm_castps_si128(mask.native()), a.native());
#elif SIMD_USE_SSE2 || SIMD_USE_NEON || SIMD_USE_ALTIVEC || SIMD_USE_MSA
                    float32<4> b = load(p);
                    b = blend(a, b, mask);
                    store(p, b);
#endif
                }

#if SIMD_USE_AVX
                static inline void i_store_masked(char *p, const float32<8> &a, const mask_float32<8> &mask) {
#if SIMD_USE_AVX512VL
                    _mm256_mask_store_ps(reinterpret_cast<float *>(p), mask.native(), a.native());
#else
                    _mm256_maskstore_ps(reinterpret_cast<float *>(p), _mm256_castps_si256(mask.native()), a.native());
#endif
                }
#endif

#if SIMD_USE_AVX512F
                static inline void i_store_masked(char *p, const float32<16> &a, const mask_float32<16> &mask) {
                    _mm512_mask_store_ps(reinterpret_cast<float *>(p), mask.native(), a.native());
                }
#endif

                // -----------------------------------------------------------------------------

                static inline void i_store_masked(char *p, const float64<2> &a, const mask_float64<2> &mask) {
#if SIMD_USE_AVX512VL
                    _mm_mask_store_pd(reinterpret_cast<double *>(p), mask.native(), a.native());
#elif SIMD_USE_AVX
                    _mm_maskstore_pd(reinterpret_cast<double *>(p), _mm_castpd_si128(mask.native()), a.native());
#elif SIMD_USE_SSE2 || SIMD_USE_NEON64 || SIMD_USE_VSX_206 || SIMD_USE_MSA
                    float64<2> b = load(p);
                    b = blend(a, b, mask);
                    store(p, b);
#elif SIMD_USE_NULL || SIMD_USE_NEON32 || SIMD_USE_ALTIVEC
                    null::store_masked(p, a, mask);
#endif
                }

#if SIMD_USE_AVX
                static inline void i_store_masked(char *p, const float64<4> &a, const mask_float64<4> &mask) {
#if SIMD_USE_AVX512VL
                    _mm256_mask_store_pd(reinterpret_cast<double *>(p), mask.native(), a.native());
#else
                    _mm256_maskstore_pd(reinterpret_cast<double *>(p), _mm256_castpd_si256(mask.native()), a.native());
#endif
                }
#endif

#if SIMD_USE_AVX512F
                static inline void i_store_masked(char *p, const float64<8> &a, const mask_float64<8> &mask) {
                    _mm512_mask_store_pd(reinterpret_cast<double *>(p), mask.native(), a.native());
                }
#endif

                // -----------------------------------------------------------------------------

                template <class V, class M> void i_store_masked(char *p, const V &a, const M &mask) {
                    const unsigned veclen = V::base_vector_type::length_bytes;

                    for (unsigned i = 0; i < a.vec_length; ++i) {
                        i_store_masked(p, a.vec(i), mask.vec(i));
                        p += veclen;
                    }
                }

            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
