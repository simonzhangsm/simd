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

#ifndef SIMD_CORE_I_REDUCE_POPCNT_H
#define SIMD_CORE_I_REDUCE_POPCNT_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/insn/i_reduce_popcnt.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {


        /** Computes the population count of all values in the vector.

            @code
            result = popcnt(a0) + popcnt(a1) + ...
            @endcode
        */
        template <unsigned N, class E> inline uint32_t reduce_popcnt(const int8<N, E> &a) {
            return detail::insn::i_reduce_popcnt(uint32<N / 4>(a.eval()));
        }

        template <unsigned N, class E> inline uint32_t reduce_popcnt(const uint8<N, E> &a) {
            return detail::insn::i_reduce_popcnt(uint32<N / 4>(a.eval()));
        }

        template <unsigned N, class E> inline uint32_t reduce_popcnt(const int16<N, E> &a) {
            return detail::insn::i_reduce_popcnt(uint32<N / 2>(a.eval()));
        }

        template <unsigned N, class E> inline uint32_t reduce_popcnt(const uint16<N, E> &a) {
            return detail::insn::i_reduce_popcnt(uint32<N / 2>(a.eval()));
        }

        template <unsigned N, class E> inline uint32_t reduce_popcnt(const int32<N, E> &a) {
            return detail::insn::i_reduce_popcnt(uint32<N>(a.eval()));
        }

        template <unsigned N, class E> inline uint32_t reduce_popcnt(const uint32<N, E> &a) {
            return detail::insn::i_reduce_popcnt(a.eval());
        }

        template <unsigned N, class E> inline uint32_t reduce_popcnt(const int64<N, E> &a) {
            return detail::insn::i_reduce_popcnt(uint32<N * 2>(a.eval()));
        }

        template <unsigned N, class E> inline uint32_t reduce_popcnt(const uint64<N, E> &a) {
            return detail::insn::i_reduce_popcnt(uint32<N * 2>(a.eval()));
        }

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
