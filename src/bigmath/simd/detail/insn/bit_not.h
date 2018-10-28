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

#ifndef SIMD_DETAIL_INSN_BIT_NOT_H
#define SIMD_DETAIL_INSN_BIT_NOT_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/core/bit_xor.h>
#include <bigmath/simd/core/to_mask.h>
#include <bigmath/simd/detail/null/bitwise.h>
#include <bigmath/simd/detail/vector_array_macros.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {


                static inline uint8x16 i_bit_not(const uint8x16 &a) {
#if SIMD_USE_NULL
                    uint8x16 r;
                    for (unsigned i = 0; i < a.length; i++) {
                        r.el(i) = ~a.el(i);
                    }
                    return r;
#elif SIMD_USE_SSE2
                    return bit_xor(a, 0xff);
#elif SIMD_USE_NEON
                    return vmvnq_u8(a.native());
#elif SIMD_USE_ALTIVEC
                    return vec_nor(a.native(), a.native());
#elif SIMD_USE_MSA
                    return __msa_nor_v(a.native(), a.native());
#endif
                }

#if SIMD_USE_AVX2
                static inline uint8x32 i_bit_not(const uint8x32 &a) {
                    return bit_xor(a, 0xff);
                }
#endif

#if SIMD_USE_AVX512BW
                inline uint8<64> i_bit_not(const uint8<64> &a) {
                    __m512i n = a.native();
                    return _mm512_ternarylogic_epi32(n, n, n, 0x1);
                }
#endif

                // -----------------------------------------------------------------------------

                inline uint16<8> i_bit_not(const uint16<8> &a) {
                    return uint16<8>(i_bit_not(uint8<16>(a)));
                }

#if SIMD_USE_AVX2
                inline uint16<16> i_bit_not(const uint16<16> &a) {
                    return uint16<16>(i_bit_not(uint8<32>(a)));
                }
#endif

#if SIMD_USE_AVX512BW
                inline uint16<32> i_bit_not(const uint16<32> &a) {
                    __m512i n = a.native();
                    return _mm512_ternarylogic_epi32(n, n, n, 0x1);
                }
#endif

                // -----------------------------------------------------------------------------

                static inline uint32<4> i_bit_not(const uint32<4> &a) {
                    return uint32<4>(i_bit_not(uint8<16>(a)));
                }

#if SIMD_USE_AVX2
                static inline uint32<8> i_bit_not(const uint32<8> &a) {
                    return uint32<8>(i_bit_not(uint8<32>(a)));
                }
#endif

#if SIMD_USE_AVX512F
                static inline uint32<16> i_bit_not(const uint32<16> &a) {
                    __m512i n = a.native();
                    return _mm512_ternarylogic_epi32(n, n, n, 0x1);
                }
#endif

                // -----------------------------------------------------------------------------

                static inline uint64<2> i_bit_not(const uint64<2> &a) {
#if SIMD_USE_NULL || (SIMD_USE_ALTIVEC && !SIMD_USE_VSX_207)
                    uint64x2 r;
                    for (unsigned i = 0; i < a.length; i++) {
                        r.el(i) = ~a.el(i);
                    }
                    return r;
#else
                    return uint64<2>(i_bit_not(uint8<16>(a)));
#endif
                }

#if SIMD_USE_AVX2
                static inline uint64<4> i_bit_not(const uint64<4> &a) {
                    return uint64<4>(i_bit_not(uint8<32>(a)));
                }
#endif

#if SIMD_USE_AVX512F
                static inline uint64<8> i_bit_not(const uint64<8> &a) {
                    __m512i n = a.native();
                    return _mm512_ternarylogic_epi64(n, n, n, 0x1);
                }
#endif

                // -----------------------------------------------------------------------------

                static inline mask_int8x16 i_bit_not(const mask_int8x16 &a) {
#if SIMD_USE_NULL
                    return detail::null::bit_not_mm(a);
#else
                    return to_mask(i_bit_not(uint8x16(a)));
#endif
                }

                static inline mask_int16x8 i_bit_not(const mask_int16x8 &a) {
#if SIMD_USE_NULL
                    return detail::null::bit_not_mm(a);
#else
                    return to_mask(i_bit_not(uint16x8(a)));
#endif
                }

                static inline mask_int32x4 i_bit_not(const mask_int32x4 &a) {
#if SIMD_USE_NULL
                    return detail::null::bit_not_mm(a);
#else
                    return to_mask(i_bit_not(uint32x4(a)));
#endif
                }

                static inline mask_int64x2 i_bit_not(const mask_int64x2 &a) {
#if SIMD_USE_NULL || (SIMD_USE_ALTIVEC && !SIMD_USE_VSX_207)
                    return detail::null::bit_not_mm(a);
#else
                    return to_mask(i_bit_not(uint64x2(a)));
#endif
                }

#if SIMD_USE_AVX2 && !SIMD_USE_AVX512VL
                static inline mask_int8x32 i_bit_not(const mask_int8x32 &a) {
                    return i_bit_not(uint8x32(a));
                }
                static inline mask_int16x16 i_bit_not(const mask_int16x16 &a) {
                    return i_bit_not(uint16x16(a));
                }
                static inline mask_int32x8 i_bit_not(const mask_int32x8 &a) {
                    return i_bit_not(uint32x8(a));
                }
                static inline mask_int64x4 i_bit_not(const mask_int64x4 &a) {
                    return i_bit_not(uint64x4(a));
                }
#endif

#if SIMD_USE_AVX512VL
                static inline mask_int8x32 i_bit_not(const mask_int8x32 &a) {
                    return ~a.native();
                }
                static inline mask_int16x16 i_bit_not(const mask_int16x16 &a) {
                    return ~a.native();
                }
                static inline mask_int32x8 i_bit_not(const mask_int32x8 &a) {
                    return ~a.native();
                }
                static inline mask_int64x4 i_bit_not(const mask_int64x4 &a) {
                    return ~a.native();
                }
#endif

#if SIMD_USE_AVX512F
                static inline mask_int32<16> i_bit_not(const mask_int32<16> &a) {
                    return _mm512_knot(a.native());
                }

                static inline mask_int64<8> i_bit_not(const mask_int64<8> &a) {
                    return _mm512_knot(a.native());
                }
#endif

#if SIMD_USE_AVX512BW
                inline mask_int8<64> i_bit_not(const mask_int8<64> &a) {
                    return ~a.native();
                }

                inline mask_int16<32> i_bit_not(const mask_int16<32> &a) {
                    return ~a.native();
                }
#endif

                // -----------------------------------------------------------------------------

                static inline float32x4 i_bit_not(const float32x4 &a) {
#if SIMD_USE_SSE2
                    return bit_xor(a, 0xffffffff);
#elif SIMD_USE_NEON_FLT_SP
                    return vreinterpretq_f32_u32(vmvnq_u32(vreinterpretq_u32_f32(a.native())));
#elif SIMD_USE_ALTIVEC
                    return vec_nor(a.native(), a.native());
#elif SIMD_USE_NULL || SIMD_USE_MSA || SIMD_USE_NEON_NO_FLT_SP
                    return float32x4(i_bit_not(uint32x4(a)));
#endif
                }

#if SIMD_USE_AVX
                static inline float32x8 i_bit_not(const float32x8 &a) {
                    return bit_xor(a, 0xffffffff);
                }
#endif

#if SIMD_USE_AVX512F
                static inline float32<16> i_bit_not(const float32<16> &a) {
                    __m512i n = _mm512_castps_si512(a.native());
                    n = _mm512_ternarylogic_epi32(n, n, n, 0x1);
                    return _mm512_castsi512_ps(n);
                }
#endif

                // -----------------------------------------------------------------------------

                static inline float64x2 i_bit_not(const float64x2 &a) {
#if SIMD_USE_SSE2
                    return bit_xor(a, 0xffffffffffffffff);
#elif SIMD_USE_NEON64
                    return vreinterpretq_f64_u32(vmvnq_u32(vreinterpretq_u32_f64(a.native())));
#elif SIMD_USE_VSX_206
                    return vec_nor(a.native(), a.native());
#elif SIMD_USE_NULL || SIMD_USE_NEON32 || SIMD_USE_ALTIVEC || SIMD_USE_MSA
                    return float64x2(i_bit_not(uint64x2(a)));
#endif
                }

#if SIMD_USE_AVX
                static inline float64x4 i_bit_not(const float64x4 &a) {
                    return bit_xor(a, 0xffffffffffffffff);
                }
#endif

#if SIMD_USE_AVX512F
                static inline float64<8> i_bit_not(const float64<8> &a) {
                    __m512i n = _mm512_castpd_si512(a.native());
                    n = _mm512_ternarylogic_epi64(n, n, n, 0x1);
                    return _mm512_castsi512_pd(n);
                }
#endif

                // -----------------------------------------------------------------------------

                static inline mask_float32x4 i_bit_not(const mask_float32x4 &a) {
#if SIMD_USE_NULL || SIMD_USE_NEON_NO_FLT_SP
                    return detail::null::bit_not_mm(a);
#else
                    return to_mask(i_bit_not(float32<4>(a)));
#endif
                }

#if SIMD_USE_AVX
                static inline mask_float32x8 i_bit_not(const mask_float32x8 &a) {
                    return to_mask(i_bit_not(float32x8(a)));
                }
#endif

#if SIMD_USE_AVX512F
                static inline mask_float32<16> i_bit_not(const mask_float32<16> &a) {
                    return _mm512_knot(a.native());
                }
#endif

                // -----------------------------------------------------------------------------

                static inline mask_float64x2 i_bit_not(const mask_float64x2 &a) {
#if SIMD_USE_NULL || SIMD_USE_NEON32 || (SIMD_USE_ALTIVEC && !SIMD_USE_VSX_206)
                    return detail::null::bit_not_mm(a);
#else
                    return to_mask(i_bit_not(float64x2(a)));
#endif
                }

#if SIMD_USE_AVX
                static inline mask_float64x4 i_bit_not(const mask_float64x4 &a) {
                    return to_mask(i_bit_not(float64x4(a)));
                }
#endif

#if SIMD_USE_AVX512F
                static inline mask_float64<8> i_bit_not(const mask_float64<8> &a) {
                    return _mm512_knot(a.native());
                }
#endif

                // -----------------------------------------------------------------------------

                template <class V> inline V i_bit_not(const V &a) {
                    SIMD_VEC_ARRAY_IMPL1(V, i_bit_not, a)
                }

            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
