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

#ifndef SIMD_DETAIL_INSN_PERMUTE2_H
#define SIMD_DETAIL_INSN_PERMUTE2_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/core/make_shuffle_bytes_mask.h>
#include <bigmath/simd/core/permute4.h>
#include <bigmath/simd/detail/null/shuffle.h>
#include <bigmath/simd/detail/shuffle/neon_int16x8.h>
#include <bigmath/simd/detail/shuffle/neon_int32x4.h>
#include <bigmath/simd/detail/shuffle/neon_int64x2.h>
#include <bigmath/simd/detail/shuffle/shuffle_mask.h>
#include <bigmath/simd/detail/vector_array_macros.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {


                template <unsigned s0, unsigned s1, unsigned N> inline uint16<N> i_permute2(const uint16<N> &a) {
                    static_assert(s0 < 2 && s1 < 2, "Selector out of range");
                    return i_permute4<s0, s1, s0 + 2, s1 + 2>(a);
                }


                template <unsigned s0, unsigned s1, unsigned N> inline uint32<N> i_permute2(const uint32<N> &a) {
                    static_assert(s0 < 2 && s1 < 2, "Selector out of range");
                    return i_permute4<s0, s1, s0 + 2, s1 + 2>(a);
                }


                template <unsigned s0, unsigned s1, unsigned N> inline float32<N> i_permute2(const float32<N> &a) {
                    static_assert(s0 < 2 && s1 < 2, "Selector out of range");
                    return i_permute4<s0, s1, s0 + 2, s1 + 2>(a);
                }


                template <unsigned s0, unsigned s1> inline uint64x2 i_permute2(const uint64x2 &a) {
                    static_assert(s0 < 2 && s1 < 2, "Selector out of range");
#if SIMD_USE_SSE2 || SIMD_USE_MSA
                    return (uint64x2)i_permute4<s0 * 2, s0 * 2 + 1, s1 * 2, s1 * 2 + 1>(int32x4(a));
#elif SIMD_USE_NEON
                    return detail::neon_shuffle_int64x2::permute2<s0, s1>(a);
#elif SIMD_USE_VSX_207
                    return vec_xxpermdi(a.native(), a.native(), SIMD_VSX_SHUFFLE_MASK_2x2(s0, s1));
#elif SIMD_USE_NULL || SIMD_USE_ALTIVEC
                    return detail::null::permute<s0, s1>(a);
#endif
                }

#if SIMD_USE_AVX2
                template <unsigned s0, unsigned s1> inline uint64x4 i_permute2(const uint64x4 &a) {
                    static_assert(s0 < 2 && s1 < 2, "Selector out of range");
                    return i_permute4<s0, s1, s0 + 2, s1 + 2>(a);
                }
#endif

#if SIMD_USE_AVX512F
                template <unsigned s0, unsigned s1> inline uint64<8> i_permute2(const uint64<8> &a) {
                    static_assert(s0 < 2 && s1 < 2, "Selector out of range");
                    return i_permute4<s0, s1, s0 + 2, s1 + 2>(a);
                }
#endif

                template <unsigned s0, unsigned s1, unsigned N> inline uint64<N> i_permute2(const uint64<N> &a) {
                    static_assert(s0 < 2 && s1 < 2, "Selector out of range");
                    SIMD_VEC_ARRAY_IMPL1(uint64<N>, (i_permute2<s0, s1>), a);
                }

                // -----------------------------------------------------------------------------

                template <unsigned s0, unsigned s1> inline float64x2 i_permute2(const float64x2 &a) {
                    static_assert(s0 < 2 && s1 < 2, "Selector out of range");
#if SIMD_USE_SSE2
                    return _mm_shuffle_pd(a.native(), a.native(), SIMD_SHUFFLE_MASK_2x2(s0, s1));
#elif SIMD_USE_VSX_206
                    return vec_xxpermdi(a.native(), a.native(), SIMD_VSX_SHUFFLE_MASK_2x2(s0, s1));
#elif SIMD_USE_NEON64 || SIMD_USE_MSA
                    return float64x2(i_permute2<s0, s1>(int64x2(a)));
#elif SIMD_USE_NULL || SIMD_USE_NEON || SIMD_USE_ALTIVEC
                    return detail::null::permute<s0, s1>(a);
#endif
                }

#if SIMD_USE_AVX
                template <unsigned s0, unsigned s1> inline float64x4 i_permute2(const float64x4 &a) {
                    static_assert(s0 < 2 && s1 < 2, "Selector out of range");
#if SIMD_USE_AVX2
                    return _mm256_permute4x64_pd(a.native(), s0 | s1 << 2 | (s0 + 2) << 4 | (s1 + 2) << 6);
#else // SIMD_USE_AVX
                    return _mm256_permute_pd(a.native(), s0 | s1 << 1 | s0 << 2 | s1 << 3);
#endif
                }
#endif

#if SIMD_USE_AVX512F
                template <unsigned s0, unsigned s1> inline float64<8> i_permute2(const float64<8> &a) {
                    static_assert(s0 < 2 && s1 < 2, "Selector out of range");
                    return _mm512_permute_pd(a.native(),
                                             s0 | s1 << 1 | s0 << 2 | s1 << 3 | s0 << 4 | s1 << 5 | s0 << 6 | s1 << 7);
                }
#endif

                template <unsigned s0, unsigned s1, unsigned N> inline float64<N> i_permute2(const float64<N> &a) {
                    static_assert(s0 < 2 && s1 < 2, "Selector out of range");
                    SIMD_VEC_ARRAY_IMPL1(float64<N>, (i_permute2<s0, s1>), a);
                }

            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
