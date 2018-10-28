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
#ifndef SIMD_PREPROCESSOR_SEQ_DETAIL_IS_EMPTY_HPP
#define SIMD_PREPROCESSOR_SEQ_DETAIL_IS_EMPTY_HPP
#
#include <bigmath/simd/detail/preprocessor/config/config.hpp>
#include <bigmath/simd/detail/preprocessor/arithmetic/dec.hpp>
#include <bigmath/simd/detail/preprocessor/logical/bool.hpp>
#include <bigmath/simd/detail/preprocessor/logical/compl.hpp>
#include <bigmath/simd/detail/preprocessor/seq/size.hpp>
#
/* An empty seq is one that is just SIMD_SEQ_NIL */
#
#define SIMD_SEQ_DETAIL_IS_EMPTY(seq)             \
    SIMD_COMPL(SIMD_SEQ_DETAIL_IS_NOT_EMPTY(seq)) \
/**/
#
#define SIMD_SEQ_DETAIL_IS_EMPTY_SIZE(size)             \
    SIMD_COMPL(SIMD_SEQ_DETAIL_IS_NOT_EMPTY_SIZE(size)) \
/**/
#
#define SIMD_SEQ_DETAIL_IS_NOT_EMPTY(seq)                              \
    SIMD_SEQ_DETAIL_IS_NOT_EMPTY_SIZE(SIMD_SEQ_DETAIL_EMPTY_SIZE(seq)) \
/**/
#
#define SIMD_SEQ_DETAIL_IS_NOT_EMPTY_SIZE(size) \
    SIMD_BOOL(size)                             \
/**/
#
#define SIMD_SEQ_DETAIL_EMPTY_SIZE(seq) \
    SIMD_DEC(SIMD_SEQ_SIZE(seq(nil)))   \
/**/
#
#endif
