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
#include <bigmath/simd/simd.h>

namespace SIMD_ARCH_NAMESPACE {

#if (__clang_major__ == 3) && (__clang_minor__ == 5)
// clang 3.5 crashes when compiling lambda in the test
template<class E, class Sum>
class SumClosure {
public:
    SumClosure(Sum& sum) : sum_(sum) {}

    void operator()(E el) { sum_ += (Sum) el; }

private:
    Sum& sum_;
};
#endif

template<class V>
void test_for_each_type(TestResultsSet& ts, TestReporter& tr)
{
    using namespace simd;
    using E = typename V::element_type;

    TestData<V> s;
    s.add(make_uint(0, 1, 2, 3));
    s.add(make_uint(0, 0, 0, 0));
    s.add(make_uint(0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff));

    for (unsigned i = 0; i < s.size(); ++i) {
        V v = s[i];
        uint64_t sum = 0;
#if (__clang_major__ == 3) && (__clang_minor__ == 5)
        for_each(v, SumClosure<E,uint64_t>(sum));
#else
        for_each(v, [&](E el) { sum += (uint64_t) el; });
#endif
        TEST_PUSH(ts, uint64_t, sum);
    }

    V v1234 = make_uint(1, 2, 3, 4);
    E expected;
    switch (V::length) {
    case 1: expected = 1; break;
    case 2: expected = 3; break;
    case 4: expected = 10; break;
    default:
        expected = 10 * V::length / 4;
    }
    E sum = 0;
#if (__clang_major__ == 3) && (__clang_minor__ == 5)
    for_each(v1234, SumClosure<E, E>(sum));
#else
    for_each(v1234, [&](E el) { sum += (uint64_t) el; });
#endif

    TEST_EQUAL(tr, expected, sum);
}

template<unsigned B>
void test_for_each_n(TestResultsSet& ts, TestReporter& tr)
{
    using namespace simd;

    using int8_n = uint8<B>;
    using int16_n = uint16<B/2>;
    using int32_n = uint32<B/4>;
    using int64_n = uint64<B/8>;
    using uint8_n = uint8<B>;
    using uint16_n = uint16<B/2>;
    using uint32_n = uint32<B/4>;
    using uint64_n = uint64<B/8>;
    using float32_n = float32<B/4>;
    using float64_n = float64<B/8>;

    test_for_each_type<int8_n>(ts, tr);
    test_for_each_type<int16_n>(ts, tr);
    test_for_each_type<int32_n>(ts, tr);
    test_for_each_type<int64_n>(ts, tr);
    test_for_each_type<uint8_n>(ts, tr);
    test_for_each_type<uint16_n>(ts, tr);
    test_for_each_type<uint32_n>(ts, tr);
    test_for_each_type<uint64_n>(ts, tr);
    test_for_each_type<float32_n>(ts, tr);
    test_for_each_type<float64_n>(ts, tr);
}

void test_for_each(TestResults& res, TestReporter& tr)
{
    TestResultsSet& ts = res.new_results_set("foreach");
    test_for_each_n<16>(ts, tr);
    test_for_each_n<32>(ts, tr);
    test_for_each_n<64>(ts, tr);
}

} // namespace SIMD_ARCH_NAMESPACE
