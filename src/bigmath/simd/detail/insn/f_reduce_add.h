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

#ifndef SIMD_DETAIL_INSN_F_REDUCE_ADD_H
#define SIMD_DETAIL_INSN_F_REDUCE_ADD_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/core/extract.h>
#include <bigmath/simd/core/f_add.h>
#include <bigmath/simd/core/permute2.h>
#include <bigmath/simd/detail/extract128.h>
#include <bigmath/simd/detail/workarounds.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {


                static inline float i_reduce_add(const float32x4 &a) {
#if SIMD_USE_NULL || SIMD_USE_NEON_NO_FLT_SP
                    float r = a.el(0);
                    for (unsigned i = 1; i < a.length; i++) {
                        r += a.el(i);
                    }
                    return r;
#elif SIMD_USE_SSE3
                    float32x4 b = a;
                    b = _mm_hadd_ps(b.native(), b.native());
                    b = _mm_hadd_ps(b.native(), b.native());
                    return _mm_cvtss_f32(b.native());
#elif SIMD_USE_SSE2
                    float32x4 sum2 = _mm_movehl_ps(a.native(), a.native());
                    float32x4 sum = add(a, sum2);
                    sum = add(sum, permute2<1, 0>(sum));
                    return _mm_cvtss_f32(sum.native());
#elif SIMD_USE_NEON_FLT_SP
                    float32x2_t a2 = vpadd_f32(vget_low_f32(a.native()), vget_high_f32(a.native()));
                    a2 = vpadd_f32(a2, a2);
                    return vget_lane_f32(a2, 0);
#elif SIMD_USE_ALTIVEC || SIMD_USE_MSA
                    float32x4 b = a;
                    b = add(b, move4_l<1>(b));
                    b = add(b, move4_l<2>(b));
                    return extract<0>(b);
#endif
                }

#if SIMD_USE_AVX
                static inline float i_reduce_add(const float32x8 &a) {
                    __m128 ah = detail::extract128<1>(a).native();
                    __m128 al = detail::extract128<0>(a).native();
                    al = _mm_hadd_ps(al, ah);
                    al = _mm_hadd_ps(al, al);
                    al = _mm_hadd_ps(al, al);
                    return _mm_cvtss_f32(al);
                }
#endif

#if SIMD_USE_AVX512F
                static inline float i_reduce_add(const float32<16> &a) {
                    return i_reduce_add(add(extract256<0>(a), extract256<1>(a)));
                }
#endif

                template <unsigned N> inline float i_reduce_add(const float32<N> &a) {
                    float32v r = a.vec(0);
                    for (unsigned i = 1; i < a.vec_length; ++i)
                        r = add(r, a.vec(i));
                    return i_reduce_add(r);
                }

                // -----------------------------------------------------------------------------

                static inline double i_reduce_add(const float64x2 &a) {
#if SIMD_USE_SSE3
                    return _mm_cvtsd_f64(_mm_hadd_pd(a.native(), a.native()));
#elif SIMD_USE_SSE2
                    float64x2 b = add(a, permute2<1, 1>(a));
                    return _mm_cvtsd_f64(b.native());
#elif SIMD_USE_NEON64
                    float64x2_t a2 = vpaddq_f64(a.native(), a.native());
                    return vgetq_lane_f64(a2, 0);
#elif SIMD_USE_VSX_206 || SIMD_USE_MSA
                    float64x2 b = add(a, permute2<1, 1>(a));
                    return extract<0>(b);
#elif SIMD_USE_NULL || SIMD_USE_NEON32 || SIMD_USE_ALTIVEC
                    double r = a.el(0);
                    for (unsigned i = 1; i < a.length; i++) {
                        r += a.el(i);
                    }
                    return r;
#endif
                }

#if SIMD_USE_AVX
                static inline double i_reduce_add(const float64x4 &a) {
                    __m128d ah = detail::extract128<1>(a).native();
                    __m128d al = detail::extract128<0>(a).native();
                    al = _mm_hadd_pd(al, ah);
                    al = _mm_hadd_pd(al, al);
                    return _mm_cvtsd_f64(al);
                }
#endif

#if SIMD_USE_AVX512F
                static inline double i_reduce_add(const float64<8> &a) {
                    return i_reduce_add(add(extract256<0>(a), extract256<1>(a)));
                }
#endif

                template <unsigned N> inline double i_reduce_add(const float64<N> &a) {
                    float64v r = a.vec(0);
                    for (unsigned i = 1; i < a.vec_length; ++i)
                        r = add(r, a.vec(i));
                    return i_reduce_add(r);
                }

            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
