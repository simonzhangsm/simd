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

#ifndef DETAIL_NULL_MATH_H
#define DETAIL_NULL_MATH_H
#if SIMD_USE_NULL || SIMD_USE_NEON || SIMD_USE_ALTIVEC

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/core/cast.h>

#include <cmath>
#include <cstdlib>
#include <limits>

// On certain versions of MSVC min and max are defined as macros.
#if _MSC_VER
#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif
#endif

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace null {

                template <class V> inline typename V::mask_vector_type isnan(const V &a) {
                    typename V::mask_vector_type r;
                    for (unsigned i = 0; i < V::length; i++) {
                        r.el(i) = std::isnan(a.el(i)) ? 1 : 0;
                    }
                    return r;
                }

                template <class V> inline typename V::mask_vector_type isnan2(const V &a, const V &b) {
                    typename V::mask_vector_type r;
                    for (unsigned i = 0; i < V::length; i++) {
                        r.el(i) = (std::isnan(a.el(i)) || std::isnan(b.el(i))) ? 1 : 0;
                    }
                    return r;
                }

                template <class V> inline V abs(const V &a) {
                    V r;
                    for (unsigned i = 0; i < V::length; i++) {
                        r.el(i) = std::abs(a.el(i));
                    }
                    return r;
                }

                template <class T, class U> inline T saturate(U t) {
                    U min = std::numeric_limits<T>::min();
                    U max = std::numeric_limits<T>::max();
                    t = t < min ? min : t;
                    t = t > max ? max : t;
                    return t;
                }

                template <class V> inline V add(const V &a, const V &b) {
                    V r;
                    for (unsigned i = 0; i < V::length; i++) {
                        r.el(i) = a.el(i) + b.el(i);
                    }
                    return r;
                }

                template <class V> inline V add_sat(const V &a, const V &b) {
                    V r;
                    for (unsigned i = 0; i < V::length; i++) {
                        r.el(i) = saturate<typename V::element_type>(int32_t(a.el(i)) + b.el(i));
                    }
                    return r;
                }

                template <class V> inline V sub(const V &a, const V &b) {
                    V r;
                    for (unsigned i = 0; i < V::length; i++) {
                        r.el(i) = a.el(i) - b.el(i);
                    }
                    return r;
                }

                template <class V> inline V sub_sat(const V &a, const V &b) {
                    V r;
                    for (unsigned i = 0; i < V::length; i++) {
                        r.el(i) = saturate<typename V::element_type>(int32_t(a.el(i)) - b.el(i));
                    }
                    return r;
                }

                template <class V> inline V neg(const V &a) {
                    V r;
                    for (unsigned i = 0; i < V::length; i++) {
                        r.el(i) = -a.el(i);
                    }
                    return r;
                }

                template <class V> inline V mul(const V &a, const V &b) {
                    V r;
                    for (unsigned i = 0; i < V::length; i++) {
                        r.el(i) = a.el(i) * b.el(i);
                    }
                    return r;
                }

                template <class V> inline V fmadd(const V &a, const V &b, const V &c) {
                    V r;
                    for (unsigned i = 0; i < V::length; i++) {
                        r.el(i) = std::fma(a.el(i), b.el(i), c.el(i));
                    }
                    return r;
                }

                template <class V> inline V fmsub(const V &a, const V &b, const V &c) {
                    V r;
                    for (unsigned i = 0; i < V::length; i++) {
                        r.el(i) = std::fma(a.el(i), b.el(i), -c.el(i));
                    }
                    return r;
                }

                template <unsigned P, class V> inline V div_p(const V &a, const V &b) {
                    // the least P significant bits of the mask are set.
                    uint64_t mask = 0;
                    mask = ~mask;
                    mask <<= P;
                    mask = ~mask;

                    V r;
                    for (unsigned i = 0; i < V::length; i++) {
                        r.el(i) = (a.el(i) & mask) / (b.el(i) & mask);
                        r.el(i) &= mask;
                    }
                    return r;
                }


                template <class V> inline V shift_r(const V &a, unsigned shift) {
                    V r;
                    for (unsigned i = 0; i < V::length; i++) {
                        r.el(i) = a.el(i) >> shift;
                    }
                    return r;
                }

                template <class V, class S> inline V shift_r_v(const V &a, const S &shift) {
                    V r;
                    for (unsigned i = 0; i < V::length; i++) {
                        r.el(i) = a.el(i) >> shift.el(i);
                    }
                    return r;
                }

                template <class V> inline V shift_l(const V &a, unsigned shift) {
                    V r;
                    for (unsigned i = 0; i < V::length; i++) {
                        r.el(i) = a.el(i) << shift;
                    }
                    return r;
                }

                template <class V, class S> inline V shift_l_v(const V &a, const S &shift) {
                    V r;
                    for (unsigned i = 0; i < V::length; i++) {
                        r.el(i) = a.el(i) << shift.el(i);
                    }
                    return r;
                }

                template <class V> inline V min(const V &a, const V &b) {
                    V r;
                    for (unsigned i = 0; i < V::length; i++) {
                        r.el(i) = a.el(i) <= b.el(i) ? a.el(i) : b.el(i);
                    }
                    return r;
                }

                template <class V> inline V max(const V &a, const V &b) {
                    V r;
                    for (unsigned i = 0; i < V::length; i++) {
                        r.el(i) = a.el(i) >= b.el(i) ? a.el(i) : b.el(i);
                    }
                    return r;
                }

            } // namespace null
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
#endif
