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
#ifndef SIMD_PREPROCESSOR_FACILITIES_IS_EMPTY_HPP
#define SIMD_PREPROCESSOR_FACILITIES_IS_EMPTY_HPP
#
#include <bigmath/simd/detail/preprocessor/config/config.hpp>
#
#if SIMD_VARIADICS
#
#include <bigmath/simd/detail/preprocessor/facilities/is_empty_variadic.hpp>
#
#else
#
#if ~SIMD_CONFIG_FLAGS() & SIMD_CONFIG_MSVC() && ~SIMD_CONFIG_FLAGS() & SIMD_CONFIG_MWCC()
#include <bigmath/simd/detail/preprocessor/tuple/elem.hpp>
#include <bigmath/simd/detail/preprocessor/facilities/identity.hpp>
#else
#include <bigmath/simd/detail/preprocessor/cat.hpp>
#include <bigmath/simd/detail/preprocessor/detail/split.hpp>
#endif
#
#/* SIMD_IS_EMPTY */
#
#if ~SIMD_CONFIG_FLAGS() & SIMD_CONFIG_MSVC() && ~SIMD_CONFIG_FLAGS() & SIMD_CONFIG_MWCC()
#define SIMD_IS_EMPTY(x) SIMD_IS_EMPTY_I(x SIMD_IS_EMPTY_HELPER)
#define SIMD_IS_EMPTY_I(contents) SIMD_TUPLE_ELEM(2, 1, (SIMD_IS_EMPTY_DEF_##contents()))
#define SIMD_IS_EMPTY_DEF_SIMD_IS_EMPTY_HELPER 1, SIMD_IDENTITY(1)
#define SIMD_IS_EMPTY_HELPER() , 0
#else
#if SIMD_CONFIG_FLAGS() & SIMD_CONFIG_MSVC()
#define SIMD_IS_EMPTY(x) SIMD_IS_EMPTY_I(SIMD_IS_EMPTY_HELPER x())
#define SIMD_IS_EMPTY_I(test) SIMD_IS_EMPTY_II(SIMD_SPLIT(0, SIMD_CAT(SIMD_IS_EMPTY_DEF_, test)))
#define SIMD_IS_EMPTY_II(id) id
#else
#define SIMD_IS_EMPTY(x) SIMD_IS_EMPTY_I((SIMD_IS_EMPTY_HELPER x()))
#define SIMD_IS_EMPTY_I(par) SIMD_IS_EMPTY_II##par
#define SIMD_IS_EMPTY_II(test) SIMD_SPLIT(0, SIMD_CAT(SIMD_IS_EMPTY_DEF_, test))
#endif
#define SIMD_IS_EMPTY_HELPER() 1
#define SIMD_IS_EMPTY_DEF_1 1, SIMD_NIL
#define SIMD_IS_EMPTY_DEF_SIMD_IS_EMPTY_HELPER 0, SIMD_NIL
#endif
#
#endif /* SIMD_VARIADICS */
#
#endif /* SIMD_PREPROCESSOR_FACILITIES_IS_EMPTY_HPP */
