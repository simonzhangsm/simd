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

#ifndef SIMD_DETAIL_INSN_MOVE_R_H
#define SIMD_DETAIL_INSN_MOVE_R_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/shuffle/shuffle_mask.h>
#include <bigmath/simd/detail/vector_array_macros.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {


                template <unsigned shift> inline uint8x16 i_move16_r(const uint8x16 &a) {
                    static_assert(shift <= 16, "Selector out of range");

#if SIMD_USE_NULL
                    return detail::null::move_n_r<shift>(a);
#elif SIMD_USE_SSE2
                    return _mm_slli_si128(a.native(), shift);
#elif SIMD_USE_NEON
                    uint8x16 zero = make_zero();
                    return vextq_u8(zero.native(), a.native(), 16 - shift);
#elif SIMD_USE_ALTIVEC
                    // return align<16-shift>((uint8x16) make_zero(), a);
                    return vec_sld_biendian<16 - shift>((uint8<16>)make_zero(), a);
#elif SIMD_USE_MSA
                    uint8x16 zero = make_zero();
                    return (v16u8)__msa_sldi_b((v16i8)a.native(), (v16i8)zero.native(), 16 - shift);
#endif
                }

#if SIMD_USE_AVX2
                template <unsigned shift> inline uint8x32 i_move16_r(const uint8x32 &a) {
                    static_assert(shift <= 16, "Selector out of range");
                    return _mm256_slli_si256(a.native(), shift);
                }
#endif

#if SIMD_USE_AVX512BW
                template <unsigned shift> inline uint8<64> i_move16_r(const uint8<64> &a) {
                    static_assert(shift <= 16, "Selector out of range");
                    return _mm512_bslli_epi128(a.native(), shift);
                }
#endif

                template <unsigned shift, unsigned N> inline uint8<N> i_move16_r(const uint8<N> &a) {
                    static_assert(shift <= 16, "Selector out of range");
                    SIMD_VEC_ARRAY_IMPL1(uint8<N>, i_move16_r<shift>, a);
                }

                // -----------------------------------------------------------------------------

                template <unsigned shift> inline uint16<8> i_move8_r(const uint16<8> &a) {
#if SIMD_USE_NULL
                    return detail::null::move_n_r<shift>(a);
#else
                    return (uint16<8>)i_move16_r<shift * 2>(uint8<16>(a));
#endif
                }

#if SIMD_USE_AVX2
                template <unsigned shift> inline uint16<16> i_move8_r(const uint16<16> &a) {
                    static_assert(shift <= 8, "Selector out of range");
                    return _mm256_slli_si256(a.native(), shift * 2);
                }
#endif

#if SIMD_USE_AVX512BW
                template <unsigned shift> inline uint16<32> i_move8_r(const uint16<32> &a) {
                    static_assert(shift <= 8, "Selector out of range");
                    return _mm512_bslli_epi128(a.native(), shift * 2);
                }
#endif

                template <unsigned shift, unsigned N> inline uint16<N> i_move8_r(const uint16<N> &a) {
                    SIMD_VEC_ARRAY_IMPL1(uint16<N>, i_move8_r<shift>, a);
                }

                // -----------------------------------------------------------------------------

                template <unsigned shift> inline uint32<4> i_move4_r(const uint32<4> &a) {
#if SIMD_USE_NULL
                    return detail::null::move_n_r<shift>(a);
#else
                    return (uint32<4>)i_move16_r<shift * 4>(uint8<16>(a));
#endif
                }

#if SIMD_USE_AVX2
                template <unsigned shift> inline uint32<8> i_move4_r(const uint32<8> &a) {
                    static_assert(shift <= 4, "Selector out of range");
                    return _mm256_slli_si256(a.native(), shift * 4);
                }
#endif

#if SIMD_USE_AVX512F
                template <unsigned shift> inline uint32<16> i_move4_r(const uint32<16> &a) {
                    static_assert(shift <= 4, "Selector out of range");
                    switch (shift) {
                        default:
                        case 0:
                            return a;
                        case 1:
                            return _mm512_maskz_shuffle_epi32(0xeeee,
                                                              a.native(),
                                                              _MM_PERM_ENUM(_MM_SHUFFLE(2, 1, 0, 0)));
                        case 2:
                            return _mm512_maskz_shuffle_epi32(0xcccc,
                                                              a.native(),
                                                              _MM_PERM_ENUM(_MM_SHUFFLE(1, 0, 0, 0)));
                        case 3:
                            return _mm512_maskz_shuffle_epi32(0x8888,
                                                              a.native(),
                                                              _MM_PERM_ENUM(_MM_SHUFFLE(0, 0, 0, 0)));
                        case 4:
                            return make_zero();
                    }
                }
#endif

                template <unsigned shift, unsigned N> inline uint32<N> i_move4_r(const uint32<N> &a) {
                    SIMD_VEC_ARRAY_IMPL1(uint32<N>, i_move4_r<shift>, a);
                }

                // -----------------------------------------------------------------------------

                template <unsigned shift> inline uint64<2> i_move2_r(const uint64<2> &a) {
#if SIMD_USE_NULL || (SIMD_USE_ALTIVEC && !SIMD_USE_VSX_207)
                    return detail::null::move_n_r<shift>(a);
#else
                    return (uint64<2>)i_move16_r<shift * 8>(uint8<16>(a));
#endif
                }

#if SIMD_USE_AVX2
                template <unsigned shift> inline uint64<4> i_move2_r(const uint64<4> &a) {
                    static_assert(shift <= 2, "Selector out of range");
                    return _mm256_slli_si256(a.native(), shift * 8);
                }
#endif

#if SIMD_USE_AVX512F
                template <unsigned shift> inline uint64<8> i_move2_r(const uint64<8> &a) {
                    static_assert(shift <= 4, "Selector out of range");
                    return (uint64<8>)i_move4_r<shift * 2>(uint32<16>(a));
                }
#endif

                template <unsigned shift, unsigned N> inline uint64<N> i_move2_r(const uint64<N> &a) {
                    SIMD_VEC_ARRAY_IMPL1(uint64<N>, i_move2_r<shift>, a);
                }

                // -----------------------------------------------------------------------------

                template <unsigned shift> inline float32<4> i_move4_r(const float32<4> &a) {
#if SIMD_USE_NULL || SIMD_USE_NEON_NO_FLT_SP
                    return detail::null::move_n_r<shift>(a);
#else
                    return (float32<4>)i_move16_r<shift * 4>(uint8<16>(a));
#endif
                }

#if SIMD_USE_AVX
                template <unsigned shift> inline float32<8> i_move4_r(const float32<8> &a) {
                    static_assert(shift <= 4, "Selector out of range");
                    return (float32<8>)i_move16_r<shift * 4>(uint8<32>(a));
                }
#endif

#if SIMD_USE_AVX512F
                template <unsigned shift> inline float32<16> i_move4_r(const float32<16> &a) {
                    static_assert(shift <= 4, "Selector out of range");
                    switch (shift) {
                        default:
                        case 0:
                            return a;
                        case 1:
                            return _mm512_maskz_shuffle_ps(0xeeee, a.native(), a.native(), _MM_SHUFFLE(2, 1, 0, 0));
                        case 2:
                            return _mm512_maskz_shuffle_ps(0xcccc, a.native(), a.native(), _MM_SHUFFLE(1, 0, 0, 0));
                        case 3:
                            return _mm512_maskz_shuffle_ps(0x8888, a.native(), a.native(), _MM_SHUFFLE(0, 0, 0, 0));
                        case 4:
                            return make_zero();
                    }
                }
#endif

                template <unsigned shift, unsigned N> inline float32<N> i_move4_r(const float32<N> &a) {
                    SIMD_VEC_ARRAY_IMPL1(float32<N>, i_move4_r<shift>, a);
                }

                // -----------------------------------------------------------------------------

                template <unsigned shift> inline float64<2> i_move2_r(const float64<2> &a) {
#if SIMD_USE_SSE2 || SIMD_USE_NEON64 || SIMD_USE_VSX_206 || SIMD_USE_MSA
                    return (float64<2>)i_move16_r<shift * 8>(uint8<16>(a));
#elif SIMD_USE_NULL || SIMD_USE_NEON || SIMD_USE_ALTIVEC
                    return detail::null::move_n_r<shift>(a);
#endif
                }

#if SIMD_USE_AVX
                template <unsigned shift> inline float64<4> i_move2_r(const float64<4> &a) {
                    static_assert(shift <= 2, "Selector out of range");
                    return (float64<4>)i_move16_r<shift * 8>(uint8<32>(a));
                }
#endif

#if SIMD_USE_AVX512F
                template <unsigned shift> inline float64<8> i_move2_r(const float64<8> &a) {
                    static_assert(shift <= 2, "Selector out of range");
                    switch (shift) {
                        default:
                        case 0:
                            return a;
                        case 1:
                            return _mm512_maskz_shuffle_pd(0xaa, a.native(), a.native(), SIMD_SHUFFLE_MASK_2x2_4(0, 0));
                        case 2:
                            return make_zero();
                    }
                }
#endif

                template <unsigned shift, unsigned N> inline float64<N> i_move2_r(const float64<N> &a) {
                    SIMD_VEC_ARRAY_IMPL1(float64<N>, i_move2_r<shift>, a);
                }

                // -----------------------------------------------------------------------------
                // Certain compilers don't like zero or full vector width moves. The templates
                // below offer a warkaround

                template <unsigned count> struct i_move2_r_wrapper {
                    template <class V> static inline V run(const V &arg) {
                        return i_move2_r<count>(arg);
                    }
                };
                template <> struct i_move2_r_wrapper<0> {
                    template <class V> static inline V run(const V &arg) {
                        return arg;
                    }
                };
                template <> struct i_move2_r_wrapper<2> {
                    template <class V> static inline V run(const V &) {
                        return (V)make_zero();
                    }
                };

                template <unsigned count> struct i_move4_r_wrapper {
                    template <class V> static inline V run(const V &arg) {
                        return i_move4_r<count>(arg);
                    }
                };
                template <> struct i_move4_r_wrapper<0> {
                    template <class V> static inline V run(const V &arg) {
                        return arg;
                    }
                };
                template <> struct i_move4_r_wrapper<4> {
                    template <class V> static inline V run(const V &) {
                        return (V)make_zero();
                    }
                };

                template <unsigned count> struct i_move8_r_wrapper {
                    template <class V> static inline V run(const V &arg) {
                        return i_move8_r<count>(arg);
                    }
                };
                template <> struct i_move8_r_wrapper<0> {
                    template <class V> static inline V run(const V &arg) {
                        return arg;
                    }
                };
                template <> struct i_move8_r_wrapper<8> {
                    template <class V> static inline V run(const V &) {
                        return (V)make_zero();
                    }
                };

                template <unsigned count> struct i_move16_r_wrapper {
                    template <class V> static inline V run(const V &arg) {
                        return i_move16_r<count>(arg);
                    }
                };
                template <> struct i_move16_r_wrapper<0> {
                    template <class V> static inline V run(const V &arg) {
                        return arg;
                    }
                };
                template <> struct i_move16_r_wrapper<16> {
                    template <class V> static inline V run(const V &) {
                        return (V)make_zero();
                    }
                };

            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
