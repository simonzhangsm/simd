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
#ifndef SIMD_PREPROCESSOR_DEBUG_ERROR_HPP
#define SIMD_PREPROCESSOR_DEBUG_ERROR_HPP
#
#include <bigmath/simd/detail/preprocessor/cat.hpp>
#include <bigmath/simd/detail/preprocessor/config/config.hpp>
#
#/* SIMD_ERROR */
#
#if SIMD_CONFIG_ERRORS
#define SIMD_ERROR(code) SIMD_CAT(SIMD_ERROR_, code)
#endif
#
#define SIMD_ERROR_0x0000 SIMD_ERROR(0x0000, SIMD_INDEX_OUT_OF_BOUNDS)
#define SIMD_ERROR_0x0001 SIMD_ERROR(0x0001, SIMD_WHILE_OVERFLOW)
#define SIMD_ERROR_0x0002 SIMD_ERROR(0x0002, SIMD_FOR_OVERFLOW)
#define SIMD_ERROR_0x0003 SIMD_ERROR(0x0003, SIMD_REPEAT_OVERFLOW)
#define SIMD_ERROR_0x0004 SIMD_ERROR(0x0004, SIMD_LIST_FOLD_OVERFLOW)
#define SIMD_ERROR_0x0005 SIMD_ERROR(0x0005, SIMD_SEQ_FOLD_OVERFLOW)
#define SIMD_ERROR_0x0006 SIMD_ERROR(0x0006, SIMD_ARITHMETIC_OVERFLOW)
#define SIMD_ERROR_0x0007 SIMD_ERROR(0x0007, SIMD_DIVISION_BY_ZERO)
#
#endif
