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
#include "../common/vectors.h"
#include <bigmath/simd/simd.h>

namespace SIMD_ARCH_NAMESPACE {

template<class V, unsigned i>
struct Test_permute2 {
    static const unsigned limit = 4;
    static void test(TestResultsSet& tc, const V& a)
    {
        const unsigned s0 = i / 2 % 2;
        const unsigned s1 = i % 2;

        V r = simd::permute2<s0,s1>(a);
        TEST_PUSH(tc, V, r);
    }
};

template<class V, unsigned i>
struct Test_permute4 {
    static const unsigned limit = 256;
    static void test(TestResultsSet& tc, const V& a)
    {
        const unsigned s0 = i / 64 % 4;
        const unsigned s1 = i / 16 % 4;
        const unsigned s2 = i / 4 % 4;
        const unsigned s3 = i % 4;

        V r = simd::permute4<s0,s1,s2,s3>(a);
        TEST_PUSH(tc, V, r);
    }
};

template<unsigned B>
void test_permute_generic_n(TestResultsSet& tc)
{
    using namespace simd;

    Vectors<B,2> v;

    // There are no permute instructions for int8<N>

    // int16
    TemplateTestHelper<Test_permute2, uint16<B/2>>::run(tc, v.u16[0]);
    TemplateTestHelper<Test_permute4, uint16<B/2>>::run(tc, v.u16[0]);

    // int32
    TemplateTestHelper<Test_permute2, uint32<B/4>>::run(tc, v.u32[0]);
    TemplateTestHelper<Test_permute4, uint32<B/4>>::run(tc, v.u32[0]);

    // int64
    TemplateTestHelper<Test_permute2, uint64<B/8>>::run(tc, v.u64[0]);

    // float32
    TemplateTestHelper<Test_permute2, float32<B/4>>::run(tc, v.f32[0]);
    TemplateTestHelper<Test_permute4, float32<B/4>>::run(tc, v.f32[0]);

    // float64
    TemplateTestHelper<Test_permute2, float64<B/8>>::run(tc, v.f64[0]);
}

void test_permute_generic(TestResults& res)
{
    TestResultsSet& tc = res.new_results_set("permute_generic");

    test_permute_generic_n<16>(tc);
    test_permute_generic_n<32>(tc);
    test_permute_generic_n<64>(tc);
}

} // namespace SIMD_ARCH_NAMESPACE
