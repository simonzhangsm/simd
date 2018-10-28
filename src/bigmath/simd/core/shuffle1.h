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

#ifndef SIMD_CORE_SHUFFLV1_H
#define SIMD_CORE_SHUFFLV1_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/insn/shuffle2x2.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {

        /** Selects 64-bit values from two vectors. The first value in
            each pair of values must come from @a a, the second - from @a b. The
            selector values must be in range [0; 1].

            @code
            r0 = a[s0]
            r1 = b[s1]

            256-bit version:
            r2 = a[s0+2]
            r3 = b[s1+2]
            @endcode

            @par floating-point
            @par 128-bit version:
            @novec{NEON, ALTIVEC}

            @par 256-bit version:
            @icost{SSE2-SSE4.1, 2}
            @novec{NEON, ALTIVEC}

            @par integer
            @par 128-bit version:
            @icost{ALTIVEC, 1-2}

            @par 256-bit version:
            @icost{SSE2-AVX, 2}
            @icost{NEON, 1-2}
            @icost{ALTIVEC, 2-3}
        */
        template <unsigned s0, unsigned s1, unsigned N, class V1, class V2>
        inline typename detail::get_expr2_nomask<V1, V2>::empty shuffle1(const any_vec64<N, V1> &a,
                                                                         const any_vec64<N, V2> &b) {
            static_assert(s0 < 2 && s1 < 2, "Selector out of range");
            typename detail::get_expr2_nomask<V1, V2>::type ra = a.wrapped().eval(), rb = b.wrapped().eval();
            return detail::insn::i_shuffle2x2<s0, s1 + 2>(ra, rb);
        }

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
