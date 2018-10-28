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

#ifndef SIMD_DETAIL_INSN_PERMUTE_BYTES16_H
#define SIMD_DETAIL_INSN_PERMUTE_BYTES16_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/not_implemented.h>
#include <bigmath/simd/detail/vector_array_macros.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {

                static inline uint8x16 i_permute_bytes16(const uint8x16 &a, const uint8x16 &mask) {
#if SIMD_USE_NULL
                    uint8x16 r;

                    for (unsigned i = 0; i < 16; i++) {
                        unsigned j = mask.el(i) & 0x0f;
                        r.el(i) = a.el(j);
                    }
                    return r;
#elif SIMD_USE_SSSE3
                    return _mm_shuffle_epi8(a.native(), mask.native());
#elif SIMD_USE_NEON32
                    uint8x8x2_t table = {{vget_low_u8(a.native()), vget_high_u8(a.native())}};
                    uint8x8_t lo = vtbl2_u8(table, vget_low_u8(mask.native()));
                    uint8x8_t hi = vtbl2_u8(table, vget_high_u8(mask.native()));
                    return vcombine_u8(lo, hi);
#elif SIMD_USE_NEON64
                    return vqtbl1q_u8(a.native(), mask.native());
#elif SIMD_USE_ALTIVEC
                    return vec_perm(a.native(), a.native(), mask.native());
#elif SIMD_USE_MSA
                    return (v16u8)__msa_vshf_b((v16i8)mask.native(), (v16i8)a.native(), (v16i8)a.native());
#else
                    return SIMD_NOT_IMPLEMENTED2(a, mask);
#endif
                }

#if SIMD_USE_AVX2
                static inline uint8x32 i_permute_bytes16(const uint8x32 &a, const uint8x32 &mask) {
                    return _mm256_shuffle_epi8(a.native(), mask.native());
                }
#endif

#if SIMD_USE_AVX512BW
                inline uint8<64> i_permute_bytes16(const uint8<64> &a, const uint8<64> &mask) {
                    return _mm512_shuffle_epi8(a.native(), mask.native());
                }
#endif

                template <unsigned N> inline uint8<N> i_permute_bytes16(const uint8<N> &a, const uint8<N> &mask) {
                    SIMD_VEC_ARRAY_IMPL2(uint8<N>, i_permute_bytes16, a, mask)
                }
                template <unsigned N> inline uint16<N> i_permute_bytes16(const uint16<N> &a, const uint16<N> &mask) {
                    return (uint16<N>)i_permute_bytes16(uint8<N * 2>(a), uint8<N * 2>(mask));
                }
                template <unsigned N> inline uint32<N> i_permute_bytes16(const uint32<N> &a, const uint32<N> &mask) {
                    return (uint32<N>)i_permute_bytes16(uint8<N * 4>(a), uint8<N * 4>(mask));
                }
                template <unsigned N> inline uint64<N> i_permute_bytes16(const uint64<N> &a, const uint64<N> &mask) {
                    return (uint64<N>)i_permute_bytes16(uint8<N * 8>(a), uint8<N * 8>(mask));
                }
                template <unsigned N> inline float32<N> i_permute_bytes16(const float32<N> &a, const uint32<N> &mask) {
                    return float32<N>(i_permute_bytes16(uint32<N>(a), mask));
                }
                template <unsigned N> inline float64<N> i_permute_bytes16(const float64<N> &a, const uint64<N> &mask) {
                    return float64<N>(i_permute_bytes16(uint64<N>(a), mask));
                }


            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
