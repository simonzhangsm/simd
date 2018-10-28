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

#ifndef SIMD_TEST_COMMON_SEL_VECTORS_H
#define SIMD_TEST_COMMON_SEL_VECTORS_H

#include <bigmath/simd/simd.h>
#include "masks.h"

namespace SIMD_ARCH_NAMESPACE {

    template <class V> V make_sel_vector(unsigned i) {
        return (V)(typename V::uint_vector_type)simd::make_uint((i / 2) % 2 ? -1 : 0, i % 2 ? -1 : 0);
    }


    /** A class that contains some dummy vectors with test data which is set so
        that each element has all bits either set or not set

        BE - bytes per vector element
        N - number of vectors
    */
    template <unsigned BE, unsigned N> struct SelVectors {
        simd::int8<BE> *volatile i8;
        simd::int16<BE / 2> *volatile i16;
        simd::int32<BE / 4> *volatile i32;
        simd::int64<BE / 8> *volatile i64;
        simd::uint8<BE> *volatile u8;
        simd::uint16<BE / 2> *volatile u16;
        simd::uint32<BE / 4> *volatile u32;
        simd::uint64<BE / 8> *volatile u64;
        simd::float32<BE / 4> *volatile f32;
        simd::float64<BE / 8> *volatile f64;

        SelVectors() {
            reset();
        }

        void reset() {
            using namespace simd;

            for (unsigned i = 0; i < N; ++i) {
                du8[i] = make_sel_vector<uint8<BE>>(i);
                du16[i] = make_sel_vector<uint16<BE / 2>>(i);
                du32[i] = make_sel_vector<uint32<BE / 4>>(i);
                du64[i] = make_sel_vector<uint64<BE / 8>>(i);
                di8[i] = make_sel_vector<uint8<BE>>(i);
                di16[i] = make_sel_vector<uint16<BE / 2>>(i);
                di32[i] = make_sel_vector<uint32<BE / 4>>(i);
                di64[i] = make_sel_vector<uint64<BE / 8>>(i);
                df32[i] = make_sel_vector<float32<BE / 4>>(i);
                df64[i] = make_sel_vector<float64<BE / 8>>(i);
            }
            u8 = du8;
            u16 = du16;
            u32 = du32;
            u64 = du64;
            i8 = di8;
            i16 = di16;
            i32 = di32;
            i64 = di64;
            f32 = df32;
            f64 = df64;
        }

    private:
        simd::int8<BE> di8[N];
        simd::int16<BE / 2> di16[N];
        simd::int32<BE / 4> di32[N];
        simd::int64<BE / 8> di64[N];
        simd::uint8<BE> du8[N];
        simd::uint16<BE / 2> du16[N];
        simd::uint32<BE / 4> du32[N];
        simd::uint64<BE / 8> du64[N];
        simd::float32<BE / 4> df32[N];
        simd::float64<BE / 8> df64[N];
    };

} // namespace SIMD_ARCH_NAMESPACE

#endif
