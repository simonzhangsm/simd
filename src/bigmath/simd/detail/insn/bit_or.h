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

#ifndef SIMD_DETAIL_INSN_BIT_OR_H
#define SIMD_DETAIL_INSN_BIT_OR_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/core/to_mask.h>
#include <bigmath/simd/detail/null/bitwise.h>
#include <bigmath/simd/detail/vector_array_macros.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {

                // -----------------------------------------------------------------------------
                // uint8, uint8
                static inline uint8<16> i_bit_or(const uint8<16> &a, const uint8<16> &b) {
#if SIMD_USE_NULL
                    return detail::null::bit_or(uint8x16(a), uint8x16(b));
#elif SIMD_USE_SSE2
                    return _mm_or_si128(a.native(), b.native());
#elif SIMD_USE_NEON
                    return vorrq_u8(a.native(), b.native());
#elif SIMD_USE_ALTIVEC
                    return vec_or(a.native(), b.native());
#elif SIMD_USE_MSA
                    return __msa_or_v(a.native(), b.native());
#endif
                }

#if SIMD_USE_AVX2
                static inline uint8<32> i_bit_or(const uint8<32> &a, const uint8<32> &b) {
                    return _mm256_or_si256(a.native(), b.native());
                }
#endif

#if SIMD_USE_AVX512BW
                inline uint8<64> i_bit_or(const uint8<64> &a, const uint8<64> &b) {
                    return _mm512_or_si512(a.native(), b.native());
                }
#endif

                // -----------------------------------------------------------------------------
                // mask_int8, mask_int8
                static inline mask_int8<16> i_bit_or(const mask_int8<16> &a, const mask_int8<16> &b) {
#if SIMD_USE_NULL
                    return detail::null::bit_or_mm(a, b);
#elif SIMD_USE_AVX512VL
                    return a.native() | b.native();
#else
                    return to_mask(i_bit_or(uint8<16>(a), uint8<16>(b)));
#endif
                }

#if SIMD_USE_AVX2
                static inline mask_int8<32> i_bit_or(const mask_int8<32> &a, const mask_int8<32> &b) {
#if SIMD_USE_AVX512VL
                    return a.native() | b.native();
#else
                    return to_mask(i_bit_or(uint8<32>(a), uint8<32>(b)));
#endif
                }
#endif

#if SIMD_USE_AVX512BW
                inline mask_int8<64> i_bit_or(const mask_int8<64> &a, const mask_int8<64> &b) {
                    return a.native() | b.native();
                }
#endif

                // -----------------------------------------------------------------------------
                // uint16, uint16
                static inline uint16<8> i_bit_or(const uint16<8> &a, const uint16<8> &b) {
                    return uint16<8>(i_bit_or(uint8<16>(a), uint8<16>(b)));
                }

#if SIMD_USE_AVX2
                static inline uint16<16> i_bit_or(const uint16<16> &a, const uint16<16> &b) {
                    return _mm256_or_si256(a.native(), b.native());
                }
#endif

#if SIMD_USE_AVX512BW
                inline uint16<32> i_bit_or(const uint16<32> &a, const uint16<32> &b) {
                    return _mm512_or_si512(a.native(), b.native());
                }
#endif

                // -----------------------------------------------------------------------------
                // mask_int16, mask_int16
                static inline mask_int16<8> i_bit_or(const mask_int16<8> &a, const mask_int16<8> &b) {
#if SIMD_USE_NULL
                    return detail::null::bit_or_mm(a, b);
#elif SIMD_USE_AVX512VL
                    return a.native() | b.native();
#else
                    return to_mask(i_bit_or(uint16<8>(a), uint16<8>(b)));
#endif
                }

#if SIMD_USE_AVX2
                static inline mask_int16<16> i_bit_or(const mask_int16<16> &a, const mask_int16<16> &b) {
#if SIMD_USE_AVX512VL
                    return a.native() | b.native();
#else
                    return to_mask(i_bit_or(uint16<16>(a), uint16<16>(b)));
#endif
                }
#endif

#if SIMD_USE_AVX512BW
                inline mask_int16<32> i_bit_or(const mask_int16<32> &a, const mask_int16<32> &b) {
                    return a.native() | b.native();
                }
#endif

                // -----------------------------------------------------------------------------
                // uint32, uint32
                static inline uint32<4> i_bit_or(const uint32<4> &a, const uint32<4> &b) {
                    return uint32<4>(i_bit_or(uint8<16>(a), uint8<16>(b)));
                }

#if SIMD_USE_AVX2
                static inline uint32<8> i_bit_or(const uint32<8> &a, const uint32<8> &b) {
                    return _mm256_or_si256(a.native(), b.native());
                }
#endif

#if SIMD_USE_AVX512F
                static inline uint32<16> i_bit_or(const uint32<16> &a, const uint32<16> &b) {
                    return _mm512_or_epi32(a.native(), b.native());
                }
#endif

                // -----------------------------------------------------------------------------
                // mask_int32, mask_int32
                static inline mask_int32<4> i_bit_or(const mask_int32<4> &a, const mask_int32<4> &b) {
#if SIMD_USE_NULL
                    return detail::null::bit_or_mm(a, b);
#elif SIMD_USE_AVX512VL
                    return a.native() | b.native();
#else
                    return to_mask(i_bit_or(uint32<4>(a), uint32<4>(b)));
#endif
                }

#if SIMD_USE_AVX2
                static inline mask_int32<8> i_bit_or(const mask_int32<8> &a, const mask_int32<8> &b) {
#if SIMD_USE_AVX512VL
                    return a.native() | b.native();
#else
                    return to_mask(i_bit_or(uint32<8>(a), uint32<8>(b)));
#endif
                }
#endif

#if SIMD_USE_AVX512F
                static inline mask_int32<16> i_bit_or(const mask_int32<16> &a, const mask_int32<16> &b) {
                    return _mm512_kor(a.native(), b.native());
                }
#endif

                // -----------------------------------------------------------------------------
                // uint64, uint64
                static inline uint64<2> i_bit_or(const uint64<2> &a, const uint64<2> &b) {
#if SIMD_USE_NULL || (SIMD_USE_ALTIVEC && !SIMD_USE_VSX_207)
                    return detail::null::bit_or(a, b);
#else
                    return uint64<2>(i_bit_or(uint8<16>(a), uint8<16>(b)));
#endif
                }

#if SIMD_USE_AVX2
                static inline uint64<4> i_bit_or(const uint64<4> &a, const uint64<4> &b) {
                    return _mm256_or_si256(a.native(), b.native());
                }
#endif

#if SIMD_USE_AVX512F
                static inline uint64<8> i_bit_or(const uint64<8> &a, const uint64<8> &b) {
                    return _mm512_or_epi64(a.native(), b.native());
                }
#endif

                // -----------------------------------------------------------------------------
                // mask_int64, mask_int64
                static inline mask_int64<2> i_bit_or(const mask_int64<2> &a, const mask_int64<2> &b) {
#if SIMD_USE_NULL || (SIMD_USE_ALTIVEC && !SIMD_USE_VSX_207)
                    return detail::null::bit_or_mm(a, b);
#elif SIMD_USE_AVX512VL
                    return a.native() | b.native();
#else
                    return to_mask(i_bit_or(uint64<2>(a), uint64<2>(b)));
#endif
                }

#if SIMD_USE_AVX2
                static inline mask_int64<4> i_bit_or(const mask_int64<4> &a, const mask_int64<4> &b) {
#if SIMD_USE_AVX512VL
                    return a.native() | b.native();
#else
                    return to_mask(i_bit_or(uint64<4>(a), uint64<4>(b)));
#endif
                }
#endif

#if SIMD_USE_AVX512F
                static inline mask_int64<8> i_bit_or(const mask_int64<8> &a, const mask_int64<8> &b) {
                    return _mm512_kor(a.native(), b.native());
                }
#endif

                // -----------------------------------------------------------------------------
                // float32, float32
                static inline float32<4> i_bit_or(const float32<4> &a, const float32<4> &b) {
#if SIMD_USE_NULL || SIMD_USE_NEON_NO_FLT_SP
                    return detail::null::bit_or(a, b);
#elif SIMD_USE_SSE2
                    return _mm_or_ps(a.native(), b.native());
#elif SIMD_USE_NEON
                    return vreinterpretq_f32_u32(
                        vorrq_u32(vreinterpretq_u32_f32(a.native()), vreinterpretq_u32_f32(b.native())));
#elif SIMD_USE_ALTIVEC
                    return vec_or(a.native(), b.native());
#elif SIMD_USE_MSA
                    return (float32<4>)i_bit_or(uint8<16>(a), uint8<16>(b));
#endif
                }

#if SIMD_USE_AVX
                static inline float32<8> i_bit_or(const float32<8> &a, const float32<8> &b) {
                    return _mm256_or_ps(a.native(), b.native());
                }
#endif

#if SIMD_USE_AVX512F
                static inline float32<16> i_bit_or(const float32<16> &a, const float32<16> &b) {
#if SIMD_USE_AVX512DQ
                    return _mm512_or_ps(a.native(), b.native());
#else
                    return (float32<16>)i_bit_or(uint32<16>(a), uint32<16>(b));
#endif
                }
#endif

                // -----------------------------------------------------------------------------
                // mask_float32, mask_float32
                static inline mask_float32<4> i_bit_or(const mask_float32<4> &a, const mask_float32<4> &b) {
#if SIMD_USE_NULL || SIMD_USE_NEON_NO_FLT_SP
                    return detail::null::bit_or_mm(a, b);
#elif SIMD_USE_AVX512VL
                    return a.native() | b.native();
#else
                    return to_mask(i_bit_or(float32<4>(a), float32<4>(b)));
#endif
                }

#if SIMD_USE_AVX
                static inline mask_float32<8> i_bit_or(const mask_float32<8> &a, const mask_float32<8> &b) {
#if SIMD_USE_AVX512VL
                    return a.native() | b.native();
#else
                    return to_mask(i_bit_or(float32<8>(a), float32<8>(b)));
#endif
                }
#endif

#if SIMD_USE_AVX512F
                static inline mask_float32<16> i_bit_or(const mask_float32<16> &a, const mask_float32<16> &b) {
                    return _mm512_kor(a.native(), b.native());
                }
#endif

                // -----------------------------------------------------------------------------
                // float64, float64
                static inline float64<2> i_bit_or(const float64<2> &a, const float64<2> &b) {
#if SIMD_USE_SSE2
                    return _mm_or_pd(a.native(), b.native());
#elif SIMD_USE_NEON64
                    return vreinterpretq_f64_u64(
                        vorrq_u64(vreinterpretq_u64_f64(a.native()), vreinterpretq_u64_f64(b.native())));
#elif SIMD_USE_VSX_206
                    return vec_or(a.native(), b.native());
#elif SIMD_USE_MSA
                    return (float64<2>)i_bit_or(uint8<16>(a), uint8<16>(b));
#elif SIMD_USE_NULL || SIMD_USE_NEON || SIMD_USE_ALTIVEC
                    return detail::null::bit_or(a, b);
#endif
                }

#if SIMD_USE_AVX
                static inline float64<4> i_bit_or(const float64<4> &a, const float64<4> &b) {
                    return _mm256_or_pd(a.native(), b.native());
                }
#endif

#if SIMD_USE_AVX512F
                static inline float64<8> i_bit_or(const float64<8> &a, const float64<8> &b) {
#if SIMD_USE_AVX512DQ
                    return _mm512_or_pd(a.native(), b.native());
#else
                    return (float64<8>)i_bit_or(uint64<8>(a), uint64<8>(b));
#endif
                }
#endif

                // -----------------------------------------------------------------------------
                // mask_float64, mask_float64
                static inline mask_float64<2> i_bit_or(const mask_float64<2> &a, const mask_float64<2> &b) {
#if SIMD_USE_NULL || SIMD_USE_NEON32 || (SIMD_USE_ALTIVEC && !SIMD_USE_VSX_206)
                    return detail::null::bit_or_mm(a, b);
#elif SIMD_USE_AVX512VL
                    return a.native() | b.native();
#else
                    return to_mask(i_bit_or(float64<2>(a), float64<2>(b)));
#endif
                }

#if SIMD_USE_AVX
                static inline mask_float64<4> i_bit_or(const mask_float64<4> &a, const mask_float64<4> &b) {
#if SIMD_USE_AVX512VL
                    return a.native() | b.native();
#else
                    return to_mask(i_bit_or(float64<4>(a), float64<4>(b)));
#endif
                }
#endif

#if SIMD_USE_AVX512F
                static inline mask_float64<8> i_bit_or(const mask_float64<8> &a, const mask_float64<8> &b) {
                    return _mm512_kor(a.native(), b.native());
                }
#endif

                // -----------------------------------------------------------------------------

                template <class V, class VM> inline V i_bit_or(const V &a, const VM &b) {
                    SIMD_VEC_ARRAY_IMPL2(V, i_bit_or, a, b)
                }

            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
