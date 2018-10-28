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
#include "../utils/test_reporter.h"
#include "../common/vectors.h"
#include "../common/masks.h"

void test_expr_bitwise(TestReporter& ts)
{
    SIMD_ARCH_NAMESPACE::Vectors<16,16> v;

    using namespace simd;

    for (unsigned i = 0; i < 4; ++i) {
        uint8<16> a = v.u8[i*4];
        uint8<16> b = v.u8[i*4+1];
        float32<4> q = v.f32[i*4+2];
        float32<4> p = v.f32[i*4+3];

        // operators
        TEST_EQUAL(ts, bit_and(a, b), a & b);
        TEST_EQUAL(ts, bit_or(a, b), a | b);
        TEST_EQUAL(ts, bit_xor(a, b), a ^ b);
        TEST_EQUAL(ts, bit_andnot(a, b), a & ~b);

        TEST_EQUAL(ts, bit_and(a, bit_or(q, p)), a & (q | p));
        TEST_EQUAL(ts, bit_xor(q, make_uint<uint32x4>(0x12341234)),
                   q ^ 0x12341234);
    }
}
