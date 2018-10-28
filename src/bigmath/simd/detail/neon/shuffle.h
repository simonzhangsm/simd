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

#ifndef DETAIL_NEON_SHUFFLE_H
#define DETAIL_NEON_SHUFFLE_H
#if SIMD_USE_NEON

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace neon {

                /** @code
                    a0 = b0
                    a1 = a1
                    b0 = a0
                    b1 = b1
                    @endcode
                */
                static inline void swap_lo(uint64x2 &a, uint64x2 &b) {
                    uint64x1_t ah, bh, al, bl;
                    al = vget_low_u64(a.native());
                    bl = vget_low_u64(b.native());
                    ah = vget_high_u64(a.native());
                    bh = vget_high_u64(b.native());
                    a = vcombine_u64(bl, ah);
                    b = vcombine_u64(al, bh);
                }

                /** @code
                    a0 = a0
                    a1 = b1
                    b0 = b0
                    b1 = a1
                    @endcode
                */
                static inline void swap_hi(uint64x2 &a, uint64x2 &b) {
                    uint64x1_t ah, bh, al, bl;
                    al = vget_low_u64(a.native());
                    bl = vget_low_u64(b.native());
                    ah = vget_high_u64(a.native());
                    bh = vget_high_u64(b.native());
                    a = vcombine_u64(al, bh);
                    b = vcombine_u64(bl, ah);
                }

                static inline void transpose2(uint64x2 &a, uint64x2 &b) {
                    uint64x1_t ah, bh, al, bl;
                    al = vget_low_u64(a.native());
                    bl = vget_low_u64(b.native());
                    ah = vget_high_u64(a.native());
                    bh = vget_high_u64(b.native());
                    a = vcombine_u64(al, bl);
                    b = vcombine_u64(ah, bh);
                }

                static inline uint64x2 zip2_lo(const uint64x2 &ca, const uint64x2 &cb) {
                    uint64<2> a = ca, b = cb;
                    transpose2(a, b);
                    return a;
                }

                static inline uint64x2 zip2_hi(const uint64x2 &ca, const uint64x2 &cb) {
                    uint64<2> a = ca, b = cb;
                    transpose2(a, b);
                    return b;
                }

            } // namespace neon
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
#endif
