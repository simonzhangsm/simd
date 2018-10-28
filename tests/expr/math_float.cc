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
void test_expr_math_float_v(TestReporter& ts)
{
    SIMD_ARCH_NAMESPACE::Vectors<16,16> v;

    using namespace simd;

    for (unsigned i = 0; i < 4; ++i) {
        V a = load(v.pu8+(i*4+0)*B);
        V b = load(v.pu8+(i*4+1)*B);
        V c = load(v.pu8+(i*4+2)*B);
        V d = load(v.pu8+(i*4+3)*B);

        // operators
        TEST_EQUAL(ts, add(a, b), a + b);
        TEST_EQUAL(ts, add(a, mul(b, c)), a + b * c);
        TEST_EQUAL(ts, add(a, sub(b, c)), a + (b - c));
        TEST_EQUAL(ts, add(a, abs(b)), a + abs(b));
        TEST_EQUAL(ts, mul(a, b), a * b);
        TEST_EQUAL(ts, mul(a, mul(b, c)), a * b * c);
        TEST_EQUAL(ts, mul(a, sub(b, c)), a * (b - c));
        TEST_EQUAL(ts, mul(a, abs(b)), a * abs(b));
        TEST_EQUAL(ts, mul(a, sub(b, bit_not(c))), a * (b - ~c));

        // expressions
        TEST_EQUAL(ts, add(a, add(b, c)), add(a, add(b, c).eval()));
        TEST_EQUAL(ts, add(add(b, c), a), add(add(b, c).eval(), a));
        TEST_EQUAL(ts, sub(a, sub(b, c)), sub(a, sub(b, c).eval()));
        TEST_EQUAL(ts, sub(sub(b, c), a), sub(sub(b, c).eval(), a));
        TEST_EQUAL(ts, mul(a, mul(b, c)), mul(a, mul(b, c).eval()));
        TEST_EQUAL(ts, mul(mul(b, c), a), mul(mul(b, c).eval(), a));
        TEST_EQUAL(ts, fmadd(a, d, fmadd(b, c, a)), fmadd(a, d, fmadd(b, c, a).eval()));
        TEST_EQUAL(ts, fmadd(a, fmadd(b, c, a), d), fmadd(a, fmadd(b, c, a).eval(), d));
        TEST_EQUAL(ts, fmadd(fmadd(b, c, a), a, d), fmadd(fmadd(b, c, a).eval(), a, d));
        TEST_EQUAL(ts, fmsub(a, d, fmsub(b, c, a)), fmsub(a, d, fmsub(b, c, a).eval()));
        TEST_EQUAL(ts, fmsub(a, fmsub(b, c, a), d), fmsub(a, fmsub(b, c, a).eval(), d));
        TEST_EQUAL(ts, fmsub(fmsub(b, c, a), a, d), fmsub(fmsub(b, c, a).eval(), a, d));
        TEST_EQUAL(ts, abs(mul(a, b)), abs(mul(a, b).eval()));
        TEST_EQUAL(ts, neg(mul(a, b)), neg(mul(a, b).eval()));

        // scalar arguments
        TEST_EQUAL(ts, add(a, make_float<V>(1234.1234f)), a + 1234.1234f);
        TEST_EQUAL(ts, add(make_float<V>(1234.1234f), a), 1234.1234f + a);
        TEST_EQUAL(ts, add(a, make_int<V>(1234)), a + 1234);
        TEST_EQUAL(ts, add(make_int<V>(1234), a), 1234 + a);
        // TEST_EQUAL(ts, add(a, make_int<V>(1234ll)), a + 1234ll);
        // TEST_EQUAL(ts, add(make_int<V>(1234ll), a), 1234ll + a);
        TEST_EQUAL(ts, add(a, make_int<V>(0x80000000)), a + 0x80000000);
        TEST_EQUAL(ts, add(make_int<V>(0x80000000), a), 0x80000000 + a);
        TEST_EQUAL(ts, add(a, make_uint<V>(0x80000000)), a + 0x80000000);
        TEST_EQUAL(ts, add(make_uint<V>(0x80000000), a), 0x80000000 + a);
        TEST_EQUAL(ts, add(a, make_int<V>(0xf12341234)), a + 0xf12341234);
        TEST_EQUAL(ts, add(make_int<V>(0xf12341234), a), 0xf12341234 + a);
        // TEST_EQUAL(ts, add(a, make_int<V>(0xf12341234ull)), a + 0xf12341234ull);
        // TEST_EQUAL(ts, add(make_int<V>(0xf12341234ull), a), 0xf12341234ull + a);
    }
}


void test_expr_math_float(TestReporter& ts)
{
    using namespace simd;

    test_expr_math_float_v<float32<4>, 16>(ts);
    test_expr_math_float_v<float64<2>, 16>(ts);
}
