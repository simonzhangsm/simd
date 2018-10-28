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
struct Test_shift_l {
    static const unsigned limit = V::num_bits - 1;
    static void test(TestResultsSet& tc, const V& a)
    {
        V b = simd::shift_l<i>(a);
        V c = simd::shift_l(a, i);
        TEST_PUSH(tc, V, b);
        TEST_PUSH(tc, V, c);
    }
};

template<class V, unsigned i>
struct Test_shift_r {
    static const unsigned limit = V::num_bits - 1;
    static void test(TestResultsSet& tc, const V& a)
    {
        V b = simd::shift_r<i>(a);
        V c = simd::shift_r(a, i);
        TEST_PUSH(tc, V, b);
        TEST_PUSH(tc, V, c);
    }
};

template<unsigned B>
void test_math_shift_int8_n(TestResultsSet& tc)
{
    using namespace simd;

    const unsigned vnum = 8;
    Vectors<B,vnum> v;

    using UV = uint8<B>;
    using IV = int8<B>;

    TemplateTestArrayHelper<Test_shift_l, UV>::run(tc, v.u8, vnum);
    TemplateTestArrayHelper<Test_shift_l, IV>::run(tc, v.i8, vnum);
    TemplateTestArrayHelper<Test_shift_r, UV>::run(tc, v.u8, vnum);
    TemplateTestArrayHelper<Test_shift_r, IV>::run(tc, v.i8, vnum);

    TestData<UV> shift;
    for (unsigned i = 0; i < 8; ++i) {
        shift.add(make_uint(i));
    }
    shift.add(make_uint(0, 1, 2, 3, 4, 5, 6, 7));
    TestData<UV> data;
    data.add(make_uint(0));
    data.add(make_uint(0xff));
    data.add(make_uint(0xff, 0));
    data.add(make_uint(0, 0xff));
    data.add(make_uint(0x55));
    data.add(make_uint(0x55, 0));
    data.add(make_uint(0, 0x55));
    data.add(make_uint(0xaa));
    data.add(make_uint(0xaa, 0));
    data.add(make_uint(0, 0xaa));

#if SIMD_HAS_UINT8_SHIFT_L_BY_VECTOR
    TEST_PUSH_ALL_COMB_OP2_SEPARATE_T(tc, UV, UV, UV, shift_l, data, shift);
#endif
#if SIMD_HAS_UINT8_SHIFT_R_BY_VECTOR
    TEST_PUSH_ALL_COMB_OP2_SEPARATE_T(tc, UV, UV, UV, shift_r, data, shift);
#endif
#if SIMD_HAS_INT8_SHIFT_R_BY_VECTOR
    TEST_PUSH_ALL_COMB_OP2_SEPARATE_T(tc, IV, IV, UV, shift_r, data, shift);
#endif
}

template<unsigned B>
void test_math_shift_int16_n(TestResultsSet& tc)
{
    using namespace simd;

    const unsigned vnum = 8;
    Vectors<B,vnum> v;

    using UV = uint16<B/2>;
    using IV = int16<B/2>;

    TemplateTestArrayHelper<Test_shift_l, UV>::run(tc, v.u16, vnum);
    TemplateTestArrayHelper<Test_shift_l, IV>::run(tc, v.i16, vnum);
    TemplateTestArrayHelper<Test_shift_r, UV>::run(tc, v.u16, vnum);
    TemplateTestArrayHelper<Test_shift_r, IV>::run(tc, v.i16, vnum);


    TestData<UV> shift;
    for (unsigned i = 0; i < 16; ++i) {
        shift.add(make_uint(i));
    }
    shift.add(make_uint(0, 1, 2, 3, 4, 5, 6, 7));

    TestData<UV> data;
    data.add(make_uint(0));
    data.add(make_uint(0xffff));
    data.add(make_uint(0xffff, 0));
    data.add(make_uint(0, 0xffff));
    data.add(make_uint(0x5555));
    data.add(make_uint(0x5555, 0));
    data.add(make_uint(0, 0x5555));
    data.add(make_uint(0xaaaa));
    data.add(make_uint(0xaaaa, 0));
    data.add(make_uint(0, 0xaaaa));
    data.add(make_uint(0xa00a));
    data.add(make_uint(0xa00a, 0));
    data.add(make_uint(0, 0xa00a));

#if SIMD_HAS_UINT16_SHIFT_L_BY_VECTOR
    TEST_PUSH_ALL_COMB_OP2_SEPARATE_T(tc, UV, UV, UV, shift_l, data, shift);
#endif
#if SIMD_HAS_UINT16_SHIFT_R_BY_VECTOR
    TEST_PUSH_ALL_COMB_OP2_SEPARATE_T(tc, UV, UV, UV, shift_r, data, shift);
#endif
#if SIMD_HAS_INT16_SHIFT_R_BY_VECTOR
    TEST_PUSH_ALL_COMB_OP2_SEPARATE_T(tc, IV, IV, UV, shift_r, data, shift);
#endif
}

template<unsigned B>
void test_math_shift_int32_n(TestResultsSet& tc)
{
    using namespace simd;

    const unsigned vnum = 8;
    Vectors<B,vnum> v;

    using UV = uint32<B/4>;
    using IV = int32<B/4>;

    TemplateTestArrayHelper<Test_shift_l, UV>::run(tc, v.u32, vnum);
    TemplateTestArrayHelper<Test_shift_l, IV>::run(tc, v.i32, vnum);
    TemplateTestArrayHelper<Test_shift_r, UV>::run(tc, v.u32, vnum);
    TemplateTestArrayHelper<Test_shift_r, IV>::run(tc, v.i32, vnum);

    TestData<UV> shift;
    for (unsigned i = 0; i < 32; ++i) {
        shift.add(make_uint(i));
    }
    shift.add(make_int(0, 1, 2, 3));
    shift.add(make_int(4, 5, 6, 7));

    TestData<UV> data;
    data.add(make_uint(0));
    data.add(make_uint(0xffffffff));
    data.add(make_uint(0xffffffff, 0));
    data.add(make_uint(0, 0xffffffff));
    data.add(make_uint(0x55555555));
    data.add(make_uint(0x55555555, 0));
    data.add(make_uint(0, 0x55555555));
    data.add(make_uint(0xaaaaaaaa));
    data.add(make_uint(0xaaaaaaaa, 0));
    data.add(make_uint(0, 0xaaaaaaaa));
    data.add(make_uint(0xa000000a));
    data.add(make_uint(0xa000000a, 0));
    data.add(make_uint(0, 0xa000000a));

#if SIMD_HAS_UINT32_SHIFT_L_BY_VECTOR
    TEST_PUSH_ALL_COMB_OP2_SEPARATE_T(tc, UV, UV, UV, shift_l, data, shift);
#endif
#if SIMD_HAS_UINT32_SHIFT_R_BY_VECTOR
    TEST_PUSH_ALL_COMB_OP2_SEPARATE_T(tc, UV, UV, UV, shift_r, data, shift);
#endif
#if SIMD_HAS_INT32_SHIFT_R_BY_VECTOR
    TEST_PUSH_ALL_COMB_OP2_SEPARATE_T(tc, IV, IV, UV, shift_r, data, shift);
#endif
}

template<unsigned B>
void test_math_shift_int64_n(TestResultsSet& tc)
{
    using namespace simd;

    const unsigned vnum = 8;
    Vectors<B,vnum> v;

    using UV = uint64<B/8>;
    using IV = int64<B/8>;

    TemplateTestArrayHelper<Test_shift_l, UV>::run(tc, v.u64, vnum);
    TemplateTestArrayHelper<Test_shift_l, IV>::run(tc, v.i64, vnum);
    TemplateTestArrayHelper<Test_shift_r, UV>::run(tc, v.u64, vnum);
    TemplateTestArrayHelper<Test_shift_r, IV>::run(tc, v.i64, vnum);
}

void test_math_shift(TestResults& res)
{
    TestResultsSet& tc = res.new_results_set("math_shift");

    test_math_shift_int8_n<16>(tc);
    test_math_shift_int16_n<16>(tc);
    test_math_shift_int32_n<16>(tc);
    test_math_shift_int64_n<16>(tc);
    test_math_shift_int8_n<32>(tc);
    test_math_shift_int16_n<32>(tc);
    test_math_shift_int32_n<32>(tc);
    test_math_shift_int64_n<32>(tc);
    test_math_shift_int8_n<64>(tc);
    test_math_shift_int16_n<64>(tc);
    test_math_shift_int32_n<64>(tc);
    test_math_shift_int64_n<64>(tc);
}

} // namespace SIMD_ARCH_NAMESPACE
