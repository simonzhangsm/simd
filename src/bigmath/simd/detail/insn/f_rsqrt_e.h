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

#ifndef SIMD_DETAIL_INSN_F_RSQRT_E_H
#define SIMD_DETAIL_INSN_F_RSQRT_E_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#if SIMD_USE_NULL || SIMD_USE_NEON || SIMD_USE_ALTIVEC
#include <cmath>
#include <bigmath/simd/detail/null/math.h>
#endif
#include <bigmath/simd/detail/vector_array_macros.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {


                static inline float32x4 i_rsqrt_e(const float32x4 &a) {
#if SIMD_USE_NULL || SIMD_USE_NEON_NO_FLT_SP
                    float32x4 r;
                    for (unsigned i = 0; i < a.length; i++) {
                        r.el(i) = 1.0f / std::sqrt(a.el(i));
                    }
                    return r;
#elif SIMD_USE_SSE2
                    return _mm_rsqrt_ps(a.native());
#elif SIMD_USE_NEON_FLT_SP
                    return vrsqrteq_f32(a.native());
#elif SIMD_USE_ALTIVEC
                    return vec_rsqrte(a.native());
#elif SIMD_USE_MSA
                    return __msa_frsqrt_w(a.native());
#endif
                }

#if SIMD_USE_AVX
                static inline float32x8 i_rsqrt_e(const float32x8 &a) {
                    return _mm256_rsqrt_ps(a.native());
                }
#endif

#if SIMD_USE_AVX512F
                static inline float32<16> i_rsqrt_e(const float32<16> &a) {
                    return _mm512_rsqrt14_ps(a.native());
                }
#endif

                template <unsigned N> inline float32<N> i_rsqrt_e(const float32<N> &a) {
                    SIMD_VEC_ARRAY_IMPL1(float32<N>, i_rsqrt_e, a);
                }


            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
