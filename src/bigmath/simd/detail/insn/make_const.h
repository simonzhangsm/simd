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

#ifndef SIMD_DETAIL_INSN_MAKE_CONST_H
#define SIMD_DETAIL_INSN_MAKE_CONST_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/null/set.h>
#include <bigmath/simd/detail/traits.h>

#if _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4244)
#endif

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {

#if SIMD_USE_NEON_FLT_SP
                template <class VE>
                inline void i_make_const(float32<4> &v, const expr_vec_make_const<VE, 1> &e, unsigned) {
                    float rv = e.val(0);
                    v = vld1q_dup_f32(&rv);
                }

                template <class VE>
                inline void i_make_const(float32<4> &v, const expr_vec_make_const<VE, 2> &e, unsigned off) {
                    float SIMDALIGN(8) data[2] = {(float)e.val(off + 0), (float)e.val(off + 1)};
                    float32x2_t half = vld1_f32(data);
                    v = vcombine_f32(half, half);
                }
#endif

                template <class VE, unsigned N>
                inline void i_make_const(float32<4> &v, const expr_vec_make_const<VE, N> &e, unsigned off) {
#if SIMD_USE_NULL || SIMD_USE_NEON_NO_FLT_SP
                    v = detail::null::make_vec<float32<4>, float>(
                        e.val(off + 0), e.val(off + 1), e.val(off + 2), e.val(off + 3));
#elif SIMD_USE_SSE2
                    v = _mm_set_ps(e.val(off + 3), e.val(off + 2), e.val(off + 1), e.val(off + 0));
#elif SIMD_USE_NEON
                    float SIMDALIGN(16) data[4] = {
                        (float)e.val(off + 0), (float)e.val(off + 1), (float)e.val(off + 2), (float)e.val(off + 3)};
                    v = vld1q_f32(data);
#elif SIMD_USE_ALTIVEC
                    v = (__vector float){
                        float(e.val(off + 0)), float(e.val(off + 1)), float(e.val(off + 2)), float(e.val(off + 3))};
#elif SIMD_USE_MSA
                    v = (v4f32){
                        float(e.val(off + 0)), float(e.val(off + 1)), float(e.val(off + 2)), float(e.val(off + 3))};
#endif
                }

#if SIMD_USE_AVX
                template <class VE, unsigned N>
                inline void i_make_const(float32<8> &v, const expr_vec_make_const<VE, N> &e, unsigned off) {
                    v = _mm256_set_ps(e.val(off + 7),
                                      e.val(off + 6),
                                      e.val(off + 5),
                                      e.val(off + 4),
                                      e.val(off + 3),
                                      e.val(off + 2),
                                      e.val(off + 1),
                                      e.val(off + 0));
                }

#endif

#if SIMD_USE_AVX512F
                template <class VE, unsigned N>
                inline void i_make_const(float32<16> &v, const expr_vec_make_const<VE, N> &e, unsigned off) {
                    v = _mm512_set_ps(e.val(off + 15),
                                      e.val(off + 14),
                                      e.val(off + 13),
                                      e.val(off + 12),
                                      e.val(off + 11),
                                      e.val(off + 10),
                                      e.val(off + 9),
                                      e.val(off + 8),
                                      e.val(off + 7),
                                      e.val(off + 6),
                                      e.val(off + 5),
                                      e.val(off + 4),
                                      e.val(off + 3),
                                      e.val(off + 2),
                                      e.val(off + 1),
                                      e.val(off + 0));
                }
#endif

                // -----------------------------------------------------------------------------

                template <class VE, unsigned N>
                inline void i_make_const(float64<2> &v, const expr_vec_make_const<VE, N> &e, unsigned off) {
#if SIMD_USE_SSE2
                    v = _mm_set_pd(e.val(off + 1), e.val(off + 0));
#elif SIMD_USE_NEON64
                    double SIMDALIGN(16) data[2] = {(double)e.val(off + 0), (double)e.val(off + 1)};
                    v = vld1q_f64(data);
#elif SIMD_USE_VSX_206
                    __vector double r = {double(e.val(off + 0)), double(e.val(off + 1))};
                    v = r;
#elif SIMD_USE_MSA
                    v = (v2f64){double(e.val(off + 0)), double(e.val(off + 1))};
#elif SIMD_USE_NULL || SIMD_USE_NEON || SIMD_USE_ALTIVEC
                    v = detail::null::make_vec<float64<2>, double>(e.val(off + 0), e.val(off + 1));
#endif
                }

#if SIMD_USE_AVX
                template <class VE, unsigned N>
                inline void i_make_const(float64<4> &v, const expr_vec_make_const<VE, N> &e, unsigned off) {
                    v = _mm256_set_pd(e.val(off + 3), e.val(off + 2), e.val(off + 1), e.val(off + 0));
                }
#endif

#if SIMD_USE_AVX512F
                template <class VE, unsigned N>
                inline void i_make_const(float64<8> &v, const expr_vec_make_const<VE, N> &e, unsigned off) {
                    v = _mm512_set_pd(e.val(off + 7),
                                      e.val(off + 6),
                                      e.val(off + 5),
                                      e.val(off + 4),
                                      e.val(off + 3),
                                      e.val(off + 2),
                                      e.val(off + 1),
                                      e.val(off + 0));
                }
#endif

                // -----------------------------------------------------------------------------

#if SIMD_USE_NEON
                template <class VE>
                inline void i_make_const(uint8<16> &v, const expr_vec_make_const<VE, 1> &e, unsigned off) {
                    uint8_t rv = e.val(off + 0);
                    v = vld1q_dup_u8(&rv);
                }

                template <class VE>
                inline void i_make_const(uint8<16> &v, const expr_vec_make_const<VE, 2> &e, unsigned off) {
                    uint16_t rv = (e.val(off + 0) & 0xff) | (e.val(off + 1) & 0xff) << 8;
                    v = (uint16<8>)vld1q_dup_u16(&rv);
                }

                template <class VE>
                inline void i_make_const(uint8<16> &v, const expr_vec_make_const<VE, 4> &e, unsigned off) {
                    uint32_t rv = (e.val(off + 0) & 0xff) | (e.val(off + 1) & 0xff) << 8 | (e.val(off + 2) & 0xff) << 16
                                  | (e.val(off + 3) & 0xff) << 24;
                    v = (uint32<4>)vld1q_dup_u32(&rv);
                }

                template <class VE>
                inline void i_make_const(uint8<16> &v, const expr_vec_make_const<VE, 8> &e, unsigned off) {
                    uint8_t SIMDALIGN(8) data[8] = {(uint8_t)e.val(off + 0),
                                                    (uint8_t)e.val(off + 1),
                                                    (uint8_t)e.val(off + 2),
                                                    (uint8_t)e.val(off + 3),
                                                    (uint8_t)e.val(off + 4),
                                                    (uint8_t)e.val(off + 5),
                                                    (uint8_t)e.val(off + 6),
                                                    (uint8_t)e.val(off + 7)};
                    uint8x8_t half = vld1_u8(data);
                    v = vcombine_u8(half, half);
                }
#endif

                template <class VE, unsigned N>
                inline void i_make_const(uint8<16> &v, const expr_vec_make_const<VE, N> &e, unsigned off) {
#if SIMD_USE_NULL
                    v = detail::null::make_vec<uint8<16>, uint8_t>(e.val(off + 0),
                                                                   e.val(off + 1),
                                                                   e.val(off + 2),
                                                                   e.val(off + 3),
                                                                   e.val(off + 4),
                                                                   e.val(off + 5),
                                                                   e.val(off + 6),
                                                                   e.val(off + 7),
                                                                   e.val(off + 8),
                                                                   e.val(off + 9),
                                                                   e.val(off + 10),
                                                                   e.val(off + 11),
                                                                   e.val(off + 12),
                                                                   e.val(off + 13),
                                                                   e.val(off + 14),
                                                                   e.val(off + 15));
#elif SIMD_USE_SSE2
                    v = _mm_set_epi8(e.val(off + 15),
                                     e.val(off + 14),
                                     e.val(off + 13),
                                     e.val(off + 12),
                                     e.val(off + 11),
                                     e.val(off + 10),
                                     e.val(off + 9),
                                     e.val(off + 8),
                                     e.val(off + 7),
                                     e.val(off + 6),
                                     e.val(off + 5),
                                     e.val(off + 4),
                                     e.val(off + 3),
                                     e.val(off + 2),
                                     e.val(off + 1),
                                     e.val(off + 0));
#elif SIMD_USE_NEON
                    uint8_t SIMDALIGN(16) data[16] = {(uint8_t)e.val(off + 0),
                                                      (uint8_t)e.val(off + 1),
                                                      (uint8_t)e.val(off + 2),
                                                      (uint8_t)e.val(off + 3),
                                                      (uint8_t)e.val(off + 4),
                                                      (uint8_t)e.val(off + 5),
                                                      (uint8_t)e.val(off + 6),
                                                      (uint8_t)e.val(off + 7),
                                                      (uint8_t)e.val(off + 8),
                                                      (uint8_t)e.val(off + 9),
                                                      (uint8_t)e.val(off + 10),
                                                      (uint8_t)e.val(off + 11),
                                                      (uint8_t)e.val(off + 12),
                                                      (uint8_t)e.val(off + 13),
                                                      (uint8_t)e.val(off + 14),
                                                      (uint8_t)e.val(off + 15)};
                    v = vld1q_u8(data);
#elif SIMD_USE_ALTIVEC
                    v = (__vector uint8_t){uint8_t(e.val(off + 0)),
                                           uint8_t(e.val(off + 1)),
                                           uint8_t(e.val(off + 2)),
                                           uint8_t(e.val(off + 3)),
                                           uint8_t(e.val(off + 4)),
                                           uint8_t(e.val(off + 5)),
                                           uint8_t(e.val(off + 6)),
                                           uint8_t(e.val(off + 7)),
                                           uint8_t(e.val(off + 8)),
                                           uint8_t(e.val(off + 9)),
                                           uint8_t(e.val(off + 10)),
                                           uint8_t(e.val(off + 11)),
                                           uint8_t(e.val(off + 12)),
                                           uint8_t(e.val(off + 13)),
                                           uint8_t(e.val(off + 14)),
                                           uint8_t(e.val(off + 15))};
#elif SIMD_USE_MSA
                    v = (v16u8){uint8_t(e.val(off + 0)),
                                uint8_t(e.val(off + 1)),
                                uint8_t(e.val(off + 2)),
                                uint8_t(e.val(off + 3)),
                                uint8_t(e.val(off + 4)),
                                uint8_t(e.val(off + 5)),
                                uint8_t(e.val(off + 6)),
                                uint8_t(e.val(off + 7)),
                                uint8_t(e.val(off + 8)),
                                uint8_t(e.val(off + 9)),
                                uint8_t(e.val(off + 10)),
                                uint8_t(e.val(off + 11)),
                                uint8_t(e.val(off + 12)),
                                uint8_t(e.val(off + 13)),
                                uint8_t(e.val(off + 14)),
                                uint8_t(e.val(off + 15))};
#endif
                }

#if SIMD_USE_AVX2
                template <class VE, unsigned N>
                inline void i_make_const(uint8<32> &v, const expr_vec_make_const<VE, N> &e, unsigned off) {
                    v = _mm256_set_epi8(e.val(off + 31),
                                        e.val(off + 30),
                                        e.val(off + 29),
                                        e.val(off + 28),
                                        e.val(off + 27),
                                        e.val(off + 26),
                                        e.val(off + 25),
                                        e.val(off + 24),
                                        e.val(off + 23),
                                        e.val(off + 22),
                                        e.val(off + 21),
                                        e.val(off + 20),
                                        e.val(off + 19),
                                        e.val(off + 18),
                                        e.val(off + 17),
                                        e.val(off + 16),
                                        e.val(off + 15),
                                        e.val(off + 14),
                                        e.val(off + 13),
                                        e.val(off + 12),
                                        e.val(off + 11),
                                        e.val(off + 10),
                                        e.val(off + 9),
                                        e.val(off + 8),
                                        e.val(off + 7),
                                        e.val(off + 6),
                                        e.val(off + 5),
                                        e.val(off + 4),
                                        e.val(off + 3),
                                        e.val(off + 2),
                                        e.val(off + 1),
                                        e.val(off + 0));
                }
#endif

#if SIMD_USE_AVX512BW
                inline uint32_t make_uint32_uint8(uint8_t a1, uint8_t a2, uint8_t a3, uint8_t a4) {
                    return (a1 & 0xff) | ((a2 & 0xff) << 8) | ((a3 & 0xff) << 16) | ((a4 & 0xff) << 24);
                }

                template <class VE, unsigned N>
                inline void i_make_const(uint8<64> &v, const expr_vec_make_const<VE, N> &e, unsigned off) {
                    v = _mm512_set_epi32(
                        make_uint32_uint8(e.val(off + 60), e.val(off + 61), e.val(off + 62), e.val(off + 63)),
                        make_uint32_uint8(e.val(off + 56), e.val(off + 57), e.val(off + 58), e.val(off + 59)),
                        make_uint32_uint8(e.val(off + 52), e.val(off + 53), e.val(off + 54), e.val(off + 55)),
                        make_uint32_uint8(e.val(off + 48), e.val(off + 49), e.val(off + 50), e.val(off + 51)),
                        make_uint32_uint8(e.val(off + 44), e.val(off + 45), e.val(off + 46), e.val(off + 47)),
                        make_uint32_uint8(e.val(off + 40), e.val(off + 41), e.val(off + 42), e.val(off + 43)),
                        make_uint32_uint8(e.val(off + 36), e.val(off + 37), e.val(off + 38), e.val(off + 39)),
                        make_uint32_uint8(e.val(off + 32), e.val(off + 33), e.val(off + 34), e.val(off + 35)),
                        make_uint32_uint8(e.val(off + 28), e.val(off + 29), e.val(off + 30), e.val(off + 31)),
                        make_uint32_uint8(e.val(off + 24), e.val(off + 25), e.val(off + 26), e.val(off + 27)),
                        make_uint32_uint8(e.val(off + 20), e.val(off + 21), e.val(off + 22), e.val(off + 23)),
                        make_uint32_uint8(e.val(off + 16), e.val(off + 17), e.val(off + 18), e.val(off + 19)),
                        make_uint32_uint8(e.val(off + 12), e.val(off + 13), e.val(off + 14), e.val(off + 15)),
                        make_uint32_uint8(e.val(off + 8), e.val(off + 9), e.val(off + 10), e.val(off + 11)),
                        make_uint32_uint8(e.val(off + 4), e.val(off + 5), e.val(off + 6), e.val(off + 7)),
                        make_uint32_uint8(e.val(off + 0), e.val(off + 1), e.val(off + 2), e.val(off + 3)));
                }
#endif


                // -----------------------------------------------------------------------------

#if SIMD_USE_NEON
                template <class VE>
                inline void i_make_const(uint16<8> &v, const expr_vec_make_const<VE, 1> &e, unsigned off) {
                    uint16_t rv = e.val(off + 0);
                    v = vld1q_dup_u16(&rv);
                }

                template <class VE>
                inline void i_make_const(uint16<8> &v, const expr_vec_make_const<VE, 2> &e, unsigned off) {
                    uint32_t rv = (e.val(off + 0) & 0xffff) | (e.val(off + 1) & 0xffff) << 16;
                    v = (uint32<4>)vld1q_dup_u32(&rv);
                }

                template <class VE>
                inline void i_make_const(uint16<8> &v, const expr_vec_make_const<VE, 4> &e, unsigned off) {
                    uint16_t SIMDALIGN(8) data[4] = {(uint16_t)e.val(off + 0),
                                                     (uint16_t)e.val(off + 1),
                                                     (uint16_t)e.val(off + 2),
                                                     (uint16_t)e.val(off + 3)};
                    uint16x4_t half = vld1_u16(data);
                    v = vcombine_u16(half, half);
                }
#endif


                template <class VE, unsigned N>
                inline void i_make_const(uint16<8> &v, const expr_vec_make_const<VE, N> &e, unsigned off) {
#if SIMD_USE_NULL
                    v = detail::null::make_vec<uint16<8>, uint16_t>(e.val(off + 0),
                                                                    e.val(off + 1),
                                                                    e.val(off + 2),
                                                                    e.val(off + 3),
                                                                    e.val(off + 4),
                                                                    e.val(off + 5),
                                                                    e.val(off + 6),
                                                                    e.val(off + 7));
#elif SIMD_USE_SSE2
                    v = _mm_set_epi16(e.val(off + 7),
                                      e.val(off + 6),
                                      e.val(off + 5),
                                      e.val(off + 4),
                                      e.val(off + 3),
                                      e.val(off + 2),
                                      e.val(off + 1),
                                      e.val(off + 0));
#elif SIMD_USE_NEON
                    uint16_t SIMDALIGN(16) data[8] = {(uint16_t)e.val(off + 0),
                                                      (uint16_t)e.val(off + 1),
                                                      (uint16_t)e.val(off + 2),
                                                      (uint16_t)e.val(off + 3),
                                                      (uint16_t)e.val(off + 4),
                                                      (uint16_t)e.val(off + 5),
                                                      (uint16_t)e.val(off + 6),
                                                      (uint16_t)e.val(off + 7)};
                    v = vld1q_u16(data);
#elif SIMD_USE_ALTIVEC
                    v = (__vector uint16_t){uint16_t(e.val(off + 0)),
                                            uint16_t(e.val(off + 1)),
                                            uint16_t(e.val(off + 2)),
                                            uint16_t(e.val(off + 3)),
                                            uint16_t(e.val(off + 4)),
                                            uint16_t(e.val(off + 5)),
                                            uint16_t(e.val(off + 6)),
                                            uint16_t(e.val(off + 7))};
#elif SIMD_USE_MSA
                    v = (v8u16){uint16_t(e.val(off + 0)),
                                uint16_t(e.val(off + 1)),
                                uint16_t(e.val(off + 2)),
                                uint16_t(e.val(off + 3)),
                                uint16_t(e.val(off + 4)),
                                uint16_t(e.val(off + 5)),
                                uint16_t(e.val(off + 6)),
                                uint16_t(e.val(off + 7))};
#endif
                }

#if SIMD_USE_AVX2
                template <class VE, unsigned N>
                inline void i_make_const(uint16<16> &v, const expr_vec_make_const<VE, N> &e, unsigned off) {
                    v = _mm256_set_epi16(e.val(off + 15),
                                         e.val(off + 14),
                                         e.val(off + 13),
                                         e.val(off + 12),
                                         e.val(off + 11),
                                         e.val(off + 10),
                                         e.val(off + 9),
                                         e.val(off + 8),
                                         e.val(off + 7),
                                         e.val(off + 6),
                                         e.val(off + 5),
                                         e.val(off + 4),
                                         e.val(off + 3),
                                         e.val(off + 2),
                                         e.val(off + 1),
                                         e.val(off + 0));
                }
#endif

#if SIMD_USE_AVX512BW
                inline uint32_t make_uint32_uint16(uint16_t a1, uint16_t a2) {
                    return (a1 & 0xffff) | ((a2 & 0xffff) << 16);
                }

                template <class VE, unsigned N>
                inline void i_make_const(uint16<32> &v, const expr_vec_make_const<VE, N> &e, unsigned off) {
                    v = _mm512_set_epi32(make_uint32_uint16(e.val(off + 30), e.val(off + 31)),
                                         make_uint32_uint16(e.val(off + 28), e.val(off + 29)),
                                         make_uint32_uint16(e.val(off + 26), e.val(off + 27)),
                                         make_uint32_uint16(e.val(off + 24), e.val(off + 25)),
                                         make_uint32_uint16(e.val(off + 22), e.val(off + 23)),
                                         make_uint32_uint16(e.val(off + 20), e.val(off + 21)),
                                         make_uint32_uint16(e.val(off + 18), e.val(off + 19)),
                                         make_uint32_uint16(e.val(off + 16), e.val(off + 17)),
                                         make_uint32_uint16(e.val(off + 14), e.val(off + 15)),
                                         make_uint32_uint16(e.val(off + 12), e.val(off + 13)),
                                         make_uint32_uint16(e.val(off + 10), e.val(off + 11)),
                                         make_uint32_uint16(e.val(off + 8), e.val(off + 9)),
                                         make_uint32_uint16(e.val(off + 6), e.val(off + 7)),
                                         make_uint32_uint16(e.val(off + 4), e.val(off + 5)),
                                         make_uint32_uint16(e.val(off + 2), e.val(off + 3)),
                                         make_uint32_uint16(e.val(off + 0), e.val(off + 1)));
                }
#endif

                // -----------------------------------------------------------------------------

#if SIMD_USE_NEON
                template <class VE>
                inline void i_make_const(uint32<4> &v, const expr_vec_make_const<VE, 1> &e, unsigned off) {
                    uint32_t rv = e.val(off + 0);
                    v = vld1q_dup_u32(&rv);
                }

                template <class VE>
                inline void i_make_const(uint32<4> &v, const expr_vec_make_const<VE, 2> &e, unsigned off) {
                    uint32_t SIMDALIGN(8) data[2] = {(uint32_t)e.val(off + 0), (uint32_t)e.val(off + 1)};
                    uint32x2_t half = vld1_u32(data);
                    v = vcombine_u32(half, half);
                }
#endif

                template <class VE, unsigned N>
                inline void i_make_const(uint32<4> &v, const expr_vec_make_const<VE, N> &e, unsigned off) {
#if SIMD_USE_NULL
                    v = detail::null::make_vec<uint32<4>, uint32_t>(
                        e.val(off + 0), e.val(off + 1), e.val(off + 2), e.val(off + 3));
#elif SIMD_USE_SSE2
                    v = _mm_set_epi32(e.val(off + 3), e.val(off + 2), e.val(off + 1), e.val(off + 0));
#elif SIMD_USE_NEON
                    uint32_t SIMDALIGN(16) data[4] = {(uint32_t)e.val(off + 0),
                                                      (uint32_t)e.val(off + 1),
                                                      (uint32_t)e.val(off + 2),
                                                      (uint32_t)e.val(off + 3)};
                    v = vld1q_u32(data);
#elif SIMD_USE_ALTIVEC
                    v = (__vector uint32_t){uint32_t(e.val(off + 0)),
                                            uint32_t(e.val(off + 1)),
                                            uint32_t(e.val(off + 2)),
                                            uint32_t(e.val(off + 3))};
#elif SIMD_USE_MSA
                    v = (v4u32){uint32_t(e.val(off + 0)),
                                uint32_t(e.val(off + 1)),
                                uint32_t(e.val(off + 2)),
                                uint32_t(e.val(off + 3))};
#endif
                }

#if SIMD_USE_AVX2
                template <class VE, unsigned N>
                inline void i_make_const(uint32<8> &v, const expr_vec_make_const<VE, N> &e, unsigned off) {
                    v = _mm256_set_epi32(e.val(off + 7),
                                         e.val(off + 6),
                                         e.val(off + 5),
                                         e.val(off + 4),
                                         e.val(off + 3),
                                         e.val(off + 2),
                                         e.val(off + 1),
                                         e.val(off + 0));
                }
#endif

#if SIMD_USE_AVX512F
                template <class VE, unsigned N>
                inline void i_make_const(uint32<16> &v, const expr_vec_make_const<VE, N> &e, unsigned off) {
                    v = _mm512_set_epi32(e.val(off + 15),
                                         e.val(off + 14),
                                         e.val(off + 13),
                                         e.val(off + 12),
                                         e.val(off + 11),
                                         e.val(off + 10),
                                         e.val(off + 9),
                                         e.val(off + 8),
                                         e.val(off + 7),
                                         e.val(off + 6),
                                         e.val(off + 5),
                                         e.val(off + 4),
                                         e.val(off + 3),
                                         e.val(off + 2),
                                         e.val(off + 1),
                                         e.val(off + 0));
                }
#endif

                // -----------------------------------------------------------------------------

#if SIMD_USE_NEON
                template <class VE>
                inline void i_make_const(uint64<2> &v, const expr_vec_make_const<VE, 1> &e, unsigned off) {
                    uint64x1_t r0 = vcreate_u64(uint64_t(e.val(off + 0)));
                    v = vcombine_u64(r0, r0);
                }
#endif

                template <class VE, unsigned N>
                inline void i_make_const(uint64<2> &v, const expr_vec_make_const<VE, N> &e, unsigned off) {
#if SIMD_USE_SSE2
#if SIMD_32_BITS && _MSC_VER
                    // MSVC does not support _mm_set_epi64x in 32-bit mode
                    uint64_t v1 = e.val(off + 1);
                    uint64_t v0 = e.val(off + 0);
                    v = _mm_set_epi32(v1 >> 32, v1 & 0xffffffff, v0 >> 32, v0 & 0xffffffff);
#else
                    v = _mm_set_epi64x(e.val(off + 1), e.val(off + 0));
#endif
#elif SIMD_USE_NEON
                    uint64_t SIMDALIGN(16) data[2] = {(uint64_t)e.val(off + 0), (uint64_t)e.val(off + 1)};
                    v = vld1q_u64(data);
#elif SIMD_USE_VSX_207
                    __vector uint64_t r = {(uint64_t)e.val(off + 0), (uint64_t)e.val(off + 1)};
                    v = r;
#elif SIMD_USE_MSA
                    v = (v2u64){uint64_t(e.val(off + 0)), uint64_t(e.val(off + 1))};
#elif SIMD_USE_NULL || SIMD_USE_ALTIVEC
                    v = detail::null::make_vec<uint64<2>, uint64_t>(e.val(off + 0), e.val(off + 1));
#endif
                }

#if SIMD_USE_AVX2
                template <class VE, unsigned N>
                inline void i_make_const(uint64<4> &v, const expr_vec_make_const<VE, N> &e, unsigned off) {
#if SIMD_32_BITS && _MSC_VER
                    // MSVC does not support _mm256_set_epi64x in 32-bit mode
                    uint64_t v3 = e.val(off + 3);
                    uint64_t v2 = e.val(off + 2);
                    uint64_t v1 = e.val(off + 1);
                    uint64_t v0 = e.val(off + 0);
                    v = _mm256_set_epi32(v3 >> 32,
                                         v3 & 0xffffffff,
                                         v2 >> 32,
                                         v2 & 0xffffffff,
                                         v1 >> 32,
                                         v1 & 0xffffffff,
                                         v0 >> 32,
                                         v0 & 0xffffffff);
#else
                    v = _mm256_set_epi64x(e.val(off + 3), e.val(off + 2), e.val(off + 1), e.val(off + 0));
#endif
                }
#endif

#if SIMD_USE_AVX512F
                template <class VE, unsigned N>
                inline void i_make_const(uint64<8> &v, const expr_vec_make_const<VE, N> &e, unsigned off) {
                    v = _mm512_set_epi64(e.val(off + 7),
                                         e.val(off + 6),
                                         e.val(off + 5),
                                         e.val(off + 4),
                                         e.val(off + 3),
                                         e.val(off + 2),
                                         e.val(off + 1),
                                         e.val(off + 0));
                }
#endif

                // -----------------------------------------------------------------------------

                template <class V, class VE, unsigned NE>
                inline void i_make_const(V &v, const expr_vec_make_const<VE, NE> &e, unsigned off) {
                    for (unsigned i = 0; i < v.vec_length; ++i) {
                        i_make_const(v.vec(i), e, off + v.base_length * i);
                    }
                }

                // -----------------------------------------------------------------------------

                template <class V, class VE, unsigned N>
                inline V i_make_const_any(const expr_vec_make_const<VE, N> &e) {
                    typename detail::remove_sign<V>::type r;
                    i_make_const(r, e, 0);
                    return V(r);
                }

                // -----------------------------------------------------------------------------
            } // namespace insn

            template <class V, class VE, unsigned N>
            inline void construct_eval(V &v, const expr_vec_make_const<VE, N> &e) {
                v = insn::i_make_const_any<V>(e);
            }

            template <class V> inline void construct_eval(V &v, const expr_vec_make_ones &e) {
                (void)e;
                expr_vec_make_const<uint64_t, 1> e2;
                e2.a[0] = (uint64_t)-1;
                typename V::uint_vector_type u;
                insn::i_make_const(u, e2, 0);
                v = u;
            }

        } // namespace detail
    }     // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#if _MSC_VER
#pragma warning(pop)
#endif

#endif
