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

#ifndef SIMD_DETAIL_INSN_F_ISNAN2_H
#define SIMD_DETAIL_INSN_F_ISNAN2_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/core/bit_or.h>
#include <bigmath/simd/core/f_isnan.h>
#include <bigmath/simd/detail/null/math.h>
#include <bigmath/simd/detail/vector_array_macros.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {


                static inline mask_float32x4 i_isnan2(const float32x4 &a, const float32x4 &b) {
#if SIMD_USE_NULL
                    return detail::null::isnan2(a, b);
#elif SIMD_USE_AVX512VL
                    return _mm_cmp_ps_mask(a.native(), b.native(), _CMP_UNORD_Q);
#elif SIMD_USE_AVX
                    return _mm_cmp_ps(a.native(), b.native(), _CMP_UNORD_Q);
#elif SIMD_USE_SSE2
                    return (mask_float32x4)_mm_cmpunord_ps(a.native(), b.native());
#elif SIMD_USE_NEON || SIMD_USE_ALTIVEC
                    return bit_or(isnan(a), isnan(b));
#elif SIMD_USE_MSA
                    return (v4f32)__msa_fcun_w(a.native(), b.native());
#endif
                }

#if SIMD_USE_AVX
                static inline mask_float32x8 i_isnan2(const float32x8 &a, const float32x8 &b) {
#if SIMD_USE_AVX512VL
                    return _mm256_cmp_ps_mask(a.native(), b.native(), _CMP_UNORD_Q);
#else
                    return _mm256_cmp_ps(a.native(), b.native(), _CMP_UNORD_Q);
#endif
                }
#endif

#if SIMD_USE_AVX512F
                static inline mask_float32<16> i_isnan2(const float32<16> &a, const float32<16> &b) {
                    return _mm512_cmp_ps_mask(a.native(), b.native(), _CMP_UNORD_Q);
                }
#endif

                // -----------------------------------------------------------------------------

                static inline mask_float64x2 i_isnan2(const float64x2 &a, const float64x2 &b) {
#if SIMD_USE_AVX512VL
                    return _mm_cmp_pd_mask(a.native(), b.native(), _CMP_UNORD_Q);
#elif SIMD_USE_AVX
                    return _mm_cmp_pd(a.native(), b.native(), _CMP_UNORD_Q);
#elif SIMD_USE_SSE2
                    return _mm_cmpunord_pd(a.native(), b.native());
#elif SIMD_USE_NEON64 || SIMD_USE_VSX_206
                    return bit_or(isnan(a), isnan(b));
#elif SIMD_USE_MSA
                    return (v2f64)__msa_fcun_d(a.native(), b.native());
#elif SIMD_USE_NULL || SIMD_USE_NEON32 || SIMD_USE_ALTIVEC
                    return detail::null::isnan2(a, b);
#endif
                }

#if SIMD_USE_AVX
                static inline mask_float64x4 i_isnan2(const float64x4 &a, const float64x4 &b) {
#if SIMD_USE_AVX512VL
                    return _mm256_cmp_pd_mask(a.native(), b.native(), _CMP_UNORD_Q);
#else
                    return _mm256_cmp_pd(a.native(), b.native(), _CMP_UNORD_Q);
#endif
                }
#endif

#if SIMD_USE_AVX512F
                static inline mask_float64<8> i_isnan2(const float64<8> &a, const float64<8> &b) {
                    return _mm512_cmp_pd_mask(a.native(), b.native(), _CMP_UNORD_Q);
                }
#endif

                // -----------------------------------------------------------------------------

                template <class V> inline typename V::mask_vector_type i_isnan2(const V &a, const V &b) {
                    SIMD_VEC_ARRAY_IMPL2(typename V::mask_vector_type, i_isnan2, a, b);
                }

            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
