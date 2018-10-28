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

#ifndef SIMD_CORE_SPLAT_H
#define SIMD_CORE_SPLAT_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/insn/splat.h>
#include <bigmath/simd/detail/get_expr.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {

        /** Broadcasts the specified element to all elements.

            @code
            r0 = a[s]
            r1 = a[s]
            ...
            rN = a[s]
            @endcode

            @par int8

            @par 128-bit version:
            @icost{SSE2-AVX, 5}
            @icost{AVX2, 2}

            @par 256-bit version:
            @icost{SSE2-AVX, 6}
            @icost{NEON, ALTIVEC, 2}

            @par int16

            @par 128-bit version:
            @icost{SSE2-AVX, 5}
            @icost{AVX2, 2}

            @par 256-bit version:
            @icost{SSE2-AVX, 6}
            @icost{NEON, ALTIVEC, 2}

            @par int32

            @par 256-bit version:
            @icost{NEON, ALTIVEC, 2}

            @par int64

            @par 128-bit version:
            @icost{ALTIVEC, 1-2}

            @par 256-bit version:
            @icost{SSE2-AVX, NEON, 2}
            @icost{ALTIVEC, 1-2}

            @par float32

            @par 256-bit version:
            @icost{SSE2-AVX, NEON, ALTIVEC, 2}

            @par float64

            @par 128-bit version:
            @novec{NEON, ALTIVEC}

            @par 256-bit version:
            @icost{SSE2-AVX, 2}
            @novec{NEON, ALTIVEC}
        */
        template <unsigned s, unsigned N, class V>
        inline typename detail::get_expr_nomask<V>::empty splat(const any_vec<N, V> &a) {
            static_assert(s < V::length, "Access out of bounds");
            typename detail::get_expr_nomask<V>::type ra = a.wrapped().eval();
            return detail::insn::i_splat<s>(ra);
        }

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
