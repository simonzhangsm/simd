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

#ifndef SIMD_DETAIL_INSN_F_FMADD_H
#define SIMD_DETAIL_INSN_F_FMADD_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/null/math.h>
#include <bigmath/simd/detail/not_implemented.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {

                static inline float32<4> i_fmadd(const float32<4> &a, const float32<4> &b, const float32<4> &c) {
#if SIMD_USE_NULL
                    return detail::null::fmadd(a, b, c);
#elif SIMD_USE_FMA3
                    return _mm_fmadd_ps(a.native(), b.native(), c.native());
#elif SIMD_USE_FMA4
                    return _mm_macc_ps(a.native(), b.native(), c.native());
#elif SIMD_USE_NEON64
                    // FIXME: also in vfpv4
                    return vfmaq_f32(a.native(), b.native(), c.native());
#elif SIMD_USE_MSA
                    return __msa_fmadd_w(c.native(), a.native(), b.native());
#else
                    return SIMD_NOT_IMPLEMENTED3(a, b, c);
#endif
                }

#if SIMD_USE_AVX
                static inline float32<8> i_fmadd(const float32<8> &a, const float32<8> &b, const float32<8> &c) {
#if SIMD_USE_FMA3
                    return _mm256_fmadd_ps(a.native(), b.native(), c.native());
#elif SIMD_USE_FMA4
                    return _mm256_macc_ps(a.native(), b.native(), c.native());
#else
                    return SIMD_NOT_IMPLEMENTED3(a, b, c);
#endif
                }
#endif

#if SIMD_USE_AVX512F
                static inline float32<16> i_fmadd(const float32<16> &a, const float32<16> &b, const float32<16> &c) {
                    return _mm512_fmadd_ps(a.native(), b.native(), c.native());
                }
#endif

                // -----------------------------------------------------------------------------

                static inline float64<2> i_fmadd(const float64<2> &a, const float64<2> &b, const float64<2> &c) {
#if SIMD_USE_NULL
                    return detail::null::fmadd(a, b, c);
#elif SIMD_USE_FMA3
                    return _mm_fmadd_pd(a.native(), b.native(), c.native());
#elif SIMD_USE_FMA4
                    return _mm_macc_pd(a.native(), b.native(), c.native());
#elif SIMD_USE_NEON64
                    // FIXME: also in vfpv4
                    return vfmaq_f64(a.native(), b.native(), c.native());
#elif SIMD_USE_MSA
                    return __msa_fmadd_d(c.native(), a.native(), b.native());
#else
                    return SIMD_NOT_IMPLEMENTED3(a, b, c);
#endif
                }

#if SIMD_USE_AVX
                static inline float64<4> i_fmadd(const float64<4> &a, const float64<4> &b, const float64<4> &c) {
#if SIMD_USE_FMA3
                    return _mm256_fmadd_pd(a.native(), b.native(), c.native());
#elif SIMD_USE_FMA4
                    return _mm256_macc_pd(a.native(), b.native(), c.native());
#else
                    return SIMD_NOT_IMPLEMENTED3(a, b, c);
#endif
                }
#endif

#if SIMD_USE_AVX512F
                static inline float64<8> i_fmadd(const float64<8> &a, const float64<8> &b, const float64<8> &c) {
                    return _mm512_fmadd_pd(a.native(), b.native(), c.native());
                }
#endif

                // -----------------------------------------------------------------------------

                template <class V> inline V i_fmadd(const V &a, const V &b, const V &c) {
                    SIMD_VEC_ARRAY_IMPL3(V, i_fmadd, a, b, c);
                }

            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
