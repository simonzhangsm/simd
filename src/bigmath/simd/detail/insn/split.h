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

#ifndef SIMD_DETAIL_INSN_SPLIT_H
#define SIMD_DETAIL_INSN_SPLIT_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {


#if SIMD_USE_AVX2
                static inline void i_split(const uint8<32> &a, uint8<16> &r1, uint8<16> &r2) {
                    r1 = _mm256_castsi256_si128(a.native());
                    r2 = _mm256_extracti128_si256(a.native(), 1);
                }
#endif

#if SIMD_USE_AVX512BW
                inline void i_split(const uint8<64> &a, uint8<32> &r1, uint8<32> &r2) {
                    r1 = _mm512_castsi512_si256(a.native());
                    r2 = _mm512_extracti64x4_epi64(a.native(), 1);
                }
#endif

                // -----------------------------------------------------------------------------

#if SIMD_USE_AVX2
                static inline void i_split(const uint16<16> &a, uint16<8> &r1, uint16<8> &r2) {
                    r1 = _mm256_castsi256_si128(a.native());
                    r2 = _mm256_extracti128_si256(a.native(), 1);
                }
#endif

#if SIMD_USE_AVX512BW
                inline void i_split(const uint16<32> &a, uint16<16> &r1, uint16<16> &r2) {
                    r1 = _mm512_castsi512_si256(a.native());
                    r2 = _mm512_extracti64x4_epi64(a.native(), 1);
                }
#endif

                // -----------------------------------------------------------------------------

#if SIMD_USE_AVX2
                static inline void i_split(const uint32<8> &a, uint32<4> &r1, uint32<4> &r2) {
                    r1 = _mm256_castsi256_si128(a.native());
                    r2 = _mm256_extracti128_si256(a.native(), 1);
                }
#endif

#if SIMD_USE_AVX512F
                static inline void i_split(const uint32<16> &a, uint32<8> &r1, uint32<8> &r2) {
                    r1 = _mm512_castsi512_si256(a.native());
                    r2 = _mm512_extracti64x4_epi64(a.native(), 1);
                }
#endif

                // -----------------------------------------------------------------------------

#if SIMD_USE_AVX2
                static inline void i_split(const uint64<4> &a, uint64<2> &r1, uint64<2> &r2) {
                    r1 = _mm256_castsi256_si128(a.native());
                    r2 = _mm256_extracti128_si256(a.native(), 1);
                }
#endif

#if SIMD_USE_AVX512F
                static inline void i_split(const uint64<8> &a, uint64<4> &r1, uint64<4> &r2) {
                    r1 = _mm512_castsi512_si256(a.native());
                    r2 = _mm512_extracti64x4_epi64(a.native(), 1);
                }
#endif

                // -----------------------------------------------------------------------------

#if SIMD_USE_AVX
                static inline void i_split(const float32<8> &a, float32<4> &r1, float32<4> &r2) {
                    r1 = _mm256_castps256_ps128(a.native());
                    r2 = _mm256_extractf128_ps(a.native(), 1);
                }
#endif

#if SIMD_USE_AVX512F
                static inline void i_split(const float32<16> &a, float32<8> &r1, float32<8> &r2) {
                    r1 = _mm512_castps512_ps256(a.native());
                    r2 = _mm256_castpd_ps(_mm512_extractf64x4_pd(_mm512_castps_pd(a.native()), 1));
                }
#endif

                // -----------------------------------------------------------------------------

#if SIMD_USE_AVX
                static inline void i_split(const float64<4> &a, float64<2> &r1, float64<2> &r2) {
                    r1 = _mm256_castpd256_pd128(a.native());
                    r2 = _mm256_extractf128_pd(a.native(), 1);
                }
#endif

#if SIMD_USE_AVX512F
                static inline void i_split(const float64<8> &a, float64<4> &r1, float64<4> &r2) {
                    // r1 = _mm512_castpd512_pd256(a.native()); GCC BUG
                    r1 = _mm512_extractf64x4_pd(a.native(), 0);
                    r2 = _mm512_extractf64x4_pd(a.native(), 1);
                }
#endif

                // -----------------------------------------------------------------------------
                // generic version -- picked up if none of the above matches the arguments

                template <class V, class H> inline void i_split(const V &a, H &r1, H &r2) {
                    unsigned h = H::vec_length;
                    for (unsigned i = 0; i < h; ++i) {
                        r1.vec(i) = a.vec(i);
                    }
                    for (unsigned i = 0; i < h; ++i) {
                        r2.vec(i) = a.vec(i + h);
                    }
                }


            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
