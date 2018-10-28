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

#ifndef SIMD_CORE_TO_INT32_H
#define SIMD_CORE_TO_INT32_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/capabilities.h>
#include <bigmath/simd/detail/insn/conv_extend_to_int32.h>
#include <bigmath/simd/detail/insn/conv_shrink_to_int32.h>
#include <bigmath/simd/detail/insn/conv_float_to_int32.h>
#include <bigmath/simd/detail/not_implemented.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {

        /** Converts elements within a vector to 32-bit signed values.

            The conversion rules are as follows:
            16-bit and narrower signed integers are sign-extended to 32 bits.
            16-bit and narrower unsigned integers are zero-extended to 32 bits.
            64-bit integers are truncated.
            floating-point numbers are converted to integer values and truncated.
            If floating-point value can not be represented in 32-bit signed integer,
            the behavior is different for different instruction sets.

            SSE specific:
            If the value can not be represented by int32_t, @c 0x80000000 is returned
            TODO: NaN handling

            NEON, ALTIVEC specific:
            If the value can not be represented by int32_t, either @c 0x80000000 or @c
            0x7fffffff is returned depending on the sign of the operand (saturation
            occurs). Conversion of NaNs results in @a 0.

            @code
            r0 = (int32_t) a0
            ...
            rN = (int32_t) aN
            @endcode
        */
        template <unsigned N, class E> inline int32<N, expr_empty> to_int32(const int8<N, E> &a) {
            return detail::insn::i_to_int32(a.eval());
        }
        template <unsigned N, class E> inline int32<N, expr_empty> to_int32(const uint8<N, E> &a) {
            return (int32<N>)detail::insn::i_to_uint32(a.eval());
        }
        template <unsigned N, class E> inline int32<N, expr_empty> to_int32(const int16<N, E> &a) {
            return detail::insn::i_to_int32(a.eval());
        }
        template <unsigned N, class E> inline int32<N, expr_empty> to_int32(const uint16<N, E> &a) {
            return (int32<N>)detail::insn::i_to_uint32(a.eval());
        }
        template <unsigned N, class E> inline int32<N, expr_empty> to_int32(const int32<N, E> &a) {
            return a;
        }
        template <unsigned N, class E> inline int32<N, expr_empty> to_int32(const uint32<N, E> &a) {
            return int32<N>(a.eval());
        }
        template <unsigned N, class E> inline int32<N, expr_empty> to_int32(const int64<N, E> &a) {
            return detail::insn::i_to_uint32(uint64<N>(a.eval()));
        }
        template <unsigned N, class E> inline int32<N, expr_empty> to_int32(const uint64<N, E> &a) {
            return detail::insn::i_to_uint32(a.eval());
        }
        template <unsigned N, class E> inline int32<N, expr_empty> to_int32(const float32<N, E> &a) {
            return detail::insn::i_to_int32(a.eval());
        }
        template <unsigned N, class E> inline int32<N, expr_empty> to_int32(const float64<N, E> &a) {
            return detail::insn::i_to_int32(a.eval());
        }

        /** Converts elements within a vector to 32-bit unsigned values.

            The conversion rules are as follows:
            16-bit and narrower signed integers are sign-extended to 32 bits.
            16-bit and narrower unsigned integers are zero-extended to 32 bits.
            64-bit integers are truncated.
            If floating-point value can not be represented in 32-bit unsigned integer,
            the behavior is different for different instruction sets.

            SSE specific:
            If the value can not be represented by uint32_t, @c 0x80000000 is returned
            @todo NaN handling

            NEON VFP specific:
            If the value can not be represented by uint32_t, either @c 0x80000000 or @c
            0x7fffffff is returned depending on the sign of the operand. Conversion of
            NaNs results in @a 0.

            @code
            r0 = (uint32_t) a0
            ...
            rN = (uint32_t) aN
            @endcode
        */
        template <unsigned N, class E> inline uint32<N, expr_empty> to_uint32(const int8<N, E> &a) {
            return (uint32<N>)detail::insn::i_to_int32(a.eval());
        }
        template <unsigned N, class E> inline uint32<N, expr_empty> to_uint32(const uint8<N, E> &a) {
            return detail::insn::i_to_uint32(a.eval());
        }
        template <unsigned N, class E> inline uint32<N, expr_empty> to_uint32(const int16<N, E> &a) {
            return (uint32<N>)detail::insn::i_to_int32(a.eval());
        }
        template <unsigned N, class E> inline uint32<N, expr_empty> to_uint32(const uint16<N, E> &a) {
            return detail::insn::i_to_uint32(a.eval());
        }
        template <unsigned N, class E> inline uint32<N, expr_empty> to_uint32(const int32<N, E> &a) {
            return a.eval();
        }
        template <unsigned N, class E> inline uint32<N, expr_empty> to_uint32(const uint32<N, E> &a) {
            return a;
        }
        template <unsigned N, class E> inline uint32<N, expr_empty> to_uint32(const int64<N, E> &a) {
            return detail::insn::i_to_uint32(uint64<N>(a.eval()));
        }
        template <unsigned N, class E> inline uint32<N, expr_empty> to_uint32(const uint64<N, E> &a) {
            return detail::insn::i_to_uint32(a.eval());
        }
        template <unsigned N, class E> inline uint32<N, expr_empty> to_uint32(const float32<N, E> &a) {
            return detail::insn::i_to_uint32(a.eval());
        }
        template <unsigned N, class E> inline uint32<N, expr_empty> to_uint32(const float64<N, E> &a) {
#if SIMD_HAS_FLOAT64_TO_UINT32_CONVERSION
            return detail::insn::i_to_uint32(a.eval());
#else
            return SIMD_NOT_IMPLEMENTED_TEMPLATE1(E, a);
#endif
        }

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
