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

#ifndef SIMD_DETAIL_INSN_I_SHIFT_H
#define SIMD_DETAIL_INSN_I_SHIFT_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>

// this file contains forward declarations of shift functions for internal use
// from within shift implementation

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {

        template <unsigned N, class E> inline uint8<N, expr_empty> shift_l(const uint8<N, E> &a, unsigned count);
        template <unsigned N, class E> inline uint16<N, expr_empty> shift_l(const uint16<N, E> &a, unsigned count);
        template <unsigned N, class E> inline uint32<N, expr_empty> shift_l(const uint32<N, E> &a, unsigned count);
        template <unsigned N, class E> inline uint64<N, expr_empty> shift_l(const uint64<N, E> &a, unsigned count);

        template <unsigned N, class E>
        inline uint8<N, expr_empty> shift_l(const uint8<N, E> &a, const uint8<N, E> &count);
        template <unsigned N, class E>
        inline uint16<N, expr_empty> shift_l(const uint16<N, E> &a, const uint16<N, E> &count);
        template <unsigned N, class E>
        inline uint32<N, expr_empty> shift_l(const uint32<N, E> &a, const uint32<N, E> &count);

        template <unsigned count, unsigned N, class E> inline uint8<N, expr_empty> shift_l(const uint8<N, E> &a);
        template <unsigned count, unsigned N, class E> inline uint16<N, expr_empty> shift_l(const uint16<N, E> &a);
        template <unsigned count, unsigned N, class E> inline uint32<N, expr_empty> shift_l(const uint32<N, E> &a);
        template <unsigned count, unsigned N, class E> inline uint64<N, expr_empty> shift_l(const uint64<N, E> &a);

        template <unsigned N, class E> inline int8<N, expr_empty> shift_r(const int8<N, E> &a, unsigned count);
        template <unsigned N, class E> inline int16<N, expr_empty> shift_r(const int16<N, E> &a, unsigned count);
        template <unsigned N, class E> inline int32<N, expr_empty> shift_r(const int32<N, E> &a, unsigned count);
        template <unsigned N, class E> inline int64<N, expr_empty> shift_r(const int64<N, E> &a, unsigned count);

        template <unsigned N, class E>
        inline int8<N, expr_empty> shift_r(const int8<N, E> &a, const uint8<N, E> &count);
        template <unsigned N, class E>
        inline int16<N, expr_empty> shift_r(const int16<N, E> &a, const uint16<N, E> &count);
        template <unsigned N, class E>
        inline int32<N, expr_empty> shift_r(const int32<N, E> &a, const uint32<N, E> &count);

        template <unsigned count, unsigned N, class E> inline int8<N, expr_empty> shift_r(const int8<N, E> &a);
        template <unsigned count, unsigned N, class E> inline int16<N, expr_empty> shift_r(const int16<N, E> &a);
        template <unsigned count, unsigned N, class E> inline int32<N, expr_empty> shift_r(const int32<N, E> &a);
        template <unsigned count, unsigned N, class E> inline int64<N, expr_empty> shift_r(const int64<N, E> &a);

        template <unsigned N, class E> inline uint8<N, expr_empty> shift_r(const uint8<N, E> &a, unsigned count);
        template <unsigned N, class E> inline uint16<N, expr_empty> shift_r(const uint16<N, E> &a, unsigned count);
        template <unsigned N, class E> inline uint32<N, expr_empty> shift_r(const uint32<N, E> &a, unsigned count);
        template <unsigned N, class E> inline uint64<N, expr_empty> shift_r(const uint64<N, E> &a, unsigned count);

        template <unsigned N, class E>
        inline uint8<N, expr_empty> shift_r(const uint8<N, E> &a, const uint8<N, E> &count);
        template <unsigned N, class E>
        inline uint16<N, expr_empty> shift_r(const uint16<N, E> &a, const uint16<N, E> &count);
        template <unsigned N, class E>
        inline uint32<N, expr_empty> shift_r(const uint32<N, E> &a, const uint32<N, E> &count);

        template <unsigned count, unsigned N, class E> inline uint8<N, expr_empty> shift_r(const uint8<N, E> &a);
        template <unsigned count, unsigned N, class E> inline uint16<N, expr_empty> shift_r(const uint16<N, E> &a);
        template <unsigned count, unsigned N, class E> inline uint32<N, expr_empty> shift_r(const uint32<N, E> &a);
        template <unsigned count, unsigned N, class E> inline uint64<N, expr_empty> shift_r(const uint64<N, E> &a);

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
