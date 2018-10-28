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

#ifndef SIMD_CORE_SHUFFLE2x2_H
#define SIMD_CORE_SHUFFLE2x2_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/insn/shuffle4x2.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {

        /** Selects 32-bit values from two vectors.
            The selector values must be in range [0; 3].

            @code
            For each 64-bit segment:
            ab = [ a..b ]
            r0 = ab[s0]
            r1 = ab[s1]
            @endcode
        */
        template <unsigned s0, unsigned s1, unsigned N, class V1, class V2>
        inline typename detail::get_expr2_nomask<V1, V2>::empty shuffle2x2(const any_vec32<N, V1> &a,
                                                                           const any_vec32<N, V2> &b) {
#if SIMD_USE_NULL || SIMD_USE_SSE2 || SIMD_USE_NEON
            static_assert(s0 < 4 && s1 < 4, "Selector out of range");
            typename detail::get_expr2_nomask_nosign<V1, V2, void>::type a0 = a.wrapped().eval(),
                                                                         b0 = b.wrapped().eval();
            return detail::insn::i_shuffle2x2<s0, s1>(a0, b0);
#else
            return SIMD_NOT_IMPLEMENTED_TEMPLATE2(V1, a, b);
#endif
        }

        /** Selects 64-bit values from two vectors.
            The selector values must be in range [0; 3].

            @code
            For each 128-bit segment:
            ab = [ a..b ]
            r0 = ab[s0]
            r1 = ab[s1]
            @endcode
        */
        template <unsigned s0, unsigned s1, unsigned N, class V1, class V2>
        inline typename detail::get_expr2_nomask<V1, V2>::empty shuffle2x2(const any_vec64<N, V1> &a,
                                                                           const any_vec64<N, V2> &b) {
#if SIMD_USE_NULL || SIMD_USE_SSE2 || SIMD_USE_NEON
            static_assert(s0 < 4 && s1 < 4, "Selector out of range");
            typename detail::get_expr2_nomask_nosign<V1, V2, void>::type a0 = a.wrapped().eval(),
                                                                         b0 = b.wrapped().eval();
            return detail::insn::i_shuffle2x2<s0, s1>(a0, b0);
#else
            return SIMD_NOT_IMPLEMENTED_TEMPLATE2(V1, a, b);
#endif
        }

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
