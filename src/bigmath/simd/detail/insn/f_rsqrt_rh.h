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

#ifndef SIMD_DETAIL_INSN_F_RSQRT_RH_H
#define SIMD_DETAIL_INSN_F_RSQRT_RH_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <cmath>
#include <bigmath/simd/types.h>
#include <bigmath/simd/core/f_mul.h>
#include <bigmath/simd/core/f_sub.h>
#include <bigmath/simd/detail/null/math.h>
#include <bigmath/simd/detail/vector_array_macros.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {

                template <class V> inline V v_rsqrt_rh(const V &cx, const V &a) {
                    V x2, r, x = cx;

                    x2 = mul(x, x);
                    r = mul(a, x2);
                    r = sub(3.0, r);
                    x = mul(x, 0.5);
                    r = mul(x, r);

                    return r;
                }

                static inline float32x4 i_rsqrt_rh(const float32x4 &cx, const float32x4 &a) {
                    // x_n = x*(3-d*x*x)/2
                    float32<4> x = cx;
#if SIMD_USE_NULL || SIMD_USE_NEON_NO_FLT_SP
                    float32x4 r;
                    for (unsigned i = 0; i < cx.length; i++) {
                        float ix = x.el(i);
                        float ia = a.el(i);
                        r.el(i) = ix * (3.0f - ia * ix * ix) * 0.5f;
                    }
                    return r;
#elif SIMD_USE_SSE2 || SIMD_USE_MSA
                    return v_rsqrt_rh(x, a);
#elif SIMD_USE_NEON_FLT_SP
                    float32x4 x2, r;

                    x2 = mul(x, x);
                    r = vrsqrtsq_f32(a.native(), x2.native());
                    x = mul(x, r);

                    return x;
#elif SIMD_USE_ALTIVEC
                    float32x4 x2, r, xp5, c3;

                    c3 = make_float(3.0f);

                    x2 = mul(x, x);
                    // r = (c3 - a*x2)
                    r = vec_nmsub(a.native(), x2.native(), c3.native());
                    xp5 = mul(x, 0.5);
                    r = mul(xp5, r);

                    return r;
#endif
                }

#if SIMD_USE_AVX
                static inline float32x8 i_rsqrt_rh(const float32x8 &x, const float32x8 &a) {
                    return v_rsqrt_rh(x, a);
                }
#endif

#if SIMD_USE_AVX512F
                static inline float32<16> i_rsqrt_rh(const float32<16> &x, const float32<16> &a) {
                    return v_rsqrt_rh(x, a);
                }
#endif


                template <unsigned N> inline float32<N> i_rsqrt_rh(const float32<N> &x, const float32<N> &a) {
                    SIMD_VEC_ARRAY_IMPL2(float32<N>, i_rsqrt_rh, x, a);
                }

            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
