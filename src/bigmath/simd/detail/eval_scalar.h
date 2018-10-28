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

#ifndef SIMD_DETAIL_EVAL_SCALAR_H
#define SIMD_DETAIL_EVAL_SCALAR_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/setup_arch.h>
#include <bigmath/simd/expr.h>
#include <bigmath/simd/detail/expr/scalar.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {

            template <class R, class E> struct eval_maybe_scalar {
                static inline R eval(const E &e) {
                    return (R)e.eval();
                }
            };

            template <class R> struct eval_maybe_scalar<R, int> {
                static inline R eval(const int &e) {
                    return expr_eval_scalar<R>(e);
                }
            };

            template <class R> struct eval_maybe_scalar<R, long> {
                static inline R eval(const long &e) {
                    return expr_eval_scalar<R>(e);
                }
            };

            template <class R> struct eval_maybe_scalar<R, long long> {
                static inline R eval(const long long &e) {
                    return expr_eval_scalar<R>(e);
                }
            };

            template <class R> struct eval_maybe_scalar<R, unsigned> {
                static inline R eval(const unsigned &e) {
                    return expr_eval_scalar<R>(e);
                }
            };

            template <class R> struct eval_maybe_scalar<R, unsigned long> {
                static inline R eval(const unsigned long &e) {
                    return expr_eval_scalar<R>(e);
                }
            };

            template <class R> struct eval_maybe_scalar<R, unsigned long long> {
                static inline R eval(const unsigned long long &e) {
                    return expr_eval_scalar<R>(e);
                }
            };

            template <class R> struct eval_maybe_scalar<R, float> {
                static inline R eval(const float &e) {
                    return expr_eval_scalar<R>(e);
                }
            };

            template <class R> struct eval_maybe_scalar<R, double> {
                static inline R eval(const double &e) {
                    return expr_eval_scalar<R>(e);
                }
            };

            template <class R, class E> struct eval_maybe_scalar_bitwise {
                static inline R eval(const E &e) {
                    return (R)e.eval();
                }
            };

            template <class R> struct eval_maybe_scalar_bitwise<R, int> {
                static inline R eval(const int &e) {
                    return expr_eval_scalar_bitwise<R>(e);
                }
            };

            template <class R> struct eval_maybe_scalar_bitwise<R, long> {
                static inline R eval(const long &e) {
                    return expr_eval_scalar_bitwise<R>(e);
                }
            };

            template <class R> struct eval_maybe_scalar_bitwise<R, long long> {
                static inline R eval(const long long &e) {
                    return expr_eval_scalar_bitwise<R>(e);
                }
            };

            template <class R> struct eval_maybe_scalar_bitwise<R, unsigned> {
                static inline R eval(const unsigned &e) {
                    return expr_eval_scalar_bitwise<R>(e);
                }
            };

            template <class R> struct eval_maybe_scalar_bitwise<R, unsigned long> {
                static inline R eval(const unsigned long &e) {
                    return expr_eval_scalar_bitwise<R>(e);
                }
            };

            template <class R> struct eval_maybe_scalar_bitwise<R, unsigned long long> {
                static inline R eval(const unsigned long long &e) {
                    return expr_eval_scalar_bitwise<R>(e);
                }
            };

            template <class R> struct eval_maybe_scalar_bitwise<R, float> {
                static inline R eval(const float &e) {
                    return expr_eval_scalar_bitwise<R>(e);
                }
            };

            template <class R> struct eval_maybe_scalar_bitwise<R, double> {
                static inline R eval(const double &e) {
                    return expr_eval_scalar_bitwise<R>(e);
                }
            };

        } // namespace detail
    }     // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
