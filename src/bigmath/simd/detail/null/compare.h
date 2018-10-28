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

#ifndef DETAIL_NULL_COMPARE_H
#define DETAIL_NULL_COMPARE_H
#if SIMD_USE_NULL || SIMD_USE_NEON || SIMD_USE_ALTIVEC

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/detail/null/mask.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace null {

                template <class V> inline typename V::mask_vector_type cmp_eq(const V &a, const V &b) {
                    typename V::mask_vector_type r;
                    for (unsigned i = 0; i < V::length; i++) {
                        r.el(i) = (a.el(i) == b.el(i)) ? 1 : 0;
                    }
                    return r;
                }

                template <class V> inline typename V::mask_vector_type cmp_neq(const V &a, const V &b) {
                    typename V::mask_vector_type r;
                    for (unsigned i = 0; i < V::length; i++) {
                        r.el(i) = (a.el(i) != b.el(i)) ? 1 : 0;
                    }
                    return r;
                }

                template <class V> inline typename V::mask_vector_type cmp_lt(const V &a, const V &b) {
                    typename V::mask_vector_type r;
                    for (unsigned i = 0; i < V::length; i++) {
                        r.el(i) = (a.el(i) < b.el(i)) ? 1 : 0;
                    }
                    return r;
                }

                template <class V> inline typename V::mask_vector_type cmp_le(const V &a, const V &b) {
                    typename V::mask_vector_type r;
                    for (unsigned i = 0; i < V::length; i++) {
                        r.el(i) = (a.el(i) <= b.el(i)) ? 1 : 0;
                    }
                    return r;
                }

                template <class V> inline typename V::mask_vector_type cmp_gt(const V &a, const V &b) {
                    typename V::mask_vector_type r;
                    for (unsigned i = 0; i < V::length; i++) {
                        r.el(i) = (a.el(i) > b.el(i)) ? 1 : 0;
                    }
                    return r;
                }

                template <class V> inline typename V::mask_vector_type cmp_ge(const V &a, const V &b) {
                    typename V::mask_vector_type r;
                    for (unsigned i = 0; i < V::length; i++) {
                        r.el(i) = (a.el(i) >= b.el(i)) ? 1 : 0;
                    }
                    return r;
                }

            } // namespace null
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
#endif
