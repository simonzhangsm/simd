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

#ifndef SIMD_DETAIL_INSN_F_TRUNC_H
#define SIMD_DETAIL_INSN_F_TRUNC_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <cmath>
#include <bigmath/simd/types.h>
#include <bigmath/simd/core/cmp_gt.h>
#include <bigmath/simd/core/cmp_lt.h>
#include <bigmath/simd/core/cmp_le.h>
#include <bigmath/simd/core/f_ceil.h>
#include <bigmath/simd/core/f_add.h>
#include <bigmath/simd/core/make_float.h>
#include <bigmath/simd/core/make_uint.h>
#include <bigmath/simd/core/to_float32.h>
#include <bigmath/simd/core/to_float64.h>
#include <bigmath/simd/core/to_int32.h>
#include <bigmath/simd/core/to_int64.h>
#include <bigmath/simd/detail/vector_array_macros.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {

                static inline float32x4 i_trunc(const float32x4 &a) {
#if SIMD_USE_NULL || SIMD_USE_NEON_NO_FLT_SP
                    float32x4 r;
                    for (unsigned i = 0; i < a.length; i++) {
                        r.el(i) = std::trunc(a.el(i));
                    }
                    return r;
#elif SIMD_USE_SSE4_1
                    return _mm_round_ps(a.native(), 3); // 3 = i_truncate
#elif SIMD_USE_NEON64
                    return vrndq_f32(a.native()); // FIXME: in ARM8 A32 too
#elif SIMD_USE_SSE2 || SIMD_USE_NEON_FLT_SP || SIMD_USE_MSA
                    // check if the value is not too large
                    float32x4 af = abs(a);
                    mask_float32x4 mask_range = cmp_lt(af, 8388608.0f);

                    // don't change the sign of negative zero
                    mask_float32x4 mask_nonzero = cmp_gt(af, 0);
                    mask_float32x4 mask = bit_and(mask_range, mask_nonzero);

                    // truncate
                    int32x4 ia = to_int32(a);
                    float32x4 fa = to_float32(ia);

                    // combine the results
                    return blend(fa, a, mask); // takes care of NaNs
#elif SIMD_USE_ALTIVEC
                    return vec_trunc(a.native());
#endif
                }

#if SIMD_USE_AVX
                static inline float32x8 i_trunc(const float32x8 &a) {
                    return _mm256_round_ps(a.native(), 3); // 3 = i_truncate
                }
#endif

#if SIMD_USE_AVX512F
                static inline float32<16> i_trunc(const float32<16> &a) {
                    return _mm512_roundscale_ps(a.native(), 0x13); // scale by 1, truncate
                }
#endif

                // -----------------------------------------------------------------------------

                static inline float64x2 i_trunc(const float64x2 &a) {
#if SIMD_USE_SSE4_1
                    return _mm_round_pd(a.native(), 3);
#elif SIMD_USE_SSE2 || SIMD_USE_MSA
                    float64x2 af = abs(a);
                    // check if the value is not too large or is a nan
                    mask_float64x2 mask_range = cmp_le(af, 4503599627370495.0);
                    // check if truncate to zero
                    float64x2 mask_zero = cmp_lt(af, 1.0).eval().unmask();

                    /*  Emulate truncation for numbers not less than 1.0.
                        This is implemented by clearing the mantissa in the source number,
                        adding 1.0 and subtracting integer 1. The mantissa of the resulting
                        number will effectively contain a bit mask defining which bits need to
                        be cleared off the source number in order to truncate it.
                    */
                    float64x2 clearbits = bit_and(af, 0x7ff0000000000000); // clear the mantissa
                    clearbits = add(clearbits, 1.0);
                    clearbits = (float64x2)sub(uint64x2(clearbits), 1);
                    clearbits = bit_andnot(clearbits, 0x7ff0000000000000); // leave only the mantissa

                    float64x2 a2 = bit_andnot(a, clearbits);
                    a2 = bit_andnot(a2, mask_zero);
                    return blend(a2, a, mask_range);
#elif SIMD_USE_NEON64
                    return vrndq_f64(a.native());
#elif SIMD_USE_VSX_206
                    return vec_trunc(a.native());
#elif SIMD_USE_MSA
                    // check if the value is not too large
                    float64<2> af = abs(a);
                    mask_float64<2> mask_range = cmp_le(af, 4503599627370495.0);

                    // don't change the sign of negative zero
                    mask_float64<2> mask_nonzero = cmp_gt(af, 0);
                    mask_float64<2> mask = bit_and(mask_range, mask_nonzero);

                    // truncate
                    int64<2> ia = to_int64(a);
                    float64<2> fa = to_float64(ia);

                    // combine the results
                    return blend(fa, a, mask); // takes care of NaNs
#elif SIMD_USE_NULL || SIMD_USE_NEON32 || SIMD_USE_ALTIVEC
                    float64x2 r;
                    for (unsigned i = 0; i < r.length; ++i) {
                        r.el(i) = std::trunc(a.el(i));
                    }
                    return r;
#endif
                }

#if SIMD_USE_AVX
                static inline float64x4 i_trunc(const float64x4 &a) {
                    return _mm256_round_pd(a.native(), 3); // 3 = i_truncate
                }
#endif

#if SIMD_USE_AVX512F
                static inline float64<8> i_trunc(const float64<8> &a) {
                    return _mm512_roundscale_pd(a.native(), 0x13); // scale by 1, truncate
                }
#endif

                // -----------------------------------------------------------------------------

                template <class V> inline V i_trunc(const V &a) {
                    SIMD_VEC_ARRAY_IMPL1(V, i_trunc, a);
                }


            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
