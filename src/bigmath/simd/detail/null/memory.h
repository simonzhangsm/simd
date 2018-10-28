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

#ifndef DETAIL_NULL_MEMORY_H
#define DETAIL_NULL_MEMORY_H
#if SIMD_USE_NULL || SIMD_USE_NEON || SIMD_USE_ALTIVEC

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace null {

                template <class V> inline void load(V &a, const char *p) {
                    using T = typename V::element_type;
                    const T *pt = reinterpret_cast<const T *>(p);
                    for (unsigned i = 0; i < V::length; i++) {
                        a.el(i) = *pt++;
                    }
                }

                template <class V> inline void load_packed2(V &a, V &b, const char *p) {
                    using T = typename V::element_type;
                    const T *pt = reinterpret_cast<const T *>(p);
                    for (unsigned i = 0; i < V::length; i++) {
                        a.el(i) = *pt++;
                        b.el(i) = *pt++;
                    }
                }

                template <class V> inline void load_packed3(V &a, V &b, V &c, const char *p) {
                    using T = typename V::element_type;
                    const T *pt = reinterpret_cast<const T *>(p);
                    for (unsigned i = 0; i < V::length; i++) {
                        a.el(i) = *pt++;
                        b.el(i) = *pt++;
                        c.el(i) = *pt++;
                    }
                }

                template <class V> inline void load_packed4(V &a, V &b, V &c, V &d, const char *p) {
                    using T = typename V::element_type;
                    const T *pt = reinterpret_cast<const T *>(p);
                    for (unsigned i = 0; i < V::length; i++) {
                        a.el(i) = *pt++;
                        b.el(i) = *pt++;
                        c.el(i) = *pt++;
                        d.el(i) = *pt++;
                    }
                }

                template <class V> inline void store(char *p, const V &a) {
                    using T = typename V::element_type;
                    T *pt = reinterpret_cast<T *>(p);
                    for (unsigned i = 0; i < V::length; i++) {
                        *pt++ = a.el(i);
                    }
                }

                template <class V, class M> inline void store_masked(char *p, const V &a, const M &mask) {
                    using T = typename V::element_type;
                    T *pt = reinterpret_cast<T *>(p);
                    for (unsigned i = 0; i < a.length; ++i) {
                        if (mask.el(i))
                            *pt = a.el(i);
                        pt++;
                    }
                }

                template <class V> inline void store_first(char *p, const V &a, unsigned n) {
                    using T = typename V::element_type;
                    T *pt = reinterpret_cast<T *>(p);
                    for (unsigned i = 0; i < V::length && i < n; i++) {
                        *pt++ = a.el(i);
                    }
                }

                template <class V> inline void store_last(char *p, const V &a, unsigned n) {
                    using T = typename V::element_type;
                    T *pt = reinterpret_cast<T *>(p);
                    pt += V::length - n;
                    for (unsigned i = V::length - n; i < V::length; i++) {
                        *pt++ = a.el(i);
                    }
                }

                template <class V> inline void store_packed2(char *p, const V &a, const V &b) {
                    using T = typename V::element_type;
                    T *pt = reinterpret_cast<T *>(p);
                    for (unsigned i = 0; i < V::length; i++) {
                        *pt++ = a.el(i);
                        *pt++ = b.el(i);
                    }
                }

                template <class V> inline void store_packed3(char *p, const V &a, const V &b, const V &c) {
                    using T = typename V::element_type;
                    T *pt = reinterpret_cast<T *>(p);
                    for (unsigned i = 0; i < V::length; i++) {
                        *pt++ = a.el(i);
                        *pt++ = b.el(i);
                        *pt++ = c.el(i);
                    }
                }

                template <class V> inline void store_packed4(char *p, const V &a, const V &b, const V &c, const V &d) {
                    using T = typename V::element_type;
                    T *pt = reinterpret_cast<T *>(p);
                    for (unsigned i = 0; i < V::length; i++) {
                        *pt++ = a.el(i);
                        *pt++ = b.el(i);
                        *pt++ = c.el(i);
                        *pt++ = d.el(i);
                    }
                }

            } // namespace null
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
#endif
