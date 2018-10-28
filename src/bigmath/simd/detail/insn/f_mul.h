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

#ifndef SIMD_DETAIL_INSN_F_MUL_H
#define SIMD_DETAIL_INSN_F_MUL_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#if SIMD_USE_NULL || SIMD_USE_NEON
#include <bigmath/simd/detail/null/math.h>
#endif
#include <bigmath/simd/detail/vector_array_macros.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {

                static inline float32<4> i_fmul(const float32<4> &a, const float32<4> &b) {
#if SIMD_USE_NULL || SIMD_USE_NEON_NO_FLT_SP
                    return detail::null::mul(a, b);
#elif SIMD_USE_SSE2
                    return _mm_mul_ps(a.native(), b.native());
#elif SIMD_USE_NEON_FLT_SP
                    return vmulq_f32(a.native(), b.native());
#elif SIMD_USE_VSX_206
                    return vec_mul(a.native(), b.native());
#elif SIMD_USE_ALTIVEC
                    float32<4> zero = make_zero();
                    return vec_madd(a.native(), b.native(), zero.native());
#elif SIMD_USE_MSA
                    return __msa_fmul_w(a.native(), b.native());
#endif
                }

#if SIMD_USE_AVX
                static inline float32<8> i_fmul(const float32<8> &a, const float32<8> &b) {
                    return _mm256_mul_ps(a.native(), b.native());
                }
#endif

#if SIMD_USE_AVX512F
                static inline float32<16> i_fmul(const float32<16> &a, const float32<16> &b) {
                    return _mm512_mul_ps(a.native(), b.native());
                }
#endif

                // -----------------------------------------------------------------------------

                static inline float64<2> i_fmul(const float64<2> &a, const float64<2> &b) {
#if SIMD_USE_SSE2
                    return _mm_mul_pd(a.native(), b.native());
#elif SIMD_USE_NEON64
                    return vmulq_f64(a.native(), b.native());
#elif SIMD_USE_VSX_206
                    return vec_mul(a.native(), b.native());
#elif SIMD_USE_MSA
                    return __msa_fmul_d(a.native(), b.native());
#elif SIMD_USE_NULL || SIMD_USE_NEON32 || SIMD_USE_ALTIVEC
                    return detail::null::mul(a, b);
#endif
                }

#if SIMD_USE_AVX
                static inline float64<4> i_fmul(const float64<4> &a, const float64<4> &b) {
                    return _mm256_mul_pd(a.native(), b.native());
                }
#endif

#if SIMD_USE_AVX512F
                static inline float64<8> i_fmul(const float64<8> &a, const float64<8> &b) {
                    return _mm512_mul_pd(a.native(), b.native());
                }
#endif

                // -----------------------------------------------------------------------------

                template <class V> inline V i_fmul(const V &a, const V &b) {
                    SIMD_VEC_ARRAY_IMPL2(V, i_fmul, a, b)
                }

            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
