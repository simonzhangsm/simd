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

#ifndef SIMD_DETAIL_ALIGN_V128_H
#define SIMD_DETAIL_ALIGN_V128_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/core/align.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {

            template <unsigned shift, unsigned N> inline uint8<N> align_v128(const uint8<N> &a, const uint8<N> &b) {
                return align16<shift>(a, b);
            }
            template <unsigned shift, unsigned N> inline uint16<N> align_v128(const uint16<N> &a, const uint16<N> &b) {
                return align8<shift>(a, b);
            }
            template <unsigned shift, unsigned N> inline uint32<N> align_v128(const uint32<N> &a, const uint32<N> &b) {
                return align4<shift>(a, b);
            }
            template <unsigned shift, unsigned N> inline uint64<N> align_v128(const uint64<N> &a, const uint64<N> &b) {
                return align2<shift>(a, b);
            }

            template <unsigned shift, unsigned N> inline int8<N> align_v128(const int8<N> &a, const int8<N> &b) {
                return align16<shift>(a, b);
            }
            template <unsigned shift, unsigned N> inline int16<N> align_v128(const int16<N> &a, const int16<N> &b) {
                return align8<shift>(a, b);
            }
            template <unsigned shift, unsigned N> inline int32<N> align_v128(const int32<N> &a, const int32<N> &b) {
                return align4<shift>(a, b);
            }
            template <unsigned shift, unsigned N> inline int64<N> align_v128(const int64<N> &a, const int64<N> &b) {
                return align2<shift>(a, b);
            }

            template <unsigned shift, unsigned N>
            inline float32<N> align_v128(const float32<N> &a, const float32<N> &b) {
                return align4<shift>(a, b);
            }
            template <unsigned shift, unsigned N>
            inline float64<N> align_v128(const float64<N> &a, const float64<N> &b) {
                return align2<shift>(a, b);
            }

        } // namespace detail
    }     // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
