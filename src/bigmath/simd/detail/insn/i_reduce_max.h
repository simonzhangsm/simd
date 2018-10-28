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

#ifndef SIMD_DETAIL_INSN_I_REDUCE_MAX_H
#define SIMD_DETAIL_INSN_I_REDUCE_MAX_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/core/i_max.h>
#include <bigmath/simd/core/extract.h>
#include <bigmath/simd/core/move_l.h>
#include <bigmath/simd/core/make_uint.h>
#include <bigmath/simd/detail/mem_block.h>
#include <bigmath/simd/detail/extract128.h>
#include <limits>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {

                static inline uint8_t i_reduce_max(const uint8x16 &a) {
#if SIMD_USE_NULL
                    uint8_t r = a.el(0);
                    for (unsigned i = 0; i < a.length; i++) {
                        r = r > a.el(i) ? r : a.el(i);
                    }
                    return r;
#elif SIMD_USE_NEON64
                    return vmaxvq_u8(a.native());
#elif SIMD_USE_SSE2 || SIMD_USE_NEON || SIMD_USE_ALTIVEC || SIMD_USE_MSA
                    uint8x16 r = max(a, move16_l<8>(a));
                    r = max(r, move16_l<4>(r));
                    r = max(r, move16_l<2>(r));
                    r = max(r, move16_l<1>(r));
                    return extract<0>(r);
#endif
                }

#if SIMD_USE_AVX2
                static inline uint8_t i_reduce_max(const uint8<32> &a) {
                    uint8x16 r = detail::extract128<0>(a);
                    r = max(r, detail::extract128<1>(a));
                    return i_reduce_max(r);
                }
#endif

#if SIMD_USE_AVX512BW
                inline uint8_t i_reduce_max(const uint8<64> &a) {
                    uint8<32> r = detail::extract256<0>(a);
                    r = max(r, detail::extract256<1>(a));
                    return i_reduce_max(r);
                }
#endif

                template <unsigned N> inline uint8_t i_reduce_max(const uint8<N> &a) {
#if SIMD_USE_NULL
                    uint8_t r = std::numeric_limits<uint8_t>::min();
                    for (unsigned j = 0; j < a.vec_length; ++j) {
                        for (unsigned i = 0; i < a.base_length; i++) {
                            r = r > a.vec(j).el(i) ? r : a.vec(j).el(i);
                        }
                    }
                    return r;
#else
                    uint8v r = a.vec(0);
                    for (unsigned j = 1; j < a.vec_length; ++j) {
                        r = max(r, a.vec(j));
                    }
                    return i_reduce_max(r);
#endif
                }

                // -----------------------------------------------------------------------------

                static inline int8_t i_reduce_max(const int8x16 &a) {
#if SIMD_USE_NULL
                    int8_t r = a.el(0);
                    for (unsigned i = 0; i < a.length; i++) {
                        r = r > a.el(i) ? r : a.el(i);
                    }
                    return r;
#elif SIMD_USE_NEON64
                    return vmaxvq_s8(a.native());
#elif SIMD_USE_SSE4_1 || SIMD_USE_NEON || SIMD_USE_ALTIVEC || SIMD_USE_MSA
                    int8x16 r = a;
                    r = max(r, move16_l<8>(r));
                    r = max(r, move16_l<4>(r));
                    r = max(r, move16_l<2>(r));
                    r = max(r, move16_l<1>(r));
                    return extract<0>(r);
#elif SIMD_USE_SSE2
                    // no instruction for int8 max available, only for uint8
                    uint8x16 ca = bit_xor(a, 0x80);
                    return i_reduce_max(ca) ^ 0x80;
#endif
                }

#if SIMD_USE_AVX2
                static inline int8_t i_reduce_max(const int8<32> &a) {
                    int8x16 r = detail::extract128<0>(a);
                    r = max(r, detail::extract128<1>(a));
                    return i_reduce_max(r);
                }
#endif

#if SIMD_USE_AVX512BW
                inline int8_t i_reduce_max(const int8<64> &a) {
                    int8<32> r = detail::extract256<0>(a);
                    r = max(r, detail::extract256<1>(a));
                    return i_reduce_max(r);
                }
#endif

                template <unsigned N> inline int8_t i_reduce_max(const int8<N> &a) {
#if SIMD_USE_NULL
                    int8_t r = std::numeric_limits<int8_t>::min();
                    ;
                    for (unsigned j = 0; j < a.vec_length; ++j) {
                        for (unsigned i = 0; i < a.base_length; i++) {
                            r = r > a.vec(j).el(i) ? r : a.vec(j).el(i);
                        }
                    }
                    return r;
#elif SIMD_USE_SSE2 && !SIMD_USE_SSE4_1
                    // no instruction for int8 max available, only for uint8
                    uint8x16 r = bit_xor(a.vec(0), 0x80);
                    for (unsigned j = 1; j < a.vec_length; ++j) {
                        uint8x16 ca = bit_xor(a.vec(j), 0x80);
                        r = max(r, ca);
                    }
                    return i_reduce_max(r) ^ 0x80;
#else
                    int8v r = a.vec(0);
                    for (unsigned j = 1; j < a.vec_length; ++j) {
                        r = max(r, a.vec(j));
                    }
                    return i_reduce_max(r);
#endif
                }

                // -----------------------------------------------------------------------------
                static inline int16_t i_reduce_max(const int16x8 &a);

                static inline uint16_t i_reduce_max(const uint16x8 &a) {
#if SIMD_USE_NULL
                    uint16_t r = a.el(0);
                    for (unsigned i = 0; i < a.length; i++) {
                        r = r > a.el(i) ? r : a.el(i);
                    }
                    return r;
#elif SIMD_USE_NEON64
                    return vmaxvq_u16(a.native());
#elif SIMD_USE_SSE4_1 || SIMD_USE_NEON || SIMD_USE_ALTIVEC || SIMD_USE_MSA
                    uint16x8 r = max(a, move8_l<4>(a));
                    r = max(r, move8_l<2>(r));
                    r = max(r, move8_l<1>(r));
                    return extract<0>(r);
#elif SIMD_USE_SSE2
                    // no instruction for uint16 max available, only for int16
                    int16x8 ca = bit_xor(a, 0x8000);
                    return i_reduce_max(ca) ^ 0x8000;
#endif
                }

#if SIMD_USE_AVX2
                static inline uint16_t i_reduce_max(const uint16x16 &a) {
                    uint16x8 r = detail::extract128<0>(a);
                    r = max(r, detail::extract128<1>(a));
                    return i_reduce_max(r);
                }
#endif

#if SIMD_USE_AVX512BW
                inline uint16_t i_reduce_max(const uint16<32> &a) {
                    uint16<16> r = detail::extract256<0>(a);
                    r = max(r, detail::extract256<1>(a));
                    return i_reduce_max(r);
                }
#endif

                template <unsigned N> inline uint16_t i_reduce_max(const uint16<N> &a) {
#if SIMD_USE_NULL
                    uint16_t r = std::numeric_limits<uint16_t>::min();
                    ;
                    for (unsigned j = 0; j < a.vec_length; ++j) {
                        for (unsigned i = 0; i < a.base_length; i++) {
                            r = r > a.vec(j).el(i) ? r : a.vec(j).el(i);
                        }
                    }
                    return r;
#elif SIMD_USE_SSE2 && !SIMD_USE_SSE4_1
                    // no instruction for uint16 max available, only for int16
                    int16x8 r = bit_xor(a.vec(0), 0x8000);
                    for (unsigned j = 1; j < a.vec_length; ++j) {
                        int16x8 ca = bit_xor(a.vec(j), 0x8000);
                        r = max(r, ca);
                    }
                    return i_reduce_max(r) ^ 0x8000;
#else
                    uint16v r = a.vec(0);
                    for (unsigned j = 1; j < a.vec_length; ++j) {
                        r = max(r, a.vec(j));
                    }
                    return i_reduce_max(r);
#endif
                }

                // -----------------------------------------------------------------------------

                static inline int16_t i_reduce_max(const int16x8 &a) {
#if SIMD_USE_NULL
                    int16_t r = a.el(0);
                    for (unsigned i = 0; i < a.length; i++) {
                        r = r > a.el(i) ? r : a.el(i);
                    }
                    return r;
#elif SIMD_USE_NEON64
                    return vmaxvq_s16(a.native());
#elif SIMD_USE_SSE2 || SIMD_USE_NEON || SIMD_USE_ALTIVEC || SIMD_USE_MSA
                    int16x8 r = max(a, move8_l<4>(a));
                    r = max(r, move8_l<2>(r));
                    r = max(r, move8_l<1>(r));
                    return extract<0>(r);
#endif
                }

#if SIMD_USE_AVX2
                static inline int16_t i_reduce_max(const int16x16 &a) {
                    int16x8 r = detail::extract128<0>(a);
                    r = max(r, detail::extract128<1>(a));
                    return i_reduce_max(r);
                }
#endif

#if SIMD_USE_AVX512BW
                inline int16_t i_reduce_max(const int16<32> &a) {
                    int16<16> r = detail::extract256<0>(a);
                    r = max(r, detail::extract256<1>(a));
                    return i_reduce_max(r);
                }
#endif

                template <unsigned N> inline int16_t i_reduce_max(const int16<N> &a) {
#if SIMD_USE_NULL
                    int16_t r = std::numeric_limits<int16_t>::min();
                    ;
                    for (unsigned j = 0; j < a.vec_length; ++j) {
                        for (unsigned i = 0; i < a.base_length; i++) {
                            r = r > a.vec(j).el(i) ? r : a.vec(j).el(i);
                        }
                    }
                    return r;
#else
                    int16v r = a.vec(0);
                    for (unsigned j = 1; j < a.vec_length; ++j) {
                        r = max(r, a.vec(j));
                    }
                    return i_reduce_max(r);
#endif
                }

                // -----------------------------------------------------------------------------

                static inline uint32_t i_reduce_max(const uint32x4 &a) {
#if SIMD_USE_NULL
                    uint32_t r = a.el(0);
                    for (unsigned i = 0; i < a.length; i++) {
                        r = r > a.el(i) ? r : a.el(i);
                    }
                    return r;
#elif SIMD_USE_NEON64
                    return vmaxvq_u32(a.native());
#elif SIMD_USE_SSE4_1 || SIMD_USE_NEON || SIMD_USE_ALTIVEC || SIMD_USE_MSA
                    uint32x4 r = max(a, move4_l<2>(a));
                    r = max(r, move4_l<1>(r));
                    return extract<0>(r);
#elif SIMD_USE_SSE2
                    mem_block<uint32x4> b = a;
                    uint32_t r = b[0];
                    for (unsigned i = 1; i < b.length; i++) {
                        r = r > b[i] ? r : b[i];
                    }
                    return r;
#endif
                }

#if SIMD_USE_AVX2
                static inline uint32_t i_reduce_max(const uint32x8 &a) {
                    uint32x4 r = detail::extract128<0>(a);
                    r = max(r, detail::extract128<1>(a));
                    r = max(r, move4_l<2>(r));
                    r = max(r, move4_l<1>(r));
                    return extract<0>(r);
                }
#endif

#if SIMD_USE_AVX512F
                static inline uint32_t i_reduce_max(const uint32<16> &a) {
                    return i_reduce_max((uint32<8>)max(extract256<0>(a), extract256<1>(a)));
                }
#endif

                template <unsigned N> inline uint32_t i_reduce_max(const uint32<N> &a) {
#if SIMD_USE_NULL
                    uint32_t r = std::numeric_limits<uint32_t>::min();
                    ;
                    for (unsigned j = 0; j < a.vec_length; ++j) {
                        for (unsigned i = 0; i < a.base_length; i++) {
                            r = r > a.vec(j).el(i) ? r : a.vec(j).el(i);
                        }
                    }
                    return r;
#else
                    uint32v r = a.vec(0);
                    for (unsigned j = 1; j < a.vec_length; ++j) {
                        r = max(r, a.vec(j));
                    }
                    return i_reduce_max(r);
#endif
                }

                // -----------------------------------------------------------------------------

                static inline int32_t i_reduce_max(const int32x4 &a) {
#if SIMD_USE_NULL
                    int32_t r = a.el(0);
                    for (unsigned i = 0; i < a.length; i++) {
                        r = r > a.el(i) ? r : a.el(i);
                    }
                    return r;
#elif SIMD_USE_NEON64
                    return vmaxvq_s32(a.native());
#elif SIMD_USE_SSE2 || SIMD_USE_NEON || SIMD_USE_ALTIVEC || SIMD_USE_MSA
                    int32x4 r = max(a, move4_l<2>(a));
                    r = max(r, move4_l<1>(r));
                    return extract<0>(r);
#endif
                }

#if SIMD_USE_AVX2
                static inline int32_t i_reduce_max(const int32x8 &a) {
                    int32x4 r = detail::extract128<0>(a);
                    r = max(r, detail::extract128<1>(a));
                    r = max(r, move4_l<2>(r));
                    r = max(r, move4_l<1>(r));
                    return extract<0>(r);
                }
#endif

#if SIMD_USE_AVX512F
                static inline int32_t i_reduce_max(const int32<16> &a) {
                    return i_reduce_max((int32<8>)max(extract256<0>(a), extract256<1>(a)));
                }
#endif

                template <unsigned N> inline int32_t i_reduce_max(const int32<N> &a) {
#if SIMD_USE_NULL
                    int32_t r = std::numeric_limits<int32_t>::min();
                    ;
                    for (unsigned j = 0; j < a.vec_length; ++j) {
                        for (unsigned i = 0; i < a.base_length; i++) {
                            r = r > a.vec(j).el(i) ? r : a.vec(j).el(i);
                        }
                    }
                    return r;
#else
                    int32v r = a.vec(0);
                    for (unsigned j = 1; j < a.vec_length; ++j) {
                        r = max(r, a.vec(j));
                    }
                    return i_reduce_max(r);
#endif
                }

                // -----------------------------------------------------------------------------

                static inline uint64_t i_reduce_max(const uint64x2 &a) {
#if SIMD_USE_AVX2 || SIMD_USE_NEON64 || SIMD_USE_VSX_207
                    uint64x2 r = max(a, move2_l<1>(a));
                    return extract<0>(r);
#elif SIMD_USE_SSE2 || SIMD_USE_NEON32
                    mem_block<uint64x2> b = a;
                    return b[0] > b[1] ? b[0] : b[1];
#elif SIMD_USE_NULL || SIMD_USE_ALTIVEC
                    uint64_t r = a.el(0);
                    for (unsigned i = 0; i < a.length; i++) {
                        r = r > a.el(i) ? r : a.el(i);
                    }
                    return r;
#else
                    return SIMD_NOT_IMPLEMENTED1(a);
#endif
                }

#if SIMD_USE_AVX2
                static inline uint64_t i_reduce_max(const uint64x4 &a) {
                    uint64x2 r = detail::extract128<0>(a);
                    r = max(r, detail::extract128<1>(a));
                    r = max(r, move2_l<1>(r));
                    return extract<0>(r);
                }
#endif

#if SIMD_USE_AVX512F
                static inline uint64_t i_reduce_max(const uint64<8> &a) {
                    return i_reduce_max((uint64<4>)max(extract256<0>(a), extract256<1>(a)));
                }
#endif

                template <unsigned N> inline uint64_t i_reduce_max(const uint64<N> &a) {
#if SIMD_USE_AVX2 || SIMD_USE_NEON64 || SIMD_USE_VSX_207 || SIMD_USE_MSA
                    uint64v r = a.vec(0);
                    for (unsigned j = 1; j < a.vec_length; ++j) {
                        r = max(r, a.vec(j));
                    }
                    return i_reduce_max(r);
#elif SIMD_USE_SSE2 || SIMD_USE_NEON32
                    uint64_t r = std::numeric_limits<uint64_t>::min();
                    for (unsigned j = 0; j < a.vec_length; ++j) {
                        mem_block<uint64v> b = a.vec(j);
                        for (unsigned i = 0; i < a.base_length; i++) {
                            r = r > b[i] ? r : b[i];
                        }
                    }
                    return r;
#elif SIMD_USE_NULL || SIMD_USE_ALTIVEC
                    uint64_t r = std::numeric_limits<uint64_t>::min();
                    ;
                    for (unsigned j = 0; j < a.vec_length; ++j) {
                        for (unsigned i = 0; i < a.base_length; i++) {
                            r = r > a.vec(j).el(i) ? r : a.vec(j).el(i);
                        }
                    }
                    return r;
#else
                    return SIMD_NOT_IMPLEMENTED1(a);
#endif
                }

                // -----------------------------------------------------------------------------

                static inline int64_t i_reduce_max(const int64x2 &a) {
#if SIMD_USE_AVX2 || SIMD_USE_NEON64 || SIMD_USE_VSX_207 || SIMD_USE_MSA
                    int64x2 r = max(a, move2_l<1>(a));
                    return extract<0>(r);
#elif SIMD_USE_SSE2 || SIMD_USE_NEON32
                    mem_block<int64x2> b = a;
                    return b[0] > b[1] ? b[0] : b[1];
#elif SIMD_USE_NULL || SIMD_USE_ALTIVEC
                    int64_t r = a.el(0);
                    for (unsigned i = 0; i < a.length; i++) {
                        r = r > a.el(i) ? r : a.el(i);
                    }
                    return r;
#else
                    return SIMD_NOT_IMPLEMENTED1(a);
#endif
                }

#if SIMD_USE_AVX2
                static inline int64_t i_reduce_max(const int64x4 &a) {
                    int64x2 r = detail::extract128<0>(a);
                    r = max(r, detail::extract128<1>(a));
                    r = max(r, move2_l<1>(r));
                    return extract<0>(r);
                }
#endif

#if SIMD_USE_AVX512F
                static inline int64_t i_reduce_max(const int64<8> &a) {
                    return i_reduce_max((int64<4>)max(extract256<0>(a), extract256<1>(a)));
                }
#endif

                template <unsigned N> inline int64_t i_reduce_max(const int64<N> &a) {
#if SIMD_USE_AXV2 || SIMD_USE_NEON64 || SIMD_USE_VSX_207 || SIMD_USE_MSA
                    int64v r = a.vec(0);
                    for (unsigned j = 1; j < a.vec_length; ++j) {
                        r = max(r, a.vec(j));
                    }
                    return i_reduce_max(r);
#elif SIMD_USE_SSE2 || SIMD_USE_NEON32
                    int64_t r = std::numeric_limits<int64_t>::min();
                    ;
                    for (unsigned j = 0; j < a.vec_length; ++j) {
                        mem_block<int64v> b = a.vec(j);
                        for (unsigned i = 0; i < a.base_length; i++) {
                            r = r > b[i] ? r : b[i];
                        }
                    }
                    return r;
#elif SIMD_USE_NULL || SIMD_USE_ALTIVEC
                    int64_t r = std::numeric_limits<int64_t>::min();
                    ;
                    for (unsigned j = 0; j < a.vec_length; ++j) {
                        for (unsigned i = 0; i < a.base_length; i++) {
                            r = r > a.vec(j).el(i) ? r : a.vec(j).el(i);
                        }
                    }
                    return r;
#else
                    return SIMD_NOT_IMPLEMENTED1(a);
#endif
                }

                // -----------------------------------------------------------------------------

            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
