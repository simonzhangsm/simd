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

#ifndef SIMD_CORE_TO_INT16_H
#define SIMD_CORE_TO_INT16_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/insn/conv_extend_to_int16.h>
#include <bigmath/simd/detail/insn/conv_shrink_to_int16.h>
#include <bigmath/simd/detail/insn/conv_float_to_int16.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {


        /** Converts elements within a vector to 16-bit signed values.

            The conversion rules are as follows:
            8-bit signed integers are sign-extended to 16 bits.
            8-bit unsigned integers are zero-extended to 16 bits.
            32-bit and wider integers are truncated.
            floating-point numbers are converted to integer values and truncated.
            If floating-point value can not be represented in 16-bit signed integer,
            the behavior is different for different instruction sets.

            @code
            r0 = (int16_t) a0
            ...
            rN = (int16_t) aN
            @endcode
        */
        template <unsigned N, class E> inline int16<N, expr_empty> to_int16(const int8<N, E> &a) {
            return detail::insn::i_to_int16(a.eval());
        }
        template <unsigned N, class E> inline int16<N, expr_empty> to_int16(const uint8<N, E> &a) {
            return (int16<N>)detail::insn::i_to_uint16(a.eval());
        }
        template <unsigned N, class E> inline int16<N, expr_empty> to_int16(const int16<N, E> &a) {
            return a.eval();
        }
        template <unsigned N, class E> inline int16<N, expr_empty> to_int16(const uint16<N, E> &a) {
            return int16<N>(a.eval());
        }
        template <unsigned N, class E> inline int16<N, expr_empty> to_int16(const int32<N, E> &a) {
            return detail::insn::i_to_uint16(uint32<N>(a.eval()));
        }
        template <unsigned N, class E> inline int16<N, expr_empty> to_int16(const uint32<N, E> &a) {
            return detail::insn::i_to_uint16(a.eval());
        }
        template <unsigned N, class E> inline int16<N, expr_empty> to_int16(const int64<N, E> &a) {
            return detail::insn::i_to_uint16(uint64<N>(a.eval()));
        }
        template <unsigned N, class E> inline int16<N, expr_empty> to_int16(const uint64<N, E> &a) {
            return detail::insn::i_to_uint16(a.eval());
        }
        template <unsigned N, class E> inline int16<N, expr_empty> to_int16(const float32<N, E> &a) {
            return detail::insn::i_to_int16(a.eval());
        }
        template <unsigned N, class E> inline int16<N, expr_empty> to_int16(const float64<N, E> &a) {
            return detail::insn::i_to_int16(a.eval());
        }

        /** Converts elements within a vector to 16-bit unsigned values.

            The conversion rules are as follows:
            8-bit signed integers are sign-extended to 16 bits.
            8-bit unsigned integers are zero-extended to 16 bits.
            32-bit and wider integers are truncated.
            If floating-point value can not be represented in 16-bit unsigned integer,
            the behavior is different for different instruction sets.

            @code
            r0 = (uint16_t) a0
            ...
            rN = (uint16_t) aN
            @endcode
        */
        template <unsigned N, class E> inline uint16<N, expr_empty> to_uint16(const int8<N, E> &a) {
            return (uint16<N>)detail::insn::i_to_int16(a.eval());
        }
        template <unsigned N, class E> inline uint16<N, expr_empty> to_uint16(const uint8<N, E> &a) {
            return detail::insn::i_to_uint16(a.eval());
        }
        template <unsigned N, class E> inline uint16<N, expr_empty> to_uint16(const int16<N, E> &a) {
            return uint16<N>(a.eval());
        }
        template <unsigned N, class E> inline uint16<N, expr_empty> to_uint16(const uint16<N, E> &a) {
            return a.eval();
        }
        template <unsigned N, class E> inline uint16<N, expr_empty> to_uint16(const int32<N, E> &a) {
            return detail::insn::i_to_uint16(uint32<N>(a.eval()));
        }
        template <unsigned N, class E> inline uint16<N, expr_empty> to_uint16(const uint32<N, E> &a) {
            return detail::insn::i_to_uint16(a.eval());
        }
        template <unsigned N, class E> inline uint16<N, expr_empty> to_uint16(const int64<N, E> &a) {
            return detail::insn::i_to_uint16(uint64<N>(a.eval()));
        }
        template <unsigned N, class E> inline uint16<N, expr_empty> to_uint16(const uint64<N, E> &a) {
            return detail::insn::i_to_uint16(a.eval());
        }
        template <unsigned N, class E> inline uint16<N, expr_empty> to_uint16(const float32<N, E> &a) {
            return detail::insn::i_to_uint16(a.eval());
        }
        template <unsigned N, class E> inline uint16<N, expr_empty> to_uint16(const float64<N, E> &a) {
            return detail::insn::i_to_uint16(a.eval());
        }

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
