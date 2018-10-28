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

#ifndef SIMD_CORE_SHUFFLE2_H
#define SIMD_CORE_SHUFFLE2_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/insn/shuffle4x2.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {

        /** Selects 32-bit floating-point values from two vectors. The first two values
            in each four consecutive values must come from @a a, the last two - from @a
            b. The selector values must be in range [0; 3].

            @code
            r0 = a[a0]
            r1 = a[a1]
            r2 = b[b0]
            r3 = b[b1]

            256-bit version:
            r4 = a[a0+4]
            r5 = a[a1+4]
            r6 = b[b0+4]
            r7 = b[b1+4]
            @endcode

            @par floating-point
            @par 128-bit version:
            @icost{ALTIVEC, 1-2}
            @icost{NEON, 1-4}

            @par 256-bit version:
            @icost{SSE2-SSE4.1, 2}
            @icost{NEON, 2-8}
            @icost{ALTIVEC, 2-3}

            @par integer
             @par 128-bit version:
            @icost{NEON, 1-4}
            @icost{ALTIVEC, 1-2}

            @par 256-bit version:
            @icost{SSE2-AVX, 2}
            @icost{NEON, 2-8}
            @icost{ALTIVEC, 2-3}
        */
        template <unsigned sa0, unsigned sa1, unsigned sb0, unsigned sb1, unsigned N, class V1, class V2>
        inline typename detail::get_expr2_nomask<V1, V2>::empty shuffle2(const any_vec32<N, V1> &a,
                                                                         const any_vec32<N, V2> &b) {
            static_assert(sa0 < 4 && sa1 < 4 && sb0 < 4 && sb1 < 4, "Selector out of range");
            typename detail::get_expr2_nomask<V1, V2, void>::type a0 = a.wrapped().eval(), b0 = b.wrapped().eval();
            return detail::insn::i_shuffle4x2<sa0, sa1, sb0 + 4, sb1 + 4>(a0, b0);
        }

        /** Selects 32-bit values from two vectors. The first two values in each four
            consecutive values must come from @a a, the last two - from @a b. The
            selector values must be in range [0; 3].

            @code
            r0 = a[s0]
            r1 = a[s1]
            r2 = b[s0]
            r3 = b[s1]

            256-bit version:
            r4 = a[s0+4]
            r5 = a[s1+4]
            r6 = b[s0+4]
            r7 = b[s1+4]
            @endcode

            @par floating-point
            @par 128-bit version:
            @icost{ALTIVEC, 1-2}
            @icost{NEON, 2-4}

            @par 256-bit version:
            @icost{SSE2-SSE4.1, 2}
            @icost{NEON, 4-8}
            @icost{ALTIVEC, 2-3}

            @par integer
            @par 128-bit version:
            @icost{NEON, 2-4}
            @icost{ALTIVEC, 1-2}

            @par 256-bit version:
            @icost{SSE2-AVX, 2}
            @icost{NEON, 4-8}
            @icost{ALTIVEC, 2-3}
        */
        template <unsigned s0, unsigned s1, unsigned N, class V1, class V2>
        inline typename detail::get_expr2_nomask<V1, V2>::empty shuffle2(const any_vec32<N, V1> &a,
                                                                         const any_vec32<N, V2> &b) {
            static_assert(s0 < 4 && s1 < 4, "Selector out of range");
            typename detail::get_expr2_nomask<V1, V2, void>::type a0 = a.wrapped().eval(), b0 = b.wrapped().eval();
            return detail::insn::i_shuffle4x2<s0, s1, s0 + 4, s1 + 4>(a0, b0);
        }


    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
