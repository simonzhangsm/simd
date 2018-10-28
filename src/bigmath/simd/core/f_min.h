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

#ifndef SIMD_CORE_F_MIN_H
#define SIMD_CORE_F_MIN_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/insn/f_min.h>
#include <bigmath/simd/core/detail/scalar_arg_impl.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {

        // note: SSE doesn't provide a way to propagate NaNs in min/max
        /** Computes minimum of the values in two vectors. If at least one of the
            values is NaN, or both values are zeroes, it is unspecified which value
            will be returned.

            @code
            r0 = min(a0, b0)
            ...
            rN = min(aN, bN)

            @endcode

            @par 256-bit version:
            @icost{SSE2-SSE4.1, NEON, ALTIVEC, 2}
        */
        template <unsigned N, class E1, class E2>
        inline float32<N, expr_empty> min(const float32<N, E1> &a, const float32<N, E2> &b) {
            return detail::insn::i_min(a.eval(), b.eval());
        }

        SIMD_SCALAR_ARG_IMPL_VEC(min, float32, float32)

        /** Computes minima of the values in two vectors. If at least one of the values
            is NaN, or both values are zeroes, it is unspecified which value will be
            returned.

            @code
            r0 = min(a0, b0)
            ...
            rN = min(aN, bN)
            @endcode

            @par 128-bit version:
            @novec{NEON, ALTIVEC}

            @par 256-bit version:
            @novec{NEON, ALTIVEC}
            @icost{SSE2-SSE4.1, 2}
        */
        template <unsigned N, class E1, class E2>
        inline float64<N, expr_empty> min(const float64<N, E1> &a, const float64<N, E2> &b) {
            return detail::insn::i_min(a.eval(), b.eval());
        }

        SIMD_SCALAR_ARG_IMPL_VEC(min, float64, float64)

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
