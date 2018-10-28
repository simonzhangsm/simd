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

#ifndef SIMD_DETAIL_INSN_STORE_PACKED2_H
#define SIMD_DETAIL_INSN_STORE_PACKED2_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/align.h>
#include <bigmath/simd/detail/insn/mem_pack.h>
#include <bigmath/simd/core/store.h>
#include <bigmath/simd/detail/null/memory.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {

                // collect some boilerplate
                template <class V> inline void v128_store_pack2(char *p, const V &ca, const V &cb);
                template <class V> inline void v256_store_pack2(char *p, const V &ca, const V &cb);
                template <class V> inline void v512_store_pack2(char *p, const V &ca, const V &cb);

                // -----------------------------------------------------------------------------

                static inline void i_store_packed2(char *p, const uint8x16 &a, const uint8x16 &b) {
                    p = detail::assume_aligned(p, 16);
#if SIMD_USE_NULL
                    detail::null::store_packed2(p, a, b);
#elif SIMD_USE_SSE2 || SIMD_USE_ALTIVEC || SIMD_USE_MSA
                    v128_store_pack2(p, a, b);
#elif SIMD_USE_NEON
                    uint8x16x2_t t;
                    t.val[0] = a.native();
                    t.val[1] = b.native();
                    vst2q_u8(reinterpret_cast<uint8_t *>(p), t);
#endif
                }

#if SIMD_USE_AVX2
                static inline void i_store_packed2(char *p, const uint8x32 &a, const uint8x32 &b) {
                    v256_store_pack2(p, a, b);
                }
#endif

#if SIMD_USE_AVX512BW
                inline void i_store_packed2(char *p, const uint8<64> &a, const uint8<64> &b) {
                    v512_store_pack2(p, a, b);
                }
#endif

                // -----------------------------------------------------------------------------

                static inline void i_store_packed2(char *p, const uint16x8 &a, const uint16x8 &b) {
                    p = detail::assume_aligned(p, 16);
#if SIMD_USE_NULL
                    detail::null::store_packed2(p, a, b);
#elif SIMD_USE_SSE2 || SIMD_USE_ALTIVEC || SIMD_USE_MSA
                    v128_store_pack2(p, a, b);
#elif SIMD_USE_NEON
                    uint16x8x2_t t;
                    t.val[0] = a.native();
                    t.val[1] = b.native();
                    vst2q_u16(reinterpret_cast<uint16_t *>(p), t);
#endif
                }

#if SIMD_USE_AVX2
                static inline void i_store_packed2(char *p, const uint16x16 &a, const uint16x16 &b) {
                    v256_store_pack2(p, a, b);
                }
#endif

#if SIMD_USE_AVX512BW
                inline void i_store_packed2(char *p, const uint16<32> &a, const uint16<32> &b) {
                    v512_store_pack2(p, a, b);
                }
#endif

                // -----------------------------------------------------------------------------

                static inline void i_store_packed2(char *p, const uint32x4 &a, const uint32x4 &b) {
                    p = detail::assume_aligned(p, 16);
#if SIMD_USE_NULL
                    detail::null::store_packed2(p, a, b);
#elif SIMD_USE_SSE2 || SIMD_USE_ALTIVEC || SIMD_USE_MSA
                    v128_store_pack2(p, a, b);
#elif SIMD_USE_NEON
                    uint32x4x2_t t;
                    t.val[0] = a.native();
                    t.val[1] = b.native();
                    vst2q_u32(reinterpret_cast<uint32_t *>(p), t);
#endif
                }

#if SIMD_USE_AVX2
                static inline void i_store_packed2(char *p, const uint32x8 &a, const uint32x8 &b) {
                    v256_store_pack2(p, a, b);
                }
#endif

#if SIMD_USE_AVX512F
                static inline void i_store_packed2(char *p, const uint32<16> &a, const uint32<16> &b) {
                    v512_store_pack2(p, a, b);
                }
#endif

                // -----------------------------------------------------------------------------

                static inline void i_store_packed2(char *p, const uint64x2 &a, const uint64x2 &b) {
#if SIMD_USE_NEON64
                    uint64x2x2_t t;
                    t.val[0] = a.native();
                    t.val[1] = b.native();
                    vst2q_u64(reinterpret_cast<uint64_t *>(p), t);
#elif SIMD_USE_SSE2 || SIMD_USE_NEON || SIMD_USE_VSX_207 || SIMD_USE_MSA
                    v128_store_pack2(p, a, b);
#elif SIMD_USE_NULL || SIMD_USE_ALTIVEC
                    detail::null::store_packed2(p, a, b);
#endif
                }

#if SIMD_USE_AVX2
                static inline void i_store_packed2(char *p, const uint64x4 &a, const uint64x4 &b) {
                    v256_store_pack2(p, a, b);
                }
#endif

#if SIMD_USE_AVX512F
                static inline void i_store_packed2(char *p, const uint64<8> &a, const uint64<8> &b) {
                    v512_store_pack2(p, a, b);
                }
#endif

                // -----------------------------------------------------------------------------

                static inline void i_store_packed2(char *p, const float32x4 &a, const float32x4 &b) {
                    p = detail::assume_aligned(p, 16);
#if SIMD_USE_NULL || SIMD_USE_NEON_NO_FLT_SP
                    detail::null::store_packed2(p, a, b);
#elif SIMD_USE_SSE2 || SIMD_USE_ALTIVEC || SIMD_USE_MSA
                    v128_store_pack2(p, a, b);
#elif SIMD_USE_NEON
                    float32x4x2_t t;
                    t.val[0] = a.native();
                    t.val[1] = b.native();
                    vst2q_f32(reinterpret_cast<float *>(p), t);
#endif
                }

#if SIMD_USE_AVX
                static inline void i_store_packed2(char *p, const float32x8 &a, const float32x8 &b) {
                    v256_store_pack2(p, a, b);
                }
#endif

#if SIMD_USE_AVX512F
                static inline void i_store_packed2(char *p, const float32<16> &a, const float32<16> &b) {
                    v512_store_pack2(p, a, b);
                }
#endif

                // -----------------------------------------------------------------------------

                static inline void i_store_packed2(char *p, const float64x2 &a, const float64x2 &b) {
#if SIMD_USE_NEON64
                    float64x2x2_t t;
                    t.val[0] = a.native();
                    t.val[1] = b.native();
                    vst2q_f64(reinterpret_cast<double *>(p), t);
#elif SIMD_USE_SSE2 || SIMD_USE_VSX_206 || SIMD_USE_MSA
                    v128_store_pack2(p, a, b);
#elif SIMD_USE_NULL || SIMD_USE_NEON || SIMD_USE_ALTIVEC
                    detail::null::store_packed2(p, a, b);
#endif
                }

#if SIMD_USE_AVX
                static inline void i_store_packed2(char *p, const float64x4 &a, const float64x4 &b) {
                    v256_store_pack2(p, a, b);
                }
#endif

#if SIMD_USE_AVX512F
                static inline void i_store_packed2(char *p, const float64<8> &a, const float64<8> &b) {
                    v512_store_pack2(p, a, b);
                }
#endif

                // -----------------------------------------------------------------------------

                template <class V> inline void v128_store_pack2(char *p, const V &ca, const V &cb) {
                    p = detail::assume_aligned(p, 32);
                    V a = ca, b = cb;
                    mem_pack2(a, b);
                    i_store(p, a);
                    i_store(p + 16, b);
                }

                template <class V> inline void v256_store_pack2(char *p, const V &ca, const V &cb) {
                    p = detail::assume_aligned(p, 32);
                    V a = ca, b = cb;
                    mem_pack2(a, b);
                    i_store(p, a);
                    i_store(p + 32, b);
                }

                template <class V> inline void v512_store_pack2(char *p, const V &ca, const V &cb) {
                    p = detail::assume_aligned(p, 32);
                    V a = ca, b = cb;
                    mem_pack2(a, b);
                    i_store(p, a);
                    i_store(p + 64, b);
                }


                template <class V> inline void i_store_packed2(char *p, const V &ca, const V &cb) {
                    const unsigned veclen = V::base_vector_type::length_bytes;
                    typename detail::remove_sign<V>::type a = ca, b = cb;

                    p = detail::assume_aligned(p, veclen);
                    for (unsigned i = 0; i < V::vec_length; ++i) {
                        i_store_packed2(p, a.vec(i), b.vec(i));
                        p += veclen * 2;
                    }
                }

            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
