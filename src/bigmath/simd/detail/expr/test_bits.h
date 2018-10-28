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

#ifndef SIMD_DETAIL_EXPR_TEST_BITS_H
#define SIMD_DETAIL_EXPR_TEST_BITS_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/expr.h>
#include <bigmath/simd/detail/insn/test_bits.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {

            template <unsigned N, class V> inline bool e_test_bits_any(const any_vec<N, V> &a) {
                typename detail::get_expr_nosign<V>::type ra;
                ra = a.wrapped().eval();
                return insn::i_test_bits_any(ra);
            }

#if SIMD_USE_SSE4_1
            template <unsigned N, template <unsigned, typename> class V, class V1, class V2>
            inline bool e_test_bits_any(const any_vec<16, V<N, expr_bit_and<V1, V2>>> &e) {
                uint8<16> a, b;
                a = e.wrapped().e.a.eval();
                b = e.wrapped().e.b.eval();
                return !_mm_testz_si128(b.native(), a.native());
            }

            template <unsigned N, template <unsigned, typename> class V, class V1, class V2>
            inline bool e_test_bits_any(const any_vec<16, V<N, expr_bit_andnot<V1, V2>>> &e) {
                uint8<16> a, b;
                a = e.wrapped().e.a.eval();
                b = e.wrapped().e.b.eval();
                return !_mm_testc_si128(b.native(), a.native());
            }
#endif

#if SIMD_USE_AVX2
            template <unsigned N, template <unsigned, typename> class V, class V1, class V2>
            inline bool e_test_bits_any(const any_vec<32, V<N, expr_bit_and<V1, V2>>> &e) {
                uint8<32> a, b;
                a = e.wrapped().e.a.eval();
                b = e.wrapped().e.b.eval();
                return !_mm256_testz_si256(b.native(), a.native());
            }

            template <unsigned N, template <unsigned, typename> class V, class V1, class V2>
            bool e_test_bits_any(const any_vec<32, V<N, expr_bit_andnot<V1, V2>>> &e) {
                uint8<32> a, b;
                a = e.wrapped().e.a.eval();
                b = e.wrapped().e.b.eval();
                return !_mm256_testc_si256(b.native(), a.native());
            }
#endif

#if SIMD_USE_AVX512F
            template <class V1, class V2> inline bool e_test_bits_any(const uint32<16, expr_bit_and<V1, V2>> &e) {
                uint32<16> a, b;
                a = e.wrapped().e.a.eval();
                b = e.wrapped().e.b.eval();
                return _mm512_test_epi64_mask(a.native(), b.native()) != 0;
            }

            template <class V1, class V2> inline bool e_test_bits_any(const uint64<8, expr_bit_and<V1, V2>> &e) {
                uint64<8> a, b;
                a = e.wrapped().e.a.eval();
                b = e.wrapped().e.b.eval();
                return _mm512_test_epi64_mask(a.native(), b.native()) != 0;
            }
#endif


        } // namespace detail
    }     // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
