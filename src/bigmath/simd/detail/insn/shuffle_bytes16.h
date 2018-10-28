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

#ifndef SIMD_DETAIL_INSN_SHUFFLE_BYTES16_H
#define SIMD_DETAIL_INSN_SHUFFLE_BYTES16_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/core/bit_or.h>
#include <bigmath/simd/core/blend.h>
#include <bigmath/simd/core/cmp_lt.h>
#include <bigmath/simd/core/i_add.h>
#include <bigmath/simd/detail/not_implemented.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {


                static inline uint8x16 i_shuffle_bytes16(const uint8x16 &a, const uint8x16 &b, const uint8x16 &mask) {
#if SIMD_USE_NULL
                    uint8x16 r;

                    for (unsigned i = 0; i < 16; i++) {
                        unsigned j = mask.el(i) & 0x0f;
                        bool which = mask.el(i) < 0x10;
                        r.el(i) = which ? a.el(j) : b.el(j);
                    }
                    return r;
#elif SIMD_USE_XOP
                    return _mm_perm_epi8(a.native(), b.native(), mask.native());
#elif SIMD_USE_AVX
                    // it's not advantageous to use _mm_blendv_epi8 on pre-AVX machines
                    // because it takes the same number of cycles as the alternative, but
                    // forces the result into xmm0 register.
                    int16x8 sel, ai, bi, r;
                    sel = _mm_slli_epi16(mask.native(), 3);

                    ai = _mm_shuffle_epi8(a.native(), mask.native());
                    bi = _mm_shuffle_epi8(b.native(), mask.native());
                    r = _mm_blendv_epi8(ai.native(), bi.native(), sel.native());
                    return (uint8<16>)r;
#elif SIMD_USE_SSSE3
#if (defined(__clang__) && (__clang_major__ == 3) && (__clang_minor__ <= 7) && (__clang_minor__ >= 6))
                    // Clang 3.7 and 3.6 incorrectly optimize certain cases of constant
                    // mask when the values are available for the compiler to collapse.
                    // Fortunately the overhead of the workaround is very small
                    uint8<16> ai, bi;
                    mask_int8<16> select_a = cmp_lt((int8<16>)mask, 0x10);
                    ai = _mm_shuffle_epi8(a.native(), mask.native());
                    bi = _mm_shuffle_epi8(b.native(), mask.native());
                    return blend(ai, bi, select_a);
#else
                    uint8x16 m1, m2, ai, bi;
                    // sets the 7-th bit if we want an element from the other vector
                    m1 = add(mask, 0x70);
                    m2 = add(mask, 0xf0);

                    ai = _mm_shuffle_epi8(a.native(), m1.native());
                    bi = _mm_shuffle_epi8(b.native(), m2.native());
                    return bit_or(ai, bi);
#endif
#elif SIMD_USE_NEON32
                    uint8x8x4_t table = {{vget_low_u8(a.native()),
                                          vget_high_u8(a.native()),
                                          vget_low_u8(b.native()),
                                          vget_high_u8(b.native())}};
                    uint8x8_t lo = vtbl4_u8(table, vget_low_u8(mask.native()));
                    uint8x8_t hi = vtbl4_u8(table, vget_high_u8(mask.native()));
                    return vcombine_u8(lo, hi);
#elif SIMD_USE_NEON64
                    uint8x16x2_t table;
                    table.val[0] = a.native();
                    table.val[1] = b.native();
                    return vqtbl2q_u8(table, mask.native());
#elif SIMD_USE_ALTIVEC
                    return vec_perm(a.native(), b.native(), mask.native());
#elif SIMD_USE_MSA
                    return (v16u8)__msa_vshf_b((v16i8)mask.native(), (v16i8)b.native(), (v16i8)a.native());
#else
                    return SIMD_NOT_IMPLEMENTED3(a, b, mask);
#endif
                }

#if SIMD_USE_AVX2
                static inline uint8x32 i_shuffle_bytes16(const uint8x32 &a, const uint8x32 &b, const uint8x32 &mask) {
                    int16x16 sel, ai, bi, r;
                    sel = mask;
                    sel = _mm256_slli_epi16(sel.native(), 3); // the top 3 bits are already clear

                    ai = _mm256_shuffle_epi8(a.native(), mask.native());
                    bi = _mm256_shuffle_epi8(b.native(), mask.native());
                    r = _mm256_blendv_epi8(ai.native(), bi.native(), sel.native());
                    return (uint8<32>)r;
                }
#endif

#if SIMD_USE_AVX512BW
                inline uint8<64> i_shuffle_bytes16(const uint8<64> &a, const uint8<64> &b, const uint8<64> &mask) {
                    uint8<64> sel_mask, ai, bi, r;
                    sel_mask = make_uint(0x10);
                    __mmask64 sel = _mm512_test_epi8_mask(mask.native(), sel_mask.native());

                    ai = _mm512_shuffle_epi8(a.native(), mask.native());
                    bi = _mm512_shuffle_epi8(b.native(), mask.native());
                    r = _mm512_mask_blend_epi8(sel, ai.native(), bi.native());
                    return r;
                }
#endif

                template <unsigned N>
                inline uint8<N> i_shuffle_bytes16(const uint8<N> &a, const uint8<N> &b, const uint8<N> &mask) {
                    SIMD_VEC_ARRAY_IMPL3(uint8<N>, i_shuffle_bytes16, a, b, mask);
                }

                template <unsigned N>
                inline uint16<N> i_shuffle_bytes16(const uint16<N> &a, const uint16<N> &b, const uint16<N> &mask) {
                    return (uint16<N>)i_shuffle_bytes16(uint8<N * 2>(a), uint8<N * 2>(b), uint8<N * 2>(mask));
                }
                template <unsigned N>
                inline uint32<N> i_shuffle_bytes16(const uint32<N> &a, const uint32<N> &b, const uint32<N> &mask) {
                    return (uint32<N>)i_shuffle_bytes16(uint8<N * 4>(a), uint8<N * 4>(b), uint8<N * 4>(mask));
                }
                template <unsigned N>
                inline uint64<N> i_shuffle_bytes16(const uint64<N> &a, const uint64<N> &b, const uint64<N> &mask) {
                    return (uint64<N>)i_shuffle_bytes16(uint8<N * 8>(a), uint8<N * 8>(b), uint8<N * 8>(mask));
                }
                template <unsigned N>
                inline float32<N> i_shuffle_bytes16(const float32<N> &a, const float32<N> &b, const uint32<N> &mask) {
                    return float32<N>(i_shuffle_bytes16(uint32<N>(a), uint32<N>(b), mask));
                }
                template <unsigned N>
                inline float64<N> i_shuffle_bytes16(const float64<N> &a, const float64<N> &b, const uint64<N> &mask) {
                    return float64<N>(i_shuffle_bytes16(uint64<N>(a), uint64<N>(b), mask));
                }


            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
