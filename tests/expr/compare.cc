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

#include <bigmath/simd/simd.h>
#include "../utils/test_results_set.h"
#include "../utils/test_helpers.h"
#include "../common/vectors.h"
#include "../common/masks.h"


template<class V, unsigned B>
void test_expr_compare_v(TestReporter& ts)
{
    SIMD_ARCH_NAMESPACE::Vectors<16,16> v;

    using namespace simd;

    for (unsigned i = 0; i < 4; ++i) {
        V a = load(v.pu8+(i*4+0)*B);
        V b = load(v.pu8+(i*4+1)*B);

        // operators
        TEST_EQUAL(ts, cmp_eq(a, b), a == b);
        TEST_EQUAL(ts, cmp_lt(a, b), a < b);
        TEST_EQUAL(ts, cmp_le(a, b), a <= b);
        TEST_EQUAL(ts, cmp_gt(a, b), a > b);
        TEST_EQUAL(ts, cmp_ge(a, b), a >= b);

        // scalar arguments not implemented yet
        TEST_EQUAL(ts, cmp_eq(a, make_int<V>(2)), a == 2);
        TEST_EQUAL(ts, cmp_lt(a, make_int<V>(2)), a < 2);
        TEST_EQUAL(ts, cmp_le(a, make_int<V>(2)), a <= 2);
        TEST_EQUAL(ts, cmp_gt(a, make_int<V>(2)), a > 2);
        TEST_EQUAL(ts, cmp_ge(a, make_int<V>(2)), a >= 2);

        TEST_EQUAL(ts, cmp_eq(a, make_float<V>(2.2)), a == 2.2);
        TEST_EQUAL(ts, cmp_lt(a, make_float<V>(2.2)), a < 2.2);
        TEST_EQUAL(ts, cmp_le(a, make_float<V>(2.2)), a <= 2.2);
        TEST_EQUAL(ts, cmp_gt(a, make_float<V>(2.2)), a > 2.2);
        TEST_EQUAL(ts, cmp_ge(a, make_float<V>(2.2)), a >= 2.2);
    }
}

template<unsigned B>
void test_expr_compare_n(TestReporter& tr)
{
    using namespace simd;

    test_expr_compare_v<uint8<B>, B>(tr);
    test_expr_compare_v<int8<B>, B>(tr);

    test_expr_compare_v<uint16<B/2>, B>(tr);
    test_expr_compare_v<int16<B/2>, B>(tr);

    test_expr_compare_v<uint32<B/4>, B>(tr);
    test_expr_compare_v<int32<B/4>, B>(tr);

#if SIMD_USE_NULL || SIMD_USE_AVX2 || SIMD_USE_NEON64
    test_expr_compare_v<uint64<B/8>, B>(tr);
    test_expr_compare_v<int64<B/8>, B>(tr);
#endif

    test_expr_compare_v<float32<B/4>, B>(tr);
    test_expr_compare_v<float64<B/8>, B>(tr);
}

void test_expr_compare(TestReporter& tr)
{
    test_expr_compare_n<16>(tr);
    test_expr_compare_n<32>(tr);
    test_expr_compare_n<64>(tr);
}
