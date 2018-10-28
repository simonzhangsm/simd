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

#ifndef SIMD_CORE_MOVE_L_H
#define SIMD_CORE_MOVE_L_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/insn/move_l.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {

        /** Moves the elements in an int8x16 vector to the left by @a shift positions.

            @code
            shift:  pos:| 0   1    .  14  15  |
             0      r = [ a0  a1   .  a14 a15 ]
             1      r = [ a1  a2   .  a15  0  ]
             2      r = [ a2  a3   .   0   0  ]
              ...    ..   .. ..   ...  ..  .. ..
             14     r = [ a15  0   .   0   0  ]
             15     r = [  0   0   .   0   0  ]
             16     r = [  0   0   .   0   0  ]
            @endcode

            @par 256-bit version:
            The lower and higher 128-bit halves are processed as if 128-bit instruction
            was applied to each of them separately.

            @icost{SSE2-AVX, NEON, ALTIVEC, 2}
        */
        template <unsigned shift, unsigned N, class V>
        inline typename detail::get_expr_nomask<V>::empty move16_l(const any_vec8<N, V> &a) {
            static_assert(shift <= 16, "Shift out of bounds");
            typename detail::get_expr_nomask_nosign<V>::type ra;
            ra = a.wrapped().eval();
            return detail::insn::i_move16_l_wrapper<shift>::run(ra);
        }

        /** Moves the 16-bit elements in a vector to the left by @a shift positions.

            @code
            shift:  pos:| 0  1   . 6  7  |
             0      r = [ a0 a1  . a6 a7 ]
             1      r = [ a1 a2  . a7  0 ]
             2      r = [ a2 a3  .  0  0 ]
              ...    ..   .. .. ... .. ..
             6      r = [ a6 a7  .  0  0 ]
             7      r = [ a7  0  .  0  0 ]
             8      r = [  0  0  .  0  0 ]
            @endcode

            @par 256-bit version:
            The lower and higher 128-bit halves are processed as if 128-bit instruction
            was applied to each of them separately.

            @icost{SSE2-AVX, NEON, ALTIVEC, 2}
        */
        template <unsigned shift, unsigned N, class V>
        inline typename detail::get_expr_nomask<V>::empty move8_l(const any_vec16<N, V> &a) {
            static_assert(shift <= 8, "Shift out of bounds");

            typename detail::get_expr_nomask_nosign<V>::type ra;
            ra = a.wrapped().eval();
            return detail::insn::i_move8_l_wrapper<shift>::run(ra);
        }

        /** Moves the 32-bit elements in a vector to the left by @a shift positions.

            @code
            shift:  pos:| 0  1  2  3  |
             0      r = [ a0 a1 a2 a3 ]
             1      r = [ a1 a2 a3  0 ]
             2      r = [ a2 a3  0  0 ]
             3      r = [ a3  0  0  0 ]
             4      r = [  0  0  0  0 ]
            @endcode

            @par 256-bit version:
            The lower and higher 128-bit halves are processed as if 128-bit instruction
            was applied to each of them separately.

            @icost{SSE2-AVX, NEON, ALTIVEC, 2}
        */
        template <unsigned shift, unsigned N, class V>
        inline typename detail::get_expr_nomask<V>::empty move4_l(const any_vec32<N, V> &a) {
            static_assert(shift <= 4, "Shift out of bounds");

            typename detail::get_expr_nomask_nosign<V>::type ra;
            ra = a.wrapped().eval();
            return detail::insn::i_move4_l_wrapper<shift>::run(ra);
        }


        /** Moves the 64-bit elements in a vector to the left by @a shift positions.

            @code
            shift:  pos:| 0  1  |
             0      r = [ a0 a1 ]
             1      r = [ a1  0 ]
             2      r = [  0  0 ]
            @endcode

            @par 256-bit version:
            The lower and higher 128-bit halves are processed as if 128-bit instruction
            was applied to each of them separately.

            @icost{SSE2-AVX, NEON, ALTIVEC, 2}
        */
        template <unsigned shift, unsigned N, class V>
        inline typename detail::get_expr_nomask<V>::empty move2_l(const any_vec64<N, V> &a) {
            static_assert(shift <= 2, "Shift out of bounds");

            typename detail::get_expr_nomask_nosign<V>::type ra;
            ra = a.wrapped().eval();
            return detail::insn::i_move2_l_wrapper<shift>::run(ra);
        }

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
