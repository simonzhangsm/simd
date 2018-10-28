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

#ifndef SIMD_DETAIL_INSN_I_SUB_SAT_H
#define SIMD_DETAIL_INSN_I_SUB_SAT_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/null/math.h>
#include <bigmath/simd/detail/vector_array_macros.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {

                static inline int8<16> i_sub_sat(const int8<16> &a, const int8<16> &b) {
#if SIMD_USE_NULL
                    return detail::null::sub_sat(a, b);
#elif SIMD_USE_SSE2
                    return _mm_subs_epi8(a.native(), b.native());
#elif SIMD_USE_NEON
                    return vqsubq_s8(a.native(), b.native());
#elif SIMD_USE_ALTIVEC
                    return vec_subs(a.native(), b.native());
#elif SIMD_USE_MSA
                    return __msa_subs_s_b(a.native(), b.native());
#endif
                }

#if SIMD_USE_AVX2
                static inline int8<32> i_sub_sat(const int8<32> &a, const int8<32> &b) {
                    return _mm256_subs_epi8(a.native(), b.native());
                }
#endif

#if SIMD_USE_AVX512BW
                static inline int8<64> i_sub_sat(const int8<64> &a, const int8<64> &b) {
                    return _mm512_subs_epi8(a.native(), b.native());
                }
#endif

                // -----------------------------------------------------------------------------

                static inline int16<8> i_sub_sat(const int16<8> &a, const int16<8> &b) {
#if SIMD_USE_NULL
                    return detail::null::sub_sat(a, b);
#elif SIMD_USE_SSE2
                    return _mm_subs_epi16(a.native(), b.native());
#elif SIMD_USE_NEON
                    return vqsubq_s16(a.native(), b.native());
#elif SIMD_USE_ALTIVEC
                    return vec_subs(a.native(), b.native());
#elif SIMD_USE_MSA
                    return __msa_subs_s_h(a.native(), b.native());
#endif
                }

#if SIMD_USE_AVX2
                static inline int16<16> i_sub_sat(const int16<16> &a, const int16<16> &b) {
                    return _mm256_subs_epi16(a.native(), b.native());
                }
#endif

#if SIMD_USE_AVX512BW
                static inline int16<32> i_sub_sat(const int16<32> &a, const int16<32> &b) {
                    return _mm512_subs_epi16(a.native(), b.native());
                }
#endif

                // -----------------------------------------------------------------------------

                static inline uint8<16> i_sub_sat(const uint8<16> &a, const uint8<16> &b) {
#if SIMD_USE_NULL
                    return detail::null::sub_sat(a, b);
#elif SIMD_USE_SSE2
                    return _mm_subs_epu8(a.native(), b.native());
#elif SIMD_USE_NEON
                    return vqsubq_u8(a.native(), b.native());
#elif SIMD_USE_ALTIVEC
                    return vec_subs(a.native(), b.native());
#elif SIMD_USE_MSA
                    return __msa_subs_u_b(a.native(), b.native());
#endif
                }

#if SIMD_USE_AVX2
                static inline uint8<32> i_sub_sat(const uint8<32> &a, const uint8<32> &b) {
                    return _mm256_subs_epu8(a.native(), b.native());
                }
#endif

#if SIMD_USE_AVX512BW
                static inline uint8<64> i_sub_sat(const uint8<64> &a, const uint8<64> &b) {
                    return _mm512_subs_epu8(a.native(), b.native());
                }
#endif

                // -----------------------------------------------------------------------------

                static inline uint16<8> i_sub_sat(const uint16<8> &a, const uint16<8> &b) {
#if SIMD_USE_NULL
                    return detail::null::sub_sat(a, b);
#elif SIMD_USE_SSE2
                    return _mm_subs_epu16(a.native(), b.native());
#elif SIMD_USE_NEON
                    return vqsubq_u16(a.native(), b.native());
#elif SIMD_USE_ALTIVEC
                    return vec_subs(a.native(), b.native());
#elif SIMD_USE_MSA
                    return __msa_subs_u_h(a.native(), b.native());
#endif
                }

#if SIMD_USE_AVX2
                static inline uint16<16> i_sub_sat(const uint16<16> &a, const uint16<16> &b) {
                    return _mm256_subs_epu16(a.native(), b.native());
                }
#endif

#if SIMD_USE_AVX512BW
                static inline uint16<32> i_sub_sat(const uint16<32> &a, const uint16<32> &b) {
                    return _mm512_subs_epu16(a.native(), b.native());
                }
#endif

                // -----------------------------------------------------------------------------

                template <class V> inline V i_sub_sat(const V &a, const V &b) {
                    SIMD_VEC_ARRAY_IMPL2(V, i_sub_sat, a, b)
                }

            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
