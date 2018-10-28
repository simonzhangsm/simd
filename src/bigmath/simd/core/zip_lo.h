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

#ifndef SIMD_CORE_ZIP_LO_H
#define SIMD_CORE_ZIP_LO_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/insn/zip_lo.h>
#include <bigmath/simd/detail/get_expr.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {

        /** Interleaves the lower halves of two vectors.

            @code
                | 0  1  2  3  4  5  ... N-2      N-1      |
            r = [ a0 b0 a1 b1 a2 b2 ... a(N/2-1) b(N/2-1) ]
            @endcode

            @par 256-bit version:
            The lower and higher 128-bit halves are processed as if 128-bit instruction
            was applied to each of them separately.

            @icost{SSE2-AVX, NEON, ALTIVEC, 2}
        */
        template <unsigned N, class V1, class V2>
        inline typename detail::get_expr2_nomask<V1, V2>::empty zip16_lo(const any_vec8<N, V1> &a,
                                                                         const any_vec8<N, V2> &b) {
            typename detail::get_expr2_nomask_nosign<V1, V2>::type ra, rb;
            ra = a.wrapped().eval();
            rb = b.wrapped().eval();
            return detail::insn::i_zip16_lo(ra, rb);
        }

        template <unsigned N, class V1, class V2>
        inline typename detail::get_expr2_nomask<V1, V2>::empty zip8_lo(const any_vec16<N, V1> &a,
                                                                        const any_vec16<N, V2> &b) {
            typename detail::get_expr2_nomask_nosign<V1, V2>::type ra, rb;
            ra = a.wrapped().eval();
            rb = b.wrapped().eval();
            return detail::insn::i_zip8_lo(ra, rb);
        }

        template <unsigned N, class V1, class V2>
        inline typename detail::get_expr2_nomask<V1, V2>::empty zip4_lo(const any_vec32<N, V1> &a,
                                                                        const any_vec32<N, V2> &b) {
            typename detail::get_expr2_nomask_nosign<V1, V2>::type ra, rb;
            ra = a.wrapped().eval();
            rb = b.wrapped().eval();
            return detail::insn::i_zip4_lo(ra, rb);
        }

        template <unsigned N, class V1, class V2>
        inline typename detail::get_expr2_nomask<V1, V2>::empty zip2_lo(const any_vec64<N, V1> &a,
                                                                        const any_vec64<N, V2> &b) {
            typename detail::get_expr2_nomask_nosign<V1, V2>::type ra, rb;
            ra = a.wrapped().eval();
            rb = b.wrapped().eval();
            return detail::insn::i_zip2_lo(ra, rb);
        }

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
