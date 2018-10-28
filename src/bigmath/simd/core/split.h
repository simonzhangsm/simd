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

#ifndef SIMD_CORE_SPLIT_H
#define SIMD_CORE_SPLIT_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/insn/split.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {

        namespace detail {

            template <class A, class R> inline void v256_split(A a, R &r1, R &r2) {
#if SIMD_USE_AVX2
                r1 = _mm256_extracti128_si256(a.native(), 0);
                r2 = _mm256_extracti128_si256(a.native(), 1);
#else
                r1 = a[0];
                r2 = a[1];
#endif
            }

        } // namespace detail

        /** Splits a vector into two vectors half as wide. This function is useful when
            the ISA supports multiple vector sizes and the user does some operations
            with vectors that are narrower than the widest native vector.

            For example, on AVX, a __m256 vector can be split into two __m128 vectors.

            @code
            [ r1, r2 ] = a
            @endcode

            @icost{AVX2, 1}
            @icost{SSE2-AVX, NEON, ALTIVEC, 0}
        */
        template <unsigned N> inline void split(const uint8<N> &a, uint8<N / 2> &r1, uint8<N / 2> &r2) {
            detail::insn::i_split(a, r1, r2);
        }

        template <unsigned N> inline void split(const uint16<N> &a, uint16<N / 2> &r1, uint16<N / 2> &r2) {
            detail::insn::i_split(a, r1, r2);
        }

        template <unsigned N> inline void split(const uint32<N> &a, uint32<N / 2> &r1, uint32<N / 2> &r2) {
            detail::insn::i_split(a, r1, r2);
        }

        template <unsigned N> inline void split(const uint64<N> &a, uint64<N / 2> &r1, uint64<N / 2> &r2) {
            detail::insn::i_split(a, r1, r2);
        }

        template <unsigned N> inline void split(const int8<N> &a, int8<N / 2> &r1, int8<N / 2> &r2) {
            uint8<N / 2> q1, q2;
            q1 = r1;
            q2 = r2;
            detail::insn::i_split(uint8<N>(a), q1, q2);
            r1 = q1;
            r2 = q2;
        }

        template <unsigned N> inline void split(const int16<N> &a, int16<N / 2> &r1, int16<N / 2> &r2) {
            uint16<N / 2> q1, q2;
            q1 = r1;
            q2 = r2;
            detail::insn::i_split(uint16<N>(a), q1, q2);
            r1 = q1;
            r2 = q2;
        }

        template <unsigned N> inline void split(const int32<N> &a, int32<N / 2> &r1, int32<N / 2> &r2) {
            uint32<N / 2> q1, q2;
            q1 = r1;
            q2 = r2;
            detail::insn::i_split(uint32<N>(a), q1, q2);
            r1 = q1;
            r2 = q2;
        }

        template <unsigned N> inline void split(const int64<N> &a, int64<N / 2> &r1, int64<N / 2> &r2) {
            uint64<N / 2> q1, q2;
            q1 = r1;
            q2 = r2;
            detail::insn::i_split(uint64<N>(a), q1, q2);
            r1 = q1;
            r2 = q2;
        }

        template <unsigned N> inline void split(const float32<N> &a, float32<N / 2> &r1, float32<N / 2> &r2) {
            detail::insn::i_split(a, r1, r2);
        }

        template <unsigned N> inline void split(const float64<N> &a, float64<N / 2> &r1, float64<N / 2> &r2) {
            detail::insn::i_split(a, r1, r2);
        }

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
