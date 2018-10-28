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

#ifndef TEST_TEST_UTILS_TEST_REPORTER_H
#define TEST_TEST_UTILS_TEST_REPORTER_H

#include <iostream>

/// Stores the summary of the tests that have been run so far (the number of
/// successful and failed test cases). Also, stores a reference to output
/// stream where the actual test results should be reported.
class TestReporter {
public:
    TestReporter(std::ostream &str) : num_failure_(0), num_success_(0), output_(str) {
    }

    unsigned num_failure() const {
        return num_failure_;
    }
    unsigned num_success() const {
        return num_success_;
    }

    void add_result(bool success) {
        if (success) {
            num_success_++;
        } else {
            num_failure_++;
        }
    }

    bool success() const {
        return num_failure_ == 0;
    }

    std::ostream &out() {
        return output_;
    }

    void report_summary() {
        output_ << "Test summary:\n"
                << "Number of tests:  " << num_success() + num_failure() << "\n"
                << "Successful tests: " << num_success() << "\n"
                << "Failed tests:     " << num_failure() << "\n";
    }

private:
    unsigned num_failure_;
    unsigned num_success_;
    std::ostream &output_;
};


#endif
