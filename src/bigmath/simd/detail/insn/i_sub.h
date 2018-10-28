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

#ifndef SIMD_DETAIL_INSN_I_SUB_H
#define SIMD_DETAIL_INSN_I_SUB_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/null/math.h>
#include <bigmath/simd/core/move_l.h>
#include <bigmath/simd/detail/vector_array_macros.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {

                static inline uint8<16> i_isub(const uint8<16> &a, const uint8<16> &b) {
#if SIMD_USE_NULL
                    return detail::null::sub(a, b);
#elif SIMD_USE_SSE2
                    return _mm_sub_epi8(a.native(), b.native());
#elif SIMD_USE_NEON
                    return vsubq_u8(a.native(), b.native());
#elif SIMD_USE_ALTIVEC
                    return vec_sub(a.native(), b.native());
#elif SIMD_USE_MSA
                    return (v16u8)__msa_subv_b((v16i8)a.native(), (v16i8)b.native());
#endif
                }

#if SIMD_USE_AVX2
                static inline uint8<32> i_isub(const uint8<32> &a, const uint8<32> &b) {
                    return _mm256_sub_epi8(a.native(), b.native());
                }
#endif

#if SIMD_USE_AVX512BW
                static inline uint8<64> i_isub(const uint8<64> &a, const uint8<64> &b) {
                    return _mm512_sub_epi8(a.native(), b.native());
                }
#endif

                // -----------------------------------------------------------------------------

                static inline uint16<8> i_isub(const uint16<8> &a, const uint16<8> &b) {
#if SIMD_USE_NULL
                    return detail::null::sub(a, b);
#elif SIMD_USE_SSE2
                    return _mm_sub_epi16(a.native(), b.native());
#elif SIMD_USE_NEON
                    return vsubq_u16(a.native(), b.native());
#elif SIMD_USE_ALTIVEC
                    return vec_sub(a.native(), b.native());
#elif SIMD_USE_MSA
                    return (v8u16)__msa_subv_h((v8i16)a.native(), (v8i16)b.native());
#endif
                }

#if SIMD_USE_AVX2
                static inline uint16<16> i_isub(const uint16<16> &a, const uint16<16> &b) {
                    return _mm256_sub_epi16(a.native(), b.native());
                }
#endif

#if SIMD_USE_AVX512BW
                static inline uint16<32> i_isub(const uint16<32> &a, const uint16<32> &b) {
                    return _mm512_sub_epi16(a.native(), b.native());
                }
#endif

                // -----------------------------------------------------------------------------

                static inline uint32<4> i_isub(const uint32<4> &a, const uint32<4> &b) {
#if SIMD_USE_NULL
                    return detail::null::sub(a, b);
#elif SIMD_USE_SSE2
                    return _mm_sub_epi32(a.native(), b.native());
#elif SIMD_USE_NEON
                    return vsubq_u32(a.native(), b.native());
#elif SIMD_USE_ALTIVEC
                    return vec_sub(a.native(), b.native());
#elif SIMD_USE_MSA
                    return (v4u32)__msa_subv_w((v4i32)a.native(), (v4i32)b.native());
#endif
                }

#if SIMD_USE_AVX2
                static inline uint32<8> i_isub(const uint32<8> &a, const uint32<8> &b) {
                    return _mm256_sub_epi32(a.native(), b.native());
                }
#endif

#if SIMD_USE_AVX512F
                static inline uint32<16> i_isub(const uint32<16> &a, const uint32<16> &b) {
                    return _mm512_sub_epi32(a.native(), b.native());
                }
#endif

                // -----------------------------------------------------------------------------

                static inline uint64<2> i_isub(const uint64<2> &a, const uint64<2> &b) {
#if SIMD_USE_SSE2
                    return _mm_sub_epi64(a.native(), b.native());
#elif SIMD_USE_NEON
                    return vsubq_u64(a.native(), b.native());
#elif SIMD_USE_VSX_207
                    return vec_sub(a.native(), b.native());
#elif SIMD_USE_MSA
                    return (v2u64)__msa_subv_d((v2i64)a.native(), (v2i64)b.native());
#elif SIMD_USE_NULL || SIMD_USE_ALTIVEC
                    return detail::null::sub(a, b);
#endif
                }

#if SIMD_USE_AVX2
                static inline uint64<4> i_isub(const uint64<4> &a, const uint64<4> &b) {
                    return _mm256_sub_epi64(a.native(), b.native());
                }
#endif

#if SIMD_USE_AVX512F
                static inline uint64<8> i_isub(const uint64<8> &a, const uint64<8> &b) {
                    return _mm512_sub_epi64(a.native(), b.native());
                }
#endif

                // -----------------------------------------------------------------------------

                template <class V> inline V i_isub(const V &a, const V &b) {
                    SIMD_VEC_ARRAY_IMPL2(V, i_isub, a, b)
                }

            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
