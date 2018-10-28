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

#ifndef SIMD_CORE_I_ABS_H
#define SIMD_CORE_I_ABS_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/expr/i_abs.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {

        /** Computes absolute value of 8-bit integer values.

            @code
            r0 = abs(a0)
            ...
            rN = abs(aN)
            @endcode

            @par 128-bit version:
            @icost{SSE2-SSE3, 3}
            @icost{ALTIVEC, 1-3}

            @par 256-bit version:
            @icost{SSE2-SSE3, 6}
            @icost{SSSE3-AVX, NEON, 2}
            @icost{ALTIVEC, 2-4}
        */
        template <unsigned N, class E> inline uint8<N, expr_iabs<int8<N, E>>> abs(const int8<N, E> &a) {
            return {{a}};
        }


        /** Computes absolute value of 16-bit integer values.

            @code
            r0 = abs(a0)
            ...
            rN = abs(aN)
            @endcode
            @par 128-bit version:
            @icost{SSE2-SSE3, 3}
            @icost{ALTIVEC, 1-3}

            @par 256-bit version:
            @icost{SSE2-SSE3, 6}
            @icost{SSSE3-AVX, NEON, 2}
            @icost{ALTIVEC, 2-5}
        */
        template <unsigned N, class E> inline uint16<N, expr_iabs<int16<N, E>>> abs(const int16<N, E> &a) {
            return {{a}};
        }

        /** Computes absolute value of 32-bit integer values.

            @code
            r0 = abs(a0)
            ...
            rN = abs(aN)
            @endcode
            @par 128-bit version:
            @icost{SSE2-SSE3, 3}
            @icost{ALTIVEC, 1-3}

            @par 256-bit version:
            @icost{SSE2-SSE3, 6}
            @icost{SSSE3-AVX, NEON, 2}
            @icost{ALTIVEC, 2-4}
        */
        template <unsigned N, class E> inline uint32<N, expr_iabs<int32<N, E>>> abs(const int32<N, E> &a) {
            return {{a}};
        }

        /** Computes absolute value of 64-bit integer values.

            @code
            r0 = abs(a0)
            ...
            rN = abs(aN)
            @endcode
            @par 128-bit version:
            @icost{SSE2-AVX, 5}
            @icost{NEON, 6}
            @novec{ALTIVEC}

            @par 256-bit version:
            @icost{SSE2-AVX, 10}
            @icost{NEON, 12}
            @icost{AVX2, 4}
            @novec{ALTIVEC}
        */
        template <unsigned N, class E> inline uint64<N, expr_iabs<int64<N, E>>> abs(const int64<N, E> &a) {
            return {{a}};
        }

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
