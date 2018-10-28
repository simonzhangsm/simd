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

#ifndef SIMD_DETAIL_INSN_F_RCP_RH_H
#define SIMD_DETAIL_INSN_F_RCP_RH_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/core/f_sub.h>
#include <bigmath/simd/core/f_mul.h>
#include <bigmath/simd/core/make_float.h>
#if SIMD_USE_NULL || SIMD_USE_NEON || SIMD_USE_ALTIVEC
#include <cmath>
#include <bigmath/simd/detail/null/math.h>
#endif
#include <bigmath/simd/detail/vector_array_macros.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {


                static inline float32x4 i_rcp_rh(const float32x4 &cx, const float32x4 &a) {
                    float32<4> x = cx;
#if SIMD_USE_NULL || SIMD_USE_NEON_NO_FLT_SP
                    float32x4 r;
                    for (unsigned i = 0; i < a.length; i++) {
                        float ix = x.el(i);
                        float ia = a.el(i);
                        r.el(i) = ix * (2.0f - ix * ia);
                    }
                    return r;
#elif SIMD_USE_SSE2 || SIMD_USE_MSA
                    float32x4 r;

                    r = mul(a, x);
                    r = sub(2.0, r);
                    x = mul(x, r);

                    return x;
#elif SIMD_USE_NEON_FLT_SP
                    float32x4 r;
                    r = vrecpsq_f32(a.native(), x.native());
                    x = mul(x, r);

                    return x;
#elif SIMD_USE_ALTIVEC
                    float32x4 r, c2;
                    c2 = make_float(2.0f);
                    // -(x*a-c2)
                    r = vec_nmsub(x.native(), a.native(), c2.native());
                    x = mul(x, r);
                    return x;
#endif
                }

#if SIMD_USE_AVX
                static inline float32x8 i_rcp_rh(const float32x8 &cx, const float32x8 &a) {
                    float32x8 r, x = cx;

                    r = mul(a, x);
                    r = sub(2.0, r);
                    x = mul(x, r);

                    return x;
                }
#endif

#if SIMD_USE_AVX512F
                static inline float32<16> i_rcp_rh(const float32<16> &cx, const float32<16> &a) {
                    float32<16> r, x = cx;

                    r = mul(a, x);
                    r = sub(2.0, r);
                    x = mul(x, r);

                    return x;
                }
#endif

                template <unsigned N> inline float32<N> i_rcp_rh(const float32<N> &x, const float32<N> &a) {
                    SIMD_VEC_ARRAY_IMPL2(float32<N>, i_rcp_rh, x, a);
                }


            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
