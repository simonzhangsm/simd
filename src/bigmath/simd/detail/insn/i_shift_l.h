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

#ifndef SIMD_DETAIL_INSN_I_SHIFT_L_H
#define SIMD_DETAIL_INSN_I_SHIFT_L_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/not_implemented.h>
#include <bigmath/simd/core/bit_and.h>
#include <bigmath/simd/core/bit_andnot.h>
#include <bigmath/simd/core/set_splat.h>
#include <bigmath/simd/detail/insn/i_shift.h>
#include <bigmath/simd/detail/null/math.h>
#include <bigmath/simd/detail/vector_array_macros.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {


                static inline uint8x16 i_shift_l(const uint8x16 &a, unsigned count) {
#if SIMD_USE_NULL
                    return detail::null::shift_l(a, count);
#elif SIMD_USE_AVX2
                    uint16x8 mask, a16;
                    uint16_t mask1 = (0x00ff >> (8 - count)) << 8;

                    a16 = a;
                    mask = splat(mask1);
                    a16 = shift_l(a16, count);
                    a16 = bit_andnot(a16, mask);
                    return uint8x16(a16);
#elif SIMD_USE_SSE2
                    uint16x8 mask, a16;
                    mask = make_ones();
                    mask = shift_r(mask, 16 - count);
                    mask = shift_l(mask, 8);

                    a16 = a;
                    a16 = shift_l(a16, count);
                    a16 = bit_andnot(a16, mask);
                    return uint8x16(a16);
#elif SIMD_USE_NEON
                    int8x16 shift = splat(count);
                    return vshlq_u8(a.native(), shift.native());
#elif SIMD_USE_ALTIVEC
                    uint8x16 shift = splat(count);
                    return vec_sl(a.native(), shift.native());
#elif SIMD_USE_MSA
                    int8x16 shift = splat(count);
                    return (v16u8)__msa_sll_b((v16i8)a.native(), shift.native());
#endif
                }

#if SIMD_USE_AVX2
                static inline uint8x32 i_shift_l(const uint8x32 &a, unsigned count) {
                    uint16x16 mask, a16;
                    uint16_t mask1 = (0x00ff >> (8 - count)) << 8;

                    a16 = a;
                    mask = splat(mask1);
                    a16 = shift_l(a16, count);
                    a16 = bit_andnot(a16, mask);
                    return uint8<32>(a16);
                }
#endif

#if SIMD_USE_AVX512BW
                inline uint8<64> i_shift_l(const uint8<64> &a, unsigned count) {
                    uint16<32> mask, a16;
                    uint16_t mask1 = (0x00ff >> (8 - count)) << 8;

                    a16 = a;
                    mask = splat(mask1);
                    a16 = shift_l(a16, count);
                    a16 = bit_andnot(a16, mask);
                    return uint8<64>(a16);
                }
#endif

                // -----------------------------------------------------------------------------

                static inline uint16x8 i_shift_l(const uint16x8 &a, unsigned count) {
#if SIMD_USE_NULL
                    return detail::null::shift_l(a, count);
#elif SIMD_USE_SSE2
                    return _mm_sll_epi16(a.native(), _mm_cvtsi32_si128(count));
#elif SIMD_USE_NEON
                    int16x8 shift = splat(count);
                    return vshlq_u16(a.native(), shift.native());
#elif SIMD_USE_ALTIVEC
                    uint16x8 shift = splat(count);
                    return vec_sl(a.native(), shift.native());
#elif SIMD_USE_MSA
                    int16x8 shift = splat(count);
                    return (v8u16)__msa_sll_h((v8i16)a.native(), shift.native());
#endif
                }

#if SIMD_USE_AVX2
                static inline uint16x16 i_shift_l(const uint16x16 &a, unsigned count) {
#if SIMD_WORKAROUND_AVX2_SHIFT_INTRINSICS
                    __m256i r = a.native();
                    __m128i x = _mm_cvtsi32_si128(count);
                    __asm("vpsllw	%1, %2, %0" : "=x"(r) : "x"(x), "x"(r));
                    return r;
#else
                    return _mm256_sll_epi16(a.native(), _mm_cvtsi32_si128(count));
#endif
                }
#endif

#if SIMD_USE_AVX512BW
                inline uint16<32> i_shift_l(const uint16<32> &a, unsigned count) {
                    return _mm512_sll_epi16(a.native(), _mm_cvtsi32_si128(count));
                }
#endif

                // -----------------------------------------------------------------------------

                static inline uint32x4 i_shift_l(const uint32x4 &a, unsigned count) {
#if SIMD_USE_NULL
                    return detail::null::shift_l(a, count);
#elif SIMD_USE_SSE2
                    return _mm_sll_epi32(a.native(), _mm_cvtsi32_si128(count));
#elif SIMD_USE_NEON
                    int32x4 shift = splat(count);
                    return vshlq_u32(a.native(), shift.native());
#elif SIMD_USE_ALTIVEC
                    uint32x4 shift = splat(count);
                    return vec_sl(a.native(), shift.native());
#elif SIMD_USE_MSA
                    int32x4 shift = splat(count);
                    return (v4u32)__msa_sll_w((v4i32)a.native(), shift.native());
#endif
                }

#if SIMD_USE_AVX2
                static inline uint32x8 i_shift_l(const uint32x8 &a, unsigned count) {
#if SIMD_WORKAROUND_AVX2_SHIFT_INTRINSICS
                    __m256i r = a.native();
                    __m128i x = _mm_cvtsi32_si128(count);
                    __asm("vpslld	%1, %2, %0" : "=x"(r) : "x"(x), "x"(r));
                    return r;
#else
                    return _mm256_sll_epi32(a.native(), _mm_cvtsi32_si128(count));
#endif
                }
#endif

#if SIMD_USE_AVX512F
                static inline uint32<16> i_shift_l(const uint32<16> &a, unsigned count) {
                    return _mm512_sll_epi32(a.native(), _mm_cvtsi32_si128(count));
                }
#endif

                // -----------------------------------------------------------------------------

                static inline uint64x2 i_shift_l(const uint64x2 &a, unsigned count) {
#if SIMD_USE_SSE2
                    return _mm_sll_epi64(a.native(), _mm_cvtsi32_si128(count));
#elif SIMD_USE_NEON
                    int64x2 shift = splat(count);
                    return vshlq_u64(a.native(), shift.native());
#elif SIMD_USE_VSX_207
                    uint64x2 shift = splat(count);
                    return vec_sl(a.native(), shift.native());
#elif SIMD_USE_MSA
                    int32x4 shift = splat(count);
                    return (v2u64)__msa_sll_d((v2i64)a.native(), (v2i64)shift.native());
#elif SIMD_USE_NULL || SIMD_USE_ALTIVEC
                    return detail::null::shift_l(a, count);
#endif
                }

#if SIMD_USE_AVX2
                static inline uint64x4 i_shift_l(const uint64x4 &a, unsigned count) {
#if SIMD_WORKAROUND_AVX2_SHIFT_INTRINSICS
                    __m256i r = a.native();
                    __m128i x = _mm_cvtsi32_si128(count);
                    __asm("vpsllq	%1, %2, %0" : "=x"(r) : "x"(x), "x"(r));
                    return r;
#else
                    return _mm256_sll_epi64(a.native(), _mm_cvtsi32_si128(count));
#endif
                }
#endif

#if SIMD_USE_AVX512F
                static inline uint64<8> i_shift_l(const uint64<8> &a, unsigned count) {
                    return _mm512_sll_epi64(a.native(), _mm_cvtsi32_si128(count));
                }
#endif

                // -----------------------------------------------------------------------------

                template <class V> inline V i_shift_l(const V &a, unsigned count) {
                    SIMD_VEC_ARRAY_IMPL2S(V, i_shift_l, a, count);
                }

                // -----------------------------------------------------------------------------

                template <unsigned count, unsigned N> inline uint8<N> sse_shift_l_8(const uint8<N> &a) {
                    uint8_t mask1 = 0xff >> count;
                    uint8<N> mask = make_uint(mask1);

                    uint16<N / 2> a16 = (uint16<N / 2>)bit_and(a, mask);
                    a16 = shift_l<count>(a16);

                    return uint8<N>(a16);
                }

                template <unsigned count> inline uint8x16 i_shift_l(const uint8x16 &a) {
                    static_assert(count < 8, "Shift out of bounds");
#if SIMD_USE_NULL
                    return i_shift_l(a, count);
#elif SIMD_USE_SSE2
                    return sse_shift_l_8<count>(a);
#elif SIMD_USE_NEON
                    return vshlq_n_u8(a.native(), count);
#elif SIMD_USE_ALTIVEC
                    uint8x16 shift = make_uint(count);
                    return vec_sl(a.native(), shift.native());
#elif SIMD_USE_MSA
                    return (v16u8)__msa_slli_b((v16i8)a.native(), count);
#endif
                }

#if SIMD_USE_AVX2
                template <unsigned count> inline uint8<32> i_shift_l(const uint8<32> &a) {
                    static_assert(count < 8, "Shift out of bounds");
                    return sse_shift_l_8<count>(a);
                }
#endif

#if SIMD_USE_AVX512BW
                template <unsigned count> inline uint8<64> i_shift_l(const uint8<64> &a) {
                    static_assert(count < 8, "Shift out of bounds");
                    return sse_shift_l_8<count>(a);
                }
#endif

                // -----------------------------------------------------------------------------

                template <unsigned count> inline uint16x8 i_shift_l(const uint16x8 &a) {
                    static_assert(count < 16, "Shift out of bounds");
#if SIMD_USE_NULL
                    return i_shift_l(a, count);
#elif SIMD_USE_SSE2
                    return _mm_slli_epi16(a.native(), count);
#elif SIMD_USE_NEON
                    return vshlq_n_u16(a.native(), count);
#elif SIMD_USE_ALTIVEC
                    uint16x8 shift = make_uint(count);
                    return vec_sl(a.native(), shift.native());
#elif SIMD_USE_MSA
                    return (v8u16)__msa_slli_h((v8i16)a.native(), count);
#endif
                }

#if SIMD_USE_AVX2
                template <unsigned count> inline uint16x16 i_shift_l(const uint16x16 &a) {
                    static_assert(count < 16, "Shift out of bounds");
                    return _mm256_slli_epi16(a.native(), count);
                }
#endif

#if SIMD_USE_AVX512BW
                template <unsigned count> inline uint16<32> i_shift_l(const uint16<32> &a) {
                    static_assert(count < 16, "Shift out of bounds");
                    return _mm512_slli_epi16(a.native(), count);
                }
#endif

                // -----------------------------------------------------------------------------

                template <unsigned count> inline uint32x4 i_shift_l(const uint32x4 &a) {
                    static_assert(count < 32, "Shift out of bounds");
#if SIMD_USE_NULL
                    return i_shift_l(a, count);
#elif SIMD_USE_SSE2
                    return _mm_slli_epi32(a.native(), count);
#elif SIMD_USE_NEON
                    return vshlq_n_u32(a.native(), count);
#elif SIMD_USE_ALTIVEC
                    uint32x4 shift = make_uint(count);
                    return vec_sl(a.native(), shift.native());
#elif SIMD_USE_MSA
                    return (v4u32)__msa_slli_w((v4i32)a.native(), count);
#endif
                }

#if SIMD_USE_AVX2
                template <unsigned count> inline uint32x8 i_shift_l(const uint32x8 &a) {
                    static_assert(count < 32, "Shift out of bounds");
                    return _mm256_slli_epi32(a.native(), count);
                }
#endif

#if SIMD_USE_AVX512F
                template <unsigned count> inline uint32<16> i_shift_l(const uint32<16> &a) {
                    static_assert(count < 32, "Shift out of bounds");
                    return _mm512_slli_epi32(a.native(), count);
                }
#endif

                // -----------------------------------------------------------------------------

                template <unsigned count> inline uint64x2 i_shift_l(const uint64x2 &a) {
                    static_assert(count < 64, "Shift out of bounds");
#if SIMD_USE_NULL || SIMD_USE_ALTIVEC
                    return i_shift_l(a, count);
#elif SIMD_USE_SSE2
                    return _mm_slli_epi64(a.native(), count);
#elif SIMD_USE_NEON
                    return vshlq_n_u64(a.native(), count);
#elif SIMD_USE_MSA
                    return (v2u64)__msa_slli_d((v2i64)a.native(), count);
#else
                    return SIMD_NOT_IMPLEMENTED1(a);
#endif
                }

#if SIMD_USE_AVX2
                template <unsigned count> inline uint64x4 i_shift_l(const uint64x4 &a) {
                    static_assert(count < 64, "Shift out of bounds");
                    return _mm256_slli_epi64(a.native(), count);
                }
#endif

#if SIMD_USE_AVX512F
                template <unsigned count> inline uint64<8> i_shift_l(const uint64<8> &a) {
                    static_assert(count < 64, "Shift out of bounds");
                    return _mm512_slli_epi64(a.native(), count);
                }
#endif

                // -----------------------------------------------------------------------------

                template <unsigned count, class V> inline V i_shift_l(const V &a) {
                    SIMD_VEC_ARRAY_IMPL1(V, i_shift_l<count>, a);
                }

                template <bool no_shift> struct i_shift_l_wrapper {
                    template <unsigned count, class V> static inline V run(const V &arg) {
                        return i_shift_l<count>(arg);
                    }
                };
                template <> struct i_shift_l_wrapper<true> {
                    template <unsigned count, class V> static inline V run(const V &arg) {
                        return arg;
                    }
                };

            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
