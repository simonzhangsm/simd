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

#ifndef SIMD_DETAIL_INSN_DETAIL_CAST_BITWISE_H
#define SIMD_DETAIL_INSN_DETAIL_CAST_BITWISE_H

#include <bigmath/simd/types.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {

            /*  Note that in this function we are invoking undefined behavior that happens
                to work in all compilers the library supports. The only non-undefined way
                to do bitwise data transfer between unrelated types without breaking strict
                aliasing rules is the memcpy() function. Unfortunately some compilers can't
                fully optimize out the overhead of the function which leads to unnecessary
                data movement to the stack.

                Note that this function does not fully work with vector types even in C++11
                mode where they are trivial types and thus may be placed in an union.
                Vectors containing one or two native vectors are fine, but larger vectors
                containing 4 or more native vectors result in internal compiler errors or
                miscompiled code on some compilers.
            */
            template <class T, class R> inline void cast_bitwise(const T &t, R &r) {
                static_assert(sizeof(R) == sizeof(T), "Size mismatch");
                union {
                    T t_union;
                    R r_union;
                };
                t_union = t;
                r = r_union;
            }

            enum {
                VECTOR_CAST_TYPE_1_TO_1,
                VECTOR_CAST_TYPE_SPLIT2,
                VECTOR_CAST_TYPE_COMBINE2,
                VECTOR_CAST_TYPE_INVALID
            };

#if (__GNUC__ >= 6) && !defined(__INTEL_COMPILER) && !defined(__clang__)
/*  native_cast, native_cast_split and native_cast_combine uses native vector
    type as class template parameter. On GCC vector types have alignment
    attributes specified on some architectures. This leads to "ignored
    attributes" warning, because the attributes are not part of the type.
    Since simd always uses the same attributes for all native_type members
    we can safely ignore this warning.
*/
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"
#endif

            // The Size argument is needed to disambiguate vectors of different size on old
            // GNU ABIs.
            template <unsigned Size, class NativeT, class NativeR, bool IsVarArray> struct native_cast;

            template <unsigned Size, class T, class R> struct native_cast<Size, T, R, false> {
                static inline R cast(const T &t) {
                    return R(t);
                }
            };

            template <unsigned Size, class T> struct native_cast<Size, T, T, false> {
                static inline T cast(const T &t) {
                    return t;
                }
            };

            template <unsigned Size, class T, class R> struct native_cast<Size, T, R, true> {
                static inline R cast(const T &t) {
                    R r;
                    cast_bitwise(t, r);
                    return r;
                }
            };

#define NATIVE_CAST_IMPL(SIZE, T_TYPE, R_TYPE, FUNC)              \
    template <> struct native_cast<SIZE, T_TYPE, R_TYPE, false> { \
        static inline R_TYPE cast(const T_TYPE &t) {              \
            return FUNC(t);                                       \
        }                                                         \
    }

#if SIMD_USE_SSE2
            NATIVE_CAST_IMPL(16, __m128, __m128i, _mm_castps_si128);
            NATIVE_CAST_IMPL(16, __m128, __m128d, _mm_castps_pd);
            NATIVE_CAST_IMPL(16, __m128i, __m128, _mm_castsi128_ps);
            NATIVE_CAST_IMPL(16, __m128i, __m128d, _mm_castsi128_pd);
            NATIVE_CAST_IMPL(16, __m128d, __m128i, _mm_castpd_si128);
            NATIVE_CAST_IMPL(16, __m128d, __m128, _mm_castpd_ps);
#endif

#if SIMD_USE_AVX
            NATIVE_CAST_IMPL(32, __m256, __m256i, _mm256_castps_si256);
            NATIVE_CAST_IMPL(32, __m256, __m256d, _mm256_castps_pd);
            NATIVE_CAST_IMPL(32, __m256i, __m256, _mm256_castsi256_ps);
            NATIVE_CAST_IMPL(32, __m256i, __m256d, _mm256_castsi256_pd);
            NATIVE_CAST_IMPL(32, __m256d, __m256i, _mm256_castpd_si256);
            NATIVE_CAST_IMPL(32, __m256d, __m256, _mm256_castpd_ps);
#endif

#if SIMD_USE_AVX512F
            NATIVE_CAST_IMPL(64, __m512, __m512i, _mm512_castps_si512);
            NATIVE_CAST_IMPL(64, __m512, __m512d, _mm512_castps_pd);
            NATIVE_CAST_IMPL(64, __m512i, __m512, _mm512_castsi512_ps);
            NATIVE_CAST_IMPL(64, __m512i, __m512d, _mm512_castsi512_pd);
            NATIVE_CAST_IMPL(64, __m512d, __m512i, _mm512_castpd_si512);
            NATIVE_CAST_IMPL(64, __m512d, __m512, _mm512_castpd_ps);
#endif

#if SIMD_USE_NEON
            NATIVE_CAST_IMPL(16, float32x4_t, uint64x2_t, vreinterpretq_u64_f32);
            NATIVE_CAST_IMPL(16, float32x4_t, int64x2_t, vreinterpretq_s64_f32);
            NATIVE_CAST_IMPL(16, float32x4_t, uint32x4_t, vreinterpretq_u32_f32);
            NATIVE_CAST_IMPL(16, float32x4_t, int32x4_t, vreinterpretq_s32_f32);
            NATIVE_CAST_IMPL(16, float32x4_t, uint16x8_t, vreinterpretq_u16_f32);
            NATIVE_CAST_IMPL(16, float32x4_t, int16x8_t, vreinterpretq_s16_f32);
            NATIVE_CAST_IMPL(16, float32x4_t, uint8x16_t, vreinterpretq_u8_f32);
            NATIVE_CAST_IMPL(16, float32x4_t, int8x16_t, vreinterpretq_s8_f32);

            NATIVE_CAST_IMPL(16, uint64x2_t, int64x2_t, vreinterpretq_s64_u64);
            NATIVE_CAST_IMPL(16, uint64x2_t, uint32x4_t, vreinterpretq_u32_u64);
            NATIVE_CAST_IMPL(16, uint64x2_t, int32x4_t, vreinterpretq_s32_u64);
            NATIVE_CAST_IMPL(16, uint64x2_t, uint16x8_t, vreinterpretq_u16_u64);
            NATIVE_CAST_IMPL(16, uint64x2_t, int16x8_t, vreinterpretq_s16_u64);
            NATIVE_CAST_IMPL(16, uint64x2_t, uint8x16_t, vreinterpretq_u8_u64);
            NATIVE_CAST_IMPL(16, uint64x2_t, int8x16_t, vreinterpretq_s8_u64);
            NATIVE_CAST_IMPL(16, uint64x2_t, float32x4_t, vreinterpretq_f32_u64);

            NATIVE_CAST_IMPL(16, int64x2_t, uint64x2_t, vreinterpretq_u64_s64);
            NATIVE_CAST_IMPL(16, int64x2_t, uint32x4_t, vreinterpretq_u32_s64);
            NATIVE_CAST_IMPL(16, int64x2_t, int32x4_t, vreinterpretq_s32_s64);
            NATIVE_CAST_IMPL(16, int64x2_t, uint16x8_t, vreinterpretq_u16_s64);
            NATIVE_CAST_IMPL(16, int64x2_t, int16x8_t, vreinterpretq_s16_s64);
            NATIVE_CAST_IMPL(16, int64x2_t, uint8x16_t, vreinterpretq_u8_s64);
            NATIVE_CAST_IMPL(16, int64x2_t, int8x16_t, vreinterpretq_s8_s64);
            NATIVE_CAST_IMPL(16, int64x2_t, float32x4_t, vreinterpretq_f32_s64);

            NATIVE_CAST_IMPL(16, uint32x4_t, uint64x2_t, vreinterpretq_u64_u32);
            NATIVE_CAST_IMPL(16, uint32x4_t, int64x2_t, vreinterpretq_s64_u32);
            NATIVE_CAST_IMPL(16, uint32x4_t, int32x4_t, vreinterpretq_s32_u32);
            NATIVE_CAST_IMPL(16, uint32x4_t, uint16x8_t, vreinterpretq_u16_u32);
            NATIVE_CAST_IMPL(16, uint32x4_t, int16x8_t, vreinterpretq_s16_u32);
            NATIVE_CAST_IMPL(16, uint32x4_t, uint8x16_t, vreinterpretq_u8_u32);
            NATIVE_CAST_IMPL(16, uint32x4_t, int8x16_t, vreinterpretq_s8_u32);
            NATIVE_CAST_IMPL(16, uint32x4_t, float32x4_t, vreinterpretq_f32_u32);

            NATIVE_CAST_IMPL(16, int32x4_t, uint64x2_t, vreinterpretq_u64_s32);
            NATIVE_CAST_IMPL(16, int32x4_t, int64x2_t, vreinterpretq_s64_s32);
            NATIVE_CAST_IMPL(16, int32x4_t, uint32x4_t, vreinterpretq_u32_s32);
            NATIVE_CAST_IMPL(16, int32x4_t, uint16x8_t, vreinterpretq_u16_s32);
            NATIVE_CAST_IMPL(16, int32x4_t, int16x8_t, vreinterpretq_s16_s32);
            NATIVE_CAST_IMPL(16, int32x4_t, uint8x16_t, vreinterpretq_u8_s32);
            NATIVE_CAST_IMPL(16, int32x4_t, int8x16_t, vreinterpretq_s8_s32);
            NATIVE_CAST_IMPL(16, int32x4_t, float32x4_t, vreinterpretq_f32_s32);

            NATIVE_CAST_IMPL(16, uint16x8_t, uint64x2_t, vreinterpretq_u64_u16);
            NATIVE_CAST_IMPL(16, uint16x8_t, int64x2_t, vreinterpretq_s64_u16);
            NATIVE_CAST_IMPL(16, uint16x8_t, uint32x4_t, vreinterpretq_u32_u16);
            NATIVE_CAST_IMPL(16, uint16x8_t, int32x4_t, vreinterpretq_s32_u16);
            NATIVE_CAST_IMPL(16, uint16x8_t, int16x8_t, vreinterpretq_s16_u16);
            NATIVE_CAST_IMPL(16, uint16x8_t, uint8x16_t, vreinterpretq_u8_u16);
            NATIVE_CAST_IMPL(16, uint16x8_t, int8x16_t, vreinterpretq_s8_u16);
            NATIVE_CAST_IMPL(16, uint16x8_t, float32x4_t, vreinterpretq_f32_u16);

            NATIVE_CAST_IMPL(16, int16x8_t, uint64x2_t, vreinterpretq_u64_s16);
            NATIVE_CAST_IMPL(16, int16x8_t, int64x2_t, vreinterpretq_s64_s16);
            NATIVE_CAST_IMPL(16, int16x8_t, uint32x4_t, vreinterpretq_u32_s16);
            NATIVE_CAST_IMPL(16, int16x8_t, int32x4_t, vreinterpretq_s32_s16);
            NATIVE_CAST_IMPL(16, int16x8_t, uint16x8_t, vreinterpretq_u16_s16);
            NATIVE_CAST_IMPL(16, int16x8_t, uint8x16_t, vreinterpretq_u8_s16);
            NATIVE_CAST_IMPL(16, int16x8_t, int8x16_t, vreinterpretq_s8_s16);
            NATIVE_CAST_IMPL(16, int16x8_t, float32x4_t, vreinterpretq_f32_s16);

            NATIVE_CAST_IMPL(16, uint8x16_t, uint64x2_t, vreinterpretq_u64_u8);
            NATIVE_CAST_IMPL(16, uint8x16_t, int64x2_t, vreinterpretq_s64_u8);
            NATIVE_CAST_IMPL(16, uint8x16_t, uint32x4_t, vreinterpretq_u32_u8);
            NATIVE_CAST_IMPL(16, uint8x16_t, int32x4_t, vreinterpretq_s32_u8);
            NATIVE_CAST_IMPL(16, uint8x16_t, uint16x8_t, vreinterpretq_u16_u8);
            NATIVE_CAST_IMPL(16, uint8x16_t, int16x8_t, vreinterpretq_s16_u8);
            NATIVE_CAST_IMPL(16, uint8x16_t, int8x16_t, vreinterpretq_s8_u8);
            NATIVE_CAST_IMPL(16, uint8x16_t, float32x4_t, vreinterpretq_f32_u8);

            NATIVE_CAST_IMPL(16, int8x16_t, uint64x2_t, vreinterpretq_u64_s8);
            NATIVE_CAST_IMPL(16, int8x16_t, int64x2_t, vreinterpretq_s64_s8);
            NATIVE_CAST_IMPL(16, int8x16_t, uint32x4_t, vreinterpretq_u32_s8);
            NATIVE_CAST_IMPL(16, int8x16_t, int32x4_t, vreinterpretq_s32_s8);
            NATIVE_CAST_IMPL(16, int8x16_t, uint16x8_t, vreinterpretq_u16_s8);
            NATIVE_CAST_IMPL(16, int8x16_t, int16x8_t, vreinterpretq_s16_s8);
            NATIVE_CAST_IMPL(16, int8x16_t, uint8x16_t, vreinterpretq_u8_s8);
            NATIVE_CAST_IMPL(16, int8x16_t, float32x4_t, vreinterpretq_f32_s8);
#endif

#if SIMD_USE_NEON64
            NATIVE_CAST_IMPL(16, float64x2_t, uint64x2_t, vreinterpretq_u64_f64);
            NATIVE_CAST_IMPL(16, float64x2_t, int64x2_t, vreinterpretq_s64_f64);
            NATIVE_CAST_IMPL(16, float64x2_t, uint32x4_t, vreinterpretq_u32_f64);
            NATIVE_CAST_IMPL(16, float64x2_t, int32x4_t, vreinterpretq_s32_f64);
            NATIVE_CAST_IMPL(16, float64x2_t, uint16x8_t, vreinterpretq_u16_f64);
            NATIVE_CAST_IMPL(16, float64x2_t, int16x8_t, vreinterpretq_s16_f64);
            NATIVE_CAST_IMPL(16, float64x2_t, uint8x16_t, vreinterpretq_u8_f64);
            NATIVE_CAST_IMPL(16, float64x2_t, int8x16_t, vreinterpretq_s8_f64);
            NATIVE_CAST_IMPL(16, float64x2_t, float32x4_t, vreinterpretq_f32_f64);

            NATIVE_CAST_IMPL(16, uint64x2_t, float64x2_t, vreinterpretq_f64_u64);
            NATIVE_CAST_IMPL(16, int64x2_t, float64x2_t, vreinterpretq_f64_s64);
            NATIVE_CAST_IMPL(16, uint32x4_t, float64x2_t, vreinterpretq_f64_u32);
            NATIVE_CAST_IMPL(16, int32x4_t, float64x2_t, vreinterpretq_f64_s32);
            NATIVE_CAST_IMPL(16, uint16x8_t, float64x2_t, vreinterpretq_f64_u16);
            NATIVE_CAST_IMPL(16, int16x8_t, float64x2_t, vreinterpretq_f64_s16);
            NATIVE_CAST_IMPL(16, uint8x16_t, float64x2_t, vreinterpretq_f64_u8);
            NATIVE_CAST_IMPL(16, int8x16_t, float64x2_t, vreinterpretq_f64_s8);
            NATIVE_CAST_IMPL(16, float32x4_t, float64x2_t, vreinterpretq_f64_f32);
#endif
#undef NATIVE_CAST_IMPL

            template <unsigned SizeT, class NativeT, class NativeR> struct native_cast_split;
            template <unsigned SizeR, class NativeT, class NativeR> struct native_cast_combine;

#if SIMD_USE_AVX
            template <> struct native_cast_split<32, __m256, __m128i> {
                static inline void cast(const __m256 &t, __m128i &r0, __m128i &r1) {
                    r0 = _mm_castps_si128(_mm256_castps256_ps128(t));
                    r1 = _mm_castps_si128(_mm256_extractf128_ps(t, 1));
                }
            };

            template <> struct native_cast_split<32, __m256d, __m128i> {
                static inline void cast(const __m256d &t, __m128i &r0, __m128i &r1) {
                    r0 = _mm_castpd_si128(_mm256_castpd256_pd128(t));
                    r1 = _mm_castpd_si128(_mm256_extractf128_pd(t, 1));
                }
            };

            template <> struct native_cast_combine<32, __m128i, __m256> {
                static inline __m256 cast(const __m128i &t0, const __m128i &t1) {
                    __m256 r = _mm256_castsi256_ps(_mm256_castsi128_si256(t0));
                    r = _mm256_insertf128_ps(r, _mm_castsi128_ps(t1), 1);
                    return r;
                }
            };

            template <> struct native_cast_combine<32, __m128i, __m256d> {
                static inline __m256d cast(const __m128i &t0, const __m128i &t1) {
                    __m256d r = _mm256_castsi256_pd(_mm256_castsi128_si256(t0));
                    r = _mm256_insertf128_pd(r, _mm_castsi128_pd(t1), 1);
                    return r;
                }
            };
#endif

#if SIMD_USE_AVX512F
            template <> struct native_cast_split<64, __m512i, __m256i> {
                static inline void cast(const __m512i &t, __m256i &r0, __m256i &r1) {
                    r0 = _mm512_castsi512_si256(t);
                    r1 = _mm512_extracti64x4_epi64(t, 1);
                }
            };

            template <> struct native_cast_split<64, __m512, __m256i> {
                static inline void cast(const __m512 &t, __m256i &r0, __m256i &r1) {
                    r0 = _mm256_castps_si256(_mm512_castps512_ps256(t));
                    r1 = _mm256_castpd_si256(_mm512_extractf64x4_pd(_mm512_castps_pd(t), 1));
                }
            };

            template <> struct native_cast_split<64, __m512d, __m256i> {
                static inline void cast(const __m512d &t, __m256i &r0, __m256i &r1) {
                    r0 = _mm256_castpd_si256(_mm512_castpd512_pd256(t));
                    r1 = _mm256_castpd_si256(_mm512_extractf64x4_pd(t, 1));
                }
            };

            template <> struct native_cast_combine<64, __m256i, __m512i> {
                static inline __m512i cast(const __m256i &t0, const __m256i &t1) {
                    __m512i r = _mm512_castsi256_si512(t0);
                    return _mm512_inserti64x4(r, t1, 1);
                }
            };

            template <> struct native_cast_combine<64, __m256i, __m512> {
                static inline __m512 cast(const __m256i &t0, const __m256i &t1) {
                    __m512d r = _mm512_castsi512_pd(_mm512_castsi256_si512(t0));
                    r = _mm512_insertf64x4(r, _mm256_castsi256_pd(t1), 1);
                    return _mm512_castpd_ps(r);
                }
            };

            template <> struct native_cast_combine<64, __m256i, __m512d> {
                static inline __m512d cast(const __m256i &t0, const __m256i &t1) {
                    __m512d r = _mm512_castsi512_pd(_mm512_castsi256_si512(t0));
                    r = _mm512_insertf64x4(r, _mm256_castsi256_pd(t1), 1);
                    return r;
                }
            };
#endif

            template <unsigned CastType> struct cast_bitwise_vector_impl;

            template <class T> struct is_vararray : std::false_type {};

            template <class T, unsigned N> struct is_vararray<vararray<T, N>> : std::true_type {};

            template <> struct cast_bitwise_vector_impl<VECTOR_CAST_TYPE_1_TO_1> {
                template <class T, class R> static inline void cast(const T &t, R &r) {
                    using NativeT = typename T::base_vector_type::native_type;
                    using NativeR = typename R::base_vector_type::native_type;
                    const bool is_arg_vararray = is_vararray<NativeT>::value || is_vararray<NativeR>::value;
                    using CastImpl = native_cast<sizeof(NativeT), NativeT, NativeR, is_arg_vararray>;

                    for (unsigned i = 0; i < T::vec_length; ++i) {
                        r.vec(i) = CastImpl::cast(t.vec(i).native());
                    }
                }
            };

            template <> struct cast_bitwise_vector_impl<VECTOR_CAST_TYPE_SPLIT2> {
                template <class T, class R> static inline void cast(const T &t, R &r) {
                    using NativeT = typename T::base_vector_type::native_type;
                    using NativeR = typename R::base_vector_type::native_type;
                    using CastImpl = native_cast_split<sizeof(NativeT), NativeT, NativeR>;

                    for (unsigned i = 0; i < T::vec_length; ++i) {
                        NativeR r0, r1;
                        CastImpl::cast(t.vec(i).native(), r0, r1);
                        r.vec(i * 2) = r0;
                        r.vec(i * 2 + 1) = r1;
                    }
                }
            };

            template <> struct cast_bitwise_vector_impl<VECTOR_CAST_TYPE_COMBINE2> {
                template <class T, class R> static inline void cast(const T &t, R &r) {
                    using NativeT = typename T::base_vector_type::native_type;
                    using NativeR = typename R::base_vector_type::native_type;
                    using CastImpl = native_cast_combine<sizeof(NativeR), NativeT, NativeR>;

                    for (unsigned i = 0; i < R::vec_length; ++i) {
                        r.vec(i) = CastImpl::cast(t.vec(i * 2).native(), t.vec(i * 2 + 1).native());
                    }
                }
            };

            template <class T, class R> inline void cast_bitwise_vector(const T &t, R &r) {
                static_assert(sizeof(R) == sizeof(T), "Size mismatch");
                const unsigned vector_cast_type =
                    T::vec_length == R::vec_length ?
                        VECTOR_CAST_TYPE_1_TO_1 :
                        T::vec_length == R::vec_length * 2 ?
                        VECTOR_CAST_TYPE_COMBINE2 :
                        T::vec_length * 2 == R::vec_length ? VECTOR_CAST_TYPE_SPLIT2 : VECTOR_CAST_TYPE_INVALID;

                cast_bitwise_vector_impl<vector_cast_type>::cast(t, r);
            }

#if (__GNUC__ >= 6) && !defined(__INTEL_COMPILER) && !defined(__clang__)
#pragma GCC diagnostic pop
#endif

        } // namespace detail
    }     // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
