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

#ifndef SIMD_H
#define SIMD_H

/* The following file sets up the preprocessor variables and includes the
   required system headers for the specific architecture
*/
#include <bigmath/simd/setup_arch.h>

#include <cstdlib>


#include <bigmath/simd/core/align.h>
#include <bigmath/simd/core/aligned_allocator.h>
#include <bigmath/simd/core/bit_and.h>
#include <bigmath/simd/core/bit_andnot.h>
#include <bigmath/simd/core/bit_not.h>
#include <bigmath/simd/core/bit_or.h>
#include <bigmath/simd/core/bit_xor.h>
#include <bigmath/simd/core/blend.h>
#include <bigmath/simd/core/cache.h>
#include <bigmath/simd/core/cast.h>
#include <bigmath/simd/core/cmp_eq.h>
#include <bigmath/simd/core/cmp_ge.h>
#include <bigmath/simd/core/cmp_gt.h>
#include <bigmath/simd/core/cmp_le.h>
#include <bigmath/simd/core/cmp_lt.h>
#include <bigmath/simd/core/cmp_neq.h>
#include <bigmath/simd/core/extract.h>
#include <bigmath/simd/core/extract_bits.h>
#include <bigmath/simd/core/f_abs.h>
#include <bigmath/simd/core/f_add.h>
#include <bigmath/simd/core/f_ceil.h>
#include <bigmath/simd/core/f_div.h>
#include <bigmath/simd/core/f_floor.h>
#include <bigmath/simd/core/f_fmadd.h>
#include <bigmath/simd/core/f_fmsub.h>
#include <bigmath/simd/core/f_isnan.h>
#include <bigmath/simd/core/f_isnan2.h>
#include <bigmath/simd/core/f_max.h>
#include <bigmath/simd/core/f_min.h>
#include <bigmath/simd/core/f_mul.h>
#include <bigmath/simd/core/f_neg.h>
#include <bigmath/simd/core/f_reduce_add.h>
#include <bigmath/simd/core/f_reduce_max.h>
#include <bigmath/simd/core/f_reduce_min.h>
#include <bigmath/simd/core/f_reduce_mul.h>
#include <bigmath/simd/core/f_rcp_e.h>
#include <bigmath/simd/core/f_rcp_rh.h>
#include <bigmath/simd/core/f_rsqrt_e.h>
#include <bigmath/simd/core/f_rsqrt_rh.h>
#include <bigmath/simd/core/f_sign.h>
#include <bigmath/simd/core/f_sqrt.h>
#include <bigmath/simd/core/f_sub.h>
#include <bigmath/simd/core/f_trunc.h>
#include <bigmath/simd/core/for_each.h>
#include <bigmath/simd/core/i_abs.h>
#include <bigmath/simd/core/i_add.h>
#include <bigmath/simd/core/i_add_sat.h>
#include <bigmath/simd/core/i_avg.h>
#include <bigmath/simd/core/i_avg_trunc.h>
#include <bigmath/simd/core/i_div_p.h>
#include <bigmath/simd/core/i_max.h>
#include <bigmath/simd/core/i_min.h>
#include <bigmath/simd/core/i_mul.h>
#include <bigmath/simd/core/i_mull.h>
#include <bigmath/simd/core/i_neg.h>
#include <bigmath/simd/core/i_popcnt.h>
#include <bigmath/simd/core/i_reduce_add.h>
#include <bigmath/simd/core/i_reduce_and.h>
#include <bigmath/simd/core/i_reduce_max.h>
#include <bigmath/simd/core/i_reduce_min.h>
#include <bigmath/simd/core/i_reduce_mul.h>
#include <bigmath/simd/core/i_reduce_or.h>
#include <bigmath/simd/core/i_reduce_popcnt.h>
#include <bigmath/simd/core/i_shift_l.h>
#include <bigmath/simd/core/i_shift_r.h>
#include <bigmath/simd/core/i_sub.h>
#include <bigmath/simd/core/i_sub_sat.h>
#include <bigmath/simd/core/insert.h>
#include <bigmath/simd/core/load.h>
#include <bigmath/simd/core/load_packed2.h>
#include <bigmath/simd/core/load_packed3.h>
#include <bigmath/simd/core/load_packed4.h>
#include <bigmath/simd/core/load_splat.h>
#include <bigmath/simd/core/load_u.h>
#include <bigmath/simd/core/make_float.h>
#include <bigmath/simd/core/make_int.h>
#include <bigmath/simd/core/make_uint.h>
#include <bigmath/simd/core/make_shuffle_bytes_mask.h>
#include <bigmath/simd/core/move_l.h>
#include <bigmath/simd/core/move_r.h>
#include <bigmath/simd/core/permute2.h>
#include <bigmath/simd/core/permute4.h>
#include <bigmath/simd/core/permute_bytes16.h>
#include <bigmath/simd/core/permute_zbytes16.h>
#include <bigmath/simd/core/set_splat.h>
#include <bigmath/simd/core/shuffle1.h>
#include <bigmath/simd/core/shuffle2.h>
#include <bigmath/simd/core/shuffle4x2.h>
#include <bigmath/simd/core/shuffle_bytes16.h>
#include <bigmath/simd/core/shuffle_zbytes16.h>
#include <bigmath/simd/core/splat.h>
#include <bigmath/simd/core/splat_n.h>
#include <bigmath/simd/core/store_first.h>
#include <bigmath/simd/core/store.h>
#include <bigmath/simd/core/store_last.h>
#include <bigmath/simd/core/store_masked.h>
#include <bigmath/simd/core/store_packed2.h>
#include <bigmath/simd/core/store_packed3.h>
#include <bigmath/simd/core/store_packed4.h>
#include <bigmath/simd/core/store_u.h>
#include <bigmath/simd/core/stream.h>
#include <bigmath/simd/core/test_bits.h>
#include <bigmath/simd/core/to_float32.h>
#include <bigmath/simd/core/to_float64.h>
#include <bigmath/simd/core/to_int16.h>
#include <bigmath/simd/core/to_int32.h>
#include <bigmath/simd/core/to_int64.h>
#include <bigmath/simd/core/to_int8.h>
#include <bigmath/simd/core/to_mask.h>
#include <bigmath/simd/core/transpose.h>
#include <bigmath/simd/core/unzip_hi.h>
#include <bigmath/simd/core/unzip_lo.h>
#include <bigmath/simd/core/zip_hi.h>
#include <bigmath/simd/core/zip_lo.h>
#include <bigmath/simd/detail/cast.h>
#include <bigmath/simd/detail/cast.inl>
#include <bigmath/simd/detail/insn/conv_to_mask.inl>

#include <bigmath/simd/detail/altivec/load1.h>

#include <bigmath/simd/detail/neon/math_int.h>
#include <bigmath/simd/detail/neon/memory_store.h>
#include <bigmath/simd/detail/neon/shuffle.h>

#include <bigmath/simd/detail/null/bitwise.h>
#include <bigmath/simd/detail/null/compare.h>
#include <bigmath/simd/detail/null/mask.h>
#include <bigmath/simd/detail/null/math.h>
#include <bigmath/simd/detail/null/memory.h>
#include <bigmath/simd/detail/null/set.h>
#include <bigmath/simd/detail/null/shuffle.h>
#include <bigmath/simd/detail/null/transpose.h>

#include <bigmath/simd/detail/extract128.h>

#include <bigmath/simd/types.h>
#include <bigmath/simd/types/generic.h>
#include <bigmath/simd/types/empty_expr.h>
#include <bigmath/simd/types/float32.h>
#include <bigmath/simd/types/float32x4.h>
#include <bigmath/simd/types/float32x8.h>
#include <bigmath/simd/types/float64.h>
#include <bigmath/simd/types/float64x2.h>
#include <bigmath/simd/types/float64x4.h>
#include <bigmath/simd/types/fwd.h>
#include <bigmath/simd/types/int16.h>
#include <bigmath/simd/types/int16x16.h>
#include <bigmath/simd/types/int16x8.h>
#include <bigmath/simd/types/int32.h>
#include <bigmath/simd/types/int32x4.h>
#include <bigmath/simd/types/int32x8.h>
#include <bigmath/simd/types/int64.h>
#include <bigmath/simd/types/int64x2.h>
#include <bigmath/simd/types/int64x4.h>
#include <bigmath/simd/types/int8.h>
#include <bigmath/simd/types/int8x16.h>
#include <bigmath/simd/types/int8x32.h>
#include <bigmath/simd/types/traits.h>
#include <bigmath/simd/expr.inl>

#include <bigmath/simd/operators/bit_and.h>
#include <bigmath/simd/operators/bit_or.h>
#include <bigmath/simd/operators/bit_xor.h>
#include <bigmath/simd/operators/bit_not.h>
#include <bigmath/simd/operators/cmp_eq.h>
#include <bigmath/simd/operators/cmp_neq.h>
#include <bigmath/simd/operators/cmp_ge.h>
#include <bigmath/simd/operators/cmp_gt.h>
#include <bigmath/simd/operators/cmp_le.h>
#include <bigmath/simd/operators/cmp_lt.h>
#include <bigmath/simd/operators/f_add.h>
#include <bigmath/simd/operators/f_div.h>
#include <bigmath/simd/operators/f_mul.h>
#include <bigmath/simd/operators/f_sub.h>
#include <bigmath/simd/operators/i_add.h>
#include <bigmath/simd/operators/i_mul.h>
#include <bigmath/simd/operators/i_shift_l.h>
#include <bigmath/simd/operators/i_shift_r.h>
#include <bigmath/simd/operators/i_sub.h>

/** @def SIMD_NO_DISPATCHER
    Disables internal dispatching functionality. If the internal dispathcher
    mechanism is not needed, the user can define the @c SIMD_NO_DISPATCHER.
*/
#ifndef SIMD_NO_DISPATCHER
#include <bigmath/simd/dispatch/dispatcher.h>
#include <bigmath/simd/dispatch/make_dispatcher.h>
#endif

#include <bigmath/simd/capabilities.h>

namespace simd {
    using namespace SIMD_ARCH_NAMESPACE;
    namespace detail {
        using namespace ::simd::SIMD_ARCH_NAMESPACE::detail;
    } // namespace detail
} // namespace simd

#endif
