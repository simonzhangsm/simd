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

#ifndef SIMD_CORE_I_AVG_H
#define SIMD_CORE_I_AVG_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/insn/i_avg.h>
#include <bigmath/simd/core/detail/scalar_arg_impl.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {


        /** Computes rounded average of the unsigned 8-bit values.

            @code
            r0 = (a0 + b0 + 1) / 2
            ...
            rN = (aN + bN + 1) / 2
            @endcode

            @par 256-bit version:
            @icost{SSE2-AVX, NEON, ALTIVEC, 2}
        */
        template <unsigned N, class E1, class E2>
        inline uint8<N, expr_empty> avg(const uint8<N, E1> &a, const uint8<N, E2> &b) {
            return detail::insn::i_avg(a.eval(), b.eval());
        }

        SIMD_SCALAR_ARG_IMPL_VEC(avg, uint8, uint8)

        /** Computes rounded average of signed 8-bit values.

            @code
            r0 = (a0 + b0 + 1) / 2
            ...
            rN = (aN + bN + 1) / 2
            @endcode

            @par 128-bit version:
            @icost{SSE2-AVX2, 4-5}

            @par 256-bit version:
            @icost{SSE2-AVX, 8-9}
            @icost{AVX2, 4-5}
            @icost{NEON, ALTIVEC, 2}
        */
        template <unsigned N, class E1, class E2>
        inline int8<N, expr_empty> avg(const int8<N, E1> &a, const int8<N, E2> &b) {
            return detail::insn::i_avg(a.eval(), b.eval());
        }

        SIMD_SCALAR_ARG_IMPL_VEC(avg, int8, int8)

        /** Computes rounded average of unsigned 16-bit values.

            @code
            r0 = (a0 + b0 + 1) / 2
            ...
            rN = (aN + bN + 1) / 2
            @endcode

            @par 256-bit version:
            @icost{SSE2-AVX, NEON, ALTIVEC, 2}
        */
        template <unsigned N, class E1, class E2>
        inline uint16<N, expr_empty> avg(const uint16<N, E1> &a, const uint16<N, E2> &b) {
            return detail::insn::i_avg(a.eval(), b.eval());
        }

        SIMD_SCALAR_ARG_IMPL_VEC(avg, uint16, uint16)

        /** Computes rounded average of signed 16-bit values.

            @code
            r0 = (a0 + b0 + 1) / 2
            ...
            rN = (aN + bN + 1) / 2
            @endcode

            @par 128-bit version:
            @icost{SSE2-AVX2, 4-5}

            @par 256-bit version:
            @icost{SSE2-AVX, 8-9}
            @icost{AVX2, 4-5}
            @icost{NEON, ALTIVEC, 2}
        */
        template <unsigned N, class E1, class E2>
        inline int16<N, expr_empty> avg(const int16<N, E1> &a, const int16<N, E2> &b) {
            return detail::insn::i_avg(a.eval(), b.eval());
        }

        SIMD_SCALAR_ARG_IMPL_VEC(avg, int16, int16)

        /** Computes rounded average of unsigned 32-bit values.

            @code
            r0 = (a0 + b0 + 1) / 2
            ...
            rN = (aN + bN + 1) / 2
            @endcode

            @par 128-bit version:
            @icost{SSE2-AVX2, 6-7}

            @par 256-bit version:
            @icost{SSE2-AVX, 12-13}
            @icost{AVX2, 6-7}
            @icost{NEON, ALTIVEC, 2}
        */
        template <unsigned N, class E1, class E2>
        inline uint32<N, expr_empty> avg(const uint32<N, E1> &a, const uint32<N, E2> &b) {
            return detail::insn::i_avg(a.eval(), b.eval());
        }

        SIMD_SCALAR_ARG_IMPL_VEC(avg, uint32, uint32)

        /** Computes rounded average of signed 32-bit values.

            @code
            r0 = (a0 + b0 + 1) / 2
            ...
            rN = (aN + bN + 1) / 2
            @endcode

            @par 128-bit version:
            @icost{SSE2-AVX2, 9-10}
            @icost{NEON, 1}

            @par 256-bit version:
            @icost{SSE2-AVX, 18-19}
            @icost{AVX2, 9-10}
            @icost{NEON, ALTIVEC, 2}
        */
        template <unsigned N, class E1, class E2>
        inline int32<N, expr_empty> avg(const int32<N, E1> &a, const int32<N, E2> &b) {
            return detail::insn::i_avg(a.eval(), b.eval());
        }

        SIMD_SCALAR_ARG_IMPL_VEC(avg, int32, int32)

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
