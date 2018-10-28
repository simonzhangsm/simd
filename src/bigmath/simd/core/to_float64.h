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

#ifndef SIMD_CORE_TO_FLOAT64_H
#define SIMD_CORE_TO_FLOAT64_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/capabilities.h>
#include <bigmath/simd/detail/insn/conv_any_to_float64.h>
#include <bigmath/simd/detail/not_implemented.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {

        /** Converts elements within a vector to 64-bit floating-point values.

            SSE specific:

            If only inexact conversion can be performed, the current rounding mode is
            used.

            NEON specific:

            If only inexact conversion can be performed, round to nearest mode is used.

            @code
            r0 = (double) a0
            ...
            rN = (double) aN
            @endcode
        */
        template <unsigned N, class E> inline float64<N, expr_empty> to_float64(const int8<N, E> &a) {
            return detail::insn::i_to_float64(a.eval());
        }
        template <unsigned N, class E> inline float64<N, expr_empty> to_float64(const uint8<N, E> &a) {
            return detail::insn::i_to_float64(a.eval());
        }
        template <unsigned N, class E> inline float64<N, expr_empty> to_float64(const int16<N, E> &a) {
            return detail::insn::i_to_float64(a.eval());
        }
        template <unsigned N, class E> inline float64<N, expr_empty> to_float64(const uint16<N, E> &a) {
            return detail::insn::i_to_float64(a.eval());
        }
        template <unsigned N, class E> inline float64<N, expr_empty> to_float64(const int32<N, E> &a) {
            return detail::insn::i_to_float64(a.eval());
        }
        template <unsigned N, class E> inline float64<N, expr_empty> to_float64(const uint32<N, E> &a) {
            return detail::insn::i_to_float64(a.eval());
        }
        template <unsigned N, class E> inline float64<N, expr_empty> to_float64(const int64<N, E> &a) {
#if SIMD_HAS_INT64_TO_FLOAT64_CONVERSION
            return detail::insn::i_to_float64(a.eval());
#else
            return SIMD_NOT_IMPLEMENTED_TEMPLATE1(E, a);
#endif
        }
        template <unsigned N, class E> inline float64<N, expr_empty> to_float64(const uint64<N, E> &a) {
#if SIMD_HAS_UINT64_TO_FLOAT64_CONVERSION
            return detail::insn::i_to_float64(a.eval());
#else
            return SIMD_NOT_IMPLEMENTED_TEMPLATE1(E, a);
#endif
        }
        template <unsigned N, class E> inline float64<N, expr_empty> to_float64(const float32<N, E> &a) {
            return detail::insn::i_to_float64(a.eval());
        }
        template <unsigned N, class E> inline float64<N, expr_empty> to_float64(const float64<N, E> &a) {
            return a;
        }

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
