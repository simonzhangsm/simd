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

#ifndef SIMD_CORE_LOAD_U_H
#define SIMD_CORE_LOAD_U_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/insn/load_u.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {

        /** Loads a 128-bit or 256-bit integer, 32-bit or 64-bit float vector from an
            unaligned memory location.

            @par 128-bit version:

            @code
            a[0..127] = *(p)
            @endcode

            @a p must be aligned to the element size. If @a p is aligned to 16 bytes
            only the referenced 16 byte block is accessed. Otherwise, memory within the
            smallest 16-byte aligned 32-byte block may be accessed.

            @icost{ALTIVEC, 4}

            @par 256-bit version:

            @code
            a[0..255] = *(p)
            @endcode
            @a p must be aligned to 32 bytes.
            @icost{SSE2-SSE4.1, NEON, 2}
            @icost{ALTIVEC, 6}

            @a p must be aligned to the element size. If @a p is aligned to 32 bytes
            only the referenced 16 byte block is accessed. Otherwise, memory within the
            smallest 32-byte aligned 64-byte block may be accessed.
        */
        // Fixme return empty expression
        template <class T> inline expr_vec_load_u load_u(const T *p) {
            return {reinterpret_cast<const char *>(p)};
        }

        template <class V, class T> inline V load_u(const T *p) {
            static_assert(is_vector<V>::value && !is_mask<V>::value, "V must be a non-mask vector");
            return detail::insn::i_load_u_any<V>(reinterpret_cast<const char *>(p));
        }
    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
