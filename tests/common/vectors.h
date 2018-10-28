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

#ifndef SIMD_TEST_COMMON_VECTORS_H
#define SIMD_TEST_COMMON_VECTORS_H

#include <bigmath/simd/simd.h>

namespace SIMD_ARCH_NAMESPACE {

    /** A class that contains some dummy vectors with test data.

        BE - bytes per vector element
        N - number of vectors
    */
    template <unsigned BE, unsigned N> struct Vectors {

        uint8_t *volatile pu8;
        uint16_t *volatile pu16;
        uint32_t *volatile pu32;
        uint64_t *volatile pu64;
        int8_t *volatile pi8;
        int16_t *volatile pi16;
        int32_t *volatile pi32;
        int64_t *volatile pi64;
        float *volatile pf32;
        double *volatile pf64;

        simd::uint8<BE> *volatile u8;
        simd::uint16<BE / 2> *volatile u16;
        simd::uint32<BE / 4> *volatile u32;
        simd::uint64<BE / 8> *volatile u64;
        simd::int8<BE> *volatile i8;
        simd::int16<BE / 2> *volatile i16;
        simd::int32<BE / 4> *volatile i32;
        simd::int64<BE / 8> *volatile i64;
        simd::float32<BE / 4> *volatile f32;
        simd::float64<BE / 8> *volatile f64;

        Vectors() {
            reset();
        }

        void reset() {
            for (unsigned i = 0; i < BE * N; i++) {
                c[i] = i % 256;
            }
            broadcast();
        }

        void broadcast() {
            pu8 = reinterpret_cast<uint8_t *>(c);
            pu16 = reinterpret_cast<uint16_t *>(c);
            pu32 = reinterpret_cast<uint32_t *>(c);
            pu64 = reinterpret_cast<uint64_t *>(c);
            pi8 = reinterpret_cast<int8_t *>(c);
            pi16 = reinterpret_cast<int16_t *>(c);
            pi32 = reinterpret_cast<int32_t *>(c);
            pi64 = reinterpret_cast<int64_t *>(c);
            pf32 = reinterpret_cast<float *>(c);
            pf64 = reinterpret_cast<double *>(c);

            u8 = reinterpret_cast<simd::uint8<BE> *>(c);
            u16 = reinterpret_cast<simd::uint16<BE / 2> *>(c);
            u32 = reinterpret_cast<simd::uint32<BE / 4> *>(c);
            u64 = reinterpret_cast<simd::uint64<BE / 8> *>(c);
            i8 = reinterpret_cast<simd::int8<BE> *>(c);
            i16 = reinterpret_cast<simd::int16<BE / 2> *>(c);
            i32 = reinterpret_cast<simd::int32<BE / 4> *>(c);
            i64 = reinterpret_cast<simd::int64<BE / 8> *>(c);
            f32 = reinterpret_cast<simd::float32<BE / 4> *>(c);
            f64 = reinterpret_cast<simd::float64<BE / 8> *>(c);
        }

        void zero() {
            for (unsigned i = 0; i < BE * N; i++) {
                c[i] = 0;
            }
            broadcast();
        }

    private:
        SIMDALIGN(64) uint8_t c[BE * N];
    };

} // namespace SIMD_ARCH_NAMESPACE

#endif
