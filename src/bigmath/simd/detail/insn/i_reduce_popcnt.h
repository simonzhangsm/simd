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

#ifndef SIMD_DETAIL_INSN_I_REDUCE_POPCNT_H
#define SIMD_DETAIL_INSN_I_REDUCE_POPCNT_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/null/bitwise.h>
#include <bigmath/simd/core/i_popcnt.h>
#include <bigmath/simd/core/i_reduce_add.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {

                static inline uint32_t i_reduce_popcnt(const uint32<4> &a) {
#if SIMD_USE_NULL
                    uint32_t r = 0;
                    for (unsigned i = 0; i < a.length; i++) {
                        r += detail::null::el_popcnt32(a.el(i));
                    }
                    return r;
#elif SIMD_USE_X86_POPCNT_INSN
                    uint32_t r = 0;
#if SIMD_64_BITS
                    uint64<2> a64;
                    a64 = a;
                    r += _mm_popcnt_u64(extract<0>(a64));
                    r += _mm_popcnt_u64(extract<1>(a64));
#else
                    r += _mm_popcnt_u32(extract<0>(a));
                    r += _mm_popcnt_u32(extract<1>(a));
                    r += _mm_popcnt_u32(extract<2>(a));
                    r += _mm_popcnt_u32(extract<3>(a));
#endif
                    return r;
#elif SIMD_USE_NEON
                    uint8<16> r = vcntq_u8(vreinterpretq_u8_u32(a.native()));
                    return reduce_add(r);
#elif SIMD_USE_VSX_207 || SIMD_USE_MSA
                    uint64<2> a64;
                    a64 = a;
                    a64 = popcnt(a64);
                    return reduce_add(a64);
#elif SIMD_USE_SSE2
                    uint64<2> r = popcnt((uint64<2>)a);
                    return (uint32_t)reduce_add(r);
#else
                    uint32<4> r = popcnt(a);
                    return reduce_add(r);
#endif
                }

#if SIMD_USE_AVX2
                static inline uint32_t i_reduce_popcnt(const uint32<8> &a) {
#if SIMD_USE_X86_POPCNT_INSN && SIMD_64_BITS
                    uint32<4> a0, a1;
                    split(a, a0, a1);
                    return i_reduce_popcnt(a0) + i_reduce_popcnt(a1);
#else
                    uint64<4> r = popcnt((uint64<4>)a);
                    return (uint32_t)reduce_add(r);
#endif
                }
#endif

#if SIMD_USE_AVX512F
                static inline uint32_t i_reduce_popcnt(const uint32<16> &a) {
#if SIMD_USE_X86_POPCNT_INSN && SIMD_64_BITS
                    uint32<8> a0, a1;
                    split(a, a0, a1);
                    return i_reduce_popcnt(a0) + i_reduce_popcnt(a1);
#else
                    // TODO: support AVX512VPOPCNTDQ
                    uint64<8> r = popcnt((uint64<8>)a);
                    return reduce_add(r);
#endif
                }
#endif

                template <unsigned N> inline uint32_t i_reduce_popcnt(const uint32<N> &a) {
                    uint32_t r = 0;
                    for (unsigned j = 0; j < a.vec_length; ++j) {
                        r += i_reduce_popcnt(a.vec(j));
                    }
                    return r;
                }

                // -----------------------------------------------------------------------------

            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
