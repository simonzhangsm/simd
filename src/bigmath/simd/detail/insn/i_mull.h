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

#ifndef SIMD_DETAIL_INSN_I_MULL_H
#define SIMD_DETAIL_INSN_I_MULL_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/mem_block.h>
#include <bigmath/simd/detail/not_implemented.h>
#include <bigmath/simd/core/detail/subvec_insert.h>
#include <bigmath/simd/core/to_int32.h>
#include <bigmath/simd/core/to_int64.h>
#include <bigmath/simd/core/i_mul.h>
#include <bigmath/simd/core/combine.h>
#include <bigmath/simd/core/zip_hi.h>
#include <bigmath/simd/core/zip_lo.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {

                /*  Note: widening integer multiplication instructions are very different among
                    instruction sets. The main difference is in which half of the elements are
                    selected for multiplication. Trying to abstract this incurs definite
                    overhead.

                     - SSE2-SSE4.1, AVX2, ALTIVEC and VSX provide only instructions with
                        interfaces similar to mul_lo and mul_hi. The result vectors must be
                        interleaved to obtain contiguous result values. Multiplying 2 vectors
                        always incurs overhead of at least two interleaving instructions.

                     - AVX512 only provides 32-bit integer support. Widening multiplication
                        can be done only by using PMULDQ, which takes odd elements and produces
                        widened multiplication results. Multiplication of two whole vectors
                        always incurs overhead of at least two shifts or interleaving
                        instructions.

                     - NEON, NEONv2 provide instructions that take elements of either the lower
                        or higher halves of two 128-bit vectors and multiply them. No
                        additional overhead is incurred to obtain contiguous result values.

                    The abstraction below uses the NEON model. No additional overhead is
                    incurred on SSE/AVX and NEON. On ALTIVEC, a single additional permute
                    instruction is needed for each vector multiplication on average.
                */

                static inline int32<8> i_mull(const int16<8> &a, const int16<8> &b) {
#if SIMD_USE_NULL
                    int32x8 r;
                    for (unsigned i = 0; i < 8; i++) {
                        r.vec(i / 4).el(i % 4) = int32_t(a.el(i)) * b.el(i);
                    }
                    return r;
#elif SIMD_USE_SSE2
                    int16x8 lo = _mm_mullo_epi16(a.native(), b.native());
                    int16x8 hi = _mm_mulhi_epi16(a.native(), b.native());
                    return (int32x8)combine(zip8_lo(lo, hi), zip8_hi(lo, hi));
#elif SIMD_USE_NEON
                    int32x4 lo = vmull_s16(vget_low_s16(a.native()), vget_low_s16(b.native()));
                    int32x4 hi = vmull_s16(vget_high_s16(a.native()), vget_high_s16(b.native()));
                    return combine(lo, hi);
#elif SIMD_USE_ALTIVEC
                    int32x4 lo = vec_mule(a.native(), b.native());
                    int32x4 hi = vec_mulo(a.native(), b.native());
                    return combine(zip4_lo(lo, hi), zip4_hi(lo, hi));
#elif SIMD_USE_MSA
                    int32<8> a32 = to_int32(a);
                    int32<8> b32 = to_int32(b);
                    a32.vec(0) = __msa_mulv_w(a32.vec(0).native(), b32.vec(0).native());
                    a32.vec(1) = __msa_mulv_w(a32.vec(1).native(), b32.vec(1).native());
                    return a32;
#endif
                }

#if SIMD_USE_AVX2
                static inline int32<16> i_mull(const int16<16> &a, const int16<16> &b) {
                    int16<16> as, bs, lo, hi;
                    as = _mm256_permute4x64_epi64(a.native(), _MM_SHUFFLE(3, 1, 2, 0));
                    bs = _mm256_permute4x64_epi64(b.native(), _MM_SHUFFLE(3, 1, 2, 0));
                    lo = _mm256_mullo_epi16(as.native(), bs.native());
                    hi = _mm256_mulhi_epi16(as.native(), bs.native());
                    return (int32<16>)combine(zip8_lo(lo, hi), zip8_hi(lo, hi));
                }
#endif

#if SIMD_USE_AVX512BW
                static inline int32<32> i_mull(const int16<32> &a, const int16<32> &b) {
                    int16<32> as, bs, lo, hi;
                    int64<8> idx = make_uint(0, 4, 1, 5, 2, 6, 3, 7);
                    as = _mm512_permutexvar_epi64(idx.native(), a.native());
                    bs = _mm512_permutexvar_epi64(idx.native(), b.native());
                    lo = _mm512_mullo_epi16(as.native(), bs.native());
                    hi = _mm512_mulhi_epi16(as.native(), bs.native());
                    return (int32<32>)combine(zip8_lo(lo, hi), zip8_hi(lo, hi));
                }
#endif

                template <unsigned N> inline int32<N> i_mull(const int16<N> &a, const int16<N> &b) {
                    int32<N> r;
                    for (unsigned i = 0; i < a.vec_length; ++i) {
                        detail::subvec_insert(r, mull(a.vec(i), b.vec(i)).eval(), i);
                    }
                    return r;
                }

                // -----------------------------------------------------------------------------

                static inline uint32<8> i_mull(const uint16<8> &a, const uint16<8> &b) {
#if SIMD_USE_NULL
                    int32x8 r;
                    for (unsigned i = 0; i < 8; i++) {
                        r.vec(i / 4).el(i % 4) = uint32_t(a.el(i)) * b.el(i);
                    }
                    return r;
#elif SIMD_USE_SSE2
                    int16x8 lo = _mm_mullo_epi16(a.native(), b.native());
                    int16x8 hi = _mm_mulhi_epu16(a.native(), b.native());
                    return (uint32x8)combine(zip8_lo(lo, hi), zip8_hi(lo, hi));
#elif SIMD_USE_NEON
                    uint32x4 lo = vmull_u16(vget_low_u16(a.native()), vget_low_u16(b.native()));
                    uint32x4 hi = vmull_u16(vget_high_u16(a.native()), vget_high_u16(b.native()));
                    return combine(lo, hi);
#elif SIMD_USE_ALTIVEC
                    uint32x4 lo = vec_mule(a.native(), b.native());
                    uint32x4 hi = vec_mulo(a.native(), b.native());
                    return combine(zip4_lo(lo, hi), zip4_hi(lo, hi));
#elif SIMD_USE_MSA
                    int32<8> a32 = (int32<8>)to_uint32(a);
                    int32<8> b32 = (int32<8>)to_uint32(b);
                    a32.vec(0) = __msa_mulv_w(a32.vec(0).native(), b32.vec(0).native());
                    a32.vec(1) = __msa_mulv_w(a32.vec(1).native(), b32.vec(1).native());
                    return uint32<8>(a32);
#endif
                }

#if SIMD_USE_AVX2
                static inline uint32<16> i_mull(const uint16<16> &a, const uint16<16> &b) {
                    uint16<16> as, bs, lo, hi;
                    as = _mm256_permute4x64_epi64(a.native(), _MM_SHUFFLE(3, 1, 2, 0));
                    bs = _mm256_permute4x64_epi64(b.native(), _MM_SHUFFLE(3, 1, 2, 0));
                    lo = _mm256_mullo_epi16(as.native(), bs.native());
                    hi = _mm256_mulhi_epu16(as.native(), bs.native());
                    return (uint32<16>)combine(zip8_lo(lo, hi), zip8_hi(lo, hi));
                }
#endif

#if SIMD_USE_AVX512BW
                static inline uint32<32> i_mull(const uint16<32> &a, const uint16<32> &b) {
                    uint16<32> as, bs, lo, hi;
                    uint64<8> idx = make_uint(0, 4, 1, 5, 2, 6, 3, 7);
                    as = _mm512_permutexvar_epi64(idx.native(), a.native());
                    bs = _mm512_permutexvar_epi64(idx.native(), b.native());
                    lo = _mm512_mullo_epi16(as.native(), bs.native());
                    hi = _mm512_mulhi_epu16(as.native(), bs.native());
                    return (uint32<32>)combine(zip8_lo(lo, hi), zip8_hi(lo, hi));
                }
#endif

                template <unsigned N> inline uint32<N> i_mull(const uint16<N> &a, const uint16<N> &b) {
                    uint32<N> r;
                    for (unsigned i = 0; i < a.vec_length; ++i) {
                        detail::subvec_insert(r, mull(a.vec(i), b.vec(i)).eval(), i);
                    }
                    return r;
                }

                // -----------------------------------------------------------------------------

                static inline int64<4> i_mull(const int32<4> &a, const int32<4> &b) {
#if SIMD_USE_NULL
                    int64x4 r;
                    r.vec(0).el(0) = int64_t(a.el(0)) * b.el(0);
                    r.vec(0).el(1) = int64_t(a.el(1)) * b.el(1);
                    r.vec(1).el(0) = int64_t(a.el(2)) * b.el(2);
                    r.vec(1).el(1) = int64_t(a.el(3)) * b.el(3);
                    return r;
#elif SIMD_USE_SSE4_1
                    int32x4 al, ah, bl, bh;
                    int64x2 rl, rh;
                    al = zip4_lo(a, a);
                    bl = zip4_lo(b, b);
                    ah = zip4_hi(a, a);
                    bh = zip4_hi(b, b);
                    rl = _mm_mul_epi32(al.native(), bl.native());
                    rh = _mm_mul_epi32(ah.native(), bh.native());
                    return combine(rl, rh);
#elif SIMD_USE_NEON
                    int64x2 lo = vmull_s32(vget_low_s32(a.native()), vget_low_s32(b.native()));
                    int64x2 hi = vmull_s32(vget_high_s32(a.native()), vget_high_s32(b.native()));
                    return combine(lo, hi);
#elif SIMD_USE_VSX_207
#if defined(__GNUC__) && (__GNUC__ < 8)
                    // BUG: GCC 7 and earlied don't implement 32-bit integer multiplication
                    __vector int32_t va = a.native(), vb = b.native();
                    __vector int64_t vlo, vhi;
#if SIMD_BIG_ENDIAN
                    asm("vmulesw %0, %1, %2" : "=v"(vlo) : "v"(va), "v"(vb));
                    asm("vmulosw %0, %1, %2" : "=v"(vhi) : "v"(va), "v"(vb));
#else
                    asm("vmulosw %0, %1, %2" : "=v"(vlo) : "v"(va), "v"(vb));
                    asm("vmulesw %0, %1, %2" : "=v"(vhi) : "v"(va), "v"(vb));
#endif
                    int64<2> lo = vlo, hi = vhi;
#else
                    int64x2 lo = vec_vmulesw(a.native(), b.native());
                    int64x2 hi = vec_vmulosw(a.native(), b.native());
#endif
                    return combine(zip2_lo(lo, hi), zip2_hi(lo, hi));
#elif SIMD_USE_MSA
                    int64<4> a64 = to_int64(a);
                    int64<4> b64 = to_int64(b);
                    a64.vec(0) = __msa_mulv_d(a64.vec(0).native(), b64.vec(0).native());
                    a64.vec(1) = __msa_mulv_d(a64.vec(1).native(), b64.vec(1).native());
                    return a64;
#else
                    return SIMD_NOT_IMPLEMENTED2(a, b);
#endif
                }

#if SIMD_USE_AVX2
                static inline int64<8> i_mull(const int32<8> &a, const int32<8> &b) {
                    int32x4 al, ah, bl, bh;
                    int64x4 rl, rh;
                    split(a, al, ah);
                    split(b, bl, bh);

                    rl = _mm256_mul_epi32(to_int64(al).eval().native(), to_int64(bl).eval().native());
                    rh = _mm256_mul_epi32(to_int64(ah).eval().native(), to_int64(bh).eval().native());
                    return combine(rl, rh);
                }
#endif

                template <unsigned N> inline int64<N> i_mull(const int32<N> &a, const int32<N> &b) {
                    int64<N> r;
                    for (unsigned i = 0; i < a.vec_length; ++i) {
                        detail::subvec_insert(r, mull(a.vec(i), b.vec(i)).eval(), i);
                    }
                    return r;
                }

                // -----------------------------------------------------------------------------

                static inline uint64<4> i_mull(const uint32<4> &a, const uint32<4> &b) {
#if SIMD_USE_NULL
                    uint64x4 r;
                    r.vec(0).el(0) = uint64_t(a.el(0)) * b.el(0);
                    r.vec(0).el(1) = uint64_t(a.el(1)) * b.el(1);
                    r.vec(1).el(0) = uint64_t(a.el(2)) * b.el(2);
                    r.vec(1).el(1) = uint64_t(a.el(3)) * b.el(3);
                    return r;
#elif SIMD_USE_SSE2
                    uint32x4 al, ah, bl, bh;
                    uint64x2 rl, rh;
                    al = zip4_lo(a, a);
                    bl = zip4_lo(b, b);
                    ah = zip4_hi(a, a);
                    bh = zip4_hi(b, b);
                    rl = _mm_mul_epu32(al.native(), bl.native());
                    rh = _mm_mul_epu32(ah.native(), bh.native());
                    return combine(rl, rh);
#elif SIMD_USE_NEON
                    uint64x2 lo = vmull_u32(vget_low_u32(a.native()), vget_low_u32(b.native()));
                    uint64x2 hi = vmull_u32(vget_high_u32(a.native()), vget_high_u32(b.native()));
                    return combine(lo, hi);
#elif SIMD_USE_VSX_207
#if defined(__GNUC__) && (__GNUC__ < 8)
                    // BUG: GCC 7 and earlied don't implement 32-bit integer multiplication
                    __vector uint32_t va = a.native(), vb = b.native();
                    __vector uint64_t vlo, vhi;
#if SIMD_BIG_ENDIAN
                    asm("vmuleuw %0, %1, %2" : "=v"(vlo) : "v"(va), "v"(vb));
                    asm("vmulouw %0, %1, %2" : "=v"(vhi) : "v"(va), "v"(vb));
#else
                    asm("vmulouw %0, %1, %2" : "=v"(vlo) : "v"(va), "v"(vb));
                    asm("vmuleuw %0, %1, %2" : "=v"(vhi) : "v"(va), "v"(vb));
#endif
                    uint64<2> lo = vlo, hi = vhi;
#else
                    uint64x2 lo = vec_vmuleuw(a.native(), b.native());
                    uint64x2 hi = vec_vmulouw(a.native(), b.native());
#endif
                    return combine(zip2_lo(lo, hi), zip2_hi(lo, hi));
#elif SIMD_USE_ALTIVEC
                    mem_block<uint32<4>> ba = a;
                    mem_block<uint32<4>> bb = b;
                    uint64x4 r;
                    r.vec(0).el(0) = (uint64_t)ba[0] * bb[0];
                    r.vec(0).el(1) = (uint64_t)ba[1] * bb[1];
                    r.vec(1).el(0) = (uint64_t)ba[2] * bb[2];
                    r.vec(1).el(1) = (uint64_t)ba[3] * bb[3];
                    return r;
#elif SIMD_USE_MSA
                    int64<4> a64 = (int64<4>)to_uint64(a);
                    int64<4> b64 = (int64<4>)to_uint64(b);
                    a64.vec(0) = __msa_mulv_d(a64.vec(0).native(), b64.vec(0).native());
                    a64.vec(1) = __msa_mulv_d(a64.vec(1).native(), b64.vec(1).native());
                    return (uint64<4>)a64;
#endif
                }

#if SIMD_USE_AVX2
                static inline uint64<8> i_mull(const uint32<8> &a, const uint32<8> &b) {
                    uint32x4 al, ah, bl, bh;
                    uint64x4 rl, rh;

                    split(a, al, ah);
                    split(b, bl, bh);

                    rl = _mm256_mul_epu32(to_uint64(al).eval().native(), to_uint64(bl).eval().native());
                    rh = _mm256_mul_epu32(to_uint64(ah).eval().native(), to_uint64(bh).eval().native());

                    return combine(rl, rh);
                }
#endif

#if SIMD_USE_AVX512F
                static inline uint64<16> i_mull(const uint32<16> &a, const uint32<16> &b) {
                    uint32<8> al, ah, bl, bh;
                    uint64<8> rl, rh;

                    split(a, al, ah);
                    split(b, bl, bh);

                    rl = _mm512_mul_epu32(to_int64(al).eval().native(), to_int64(bl).eval().native());
                    rh = _mm512_mul_epu32(to_int64(ah).eval().native(), to_int64(bh).eval().native());

                    return combine(rl, rh);
                }
#endif

                template <unsigned N> inline uint64<N> i_mull(const uint32<N> &a, const uint32<N> &b) {
                    uint64<N> r;
                    for (unsigned i = 0; i < a.vec_length; ++i) {
                        detail::subvec_insert(r, mull(a.vec(i), b.vec(i)).eval(), i);
                    }
                    return r;
                }

            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
