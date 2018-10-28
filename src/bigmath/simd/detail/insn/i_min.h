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

#ifndef SIMD_DETAIL_INSN_I_MIN_H
#define SIMD_DETAIL_INSN_I_MIN_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/core/blend.h>
#include <bigmath/simd/core/cmp_lt.h>
#include <bigmath/simd/core/bit_xor.h>
#include <bigmath/simd/detail/not_implemented.h>
#include <bigmath/simd/detail/null/math.h>
#include <bigmath/simd/detail/vector_array_macros.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {


                static inline int8x16 i_min(const int8x16 &a, const int8x16 &b) {
#if SIMD_USE_NULL
                    return detail::null::min(a, b);
#elif SIMD_USE_SSE4_1
                    return _mm_min_epi8(a.native(), b.native());
#elif SIMD_USE_SSE2
                    int8x16 ca = bit_xor(a, 0x80);
                    int8x16 cb = bit_xor(b, 0x80);
                    int8x16 r = _mm_min_epu8(ca.native(), cb.native());
                    return bit_xor(r, 0x80);
#elif SIMD_USE_NEON
                    return vminq_s8(a.native(), b.native());
#elif SIMD_USE_ALTIVEC
                    return vec_min(a.native(), b.native());
#elif SIMD_USE_MSA
                    return __msa_min_s_b(a.native(), b.native());
#endif
                }

#if SIMD_USE_AVX2
                static inline int8x32 i_min(const int8x32 &a, const int8x32 &b) {
                    return _mm256_min_epi8(a.native(), b.native());
                }
#endif

#if SIMD_USE_AVX512BW
                inline int8<64> i_min(const int8<64> &a, const int8<64> &b) {
                    return _mm512_min_epi8(a.native(), b.native());
                }
#endif

                template <unsigned N> inline int8<N> i_min(const int8<N> &a, const int8<N> &b) {
                    SIMD_VEC_ARRAY_IMPL2(int8<N>, i_min, a, b);
                }

                // -----------------------------------------------------------------------------

                static inline uint8x16 i_min(const uint8x16 &a, const uint8x16 &b) {
#if SIMD_USE_NULL
                    return detail::null::min(a, b);
#elif SIMD_USE_SSE2
                    return _mm_min_epu8(a.native(), b.native());
#elif SIMD_USE_NEON
                    return vminq_u8(a.native(), b.native());
#elif SIMD_USE_ALTIVEC
                    return vec_min(a.native(), b.native());
#elif SIMD_USE_MSA
                    return __msa_min_u_b(a.native(), b.native());
#endif
                }

#if SIMD_USE_AVX2
                static inline uint8x32 i_min(const uint8x32 &a, const uint8x32 &b) {
                    return _mm256_min_epu8(a.native(), b.native());
                }
#endif

#if SIMD_USE_AVX512BW
                inline uint8<64> i_min(const uint8<64> &a, const uint8<64> &b) {
                    return _mm512_min_epu8(a.native(), b.native());
                }
#endif

                template <unsigned N> inline uint8<N> i_min(const uint8<N> &a, const uint8<N> &b) {
                    SIMD_VEC_ARRAY_IMPL2(uint8<N>, i_min, a, b);
                }

                // -----------------------------------------------------------------------------

                static inline int16x8 i_min(const int16x8 &a, const int16x8 &b) {
#if SIMD_USE_NULL
                    return detail::null::min(a, b);
#elif SIMD_USE_SSE2
                    return _mm_min_epi16(a.native(), b.native());
#elif SIMD_USE_NEON
                    return vminq_s16(a.native(), b.native());
#elif SIMD_USE_ALTIVEC
                    return vec_min(a.native(), b.native());
#elif SIMD_USE_MSA
                    return __msa_min_s_h(a.native(), b.native());
#endif
                }

#if SIMD_USE_AVX2
                static inline int16x16 i_min(const int16x16 &a, const int16x16 &b) {
                    return _mm256_min_epi16(a.native(), b.native());
                }
#endif

#if SIMD_USE_AVX512BW
                inline int16<32> i_min(const int16<32> &a, const int16<32> &b) {
                    return _mm512_min_epi16(a.native(), b.native());
                }
#endif

                template <unsigned N> inline int16<N> i_min(const int16<N> &a, const int16<N> &b) {
                    SIMD_VEC_ARRAY_IMPL2(int16<N>, i_min, a, b);
                }

                // -----------------------------------------------------------------------------

                static inline uint16x8 i_min(const uint16x8 &a, const uint16x8 &b) {
#if SIMD_USE_NULL
                    return detail::null::min(a, b);
#elif SIMD_USE_SSE4_1
                    return _mm_min_epu16(a.native(), b.native());
#elif SIMD_USE_SSE2
                    int16x8 ca = bit_xor(a, 0x8000);
                    int16x8 cb = bit_xor(b, 0x8000);
                    int16x8 r = _mm_min_epi16(ca.native(), cb.native());
                    return bit_xor(r, 0x8000);
#elif SIMD_USE_NEON
                    return vminq_u16(a.native(), b.native());
#elif SIMD_USE_ALTIVEC
                    return vec_min(a.native(), b.native());
#elif SIMD_USE_MSA
                    return __msa_min_u_h(a.native(), b.native());
#endif
                }

#if SIMD_USE_AVX2
                static inline uint16x16 i_min(const uint16x16 &a, const uint16x16 &b) {
                    return _mm256_min_epu16(a.native(), b.native());
                }
#endif

#if SIMD_USE_AVX512BW
                inline uint16<32> i_min(const uint16<32> &a, const uint16<32> &b) {
                    return _mm512_min_epu16(a.native(), b.native());
                }
#endif

                template <unsigned N> inline uint16<N> i_min(const uint16<N> &a, const uint16<N> &b) {
                    SIMD_VEC_ARRAY_IMPL2(uint16<N>, i_min, a, b);
                }

                // -----------------------------------------------------------------------------

                static inline int32x4 i_min(const int32x4 &a, const int32x4 &b) {
#if SIMD_USE_NULL
                    return detail::null::min(a, b);
#elif SIMD_USE_SSE4_1
                    return _mm_min_epi32(a.native(), b.native());
#elif SIMD_USE_SSE2
                    mask_int32x4 mask = cmp_lt(a, b);
                    return blend(a, b, mask);
#elif SIMD_USE_NEON
                    return vminq_s32(a.native(), b.native());
#elif SIMD_USE_ALTIVEC
                    return vec_min(a.native(), b.native());
#elif SIMD_USE_MSA
                    return __msa_min_s_w(a.native(), b.native());
#endif
                }

#if SIMD_USE_AVX2
                static inline int32x8 i_min(const int32x8 &a, const int32x8 &b) {
                    return _mm256_min_epi32(a.native(), b.native());
                }
#endif

#if SIMD_USE_AVX512F
                static inline int32<16> i_min(const int32<16> &a, const int32<16> &b) {
                    return _mm512_min_epi32(a.native(), b.native());
                }
#endif

                template <unsigned N> inline int32<N> i_min(const int32<N> &a, const int32<N> &b) {
                    SIMD_VEC_ARRAY_IMPL2(int32<N>, i_min, a, b);
                }

                // -----------------------------------------------------------------------------

                static inline uint32x4 i_min(const uint32x4 &a, const uint32x4 &b) {
#if SIMD_USE_NULL
                    return detail::null::min(a, b);
#elif SIMD_USE_SSE4_1
                    return _mm_min_epu32(a.native(), b.native());
#elif SIMD_USE_SSE2
                    mask_int32x4 mask = cmp_lt(a, b);
                    return blend(a, b, mask);
#elif SIMD_USE_NEON
                    return vminq_u32(a.native(), b.native());
#elif SIMD_USE_ALTIVEC
                    return vec_min(a.native(), b.native());
#elif SIMD_USE_MSA
                    return __msa_min_u_w(a.native(), b.native());
#endif
                }

#if SIMD_USE_AVX2
                static inline uint32x8 i_min(const uint32x8 &a, const uint32x8 &b) {
                    return _mm256_min_epu32(a.native(), b.native());
                }
#endif

#if SIMD_USE_AVX512F
                static inline uint32<16> i_min(const uint32<16> &a, const uint32<16> &b) {
                    return _mm512_min_epu32(a.native(), b.native());
                }
#endif

                template <unsigned N> inline uint32<N> i_min(const uint32<N> &a, const uint32<N> &b) {
                    SIMD_VEC_ARRAY_IMPL2(uint32<N>, i_min, a, b);
                }

                // -----------------------------------------------------------------------------

                static inline int64x2 i_min(const int64x2 &a, const int64x2 &b) {
#if SIMD_USE_AVX512VL
                    return _mm_min_epi64(a.native(), b.native());
#elif SIMD_USE_AVX2 || SIMD_USE_NEON64
                    mask_int64x2 mask = cmp_lt(a, b);
                    return blend(a, b, mask);
#elif SIMD_USE_VSX_207
                    return vec_min(a.native(), b.native());
#elif SIMD_USE_MSA
                    return __msa_min_s_d(a.native(), b.native());
#elif SIMD_USE_NULL || SIMD_USE_ALTIVEC
                    return detail::null::min(a, b);
#else
                    return SIMD_NOT_IMPLEMENTED2(a, b);
#endif
                }

#if SIMD_USE_AVX2
                static inline int64x4 i_min(const int64x4 &a, const int64x4 &b) {
#if SIMD_USE_AVX512VL
                    return _mm256_min_epi64(a.native(), b.native());
#else
                    mask_int64x4 mask = cmp_lt(a, b);
                    return blend(a, b, mask);
#endif
                }
#endif

#if SIMD_USE_AVX512F
                static inline int64<8> i_min(const int64<8> &a, const int64<8> &b) {
                    return _mm512_min_epi64(a.native(), b.native());
                }
#endif

                template <unsigned N> inline int64<N> i_min(const int64<N> &a, const int64<N> &b) {
                    SIMD_VEC_ARRAY_IMPL2(int64<N>, i_min, a, b);
                }

                // -----------------------------------------------------------------------------

                static inline uint64x2 i_min(const uint64x2 &a, const uint64x2 &b) {
#if SIMD_USE_AVX512VL
                    return _mm_min_epu64(a.native(), b.native());
#elif SIMD_USE_AVX2 || SIMD_USE_NEON64
                    mask_int64x2 mask = cmp_lt(a, b);
                    return blend(a, b, mask);
#elif SIMD_USE_VSX_207
                    return vec_min(a.native(), b.native());
#elif SIMD_USE_MSA
                    return __msa_min_u_d(a.native(), b.native());
#elif SIMD_USE_NULL || SIMD_USE_ALTIVEC
                    return detail::null::min(a, b);
#else
                    return SIMD_NOT_IMPLEMENTED2(a, b);
#endif
                }

#if SIMD_USE_AVX2
                static inline uint64x4 i_min(const uint64x4 &a, const uint64x4 &b) {
#if SIMD_USE_AVX512VL
                    return _mm256_min_epu64(a.native(), b.native());
#else
                    mask_int64x4 mask = cmp_lt(a, b);
                    return blend(a, b, mask);
#endif
                }
#endif

#if SIMD_USE_AVX512F
                static inline uint64<8> i_min(const uint64<8> &a, const uint64<8> &b) {
                    return _mm512_min_epu64(a.native(), b.native());
                }
#endif

                template <unsigned N> inline uint64<N> i_min(const uint64<N> &a, const uint64<N> &b) {
                    SIMD_VEC_ARRAY_IMPL2(uint64<N>, i_min, a, b);
                }

            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
