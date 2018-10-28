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

#ifndef SIMD_CORE_COMBINE_H
#define SIMD_CORE_COMBINE_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/insn/combine.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {

        /** Combines two vectors into one twice as large. This function is useful when
            the ISA supports multiple vector sizes and the user does some operations
            with vectors that are narrower than the widest native vector.

            For example, on AVX, two __m128 vectors can be combined into a __m256
            vector.

            @todo icost
        */
        template <unsigned N, class E1, class E2>
        inline uint8<N * 2> combine(const uint8<N, E1> &a1, const uint8<N, E2> &a2) {
            return detail::insn::i_combine<uint8<N * 2>>(a1.eval(), a2.eval());
        }

        template <unsigned N, class E1, class E2>
        inline uint16<N * 2> combine(const uint16<N, E1> &a1, const uint16<N, E2> &a2) {
            return detail::insn::i_combine<uint16<N * 2>>(a1.eval(), a2.eval());
        }

        template <unsigned N, class E1, class E2>
        inline uint32<N * 2> combine(const uint32<N, E1> &a1, const uint32<N, E2> &a2) {
            return detail::insn::i_combine<uint32<N * 2>>(a1.eval(), a2.eval());
        }

        template <unsigned N, class E1, class E2>
        inline uint64<N * 2> combine(const uint64<N, E1> &a1, const uint64<N, E2> &a2) {
            return detail::insn::i_combine<uint64<N * 2>>(a1.eval(), a2.eval());
        }

        template <unsigned N, class E1, class E2>
        inline int8<N * 2> combine(const int8<N, E1> &a1, const int8<N, E2> &a2) {
            return detail::insn::i_combine<uint8<N * 2>>(uint8<N>(a1.eval()), uint8<N>(a2.eval()));
        }

        template <unsigned N, class E1, class E2>
        inline int16<N * 2> combine(const int16<N, E1> &a1, const int16<N, E2> &a2) {
            return detail::insn::i_combine<uint16<N * 2>>(uint16<N>(a1.eval()), uint16<N>(a2.eval()));
        }

        template <unsigned N, class E1, class E2>
        inline int32<N * 2> combine(const int32<N, E1> &a1, const int32<N, E2> &a2) {
            return detail::insn::i_combine<uint32<N * 2>>(uint32<N>(a1.eval()), uint32<N>(a2.eval()));
        }

        template <unsigned N, class E1, class E2>
        inline int64<N * 2> combine(const int64<N, E1> &a1, const int64<N, E2> &a2) {
            return detail::insn::i_combine<uint64<N * 2>>(uint64<N>(a1.eval()), uint64<N>(a2.eval()));
        }

        template <unsigned N, class E1, class E2>
        inline float32<N * 2> combine(const float32<N, E1> &a1, const float32<N, E2> &a2) {
            return detail::insn::i_combine<float32<N * 2>>(a1.eval(), a2.eval());
        }

        template <unsigned N, class E1, class E2>
        inline float64<N * 2> combine(const float64<N, E1> &a1, const float64<N, E2> &a2) {
            return detail::insn::i_combine<float64<N * 2>>(a1.eval(), a2.eval());
        }

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
