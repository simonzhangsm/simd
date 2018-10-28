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

#ifndef SIMD_EXTRACT_H
#define SIMD_EXTRACT_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/insn/extract.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {

        /** Extracts the @a id-th element from a vector.

            @code
            r = a[id]
            @endcode

            This function may have very high latency.
        */
        template <unsigned id, unsigned N> inline uint8_t extract(const uint8<N> &a) {
            static_assert(id < N, "index out of bounds");
            return detail::insn::i_extract<id>(a);
        }

        template <unsigned id, unsigned N> inline int8_t extract(const int8<N> &a) {
            static_assert(id < N, "index out of bounds");
            return detail::insn::i_extract<id>(a);
        }

        template <unsigned id, unsigned N> inline uint16_t extract(const uint16<N> &a) {
            static_assert(id < N, "index out of bounds");
            return detail::insn::i_extract<id>(a);
        }

        template <unsigned id, unsigned N> inline int16_t extract(const int16<N> &a) {
            static_assert(id < N, "index out of bounds");
            return detail::insn::i_extract<id>(a);
        }

        template <unsigned id, unsigned N> inline uint32_t extract(const uint32<N> &a) {
            static_assert(id < N, "index out of bounds");
            return detail::insn::i_extract<id>(a);
        }

        template <unsigned id, unsigned N> inline int32_t extract(const int32<N> &a) {
            static_assert(id < N, "index out of bounds");
            return detail::insn::i_extract<id>(a);
        }

        template <unsigned id, unsigned N> inline uint64_t extract(const uint64<N> &a) {
            static_assert(id < N, "index out of bounds");
            return detail::insn::i_extract<id>(a);
        }

        template <unsigned id, unsigned N> inline int64_t extract(const int64<N> &a) {
            static_assert(id < N, "index out of bounds");
            return detail::insn::i_extract<id>(a);
        }

        template <unsigned id, unsigned N> inline float extract(const float32<N> &a) {
            static_assert(id < N, "index out of bounds");
            return detail::insn::i_extract<id>(a);
        }

        template <unsigned id, unsigned N> inline double extract(const float64<N> &a) {
            static_assert(id < N, "index out of bounds");
            return detail::insn::i_extract<id>(a);
        }

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
