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

#ifndef SIMD_DETAIL_INSN_ZIP128_H
#define SIMD_DETAIL_INSN_ZIP128_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/insn/zip_hi.h>
#include <bigmath/simd/detail/insn/zip_lo.h>
#include <bigmath/simd/detail/insn/unzip_hi.h>
#include <bigmath/simd/detail/insn/unzip_lo.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace insn {

                template <unsigned N> inline uint8<N> unzip128_lo(const uint8<N> &a, const uint8<N> &b) {
                    return unzip16_lo(a, b);
                }
                template <unsigned N> inline uint16<N> unzip128_lo(const uint16<N> &a, const uint16<N> &b) {
                    return unzip8_lo(a, b);
                }
                template <unsigned N> inline uint32<N> unzip128_lo(const uint32<N> &a, const uint32<N> &b) {
                    return unzip4_lo(a, b);
                }
                template <unsigned N> inline uint64<N> unzip128_lo(const uint64<N> &a, const uint64<N> &b) {
                    return unzip2_lo(a, b);
                }
                template <unsigned N> inline float32<N> unzip128_lo(const float32<N> &a, const float32<N> &b) {
                    return unzip4_lo(a, b);
                }
                template <unsigned N> inline float64<N> unzip128_lo(const float64<N> &a, const float64<N> &b) {
                    return unzip2_lo(a, b);
                }

                template <unsigned N> inline uint8<N> unzip128_hi(const uint8<N> &a, const uint8<N> &b) {
                    return unzip16_hi(a, b);
                }
                template <unsigned N> inline uint16<N> unzip128_hi(const uint16<N> &a, const uint16<N> &b) {
                    return unzip8_hi(a, b);
                }
                template <unsigned N> inline uint32<N> unzip128_hi(const uint32<N> &a, const uint32<N> &b) {
                    return unzip4_hi(a, b);
                }
                template <unsigned N> inline uint64<N> unzip128_hi(const uint64<N> &a, const uint64<N> &b) {
                    return unzip2_hi(a, b);
                }
                template <unsigned N> inline float32<N> unzip128_hi(const float32<N> &a, const float32<N> &b) {
                    return unzip4_hi(a, b);
                }
                template <unsigned N> inline float64<N> unzip128_hi(const float64<N> &a, const float64<N> &b) {
                    return unzip2_hi(a, b);
                }

                template <unsigned N> inline uint8<N> zip128_lo(const uint8<N> &a, const uint8<N> &b) {
                    return zip16_lo(a, b);
                }
                template <unsigned N> inline uint16<N> zip128_lo(const uint16<N> &a, const uint16<N> &b) {
                    return zip8_lo(a, b);
                }
                template <unsigned N> inline uint32<N> zip128_lo(const uint32<N> &a, const uint32<N> &b) {
                    return zip4_lo(a, b);
                }
                template <unsigned N> inline uint64<N> zip128_lo(const uint64<N> &a, const uint64<N> &b) {
                    return zip2_lo(a, b);
                }
                template <unsigned N> inline float32<N> zip128_lo(const float32<N> &a, const float32<N> &b) {
                    return zip4_lo(a, b);
                }
                template <unsigned N> inline float64<N> zip128_lo(const float64<N> &a, const float64<N> &b) {
                    return zip2_lo(a, b);
                }

                template <unsigned N> inline uint8<N> zip128_hi(const uint8<N> &a, const uint8<N> &b) {
                    return zip16_hi(a, b);
                }
                template <unsigned N> inline uint16<N> zip128_hi(const uint16<N> &a, const uint16<N> &b) {
                    return zip8_hi(a, b);
                }
                template <unsigned N> inline uint32<N> zip128_hi(const uint32<N> &a, const uint32<N> &b) {
                    return zip4_hi(a, b);
                }
                template <unsigned N> inline uint64<N> zip128_hi(const uint64<N> &a, const uint64<N> &b) {
                    return zip2_hi(a, b);
                }
                template <unsigned N> inline float32<N> zip128_hi(const float32<N> &a, const float32<N> &b) {
                    return zip4_hi(a, b);
                }
                template <unsigned N> inline float64<N> zip128_hi(const float64<N> &a, const float64<N> &b) {
                    return zip2_hi(a, b);
                }

            } // namespace insn
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
