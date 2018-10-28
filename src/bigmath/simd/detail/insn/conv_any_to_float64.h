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

#ifndef SIMD_DETAIL_INSN_CONV_ANY_TO_FLOAT64_H
#define SIMD_DETAIL_INSN_CONV_ANY_TO_FLOAT64_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/core/combine.h>
#include <bigmath/simd/core/f_add.h>
#include <bigmath/simd/core/f_neg.h>
#include <bigmath/simd/core/i_shift_r.h>
#include <bigmath/simd/core/move_l.h>
#include <bigmath/simd/core/zip_lo.h>
#include <bigmath/simd/core/zip_hi.h>
#include <bigmath/simd/core/detail/subvec_insert.h>
#include <bigmath/simd/detail/mem_block.h>
#include <bigmath/simd/detail/insn/conv_extend_to_int64.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {


                static inline float64x4 i_to_float64(const float32x4 &a) {
#if SIMD_USE_AVX
                    return _mm256_cvtps_pd(a.native());
#elif SIMD_USE_SSE2
                    float64x2 r1, r2;
                    r1 = _mm_cvtps_pd(a.native());
                    r2 = _mm_cvtps_pd(move4_l<2>(a).eval().native());
                    return combine(r1, r2);
#elif SIMD_USE_NEON64
                    float64<2> r1, r2;
                    r1 = vcvt_f64_f32(vget_low_f32(a.native()));
                    r2 = vcvt_high_f64_f32(a.native());
                    return combine(r1, r2);
#elif SIMD_USE_VSX_206
                    float32<4> lo, hi;
#if SIMD_BIG_ENDIAN
                    lo = zip4_lo(a, (float32<4>)make_zero());
                    hi = zip4_hi(a, (float32<4>)make_zero());
#else
                    lo = zip4_lo((float32<4>)make_zero(), a);
                    hi = zip4_hi((float32<4>)make_zero(), a);
#endif
                    float64<2> lo_f, hi_f;
                    lo_f = __builtin_vsx_xvcvspdp(lo.native());
                    hi_f = __builtin_vsx_xvcvspdp(hi.native());
                    return combine(lo_f, hi_f);
#elif SIMD_USE_MSA
                    float64<2> lo, hi;
                    lo = __msa_fexupr_d(a.native());
                    hi = __msa_fexupl_d(a.native());
                    return combine(lo, hi);
#elif SIMD_USE_NULL || SIMD_USE_NEON32 || SIMD_USE_ALTIVEC
                    detail::mem_block<float32x4> ax(a);
                    float64x4 r;
                    r.vec(0).el(0) = double(ax[0]);
                    r.vec(0).el(1) = double(ax[1]);
                    r.vec(1).el(0) = double(ax[2]);
                    r.vec(1).el(1) = double(ax[3]);
                    return r;
#endif
                }

#if SIMD_USE_AVX
                static inline float64<8> i_to_float64(const float32x8 &a) {
#if SIMD_USE_AVX512F
                    return _mm512_cvtps_pd(a.native());
#else
                    float64x4 r1, r2;
                    float32x4 a1, a2;
                    split(a, a1, a2);
                    r1 = _mm256_cvtps_pd(a1.native());
                    r2 = _mm256_cvtps_pd(a2.native());
                    return combine(r1, r2);
#endif
                }
#endif

#if SIMD_USE_AVX512F
                static inline float64<16> i_to_float64(const float32<16> &a) {
                    float64<8> r1, r2;
                    float32<8> a1, a2;
                    split(a, a1, a2);
                    r1 = _mm512_cvtps_pd(a1.native());
                    r2 = _mm512_cvtps_pd(a2.native());
                    return combine(r1, r2);
                }
#endif

                template <unsigned N> inline float64<N> i_to_float64(const float32<N> &a) {
                    float64<N> r;
                    for (unsigned i = 0; i < a.vec_length; ++i) {
                        detail::subvec_insert(r, i_to_float64(a.vec(i)), i);
                    }
                    return r;
                }

                // -----------------------------------------------------------------------------

                static inline float64x4 i_to_float64(const int32x4 &a) {
#if SIMD_USE_AVX
                    return _mm256_cvtepi32_pd(a.native());
#elif SIMD_USE_SSE2
                    float64x2 r1, r2;
                    r1 = _mm_cvtepi32_pd(a.native());
                    r2 = _mm_cvtepi32_pd(move4_l<2>(a).eval().native());
                    return combine(r1, r2);
#elif SIMD_USE_NEON64
                    float64<2> r1, r2;
                    r1 = vcvtq_f64_s64(vmovl_s32(vget_low_s32(a.native())));
                    r2 = vcvtq_f64_s64(vmovl_s32(vget_high_s32(a.native())));
                    return combine(r1, r2);
#elif SIMD_USE_VSX_206
#if SIMD_USE_VSX_207
                    int64<4> a64 = i_to_int64(a);
                    __vector int64_t b0 = a64.vec(0).native();
                    __vector int64_t b1 = a64.vec(1).native();
#else
                    int32<4> sign = shift_r<31>(a);
                    __vector int64_t b0 = (__vector int64_t)vec_mergeh(a.native(), sign.native());
                    __vector int64_t b1 = (__vector int64_t)vec_mergel(a.native(), sign.native());
#endif

                    float64<4> r;
                    r.vec(0) = vec_ctf(b0, 0);
                    r.vec(1) = vec_ctf(b1, 0);
                    return r;
#elif SIMD_USE_MSA
                    int64<4> a64 = i_to_int64(a);
                    float64<4> r;
                    r.vec(0) = __msa_ffint_s_d(a64.vec(0).native());
                    r.vec(1) = __msa_ffint_s_d(a64.vec(1).native());
                    return r;
#elif SIMD_USE_NULL || SIMD_USE_NEON || SIMD_USE_ALTIVEC
                    detail::mem_block<int32x4> ax(a);
                    float64x4 r;
                    r.vec(0).el(0) = double(ax[0]);
                    r.vec(0).el(1) = double(ax[1]);
                    r.vec(1).el(0) = double(ax[2]);
                    r.vec(1).el(1) = double(ax[3]);
                    return r;
#endif
                }

#if SIMD_USE_AVX2
                static inline float64<8> i_to_float64(const int32x8 &a) {
#if SIMD_USE_AVX512F
                    return _mm512_cvtepi32_pd(a.native());
#else
                    float64x4 r1, r2;
                    int32x4 a1, a2;
                    split(a, a1, a2);
                    r1 = _mm256_cvtepi32_pd(a1.native());
                    r2 = _mm256_cvtepi32_pd(a2.native());
                    return combine(r1, r2);
#endif
                }
#endif

#if SIMD_USE_AVX512F
                static inline float64<16> i_to_float64(const int32<16> &a) {
                    float64<8> r1, r2;
                    r1 = _mm512_cvtepi32_pd(_mm512_castsi512_si256(a.native()));
                    r2 = _mm512_cvtepi32_pd(_mm512_extracti64x4_epi64(a.native(), 1));
                    return combine(r1, r2);
                }
#endif

                template <unsigned N> inline float64<N> i_to_float64(const int32<N> &a) {
                    float64<N> r;
                    for (unsigned i = 0; i < a.vec_length; ++i) {
                        detail::subvec_insert(r, i_to_float64(a.vec(i)), i);
                    }
                    return r;
                }

                // -----------------------------------------------------------------------------

                static inline float64<4> i_to_float64(const uint32<4> &a) {
#if SIMD_USE_AVX512VL
                    return _mm256_cvtepu32_pd(a.native());
#elif SIMD_USE_SSE2
                    float64<4> f;
#if SIMD_USE_AVX
                    f = _mm256_cvtepi32_pd(a.native());
#else
                    f.vec(0) = _mm_cvtepi32_pd(a.native());
                    f.vec(1) = _mm_cvtepi32_pd(move4_l<2>(a).eval().native());
#endif
                    // if result is negative, we converted integer larger than 0x7fffffff
                    mask_float64<4> is_large = cmp_lt(f, 0);
                    return blend(add(f, (double)0x100000000), f, is_large);
#elif SIMD_USE_NEON64
                    float64<2> r1, r2;
                    r1 = vcvtq_f64_u64(vmovl_u32(vget_low_u32(a.native())));
                    r2 = vcvtq_f64_u64(vmovl_u32(vget_high_u32(a.native())));
                    return combine(r1, r2);
#elif SIMD_USE_VSX_206
#if SIMD_USE_VSX_207
                    uint64<4> a64 = i_to_uint64(a);
                    __vector uint64_t b0 = a64.vec(0).native();
                    __vector uint64_t b1 = a64.vec(1).native();
#else
                    uint32<4> zero = make_zero();
                    __vector uint64_t b0 = (__vector uint64_t)vec_mergeh(a.native(), zero.native());
                    __vector uint64_t b1 = (__vector uint64_t)vec_mergel(a.native(), zero.native());
#endif

                    float64<4> r;
                    r.vec(0) = vec_ctf(b0, 0);
                    r.vec(1) = vec_ctf(b1, 0);
                    return r;
#elif SIMD_USE_MSA
                    uint64<4> a64 = i_to_uint64(a);
                    float64<4> r;
                    r.vec(0) = __msa_ffint_u_d(a64.vec(0).native());
                    r.vec(1) = __msa_ffint_u_d(a64.vec(1).native());
                    return r;
#elif SIMD_USE_NULL || SIMD_USE_NEON || SIMD_USE_ALTIVEC
                    detail::mem_block<uint32<4>> ax(a);
                    float64<4> r;
                    r.vec(0).el(0) = double(ax[0]);
                    r.vec(0).el(1) = double(ax[1]);
                    r.vec(1).el(0) = double(ax[2]);
                    r.vec(1).el(1) = double(ax[3]);
                    return r;
#endif
                }

#if SIMD_USE_AVX2
                static inline float64<8> i_to_float64(const uint32<8> &a) {
#if SIMD_USE_AVX512F
                    return _mm512_cvtepu32_pd(a.native());
#else
                    uint32<4> a0, a1;
                    float64<8> f;
                    split(a, a0, a1);

                    f.vec(0) = _mm256_cvtepi32_pd(a0.native());
                    f.vec(1) = _mm256_cvtepi32_pd(a1.native());

                    // if result is negative, we converted integer larger than 0x7fffffff
                    mask_float64<8> is_large = cmp_lt(f, 0);
                    return blend(add(f, (double)0x100000000), f, is_large);
#endif
                }
#endif

#if SIMD_USE_AVX512F
                static inline float64<16> i_to_float64(const uint32<16> &a) {
                    float64<16> r;
                    uint32<8> a0, a1;
                    split(a, a0, a1);

                    r.vec(0) = _mm512_cvtepu32_pd(a0.native());
                    r.vec(1) = _mm512_cvtepu32_pd(a1.native());
                    return r;
                }
#endif

                template <unsigned N> inline float64<N> i_to_float64(const uint32<N> &a) {
                    float64<N> r;
                    for (unsigned i = 0; i < a.vec_length; ++i) {
                        detail::subvec_insert(r, i_to_float64(a.vec(i)), i);
                    }
                    return r;
                }

                // -----------------------------------------------------------------------------

                template <unsigned N> inline float64<N> i_to_float64(const uint16<N> &a) {
                    return i_to_float64(i_to_uint32(a));
                }

                template <unsigned N> inline float64<N> i_to_float64(const int16<N> &a) {
                    return i_to_float64(i_to_int32(a));
                }

                // -----------------------------------------------------------------------------

                template <unsigned N> inline float64<N> i_to_float64(const uint8<N> &a) {
                    return i_to_float64(i_to_uint32(a));
                }

                template <unsigned N> inline float64<N> i_to_float64(const int8<N> &a) {
                    return i_to_float64(i_to_int32(a));
                }

                // -----------------------------------------------------------------------------

                static inline float64<2> i_to_float64(const int64<2> &a) {
#if SIMD_USE_AVX512VL
                    return _mm_cvtepi64_pd(a.native());
#elif SIMD_USE_NEON64
                    return vcvtq_f64_s64(a.native());
#elif SIMD_USE_VSX_207
                    return vec_ctf(a.native(), 0);
#elif SIMD_USE_VSX_206
                    int32<4> a32;
                    a32 = a; // a stores 64-bit values in GPR
                    return vec_ctf((__vector int64_t)a32.native(), 0);
#elif SIMD_USE_MSA
                    return __msa_ffint_s_d(a.native());
#elif SIMD_USE_NULL || SIMD_USE_NEON || SIMD_USE_ALTIVEC
                    detail::mem_block<int64<2>> ax(a);
                    float64<2> r;
                    r.el(0) = double(ax[0]);
                    r.el(1) = double(ax[1]);
                    return r;
#else
                    return SIMD_NOT_IMPLEMENTED1(a);
#endif
                }

#if SIMD_USE_AVX
                static inline float64<4> i_to_float64(const int64<4> &a) {
#if SIMD_USE_AVX512VL
                    return _mm256_cvtepi64_pd(a.native());
#else
                    return SIMD_NOT_IMPLEMENTED1(a);
#endif
                }
#endif

#if SIMD_USE_AVX512F
                static inline float64<8> i_to_float64(const int64<8> &a) {
                    return _mm512_cvtepi64_pd(a.native());
                }
#endif

                template <unsigned N> inline float64<N> i_to_float64(const int64<N> &a) {
                    float64<N> r;
                    for (unsigned i = 0; i < a.vec_length; ++i) {
                        detail::subvec_insert(r, i_to_float64(a.vec(i)), i);
                    }
                    return r;
                }

                // -----------------------------------------------------------------------------

                static inline float64<2> i_to_float64(const uint64<2> &a) {
#if SIMD_USE_AVX512VL
                    return _mm_cvtepu64_pd(a.native());
#elif SIMD_USE_NEON64
                    return vcvtq_f64_u64(a.native());
#elif SIMD_USE_VSX_207
                    return vec_ctf(a.native(), 0);
#elif SIMD_USE_VSX_206
                    uint32<4> a32;
                    a32 = a; // a stores 64-bit values in GPR
                    return vec_ctf((__vector uint64_t)a32.native(), 0);
#elif SIMD_USE_MSA
                    return __msa_ffint_u_d(a.native());
#elif SIMD_USE_NULL || SIMD_USE_NEON || SIMD_USE_ALTIVEC
                    detail::mem_block<uint64<2>> ax(a);
                    float64<2> r;
                    r.el(0) = double(ax[0]);
                    r.el(1) = double(ax[1]);
                    return r;
#else
                    return SIMD_NOT_IMPLEMENTED1(a);
#endif
                }

#if SIMD_USE_AVX
                static inline float64<4> i_to_float64(const uint64<4> &a) {
#if SIMD_USE_AVX512VL
                    return _mm256_cvtepu64_pd(a.native());
#else
                    return SIMD_NOT_IMPLEMENTED1(a);
#endif
                }
#endif

#if SIMD_USE_AVX512F
                static inline float64<8> i_to_float64(const uint64<8> &a) {
                    return _mm512_cvtepu64_pd(a.native());
                }
#endif

                template <unsigned N> inline float64<N> i_to_float64(const uint64<N> &a) {
                    float64<N> r;
                    for (unsigned i = 0; i < a.vec_length; ++i) {
                        detail::subvec_insert(r, i_to_float64(a.vec(i)), i);
                    }
                    return r;
                }

                // -----------------------------------------------------------------------------

            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
