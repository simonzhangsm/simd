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

template<unsigned B>
void test_transpose_n(TestResultsSet& tc)
{
    using namespace simd;
    Vectors<B,8> v;

    // int8x16
    transpose4(v.u8[0], v.u8[1], v.u8[2], v.u8[3]);
    TEST_PUSH_ARRAY(tc, uint8<B>, v.u8);
    v.reset();

    // int16
    transpose4(v.u16[0], v.u16[1], v.u16[2], v.u16[3]);
    TEST_PUSH_ARRAY(tc, uint16<B/2>, v.u16);
    v.reset();

    transpose2(v.u16[0], v.u16[1]);
    TEST_PUSH_ARRAY(tc, uint16<B/2>, v.u16);
    v.reset();

    // int32
    transpose4(v.u32[0], v.u32[1], v.u32[2], v.u32[3]);
    TEST_PUSH_ARRAY(tc, uint32<B/4>, v.u32);
    v.reset();

    transpose2(v.u32[0], v.u32[1]);
    TEST_PUSH_ARRAY(tc, uint32<B/4>, v.u32);
    v.reset();

    // int64
    transpose2(v.u64[0], v.u64[1]);
    TEST_PUSH_ARRAY(tc, uint64<B/8>, v.u64);
    v.reset();

    // float32
    transpose4(v.f32[0], v.f32[1], v.f32[2], v.f32[3]);
    TEST_PUSH_ARRAY(tc, float32<B/4>, v.f32);
    v.reset();

    transpose2(v.f32[0], v.f32[1]);
    TEST_PUSH_ARRAY(tc, float32<B/4>, v.f32);
    v.reset();

    // float64
    transpose2(v.f64[0], v.f64[1]);
    TEST_PUSH_ARRAY(tc, float64<B/8>, v.f64);
    v.reset();
}

void test_transpose(TestResults& res)
{
    TestResultsSet& tc = res.new_results_set("transpose");
    test_transpose_n<16>(tc);
    test_transpose_n<32>(tc);
    test_transpose_n<64>(tc);
}

} // namespace SIMD_ARCH_NAMESPACE
