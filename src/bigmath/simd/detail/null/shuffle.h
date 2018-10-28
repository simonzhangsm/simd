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

#ifndef DETAIL_NULL_SHUFFLE_H
#define DETAIL_NULL_SHUFFLE_H
#if SIMD_USE_NULL || SIMD_USE_NEON || SIMD_USE_ALTIVEC

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/core/bit_and.h>
#include <bigmath/simd/core/bit_andnot.h>
#include <bigmath/simd/core/bit_or.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace null {

                template <unsigned count, class V> inline V move_n_l(const V &a) {
                    V r;
                    for (unsigned i = 0; i < V::length - count; i++) {
                        r.el(i) = a.el(i + count);
                    }
                    for (unsigned i = V::length - count; i < V::length; i++) {
                        r.el(i) = 0;
                    }
                    return r;
                }

                template <unsigned count, class V> inline V move_n_r(const V &a) {
                    V r;
                    for (unsigned i = 0; i < count; i++) {
                        r.el(i) = 0;
                    }
                    for (unsigned i = 0; i < V::length - count; i++) {
                        r.el(i + count) = a.el(i);
                    }
                    return r;
                }

                template <class V> inline V zip_lo_impl(const V &a, const V &b) {
                    V r;
                    for (unsigned i = 0; i < V::length / 2; i++) {
                        r.el(i * 2) = a.el(i);
                        r.el(i * 2 + 1) = b.el(i);
                    }
                    return r;
                }

                template <class V> inline V zip_hi_impl(const V &a, const V &b) {
                    V r;
                    unsigned half = V::length / 2;
                    for (unsigned i = 0; i < half; i++) {
                        r.el(i * 2) = a.el(half + i);
                        r.el(i * 2 + 1) = b.el(half + i);
                    }
                    return r;
                }


                template <class V> inline V unzip_lo_impl(const V &a, const V &b) {
                    V r;
                    unsigned half = V::length / 2;
                    for (unsigned i = 0; i < half; i++) {
                        r.el(i) = a.el(i * 2);
                        r.el(i + half) = b.el(i * 2);
                    }
                    return r;
                }

                template <class V> inline V unzip_hi_impl(const V &a, const V &b) {
                    V r;
                    unsigned half = V::length / 2;
                    for (unsigned i = 0; i < half; i++) {
                        r.el(i) = a.el(i * 2 + 1);
                        r.el(i + half) = b.el(i * 2 + 1);
                    }
                    return r;
                }

                template <class V> inline V zip16_lo(const V &a, const V &b) {
                    return zip_lo_impl(a, b);
                }
                template <class V> inline V zip8_lo(const V &a, const V &b) {
                    return zip_lo_impl(a, b);
                }
                template <class V> inline V zip4_lo(const V &a, const V &b) {
                    return zip_lo_impl(a, b);
                }
                template <class V> inline V zip2_lo(const V &a, const V &b) {
                    return zip_lo_impl(a, b);
                }
                template <class V> inline V zip16_hi(const V &a, const V &b) {
                    return zip_hi_impl(a, b);
                }
                template <class V> inline V zip8_hi(const V &a, const V &b) {
                    return zip_hi_impl(a, b);
                }
                template <class V> inline V zip4_hi(const V &a, const V &b) {
                    return zip_hi_impl(a, b);
                }
                template <class V> inline V zip2_hi(const V &a, const V &b) {
                    return zip_hi_impl(a, b);
                }

                template <class V> inline V unzip16_lo(const V &a, const V &b) {
                    return unzip_lo_impl(a, b);
                }
                template <class V> inline V unzip8_lo(const V &a, const V &b) {
                    return unzip_lo_impl(a, b);
                }
                template <class V> inline V unzip4_lo(const V &a, const V &b) {
                    return unzip_lo_impl(a, b);
                }
                template <class V> inline V unzip2_lo(const V &a, const V &b) {
                    return unzip_lo_impl(a, b);
                }
                template <class V> inline V unzip16_hi(const V &a, const V &b) {
                    return unzip_hi_impl(a, b);
                }
                template <class V> inline V unzip8_hi(const V &a, const V &b) {
                    return unzip_hi_impl(a, b);
                }
                template <class V> inline V unzip4_hi(const V &a, const V &b) {
                    return unzip_hi_impl(a, b);
                }
                template <class V> inline V unzip2_hi(const V &a, const V &b) {
                    return unzip_hi_impl(a, b);
                }

                template <unsigned pos, class V> inline V splat(const V &v) {
                    V r;
                    for (unsigned i = 0; i < V::length; i++) {
                        r.el(i) = v.el(pos);
                    }
                    return r;
                }

                template <unsigned shift, class V> inline V align(const V &lo, const V &hi) {
                    V r;
                    for (unsigned i = 0; i < 16 - shift; i++) {
                        r.el(i) = lo.el(i + shift);
                    }
                    for (unsigned i = 16 - shift; i < 16; i++) {
                        r.el(i) = hi.el(i - 16 + shift);
                    }
                    return r;
                }

                template <class V> inline V blend(const V &on, const V &off, const V &mask) {
                    V r;
                    using E = typename V::element_type;
                    using U = typename V::uint_element_type;
                    for (unsigned i = 0; i < V::length; i++) {
                        U on1 = bit_cast<U, E>(on.el(i));
                        U off1 = bit_cast<U, E>(off.el(i));
                        U mask1 = bit_cast<U, E>(mask.el(i));
                        r.el(i) = bit_cast<E, U>((on1 & mask1) | (off1 & ~mask1));
                    }
                    return r;
                }

                template <unsigned L> struct blend_mask_impl {
                    template <class V, class M> static inline V run(const V &on, const V &off, const M &mask) {
                        V r;
                        for (unsigned i = 0; i < L; i++) {
                            r.el(i) = mask.el(i) ? on.el(i) : off.el(i);
                        }
                        return r;
                    }
                };

                template <> struct blend_mask_impl<1> {
                    template <class V, class M> static inline V run(const V &on, const V &off, const M &mask) {
                        V r;
                        r.el(0) = mask.el(0) ? on.el(0) : off.el(0);
                        return r;
                    }
                };
                template <> struct blend_mask_impl<2> {
                    template <class V, class M> static inline V run(const V &on, const V &off, const M &mask) {
                        V r;
                        r.el(0) = mask.el(0) ? on.el(0) : off.el(0);
                        r.el(1) = mask.el(1) ? on.el(1) : off.el(1);
                        return r;
                    }
                };
                template <> struct blend_mask_impl<4> {
                    template <class V, class M> static inline V run(const V &on, const V &off, const M &mask) {
                        V r;
                        r.el(0) = mask.el(0) ? on.el(0) : off.el(0);
                        r.el(1) = mask.el(1) ? on.el(1) : off.el(1);
                        r.el(2) = mask.el(2) ? on.el(2) : off.el(2);
                        r.el(3) = mask.el(3) ? on.el(3) : off.el(3);
                        return r;
                    }
                };

                template <class V, class M> inline V blend_mask(const V &on, const V &off, const M &mask) {
                    return blend_mask_impl<V::length>::run(on, off, mask);
                }

                template <unsigned s0, unsigned s1, class V> inline V permute(const V &a) {
                    V r;
                    for (unsigned i = 0; i < V::length; i += 2) {
                        r.el(i) = a.el(i + s0);
                        r.el(i + 1) = a.el(i + s1);
                    }
                    return r;
                }

                template <unsigned s0, unsigned s1, unsigned s2, unsigned s3, class V> inline V permute(const V &a) {
                    V r;
                    for (unsigned i = 0; i < V::length; i += 4) {
                        r.el(i) = a.el(i + s0);
                        r.el(i + 1) = a.el(i + s1);
                        r.el(i + 2) = a.el(i + s2);
                        r.el(i + 3) = a.el(i + s3);
                    }
                    return r;
                }

                template <unsigned s0, unsigned s1, class V> inline V shuffle1(const V &a, const V &b) {
                    V r;
                    for (unsigned i = 0; i < V::length; i += 2) {
                        r.el(i) = a.el(i + s0);
                        r.el(i + 1) = b.el(i + s1);
                    }
                    return r;
                }

                template <unsigned s0, unsigned s1, unsigned s2, unsigned s3, class V>
                inline V shuffle2(const V &a, const V &b) {
                    V r;
                    for (unsigned i = 0; i < V::length; i += 4) {
                        r.el(i) = a.el(i + s0);
                        r.el(i + 1) = a.el(i + s1);
                        r.el(i + 2) = b.el(i + s2);
                        r.el(i + 3) = b.el(i + s3);
                    }
                    return r;
                }

            } // namespace null
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
#endif
