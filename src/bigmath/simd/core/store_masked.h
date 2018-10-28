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

#ifndef SIMD_CORE_STORE_MASKED_H
#define SIMD_CORE_STORE_MASKED_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/insn/store_masked.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {

        /** Stores the first @a n elements of an 128-bit or 256-bit integer, 32-bit or
            64-bit floating point vector to memory. @a n must be in range [0..N-1]
            where @a N is the number of elements in the vector. If @a n is zero, no
            store is made.

            The pointer must be aligned to the native vector size.
        */
        template <class T, unsigned N, class V, class M>
        inline void store_masked(T *p, const any_int32<N, V> &a, const mask_int32<N, M> &mask) {
            uint32<N> ra;
            ra = a.wrapped().eval();
            detail::insn::i_store_masked(reinterpret_cast<char *>(p), ra, mask.wrapped().eval());
        }
        template <class T, unsigned N, class V, class M>
        inline void store_masked(T *p, const any_int64<N, V> &a, const mask_int64<N, M> &mask) {
            uint64<N> ra;
            ra = a.wrapped().eval();
            detail::insn::i_store_masked(reinterpret_cast<char *>(p), ra, mask.wrapped().eval());
        }
        template <class T, unsigned N, class V, class M>
        inline void store_masked(T *p, const any_float32<N, V> &a, const mask_float32<N, M> &mask) {
            float32<N> ra;
            ra = a.wrapped().eval();
            detail::insn::i_store_masked(reinterpret_cast<char *>(p), ra, mask.wrapped().eval());
        }
        template <class T, unsigned N, class V, class M>
        inline void store_masked(T *p, const any_float64<N, V> &a, const mask_float64<N, M> &mask) {
            float64<N> ra;
            ra = a.wrapped().eval();
            detail::insn::i_store_masked(reinterpret_cast<char *>(p), ra, mask.wrapped().eval());
        }

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
