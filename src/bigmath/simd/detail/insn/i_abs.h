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

#ifndef SIMD_DETAIL_INSN_I_ABS_H
#define SIMD_DETAIL_INSN_I_ABS_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/core/bit_xor.h>
#include <bigmath/simd/core/cmp_lt.h>
#include <bigmath/simd/core/cmp_neq.h>
#include <bigmath/simd/core/i_shift_r.h>
#include <bigmath/simd/core/i_sub.h>
#include <bigmath/simd/core/move_r.h>
#include <bigmath/simd/detail/null/math.h>
#include <bigmath/simd/detail/vector_array_macros.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {

                static inline uint8<16> i_iabs(const int8<16> &a) {
#if SIMD_USE_NULL
                    return detail::null::abs(a);
#elif SIMD_USE_SSSE3
                    return _mm_abs_epi8(a.native());
#elif SIMD_USE_SSE2
                    int8<16> t, r;
                    t = cmp_lt(a, 0);
                    r = bit_xor(a, t);
                    r = sub(r, t);
                    return r;
#elif SIMD_USE_NEON
                    return int8x16(vabsq_s8(a.native()));
#elif SIMD_USE_ALTIVEC
                    // expands to 3 instructions
                    return (__vector uint8_t)vec_abs(a.native());
#elif SIMD_USE_MSA
                    int8<16> zero = make_zero();
                    return (v16u8)__msa_add_a_b(a.native(), zero.native());
#endif
                }

#if SIMD_USE_AVX2
                static inline uint8<32> i_iabs(const int8<32> &a) {
                    return _mm256_abs_epi8(a.native());
                }
#endif

#if SIMD_USE_AVX512BW
                static inline uint8<64> i_iabs(const int8<64> &a) {
                    return _mm512_abs_epi8(a.native());
                }
#endif

                // -----------------------------------------------------------------------------

                static inline uint16<8> i_iabs(const int16<8> &a) {
#if SIMD_USE_NULL
                    return detail::null::abs(a);
#elif SIMD_USE_SSSE3
                    return _mm_abs_epi16(a.native());
#elif SIMD_USE_SSE2
                    int16<8> t, r;
                    t = cmp_lt(a, 0);
                    r = bit_xor(a, t);
                    r = sub(r, t);
                    return r;
#elif SIMD_USE_NEON
                    return int16x8(vabsq_s16(a.native()));
#elif SIMD_USE_ALTIVEC
                    // expands to 3 instructions
                    return (__vector uint16_t)vec_abs(a.native());
#elif SIMD_USE_MSA
                    int16<8> zero = make_zero();
                    return (v8u16)__msa_add_a_h(a.native(), zero.native());
#endif
                }

#if SIMD_USE_AVX2
                static inline uint16<16> i_iabs(const int16<16> &a) {
                    return _mm256_abs_epi16(a.native());
                }
#endif

#if SIMD_USE_AVX512BW
                static inline uint16<32> i_iabs(const int16<32> &a) {
                    return _mm512_abs_epi16(a.native());
                }
#endif

                // -----------------------------------------------------------------------------

                static inline uint32<4> i_iabs(const int32<4> &a) {
#if SIMD_USE_NULL
                    return detail::null::abs(a);
#elif SIMD_USE_SSSE3
                    return _mm_abs_epi32(a.native());
#elif SIMD_USE_SSE2
                    int32<4> t, r;
                    t = cmp_lt(a, 0);
                    r = bit_xor(a, t);
                    r = sub(r, t);
                    return r;
#elif SIMD_USE_NEON
                    return int32x4(vabsq_s32(a.native()));
#elif SIMD_USE_ALTIVEC
                    // expands to 3 instructions
                    return (__vector uint32_t)vec_abs(a.native());
#elif SIMD_USE_MSA
                    int32<4> zero = make_zero();
                    return (v4u32)__msa_add_a_w(a.native(), zero.native());
#endif
                }

#if SIMD_USE_AVX2
                static inline uint32<8> i_iabs(const int32<8> &a) {
                    return _mm256_abs_epi32(a.native());
                }
#endif

#if SIMD_USE_AVX512F
                static inline uint32<16> i_iabs(const int32<16> &a) {
                    return _mm512_abs_epi32(a.native());
                }
#endif

                // -----------------------------------------------------------------------------

                static inline uint64<2> i_iabs(const int64<2> &a) {
#if SIMD_USE_AVX512VL
                    return _mm_abs_epi64(a.native());
#elif SIMD_USE_SSE2
                    uint32x4 ta;
                    int64x2 t, r;
                    ta = (uint32x4)bit_and(a, 0x8000000000000000);
                    ta = shift_r<1>(ta);
                    t = cmp_neq(float64x2(ta), 0);
                    r = bit_xor(a, t);
                    r = sub(r, t);
                    return r;
#elif SIMD_USE_NEON
                    int32x4 z;
                    int64<2> r;
                    z = shift_r<63>(uint64x2(a));
                    z = cmp_eq(z, 0);
                    z = permute4<0, 0, 2, 2>(z);
                    z = bit_not(z);
                    int64x2 t;
                    t = z;
                    r = bit_xor(a, t);
                    r = sub(r, t);
                    return r;
#elif SIMD_USE_VSX_207
                    // expands to 3 instructions
                    return (__vector uint64_t)vec_abs(a.native());
#elif SIMD_USE_MSA
                    int64<2> zero = make_zero();
                    return (v2u64)__msa_add_a_d(a.native(), zero.native());
#elif SIMD_USE_NULL || SIMD_USE_ALTIVEC
                    return detail::null::abs(a);
#endif
                }

#if SIMD_USE_AVX2
                static inline uint64<4> i_iabs(const int64<4> &a) {
#if SIMD_USE_AVX512VL
                    return _mm256_abs_epi64(a.native());
#else
                    int64x4 t, r;
                    int64x4 zero = make_zero();
                    t = _mm256_cmpgt_epi64(zero.native(), a.native());
                    r = bit_xor(a, t);
                    r = sub(r, t);
                    return r;
#endif
                }
#endif

#if SIMD_USE_AVX512F
                static inline uint64<8> i_iabs(const int64<8> &a) {
                    return _mm512_abs_epi64(a.native());
                }
#endif

                // -----------------------------------------------------------------------------

                template <class V> inline V i_iabs(const V &a) {
                    SIMD_VEC_ARRAY_IMPL1(V, i_iabs, a)
                }

            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
