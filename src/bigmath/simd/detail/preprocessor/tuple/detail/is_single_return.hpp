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
#ifndef SIMD_PREPROCESSOR_TUPLE_DETAIL_IS_SINGLE_RETURN_HPP
#define SIMD_PREPROCESSOR_TUPLE_DETAIL_IS_SINGLE_RETURN_HPP
#
#include <bigmath/simd/detail/preprocessor/config/config.hpp>
#
#/* SIMD_TUPLE_IS_SINGLE_RETURN */
#
#if SIMD_VARIADICS && SIMD_VARIADICS_MSVC
#include <bigmath/simd/detail/preprocessor/control/iif.hpp>
#include <bigmath/simd/detail/preprocessor/facilities/is_1.hpp>
#include <bigmath/simd/detail/preprocessor/tuple/size.hpp>
#define SIMD_TUPLE_IS_SINGLE_RETURN(sr, nsr, tuple)      \
    SIMD_IIF(SIMD_IS_1(SIMD_TUPLE_SIZE(tuple)), sr, nsr) \
    /**/
#endif /* SIMD_VARIADICS && SIMD_VARIADICS_MSVC */
#
#endif /* SIMD_PREPROCESSOR_TUPLE_DETAIL_IS_SINGLE_RETURN_HPP */
