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

#include "../utils/test_helpers.h"
#include "../utils/test_results.h"
#include "../common/masks.h"
#include "../common/vectors.h"
#include "../common/sel_vectors.h"
#include <bigmath/simd/simd.h>

namespace SIMD_ARCH_NAMESPACE {

template<unsigned B>
void test_test_utils_n(TestResultsSet& tc)
{
    using namespace simd;

    using uint8_n = uint8<B>;
    using uint16_n = uint16<B/2>;
    using uint32_n = uint32<B/4>;
    using uint64_n = uint64<B/8>;
    using float32_n = float32<B/4>;
    using float64_n = float64<B/8>;

    // masks
    Vectors<B,4> v;
    SelVectors<B,4> s;
    Masks<B,4> m;

    for (unsigned i = 0; i < 4; i++) {
        TEST_PUSH(tc, uint8_n,   v.u8[i]);
        TEST_PUSH(tc, uint16_n,  v.u16[i]);
        TEST_PUSH(tc, uint32_n,  v.u32[i]);
        TEST_PUSH(tc, uint64_n,  v.u64[i]);
        TEST_PUSH(tc, float32_n, v.f32[i]);
        TEST_PUSH(tc, float64_n, v.f64[i]);
        TEST_PUSH(tc, uint8_n,   m.u8[i]);
        TEST_PUSH(tc, uint16_n,  m.u16[i]);
        TEST_PUSH(tc, uint32_n,  m.u32[i]);
        TEST_PUSH(tc, uint64_n,  m.u64[i]);
        TEST_PUSH(tc, float32_n, m.f32[i]);
        TEST_PUSH(tc, float64_n, m.f64[i]);
        TEST_PUSH(tc, uint8_n,   s.u8[i]);
        TEST_PUSH(tc, uint16_n,  s.u16[i]);
        TEST_PUSH(tc, uint32_n,  s.u32[i]);
        TEST_PUSH(tc, uint64_n,  s.u64[i]);
        TEST_PUSH(tc, float32_n, s.f32[i]);
        TEST_PUSH(tc, float64_n, s.f64[i]);
    }
}

void test_test_utils(TestResults& res)
{
    TestResultsSet& tc = res.new_results_set("test_utils");
    test_test_utils_n<16>(tc);
    test_test_utils_n<32>(tc);
    test_test_utils_n<64>(tc);
}


} // namespace SIMD_ARCH_NAMESPACE
