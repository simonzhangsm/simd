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

template<class V, unsigned vnum>
void test_load_helper(TestResultsSet& tc, TestReporter& tr,
                      const typename V::element_type* sdata)
{
    using namespace simd;
    V zero = make_zero();

    V sv[vnum];
    std::memcpy(sv, sdata, V::length_bytes * vnum);

    // On certain architectures, e.g. armv7 NEON, 128 bit vectors are not
    // necessarily aligned to 16 bytes on the stack.
    // NOTE: MSVC 2013 does not support constant expressions within
    // SIMDALIGN, thus we're aligning to the alignment of the largest V
    // is going to be instantiated with
    SIMDALIGN(64) V rv[vnum];

    auto rzero = [&](V* r)
    {
        std::memset(r, 0, V::length_bytes * vnum);
    };

    // calls constructor that accepts expr_construct
    for (unsigned i = 0; i < vnum; i++) {
        V r = simd::load(sdata + i*V::length);
        TEST_PUSH(tc, V, r);
        TEST_EQUAL(tr, sv[i], r);
    }

    for (unsigned i = 0; i < (vnum-1)*V::length; i++) {
        V r = simd::load_u(sdata+i);
        TEST_PUSH(tc, V, r);
        TEST_NOT_EQUAL(tr, zero, r);
    }

    // calls operator= that accepts expr_construct
    for (unsigned i = 0; i < vnum; i++) {
        V r;
        r = simd::load(sdata + i*V::length);
        TEST_PUSH(tc, V, r);
        TEST_EQUAL(tr, sv[i], r);
    }

    for (unsigned i = 0; i < (vnum-1)*V::length; i++) {
        V r;
        r = simd::load_u(sdata+i);
        TEST_PUSH(tc, V, r);
        TEST_NOT_EQUAL(tr, zero, r);
    }

    // initializes the vector directly
    for (unsigned i = 0; i < vnum; i++) {
        V r = simd::load<V>(sdata + i*V::length);
        TEST_PUSH(tc, V, r);
        TEST_EQUAL(tr, sv[i], r);
    }

    for (unsigned i = 0; i < (vnum-1)*V::length; i++) {
        V r = simd::load_u<V>(sdata+i);
        TEST_PUSH(tc, V, r);
        TEST_NOT_EQUAL(tr, zero, r);
    }

    rzero(rv);
    load_packed2(rv[0], rv[1], sdata);
    TEST_PUSH_ARRAY(tc, V, rv);
    TEST_NOT_EQUAL(tr, zero, rv[0]);
    TEST_NOT_EQUAL(tr, zero, rv[1]);

    rzero(rv);
    load_packed3(rv[0], rv[1], rv[2], sdata);
    TEST_PUSH_ARRAY(tc, V, rv);
    TEST_NOT_EQUAL(tr, zero, rv[0]);
    TEST_NOT_EQUAL(tr, zero, rv[1]);
    TEST_NOT_EQUAL(tr, zero, rv[2]);

    rzero(rv);
    load_packed4(rv[0], rv[1], rv[2], rv[3], sdata);
    TEST_PUSH_ARRAY(tc, V, rv);
    TEST_NOT_EQUAL(tr, zero, rv[0]);
    TEST_NOT_EQUAL(tr, zero, rv[1]);
    TEST_NOT_EQUAL(tr, zero, rv[2]);
    TEST_NOT_EQUAL(tr, zero, rv[3]);
}

template<unsigned B>
void test_memory_load_n(TestResultsSet& tc, TestReporter& tr)
{
    using namespace simd;

    // vnum must be at least 4
    const unsigned vnum = 4;
    Vectors<B,vnum> v;

    test_load_helper<uint8<B>, vnum>(tc, tr, v.pu8);
    test_load_helper<uint16<B/2>, vnum>(tc, tr, v.pu16);
    test_load_helper<uint32<B/4>, vnum>(tc, tr, v.pu32);
    test_load_helper<uint64<B/8>, vnum>(tc, tr, v.pu64);

    test_load_helper<int8<B>, vnum>(tc, tr, v.pi8);
    test_load_helper<int16<B/2>, vnum>(tc, tr, v.pi16);
    test_load_helper<int32<B/4>, vnum>(tc, tr, v.pi32);
    test_load_helper<int64<B/8>, vnum>(tc, tr, v.pi64);

    test_load_helper<float32<B/4>, vnum>(tc, tr, v.pf32);
    test_load_helper<float64<B/8>, vnum>(tc, tr, v.pf64);
}

void test_memory_load(TestResults& res, TestReporter& tr)
{
    TestResultsSet& tc = res.new_results_set("memory_load");

    test_memory_load_n<16>(tc, tr);
    test_memory_load_n<32>(tc, tr);
    test_memory_load_n<64>(tc, tr);
}

} // namespace SIMD_ARCH_NAMESPACE
