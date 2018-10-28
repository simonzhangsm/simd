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

#ifndef SIMD_DETAIL_INSN_I_POPCNT_H
#define SIMD_DETAIL_INSN_I_POPCNT_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/core/bit_and.h>
#include <bigmath/simd/core/extract.h>
#include <bigmath/simd/core/i_add.h>
#include <bigmath/simd/core/i_shift_r.h>
#include <bigmath/simd/core/i_sub.h>
#include <bigmath/simd/core/i_mul.h>
#include <bigmath/simd/core/insert.h>
#include <bigmath/simd/detail/null/bitwise.h>
#include <bigmath/simd/detail/width.h>
#include <bigmath/simd/detail/vector_array_macros.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {

                template <class V> inline V v_emul_popcnt_u8(const V &a) {
                    // We're using 16-bit ops because on SSE/AVX no 8-bit shift is available
                    // There's no difference on other architectures
                    using w_b16 = typename same_width<V>::u16;

                    w_b16 p = (w_b16)a;
                    w_b16 m55 = splat(0x5555);
                    w_b16 m33 = splat(0x3333);
                    w_b16 m0f = splat(0x0f0f);

                    p = sub(p, bit_and(shift_r<1>(p), m55));
                    p = add(bit_and(p, m33), bit_and(shift_r<2>(p), m33));
                    p = bit_and(add(p, shift_r<4>(p)), m0f);
                    return (V)p;
                }

                static inline uint8<16> i_popcnt(const uint8<16> &a) {
#if SIMD_USE_NULL
                    uint8<16> r;
                    for (unsigned i = 0; i < a.length; i++) {
                        r.el(i) = detail::null::el_popcnt8(a.el(i));
                    }
                    return r;
#elif SIMD_USE_NEON
                    return vcntq_u8(a.native());
#elif SIMD_USE_VSX_207
                    return vec_vpopcnt(a.native());
#elif SIMD_USE_MSA
                    return (v16u8)__msa_pcnt_b((v16i8)a.native());
#else
                    return v_emul_popcnt_u8(a);
#endif
                }

#if SIMD_USE_AVX2
                static inline uint8<32> i_popcnt(const uint8<32> &a) {
                    return v_emul_popcnt_u8(a);
                }
#endif

#if SIMD_USE_AVX512BW
                static inline uint8<64> i_popcnt(const uint8<64> &a) {
                    return v_emul_popcnt_u8(a);
                }
#endif

                // -----------------------------------------------------------------------------

                template <class V> inline V v_emul_popcnt_u16(const V &a) {
                    V p = a;
                    V m55 = splat(0x5555);
                    V m33 = splat(0x3333);
                    V m0f = splat(0x0f0f);
                    V res_mask = splat(0x00ff);


                    p = sub(p, bit_and(shift_r<1>(p), m55));
                    p = add(bit_and(p, m33), bit_and(shift_r<2>(p), m33));
                    p = bit_and(add(p, shift_r<4>(p)), m0f);
                    p = add(p, shift_r<8>(p));
                    p = bit_and(p, res_mask);
                    return p;
                }

                static inline uint16<8> i_popcnt(const uint16<8> &a) {
#if SIMD_USE_NULL
                    uint16<8> r;
                    for (unsigned i = 0; i < a.length; i++) {
                        r.el(i) = detail::null::el_popcnt16(a.el(i));
                    }
                    return r;
#elif SIMD_USE_NEON
                    uint8x16_t p8 = vcntq_u8(vreinterpretq_u8_u16(a.native()));
                    return vpaddlq_u8(p8);
#elif SIMD_USE_VSX_207
                    return vec_vpopcnt(a.native());
#elif SIMD_USE_MSA
                    return (v8u16)__msa_pcnt_h((v8i16)a.native());
#else
                    return v_emul_popcnt_u16(a);
#endif
                }

#if SIMD_USE_AVX2
                static inline uint16<16> i_popcnt(const uint16<16> &a) {
                    return v_emul_popcnt_u16(a);
                }
#endif

#if SIMD_USE_AVX512BW
                static inline uint16<32> i_popcnt(const uint16<32> &a) {
                    return v_emul_popcnt_u16(a);
                }
#endif

                // -----------------------------------------------------------------------------

                template <class V> inline V v_emul_popcnt_u32(const V &a) {
                    V p = a;
                    V m55 = splat(0x55555555);
                    V m33 = splat(0x33333333);
                    V m0f = splat(0x0f0f0f0f);

                    p = sub(p, bit_and(shift_r<1>(p), m55));
                    p = add(bit_and(p, m33), bit_and(shift_r<2>(p), m33));
                    p = bit_and(add(p, shift_r<4>(p)), m0f);
#if SIMD_USE_SSE4_1 || SIMD_USE_NEON || SIMD_USE_MSA
                    V m01 = splat(0x01010101);
                    // rather than doing 2 adds + 2 shifts we can do 1 mul + 1 shift
                    p = shift_r<24>(mul_lo(p, m01));
#else
                    V res_mask = splat(0x000000ff);
                    p = add(p, shift_r<8>(p));
                    p = add(p, shift_r<16>(p));
                    p = bit_and(p, res_mask);
#endif
                    return p;
                }

                static inline uint32<4> i_popcnt(const uint32<4> &a) {
#if SIMD_USE_NULL
                    uint32<4> r;
                    for (unsigned i = 0; i < a.length; i++) {
                        r.el(i) = detail::null::el_popcnt32(a.el(i));
                    }
                    return r;
#elif SIMD_USE_X86_POPCNT_INSN
                    // slightly faster than the vectorized version
                    unsigned a0 = _mm_popcnt_u32(extract<0>(a));
                    unsigned a1 = _mm_popcnt_u32(extract<1>(a));
                    unsigned a2 = _mm_popcnt_u32(extract<2>(a));
                    unsigned a3 = _mm_popcnt_u32(extract<3>(a));
                    uint16<8> r = _mm_cvtsi32_si128(a0);
                    r = insert<2>(r, a1);
                    r = insert<4>(r, a2);
                    r = insert<6>(r, a3);
                    return (uint32<4>)r;
#elif SIMD_USE_NEON
                    uint8x16_t p8 = vcntq_u8(vreinterpretq_u8_u32(a.native()));
                    uint16x8_t p16 = vpaddlq_u8(p8);
                    return vpaddlq_u16(p16);
#elif SIMD_USE_VSX_207
                    return vec_vpopcnt(a.native());
#elif SIMD_USE_MSA
                    return (v4u32)__msa_pcnt_w((v4i32)a.native());
#else
                    return v_emul_popcnt_u32(a);
#endif
                }

#if SIMD_USE_AVX2
                static inline uint32<8> i_popcnt(const uint32<8> &a) {
                    return v_emul_popcnt_u32(a);
                }
#endif

#if SIMD_USE_AVX512F
                static inline uint32<16> i_popcnt(const uint32<16> &a) {
                    // TODO: support AVX512VPOPCNTDQ
                    return v_emul_popcnt_u32(a);
                }
#endif

                // -----------------------------------------------------------------------------

                template <class V> inline V v_emul_popcnt_u64(const V &a) {
                    V p = a;
                    V m55 = splat(0x5555555555555555);
                    V m33 = splat(0x3333333333333333);
                    V m0f = splat(0x0f0f0f0f0f0f0f0f);
                    V res_mask = splat(0x00000000000000ff);


                    p = sub(p, bit_and(shift_r<1>(p), m55));
                    p = add(bit_and(p, m33), bit_and(shift_r<2>(p), m33));
                    p = bit_and(add(p, shift_r<4>(p)), m0f);
                    p = add(p, shift_r<8>(p));
                    p = add(p, shift_r<16>(p));
                    p = add(p, shift_r<32>(p));
                    p = bit_and(p, res_mask);
                    return p;
                }

                static inline uint64<2> i_popcnt(const uint64<2> &a) {
#if SIMD_USE_NULL
                    uint64<2> r;
                    for (unsigned i = 0; i < a.length; i++) {
                        r.el(i) = detail::null::el_popcnt64(a.el(i));
                    }
                    return r;
#elif SIMD_USE_X86_POPCNT_INSN
                    unsigned a0, a1;
#if SIMD_64_BITS
                    a0 = _mm_popcnt_u64(extract<0>(a));
                    a1 = _mm_popcnt_u64(extract<1>(a));
#else
                    uint32<4> a32;
                    a32 = a;
                    a0 = _mm_popcnt_u32(extract<0>(a32));
                    a0 += _mm_popcnt_u32(extract<1>(a32));
                    a1 = _mm_popcnt_u32(extract<2>(a32));
                    a1 += _mm_popcnt_u32(extract<3>(a32));
#endif
                    uint16<8> r = _mm_cvtsi32_si128(a0);
                    r = insert<4>(r, a1);
                    return (uint64<2>)r;
#elif SIMD_USE_SSE2
                    uint8<16> p8 = v_emul_popcnt_u8((uint8<16>)a);
                    return _mm_sad_epu8(p8.native(), _mm_setzero_si128());
#elif SIMD_USE_NEON
                    uint8x16_t p8 = vcntq_u8(vreinterpretq_u8_u64(a.native()));
                    uint16x8_t p16 = vpaddlq_u8(p8);
                    uint32x4_t p32 = vpaddlq_u16(p16);
                    return vpaddlq_u32(p32);
#elif SIMD_USE_VSX_207
                    return vec_vpopcnt(a.native());
#elif SIMD_USE_MSA
                    return (v2u64)__msa_pcnt_d((v2i64)a.native());
#else
                    return v_emul_popcnt_u64(a);
#endif
                }

#if SIMD_USE_AVX2
                static inline uint64<4> i_popcnt(const uint64<4> &a) {
#if SIMD_USE_X86_POPCNT_INSN && SIMD_64_BITS
                    uint64<2> a0, a1;
                    split(a, a0, a1);
                    a0 = i_popcnt(a0);
                    a1 = i_popcnt(a1);
                    return combine(a0, a1);
#else
                    uint8<32> p8 = v_emul_popcnt_u8((uint8<32>)a);
                    return _mm256_sad_epu8(p8.native(), _mm256_setzero_si256());
#endif
                }
#endif

#if SIMD_USE_AVX512F
                static inline uint64<8> i_popcnt(const uint64<8> &a) {
                    // TODO: support AVX512VPOPCNTDQ
#if SIMD_USE_AVX512BW
                    uint8<64> p8 = v_emul_popcnt_u8((uint8<64>)a);
                    return _mm512_sad_epu8(p8.native(), _mm512_setzero_si512());
#else
                    return v_emul_popcnt_u64(a);
#endif
                }
#endif

                // -----------------------------------------------------------------------------

                template <class V> inline V i_popcnt(const V &a) {
                    SIMD_VEC_ARRAY_IMPL1(V, i_popcnt, a)
                }


            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
