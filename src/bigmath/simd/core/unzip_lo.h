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

#ifndef SIMD_CORE_UNZIP_LO_H
#define SIMD_CORE_UNZIP_LO_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/insn/unzip_lo.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {

        /** De-interleaves the odd(lower) elements of two int8x16 vectors

            For example, in case of int8x16:

            @code
                | 0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  |
            r = [ a0  a2  a4  a6  a8  a10 a12 a14 b0  b2  b4  b6  b8  b10 b12 b14 ]
            @endcode

            @par int8

            @par 128-bit version:
            @icost{SSE2-AVX2, 4-5}
            @icost{ALTIVEC, 1-2}

            @par 256-bit version:
            The lower and higher 128-bit halves are processed as if 128-bit instruction
            was applied to each of them separately.

            @icost{SSE2-AVX, 8-9}
            @icost{NEON, 2}
            @icost{AVX2, 4-5}
            @icost{ALTIVEC, 2-3}

            @par int16

            @par 128-bit version:
            @icost{SSE2-SSSE3, 5}
            @icost{SSE4.1-AVX2, 4-5}
            @icost{ALTIVEC, 1-2}

            @par 256-bit version:
            The lower and higher 128-bit halves are processed as if 128-bit instruction
            was applied to each of them separately.

            @icost{SSE2-SSSE3, 5}
            @icost{SSE4.1-AVX, 8-9}
            @icost{AVX2, 4-5}
            @icost{NEON, 2}
            @icost{ALTIVEC, 2-3}

            @par int32

            @par 128-bit version:
            @icost{ALTIVEC, 1-2}

            @par 256-bit version:
            @icost{SSE2-AVX, NEON, 2}
            @icost{ALTIVEC, 2-3}

            The lower and higher 128-bit halves are processed as if 128-bit instruction
            was applied to each of them separately.

            @par int64

            @par 256-bit version:
            The lower and higher 128-bit halves are processed as if 128-bit instruction
            was applied to each of them separately.

            @icost{SSE2-AVX, NEON, ALTIVEC, 2}

            @par float32

            @par 256-bit version:
            The lower and higher 128-bit halves are processed as if 128-bit instruction
            was applied to each of them separately.

            @icost{SSE2-SSE4.1, NEON, ALTIVEC, 2}

            @par float64

            @par 128-bit version:
            @novec{NEON, ALTIVEC}

            @par 256-bit version:
            @icost{SSE2-AVX, 2}
            @novec{NEON, ALTIVEC}

            The lower and higher 128-bit halves are processed as if 128-bit instruction
            was applied to each of them separately.
        */
        template <unsigned N, class V1, class V2>
        inline typename detail::get_expr2_nomask<V1, V2>::empty unzip16_lo(const any_vec8<N, V1> &a,
                                                                           const any_vec8<N, V2> &b) {
            typename detail::get_expr2_nomask_nosign<V1, V2>::type ra, rb;
            ra = a.wrapped().eval();
            rb = b.wrapped().eval();
            return detail::insn::i_unzip16_lo(ra, rb);
        }

        template <unsigned N, class V1, class V2>
        inline typename detail::get_expr2_nomask<V1, V2>::empty unzip8_lo(const any_vec16<N, V1> &a,
                                                                          const any_vec16<N, V2> &b) {
            typename detail::get_expr2_nomask_nosign<V1, V2>::type ra, rb;
            ra = a.wrapped().eval();
            rb = b.wrapped().eval();
            return detail::insn::i_unzip8_lo(ra, rb);
        }

        template <unsigned N, class V1, class V2>
        inline typename detail::get_expr2_nomask<V1, V2>::empty unzip4_lo(const any_vec32<N, V1> &a,
                                                                          const any_vec32<N, V2> &b) {
            typename detail::get_expr2_nomask_nosign<V1, V2>::type ra, rb;
            ra = a.wrapped().eval();
            rb = b.wrapped().eval();
            return detail::insn::i_unzip4_lo(ra, rb);
        }

        template <unsigned N, class V1, class V2>
        inline typename detail::get_expr2_nomask<V1, V2>::empty unzip2_lo(const any_vec64<N, V1> &a,
                                                                          const any_vec64<N, V2> &b) {
            typename detail::get_expr2_nomask_nosign<V1, V2>::type ra, rb;
            ra = a.wrapped().eval();
            rb = b.wrapped().eval();
            return detail::insn::i_unzip2_lo(ra, rb);
        }

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
