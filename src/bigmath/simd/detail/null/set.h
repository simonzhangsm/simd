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

#ifndef DETAIL_NULL_SET_H
#define DETAIL_NULL_SET_H
#if SIMD_USE_NULL || SIMD_USE_NEON || SIMD_USE_ALTIVEC

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace null {

                template <class V, class E = typename V::element_type> inline V make_vec(E v0) {
                    V r;
                    for (unsigned i = 0; i < V::length; i++) {
                        r.el(i) = v0;
                    }
                    return r;
                }

                template <class V, class E = typename V::element_type> inline V make_vec(E v0, E v1) {
                    V r;
                    for (unsigned i = 0; i < V::length; i += 2) {
                        r.el(i) = v0;
                        r.el(i + 1) = v1;
                    }
                    return r;
                }

                template <class V, class E = typename V::element_type> inline V make_vec(E v0, E v1, E v2, E v3) {
                    V r;
                    for (unsigned i = 0; i < V::length; i += 4) {
                        r.el(i) = v0;
                        r.el(i + 1) = v1;
                        r.el(i + 2) = v2;
                        r.el(i + 3) = v3;
                    }
                    return r;
                }

                template <class V, class E = typename V::element_type>
                inline V make_vec(E v0, E v1, E v2, E v3, E v4, E v5, E v6, E v7) {
                    V r;
                    for (unsigned i = 0; i < V::length; i += 8) {
                        r.el(i) = v0;
                        r.el(i + 1) = v1;
                        r.el(i + 2) = v2;
                        r.el(i + 3) = v3;
                        r.el(i + 4) = v4;
                        r.el(i + 5) = v5;
                        r.el(i + 6) = v6;
                        r.el(i + 7) = v7;
                    }
                    return r;
                }

                template <class V, class E = typename V::element_type>
                inline V make_vec(E v0,
                                  E v1,
                                  E v2,
                                  E v3,
                                  E v4,
                                  E v5,
                                  E v6,
                                  E v7,
                                  E v8,
                                  E v9,
                                  E v10,
                                  E v11,
                                  E v12,
                                  E v13,
                                  E v14,
                                  E v15) {
                    V r;
                    for (unsigned i = 0; i < V::length; i += 16) {
                        r.el(i) = v0;
                        r.el(i + 1) = v1;
                        r.el(i + 2) = v2;
                        r.el(i + 3) = v3;
                        r.el(i + 4) = v4;
                        r.el(i + 5) = v5;
                        r.el(i + 6) = v6;
                        r.el(i + 7) = v7;
                        r.el(i + 8) = v8;
                        r.el(i + 9) = v9;
                        r.el(i + 10) = v10;
                        r.el(i + 11) = v11;
                        r.el(i + 12) = v12;
                        r.el(i + 13) = v13;
                        r.el(i + 14) = v14;
                        r.el(i + 15) = v15;
                    }
                    return r;
                }

            } // namespace null
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
#endif
