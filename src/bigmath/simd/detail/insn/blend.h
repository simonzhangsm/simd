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

#ifndef SIMD_DETAIL_INSN_BLEND_H
#define SIMD_DETAIL_INSN_BLEND_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/core/bit_and.h>
#include <bigmath/simd/core/bit_andnot.h>
#include <bigmath/simd/core/bit_or.h>
#include <bigmath/simd/core/to_mask.h>
#include <bigmath/simd/detail/null/shuffle.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {

                // -----------------------------------------------------------------------------
                // uint8, uint8, uint8

                static inline uint8<16> i_blend(const uint8<16> &con, const uint8<16> &coff, const uint8<16> &mask) {
                    uint8<16> on = con, off = coff;
#if SIMD_USE_NULL
                    return detail::null::blend(on, off, mask);
#elif SIMD_USE_AVX2
                    return _mm_blendv_epi8(off.native(), on.native(), mask.native());
#elif SIMD_USE_XOP
                    return _mm_cmov_si128(on.native(), off.native(), mask.native());
#elif SIMD_USE_SSE2
                    // _mm_blendv_epi8 needs xmm0 and occupies the shuffle ports, yet saves
                    // only one uop
                    uint8<16> r;
                    on = bit_and(on, mask);
                    off = bit_andnot(off, mask);
                    r = bit_or(on, off);
                    return r;
#elif SIMD_USE_NEON
                    return vbslq_u8(mask.native(), on.native(), off.native());
#elif SIMD_USE_ALTIVEC
                    return vec_sel(off.native(), on.native(), mask.native());
#elif SIMD_USE_MSA
                    return __msa_bsel_v(mask.native(), off.native(), on.native());
#endif
                }

#if SIMD_USE_AVX2
                static inline uint8<32> i_blend(const uint8<32> &on, const uint8<32> &off, const uint8<32> &mask) {
                    return _mm256_blendv_epi8(off.native(), on.native(), mask.native());
                }
#endif

#if SIMD_USE_AVX512BW
                inline uint8<64> i_blend(const uint8<64> &on, const uint8<64> &off, const uint8<64> &mask) {
                    return _mm512_ternarylogic_epi32(on.native(), off.native(), mask.native(), 0xe4);
                }
#endif

                // -----------------------------------------------------------------------------
                // uint8, uint8, mask_int8

                static inline uint8<16> i_blend(const uint8<16> &on, const uint8<16> &off, const mask_int8<16> &mask) {
#if SIMD_USE_NULL
                    return detail::null::blend_mask(on, off, mask);
#else
                    return i_blend(on, off, uint8<16>(mask));
#endif
                }

#if SIMD_USE_AVX2
                static inline uint8<32> i_blend(const uint8<32> &on, const uint8<32> &off, const mask_int8<32> &mask) {
                    return i_blend(on, off, uint8<32>(mask));
                }
#endif

#if SIMD_USE_AVX512BW
                inline uint8<64> i_blend(const uint8<64> &on, const uint8<64> &off, const mask_int8<64> &mask) {
                    return _mm512_mask_blend_epi8(mask.native(), off.native(), on.native());
                }
#endif

                // -----------------------------------------------------------------------------
                // mask_int8, mask_int8, mask_int8

                static inline mask_int8<16> i_blend(const mask_int8<16> &on,
                                                    const mask_int8<16> &off,
                                                    const mask_int8<16> &mask) {
#if SIMD_USE_NULL
                    return detail::null::blend_mask(on, off, mask);
#elif SIMD_USE_AVX512VL
                    return (on.native() & mask.native()) | (off.native() & ~(mask.native()));
#else
                    return mask_int8<16>(i_blend(uint8<16>(on), uint8<16>(off), uint8<16>(mask)));
#endif
                }

#if SIMD_USE_AVX2
                static inline mask_int8<32> i_blend(const mask_int8<32> &on,
                                                    const mask_int8<32> &off,
                                                    const mask_int8<32> &mask) {
#if SIMD_USE_AVX512VL
                    return (on.native() & mask.native()) | (off.native() & ~(mask.native()));
#else
                    return mask_int8<32>(i_blend(uint8<32>(on), uint8<32>(off), uint8<32>(mask)));
#endif
                }
#endif

#if SIMD_USE_AVX512BW
                inline mask_int8<64> i_blend(const mask_int8<64> &on,
                                             const mask_int8<64> &off,
                                             const mask_int8<64> &mask) {
                    return (on.native() & mask.native()) | (off.native() & ~(mask.native()));
                }
#endif

                // -----------------------------------------------------------------------------
                // uint16, uint16, uint16

                static inline uint16<8> i_blend(const uint16<8> &on, const uint16<8> &off, const uint16<8> &mask) {
                    return uint16<8>(i_blend(uint8<16>(on), uint8<16>(off), uint8<16>(mask)));
                }

#if SIMD_USE_AVX2
                static inline uint16<16> i_blend(const uint16<16> &on, const uint16<16> &off, const uint16<16> &mask) {
                    return _mm256_blendv_epi8(off.native(), on.native(), mask.native());
                }
#endif

#if SIMD_USE_AVX512BW
                inline uint16<32> i_blend(const uint16<32> &on, const uint16<32> &off, const uint16<32> &mask) {
                    return _mm512_ternarylogic_epi32(on.native(), off.native(), mask.native(), 0xe4);
                }
#endif

                // -----------------------------------------------------------------------------
                // uint16, uint16, mask_int16

                static inline uint16<8> i_blend(const uint16<8> &on, const uint16<8> &off, const mask_int16<8> &mask) {
#if SIMD_USE_NULL
                    return detail::null::blend_mask(on, off, mask);
#else
                    return uint16<8>(i_blend(uint8<16>(on), uint8<16>(off), uint8<16>(mask)));
#endif
                }

#if SIMD_USE_AVX2
                static inline uint16<16> i_blend(const uint16<16> &on,
                                                 const uint16<16> &off,
                                                 const mask_int16<16> &mask) {
                    return i_blend(on, off, uint16<16>(mask));
                }
#endif

#if SIMD_USE_AVX512BW
                inline uint16<32> i_blend(const uint16<32> &on, const uint16<32> &off, const mask_int16<32> &mask) {
                    return _mm512_mask_blend_epi16(mask.native(), off.native(), on.native());
                }
#endif

                // -----------------------------------------------------------------------------
                // mask_int16, mask_int16, mask_int16

                static inline mask_int16<8> i_blend(const mask_int16<8> &on,
                                                    const mask_int16<8> &off,
                                                    const mask_int16<8> &mask) {
#if SIMD_USE_NULL
                    return detail::null::blend_mask(on, off, mask);
#elif SIMD_USE_AVX512VL
                    return (on.native() & mask.native()) | (off.native() & ~(mask.native()));
#else
                    return to_mask(i_blend(uint16<8>(on), uint16<8>(off), uint16<8>(mask)));
#endif
                }

#if SIMD_USE_AVX2
                static inline mask_int16<16> i_blend(const mask_int16<16> &on,
                                                     const mask_int16<16> &off,
                                                     const mask_int16<16> &mask) {
#if SIMD_USE_AVX512VL
                    return (on.native() & mask.native()) | (off.native() & ~(mask.native()));
#else
                    return to_mask(i_blend(uint16<16>(on), uint16<16>(off), uint16<16>(mask)));
#endif
                }
#endif

#if SIMD_USE_AVX512BW
                inline mask_int16<32> i_blend(const mask_int16<32> &on,
                                              const mask_int16<32> &off,
                                              const mask_int16<32> &mask) {
                    return (on.native() & mask.native()) | (off.native() & ~mask.native());
                }
#endif

                // -----------------------------------------------------------------------------
                // uint32, uint32, uint32

                static inline uint32<4> i_blend(const uint32<4> &on, const uint32<4> &off, const uint32<4> &mask) {
                    return uint32<4>(i_blend(uint8<16>(on), uint8<16>(off), uint8<16>(mask)));
                }

#if SIMD_USE_AVX2
                static inline uint32<8> i_blend(const uint32<8> &on, const uint32<8> &off, const uint32<8> &mask) {
                    return _mm256_blendv_epi8(off.native(), on.native(), mask.native());
                }
#endif

#if SIMD_USE_AVX512F
                static inline uint32<16> i_blend(const uint32<16> &on, const uint32<16> &off, const uint32<16> &mask) {
                    return _mm512_ternarylogic_epi32(on.native(), off.native(), mask.native(), 0xe4);
                }
#endif

                // -----------------------------------------------------------------------------
                // uint32, uint32, mask_int32

                static inline uint32<4> i_blend(const uint32<4> &on, const uint32<4> &off, const mask_int32<4> &mask) {
#if SIMD_USE_NULL
                    return detail::null::blend_mask(on, off, mask);
#else
                    return uint32<4>(i_blend(uint8<16>(on), uint8<16>(off), uint8<16>(mask)));
#endif
                }

#if SIMD_USE_AVX2
                static inline uint32<8> i_blend(const uint32<8> &on, const uint32<8> &off, const mask_int32<8> &mask) {
                    return i_blend(on, off, uint32<8>(mask));
                }
#endif

#if SIMD_USE_AVX512F
                static inline uint32<16> i_blend(const uint32<16> &on,
                                                 const uint32<16> &off,
                                                 const mask_int32<16> &mask) {
                    return _mm512_mask_blend_epi32(mask.native(), off.native(), on.native());
                }
#endif

                // -----------------------------------------------------------------------------
                // mask_int32, mask_int32, mask_int32

                static inline mask_int32<4> i_blend(const mask_int32<4> &on,
                                                    const mask_int32<4> &off,
                                                    const mask_int32<4> &mask) {
#if SIMD_USE_NULL
                    return detail::null::blend_mask(on, off, mask);
#elif SIMD_USE_AVX512VL
                    return (on.native() & mask.native()) | (off.native() & ~(mask.native()));
#else
                    return to_mask(i_blend(uint32<4>(on), uint32<4>(off), uint32<4>(mask)));
#endif
                }

#if SIMD_USE_AVX2
                static inline mask_int32<8> i_blend(const mask_int32<8> &on,
                                                    const mask_int32<8> &off,
                                                    const mask_int32<8> &mask) {
#if SIMD_USE_AVX512VL
                    return (on.native() & mask.native()) | (off.native() & ~(mask.native()));
#else
                    return to_mask(i_blend(uint32<8>(on), uint32<8>(off), uint32<8>(mask)));
#endif
                }
#endif

#if SIMD_USE_AVX512F
                static inline mask_int32<16> i_blend(const mask_int32<16> &on,
                                                     const mask_int32<16> &off,
                                                     const mask_int32<16> &mask) {
                    return _mm512_kor(_mm512_kand(on.native(), mask.native()),
                                      _mm512_kandn(mask.native(), off.native()));
                }
#endif

                // -----------------------------------------------------------------------------
                // float32, float32, float32

                static inline float32<4> i_blend(const float32<4> &con,
                                                 const float32<4> &coff,
                                                 const float32<4> &mask) {
                    float32<4> on = con, off = coff;
#if SIMD_USE_NULL || SIMD_USE_NEON_NO_FLT_SP
                    return detail::null::blend(on, off, mask);
#elif SIMD_USE_AVX
                    return _mm_blendv_ps(off.native(), on.native(), mask.native());
#elif SIMD_USE_SSE2
                    float32x4 r;
                    on = bit_and(on, mask);
                    off = bit_andnot(off, mask);
                    r = bit_or(on, off);
                    return r;
#elif SIMD_USE_NEON
                    return vbslq_f32(uint32x4(mask).native(), on.native(), off.native());
#elif SIMD_USE_ALTIVEC
                    return vec_sel(off.native(), on.native(), mask.native());
#elif SIMD_USE_MSA
                    return (v4f32)__msa_bsel_v((v16u8)mask.native(), (v16u8)off.native(), (v16u8)on.native());
#endif
                }

#if SIMD_USE_AVX
                static inline float32<8> i_blend(const float32<8> &on, const float32<8> &off, const float32<8> &mask) {
                    return _mm256_blendv_ps(off.native(), on.native(), mask.native());
                }
#endif

#if SIMD_USE_AVX512F
                static inline float32<16> i_blend(const float32<16> &on,
                                                  const float32<16> &off,
                                                  const float32<16> &mask) {
                    // maybe cmp_eq + blend has lower latency?
                    return (float32<16>)i_blend(uint32<16>(on), uint32<16>(off), uint32<16>(mask));
                }
#endif

                // -----------------------------------------------------------------------------
                // float32, float32, mask_float32

                static inline float32<4> i_blend(const float32<4> &on,
                                                 const float32<4> &off,
                                                 const mask_float32<4> &mask) {
#if SIMD_USE_NULL
                    return detail::null::blend_mask(on, off, mask);
#else
                    return i_blend(on, off, float32<4>(mask));
#endif
                }

#if SIMD_USE_AVX
                static inline float32<8> i_blend(const float32<8> &on,
                                                 const float32<8> &off,
                                                 const mask_float32<8> &mask) {
                    return i_blend(on, off, float32<8>(mask));
                }
#endif

#if SIMD_USE_AVX512F
                static inline float32<16> i_blend(const float32<16> &on,
                                                  const float32<16> &off,
                                                  const mask_float32<16> &mask) {
                    return _mm512_mask_blend_ps(mask.native(), off.native(), on.native());
                }
#endif

                // -----------------------------------------------------------------------------
                // mask_float32, mask_float32, mask_float32

                static inline mask_float32<4> i_blend(const mask_float32<4> &on,
                                                      const mask_float32<4> &off,
                                                      const mask_float32<4> &mask) {
#if SIMD_USE_NULL || SIMD_USE_NEON_NO_FLT_SP
                    return detail::null::blend_mask(on, off, mask);
#elif SIMD_USE_AVX512VL
                    return (on.native() & mask.native()) | (off.native() & ~(mask.native()));
#else
                    return to_mask(i_blend(float32<4>(on), float32<4>(off), float32<4>(mask)));
#endif
                }

#if SIMD_USE_AVX
                static inline mask_float32<8> i_blend(const mask_float32<8> &on,
                                                      const mask_float32<8> &off,
                                                      const mask_float32<8> &mask) {
#if SIMD_USE_AVX512VL
                    return (on.native() & mask.native()) | (off.native() & ~(mask.native()));
#else
                    return to_mask(i_blend(float32<8>(on), float32<8>(off), float32<8>(mask)));
#endif
                }
#endif

#if SIMD_USE_AVX512F
                static inline mask_float32<16> i_blend(const mask_float32<16> &on,
                                                       const mask_float32<16> &off,
                                                       const mask_float32<16> &mask) {
                    return _mm512_kor(_mm512_kand(on.native(), mask.native()),
                                      _mm512_kandn(mask.native(), off.native()));
                }
#endif

                // -----------------------------------------------------------------------------
                // uint64, uint64, uint64

                static inline uint64<2> i_blend(const uint64<2> &on, const uint64<2> &off, const uint64<2> &mask) {
#if SIMD_USE_NULL || (SIMD_USE_ALTIVEC && !SIMD_USE_VSX_207)
                    return detail::null::blend(on, off, mask);
#else
                    return uint64<2>(i_blend(uint8<16>(on), uint8<16>(off), uint8<16>(mask)));
#endif
                }

#if SIMD_USE_AVX2
                static inline uint64<4> i_blend(const uint64<4> &on, const uint64<4> &off, const uint64<4> &mask) {
                    return _mm256_blendv_epi8(off.native(), on.native(), mask.native());
                }
#endif

#if SIMD_USE_AVX512F
                static inline uint64<8> i_blend(const uint64<8> &on, const uint64<8> &off, const uint64<8> &mask) {
                    return _mm512_ternarylogic_epi64(on.native(), off.native(), mask.native(), 0xe4);
                }
#endif

                // -----------------------------------------------------------------------------
                // uint64, uint64, mask_int64

                static inline uint64<2> i_blend(const uint64<2> &on, const uint64<2> &off, const mask_int64<2> &mask) {
#if SIMD_USE_NULL || (SIMD_USE_ALTIVEC && !SIMD_USE_VSX_207)
                    return detail::null::blend_mask(on, off, mask);
#else
                    return uint64<2>(i_blend(uint8<16>(on), uint8<16>(off), uint8<16>(mask)));
#endif
                }

#if SIMD_USE_AVX2
                static inline uint64<4> i_blend(const uint64<4> &on, const uint64<4> &off, const mask_int64<4> &mask) {
                    return i_blend(on, off, uint64<4>(mask));
                }
#endif

#if SIMD_USE_AVX512F
                static inline uint64<8> i_blend(const uint64<8> &on, const uint64<8> &off, const mask_int64<8> &mask) {
                    return _mm512_mask_blend_epi64(mask.native(), off.native(), on.native());
                }
#endif

                // -----------------------------------------------------------------------------
                // mask_int64, mask_int64, mask_int64

                static inline mask_int64<2> i_blend(const mask_int64<2> &on,
                                                    const mask_int64<2> &off,
                                                    const mask_int64<2> &mask) {
#if SIMD_USE_NULL || (SIMD_USE_ALTIVEC && !SIMD_USE_VSX_207)
                    return detail::null::blend_mask(on, off, mask);
#elif SIMD_USE_AVX512VL
                    return (on.native() & mask.native()) | (off.native() & ~(mask.native()));
#else
                    return to_mask(i_blend(uint64<2>(on), uint64<2>(off), uint64<2>(mask)));
#endif
                }

#if SIMD_USE_AVX2
                static inline mask_int64<4> i_blend(const mask_int64<4> &on,
                                                    const mask_int64<4> &off,
                                                    const mask_int64<4> &mask) {
#if SIMD_USE_AVX512VL
                    return (on.native() & mask.native()) | (off.native() & ~(mask.native()));
#else
                    return to_mask(i_blend(uint64<4>(on), uint64<4>(off), uint64<4>(mask)));
#endif
                }
#endif

#if SIMD_USE_AVX512F
                static inline mask_int64<8> i_blend(const mask_int64<8> &on,
                                                    const mask_int64<8> &off,
                                                    const mask_int64<8> &mask) {
                    return _mm512_kor(_mm512_kand(on.native(), mask.native()),
                                      _mm512_kandn(mask.native(), off.native()));
                }
#endif

                // -----------------------------------------------------------------------------
                // float64, float64, float64

                static inline float64<2> i_blend(const float64<2> &con,
                                                 const float64<2> &coff,
                                                 const float64<2> &mask) {
                    float64<2> on = con, off = coff;
#if SIMD_USE_AVX
                    return _mm_blendv_pd(off.native(), on.native(), mask.native());
#elif SIMD_USE_SSE2
                    float64x2 r;
                    on = bit_and(on, mask);
                    off = bit_andnot(off, mask);
                    r = bit_or(on, off);
                    return r;
#elif SIMD_USE_NEON64
                    return vbslq_f64(vreinterpretq_u64_f64(mask.native()), on.native(), off.native());
#elif SIMD_USE_VSX_206
                    return vec_sel(off.native(), on.native(), mask.native());
#elif SIMD_USE_MSA
                    return (v2f64)__msa_bsel_v((v16u8)mask.native(), (v16u8)off.native(), (v16u8)on.native());
#elif SIMD_USE_NULL || SIMD_USE_NEON32 || SIMD_USE_ALTIVEC
                    return detail::null::blend(on, off, mask);
#endif
                }

#if SIMD_USE_AVX
                static inline float64<4> i_blend(const float64<4> &on, const float64<4> &off, const float64<4> &mask) {
                    return _mm256_blendv_pd(off.native(), on.native(), mask.native());
                }
#endif

#if SIMD_USE_AVX512F
                static inline float64<8> i_blend(const float64<8> &on, const float64<8> &off, const float64<8> &mask) {
                    return (float64<8>)i_blend(uint64<8>(on), uint64<8>(off), uint64<8>(mask));
                }
#endif

                // -----------------------------------------------------------------------------
                // float64, float64, mask_float64

                static inline float64<2> i_blend(const float64<2> &on,
                                                 const float64<2> &off,
                                                 const mask_float64<2> &mask) {
#if SIMD_USE_NULL || SIMD_USE_NEON32 || (SIMD_USE_ALTIVEC && !SIMD_USE_VSX_206)
                    return detail::null::blend_mask(on, off, mask);
#else
                    return i_blend(on, off, float64<2>(mask));
#endif
                }

#if SIMD_USE_AVX
                static inline float64<4> i_blend(const float64<4> &on,
                                                 const float64<4> &off,
                                                 const mask_float64<4> &mask) {
                    return i_blend(on, off, float64<4>(mask));
                }
#endif

#if SIMD_USE_AVX512F
                static inline float64<8> i_blend(const float64<8> &on,
                                                 const float64<8> &off,
                                                 const mask_float64<8> &mask) {
                    return _mm512_mask_blend_pd(mask.native(), off.native(), on.native());
                }
#endif

                // -----------------------------------------------------------------------------
                // mask_float64, mask_float64, mask_float64

                static inline mask_float64<2> i_blend(const mask_float64<2> &on,
                                                      const mask_float64<2> &off,
                                                      const mask_float64<2> &mask) {
#if SIMD_USE_NULL || SIMD_USE_NEON32 || (SIMD_USE_ALTIVEC && !SIMD_USE_VSX_206)
                    return detail::null::blend_mask(on, off, mask);
#elif SIMD_USE_AVX512VL
                    return (on.native() & mask.native()) | (off.native() & ~(mask.native()));
#else
                    return to_mask(i_blend(float64<2>(on), float64<2>(off), float64<2>(mask)));
#endif
                }

#if SIMD_USE_AVX
                static inline mask_float64<4> i_blend(const mask_float64<4> &on,
                                                      const mask_float64<4> &off,
                                                      const mask_float64<4> &mask) {
#if SIMD_USE_AVX512VL
                    return (on.native() & mask.native()) | (off.native() & ~(mask.native()));
#else
                    return to_mask(i_blend(float64<4>(on), float64<4>(off), float64<4>(mask)));
#endif
                }
#endif

#if SIMD_USE_AVX512F
                static inline mask_float64<8> i_blend(const mask_float64<8> &on,
                                                      const mask_float64<8> &off,
                                                      const mask_float64<8> &mask) {
                    return _mm512_kor(_mm512_kand(on.native(), mask.native()),
                                      _mm512_kandn(mask.native(), off.native()));
                }
#endif

                // -----------------------------------------------------------------------------

                template <class V1, class V2, class V3> inline V1 i_blend(const V1 &on, const V2 &off, const V3 &mask) {
                    SIMD_VEC_ARRAY_IMPL3(V1, i_blend, on, off, mask)
                }


            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
