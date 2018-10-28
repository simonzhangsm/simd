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

#ifndef SIMD_CORE_I_NEG_H
#define SIMD_CORE_I_NEG_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/expr/i_neg.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {

        /** Negates signed 8-bit values.

            @code
            r0 = -a0
            ...
            rN = -aN
            @endcode

            @par 256-bit version:
            @icost{SSE2-AVX, NEON, ALTIVEC, 2}
        */
        template <unsigned N, class E> inline int8<N, expr_ineg<int8<N, E>>> neg(const int8<N, E> &a) {
            return {{a}};
        }

        /** Negates signed 16-bit values.

            @code
            r0 = -a0
            ...
            rN = -aN
            @endcode

            @par 256-bit version:
            @icost{SSE2-AVX, NEON, ALTIVEC, 2}
        */
        template <unsigned N, class E> inline int16<N, expr_ineg<int16<N, E>>> neg(const int16<N, E> &a) {
            return {{a}};
        }

        /** Negates signed 32-bit values.

            @code
            r0 = -a0
            ...
            rN = -aN
            @endcode

            @par 256-bit version:
            @icost{SSE2-AVX, NEON, ALTIVEC, 2}
        */
        template <unsigned N, class E> inline int32<N, expr_ineg<int32<N, E>>> neg(const int32<N, E> &a) {
            return {{a}};
        }

        /** Negates signed 64-bit values.

            @code
            r0 = -a0
            ...
            rN = -aN
            @endcode

            @par 128-bit version:
            @icost{ALTIVEC, 4-5}

            @par 256-bit version:
            @icost{SSE2-AVX, NEON, 2}
            @icost{ALTIVEC, 8-9}
        */
        template <unsigned N, class E> inline int64<N, expr_ineg<int64<N, E>>> neg(const int64<N, E> &a) {
            return {{a}};
        }

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
