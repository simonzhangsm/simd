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

#ifndef SIMD_DETAIL_INSN_CONV_SHRINK_TO_INT32_H
#define SIMD_DETAIL_INSN_CONV_SHRINK_TO_INT32_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/core/permute4.h>
#include <bigmath/simd/core/unzip_lo.h>
#include <bigmath/simd/core/zip_lo.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {


                inline uint32<4> i_to_uint32(const uint64<4> &a) {
#if SIMD_USE_NULL
                    uint32<4> r;
                    for (unsigned i = 0; i < 4; i++) {
                        r.el(i) = uint32_t(a.vec(i / 2).el(i % 2));
                    }
                    return r;
#elif SIMD_USE_AVX512VL
                    return _mm256_cvtepi64_epi32(a.native());
#elif SIMD_USE_AVX2
                    uint64<4> a64;
                    a64 = permute4<0, 2, 0, 2>((uint32<8>)a);
                    a64 = permute4<0, 2, 0, 2>(a64);
                    return _mm256_castsi256_si128(a64.native());
#elif SIMD_USE_NEON64
                    uint32x2_t low = vmovn_u64(a.vec(0).native());
                    return vmovn_high_u64(low, a.vec(1).native());
#elif SIMD_USE_NEON
                    uint32x2_t low = vmovn_u64(a.vec(0).native());
                    uint32x2_t high = vmovn_u64(a.vec(1).native());
                    return vcombine_u32(low, high);
#elif SIMD_USE_VSX_207
                    return vec_pack(a.vec(0).native(), a.vec(1).native());
#elif SIMD_USE_ALTIVEC && SIMD_BIG_ENDIAN
                    uint32<4> r1, r2;
                    r1 = a.vec(0);
                    r2 = a.vec(1);
                    return unzip4_hi(r1, r2);
#elif SIMD_USE_SSE2 || SIMD_USE_MSA || (SIMD_USE_ALTIVEC && SIMD_LITTLE_ENDIAN)
                    uint32<4> r1, r2;
                    r1 = a.vec(0);
                    r2 = a.vec(1);
                    return unzip4_lo(r1, r2);
#endif
                }

#if SIMD_USE_AVX2
                inline uint32<8> i_to_uint32(const uint64<8> &a) {
#if SIMD_USE_AVX512F
                    return _mm512_cvtepi64_epi32(a.native());
#else
                    uint64<4> b0, b1;
                    b0 = permute4<0, 2, 0, 2>((uint32<8>)a.vec(0));
                    b1 = permute4<0, 2, 0, 2>((uint32<8>)a.vec(1));
                    b0 = zip2_lo(b0, b1);
                    b0 = permute4<0, 2, 1, 3>(b0);
                    return (uint32<8>)b0;
#endif
                }
#endif

#if SIMD_USE_AVX512F
                inline uint32<16> i_to_uint32(const uint64<16> &a) {
                    uint32<8> r1 = _mm512_cvtepi64_epi32(a.vec(0).native());
                    uint32<8> r2 = _mm512_cvtepi64_epi32(a.vec(1).native());
                    return combine(r1, r2);
                }
#endif

                template <unsigned N> inline uint32<N> i_to_uint32(const uint64<N> &a) {
                    SIMD_VEC_ARRAY_IMPL_CONV_EXTRACT(uint32<N>, i_to_uint32, a)
                }


            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
