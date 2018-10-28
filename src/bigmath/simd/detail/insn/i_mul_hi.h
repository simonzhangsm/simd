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

#ifndef SIMD_DETAIL_INSN_I_MUL_HI_H
#define SIMD_DETAIL_INSN_I_MUL_HI_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/core/i_mull.h>
#include <bigmath/simd/core/unzip_hi.h>
#include <bigmath/simd/detail/null/math.h>
#include <bigmath/simd/detail/vector_array_macros.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {

                static inline int16<8> i_mul_hi(const int16<8> &a, const int16<8> &b) {
#if SIMD_USE_NULL
                    uint16<8> r;
                    for (unsigned i = 0; i < a.length; i++) {
                        r.el(i) = (int32_t(a.el(i)) * b.el(i)) >> 16;
                    }
                    return r;
#elif SIMD_USE_SSE2
                    return _mm_mulhi_epi16(a.native(), b.native());
#elif SIMD_USE_NEON
                    int32x4 lo = vmull_s16(vget_low_s16(a.native()), vget_low_s16(b.native()));
                    int32x4 hi = vmull_s16(vget_high_s16(a.native()), vget_high_s16(b.native()));
                    return unzip8_hi(int16x8(lo), int16x8(hi));
#elif SIMD_USE_ALTIVEC || SIMD_USE_MSA
#if SIMD_BIG_ENDIAN
                    int16<16> ab;
                    ab = mull(a, b);
                    return unzip8_lo(ab.vec(0), ab.vec(1));
#else
                    int16<16> ab;
                    ab = mull(a, b);
                    return unzip8_hi(ab.vec(0), ab.vec(1));
#endif
#endif
                }

#if SIMD_USE_AVX2
                static inline int16<16> i_mul_hi(const int16<16> &a, const int16<16> &b) {
                    return _mm256_mulhi_epi16(a.native(), b.native());
                }
#endif

#if SIMD_USE_AVX512BW
                static inline int16<32> i_mul_hi(const int16<32> &a, const int16<32> &b) {
                    return _mm512_mulhi_epi16(a.native(), b.native());
                }
#endif

                // -----------------------------------------------------------------------------

                static inline uint16<8> i_mul_hi(const uint16<8> &a, const uint16<8> &b) {
#if SIMD_USE_NULL
                    uint16<8> r;
                    for (unsigned i = 0; i < a.length; i++) {
                        r.el(i) = (uint32_t(a.el(i)) * b.el(i)) >> 16;
                    }
                    return r;
#elif SIMD_USE_SSE2
                    return _mm_mulhi_epu16(a.native(), b.native());
#elif SIMD_USE_NEON
                    uint32x4 lo = vmull_u16(vget_low_u16(a.native()), vget_low_u16(b.native()));
                    uint32x4 hi = vmull_u16(vget_high_u16(a.native()), vget_high_u16(b.native()));
                    return unzip8_hi(uint16x8(lo), uint16x8(hi));
#elif SIMD_USE_ALTIVEC && SIMD_BIG_ENDIAN
                    uint16<16> ab;
                    ab = mull(a, b);
                    return unzip8_lo(ab.vec(0), ab.vec(1));
#elif (SIMD_USE_ALTIVEC && SIMD_LITTLE_ENDIAN) || SIMD_USE_MSA
                    uint16<16> ab;
                    ab = mull(a, b);
                    return unzip8_hi(ab.vec(0), ab.vec(1));
#endif
                }

#if SIMD_USE_AVX2
                static inline uint16<16> i_mul_hi(const uint16<16> &a, const uint16<16> &b) {
                    return _mm256_mulhi_epu16(a.native(), b.native());
                }
#endif

#if SIMD_USE_AVX512BW
                static inline uint16<32> i_mul_hi(const uint16<32> &a, const uint16<32> &b) {
                    return _mm512_mulhi_epu16(a.native(), b.native());
                }
#endif

                // -----------------------------------------------------------------------------

                template <class V> inline V i_mul_hi(const V &a, const V &b) {
                    SIMD_VEC_ARRAY_IMPL2(V, i_mul_hi, a, b)
                }

            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
