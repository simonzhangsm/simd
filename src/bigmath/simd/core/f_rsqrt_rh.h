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

#ifndef SIMD_CORE_F_RSQRT_RH_H
#define SIMD_CORE_F_RSQRT_RH_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/insn/f_rsqrt_rh.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {


        /** Computes one Newton-Rhapson iteration for inverse of square root. @a x is
            the current estimate, @a a are the values to estimate the inverse square
            root for.

            @code
            r0 = x0 * (3 - a0*x0*x0) * 0.5
            ...
            rN = xN * (3 - aN*xN*xN) * 0.5
            @endcode

            @par 128-bit version:
            @icost{SSE2, SSE3, SSSE3, SSE4.1, 5-7}
            @icost{NEON, 3}
            @icost{ALTIVEC, 4-6}

            @par 256-bit version:
            @icost{AVX-AVX2, 7}
            @icost{SSE2, SSE3, SSSE3, SSE4.1, 10-12}
            @icost{NEON, 6}
            @icost{ALTIVEC, 8-10}
        */
        template <unsigned N, class E>
        inline float32<N, expr_empty> rsqrt_rh(const float32<N, E> &x, const float32<N, E> &a) {
            return detail::insn::i_rsqrt_rh(x.eval(), a.eval());
        }

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
