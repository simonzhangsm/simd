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

#ifndef SIMD_DETAIL_INSN_TEST_BITS_H
#define SIMD_DETAIL_INSN_TEST_BITS_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/expr.h>
#include <bigmath/simd/core/bit_and.h>
#include <bigmath/simd/core/extract.h>
#include <bigmath/simd/core/move_l.h>
#include <bigmath/simd/detail/insn/test_bits.h>
#include <bigmath/simd/detail/null/bitwise.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {

                static inline bool i_test_bits_any(const uint32<4> &a) {
#if SIMD_USE_NULL
                    return null::test_bits_any(a);
#elif SIMD_USE_SSE4_1
                    return !_mm_testz_si128(a.native(), a.native());
#elif SIMD_USE_SSE2
                    uint32<4> r = _mm_cmpeq_epi32(a.native(), _mm_setzero_si128());
                    return _mm_movemask_epi8(r.native()) != 0xffff;
#elif SIMD_USE_NEON
#if SIMD_64_BITS
                    uint64<2> r;
                    r = a;
                    r = bit_or(r, move2_l<1>(r));
                    return extract<0>(r) != 0;
#else
                    uint32x4 r = bit_or(a, move4_l<2>(a));
                    r = bit_or(r, move4_l<1>(r));
                    return extract<0>(r) != 0;
#endif
#elif SIMD_USE_ALTIVEC
                    uint32<4> z = make_uint(0);
                    return vec_any_gt(a.native(), z.native());
#elif SIMD_USE_MSA
                    return __msa_test_bnz_v((v16u8)a.native());
#endif
                }

                static inline bool i_test_bits_any(const uint16<8> &a) {
                    return i_test_bits_any(uint32<4>(a));
                }
                static inline bool i_test_bits_any(const uint8<16> &a) {
                    return i_test_bits_any(uint32<4>(a));
                }

                static inline bool i_test_bits_any(const uint64<2> &a) {
#if SIMD_USE_VSX_207
                    uint64<2> z = make_zero();
                    return vec_any_gt(a.native(), z.native());
#elif SIMD_USE_NULL || SIMD_USE_ALTIVEC
                    return null::test_bits_any(a);
#else
                    return i_test_bits_any(uint32<4>(a));
#endif
                }

                static inline bool i_test_bits_any(const float32<4> &a) {
#if SIMD_USE_NULL || SIMD_USE_NEON_NO_FLT_SP
                    return null::test_bits_any(a);
#else
                    return i_test_bits_any(uint32<4>(a));
#endif
                }

                static inline bool i_test_bits_any(const float64<2> &a) {
#if SIMD_USE_VSX_206
                    return i_test_bits_any(uint32<4>(a));
#elif SIMD_USE_NULL || SIMD_USE_NEON32 || SIMD_USE_ALTIVEC
                    return null::test_bits_any(a);
#else
                    return i_test_bits_any(uint32<4>(a));
#endif
                }

#if SIMD_USE_AVX
                static inline bool i_test_bits_any(const float32<8> &a) {
                    return !_mm256_testz_si256(_mm256_castps_si256(a.native()), _mm256_castps_si256(a.native()));
                }
                static inline bool i_test_bits_any(const float64<4> &a) {
                    return !_mm256_testz_si256(_mm256_castpd_si256(a.native()), _mm256_castpd_si256(a.native()));
                }
#endif

#if SIMD_USE_AVX2
                static inline bool i_test_bits_any(const uint8<32> &a) {
                    return !_mm256_testz_si256(a.native(), a.native());
                }
                static inline bool i_test_bits_any(const uint16<16> &a) {
                    return !_mm256_testz_si256(a.native(), a.native());
                }
                static inline bool i_test_bits_any(const uint32<8> &a) {
                    return !_mm256_testz_si256(a.native(), a.native());
                }
                static inline bool i_test_bits_any(const uint64<4> &a) {
                    return !_mm256_testz_si256(a.native(), a.native());
                }
#endif

#if SIMD_USE_AVX512F
                static inline bool i_test_bits_any(const uint32<16> &a) {
                    return _mm512_test_epi64_mask(a.native(), a.native()) != 0;
                }
                static inline bool i_test_bits_any(const uint64<8> &a) {
                    return i_test_bits_any(uint32<16>(a));
                }
                static inline bool i_test_bits_any(const float32<16> &a) {
                    return i_test_bits_any(uint32<16>(a));
                }
                static inline bool i_test_bits_any(const float64<8> &a) {
                    return i_test_bits_any(uint32<16>(a));
                }
#endif

#if SIMD_USE_AVX512BW
                inline bool i_test_bits_any(const uint8<64> &a) {
                    return i_test_bits_any(uint32<16>(a));
                }
                inline bool i_test_bits_any(const uint16<32> &a) {
                    return i_test_bits_any(uint32<16>(a));
                }
#endif

                template <unsigned N, class V> inline bool i_test_bits_any(const any_vec<N, V> &a) {
                    const V &wa = a.wrapped();
                    typename V::base_vector_type r = wa.vec(0);
                    for (unsigned i = 1; i < wa.vec_length; ++i)
                        r = bit_or(r, wa.vec(i));
                    return i_test_bits_any(r);
                }

            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
