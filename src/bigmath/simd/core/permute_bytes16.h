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

#ifndef SIMD_CORE_PERMUTE_BYTES16_H
#define SIMD_CORE_PERMUTE_BYTES16_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/get_expr.h>
#include <bigmath/simd/detail/insn/permute_bytes16.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {

        /** Selects bytes from a vector according to a mask. Each byte within the
            mask defines which element to select:
             * Bits 7-4 must be zero or the behavior is undefined
             * Bits 3-0 define the element within the given vector.
        */
        template <unsigned N, class V1, class E2>
        inline typename detail::get_expr_nomask<V1>::empty permute_bytes16(const any_vec8<N, V1> &a,
                                                                           const uint8<N, E2> &mask) {
            typename detail::get_expr_nomask<V1>::type ra = a.wrapped().eval();
            return detail::insn::i_permute_bytes16(ra, mask.eval());
        }

        template <unsigned N, class V1, class E2>
        inline typename detail::get_expr_nomask<V1>::empty permute_bytes16(const any_vec16<N, V1> &a,
                                                                           const uint16<N, E2> &mask) {
            typename detail::get_expr_nomask<V1>::type ra = a.wrapped().eval();
            return detail::insn::i_permute_bytes16(ra, mask.eval());
        }

        template <unsigned N, class V1, class E2>
        inline typename detail::get_expr_nomask<V1>::empty permute_bytes16(const any_vec32<N, V1> &a,
                                                                           const uint32<N, E2> &mask) {
            typename detail::get_expr_nomask<V1>::type ra = a.wrapped().eval();
            return detail::insn::i_permute_bytes16(ra, mask.eval());
        }

        template <unsigned N, class V1, class E2>
        inline typename detail::get_expr_nomask<V1>::empty permute_bytes16(const any_vec64<N, V1> &a,
                                                                           const uint64<N, E2> &mask) {
            typename detail::get_expr_nomask<V1>::type ra = a.wrapped().eval();
            return detail::insn::i_permute_bytes16(ra, mask.eval());
        }
    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
