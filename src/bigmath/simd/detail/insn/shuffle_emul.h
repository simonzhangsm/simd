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

#ifndef SIMD_DETAIL_INSN_SHUFFLE_EMUL_H
#define SIMD_DETAIL_INSN_SHUFFLE_EMUL_H
#if SIMD_USE_SSE2 || SIMD_USE_NEON || SIMD_USE_ALTIVEC

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/core/permute2.h>
#include <bigmath/simd/core/shuffle1.h>
#include <bigmath/simd/core/combine.h>
#include <bigmath/simd/core/split.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {

                template <unsigned s0, unsigned s1, class V> inline V permute_half(const V &a0, const V &a1) {
                    switch (s0 * 4 + s1) {
                        default:
                        case 0: /* 0 0 */
                            return permute2<0, 0>(a0);
                        case 1: /* 0 1 */
                            return a0;
                        case 2: /* 0 2 */
                            return shuffle1<0, 0>(a0, a1);
                        case 3: /* 0 3 */
                            return shuffle1<0, 1>(a0, a1);
                        case 4: /* 1 0 */
                            return permute2<1, 0>(a0);
                        case 5: /* 1 1 */
                            return permute2<1, 1>(a0);
                        case 6: /* 1 2 */
                            return shuffle1<1, 0>(a0, a1);
                        case 7: /* 1 3 */
                            return shuffle1<1, 1>(a0, a1);
                        case 8: /* 2 0 */
                            return shuffle1<0, 0>(a1, a0);
                        case 9: /* 2 1 */
                            return shuffle1<0, 1>(a1, a0);
                        case 10: /* 2 2 */
                            return permute2<0, 0>(a1);
                        case 11: /* 2 3 */
                            return a1;
                        case 12: /* 3 0 */
                            return shuffle1<1, 0>(a1, a0);
                        case 13: /* 3 1 */
                            return shuffle1<1, 1>(a1, a0);
                        case 14: /* 3 2 */
                            return permute2<1, 0>(a1);
                        case 15: /* 3 3 */
                            return permute2<1, 1>(a1);
                    }
                }

                /** Permutes 4 64-bit elements within 256-bit vector using 2 element shuffling
                    functions.
                */
                template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                inline uint64x4 permute_emul(const uint64x4 &a) {
                    uint64x2 r0, r1, a0, a1;
                    split(a, a0, a1);
                    r0 = permute_half<s0, s1>(a0, a1);
                    r1 = permute_half<s2, s3>(a0, a1);
                    return combine(r0, r1);
                }

                template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                inline float64x4 permute_emul(const float64x4 &a) {
                    float64x2 r0, r1, a0, a1;
                    split(a, a0, a1);
                    r0 = permute_half<s0, s1>(a0, a1);
                    r1 = permute_half<s2, s3>(a0, a1);
                    return combine(r0, r1);
                }

            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif // SIMD_USE_SSE2 || SIMD_USE_NEON || SIMD_USE_ALTIVEC
#endif
