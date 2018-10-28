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

#ifndef SIMD_INSERT_H
#define SIMD_INSERT_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/insn/insert.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {


        /** Inserts an element into a vector at the position identified by @a id.

            @code
            r0 = (id == 0) ? x : a0
            ...
            rN = (id == N) ? x : aN
            @endcode

            This function may have very high latency.
            It is expected that the argument comes from a general-purpose register.
        */
        template <unsigned id, unsigned N> inline uint8<N> insert(const uint8<N> &a, uint8_t x) {
            static_assert(id < N, "index out of bounds");
            return detail::insn::i_insert<id>(a, x);
        }

        template <unsigned id, unsigned N> inline int8<N> insert(const int8<N> &a, int8_t x) {
            static_assert(id < N, "index out of bounds");
            return (int8<N>)detail::insn::i_insert<id>((uint8<N>)a, (uint8_t)x);
        }

        template <unsigned id, unsigned N> inline uint16<N> insert(const uint16<N> &a, uint16_t x) {
            static_assert(id < N, "index out of bounds");
            return detail::insn::i_insert<id>(a, x);
        }

        template <unsigned id, unsigned N> inline int16<N> insert(const int16<N> &a, int16_t x) {
            static_assert(id < N, "index out of bounds");
            return (int16<N>)detail::insn::i_insert<id>((uint16<N>)a, (uint16_t)x);
        }

        template <unsigned id, unsigned N> inline uint32<N> insert(const uint32<N> &a, uint32_t x) {
            static_assert(id < N, "index out of bounds");
            return detail::insn::i_insert<id>(a, x);
        }

        template <unsigned id, unsigned N> inline int32<N> insert(const int32<N> &a, int32_t x) {
            static_assert(id < N, "index out of bounds");
            return (int32<N>)detail::insn::i_insert<id>((uint32<N>)a, (uint32_t)x);
        }

        template <unsigned id, unsigned N> inline uint64<N> insert(const uint64<N> &a, uint64_t x) {
            static_assert(id < N, "index out of bounds");
            return detail::insn::i_insert<id>(a, x);
        }

        template <unsigned id, unsigned N> inline int64<N> insert(const int64<N> &a, int64_t x) {
            static_assert(id < N, "index out of bounds");
            return (int64<N>)detail::insn::i_insert<id>((uint64<N>)a, (uint64_t)x);
        }

        template <unsigned id, unsigned N> inline float32<N> insert(const float32<N> &a, float x) {
            static_assert(id < N, "index out of bounds");
            return detail::insn::i_insert<id>(a, x);
        }

        template <unsigned id, unsigned N> inline float64<N> insert(const float64<N> &a, double x) {
            static_assert(id < N, "index out of bounds");
            return detail::insn::i_insert<id>(a, x);
        }


    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
