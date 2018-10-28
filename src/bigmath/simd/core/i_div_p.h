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

#ifndef SIMD_CORE_I_DIV_P_H
#define SIMD_CORE_I_DIV_P_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/core/bit_and.h>
#include <bigmath/simd/core/bit_andnot.h>
#include <bigmath/simd/core/bit_or.h>
#include <bigmath/simd/core/cmp_lt.h>
#include <bigmath/simd/core/i_sub.h>
#include <bigmath/simd/detail/null/math.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {

        // FIXME: move to adv
        /** Divides one 8-bit unsigned number by another. The precision of the operation
            is configurable: only P least significant bits of both numerator and
            denumerator are considered.

            @code
            r0 = num0 / den0
            ...
            rN = numN / denN
            @endcode
            @par 128-bit version:
            The operations costs at least 9 instructions per bit of precision.

            @par 256-bit version:
            @icost{SSE2-AVX, NEON, 10}
            @icost{AVX2, 4}
        */
        template <unsigned P> inline uint8x16 div_p(const uint8x16 &num, const uint8x16 &den) {
#if SIMD_USE_NULL
            return detail::null::div_p<P>(num, den);
#else
            static_assert(P <= 8, "Precision too large");
            uint8x16 r, q, bit_mask;
            r = q = make_zero();
            bit_mask = make_uint(1 << (P - 1));

            for (unsigned i = P; i > 0; i--) {
                unsigned bit = i - 1;
                uint8x16 n_bit;
                // we'll never shift out any bits, so larger shift doesn't matter
                r = shift_l<1>((uint16x8)r);

                n_bit = bit_and(num, bit_mask);
                n_bit = shift_r((uint16x8)n_bit, bit);
                r = bit_or(r, n_bit);

                uint8x16 cmp, csub, cbit;
                cmp = cmp_lt(r, den);

                csub = bit_andnot(den, cmp);
                cbit = bit_andnot(bit_mask, cmp);
                r = sub(r, csub);
                q = bit_or(q, cbit);

                bit_mask = shift_r<1>((uint16x8)bit_mask);
            }
            return q;

            /*
            The actual algorithm is as follows:
            N - numerator, D - denominator, R - remainder, Q - quetient
            R = 0; Q = 0;
            for (unsigned i = P; i > 0; i--) {
                unsigned bit = i-1;
                R <<= 1;
                R |= (N >> bit) & 1;
                if (R >= D) {
                    R = R - D;
                    Q |= 1 << bit;
                }
            }*/
#endif
        }

        template <unsigned P> inline uint16x8 div_p(const uint16x8 &num, const uint16x8 &den) {
#if SIMD_USE_NULL
            return detail::null::div_p<P>(num, den);
#else
            static_assert(P <= 16, "Precision too large");
            uint16x8 r, q, bit_mask;

            r = q = make_zero();
            bit_mask = make_uint(1 << (P - 1));

            for (unsigned i = P; i > 0; i--) {
                unsigned bit = i - 1; // TODO precision
                uint16x8 n_bit;
                r = shift_l<1>(r);

                n_bit = bit_and(num, bit_mask);
                n_bit = shift_r(n_bit, bit);
                r = bit_or(r, n_bit);

                uint16x8 cmp, csub, cbit;
                cmp = cmp_lt(r, den);

                csub = bit_andnot(den, cmp);
                cbit = bit_andnot(bit_mask, cmp);
                r = sub(r, csub);
                q = bit_or(q, cbit);

                bit_mask = shift_r<1>(bit_mask);
            }
            return q;
#endif
        }

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
