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

#ifndef SIMD_DETAIL_INSN_CONV_EXTEND_TO_INT16_H
#define SIMD_DETAIL_INSN_CONV_EXTEND_TO_INT16_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/core/combine.h>
#include <bigmath/simd/detail/not_implemented.h>
#include <bigmath/simd/core/i_shift_r.h>
#include <bigmath/simd/core/move_l.h>
#include <bigmath/simd/core/zip_hi.h>
#include <bigmath/simd/core/zip_lo.h>
#include <bigmath/simd/detail/vector_array_conv_macros.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {

                inline uint16<16> i_to_uint16(const uint8<16> &a) {
#if SIMD_USE_NULL
                    uint16x16 r;
                    for (unsigned i = 0; i < 16; i++) {
                        r.vec(i / 8).el(i % 8) = uint16_t(a.el(i));
                    }
                    return r;
#elif SIMD_USE_AVX2
                    return _mm256_cvtepu8_epi16(a.native());
#elif SIMD_USE_SSE4_1
                    uint16x8 r1, r2;
                    r1 = _mm_cvtepu8_epi16(a.native());
                    r2 = _mm_cvtepu8_epi16(move16_l<8>(a).eval().native());
                    return combine(r1, r2);
#elif SIMD_USE_SSE2 || (SIMD_USE_ALTIVEC && SIMD_LITTLE_ENDIAN) || SIMD_USE_MSA
                    uint16x8 r1, r2;
                    r1 = zip16_lo(a, (uint8x16)make_zero());
                    r2 = zip16_hi(a, (uint8x16)make_zero());
                    return combine(r1, r2);
#elif SIMD_USE_NEON
                    uint16x16 r;
                    r.vec(0) = vmovl_u8(vget_low_u8(a.native()));
                    r.vec(1) = vmovl_u8(vget_high_u8(a.native()));
                    return r;
#elif (SIMD_USE_ALTIVEC && SIMD_BIG_ENDIAN)
                    uint16x8 r1, r2;
                    r1 = zip16_lo((uint8x16)make_zero(), a);
                    r2 = zip16_hi((uint8x16)make_zero(), a);
                    return combine(r1, r2);
#endif
                }

#if SIMD_USE_AVX2
                inline uint16<32> i_to_uint16(const uint8<32> &a) {
#if SIMD_USE_AVX512BW
                    return _mm512_cvtepu8_epi16(a.native());
#else
                    uint16<16> r0, r1;
                    uint8<16> a0, a1;
                    split(a, a0, a1);
                    r0 = _mm256_cvtepu8_epi16(a0.native());
                    r1 = _mm256_cvtepu8_epi16(a1.native());
                    return combine(r0, r1);
#endif
                }
#endif

#if SIMD_USE_AVX512BW
                inline uint16<64> i_to_uint16(const uint8<64> &a) {
                    uint16<32> r0, r1;
                    uint8<32> a0, a1;
                    split(a, a0, a1);
                    r0 = _mm512_cvtepu8_epi16(a0.native());
                    r1 = _mm512_cvtepu8_epi16(a1.native());
                    return combine(r0, r1);
                }
#endif

                template <unsigned N> inline uint16<N> i_to_uint16(const uint8<N> &a) {
                    SIMD_VEC_ARRAY_IMPL_CONV_INSERT(uint16<N>, i_to_uint16, a)
                }

                // -----------------------------------------------------------------------------

                inline int16x16 i_to_int16(const int8x16 &a) {
#if SIMD_USE_NULL
                    int16x16 r;
                    for (unsigned i = 0; i < 16; i++) {
                        r.vec(i / 8).el(i % 8) = int16_t(a.el(i));
                    }
                    return r;
#elif SIMD_USE_AVX2
                    return _mm256_cvtepi8_epi16(a.native());
#elif SIMD_USE_SSE4_1
                    int16x8 r1, r2;
                    r1 = _mm_cvtepi8_epi16(a.native());
                    r2 = _mm_cvtepi8_epi16(move16_l<8>(a).eval().native());
                    return combine(r1, r2);
#elif SIMD_USE_SSE2
                    int16x8 r1, r2;
                    r1 = zip16_lo((int8x16)make_zero(), a);
                    r1 = shift_r<8>(r1);
                    r2 = zip16_hi((int8x16)make_zero(), a);
                    r2 = shift_r<8>(r2);
                    return combine(r1, r2);
#elif SIMD_USE_NEON
                    int16x16 r;
                    r.vec(0) = vmovl_s8(vget_low_s8(a.native()));
                    r.vec(1) = vmovl_s8(vget_high_s8(a.native()));
                    return r;
#elif SIMD_USE_MSA
                    int8x16 sign = shift_r<7>(a);
                    int16x8 lo, hi;
                    lo = zip16_lo(a, sign);
                    hi = zip16_hi(a, sign);
                    return combine(lo, hi);
#elif SIMD_USE_ALTIVEC
                    int16x16 r;
                    r.vec(0) = vec_unpackh(a.vec(0).native());
                    r.vec(1) = vec_unpackl(a.vec(0).native());
                    return r;
#endif
                }

#if SIMD_USE_AVX2
                inline int16<32> i_to_int16(const int8<32> &a) {
#if SIMD_USE_AVX512BW
                    return _mm512_cvtepi8_epi16(a.native());
#else
                    int16<16> r0, r1;
                    int8<16> a0, a1;
                    split(a, a0, a1);
                    r0 = _mm256_cvtepi8_epi16(a0.native());
                    r1 = _mm256_cvtepi8_epi16(a1.native());
                    return combine(r0, r1);
#endif
                }
#endif

#if SIMD_USE_AVX512BW
                inline int16<64> i_to_int16(const int8<64> &a) {
                    int16<32> r0, r1;
                    int8<32> a0, a1;
                    split(a, a0, a1);
                    r0 = _mm512_cvtepi8_epi16(a0.native());
                    r1 = _mm512_cvtepi8_epi16(a1.native());
                    return combine(r0, r1);
                }
#endif

                template <unsigned N> inline int16<N> i_to_int16(const int8<N> &a) {
                    SIMD_VEC_ARRAY_IMPL_CONV_INSERT(int16<N>, i_to_int16, a)
                }


            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
