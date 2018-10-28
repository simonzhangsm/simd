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

#ifndef SIMD_DETAIL_INSN_CONV_FLOAT_TO_INT64_H
#define SIMD_DETAIL_INSN_CONV_FLOAT_TO_INT64_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/insn/conv_any_to_float64.h>
#include <bigmath/simd/detail/vector_array_conv_macros.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {


                static inline uint64<2> i_to_uint64(const float64<2> &a) {
#if SIMD_USE_AVX512DQ && SIMD_USE_AVX512VL
                    return _mm_cvttpd_epu64(a.native());
#elif SIMD_USE_AVX512DQ
                    __m512d a512 = _mm512_castpd128_pd512(a.native());
                    return _mm512_castsi512_si128(_mm512_cvttpd_epu64(a512));
#elif SIMD_USE_NEON64
                    return vcvtq_u64_f64(a.native());
#elif SIMD_USE_VSX_206
                    uint32<4> r;
                    r = (__vector uint32_t)vec_ctu(a.native(), 0);
                    return (uint64<2>)r;
#elif SIMD_USE_VSX_207
                    return vec_ctu(a.native(), 0);
#elif SIMD_USE_MSA
                    return __msa_ftrunc_u_d(a.native());
#elif SIMD_USE_NULL || SIMD_USE_NEON32 || SIMD_USE_ALTIVEC
                    detail::mem_block<uint64<2>> r;
                    r[0] = uint64_t(a.el(0));
                    r[1] = uint64_t(a.el(1));
                    return r;
#else
                    return SIMD_NOT_IMPLEMENTED1(a);
#endif
                }

#if SIMD_USE_AVX
                static inline uint64<4> i_to_uint64(const float64<4> &a) {
#if SIMD_USE_AVX512DQ && SIMD_USE_AVX512VL
                    return _mm256_cvttpd_epu64(a.native());
#elif SIMD_USE_AVX512DQ
                    __m512d a512 = _mm512_castpd256_pd512(a.native());
                    return _mm512_castsi512_si256(_mm512_cvttpd_epu64(a512));
#else
                    return SIMD_NOT_IMPLEMENTED1(a);
#endif
                }
#endif

#if SIMD_USE_AVX512F
                static inline uint64<8> i_to_uint64(const float64<8> &a) {
#if SIMD_USE_AVX512DQ
                    return _mm512_cvttpd_epu64(a.native());
#else
                    return SIMD_NOT_IMPLEMENTED1(a);
#endif
                }
#endif

                template <unsigned N> inline uint64<N> i_to_uint64(const float64<N> &a) {
                    SIMD_VEC_ARRAY_IMPL_CONV_EXTRACT(uint64<N>, i_to_uint64, a)
                }

                // -----------------------------------------------------------------------------

                static inline int64<2> i_to_int64(const float64<2> &a) {
#if SIMD_USE_AVX512DQ && SIMD_USE_AVX512VL
                    return _mm_cvttpd_epi64(a.native());
#elif SIMD_USE_AVX512DQ
                    __m512d a512 = _mm512_castpd128_pd512(a.native());
                    return _mm512_castsi512_si128(_mm512_cvttpd_epi64(a512));
#elif SIMD_USE_NEON64
                    return vcvtq_s64_f64(a.native());
#elif SIMD_USE_VSX_207
                    return vec_cts(a.native(), 0);
#elif SIMD_USE_VSX_206
                    int32<4> r;
                    r = (__vector int32_t)vec_cts(a.native(), 0);
                    return (int64<2>)r;
#elif SIMD_USE_MSA
                    return __msa_ftrunc_s_d(a.native());
#elif SIMD_USE_NULL || SIMD_USE_NEON32 || SIMD_USE_ALTIVEC
                    detail::mem_block<int64<2>> r;
                    r[0] = int64_t(a.el(0));
                    r[1] = int64_t(a.el(1));
                    return r;
#else
                    return SIMD_NOT_IMPLEMENTED1(a);
#endif
                }

#if SIMD_USE_AVX
                static inline int64<4> i_to_int64(const float64<4> &a) {
#if SIMD_USE_AVX512DQ && SIMD_USE_AVX512VL
                    return _mm256_cvttpd_epi64(a.native());
#elif SIMD_USE_AVX512DQ
                    __m512d a512 = _mm512_castpd256_pd512(a.native());
                    return _mm512_castsi512_si256(_mm512_cvttpd_epi64(a512));
#else
                    return SIMD_NOT_IMPLEMENTED1(a);
#endif
                }
#endif

#if SIMD_USE_AVX512F
                static inline int64<8> i_to_int64(const float64<8> &a) {
#if SIMD_USE_AVX512DQ
                    return _mm512_cvttpd_epi64(a.native());
#else
                    return SIMD_NOT_IMPLEMENTED1(a);
#endif
                }
#endif

                template <unsigned N> inline int64<N> i_to_int64(const float64<N> &a) {
                    SIMD_VEC_ARRAY_IMPL_CONV_EXTRACT(int64<N>, i_to_int64, a)
                }

                // ----------------------------------------------------------------------------

                static inline uint64<4> i_to_uint64(const float32<4> &a) {
#if SIMD_USE_AVX512DQ && SIMD_USE_AVX512VL
                    return _mm256_cvttps_epu64(a.native());
#elif SIMD_USE_AVX512DQ
                    __m256 a256 = _mm256_castps128_ps256(a.native());
                    return _mm512_castsi512_si256(_mm512_cvttps_epu64(a256));
#elif SIMD_USE_NEON64 || SIMD_USE_VSX_206 || SIMD_USE_MSA
                    return i_to_uint64(i_to_float64(a));
#elif SIMD_USE_NULL || SIMD_USE_NEON32 || SIMD_USE_ALTIVEC
                    detail::mem_block<uint64<4>> r;
                    detail::mem_block<float32<4>> mi(a);
                    r[0] = int64_t(mi[0]);
                    r[1] = int64_t(mi[1]);
                    r[2] = int64_t(mi[2]);
                    r[3] = int64_t(mi[3]);
                    return r;
#else
                    return SIMD_NOT_IMPLEMENTED1(a);
#endif
                }

#if SIMD_USE_AVX
                static inline uint64<8> i_to_uint64(const float32<8> &a) {
#if SIMD_USE_AVX512DQ && SIMD_USE_AVX512VL
                    return _mm512_cvttps_epu64(a.native());
#else
                    return SIMD_NOT_IMPLEMENTED1(a);
#endif
                }
#endif

#if SIMD_USE_AVX512F
                static inline uint64<16> i_to_uint64(const float32<16> &a) {
#if SIMD_USE_AVX512DQ
                    float32<8> a0, a1;
                    uint64<16> r;
                    split(a, a0, a1);

                    r.vec(0) = _mm512_cvttps_epu64(a0.native());
                    r.vec(1) = _mm512_cvttps_epu64(a1.native());

                    return r;
#else
                    return SIMD_NOT_IMPLEMENTED1(a);
#endif
                }
#endif

                template <unsigned N> inline uint64<N> i_to_uint64(const float32<N> &a) {
                    SIMD_VEC_ARRAY_IMPL_CONV_INSERT(uint64<N>, i_to_uint64, a)
                }

                // -----------------------------------------------------------------------------

                static inline int64<4> i_to_int64(const float32<4> &a) {
#if SIMD_USE_AVX512DQ && SIMD_USE_AVX512VL
                    return _mm256_cvttps_epi64(a.native());
#elif SIMD_USE_AVX512DQ
                    __m256 a256 = _mm256_castps128_ps256(a.native());
                    return _mm512_castsi512_si256(_mm512_cvttps_epi64(a256));
#elif SIMD_USE_NEON64 || SIMD_USE_VSX_206 || SIMD_USE_MSA
                    return i_to_int64(i_to_float64(a));
#elif SIMD_USE_NULL || SIMD_USE_NEON32 || SIMD_USE_ALTIVEC
                    detail::mem_block<int64<4>> r;
                    detail::mem_block<float32<4>> mi(a);
                    r[0] = int64_t(mi[0]);
                    r[1] = int64_t(mi[1]);
                    r[2] = int64_t(mi[2]);
                    r[3] = int64_t(mi[3]);
                    return r;
#else
                    return SIMD_NOT_IMPLEMENTED1(a);
#endif
                }

#if SIMD_USE_AVX
                static inline int64<8> i_to_int64(const float32<8> &a) {
#if SIMD_USE_AVX512DQ && SIMD_USE_AVX512VL
                    return _mm512_cvttps_epi64(a.native());
#else
                    return SIMD_NOT_IMPLEMENTED1(a);
#endif
                }
#endif

#if SIMD_USE_AVX512F
                static inline int64<16> i_to_int64(const float32<16> &a) {
#if SIMD_USE_AVX512DQ
                    float32<8> a0, a1;
                    int64<16> r;
                    split(a, a0, a1);

                    r.vec(0) = _mm512_cvttps_epi64(a0.native());
                    r.vec(1) = _mm512_cvttps_epi64(a1.native());

                    return r;
#else
                    return SIMD_NOT_IMPLEMENTED1(a);
#endif
                }
#endif

                template <unsigned N> inline int64<N> i_to_int64(const float32<N> &a) {
                    SIMD_VEC_ARRAY_IMPL_CONV_INSERT(int64<N>, i_to_int64, a)
                }

            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
