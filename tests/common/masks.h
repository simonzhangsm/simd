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

#ifndef SIMD_TEST_COMMON_MASKS_H
#define SIMD_TEST_COMMON_MASKS_H

#include <bigmath/simd/simd.h>
#include "vectors.h"

namespace SIMD_ARCH_NAMESPACE {

    template <class M, class V> inline M make_mask(unsigned i) {
        V v1 = simd::make_uint((i / 2) % 2, i % 2);
        V v2 = simd::make_zero();
        return cmp_eq(v1, v2);
    }

    /** A class that contains some dummy mask vectors with test data.

        BE - bytes per vector element
        N - number of vectors
    */
    template <unsigned BE, unsigned N> struct Masks {
        simd::mask_int8<BE> *volatile u8;
        simd::mask_int16<BE / 2> *volatile u16;
        simd::mask_int32<BE / 4> *volatile u32;
        simd::mask_int64<BE / 8> *volatile u64;
        simd::mask_float32<BE / 4> *volatile f32;
        simd::mask_float64<BE / 8> *volatile f64;

        Masks() {
            reset();
        }

        void reset() {
            using namespace simd;

            for (unsigned i = 0; i < N; ++i) {
                du8[i] = make_mask<mask_int8<BE>, uint8<BE>>(i);
                du16[i] = make_mask<mask_int16<BE / 2>, uint16<BE / 2>>(i);
                du32[i] = make_mask<mask_int32<BE / 4>, uint32<BE / 4>>(i);
                du64[i] = make_mask<mask_int64<BE / 8>, uint64<BE / 8>>(i);
                df32[i] = make_mask<mask_float32<BE / 4>, float32<BE / 4>>(i);
                df64[i] = make_mask<mask_float64<BE / 8>, float64<BE / 8>>(i);
            }
            u8 = du8;
            u16 = du16;
            u32 = du32;
            u64 = du64;
            f32 = df32;
            f64 = df64;
        }

    private:
        simd::mask_int8<BE> du8[N];
        simd::mask_int16<BE / 2> du16[N];
        simd::mask_int32<BE / 4> du32[N];
        simd::mask_int64<BE / 8> du64[N];
        simd::mask_float32<BE / 4> df32[N];
        simd::mask_float64<BE / 8> df64[N];
    };

} // namespace SIMD_ARCH_NAMESPACE

#endif
