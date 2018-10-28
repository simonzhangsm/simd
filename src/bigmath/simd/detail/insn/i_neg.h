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

#ifndef SIMD_DETAIL_INSN_I_NEG_H
#define SIMD_DETAIL_INSN_I_NEG_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/core/i_sub.h>
#include <bigmath/simd/detail/null/math.h>
#include <bigmath/simd/detail/vector_array_macros.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {

                static inline int8<16> i_ineg(const int8<16> &a) {
#if SIMD_USE_NULL
                    return detail::null::neg(a);
#elif SIMD_USE_SSE2 || SIMD_USE_ALTIVEC || SIMD_USE_MSA
                    return sub(0, a);
#elif SIMD_USE_NEON
                    return vnegq_s8(a.native());
#endif
                }

#if SIMD_USE_AVX2
                static inline int8<32> i_ineg(const int8<32> &a) {
                    return sub(0, a);
                }
#endif

#if SIMD_USE_AVX512BW
                static inline int8<64> i_ineg(const int8<64> &a) {
                    return sub(0, a);
                }
#endif

                // -----------------------------------------------------------------------------

                static inline int16<8> i_ineg(const int16<8> &a) {
#if SIMD_USE_NULL
                    return detail::null::neg(a);
#elif SIMD_USE_SSE2 || SIMD_USE_ALTIVEC || SIMD_USE_MSA
                    return sub(0, a);
#elif SIMD_USE_NEON
                    return vnegq_s16(a.native());
#endif
                }

#if SIMD_USE_AVX2
                static inline int16<16> i_ineg(const int16<16> &a) {
                    return sub(0, a);
                }
#endif

#if SIMD_USE_AVX512BW
                static inline int16<32> i_ineg(const int16<32> &a) {
                    return sub(0, a);
                }
#endif

                // -----------------------------------------------------------------------------

                static inline int32<4> i_ineg(const int32<4> &a) {
#if SIMD_USE_NULL
                    return detail::null::neg(a);
#elif SIMD_USE_SSE2 || SIMD_USE_ALTIVEC || SIMD_USE_MSA
                    return sub(0, a);
#elif SIMD_USE_NEON
                    return vnegq_s32(a.native());
#endif
                }

#if SIMD_USE_AVX2
                static inline int32<8> i_ineg(const int32<8> &a) {
                    return sub(0, a);
                }
#endif

#if SIMD_USE_AVX512F
                static inline int32<16> i_ineg(const int32<16> &a) {
                    return sub(0, a);
                }
#endif

                // -----------------------------------------------------------------------------

                static inline int64<2> i_ineg(const int64<2> &a) {
#if SIMD_USE_SSE2 || SIMD_USE_NEON || SIMD_USE_VSX_207 || SIMD_USE_MSA
                    return sub(0, a);
#elif SIMD_USE_NULL || SIMD_USE_ALTIVEC
                    return detail::null::neg(a);
#endif
                }

#if SIMD_USE_AVX2
                static inline uint64<4> i_ineg(const int64<4> &a) {
                    return sub(0, a);
                }
#endif

#if SIMD_USE_AVX512F
                static inline uint64<8> i_ineg(const int64<8> &a) {
                    return sub(0, a);
                }
#endif

                // -----------------------------------------------------------------------------

                template <class V> inline V i_ineg(const V &a) {
                    SIMD_VEC_ARRAY_IMPL1(V, i_ineg, a)
                }

            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
