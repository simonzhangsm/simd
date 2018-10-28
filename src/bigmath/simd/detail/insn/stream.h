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

#ifndef SIMD_DETAIL_INSN_STREAM_H
#define SIMD_DETAIL_INSN_STREAM_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/align.h>
#include <bigmath/simd/core/store.h>
#include <bigmath/simd/detail/null/memory.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {

                static inline void i_stream(char *p, const uint8<16> &a) {
                    p = detail::assume_aligned(p, 16);
#if SIMD_USE_NULL
                    detail::null::store(p, a);
#elif SIMD_USE_SSE2
                    _mm_stream_si128(reinterpret_cast<__m128i *>(p), a.native());
#elif SIMD_USE_NEON || SIMD_USE_MSA
                    store(p, a);
#elif SIMD_USE_ALTIVEC
                    vec_st(a.native(), 0, reinterpret_cast<uint8_t *>(p));
#endif
                }

#if SIMD_USE_AVX2
                static inline void i_stream(char *p, const uint8<32> &a) {
                    p = detail::assume_aligned(p, 32);
                    _mm256_stream_si256(reinterpret_cast<__m256i *>(p), a.native());
                }
#endif

#if SIMD_USE_AVX512BW
                inline void i_stream(char *p, const uint8<64> &a) {
                    p = detail::assume_aligned(p, 64);
                    _mm512_stream_si512(reinterpret_cast<__m512i *>(p), a.native());
                }
#endif

                // -----------------------------------------------------------------------------

                static inline void i_stream(char *p, const uint16<8> &a) {
                    i_stream(p, uint8<16>(a));
                }

#if SIMD_USE_AVX2
                static inline void i_stream(char *p, const uint16<16> &a) {
                    i_stream(p, uint8<32>(a));
                }
#endif

#if SIMD_USE_AVX512BW
                inline void i_stream(char *p, const uint16<32> &a) {
                    p = detail::assume_aligned(p, 64);
                    _mm512_stream_si512(reinterpret_cast<__m512i *>(p), a.native());
                }
#endif

                // -----------------------------------------------------------------------------

                static inline void i_stream(char *p, const uint32<4> &a) {
                    i_stream(p, uint8<16>(a));
                }

#if SIMD_USE_AVX2
                static inline void i_stream(char *p, const uint32<8> &a) {
                    i_stream(p, uint8<32>(a));
                }
#endif

#if SIMD_USE_AVX512F
                static inline void i_stream(char *p, const uint32<16> &a) {
                    p = detail::assume_aligned(p, 64);
                    _mm512_stream_si512(reinterpret_cast<__m512i *>(p), a.native());
                }
#endif

                // -----------------------------------------------------------------------------

                static inline void i_stream(char *p, const uint64<2> &a) {
#if (SIMD_USE_ALTIVEC && !SIMD_USE_VSX_207)
                    p = detail::assume_aligned(p, 16);
                    detail::null::store(p, a);
#else
                    i_stream(p, uint8<16>(a));
#endif
                }

#if SIMD_USE_AVX2
                static inline void i_stream(char *p, const uint64<4> &a) {
                    i_stream(p, uint8<32>(a));
                }
#endif

#if SIMD_USE_AVX512F
                static inline void i_stream(char *p, const uint64<8> &a) {
                    p = detail::assume_aligned(p, 64);
                    _mm512_stream_si512(reinterpret_cast<__m512i *>(p), a.native());
                }
#endif

                // -----------------------------------------------------------------------------

                static inline void i_stream(char *p, const float32x4 &a) {
                    p = detail::assume_aligned(p, 16);
                    float *q = reinterpret_cast<float *>(p);
                    (void)q;
#if SIMD_USE_NULL
                    detail::null::store(p, a);
#elif SIMD_USE_SSE2
                    _mm_stream_ps(q, a.native());
#elif SIMD_USE_NEON || SIMD_USE_MSA
                    store(q, a);
#elif SIMD_USE_ALTIVEC
                    vec_st(a.native(), 0, q);
#endif
                }

#if SIMD_USE_AVX
                static inline void i_stream(char *p, const float32x8 &a) {
                    p = detail::assume_aligned(p, 32);
                    _mm256_stream_ps(reinterpret_cast<float *>(p), a.native());
                }
#endif

#if SIMD_USE_AVX512F
                static inline void i_stream(char *p, const float32<16> &a) {
                    p = detail::assume_aligned(p, 64);
                    _mm512_stream_ps(reinterpret_cast<float *>(p), a.native());
                }
#endif

                // -----------------------------------------------------------------------------

                static inline void i_stream(char *p, const float64x2 &a) {
                    p = detail::assume_aligned(p, 16);
#if SIMD_USE_SSE2
                    _mm_stream_pd(reinterpret_cast<double *>(p), a.native());
#elif SIMD_USE_NEON64 || SIMD_USE_VSX_206 || SIMD_USE_MSA
                    store(p, a);
#elif SIMD_USE_NULL || SIMD_USE_NEON32 || SIMD_USE_ALTIVEC
                    detail::null::store(p, a);
#endif
                }

#if SIMD_USE_AVX
                static inline void i_stream(char *p, const float64x4 &a) {
                    p = detail::assume_aligned(p, 32);
                    _mm256_stream_pd(reinterpret_cast<double *>(p), a.native());
                }
#endif

#if SIMD_USE_AVX512F
                static inline void i_stream(char *p, const float64<8> &a) {
                    p = detail::assume_aligned(p, 64);
                    _mm512_stream_pd(reinterpret_cast<double *>(p), a.native());
                }
#endif

                // -----------------------------------------------------------------------------

                template <class V> inline void i_stream(char *p, const V &ca) {
                    const unsigned veclen = V::base_vector_type::length_bytes;

                    typename detail::remove_sign<V>::type a = ca;
                    p = detail::assume_aligned(p, veclen);
                    for (unsigned i = 0; i < V::vec_length; ++i) {
                        i_stream(p, a.vec(i));
                        p += veclen;
                    }
                }

            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
