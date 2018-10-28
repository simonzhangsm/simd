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

#ifndef TEST_UTILS_TEST_RESULTS_H
#define TEST_UTILS_TEST_RESULTS_H

#include "test_results_set.h"
#include "test_reporter.h"
#include <vector>
#include <deque>
#include <functional>
#include <algorithm>

struct TestOptions {
    bool is_simulator;

    TestOptions() : is_simulator(false) {
    }
};

/** Represents all test results for a particular architecture
 */
class TestResults {
public:
    // test case container.
    struct TestCaseCont {
        unsigned id; // insertion number. Used for sorting
        TestResultsSet results_set;
    };

    TestResults(const char *arch) : arch_{arch} {
    }

    TestResultsSet &new_results_set(const char *name) {
        unsigned id = (unsigned)test_sets_.size();
        test_sets_.push_back(TestCaseCont{id, TestResultsSet{name}});
        return test_sets_.back().results_set;
    }

private:
    friend void report_test_comparison(const TestResults &a, const TestResults &b, TestReporter &tr);

    const char *arch_;
    // use deque because we must never invalidate references to test cases
    std::deque<TestCaseCont> test_sets_;
};

inline void report_test_comparison(const TestResults &a, const TestResults &b, TestReporter &tr) {
    using TestCaseCont = TestResults::TestCaseCont;
    using CaseContPair =
        std::pair<std::reference_wrapper<const TestCaseCont>, std::reference_wrapper<const TestCaseCont>>;

    using CaseContRef = std::reference_wrapper<const TestCaseCont>;

    auto case_cont_cmp = [](const TestCaseCont &lhs, const TestCaseCont &rhs) {
        return std::strcmp(lhs.results_set.name(), rhs.results_set.name()) < 0;
    };

    // sort the cases by name
    std::vector<CaseContRef> a_cases(a.test_sets_.begin(), a.test_sets_.end());
    std::vector<CaseContRef> b_cases(b.test_sets_.begin(), b.test_sets_.end());

    std::sort(a_cases.begin(), a_cases.end(), case_cont_cmp);
    std::sort(b_cases.begin(), b_cases.end(), case_cont_cmp);

    std::vector<CaseContPair> to_compare;

    auto first1 = a_cases.begin();
    auto last1 = a_cases.end();
    auto first2 = b_cases.begin();
    auto last2 = b_cases.end();

    // set intersection. Get test cases present in both result sets
    while (first1 != last1 && first2 != last2) {
        if (case_cont_cmp(first1->get(), first2->get())) {
            ++first1;
        } else {
            if (!case_cont_cmp(first2->get(), first1->get())) {
                to_compare.emplace_back(first1->get(), first2->get());
            }
            ++first2;
        }
    }

    // sort the cases in the order of insertion to the result set
    auto ins_cmp = [](const CaseContPair &lhs, const CaseContPair &rhs) {
        return lhs.first.get().id < rhs.first.get().id;
    };
    std::sort(to_compare.begin(), to_compare.end(), ins_cmp);

    // loop through cases with the same names
    for (const auto &io : to_compare) {
        report_test_comparison(io.first.get().results_set, a.arch_, io.second.get().results_set, b.arch_, tr);
    }
}

#endif
