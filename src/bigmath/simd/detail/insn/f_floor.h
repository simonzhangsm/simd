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

#ifndef SIMD_DETAIL_INSN_F_FLOOR_H
#define SIMD_DETAIL_INSN_F_FLOOR_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <cmath>
#include <bigmath/simd/types.h>
#include <bigmath/simd/core/f_abs.h>
#include <bigmath/simd/core/bit_or.h>
#include <bigmath/simd/core/blend.h>
#include <bigmath/simd/core/cmp_eq.h>
#include <bigmath/simd/core/cmp_gt.h>
#include <bigmath/simd/core/i_shift_r.h>
#include <bigmath/simd/core/i_sub.h>
#include <bigmath/simd/core/to_float32.h>
#include <bigmath/simd/core/to_int32.h>
#include <bigmath/simd/detail/vector_array_macros.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {


                static inline float32x4 i_floor(const float32x4 &a) {
#if SIMD_USE_NULL || SIMD_USE_NEON_NO_FLT_SP
                    float32x4 r;
                    for (unsigned i = 0; i < a.length; i++) {
                        r.el(i) = std::floor(a.el(i));
                    }
                    return r;
#elif SIMD_USE_SSE4_1
                    return _mm_floor_ps(a.native());
#elif SIMD_USE_NEON64
                    return vrndmq_f32(a.native());
#elif SIMD_USE_SSE2 || SIMD_USE_NEON_FLT_SP || SIMD_USE_MSA
                    // check if the value is not too large, or is zero
                    float32x4 ba = abs(a);
                    mask_float32x4 mask_range = cmp_le(ba, 8388607.0f);
                    mask_float32x4 mask_nonzero = cmp_gt(ba, 0);
                    mask_float32x4 mask = bit_and(mask_range, mask_nonzero); // takes care of nans and zeros

                    // calculate the i_floor using trunc
                    int32x4 s = shift_r((uint32x4)a, 31);         //=1 if a<0
                    float32x4 at = (float32x4)sub((int32x4)a, s); //=nextafter towards +inf, if a<0
                    int32x4 ia = to_int32(at);
                    ia = sub(ia, s);
                    float32x4 fa = to_float32(ia);

                    // combine the results
                    return blend(fa, a, mask);
#elif SIMD_USE_ALTIVEC
                    return vec_floor(a.native());
#endif
                }

#if SIMD_USE_AVX
                static inline float32x8 i_floor(const float32x8 &a) {
                    return _mm256_floor_ps(a.native());
                }
#endif

#if SIMD_USE_AVX512F
                static inline float32<16> i_floor(const float32<16> &a) {
                    return _mm512_floor_ps(a.native());
                }
#endif

                // -----------------------------------------------------------------------------

                static inline float64x2 i_floor(const float64x2 &a) {
#if SIMD_USE_SSE4_1
                    return _mm_floor_pd(a.native());
#elif SIMD_USE_SSE2 || SIMD_USE_MSA
                    float64x2 af = abs(a);
                    // check if the value is not too large or is a nan
                    mask_float64x2 mask_range = cmp_le(af, 4503599627370495.0);
                    // check if truncate to zero or minus one
                    mask_float64x2 mask_1to1 = cmp_lt(af, 1.0);

                    /*  Emulate truncation for numbers not less than 1.0.
                        This is implemented by clearing the mantissa in the source number,
                        adding 1.0 and subtracting integer 1. The mantissa of the resulting
                        number will effectively contain a bit mask defining which bits need to
                        be cleared off the source number in order to truncate it.
                    */
                    float64x2 clearbits = bit_and(af, 0x7ff0000000000000); // clear the mantissa
                    clearbits = add(clearbits, 1.0);
                    clearbits = (float64x2)sub(uint64x2(clearbits), 1);
                    clearbits = bit_andnot(clearbits, 0xfff0000000000000); // leave only the mantissa

                    float64x2 a2 = bit_andnot(a, clearbits); // truncate

                    // check if we need to subtract one (truncated bits when negative)
                    mask_float64x2 mask_neg = cmp_lt(a, 0.0);
                    mask_float64x2 mask_sub1 = cmp_gt(bit_and(a, clearbits), 0.0);
                    mask_sub1 = bit_and(mask_sub1, mask_neg);

                    // one special case is when 'a' is in the range of (-1.0, 0.0) in which
                    // a & clearbits may still yield to zero. Thus this additional check
                    mask_sub1 = bit_or(mask_sub1, bit_and(mask_1to1, mask_neg));
                    float64x2 sub1 = make_float(-1.0);
                    sub1 = bit_and(sub1, mask_sub1);

                    a2 = bit_andnot(a, mask_1to1);
                    a2 = sub(a2, sub1);

                    return blend(a2, a, mask_range);
#elif SIMD_USE_NEON64
                    return vrndnq_f64(a.native());
#elif SIMD_USE_VSX_206
                    return vec_floor(a.native());
#elif SIMD_USE_NULL || SIMD_USE_NEON32 || SIMD_USE_ALTIVEC
                    float64x2 r;
                    for (unsigned i = 0; i < r.length; ++i) {
                        r.el(i) = std::floor(a.el(i));
                    }
                    return r;
#endif
                }

#if SIMD_USE_AVX
                static inline float64x4 i_floor(const float64x4 &a) {
                    return _mm256_floor_pd(a.native());
                }
#endif

#if SIMD_USE_AVX512F
                static inline float64<8> i_floor(const float64<8> &a) {
                    return _mm512_floor_pd(a.native());
                }
#endif

                template <class V> inline V i_floor(const V &a) {
                    SIMD_VEC_ARRAY_IMPL1(V, i_floor, a);
                }

            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
