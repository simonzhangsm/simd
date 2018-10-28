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

#ifndef SIMD_CORE_I_REDUCE_ADD_H
#define SIMD_CORE_I_REDUCE_ADD_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/insn/i_reduce_add.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {


        /** Computes the sum of the elements in the vector. Intermediate and the
            final result has twice as many bits as the input element size in 8 and 16
            bit cases.

            @code
            r0 = a0 + a1 + a2 + ...
            @endcode
        */
        template <unsigned N, class E> inline int16_t reduce_add(const int8<N, E> &a) {
            return detail::insn::i_reduce_add(a.eval());
        }

        template <unsigned N, class E> inline uint16_t reduce_add(const uint8<N, E> &a) {
            return detail::insn::i_reduce_add(a.eval());
        }

        template <unsigned N, class E> inline int32_t reduce_add(const int16<N, E> &a) {
            return detail::insn::i_reduce_add(a.eval());
        }

        template <unsigned N, class E> inline uint32_t reduce_add(const uint16<N, E> &a) {
            return detail::insn::i_reduce_add(a.eval());
        }

        template <unsigned N, class E> inline int32_t reduce_add(const int32<N, E> &a) {
            return detail::insn::i_reduce_add(uint32<N>(a.eval()));
        }

        template <unsigned N, class E> inline uint32_t reduce_add(const uint32<N, E> &a) {
            return detail::insn::i_reduce_add(a.eval());
        }

        template <unsigned N, class E> inline int64_t reduce_add(const int64<N, E> &a) {
            return detail::insn::i_reduce_add(uint64<N>(a.eval()));
        }

        template <unsigned N, class E> inline uint64_t reduce_add(const uint64<N, E> &a) {
            return detail::insn::i_reduce_add(a.eval());
        }

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
