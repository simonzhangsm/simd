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

#ifndef SIMD_CORE_I_SHIFT_L_H
#define SIMD_CORE_I_SHIFT_L_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/capabilities.h>
#include <bigmath/simd/detail/insn/i_shift_l.h>
#include <bigmath/simd/detail/insn/i_shift_l_v.h>
#include <bigmath/simd/detail/not_implemented.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {

        // -----------------------------------------------------------------------------
        // shift by scalar

        /** Shifts 8-bit values left by @a count bits while shifting in zeros.

            @code
            r0 = a0 << count
            ...
            rN = aN << count
            @endcode
        */
        template <unsigned N, class E> inline int8<N, expr_empty> shift_l(const int8<N, E> &a, unsigned count) {
            uint8<N> qa = a.eval();
            return detail::insn::i_shift_l(qa, count);
        }

        template <unsigned N, class E> inline uint8<N, expr_empty> shift_l(const uint8<N, E> &a, unsigned count) {
            return detail::insn::i_shift_l(a.eval(), count);
        }

        /** Shifts 16-bit values left by @a count bits while shifting in zeros.

            @code
            r0 = a0 << count
            ...
            rN = aN << count
            @endcode
        */
        template <unsigned N, class E> inline int16<N, expr_empty> shift_l(const int16<N, E> &a, unsigned count) {
            uint16<N> qa = a.eval();
            return detail::insn::i_shift_l(qa, count);
        }

        template <unsigned N, class E> inline uint16<N, expr_empty> shift_l(const uint16<N, E> &a, unsigned count) {
            return detail::insn::i_shift_l(a.eval(), count);
        }

        /** Shifts 32-bit values left by @a count bits while shifting in zeros.

            @code
            r0 = a0 << count
            ...
            rN = aN << count
            @endcode
        */
        template <unsigned N, class E> inline int32<N, expr_empty> shift_l(const int32<N, E> &a, unsigned count) {
            uint32<N> qa = a.eval();
            return detail::insn::i_shift_l(qa, count);
        }

        template <unsigned N, class E> inline uint32<N, expr_empty> shift_l(const uint32<N, E> &a, unsigned count) {
            return detail::insn::i_shift_l(a.eval(), count);
        }

        /** Shifts 64-bit values left by @a count bits while shifting in zeros.

            @code
            r0 = a0 << count
            ...
            rN = aN << count
            @endcode
        */
        template <unsigned N, class E> inline int64<N, expr_empty> shift_l(const int64<N, E> &a, unsigned count) {
            uint64<N> qa = a.eval();
            return detail::insn::i_shift_l(qa, count);
        }

        template <unsigned N, class E> inline uint64<N, expr_empty> shift_l(const uint64<N, E> &a, unsigned count) {
            return detail::insn::i_shift_l(a.eval(), count);
        }

        // -----------------------------------------------------------------------------
        // shift by vector

        /** Shifts 8-bit values left by the number of bits in corresponding element
            in the given count vector. Zero bits are shifted in.

            @code
            r0 = a0 << count0
            ...
            rN = aN << countN
            @endcode
        */
        template <unsigned N, class E>
        inline int8<N, expr_empty> shift_l(const int8<N, E> &a, const uint8<N, E> &count) {
#if SIMD_HAS_INT8_SHIFT_R_BY_VECTOR
            uint8<N> qa = a.eval();
            return detail::insn::i_shift_l_v(qa, count.eval());
#else
            return SIMD_NOT_IMPLEMENTED_TEMPLATE2(E, a, count);
#endif
        }

        template <unsigned N, class E>
        inline uint8<N, expr_empty> shift_l(const uint8<N, E> &a, const uint8<N, E> &count) {
#if SIMD_HAS_UINT8_SHIFT_R_BY_VECTOR
            return detail::insn::i_shift_l_v(a.eval(), count.eval());
#else
            return SIMD_NOT_IMPLEMENTED_TEMPLATE2(E, a, count);
#endif
        }

        /** Shifts 16-bit values left by the number of bits in corresponding element
            in the given count vector. Zero bits are shifted in.

            @code
            r0 = a0 << count0
            ...
            rN = aN << countN
            @endcode
        */
        template <unsigned N, class E>
        inline int16<N, expr_empty> shift_l(const int16<N, E> &a, const uint16<N, E> &count) {
#if SIMD_HAS_INT16_SHIFT_R_BY_VECTOR
            uint16<N> qa = a.eval();
            return detail::insn::i_shift_l_v(qa, count.eval());
#else
            return SIMD_NOT_IMPLEMENTED_TEMPLATE2(E, a, count);
#endif
        }

        template <unsigned N, class E>
        inline uint16<N, expr_empty> shift_l(const uint16<N, E> &a, const uint16<N, E> &count) {
#if SIMD_HAS_UINT16_SHIFT_R_BY_VECTOR
            return detail::insn::i_shift_l_v(a.eval(), count.eval());
#else
            return SIMD_NOT_IMPLEMENTED_TEMPLATE2(E, a, count);
#endif
        }

        /** Shifts 32-bit values left by the number of bits in corresponding element
            in the given count vector. Zero bits are shifted in.

            @code
            r0 = a0 << count0
            ...
            rN = aN << countN
            @endcode
        */
        template <unsigned N, class E>
        inline int32<N, expr_empty> shift_l(const int32<N, E> &a, const uint32<N, E> &count) {
#if SIMD_HAS_INT32_SHIFT_R_BY_VECTOR
            uint32<N> qa = a.eval();
            return detail::insn::i_shift_l_v(qa, count.eval());
#else
            return SIMD_NOT_IMPLEMENTED_TEMPLATE2(E, a, count);
#endif
        }

        template <unsigned N, class E>
        inline uint32<N, expr_empty> shift_l(const uint32<N, E> &a, const uint32<N, E> &count) {
#if SIMD_HAS_UINT32_SHIFT_R_BY_VECTOR
            return detail::insn::i_shift_l_v(a.eval(), count.eval());
#else
            return SIMD_NOT_IMPLEMENTED_TEMPLATE2(E, a, count);
#endif
        }

        // -----------------------------------------------------------------------------
        // shift by compile-time constant

        /** Shifts 8-bit values left by @a count bits while shifting in zeros.

            @code
            r0 = a0 << count
            ...
            rN = aN << count
            @endcode
        */
        template <unsigned count, unsigned N, class E> inline int8<N, expr_empty> shift_l(const int8<N, E> &a) {
            static_assert(count < 8, "Shift out of bounds");
            uint8<N> qa = a.eval();
            return detail::insn::i_shift_l_wrapper<count == 0>::template run<count>(qa);
        }

        template <unsigned count, unsigned N, class E> inline uint8<N, expr_empty> shift_l(const uint8<N, E> &a) {
            static_assert(count < 8, "Shift out of bounds");
            return detail::insn::i_shift_l_wrapper<count == 0>::template run<count>(a.eval());
        }

        /** Shifts 16-bit values left by @a count bits while shifting in zeros.

            @code
            r0 = a0 << count
            ...
            rN = aN << count
            @endcode
        */
        template <unsigned count, unsigned N, class E> inline int16<N, expr_empty> shift_l(const int16<N, E> &a) {
            static_assert(count < 16, "Shift out of bounds");
            uint16<N> qa = a.eval();
            return detail::insn::i_shift_l_wrapper<count == 0>::template run<count>(qa);
        }

        template <unsigned count, unsigned N, class E> inline uint16<N, expr_empty> shift_l(const uint16<N, E> &a) {
            static_assert(count < 16, "Shift out of bounds");
            return detail::insn::i_shift_l_wrapper<count == 0>::template run<count>(a.eval());
        }

        /** Shifts 32-bit values left by @a count bits while shifting in zeros.

            @code
            r0 = a0 << count
            ...
            rN = aN << count
            @endcode
        */
        template <unsigned count, unsigned N, class E> inline int32<N, expr_empty> shift_l(const int32<N, E> &a) {
            static_assert(count < 32, "Shift out of bounds");
            uint32<N> qa = a.eval();
            return detail::insn::i_shift_l_wrapper<count == 0>::template run<count>(qa);
        }

        template <unsigned count, unsigned N, class E> inline uint32<N, expr_empty> shift_l(const uint32<N, E> &a) {
            static_assert(count < 32, "Shift out of bounds");
            return detail::insn::i_shift_l_wrapper<count == 0>::template run<count>(a.eval());
        }

        /** Shifts 64-bit values left by @a count bits while shifting in zeros.

            @code
            r0 = a0 << count
            ...
            rN = aN << count
            @endcode
        */
        template <unsigned count, unsigned N, class E> inline int64<N, expr_empty> shift_l(const int64<N, E> &a) {
            static_assert(count < 64, "Shift out of bounds");
            uint64<N> qa = a.eval();
            return detail::insn::i_shift_l_wrapper<count == 0>::template run<count>(qa);
        }

        template <unsigned count, unsigned N, class E> inline uint64<N, expr_empty> shift_l(const uint64<N, E> &a) {
            static_assert(count < 64, "Shift out of bounds");
            return detail::insn::i_shift_l_wrapper<count == 0>::template run<count>(a.eval());
        }

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
