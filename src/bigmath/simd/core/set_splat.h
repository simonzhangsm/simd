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

#ifndef SIMD_CORE_SET_SPLAT_H
#define SIMD_CORE_SET_SPLAT_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/insn/set_splat.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {

        /** Loads a value from a register and broadcasts it to all elements of a vector.
            The argument value is converted to the element of the resulting vector using
            standard conversions.

            @code
            r0 = a
            ...
            rN = a
            @endcode
        */
        // FIXME: return empty expression
        inline expr_vec_set_splat<uint32_t> splat(unsigned x) {
            return {x};
        }
        inline expr_vec_set_splat<uint64_t> splat(unsigned long x) {
            return {x};
        }
        inline expr_vec_set_splat<uint64_t> splat(unsigned long long x) {
            return {x};
        }
        inline expr_vec_set_splat<int32_t> splat(int x) {
            return {x};
        }
        inline expr_vec_set_splat<int64_t> splat(long x) {
            return {x};
        }
        inline expr_vec_set_splat<int64_t> splat(long long x) {
            return {x};
        }
        inline expr_vec_set_splat<float> splat(float x) {
            return {x};
        }
        inline expr_vec_set_splat<double> splat(double x) {
            return {x};
        }

        template <class V> inline V splat(unsigned x) {
            return detail::splat_impl<V>(x);
        }
        template <class V> inline V splat(unsigned long x) {
            return detail::splat_impl<V>(x);
        }
        template <class V> inline V splat(unsigned long long x) {
            return detail::splat_impl<V>(x);
        }
        template <class V> inline V splat(int x) {
            return detail::splat_impl<V>(x);
        }
        template <class V> inline V splat(long x) {
            return detail::splat_impl<V>(x);
        }
        template <class V> inline V splat(long long x) {
            return detail::splat_impl<V>(x);
        }
        template <class V> inline V splat(float x) {
            return detail::splat_impl<V>(x);
        }
        template <class V> inline V splat(double x) {
            return detail::splat_impl<V>(x);
        }

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
