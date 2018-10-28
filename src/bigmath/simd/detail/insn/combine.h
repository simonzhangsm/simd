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

#ifndef SIMD_DETAIL_INSN_COMBINE_H
#define SIMD_DETAIL_INSN_COMBINE_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {

#if SIMD_USE_AVX2
                template <class Dummy> inline uint8<32> i_combine(const uint8<16> &a, const uint8<16> &b) {
                    uint8<32> r;
                    r = _mm256_castsi128_si256(a.native());
                    r = _mm256_inserti128_si256(r.native(), b.native(), 1);
                    return r;
                }
#endif

#if SIMD_USE_AVX512BW
                template <class Dummy> inline uint8<64> i_combine(const uint8<32> &a, const uint8<32> &b) {
                    uint8<64> r;
                    r = _mm512_castsi256_si512(a.native());
                    r = _mm512_inserti64x4(r.native(), b.native(), 1);
                    return r;
                }
#endif

                // -----------------------------------------------------------------------------

#if SIMD_USE_AVX2
                template <class Dummy> inline uint16<16> i_combine(const uint16<8> &a, const uint16<8> &b) {
                    uint16<16> r;
                    r = _mm256_castsi128_si256(a.native());
                    r = _mm256_inserti128_si256(r.native(), b.native(), 1);
                    return r;
                }
#endif

#if SIMD_USE_AVX512BW
                template <class Dummy> inline uint16<32> i_combine(const uint16<16> &a, const uint16<16> &b) {
                    uint16<32> r;
                    r = _mm512_castsi256_si512(a.native());
                    r = _mm512_inserti64x4(r.native(), b.native(), 1);
                    return r;
                }
#endif

                // -----------------------------------------------------------------------------

#if SIMD_USE_AVX2
                template <class Dummy> inline uint32<8> i_combine(const uint32<4> &a, const uint32<4> &b) {
                    uint32<8> r;
                    r = _mm256_castsi128_si256(a.native());
                    r = _mm256_inserti128_si256(r.native(), b.native(), 1);
                    return r;
                }
#endif

#if SIMD_USE_AVX512F
                template <class Dummy> inline uint32<16> i_combine(const uint32<8> &a, const uint32<8> &b) {
                    uint32<16> r;
                    r = _mm512_castsi256_si512(a.native());
                    r = _mm512_inserti64x4(r.native(), b.native(), 1);
                    return r;
                }
#endif

                // -----------------------------------------------------------------------------

#if SIMD_USE_AVX2
                template <class Dummy> inline uint64<4> i_combine(const uint64<2> &a, const uint64<2> &b) {
                    uint64<4> r;
                    r = _mm256_castsi128_si256(a.native());
                    r = _mm256_inserti128_si256(r.native(), b.native(), 1);
                    return r;
                }
#endif

#if SIMD_USE_AVX512F
                template <class Dummy> inline uint64<8> i_combine(const uint64<4> &a, const uint64<4> &b) {
                    uint64<8> r;
                    r = _mm512_castsi256_si512(a.native());
                    r = _mm512_inserti64x4(r.native(), b.native(), 1);
                    return r;
                }
#endif

                // -----------------------------------------------------------------------------

#if SIMD_USE_AVX
                template <class Dummy> inline float32<8> i_combine(const float32<4> &a, const float32<4> &b) {
                    float32<8> r;
                    r = _mm256_castps128_ps256(a.native());
                    r = _mm256_insertf128_ps(r.native(), b.native(), 1);
                    return r;
                }
#endif

#if SIMD_USE_AVX512F
                template <class Dummy> inline float32<16> i_combine(const float32<8> &a, const float32<8> &b) {
                    float32<16> r;
                    r = _mm512_castps256_ps512(a.native());
                    r = _mm512_castpd_ps(
                        _mm512_insertf64x4(_mm512_castps_pd(r.native()), _mm256_castps_pd(b.native()), 1));
                    return r;
                }
#endif

                // -----------------------------------------------------------------------------

#if SIMD_USE_AVX
                template <class Dummy> inline float64<4> i_combine(const float64<2> &a, const float64<2> &b) {
                    float64<4> r;
                    r = _mm256_castpd128_pd256(a.native());
                    r = _mm256_insertf128_pd(r.native(), b.native(), 1);
                    return r;
                }
#endif

#if SIMD_USE_AVX512F
                template <class Dummy> inline float64<8> i_combine(const float64<4> &a, const float64<4> &b) {
                    float64<8> r;
                    r = _mm512_castpd256_pd512(a.native());
                    r = _mm512_insertf64x4(r.native(), b.native(), 1);
                    return r;
                }
#endif

                // -----------------------------------------------------------------------------
                // generic implementation
                template <class V, class H> inline V i_combine(const H &a1, const H &a2) {
                    V r;
                    unsigned h = H::vec_length;
                    for (unsigned i = 0; i < h; ++i) {
                        r.vec(i) = a1.vec(i);
                    }
                    for (unsigned i = 0; i < h; ++i) {
                        r.vec(i + h) = a2.vec(i);
                    }
                    return r;
                }

            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
