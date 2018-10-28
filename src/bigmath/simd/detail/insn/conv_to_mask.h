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

#ifndef SIMD_DETAIL_INSN_CONV_TO_MASK_H
#define SIMD_DETAIL_INSN_CONV_TO_MASK_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {

                static inline mask_int8<16> i_to_mask(const uint8<16> &a);

#if SIMD_USE_AVX2
                static inline mask_int8<32> i_to_mask(const uint8<32> &a);
#endif

#if SIMD_USE_AVX512BW
                static inline mask_int8<64> i_to_mask(const uint8<64> &a);
#endif

                // -----------------------------------------------------------------------------

                static inline mask_int16<8> i_to_mask(const uint16<8> &a);

#if SIMD_USE_AVX2
                static inline mask_int16<16> i_to_mask(const uint16<16> &a);
#endif

#if SIMD_USE_AVX512BW
                static inline mask_int16<32> i_to_mask(const uint16<32> &a);
#endif

                // -----------------------------------------------------------------------------

                static inline mask_int32<4> i_to_mask(const uint32<4> &a);

#if SIMD_USE_AVX2
                static inline mask_int32<8> i_to_mask(const uint32<8> &a);
#endif

#if SIMD_USE_AVX512F
                static inline mask_int32<16> i_to_mask(const uint32<16> &a);
#endif

                // -----------------------------------------------------------------------------

                static inline mask_int64<2> i_to_mask(const uint64<2> &a);

#if SIMD_USE_AVX2
                static inline mask_int64<4> i_to_mask(const uint64<4> &a);
#endif

#if SIMD_USE_AVX512F
                static inline mask_int64<8> i_to_mask(const uint64<8> &a);
#endif

                // -----------------------------------------------------------------------------

                static inline mask_float32<4> i_to_mask(const float32<4> &a);

#if SIMD_USE_AVX2
                static inline mask_float32<8> i_to_mask(const float32<8> &a);
#endif

#if SIMD_USE_AVX512F
                static inline mask_float32<16> i_to_mask(const float32<16> &a);
#endif

                // -----------------------------------------------------------------------------

                static inline mask_float64<2> i_to_mask(const float64<2> &a);

#if SIMD_USE_AVX2
                static inline mask_float64<4> i_to_mask(const float64<4> &a);
#endif

#if SIMD_USE_AVX512F
                static inline mask_float64<8> i_to_mask(const float64<8> &a);
#endif

                // -----------------------------------------------------------------------------

                template <class V> inline typename V::mask_vector_type i_to_mask(const V &a);

            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
