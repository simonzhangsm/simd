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

#ifndef SIMD_DETAIL_INSN_F_NEG_H
#define SIMD_DETAIL_INSN_F_NEG_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/core/bit_xor.h>
#include <bigmath/simd/detail/null/math.h>
#include <bigmath/simd/detail/vector_array_macros.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {

                static inline float32<4> i_fneg(const float32<4> &a) {
#if SIMD_USE_NULL || SIMD_USE_NEON_NO_FLT_SP
                    return detail::null::neg(a);
#elif SIMD_USE_SSE2 || SIMD_USE_ALTIVEC || SIMD_USE_MSA
                    // reversion of the sign bit required even for NaNs and zeros
                    return bit_xor(a, 0x80000000);
#elif SIMD_USE_NEON_FLT_SP
                    return vnegq_f32(a.native());
#endif
                }

#if SIMD_USE_AVX
                static inline float32<8> i_fneg(const float32<8> &a) {
                    return bit_xor(a, 0x80000000);
                }
#endif

#if SIMD_USE_AVX512F
                static inline float32<16> i_fneg(const float32<16> &a) {
                    // FIXME: check whether we can simply use sub
                    return bit_xor(a, 0x80000000);
                }
#endif

                // -----------------------------------------------------------------------------

                static inline float64x2 i_fneg(const float64<2> &a) {
#if SIMD_USE_SSE2 || SIMD_USE_VSX_206 || SIMD_USE_MSA
                    return bit_xor(a, 0x8000000000000000);
#elif SIMD_USE_NEON64
                    return vnegq_f64(a.native());
#elif SIMD_USE_NULL || SIMD_USE_NEON32 || SIMD_USE_ALTIVEC
                    return detail::null::neg(a);
#endif
                }

#if SIMD_USE_AVX
                static inline float64x4 i_fneg(const float64<4> &a) {
                    return bit_xor(a, 0x8000000000000000);
                }
#endif

#if SIMD_USE_AVX512F
                static inline float64<8> i_fneg(const float64<8> &a) {
                    // FIXME: check whether we can simply use sub
                    return bit_xor(a, 0x8000000000000000);
                }
#endif

                // -----------------------------------------------------------------------------

                template <class V> inline V i_fneg(const V &a) {
                    SIMD_VEC_ARRAY_IMPL1(V, i_fneg, a)
                }

            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
