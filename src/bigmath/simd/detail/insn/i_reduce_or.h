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

#ifndef SIMD_DETAIL_INSN_I_REDUCE_OR_H
#define SIMD_DETAIL_INSN_I_REDUCE_OR_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/core/bit_or.h>
#include <bigmath/simd/core/extract.h>
#include <bigmath/simd/core/move_l.h>
#include <bigmath/simd/core/make_uint.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {

                static inline uint8_t i_reduce_or(const uint8x16 &a) {
#if SIMD_USE_NULL
                    uint8_t r = a.el(0);
                    for (unsigned i = 1; i < a.length; i++) {
                        r |= a.el(i);
                    }
                    return r;
#elif SIMD_USE_SSE2 || SIMD_USE_NEON || SIMD_USE_ALTIVEC || SIMD_USE_MSA
                    uint8x16 r = bit_or(a, move16_l<8>(a));
                    r = bit_or(r, move16_l<4>(r));
                    r = bit_or(r, move16_l<2>(r));
                    r = bit_or(r, move16_l<1>(r));
                    return extract<0>(r);
#endif
                }

#if SIMD_USE_AVX2
                static inline uint8_t i_reduce_or(const uint8x32 &a) {
                    uint8x16 r = detail::extract128<0>(a);
                    r = bit_or(r, detail::extract128<1>(a));
                    return i_reduce_or(r);
                }
#endif

#if SIMD_USE_AVX512BW
                inline uint8_t i_reduce_or(const uint8<64> &a) {
                    uint8<32> r = detail::extract256<0>(a);
                    r = bit_or(r, detail::extract256<1>(a));
                    return i_reduce_or(r);
                }
#endif

                template <unsigned N> inline uint8_t i_reduce_or(const uint8<N> &a) {
#if SIMD_USE_NULL
                    uint8_t r = 0;
                    for (unsigned j = 0; j < a.vec_length; ++j) {
                        for (unsigned i = 0; i < a.base_length; i++) {
                            r |= a.vec(j).el(i);
                        }
                    }
                    return r;
#else
                    uint8v r = a.vec(0);
                    for (unsigned j = 1; j < a.vec_length; ++j) {
                        r = bit_or(r, a.vec(j));
                    }
                    return i_reduce_or(r);
#endif
                }

                // -----------------------------------------------------------------------------

                static inline uint16_t i_reduce_or(const uint16x8 &a) {
#if SIMD_USE_NULL
                    uint16_t r = a.el(0);
                    for (unsigned i = 0; i < a.length; i++) {
                        r |= a.el(i);
                    }
                    return r;
#elif SIMD_USE_SSE2 || SIMD_USE_NEON || SIMD_USE_ALTIVEC || SIMD_USE_MSA
                    uint16x8 r = bit_or(a, move8_l<4>(a));
                    r = bit_or(r, move8_l<2>(r));
                    r = bit_or(r, move8_l<1>(r));
                    return extract<0>(r);
#endif
                }

#if SIMD_USE_AVX2
                static inline uint16_t i_reduce_or(const uint16x16 &a) {
                    uint16x8 r = detail::extract128<0>(a);
                    r = bit_or(r, detail::extract128<1>(a));
                    return i_reduce_or(r);
                }
#endif

#if SIMD_USE_AVX512BW
                inline uint16_t i_reduce_or(const uint16<32> &a) {
                    uint16<16> r = detail::extract256<0>(a);
                    r = bit_or(r, detail::extract256<1>(a));
                    return i_reduce_or(r);
                }
#endif

                template <unsigned N> inline uint16_t i_reduce_or(const uint16<N> &a) {
#if SIMD_USE_NULL
                    uint16_t r = 0;
                    for (unsigned j = 0; j < a.vec_length; ++j) {
                        for (unsigned i = 0; i < a.base_length; i++) {
                            r |= a.vec(j).el(i);
                        }
                    }
                    return r;
#else
                    uint16v r = a.vec(0);
                    for (unsigned j = 1; j < a.vec_length; ++j) {
                        r = bit_or(r, a.vec(j));
                    }
                    return i_reduce_or(r);
#endif
                }

                // -----------------------------------------------------------------------------

                static inline uint32_t i_reduce_or(const uint32x4 &a) {
#if SIMD_USE_NULL
                    uint32_t r = a.el(0);
                    for (unsigned i = 0; i < a.length; i++) {
                        r |= a.el(i);
                    }
                    return r;
#elif SIMD_USE_SSE2 || SIMD_USE_NEON || SIMD_USE_ALTIVEC || SIMD_USE_MSA
                    uint32x4 r = bit_or(a, move4_l<2>(a));
                    r = bit_or(r, move4_l<1>(r));
                    return extract<0>(r);
#endif
                }

#if SIMD_USE_AVX2
                static inline uint32_t i_reduce_or(const uint32x8 &a) {
                    uint32x4 r = detail::extract128<0>(a);
                    r = bit_or(r, detail::extract128<1>(a));
                    r = bit_or(r, move4_l<2>(r));
                    r = bit_or(r, move4_l<1>(r));
                    return extract<0>(r);
                }
#endif

#if SIMD_USE_AVX512F
                static inline uint32_t i_reduce_or(const uint32<16> &a) {
                    return i_reduce_or(bit_or(extract256<0>(a), extract256<1>(a)));
                }
#endif

                template <unsigned N> inline uint32_t i_reduce_or(const uint32<N> &a) {
#if SIMD_USE_NULL
                    uint32_t r = 0;
                    for (unsigned j = 0; j < a.vec_length; ++j) {
                        for (unsigned i = 0; i < a.base_length; i++) {
                            r |= a.vec(j).el(i);
                        }
                    }
                    return r;
#else
                    uint32v r = a.vec(0);
                    for (unsigned j = 1; j < a.vec_length; ++j) {
                        r = bit_or(r, a.vec(j));
                    }
                    return i_reduce_or(r);
#endif
                }

                // -----------------------------------------------------------------------------

                static inline uint64_t i_reduce_or(const uint64x2 &a) {
#if SIMD_USE_SSE2 || SIMD_USE_NEON || SIMD_USE_VSX_207 || SIMD_USE_MSA
                    uint64x2 r = bit_or(a, move2_l<1>(a));
                    return extract<0>(r);
#elif SIMD_USE_NULL || SIMD_USE_ALTIVEC
                    uint64_t r = a.el(0);
                    for (unsigned i = 0; i < a.length; i++) {
                        r |= a.el(i);
                    }
                    return r;
#endif
                }

#if SIMD_USE_AVX2
                static inline uint64_t i_reduce_or(const uint64x4 &a) {
                    uint64x2 r = detail::extract128<0>(a);
                    r = bit_or(r, detail::extract128<1>(a));
                    r = bit_or(r, move2_l<1>(r));
                    return extract<0>(r);
                }
#endif

#if SIMD_USE_AVX512F
                static inline uint64_t i_reduce_or(const uint64<8> &a) {
                    return i_reduce_or(bit_or(extract256<0>(a), extract256<1>(a)));
                }
#endif

                template <unsigned N> inline uint64_t i_reduce_or(const uint64<N> &a) {
#if SIMD_USE_NULL
                    uint64_t r = 0;
                    for (unsigned j = 0; j < a.vec_length; ++j) {
                        for (unsigned i = 0; i < a.base_length; i++) {
                            r |= a.vec(j).el(i);
                        }
                    }
                    return r;
#else
                    uint64v r = a.vec(0);
                    for (unsigned j = 1; j < a.vec_length; ++j) {
                        r = bit_or(r, a.vec(j));
                    }
                    return i_reduce_or(r);
#endif
                }

                // -----------------------------------------------------------------------------

            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
