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

#ifndef SIMD_CORE_F_SIGN_H
#define SIMD_CORE_F_SIGN_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/insn/f_sign.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {


        /** Extracts sign bits from the values in float32x4 vector

            @code
            r0 = a0 & 0x80000000
            ...
            rN = aN & 0x80000000
            @endcode

            @par 128-bit version:
            @icost{SSE2-SSE4.1, ALTIVEC, NEON, 1-2}

            @par 256-bit version:
            @icost{SSE2-SSE4.1, ALTIVEC, NEON, 2-3}
            @icost{AVX-AVX2, 1-2}
        */
        template <unsigned N, class E> inline float32<N, expr_empty> sign(const float32<N, E> &a) {
            return detail::insn::i_sign(a.eval());
        }

        /** Extracts sigh bit from the values in float64x2 vector.

            @code
            r0 = a0 & 0x8000000000000000
            ...
            r0 = aN & 0x8000000000000000
            @endcode

            @par 128-bit version:
            @icost{SSE2-AVX2, 1-2}
            @novec{NEON, ALTIVEC}

            @par 256-bit version:
            @icost{SSE2-SSE4.1, 2-3}
            @icost{AVX-AVX2, 1-2}
            @novec{NEON, ALTIVEC}
        */
        template <unsigned N, class E> inline float64<N, expr_empty> sign(const float64<N, E> &a) {
            return detail::insn::i_sign(a.eval());
        }


    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
