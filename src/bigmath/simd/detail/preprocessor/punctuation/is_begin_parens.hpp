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

#ifndef SIMD_PREPROCESSOR_IS_BEGIN_PARENS_HPP
#define SIMD_PREPROCESSOR_IS_BEGIN_PARENS_HPP

#include <bigmath/simd/detail/preprocessor/config/config.hpp>

#if SIMD_VARIADICS

#include <bigmath/simd/detail/preprocessor/punctuation/detail/is_begin_parens.hpp>

#if SIMD_VARIADICS_MSVC && _MSC_VER <= 1400

#define SIMD_IS_BEGIN_PARENS(param)                                                                                    \
    SIMD_DETAIL_IBP_SPLIT(0, SIMD_DETAIL_IBP_CAT(SIMD_DETAIL_IBP_IS_VARIADIC_R_, SIMD_DETAIL_IBP_IS_VARIADIC_C param)) \
    /**/

#else

#define SIMD_IS_BEGIN_PARENS(...)                                                                          \
    SIMD_DETAIL_IBP_SPLIT(                                                                                 \
        0, SIMD_DETAIL_IBP_CAT(SIMD_DETAIL_IBP_IS_VARIADIC_R_, SIMD_DETAIL_IBP_IS_VARIADIC_C __VA_ARGS__)) \
    /**/

#endif /* SIMD_VARIADICS_MSVC && _MSC_VER <= 1400 */
#endif /* SIMD_VARIADICS */
#endif /* SIMD_PREPROCESSOR_IS_BEGIN_PARENS_HPP */
