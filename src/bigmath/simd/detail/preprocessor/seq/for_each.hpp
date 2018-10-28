/**********************************************************************
 * BIGMATH INSIGHT CONFIDENTIAL
 *
 * Copyright (C) 2016-2018 BIGMATH CORPORATION, All Rights Reserved.
 *
 * @Author: Simon Zhang on 19 Oct 2018
 * @EMail: simon.zhangsm@hotmail.com
 * @Version: $BIGMATH_SIMD_LIB_VERSION
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
#ifndef SIMD_PREPROCESSOR_SEQ_FOR_EACH_HPP
#define SIMD_PREPROCESSOR_SEQ_FOR_EACH_HPP
#
#include <bigmath/simd/detail/preprocessor/arithmetic/dec.hpp>
#include <bigmath/simd/detail/preprocessor/config/config.hpp>
#include <bigmath/simd/detail/preprocessor/control/if.hpp>
#include <bigmath/simd/detail/preprocessor/control/iif.hpp>
#include <bigmath/simd/detail/preprocessor/repetition/for.hpp>
#include <bigmath/simd/detail/preprocessor/seq/seq.hpp>
#include <bigmath/simd/detail/preprocessor/seq/size.hpp>
#include <bigmath/simd/detail/preprocessor/seq/detail/is_empty.hpp>
#include <bigmath/simd/detail/preprocessor/tuple/elem.hpp>
#include <bigmath/simd/detail/preprocessor/tuple/rem.hpp>
#
#/* SIMD_SEQ_FOR_EACH */
#
#if ~SIMD_CONFIG_FLAGS() & SIMD_CONFIG_EDG()
#define SIMD_SEQ_FOR_EACH(macro, data, seq) SIMD_SEQ_FOR_EACH_DETAIL_CHECK(macro, data, seq)
#else
#define SIMD_SEQ_FOR_EACH(macro, data, seq) SIMD_SEQ_FOR_EACH_D(macro, data, seq)
#define SIMD_SEQ_FOR_EACH_D(macro, data, seq) SIMD_SEQ_FOR_EACH_DETAIL_CHECK(macro, data, seq)
#endif
#
#define SIMD_SEQ_FOR_EACH_DETAIL_CHECK_EXEC(macro, data, seq) \
    SIMD_FOR((macro, data, seq, SIMD_SEQ_SIZE(seq)), SIMD_SEQ_FOR_EACH_P, SIMD_SEQ_FOR_EACH_O, SIMD_SEQ_FOR_EACH_M)
#define SIMD_SEQ_FOR_EACH_DETAIL_CHECK_EMPTY(macro, data, seq)
#
#define SIMD_SEQ_FOR_EACH_DETAIL_CHECK(macro, data, seq) \
    SIMD_IIF(SIMD_SEQ_DETAIL_IS_NOT_EMPTY(seq),          \
             SIMD_SEQ_FOR_EACH_DETAIL_CHECK_EXEC,        \
             SIMD_SEQ_FOR_EACH_DETAIL_CHECK_EMPTY)       \
    (macro, data, seq) /**/
#
#define SIMD_SEQ_FOR_EACH_P(r, x) SIMD_TUPLE_ELEM(4, 3, x)
#
#if SIMD_CONFIG_FLAGS() & SIMD_CONFIG_STRICT()
#define SIMD_SEQ_FOR_EACH_O(r, x) SIMD_SEQ_FOR_EACH_O_I x
#else
#define SIMD_SEQ_FOR_EACH_O(r, x) \
    SIMD_SEQ_FOR_EACH_O_I(        \
        SIMD_TUPLE_ELEM(4, 0, x), SIMD_TUPLE_ELEM(4, 1, x), SIMD_TUPLE_ELEM(4, 2, x), SIMD_TUPLE_ELEM(4, 3, x))
#endif
#
#define SIMD_SEQ_FOR_EACH_O_I(macro, data, seq, sz)           \
    SIMD_SEQ_FOR_EACH_O_I_DEC(macro, data, seq, SIMD_DEC(sz)) \
/**/
#define SIMD_SEQ_FOR_EACH_O_I_DEC(macro, data, seq, sz) \
    (macro, data, SIMD_IF(sz, SIMD_SEQ_FOR_EACH_O_I_TAIL, SIMD_SEQ_FOR_EACH_O_I_NIL)(seq), sz) /**/
#define SIMD_SEQ_FOR_EACH_O_I_TAIL(seq) SIMD_SEQ_TAIL(seq)
#define SIMD_SEQ_FOR_EACH_O_I_NIL(seq) SIMD_NIL
#
#if SIMD_CONFIG_FLAGS() & SIMD_CONFIG_STRICT()
#define SIMD_SEQ_FOR_EACH_M(r, x) SIMD_SEQ_FOR_EACH_M_IM(r, SIMD_TUPLE_REM_4 x)
#define SIMD_SEQ_FOR_EACH_M_IM(r, im) SIMD_SEQ_FOR_EACH_M_I(r, im)
#else
#define SIMD_SEQ_FOR_EACH_M(r, x) \
    SIMD_SEQ_FOR_EACH_M_I(        \
        r, SIMD_TUPLE_ELEM(4, 0, x), SIMD_TUPLE_ELEM(4, 1, x), SIMD_TUPLE_ELEM(4, 2, x), SIMD_TUPLE_ELEM(4, 3, x))
#endif
#
#define SIMD_SEQ_FOR_EACH_M_I(r, macro, data, seq, sz) macro(r, data, SIMD_SEQ_HEAD(seq))
#
#/* SIMD_SEQ_FOR_EACH_R */
#
#if ~SIMD_CONFIG_FLAGS() & SIMD_CONFIG_EDG()
#define SIMD_SEQ_FOR_EACH_R(r, macro, data, seq) SIMD_SEQ_FOR_EACH_DETAIL_CHECK_R(r, macro, data, seq)
#else
#define SIMD_SEQ_FOR_EACH_R(r, macro, data, seq) SIMD_SEQ_FOR_EACH_R_I(r, macro, data, seq)
#define SIMD_SEQ_FOR_EACH_R_I(r, macro, data, seq) SIMD_SEQ_FOR_EACH_DETAIL_CHECK_R(r, macro, data, seq)
#endif
#
#define SIMD_SEQ_FOR_EACH_DETAIL_CHECK_EXEC_R(r, macro, data, seq) \
    SIMD_FOR_##r((macro, data, seq, SIMD_SEQ_SIZE(seq)), SIMD_SEQ_FOR_EACH_P, SIMD_SEQ_FOR_EACH_O, SIMD_SEQ_FOR_EACH_M)
#define SIMD_SEQ_FOR_EACH_DETAIL_CHECK_EMPTY_R(r, macro, data, seq)
#
#define SIMD_SEQ_FOR_EACH_DETAIL_CHECK_R(r, macro, data, seq) \
    SIMD_IIF(SIMD_SEQ_DETAIL_IS_NOT_EMPTY(seq),               \
             SIMD_SEQ_FOR_EACH_DETAIL_CHECK_EXEC_R,           \
             SIMD_SEQ_FOR_EACH_DETAIL_CHECK_EMPTY_R)          \
    (r, macro, data, seq) /**/
#
#endif
