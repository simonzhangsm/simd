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

#ifndef SIMD_CORE_SPLAT_N_H
#define SIMD_CORE_SPLAT_N_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/insn/splat_n.h>
#include <bigmath/simd/detail/expr/splat_n.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {

        /** Broadcasts the specified 8-bit value to all elements within 128-bit lanes.

            @code
            r0 = a[s]
            r1 = a[s]
            ...
            rN = a[s]
            @endcode

            @par 128-bit version:
            @icost{SSE2-SSE3, 7}
            @icost{SSSE3-AVX, 1-2}
            @icost{AVX2, 2}

            @par 256-bit version:
            The lower and higher 128-bit halves are processed as if 128-bit instruction
            was applied to each of them separately.

            @icost{SSE2-SSE3, 14}
            @icost{SSSE3-AVX, 2-3}
            @icost{NEON, ALTIVEC, 2}
        */
        template <unsigned s, unsigned N, class E>
        inline int8<N, expr_splat16<s, int8<N, E>>> splat16(const int8<N, E> &a) {
            static_assert(s < 16, "Access out of bounds");
            return {{a}};
        }

        template <unsigned s, unsigned N, class E>
        inline uint8<N, expr_splat16<s, uint8<N, E>>> splat16(const uint8<N, E> &a) {
            static_assert(s < 16, "Access out of bounds");
            return {{a}};
        }

        /** Broadcasts the specified 16-bit value to all elements within 128-bit lanes.

            @code
            r0 = a[s]
            r1 = a[s]
            ...
            r7 = a[s]
            @endcode

            @par 128-bit version:
            @icost{SSE2-SSE3, 3}
            @icost{SSSE3-AVX, 1-2}
            @icost{AVX2, 2}

            @par 256-bit version:
            @icost{SSE2-SSE3, 6}
            @icost{SSSE3-AVX, 2-3}
            @icost{AVX2, NEON, ALTIVEC, 2}
        */
        template <unsigned s, unsigned N, class E>
        inline int16<N, expr_splat8<s, int16<N, E>>> splat8(const int16<N, E> &a) {
            static_assert(s < 8, "Access out of bounds");
            return {{a}};
        }

        template <unsigned s, unsigned N, class E>
        inline uint16<N, expr_splat8<s, uint16<N, E>>> splat8(const uint16<N, E> &a) {
            static_assert(s < 8, "Access out of bounds");
            return {{a}};
        }

        /** Broadcasts the specified 32-bit value to all elements within 128-bit lanes.

            @code
            r0 = a[s]
            r1 = a[s]
            r2 = a[s]
            r3 = a[s]
            @endcode

            @par 256-bit version:
            @icost{NEON, ALTIVEC, 2}
        */
        template <unsigned s, unsigned N, class E>
        inline int32<N, expr_splat4<s, int32<N, E>>> splat4(const int32<N, E> &a) {
            static_assert(s < 4, "Access out of bounds");
            return {{a}};
        }

        template <unsigned s, unsigned N, class E>
        inline uint32<N, expr_splat4<s, uint32<N, E>>> splat4(const uint32<N, E> &a) {
            static_assert(s < 4, "Access out of bounds");
            return {{a}};
        }

        /** Broadcasts the specified 64-bit value to all elements within 128-bit lanes.

            @code
            r0 = a[s]
            r1 = a[s]
            @endcode

            @par 128-bit version:
            @icost{ALTIVEC, 1-2}

            @par 256-bit version:
            @icost{SSE2-AVX, NEON, 2}
            @icost{ALTIVEC, 2-3}
        */
        template <unsigned s, unsigned N, class E>
        inline int64<N, expr_splat2<s, int64<N, E>>> splat2(const int64<N, E> &a) {
            static_assert(s < 2, "Access out of bounds");
            return {{a}};
        }

        template <unsigned s, unsigned N, class E>
        inline uint64<N, expr_splat2<s, uint64<N, E>>> splat2(const uint64<N, E> &a) {
            static_assert(s < 2, "Access out of bounds");
            return {{a}};
        }

        /** Broadcasts the specified 32-bit value to all elements within 128-bit lanes.

            @code
            r0 = a[s]
            r1 = a[s]
            r2 = a[s]
            r3 = a[s]
            @endcode

            @par 256-bit version:
            @icost{SSE2-AVX, NEON, ALTIVEC, 2}
        */
        template <unsigned s, unsigned N, class E>
        inline float32<N, expr_splat4<s, float32<N, E>>> splat4(const float32<N, E> &a) {
            static_assert(s < 4, "Access out of bounds");
            return {{a}};
        }

        /** Broadcasts the specified 64-bit value to all elements within 128-bit lanes.

            @code
            r0 = a[s]
            r1 = a[s]
            @endcode

            @par 128-bit version:
            @novec{NEON, ALTIVEC}

            @par 256-bit version:
            @icost{SSE2-AVX, 2}
            @novec{NEON, ALTIVEC}
        */
        template <unsigned s, unsigned N, class E>
        inline float64<N, expr_splat2<s, float64<N, E>>> splat2(const float64<N, E> &a) {
            static_assert(s < 2, "Access out of bounds");
            return {{a}};
        }

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
