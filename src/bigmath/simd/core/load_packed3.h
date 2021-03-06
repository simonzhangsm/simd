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

#ifndef SIMD_CORE_LOAD_PACKED3_H
#define SIMD_CORE_LOAD_PACKED3_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/insn/load_packed3.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {


        /** Loads values packed in triplets, de-interleaves them and stores the result
            into three vectors.

            @code
            a = [ *(p),   *(p+3), *(p+6), ... , *(p+M*3-3) ]
            b = [ *(p+1), *(p+4), *(p+7), ... , *(p+M*3-2) ]
            c = [ *(p+2), *(p+5), *(p+8), ... , *(p+M*3-1) ]
            @endcode

            Here M is the number of elements in the vector

            @a p must be aligned to the vector size in bytes
        */
        template <unsigned N, class V, class T>
        inline void load_packed3(any_vec<N, V> &a, any_vec<N, V> &b, any_vec<N, V> &c, const T *p) {
            static_assert(!is_mask<V>::value, "Mask types can not be loaded");
            typename detail::get_expr_nosign<V>::type ra, rb, rc;
            detail::insn::i_load_packed3(ra, rb, rc, reinterpret_cast<const char *>(p));
            a.wrapped() = ra;
            b.wrapped() = rb;
            c.wrapped() = rc;
        }


    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
