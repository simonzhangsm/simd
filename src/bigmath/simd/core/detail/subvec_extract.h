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

#ifndef SIMD_CORE_DETAIL_VEC_EXTRACT_H
#define SIMD_CORE_DETAIL_VEC_EXTRACT_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/setup_arch.h>
#include <bigmath/simd/types.h>
#include <bigmath/simd/core/insert.h>
#include <bigmath/simd/core/extract.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {

            template <class R, class V> inline R subvec_extract_impl(const V &a, unsigned n) {
                static_assert(R::length >= V::base_length, "Too small vector to extract");

                R r;
                for (unsigned i = 0; i < r.vec_length; ++i) {
                    r.vec(i) = a.vec(n * r.vec_length + i);
                }
                return r;
            }

            // extract a sub-vector consisting of [M*n .. M*(n+1)) elements
            template <unsigned M, unsigned N> inline uint8<M> subvec_extract(const uint8<N> &a, unsigned n) {
                return subvec_extract_impl<uint8<M>>(a, n);
            }

            template <unsigned M, unsigned N> inline uint16<M> subvec_extract(const uint16<N> &a, unsigned n) {
                return subvec_extract_impl<uint16<M>>(a, n);
            }

            template <unsigned M, unsigned N> inline uint32<M> subvec_extract(const uint32<N> &a, unsigned n) {
                return subvec_extract_impl<uint32<M>>(a, n);
            }

            template <unsigned M, unsigned N> inline uint64<M> subvec_extract(const uint64<N> &a, unsigned n) {
                return subvec_extract_impl<uint64<M>>(a, n);
            }

            template <unsigned M, unsigned N> inline int8<M> subvec_extract(const int8<N> &a, unsigned n) {
                return subvec_extract_impl<int8<M>>(a, n);
            }

            template <unsigned M, unsigned N> inline int16<M> subvec_extract(const int16<N> &a, unsigned n) {
                return subvec_extract_impl<int16<M>>(a, n);
            }

            template <unsigned M, unsigned N> inline int32<M> subvec_extract(const int32<N> &a, unsigned n) {
                return subvec_extract_impl<int32<M>>(a, n);
            }

            template <unsigned M, unsigned N> inline int64<M> subvec_extract(const int64<N> &a, unsigned n) {
                return subvec_extract_impl<int64<M>>(a, n);
            }

            template <unsigned M, unsigned N> inline float32<M> subvec_extract(const float32<N> &a, unsigned n) {
                return subvec_extract_impl<float32<M>>(a, n);
            }

            template <unsigned M, unsigned N> inline float64<M> subvec_extract(const float64<N> &a, unsigned n) {
                return subvec_extract_impl<float64<M>>(a, n);
            }


        } // namespace detail
    }     // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
