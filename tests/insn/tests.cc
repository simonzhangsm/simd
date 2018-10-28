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
#include "tests.h"
#include <bigmath/simd/simd.h>
#include <vector>

static_assert(sizeof(simd::uint8<16>) == 16, "Incorrect vector size");
static_assert(sizeof(simd::int8<16>) == 16, "Incorrect vector size");
static_assert(sizeof(simd::uint16<8>) == 16, "Incorrect vector size");
static_assert(sizeof(simd::int16<8>) == 16, "Incorrect vector size");
static_assert(sizeof(simd::uint32<4>) == 16, "Incorrect vector size");
static_assert(sizeof(simd::int32<4>) == 16, "Incorrect vector size");
static_assert(sizeof(simd::uint64<2>) == 16, "Incorrect vector size");
static_assert(sizeof(simd::int64<2>) == 16, "Incorrect vector size");
static_assert(sizeof(simd::float32<4>) == 16, "Incorrect vector size");
static_assert(sizeof(simd::float64<2>) == 16, "Incorrect vector size");

static_assert(sizeof(simd::uint8<32>) == 32, "Incorrect vector size");
static_assert(sizeof(simd::int8<32>) == 32, "Incorrect vector size");
static_assert(sizeof(simd::uint16<16>) == 32, "Incorrect vector size");
static_assert(sizeof(simd::int16<16>) == 32, "Incorrect vector size");
static_assert(sizeof(simd::uint32<8>) == 32, "Incorrect vector size");
static_assert(sizeof(simd::int32<8>) == 32, "Incorrect vector size");
static_assert(sizeof(simd::uint64<4>) == 32, "Incorrect vector size");
static_assert(sizeof(simd::int64<4>) == 32, "Incorrect vector size");
static_assert(sizeof(simd::float32<8>) == 32, "Incorrect vector size");
static_assert(sizeof(simd::float64<4>) == 32, "Incorrect vector size");

static_assert(sizeof(simd::uint8<64>) == 64, "Incorrect vector size");
static_assert(sizeof(simd::int8<64>) == 64, "Incorrect vector size");
static_assert(sizeof(simd::uint16<32>) == 64, "Incorrect vector size");
static_assert(sizeof(simd::int16<32>) == 64, "Incorrect vector size");
static_assert(sizeof(simd::uint32<16>) == 64, "Incorrect vector size");
static_assert(sizeof(simd::int32<16>) == 64, "Incorrect vector size");
static_assert(sizeof(simd::uint64<8>) == 64, "Incorrect vector size");
static_assert(sizeof(simd::int64<8>) == 64, "Incorrect vector size");
static_assert(sizeof(simd::float32<16>) == 64, "Incorrect vector size");
static_assert(sizeof(simd::float64<8>) == 64, "Incorrect vector size");

namespace SIMD_ARCH_NAMESPACE {

void main_test_function(TestResults& res, TestReporter& tr, const TestOptions& opts)
{
    test_test_utils(res);

    // Tests are ordered in such a way so that base functionality that other
    // tests depend on is tested first.
    test_construct(res);
    test_memory_load(res, tr);
    test_memory_store(res, tr);

    test_blend(res);
    test_bitwise(res, tr);
    test_permute_generic(res);
    test_shuffle_generic(res);
    test_shuffle(res);
    test_shuffle_bytes(res, tr);

    test_convert(res);
    test_math_fp(res, opts);
    test_math_int(res);
    test_compare(res);
    test_math_shift(res);
    test_transpose(res);

    test_for_each(res, tr);
}

} // namespace SIMD_ARCH_NAMESPACE
/* TODO: here we use dispatcher only to register the available functions, not
    to dispatch them. To simplify, use a dummy function for SIMD_USER_ARCH_INFO
*/
inline simd::Arch get_arch()
{
    return simd::Arch();
}

#define SIMD_USER_ARCH_INFO get_arch()

SIMD_MAKE_DISPATCHER_VOID3(main_test_function, TestResults&, TestReporter&, const TestOptions&)

#if SIMD_EMIT_DISPATCHER
std::vector<simd::detail::FnVersion> get_test_archs()
{
    simd::detail::FnVersion versions[SIMD_DISPATCH_MAX_ARCHS] = {};
    using FunPtr = void(*)(TestResults&, TestReporter&, const TestOptions&);
    SIMD_DISPATCH_COLLECT_FUNCTIONS(versions, main_test_function, FunPtr)
    std::vector<simd::detail::FnVersion> result;
    result.assign(versions, versions+SIMD_DISPATCH_MAX_ARCHS);
    return result;
}
#endif

