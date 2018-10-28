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

#ifndef SIMD_DETAIL_INSN_I_MUL_LO_H
#define SIMD_DETAIL_INSN_I_MUL_LO_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/core/i_mull.h>
#include <bigmath/simd/core/move_l.h>
#include <bigmath/simd/core/permute4.h>
#include <bigmath/simd/core/shuffle2.h>
#include <bigmath/simd/detail/null/math.h>
#include <bigmath/simd/detail/vector_array_macros.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {

                static inline uint16<8> i_mul_lo(const uint16<8> &a, const uint16<8> &b) {
#if SIMD_USE_NULL
                    return detail::null::mul(a, b);
#elif SIMD_USE_SSE2
                    return _mm_mullo_epi16(a.native(), b.native());
#elif SIMD_USE_NEON
                    return vmulq_u16(a.native(), b.native());
#elif SIMD_USE_ALTIVEC
                    return vec_mladd(a.native(), b.native(), ((uint16x8)make_zero()).native());
#elif SIMD_USE_MSA
                    return (v8u16)__msa_mulv_h((v8i16)a.native(), (v8i16)b.native());
#endif
                }

#if SIMD_USE_AVX2
                static inline uint16<16> i_mul_lo(const uint16<16> &a, const uint16<16> &b) {
                    return _mm256_mullo_epi16(a.native(), b.native());
                }
#endif

#if SIMD_USE_AVX512BW
                static inline uint16<32> i_mul_lo(const uint16<32> &a, const uint16<32> &b) {
                    return _mm512_mullo_epi16(a.native(), b.native());
                }
#endif

                // -----------------------------------------------------------------------------

                static inline uint32<4> i_mul_lo(const uint32<4> &a, const uint32<4> &b) {
#if SIMD_USE_NULL
                    return detail::null::mul(a, b);
#elif SIMD_USE_SSE4_1
                    return _mm_mullo_epi32(a.native(), b.native());
#elif SIMD_USE_SSE2
                    uint32x4 a1, b1, r;
                    a1 = move4_l<1>(a);
                    b1 = move4_l<1>(b);
                    r = _mm_mul_epu32(a.native(), b.native());
                    a1 = _mm_mul_epu32(a1.native(), b1.native());
                    r = shuffle2<0, 2, 0, 2>(r, a1); // moves to FP domain, additional latency unavoidable
                    r = permute4<0, 2, 1, 3>(r);
                    return r;
#elif SIMD_USE_NEON
                    return vmulq_u32(a.native(), b.native());
#elif SIMD_USE_VSX_207
#if __GNUC__
                    // BUG: GCC does not have support for vmuluwm yet
                    __vector uint32_t va = a.native(), vb = b.native();
                    __vector uint32_t vr;
                    asm("vmuluwm	%0, %1, %2" : "=v"(vr) : "v"(va), "v"(vb));
                    return vr;
#else
                    return vec_vmuluwm(a.native(), b.native());
#endif
#elif SIMD_USE_ALTIVEC
                    // implement in terms of 16-bit multiplies
                    //   *  ah  al
                    //      bh  bl
                    //      ======
                    //   + (al*bl) <-  l_ab
                    //+ (ah*bl)    <-  h_ab
                    //+ (al*bh)    <-  h_ba

                    uint16<8> ra, rb;
                    ra = a, rb = b;
#if SIMD_BIG_ENDIAN
                    uint16<8> sa = move8_r<1>(ra);
                    uint16<8> sb = move8_r<1>(rb);

                    uint32<4> l_ab = vec_mulo(ra.native(), rb.native());
                    uint32<4> h_ab = vec_mulo(ra.native(), sb.native());
                    uint32<4> h_ba = vec_mulo(sa.native(), rb.native());
#else
                    uint16<8> sa = move8_l<1>(ra);
                    uint16<8> sb = move8_l<1>(rb);

                    uint32<4> l_ab = vec_mule(ra.native(), rb.native());
                    uint32<4> h_ab = vec_mule(ra.native(), sb.native());
                    uint32<4> h_ba = vec_mule(sa.native(), rb.native());
#endif

                    h_ab = shift_l<16>(add(h_ab, h_ba));
                    h_ab = add(h_ab, l_ab);
                    return h_ab;
#elif SIMD_USE_MSA
                    return (v4u32)__msa_mulv_w((v4i32)a.native(), (v4i32)b.native());
#endif
                }

#if SIMD_USE_AVX2
                static inline uint32<8> i_mul_lo(const uint32<8> &a, const uint32<8> &b) {
                    return _mm256_mullo_epi32(a.native(), b.native());
                }
#endif

#if SIMD_USE_AVX512F
                static inline uint32<16> i_mul_lo(const uint32<16> &a, const uint32<16> &b) {
                    return _mm512_mullo_epi32(a.native(), b.native());
                }
#endif

                // -----------------------------------------------------------------------------

                template <class V> inline V i_mul_lo(const V &a, const V &b) {
                    SIMD_VEC_ARRAY_IMPL2(V, i_mul_lo, a, b)
                }

            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
