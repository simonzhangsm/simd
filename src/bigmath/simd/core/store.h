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

#ifndef SIMD_CORE_STORE_H
#define SIMD_CORE_STORE_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/insn/store.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {

        /** Stores a 128-bit or 256-bit integer vector to an aligned memory location.

            @par 128-bit version:

            @code
            *(p) = a[0..127]
            @endcode
            @a p must be aligned to 16 bytes.

            @par 256-bit version:

            @code
            *(p) = a[0..255]
            @endcode
            @a p must be aligned to 32 bytes.
            @icost{SSE2-SSE4.1, NEON, ALTIVEC, 2}
            @icost{AVX (integer vectors), 2}
        */
        template <class T, unsigned N, class V> inline void store(T *p, const any_vec<N, V> &a) {
            static_assert(!is_mask<V>::value, "Masks can not be stored"); // FIXME: automatically convert
            detail::insn::i_store(reinterpret_cast<char *>(p), a.wrapped().eval());
        }

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
