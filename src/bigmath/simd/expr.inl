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

#ifndef SIMD_TYPES_GENERIC_INL
#define SIMD_TYPES_GENERIC_INL

#include <bigmath/simd/setup_arch.h>
#include <bigmath/simd/expr.h>
#include <bigmath/simd/detail/expr/bit_and.h>
#include <bigmath/simd/detail/expr/bit_andnot.h>
#include <bigmath/simd/detail/expr/bit_not.h>
#include <bigmath/simd/detail/expr/bit_or.h>
#include <bigmath/simd/detail/expr/blend.h>
#include <bigmath/simd/detail/expr/f_abs.h>
#include <bigmath/simd/detail/expr/f_add.h>
#include <bigmath/simd/detail/expr/f_fmadd.h>
#include <bigmath/simd/detail/expr/f_fmsub.h>
#include <bigmath/simd/detail/expr/f_mul.h>
#include <bigmath/simd/detail/expr/f_neg.h>
#include <bigmath/simd/detail/expr/f_sub.h>
#include <bigmath/simd/detail/expr/i_abs.h>
#include <bigmath/simd/detail/expr/i_add.h>
#include <bigmath/simd/detail/expr/i_add_sat.h>
#include <bigmath/simd/detail/expr/i_mul.h>
#include <bigmath/simd/detail/expr/i_mull.h>
#include <bigmath/simd/detail/expr/i_neg.h>
#include <bigmath/simd/detail/expr/i_sub.h>
#include <bigmath/simd/detail/expr/i_sub_sat.h>
#include <bigmath/simd/detail/expr/scalar.h>
#include <bigmath/simd/detail/expr/splat_n.h>
#include <bigmath/simd/detail/expr/test_bits.h>
#include <bigmath/simd/detail/expr/vec.h>

namespace simd {
namespace SIMD_ARCH_NAMESPACE {
namespace detail {

template<class R, class E> struct expr_eval_wrapper {
static inline R eval(const E& e) { return expr_eval<R, E>::eval(e); }
};

} // namespace detail
} // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
