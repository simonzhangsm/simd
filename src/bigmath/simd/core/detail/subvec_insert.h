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

#ifndef SIMD_CORE_DETAIL_VEC_INSERT_H
#define SIMD_CORE_DETAIL_VEC_INSERT_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/setup_arch.h>
#include <bigmath/simd/types.h>

#include <cstring>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {

            template <class R, class V> inline void subvec_insert_impl(R &r, const V &v, unsigned n) {
                static_assert(V::length >= R::base_length, "Too small vector to insert");

                for (unsigned i = 0; i < V::vec_length; ++i) {
                    r.vec(n * v.vec_length + i) = v.vec(i); // TODO combine or split as needed
                }
            }

            // Sets the elements [M*n .. M*(n+1)) of @a a to the contents of @a x
            template <unsigned N, unsigned M> inline void subvec_insert(uint8<N> &a, const uint8<M> &x, unsigned n) {
                subvec_insert_impl(a, x, n);
            }
            template <unsigned N, unsigned M> inline void subvec_insert(uint16<N> &a, const uint16<M> &x, unsigned n) {
                subvec_insert_impl(a, x, n);
            }
            template <unsigned N, unsigned M> inline void subvec_insert(uint32<N> &a, const uint32<M> &x, unsigned n) {
                subvec_insert_impl(a, x, n);
            }
            template <unsigned N, unsigned M> inline void subvec_insert(uint64<N> &a, const uint64<M> &x, unsigned n) {
                subvec_insert_impl(a, x, n);
            }

            template <unsigned N, unsigned M> inline void subvec_insert(int8<N> &a, const int8<M> &x, unsigned n) {
                subvec_insert_impl(a, x, n);
            }
            template <unsigned N, unsigned M> inline void subvec_insert(int16<N> &a, const int16<M> &x, unsigned n) {
                subvec_insert_impl(a, x, n);
            }
            template <unsigned N, unsigned M> inline void subvec_insert(int32<N> &a, const int32<M> &x, unsigned n) {
                subvec_insert_impl(a, x, n);
            }
            template <unsigned N, unsigned M> inline void subvec_insert(int64<N> &a, const int64<M> &x, unsigned n) {
                subvec_insert_impl(a, x, n);
            }

            template <unsigned N, unsigned M>
            inline void subvec_insert(float32<N> &a, const float32<M> &x, unsigned n) {
                subvec_insert_impl(a, x, n);
            }
            template <unsigned N, unsigned M>
            inline void subvec_insert(float64<N> &a, const float64<M> &x, unsigned n) {
                subvec_insert_impl(a, x, n);
            }

        } // namespace detail
    }     // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
