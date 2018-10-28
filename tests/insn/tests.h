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

#ifndef SIMD_TEST_INSN_TESTS_H
#define SIMD_TEST_INSN_TESTS_H

#include "../utils/test_helpers.h"
#include "../utils/test_results.h"

#include <cstdint>
#include <iostream>

namespace SIMD_ARCH_NAMESPACE {

    void main_test_function(TestResults &res, TestReporter &tr, const TestOptions &opts);
    void test_bitwise(TestResults &res, TestReporter &tr);
    void test_blend(TestResults &res);
    void test_compare(TestResults &res);
    void test_convert(TestResults &res);
    void test_construct(TestResults &res);
    void test_for_each(TestResults &res, TestReporter &tr);
    void test_math_fp(TestResults &res, const TestOptions &opts);
    void test_math_int(TestResults &res);
    void test_math_shift(TestResults &res);
    void test_memory_load(TestResults &res, TestReporter &tr);
    void test_memory_store(TestResults &res, TestReporter &tr);
    void test_set(TestResults &res);
    void test_shuffle(TestResults &res);
    void test_shuffle_bytes(TestResults &res, TestReporter &tr);
    void test_shuffle_generic(TestResults &res);
    void test_permute_generic(TestResults &res);
    void test_shuffle_transpose(TestResults &res);
    void test_test_utils(TestResults &res);
    void test_transpose(TestResults &res);

} // namespace SIMD_ARCH_NAMESPACE

std::vector<simd::detail::FnVersion> get_test_archs();

#endif
