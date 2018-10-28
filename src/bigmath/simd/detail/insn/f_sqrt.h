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

#ifndef SIMD_DETAIL_INSN_F_SQRT_H
#define SIMD_DETAIL_INSN_F_SQRT_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <cmath>
#include <bigmath/simd/types.h>
#include <bigmath/simd/core/f_rsqrt_e.h>
#include <bigmath/simd/core/f_rsqrt_rh.h>
#include <bigmath/simd/detail/null/math.h>
#include <bigmath/simd/detail/vector_array_macros.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {


                static inline float32x4 i_sqrt(const float32x4 &a) {
#if SIMD_USE_NULL || SIMD_USE_NEON_NO_FLT_SP
                    float32x4 r;
                    for (unsigned i = 0; i < a.length; i++) {
                        r.el(i) = std::sqrt(a.el(i));
                    }
                    return r;
#elif SIMD_USE_SSE2
                    return _mm_sqrt_ps(a.native());
#elif SIMPDP_USE_NEON64
                    return vsqrtq_f32(a.native());
#elif SIMD_USE_NEON_FLT_SP || SIMD_USE_ALTIVEC
                    float32x4 x;
                    x = rsqrt_e(a);
                    x = rsqrt_rh(x, a);
                    return mul(a, x);
#elif SIMD_USE_MSA
                    return __msa_fsqrt_w(a.native());
#endif
                }

#if SIMD_USE_AVX
                static inline float32x8 i_sqrt(const float32x8 &a) {
                    return _mm256_sqrt_ps(a.native());
                }
#endif

#if SIMD_USE_AVX512F
                static inline float32<16> i_sqrt(const float32<16> &a) {
                    return _mm512_sqrt_ps(a.native());
                }
#endif

                template <unsigned N> inline float32<N> i_sqrt(const float32<N> &a) {
                    SIMD_VEC_ARRAY_IMPL1(float32<N>, i_sqrt, a);
                }

                // -----------------------------------------------------------------------------

                static inline float64x2 i_sqrt(const float64x2 &a) {
#if SIMD_USE_SSE2
                    return _mm_sqrt_pd(a.native());
#elif SIMD_USE_NEON64
                    return vsqrtq_f64(a.native());
#elif SIMD_USE_VSX_206
                    return vec_sqrt(a.native());
#elif SIMD_USE_MSA
                    return __msa_fsqrt_d(a.native());
#elif SIMD_USE_NULL || SIMD_USE_NEON32 || SIMD_USE_ALTIVEC
                    float64x2 r;
                    for (unsigned i = 0; i < a.length; i++) {
                        r.el(i) = std::sqrt(a.el(i));
                    }
                    return r;
#endif
                }

#if SIMD_USE_AVX
                static inline float64x4 i_sqrt(const float64x4 &a) {
                    return _mm256_sqrt_pd(a.native());
                }
#endif

#if SIMD_USE_AVX512F
                static inline float64<8> i_sqrt(const float64<8> &a) {
                    return _mm512_sqrt_pd(a.native());
                }
#endif

                template <unsigned N> inline float64<N> i_sqrt(const float64<N> &a) {
                    SIMD_VEC_ARRAY_IMPL1(float64<N>, i_sqrt, a);
                }


            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
