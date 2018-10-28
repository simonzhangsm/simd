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

#ifndef DETAIL_NEON_MATH_INT_H
#define DETAIL_NEON_MATH_INT_H
#if SIMD_USE_NEON

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace neon {

                /** Multiplies the values of two int8x16 vectors and returns the low
                    part of the multiplication

                    @code
                    r0 = low(a0 * b0)
                    ...
                    r15 = low(a15 * b15)
                    @endcode
                */
                static inline uint8x16 mul_lo(const uint8x16 &a, const uint8x16 &b) {
                    return vmulq_u8(a.native(), b.native());
                }

                /** Multiplies the first 8 values of two signed int8x16 vectors and expands the
                    results to 16 bits.

                    @code
                    r0 = a0 * b0
                    ...
                    r7 = a7 * b7
                    @endcode
                */
                static inline int16x8 mull_lo(const int8x16 &a, const int8x16 &b) {
                    return vmull_s8(vget_low_s8(a.native()), vget_low_s8(b.native()));
                }

                /** Multiplies the first 8 values of two unsigned int8x16 vectors and expands the
                    results to 16 bits.

                    @code
                    r0 = a0 * b0
                    ...
                    r7 = a7 * b7
                    @endcode
                */
                static inline uint16x8 mull_lo(const uint8x16 &a, const uint8x16 &b) {
                    return vmull_u8(vget_low_u8(a.native()), vget_low_u8(b.native()));
                }

                /** Multiplies the last 8 values of two signed int8x16 vectors and expands the
                    results to 16 bits.

                    @code
                    r0 = a8 * b8
                    ...
                    r7 = a15 * b15
                    @endcode
                */
                static inline int16x8 mull_hi(const int8x16 &a, const int8x16 &b) {
                    return vmull_s8(vget_high_s8(a.native()), vget_high_s8(b.native()));
                }


                /** Multiplies the last 8 values of two unsigned int8x16 vectors and expands
                    the results to 16 bits.

                    @code
                    r0 = a8 * b8
                    ...
                    r7 = a15 * b15
                    @endcode
                */
                static inline uint16x8 mull_hi(const uint8x16 &a, const uint8x16 &b) {
                    return vmull_u8(vget_high_u8(a.native()), vget_high_u8(b.native()));
                }

            } // namespace neon
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
#endif
