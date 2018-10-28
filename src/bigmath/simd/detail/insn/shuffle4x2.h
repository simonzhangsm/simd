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

#ifndef SIMD_DETAIL_INSN_SHUFFLE4x2_H
#define SIMD_DETAIL_INSN_SHUFFLE4x2_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/core/make_shuffle_bytes_mask.h>
#include <bigmath/simd/core/shuffle_bytes16.h>
#include <bigmath/simd/detail/insn/shuffle2x2.h>
#include <bigmath/simd/detail/shuffle/sse_float32_4x2.h>
#include <bigmath/simd/detail/shuffle/sse_float64_4x2.h>
#include <bigmath/simd/detail/shuffle/sse_int32_4x2.h>
#include <bigmath/simd/detail/shuffle/sse_int64_4x2.h>
#include <bigmath/simd/detail/shuffle/neon_int32x4.h>
#include <bigmath/simd/detail/not_implemented.h>
#include <bigmath/simd/detail/vector_array_macros.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {

                // -----------------------------------------------------------------------------
                // emulates 64x4 shuffle on architectures with 128-bit vectors

                template <unsigned s0, unsigned s1, class V>
                V i_shuffle_emul_64x4_half(const V &a0, const V &a1, const V &b0, const V &b1) {
                    const V &h0 = s0 < 2 ? a0 : s0 < 4 ? a1 : s0 < 6 ? b0 : b1;
                    const V &h1 = s1 < 2 ? a0 : s1 < 4 ? a1 : s1 < 6 ? b0 : b1;
                    return i_shuffle2x2<s0 % 2, s1 % 2 + 2>(h0, h1);
                }

                // -----------------------------------------------------------------------------
                // float32

                template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                inline float32<4> i_shuffle4x2(const float32<4> &a, const float32<4> &b) {
                    static_assert(s0 < 8 && s1 < 8 && s2 < 8 && s3 < 8, "Selector out of range");
#if SIMD_USE_NULL || SIMD_USE_NEON_NO_FLT_SP
                    float32<4> r;
                    r.el(0) = s0 < 4 ? a.el(s0) : b.el(s0 - 4);
                    r.el(1) = s1 < 4 ? a.el(s1) : b.el(s1 - 4);
                    r.el(2) = s2 < 4 ? a.el(s2) : b.el(s2 - 4);
                    r.el(3) = s3 < 4 ? a.el(s3) : b.el(s3 - 4);
                    return r;
#elif SIMD_USE_SSE2
                    return sse_shuffle4x2_float32::do_shuffle<s0, s1, s2, s3>(a, b);
#elif SIMD_USE_NEON_FLT_SP
                    return (float32<4>)detail::neon_shuffle_int32x4::shuffle4x2<s0, s1, s2, s3>(uint32<4>(a),
                                                                                                uint32<4>(b));
#elif SIMD_USE_ALTIVEC
                    uint32<4> mask = make_shuffle_bytes16_mask<s0, s1, s2, s3>(mask);
                    return shuffle_bytes16(a, b, mask);
#elif SIMD_USE_MSA
                    uint32<4> mask = make_uint(s0, s1, s2, s3);
                    return (v4f32)__msa_vshf_w((v4i32)mask.native(), (v4i32)b.native(), (v4i32)a.native());
#else
                    return SIMD_NOT_IMPLEMENTED_TEMPLATE2(int64<s0 + 4>, a, b);
#endif
                }

#if SIMD_USE_AVX
                template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                inline float32<8> i_shuffle4x2(const float32<8> &a, const float32<8> &b) {
                    static_assert(s0 < 8 && s1 < 8 && s2 < 8 && s3 < 8, "Selector out of range");
                    return sse_shuffle4x2_float32::do_shuffle<s0, s1, s2, s3>(a, b);
                }
#endif

#if SIMD_USE_AVX512F
                template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                inline float32<16> i_shuffle4x2(const float32<16> &a, const float32<16> &b) {
                    static_assert(s0 < 8 && s1 < 8 && s2 < 8 && s3 < 8, "Selector out of range");
                    return sse_shuffle4x2_float32::do_shuffle<s0, s1, s2, s3>(a, b);
                }
#endif

                template <unsigned s0, unsigned s1, unsigned s2, unsigned s3, unsigned N>
                inline float32<N> i_shuffle4x2(const float32<N> &a, const float32<N> &b) {
                    SIMD_VEC_ARRAY_IMPL2(float32<N>, (i_shuffle4x2<s0, s1, s2, s3>), a, b);
                }

                // -----------------------------------------------------------------------------
                // float64

#if SIMD_USE_AVX
                template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                inline float64<4> i_shuffle4x2(const float64<4> &a, const float64<4> &b) {
                    static_assert(s0 < 8 && s1 < 8 && s2 < 8 && s3 < 8, "Selector out of range");
                    return sse_shuffle4x2_float64::do_shuffle<s0, s1, s2, s3>(a, b);
                }
#endif

#if SIMD_USE_AVX512F
                template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                inline float64<8> i_shuffle4x2(const float64<8> &a, const float64<8> &b) {
                    static_assert(s0 < 8 && s1 < 8 && s2 < 8 && s3 < 8, "Selector out of range");
                    return sse_shuffle4x2_float64::do_shuffle<s0, s1, s2, s3>(a, b);
                }
#endif

                template <unsigned s0, unsigned s1, unsigned s2, unsigned s3, unsigned N>
                inline float64<N> i_shuffle4x2(const float64<N> &a, const float64<N> &b) {
#if SIMD_USE_AVX
                    SIMD_VEC_ARRAY_IMPL2(float64<N>, (i_shuffle4x2<s0, s1, s2, s3>), a, b);
#else
                    float64<N> r;
                    for (unsigned i = 0; i < float64<N>::vec_length; i += 2) {
                        r.vec(i * 2) = i_shuffle_emul_64x4_half<s0, s1>(
                            a.vec(i * 2), a.vec(i * 2 + 1), b.vec(i * 2), b.vec(i * 2 + 1));
                        r.vec(i * 2 + 1) = i_shuffle_emul_64x4_half<s2, s3>(
                            a.vec(i * 2), a.vec(i * 2 + 1), b.vec(i * 2), b.vec(i * 2 + 1));
                    }
                    return r;
#endif
                }

                // -----------------------------------------------------------------------------

                template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                inline uint32<4> i_shuffle4x2(const uint32<4> &a, const uint32<4> &b) {
                    static_assert(s0 < 8 && s1 < 8 && s2 < 8 && s3 < 8, "Selector out of range");
#if SIMD_USE_NULL
                    uint32<4> r;
                    r.el(0) = s0 < 4 ? a.el(s0) : b.el(s0 - 4);
                    r.el(1) = s1 < 4 ? a.el(s1) : b.el(s1 - 4);
                    r.el(2) = s2 < 4 ? a.el(s2) : b.el(s2 - 4);
                    r.el(3) = s3 < 4 ? a.el(s3) : b.el(s3 - 4);
                    return r;
#elif SIMD_USE_SSE2
                    return sse_shuffle4x2_int32::do_shuffle<s0, s1, s2, s3>(a, b);
#elif SIMD_USE_NEON
                    return detail::neon_shuffle_int32x4::shuffle4x2<s0, s1, s2, s3>(a, b);
#elif SIMD_USE_ALTIVEC
                    uint32<4> mask = make_shuffle_bytes16_mask<s0, s1, s2, s3>(mask);
                    return shuffle_bytes16(a, b, mask);
#elif SIMD_USE_MSA
                    uint32<4> mask = make_uint(s0, s1, s2, s3);
                    return (v4u32)__msa_vshf_w((v4i32)mask.native(), (v4i32)b.native(), (v4i32)a.native());
#else
                    return SIMD_NOT_IMPLEMENTED_TEMPLATE2(int64<s0 + 4>, a, b);
#endif
                }

#if SIMD_USE_AVX2
                template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                inline uint32<8> i_shuffle4x2(const uint32<8> &a, const uint32<8> &b) {
                    static_assert(s0 < 8 && s1 < 8 && s2 < 8 && s3 < 8, "Selector out of range");
                    return sse_shuffle4x2_int32::do_shuffle<s0, s1, s2, s3>(a, b);
                }
#endif

#if SIMD_USE_AVX512F
                template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                inline uint32<16> i_shuffle4x2(const uint32<16> &a, const uint32<16> &b) {
                    static_assert(s0 < 8 && s1 < 8 && s2 < 8 && s3 < 8, "Selector out of range");
                    return sse_shuffle4x2_int32::do_shuffle<s0, s1, s2, s3>(a, b);
                }
#endif

                template <unsigned s0, unsigned s1, unsigned s2, unsigned s3, unsigned N>
                inline uint32<N> i_shuffle4x2(const uint32<N> &a, const uint32<N> &b) {
                    SIMD_VEC_ARRAY_IMPL2(uint32<N>, (i_shuffle4x2<s0, s1, s2, s3>), a, b);
                }

                // -----------------------------------------------------------------------------
                // int64

#if SIMD_USE_AVX2
                template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                inline uint64<4> i_shuffle4x2(const uint64<4> &a, const uint64<4> &b) {
                    static_assert(s0 < 8 && s1 < 8 && s2 < 8 && s3 < 8, "Selector out of range");
                    return sse_shuffle4x2_int64::do_shuffle<s0, s1, s2, s3>(a, b);
                }
#endif

#if SIMD_USE_AVX512F
                template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                inline uint64<8> i_shuffle4x2(const uint64<8> &a, const uint64<8> &b) {
                    static_assert(s0 < 8 && s1 < 8 && s2 < 8 && s3 < 8, "Selector out of range");
                    return sse_shuffle4x2_int64::do_shuffle<s0, s1, s2, s3>(a, b);
                }
#endif

                template <unsigned s0, unsigned s1, unsigned s2, unsigned s3, unsigned N>
                inline uint64<N> i_shuffle4x2(const uint64<N> &a, const uint64<N> &b) {
#if SIMD_USE_AVX2
                    SIMD_VEC_ARRAY_IMPL2(uint64<N>, (i_shuffle4x2<s0, s1, s2, s3>), a, b);
#else
                    uint64<N> r;
                    for (unsigned i = 0; i < uint64<N>::vec_length; i += 2) {
                        r.vec(i * 2) = i_shuffle_emul_64x4_half<s0, s1>(
                            a.vec(i * 2), a.vec(i * 2 + 1), b.vec(i * 2), b.vec(i * 2 + 1));
                        r.vec(i * 2 + 1) = i_shuffle_emul_64x4_half<s2, s3>(
                            a.vec(i * 2), a.vec(i * 2 + 1), b.vec(i * 2), b.vec(i * 2 + 1));
                    }
                    return r;
#endif
                }


            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
