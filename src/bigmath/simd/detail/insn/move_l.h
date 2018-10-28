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

#ifndef SIMD_DETAIL_INSN_MOVE_L_H
#define SIMD_DETAIL_INSN_MOVE_L_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/core/permute4.h>
#include <bigmath/simd/detail/null/shuffle.h>
#include <bigmath/simd/detail/shuffle/shuffle_mask.h>
#include <bigmath/simd/detail/vector_array_macros.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {

#if SIMD_USE_ALTIVEC
                template <unsigned shift>
                inline uint8<16> vec_sld_biendian(const uint8<16> &lower, const uint8<16> &upper) {
#if SIMD_BIG_ENDIAN
                    return vec_sld(lower.native(), upper.native(), shift);
#else
                    // by default GCC adjusts vec_sld element order to match endianness of the target
                    return vec_sld(upper.native(), lower.native(), 16 - shift);
#endif
                }
#endif

                template <unsigned shift> inline uint8x16 i_move16_l(const uint8x16 &a) {
                    static_assert(shift <= 16, "Selector out of range");
#if SIMD_USE_NULL
                    return detail::null::move_n_l<shift>(a);
#elif SIMD_USE_SSE2
                    return _mm_srli_si128(a.native(), shift);
#elif SIMD_USE_NEON
                    uint8x16 z = make_zero();
                    return vextq_u8(a.native(), z.native(), shift);
#elif SIMD_USE_ALTIVEC
                    // return align<shift>(a, (uint8x16) make_zero());
                    return vec_sld_biendian<shift>((uint8<16>)a, (uint8<16>)make_zero());
#elif SIMD_USE_MSA
                    uint8x16 zero = make_zero();
                    return (v16u8)__msa_sldi_b((v16i8)zero.native(), (v16i8)a.native(), shift);
#endif
                }

#if SIMD_USE_AVX2
                template <unsigned shift> inline uint8x32 i_move16_l(const uint8x32 &a) {
                    static_assert(shift <= 16, "Selector out of range");
                    return _mm256_srli_si256(a.native(), shift);
                }
#endif

#if SIMD_USE_AVX512BW
                template <unsigned shift> inline uint8<64> i_move16_l(const uint8<64> &a) {
                    static_assert(shift <= 16, "Selector out of range");
                    return _mm512_bsrli_epi128(a.native(), shift);
                }
#endif

                template <unsigned shift, unsigned N> inline uint8<N> i_move16_l(const uint8<N> &a) {
                    static_assert(shift <= 16, "Selector out of range");
                    SIMD_VEC_ARRAY_IMPL1(uint8<N>, i_move16_l<shift>, a);
                }

                // -----------------------------------------------------------------------------

                template <unsigned shift> inline uint16<8> i_move8_l(const uint16<8> &a) {
#if SIMD_USE_NULL
                    return detail::null::move_n_l<shift>(a);
#else
                    return (uint16<8>)i_move16_l<shift * 2>(uint8<16>(a));
#endif
                }

#if SIMD_USE_AVX2
                template <unsigned shift> inline uint16<16> i_move8_l(const uint16<16> &a) {
                    static_assert(shift <= 8, "Selector out of range");
                    return _mm256_srli_si256(a.native(), shift * 2);
                }
#endif

#if SIMD_USE_AVX512BW
                template <unsigned shift> inline uint16<32> i_move8_l(const uint16<32> &a) {
                    static_assert(shift <= 8, "Selector out of range");
                    return _mm512_bsrli_epi128(a.native(), shift * 2);
                }
#endif

                template <unsigned shift, unsigned N> inline uint16<N> i_move8_l(const uint16<N> &a) {
                    SIMD_VEC_ARRAY_IMPL1(uint16<N>, i_move8_l<shift>, a);
                }

                // -----------------------------------------------------------------------------

                template <unsigned shift> inline uint32<4> i_move4_l(const uint32<4> &a) {
#if SIMD_USE_NULL
                    return detail::null::move_n_l<shift>(a);
#else
                    return (uint32<4>)i_move16_l<shift * 4>(uint8<16>(a));
#endif
                }

#if SIMD_USE_AVX2
                template <unsigned shift> inline uint32<8> i_move4_l(const uint32<8> &a) {
                    static_assert(shift <= 4, "Selector out of range");
                    return _mm256_srli_si256(a.native(), shift * 4);
                }
#endif

#if SIMD_USE_AVX512F
                template <unsigned shift> inline uint32<16> i_move4_l(const uint32<16> &a) {
                    static_assert(shift <= 4, "Selector out of range");
                    switch (shift) {
                        default:
                        case 0:
                            return a;
                        case 1:
                            return _mm512_maskz_shuffle_epi32(0x7777,
                                                              a.native(),
                                                              _MM_PERM_ENUM(_MM_SHUFFLE(3, 3, 2, 1)));
                        case 2:
                            return _mm512_maskz_shuffle_epi32(0x3333,
                                                              a.native(),
                                                              _MM_PERM_ENUM(_MM_SHUFFLE(3, 3, 3, 2)));
                        case 3:
                            return _mm512_maskz_shuffle_epi32(0x1111,
                                                              a.native(),
                                                              _MM_PERM_ENUM(_MM_SHUFFLE(3, 3, 3, 3)));
                        case 4:
                            return make_zero();
                    }
                }
#endif

                template <unsigned shift, unsigned N> inline uint32<N> i_move4_l(const uint32<N> &a) {
                    SIMD_VEC_ARRAY_IMPL1(uint32<N>, i_move4_l<shift>, a);
                }

                // -----------------------------------------------------------------------------

                template <unsigned shift> inline uint64<2> i_move2_l(const uint64<2> &a) {
#if SIMD_USE_NULL || (SIMD_USE_ALTIVEC && !SIMD_USE_VSX_207)
                    return detail::null::move_n_l<shift>(a);
#else
                    return (uint64<2>)i_move16_l<shift * 8>(uint8<16>(a));
#endif
                }

#if SIMD_USE_AVX2
                template <unsigned shift> inline uint64<4> i_move2_l(const uint64<4> &a) {
                    static_assert(shift <= 2, "Selector out of range");
                    return _mm256_srli_si256(a.native(), shift * 8);
                }
#endif

#if SIMD_USE_AVX512F
                template <unsigned shift> inline uint64<8> i_move2_l(const uint64<8> &a) {
                    static_assert(shift <= 4, "Selector out of range");
                    return (uint64<8>)i_move4_l<shift * 2>(uint32<16>(a));
                }
#endif

                template <unsigned shift, unsigned N> inline uint64<N> i_move2_l(const uint64<N> &a) {
                    SIMD_VEC_ARRAY_IMPL1(uint64<N>, i_move2_l<shift>, a);
                }

                // -----------------------------------------------------------------------------

                template <unsigned shift> inline float32<4> i_move4_l(const float32<4> &a) {
#if SIMD_USE_NULL || SIMD_USE_NEON_NO_FLT_SP
                    return detail::null::move_n_l<shift>(a);
#else
                    return (float32<4>)i_move16_l<shift * 4>(uint8<16>(a));
#endif
                }

#if SIMD_USE_AVX
                template <unsigned shift> inline float32<8> i_move4_l(const float32<8> &a) {
                    static_assert(shift <= 4, "Selector out of range");
                    return (float32<8>)i_move16_l<shift * 4>(uint8<32>(a));
                }
#endif

#if SIMD_USE_AVX512F
                template <unsigned shift> inline float32<16> i_move4_l(const float32<16> &a) {
                    static_assert(shift <= 4, "Selector out of range");
                    switch (shift) {
                        default:
                        case 0:
                            return a;
                        case 1:
                            return _mm512_maskz_shuffle_ps(0x7777, a.native(), a.native(), _MM_SHUFFLE(3, 3, 2, 1));
                        case 2:
                            return _mm512_maskz_shuffle_ps(0x3333, a.native(), a.native(), _MM_SHUFFLE(3, 3, 3, 2));
                        case 3:
                            return _mm512_maskz_shuffle_ps(0x1111, a.native(), a.native(), _MM_SHUFFLE(3, 3, 3, 3));
                        case 4:
                            return make_zero();
                    }
                }
#endif

                template <unsigned shift, unsigned N> inline float32<N> i_move4_l(const float32<N> &a) {
                    SIMD_VEC_ARRAY_IMPL1(float32<N>, i_move4_l<shift>, a);
                }

                // -----------------------------------------------------------------------------

                template <unsigned shift> inline float64<2> i_move2_l(const float64<2> &a) {
#if SIMD_USE_SSE2 || SIMD_USE_NEON64 || SIMD_USE_VSX_206 || SIMD_USE_MSA
                    return (float64<2>)i_move16_l<shift * 8>(uint8<16>(a));
#elif SIMD_USE_NULL || SIMD_USE_NEON32 || SIMD_USE_ALTIVEC
                    return detail::null::move_n_l<shift>(a);
#endif
                }

#if SIMD_USE_AVX
                template <unsigned shift> inline float64<4> i_move2_l(const float64<4> &a) {
                    static_assert(shift <= 2, "Selector out of range");
                    return (float64<4>)i_move16_l<shift * 8>(uint8<32>(a));
                }
#endif

#if SIMD_USE_AVX512F
                template <unsigned shift> inline float64<8> i_move2_l(const float64<8> &a) {
                    static_assert(shift <= 2, "Selector out of range");
                    switch (shift) {
                        default:
                        case 0:
                            return a;
                        case 1:
                            return _mm512_maskz_shuffle_pd(0x55, a.native(), a.native(), SIMD_SHUFFLE_MASK_2x2_4(1, 1));
                        case 2:
                            return make_zero();
                    }
                }
#endif

                template <unsigned shift, unsigned N> inline float64<N> i_move2_l(const float64<N> &a) {
                    SIMD_VEC_ARRAY_IMPL1(float64<N>, i_move2_l<shift>, a);
                }

                // -----------------------------------------------------------------------------
                // Certain compilers don't like zero or full vector width moves. The templates
                // below offer a warkaround

                template <unsigned count> struct i_move2_l_wrapper {
                    template <class V> static inline V run(const V &arg) {
                        return i_move2_l<count>(arg);
                    }
                };
                template <> struct i_move2_l_wrapper<0> {
                    template <class V> static inline V run(const V &arg) {
                        return arg;
                    }
                };
                template <> struct i_move2_l_wrapper<2> {
                    template <class V> static inline V run(const V &) {
                        return (V)make_zero();
                    }
                };

                template <unsigned count> struct i_move4_l_wrapper {
                    template <class V> static inline V run(const V &arg) {
                        return i_move4_l<count>(arg);
                    }
                };
                template <> struct i_move4_l_wrapper<0> {
                    template <class V> static inline V run(const V &arg) {
                        return arg;
                    }
                };
                template <> struct i_move4_l_wrapper<4> {
                    template <class V> static inline V run(const V &) {
                        return (V)make_zero();
                    }
                };

                template <unsigned count> struct i_move8_l_wrapper {
                    template <class V> static inline V run(const V &arg) {
                        return i_move8_l<count>(arg);
                    }
                };
                template <> struct i_move8_l_wrapper<0> {
                    template <class V> static inline V run(const V &arg) {
                        return arg;
                    }
                };
                template <> struct i_move8_l_wrapper<8> {
                    template <class V> static inline V run(const V &) {
                        return (V)make_zero();
                    }
                };

                template <unsigned count> struct i_move16_l_wrapper {
                    template <class V> static inline V run(const V &arg) {
                        return i_move16_l<count>(arg);
                    }
                };
                template <> struct i_move16_l_wrapper<0> {
                    template <class V> static inline V run(const V &arg) {
                        return arg;
                    }
                };
                template <> struct i_move16_l_wrapper<16> {
                    template <class V> static inline V run(const V &) {
                        return (V)make_zero();
                    }
                };

            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
