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

template<unsigned expected_tag, class V>
void test_type_tag_equal(const V&)
{
    static_assert(expected_tag == V::type_tag,
                  "Return type has been incorrectly resolved");
}

template<class V, unsigned B>
void test_expr_math_int_v(TestReporter& ts)
{
    SIMD_ARCH_NAMESPACE::Vectors<16,16> v;

    using namespace simd;

    for (unsigned i = 0; i < 4; ++i) {
        V a = load(v.pu8+(i*4+0)*B);
        V b = load(v.pu8+(i*4+1)*B);
        V c = load(v.pu8+(i*4+2)*B);

        // operators
        TEST_EQUAL(ts, add(a, b), a + b);
        TEST_EQUAL(ts, add(a, mul_lo(b, c)), a + b * c);
        TEST_EQUAL(ts, add(a, sub(b, c)), a + (b - c));
        //TEST_EQUAL(ts, add(a, neg(b)), a + neg(b));
        TEST_EQUAL(ts, mul_lo(a, b), a * b);
        TEST_EQUAL(ts, mul_lo(a, mul_lo(b, c)), a * b * c);
        TEST_EQUAL(ts, mul_lo(a, sub(b, c)), a * (b - c));
        //TEST_EQUAL(ts, mul_lo(a, neg(b)), a * neg(b));
        TEST_EQUAL(ts, mul_lo(a, sub(b, bit_not(c))), a * (b - ~c));
        TEST_EQUAL(ts, shift_l(a, 4), a << 4);
        TEST_EQUAL(ts, shift_r(a, 4), a >> 4);
        TEST_EQUAL(ts, shift_l<4>(a), a << 4);
        TEST_EQUAL(ts, shift_r<4>(a), a >> 4);

        // expressions
        TEST_EQUAL(ts, add(a, add(b, c)), add(a, add(b, c).eval()));
        TEST_EQUAL(ts, add(add(b, c), a), add(add(b, c).eval(), a));
        TEST_EQUAL(ts, sub(a, sub(b, c)), sub(a, sub(b, c).eval()));
        TEST_EQUAL(ts, sub(sub(b, c), a), sub(sub(b, c).eval(), a));
        //TEST_EQUAL(ts, add_sat(a, add_sat(b, c)), add_sat(a, add_sat(b, c).eval()));
        //TEST_EQUAL(ts, add_sat(add_sat(b, c), a), add_sat(add_sat(b, c).eval(), a));
        //TEST_EQUAL(ts, sub_sat(a, sub_sat(b, c)), sub_sat(a, sub_sat(b, c).eval()));
        //TEST_EQUAL(ts, sub_sat(sub_sat(b, c), a), sub_sat(sub_sat(b, c).eval(), a));
        TEST_EQUAL(ts, mul_lo(a, mul_lo(b, c)), mul_lo(a, mul_lo(b, c).eval()));
        TEST_EQUAL(ts, mul_lo(mul_lo(b, c), a), mul_lo(mul_lo(b, c).eval(), a));
        //TEST_EQUAL(ts, abs(add(a, b)), abs(add(a, b).eval()));
        //TEST_EQUAL(ts, neg(add(a, b)), neg(add(a, b).eval()));

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

template<class SignedV, class UnsignedV>
void test_expr_math_int_return_types_add()
{
    using namespace simd;

    UnsignedV u = splat(0);
    SignedV s = splat(0);
    unsigned ue = 1;
    int se = 1;
    test_type_tag_equal<SIMD_TAG_UINT>(add(u, u));
    test_type_tag_equal<SIMD_TAG_UINT>(add(u, ue));
    test_type_tag_equal<SIMD_TAG_UINT>(add(ue, u));
    test_type_tag_equal<SIMD_TAG_UINT>(u + u);
    test_type_tag_equal<SIMD_TAG_UINT>(u + ue);
    test_type_tag_equal<SIMD_TAG_UINT>(ue + u);

    test_type_tag_equal<SIMD_TAG_UINT>(add(s, u));
    test_type_tag_equal<SIMD_TAG_UINT>(add(s, ue));
    test_type_tag_equal<SIMD_TAG_UINT>(add(u, s));
    test_type_tag_equal<SIMD_TAG_UINT>(add(u, se));
    test_type_tag_equal<SIMD_TAG_UINT>(add(se, u));
    test_type_tag_equal<SIMD_TAG_UINT>(add(ue, s));
    test_type_tag_equal<SIMD_TAG_UINT>(s + u);
    test_type_tag_equal<SIMD_TAG_UINT>(s + ue);
    test_type_tag_equal<SIMD_TAG_UINT>(u + s);
    test_type_tag_equal<SIMD_TAG_UINT>(u + se);
    test_type_tag_equal<SIMD_TAG_UINT>(se + u);
    test_type_tag_equal<SIMD_TAG_UINT>(ue + s);

    test_type_tag_equal<SIMD_TAG_INT>(add(s, s));
    test_type_tag_equal<SIMD_TAG_INT>(add(s, se));
    test_type_tag_equal<SIMD_TAG_INT>(add(se, s));
    test_type_tag_equal<SIMD_TAG_INT>(s + s);
    test_type_tag_equal<SIMD_TAG_INT>(s + se);
    test_type_tag_equal<SIMD_TAG_INT>(se + s);
}

void test_expr_math_int(TestReporter& ts)
{
    using namespace simd;

    test_expr_math_int_v<int16<8>, 16>(ts);
    test_expr_math_int_v<uint16<8>, 16>(ts);
    test_expr_math_int_v<uint32<4>, 16>(ts);

    // All integer expressions use get_expr_uint, it's enough to test one
    // expression type extensively to get proper coverage of all return types
    test_expr_math_int_return_types_add<int8<16>, uint8<16>>();
    test_expr_math_int_return_types_add<int8<32>, uint8<32>>();
    test_expr_math_int_return_types_add<int8<64>, uint8<64>>();
    test_expr_math_int_return_types_add<int16<8>, uint16<8>>();
    test_expr_math_int_return_types_add<int16<16>, uint16<16>>();
    test_expr_math_int_return_types_add<int16<32>, uint16<32>>();
    test_expr_math_int_return_types_add<int32<4>, uint32<4>>();
    test_expr_math_int_return_types_add<int32<8>, uint32<8>>();
    test_expr_math_int_return_types_add<int32<16>, uint32<16>>();
    test_expr_math_int_return_types_add<int64<2>, uint64<2>>();
    test_expr_math_int_return_types_add<int64<4>, uint64<4>>();
    test_expr_math_int_return_types_add<int64<8>, uint64<8>>();
}
