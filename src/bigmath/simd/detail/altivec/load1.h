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

#ifndef ALTIVEC_LOAD1_H
#define ALTIVEC_LOAD1_H
#if SIMD_USE_ALTIVEC

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace altivec {

                /** Loads a single element from unaligned memory location and places it to the
                    first position in the vector. The contents of the rest of the vector are
                    undefined.

                    @code
                    a.vec(0) = *p
                    @endcode

                    @icost{ALTIVEC, 2}
                */
                static inline uint8x16 load1_u(uint8x16 &a, const uint8_t *p) {
                    a = vec_lde(0, p);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated"
                    __vector uint8_t perm = vec_lvsl(0, p);
#pragma GCC diagnostic pop
                    a = (__vector uint8_t)vec_perm(a.native(), a.native(), perm);
                    return a;
                }

                static inline uint16x8 load1_u(uint16x8 &a, const uint16_t *p) {
                    __vector uint16_t r = vec_lde(0, p);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated"
                    __vector uint8_t perm = vec_lvsl(0, p);
#pragma GCC diagnostic pop
                    a = (__vector uint16_t)vec_perm((__vector uint8_t)r, (__vector uint8_t)r, perm);
                    return a;
                }

                static inline uint32x4 load1_u(uint32x4 &a, const uint32_t *p) {
                    __vector uint32_t r = vec_lde(0, p);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated"
                    __vector uint8_t perm = vec_lvsl(0, p);
#pragma GCC diagnostic pop
                    a = (__vector uint32_t)vec_perm((__vector uint8_t)r, (__vector uint8_t)r, perm);
                    return a;
                }

                static inline float32x4 load1_u(float32x4 &a, const float *p) {
                    __vector float r = vec_lde(0, p);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated"
                    __vector uint8_t perm = vec_lvsl(0, p);
#pragma GCC diagnostic pop
                    a = (__vector float)vec_perm((__vector uint8_t)r, (__vector uint8_t)r, perm);
                    return a;
                }

                /** Loads a single element from a memory location and places it to the vector.
                    The position of the element is determined by the last 4 address @a p bits.
                    The contents of the rest of the vector are undefined.

                    @code
                    i = (p % 15) / sizeof(element)
                    a[i] = *p
                    @endcode
                */
                static inline uint8x16 load1(uint8x16 &a, const uint8_t *p) {
                    a = vec_lde(0, p);
                    return a;
                }

                static inline uint16x8 load1(uint16x8 &a, const uint16_t *p) {
                    a = vec_lde(0, p);
                    return a;
                }

                static inline uint32x4 load1(uint32x4 &a, const uint32_t *p) {
                    a = vec_lde(0, p);
                    return a;
                }

                static inline float32x4 load1(float32x4 &a, const float *p) {
                    a = vec_lde(0, p);
                    return a;
                }

            } // namespace altivec
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
#endif
