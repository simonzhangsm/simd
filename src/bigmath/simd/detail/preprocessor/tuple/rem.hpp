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
#ifndef SIMD_PREPROCESSOR_TUPLE_REM_HPP
#define SIMD_PREPROCESSOR_TUPLE_REM_HPP
#
#include <bigmath/simd/detail/preprocessor/cat.hpp>
#include <bigmath/simd/detail/preprocessor/config/config.hpp>
#include <bigmath/simd/detail/preprocessor/facilities/expand.hpp>
#include <bigmath/simd/detail/preprocessor/facilities/overload.hpp>
#include <bigmath/simd/detail/preprocessor/tuple/detail/is_single_return.hpp>
#
#/* SIMD_REM */
#
#if SIMD_VARIADICS
#if SIMD_VARIADICS_MSVC
/* To be used internally when __VA_ARGS__ could be empty ( or is a single element ) */
#define SIMD_REM_CAT(...) SIMD_CAT(__VA_ARGS__, )
#endif
#define SIMD_REM(...) __VA_ARGS__
#else
#define SIMD_REM(x) x
#endif
#
#/* SIMD_TUPLE_REM */
#
/*
  VC++8.0 cannot handle the variadic version of SIMD_TUPLE_REM(size)
*/
#if SIMD_VARIADICS && !(SIMD_VARIADICS_MSVC && _MSC_VER <= 1400)
#if SIMD_VARIADICS_MSVC
/* To be used internally when the size could be 0 ( or 1 ) */
#define SIMD_TUPLE_REM_CAT(size) SIMD_REM_CAT
#endif
#define SIMD_TUPLE_REM(size) SIMD_REM
#else
#if ~SIMD_CONFIG_FLAGS() & SIMD_CONFIG_MWCC()
#define SIMD_TUPLE_REM(size) SIMD_TUPLE_REM_I(size)
#else
#define SIMD_TUPLE_REM(size) SIMD_TUPLE_REM_OO((size))
#define SIMD_TUPLE_REM_OO(par) SIMD_TUPLE_REM_I##par
#endif
#define SIMD_TUPLE_REM_I(size) SIMD_TUPLE_REM_##size
#endif
#define SIMD_TUPLE_REM_0()
#define SIMD_TUPLE_REM_1(e0) e0
#define SIMD_TUPLE_REM_2(e0, e1) e0, e1
#define SIMD_TUPLE_REM_3(e0, e1, e2) e0, e1, e2
#define SIMD_TUPLE_REM_4(e0, e1, e2, e3) e0, e1, e2, e3
#define SIMD_TUPLE_REM_5(e0, e1, e2, e3, e4) e0, e1, e2, e3, e4
#define SIMD_TUPLE_REM_6(e0, e1, e2, e3, e4, e5) e0, e1, e2, e3, e4, e5
#define SIMD_TUPLE_REM_7(e0, e1, e2, e3, e4, e5, e6) e0, e1, e2, e3, e4, e5, e6
#define SIMD_TUPLE_REM_8(e0, e1, e2, e3, e4, e5, e6, e7) e0, e1, e2, e3, e4, e5, e6, e7
#define SIMD_TUPLE_REM_9(e0, e1, e2, e3, e4, e5, e6, e7, e8) e0, e1, e2, e3, e4, e5, e6, e7, e8
#define SIMD_TUPLE_REM_10(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9) e0, e1, e2, e3, e4, e5, e6, e7, e8, e9
#define SIMD_TUPLE_REM_11(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10) e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10
#define SIMD_TUPLE_REM_12(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11) \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11
#define SIMD_TUPLE_REM_13(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12) \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12
#define SIMD_TUPLE_REM_14(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13) \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13
#define SIMD_TUPLE_REM_15(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14) \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14
#define SIMD_TUPLE_REM_16(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15) \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15
#define SIMD_TUPLE_REM_17(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16) \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16
#define SIMD_TUPLE_REM_18(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17) \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17
#define SIMD_TUPLE_REM_19(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18) \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18
#define SIMD_TUPLE_REM_20(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19) \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19
#define SIMD_TUPLE_REM_21(                                                                         \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20) \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20
#define SIMD_TUPLE_REM_22(                                                                              \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21) \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21
#define SIMD_TUPLE_REM_23(                                                                                   \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22) \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22
#define SIMD_TUPLE_REM_24(                                                                                        \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23) \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23
#define SIMD_TUPLE_REM_25(                                                                                             \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24) \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24
#define SIMD_TUPLE_REM_26(e0,                                                                                          \
                          e1,                                                                                          \
                          e2,                                                                                          \
                          e3,                                                                                          \
                          e4,                                                                                          \
                          e5,                                                                                          \
                          e6,                                                                                          \
                          e7,                                                                                          \
                          e8,                                                                                          \
                          e9,                                                                                          \
                          e10,                                                                                         \
                          e11,                                                                                         \
                          e12,                                                                                         \
                          e13,                                                                                         \
                          e14,                                                                                         \
                          e15,                                                                                         \
                          e16,                                                                                         \
                          e17,                                                                                         \
                          e18,                                                                                         \
                          e19,                                                                                         \
                          e20,                                                                                         \
                          e21,                                                                                         \
                          e22,                                                                                         \
                          e23,                                                                                         \
                          e24,                                                                                         \
                          e25)                                                                                         \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, \
        e25
#define SIMD_TUPLE_REM_27(e0,                                                                                          \
                          e1,                                                                                          \
                          e2,                                                                                          \
                          e3,                                                                                          \
                          e4,                                                                                          \
                          e5,                                                                                          \
                          e6,                                                                                          \
                          e7,                                                                                          \
                          e8,                                                                                          \
                          e9,                                                                                          \
                          e10,                                                                                         \
                          e11,                                                                                         \
                          e12,                                                                                         \
                          e13,                                                                                         \
                          e14,                                                                                         \
                          e15,                                                                                         \
                          e16,                                                                                         \
                          e17,                                                                                         \
                          e18,                                                                                         \
                          e19,                                                                                         \
                          e20,                                                                                         \
                          e21,                                                                                         \
                          e22,                                                                                         \
                          e23,                                                                                         \
                          e24,                                                                                         \
                          e25,                                                                                         \
                          e26)                                                                                         \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, \
        e25, e26
#define SIMD_TUPLE_REM_28(e0,                                                                                          \
                          e1,                                                                                          \
                          e2,                                                                                          \
                          e3,                                                                                          \
                          e4,                                                                                          \
                          e5,                                                                                          \
                          e6,                                                                                          \
                          e7,                                                                                          \
                          e8,                                                                                          \
                          e9,                                                                                          \
                          e10,                                                                                         \
                          e11,                                                                                         \
                          e12,                                                                                         \
                          e13,                                                                                         \
                          e14,                                                                                         \
                          e15,                                                                                         \
                          e16,                                                                                         \
                          e17,                                                                                         \
                          e18,                                                                                         \
                          e19,                                                                                         \
                          e20,                                                                                         \
                          e21,                                                                                         \
                          e22,                                                                                         \
                          e23,                                                                                         \
                          e24,                                                                                         \
                          e25,                                                                                         \
                          e26,                                                                                         \
                          e27)                                                                                         \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, \
        e25, e26, e27
#define SIMD_TUPLE_REM_29(e0,                                                                                          \
                          e1,                                                                                          \
                          e2,                                                                                          \
                          e3,                                                                                          \
                          e4,                                                                                          \
                          e5,                                                                                          \
                          e6,                                                                                          \
                          e7,                                                                                          \
                          e8,                                                                                          \
                          e9,                                                                                          \
                          e10,                                                                                         \
                          e11,                                                                                         \
                          e12,                                                                                         \
                          e13,                                                                                         \
                          e14,                                                                                         \
                          e15,                                                                                         \
                          e16,                                                                                         \
                          e17,                                                                                         \
                          e18,                                                                                         \
                          e19,                                                                                         \
                          e20,                                                                                         \
                          e21,                                                                                         \
                          e22,                                                                                         \
                          e23,                                                                                         \
                          e24,                                                                                         \
                          e25,                                                                                         \
                          e26,                                                                                         \
                          e27,                                                                                         \
                          e28)                                                                                         \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, \
        e25, e26, e27, e28
#define SIMD_TUPLE_REM_30(e0,                                                                                          \
                          e1,                                                                                          \
                          e2,                                                                                          \
                          e3,                                                                                          \
                          e4,                                                                                          \
                          e5,                                                                                          \
                          e6,                                                                                          \
                          e7,                                                                                          \
                          e8,                                                                                          \
                          e9,                                                                                          \
                          e10,                                                                                         \
                          e11,                                                                                         \
                          e12,                                                                                         \
                          e13,                                                                                         \
                          e14,                                                                                         \
                          e15,                                                                                         \
                          e16,                                                                                         \
                          e17,                                                                                         \
                          e18,                                                                                         \
                          e19,                                                                                         \
                          e20,                                                                                         \
                          e21,                                                                                         \
                          e22,                                                                                         \
                          e23,                                                                                         \
                          e24,                                                                                         \
                          e25,                                                                                         \
                          e26,                                                                                         \
                          e27,                                                                                         \
                          e28,                                                                                         \
                          e29)                                                                                         \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, \
        e25, e26, e27, e28, e29
#define SIMD_TUPLE_REM_31(e0,                                                                                          \
                          e1,                                                                                          \
                          e2,                                                                                          \
                          e3,                                                                                          \
                          e4,                                                                                          \
                          e5,                                                                                          \
                          e6,                                                                                          \
                          e7,                                                                                          \
                          e8,                                                                                          \
                          e9,                                                                                          \
                          e10,                                                                                         \
                          e11,                                                                                         \
                          e12,                                                                                         \
                          e13,                                                                                         \
                          e14,                                                                                         \
                          e15,                                                                                         \
                          e16,                                                                                         \
                          e17,                                                                                         \
                          e18,                                                                                         \
                          e19,                                                                                         \
                          e20,                                                                                         \
                          e21,                                                                                         \
                          e22,                                                                                         \
                          e23,                                                                                         \
                          e24,                                                                                         \
                          e25,                                                                                         \
                          e26,                                                                                         \
                          e27,                                                                                         \
                          e28,                                                                                         \
                          e29,                                                                                         \
                          e30)                                                                                         \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, \
        e25, e26, e27, e28, e29, e30
#define SIMD_TUPLE_REM_32(e0,                                                                                          \
                          e1,                                                                                          \
                          e2,                                                                                          \
                          e3,                                                                                          \
                          e4,                                                                                          \
                          e5,                                                                                          \
                          e6,                                                                                          \
                          e7,                                                                                          \
                          e8,                                                                                          \
                          e9,                                                                                          \
                          e10,                                                                                         \
                          e11,                                                                                         \
                          e12,                                                                                         \
                          e13,                                                                                         \
                          e14,                                                                                         \
                          e15,                                                                                         \
                          e16,                                                                                         \
                          e17,                                                                                         \
                          e18,                                                                                         \
                          e19,                                                                                         \
                          e20,                                                                                         \
                          e21,                                                                                         \
                          e22,                                                                                         \
                          e23,                                                                                         \
                          e24,                                                                                         \
                          e25,                                                                                         \
                          e26,                                                                                         \
                          e27,                                                                                         \
                          e28,                                                                                         \
                          e29,                                                                                         \
                          e30,                                                                                         \
                          e31)                                                                                         \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, \
        e25, e26, e27, e28, e29, e30, e31
#define SIMD_TUPLE_REM_33(e0,                                                                                          \
                          e1,                                                                                          \
                          e2,                                                                                          \
                          e3,                                                                                          \
                          e4,                                                                                          \
                          e5,                                                                                          \
                          e6,                                                                                          \
                          e7,                                                                                          \
                          e8,                                                                                          \
                          e9,                                                                                          \
                          e10,                                                                                         \
                          e11,                                                                                         \
                          e12,                                                                                         \
                          e13,                                                                                         \
                          e14,                                                                                         \
                          e15,                                                                                         \
                          e16,                                                                                         \
                          e17,                                                                                         \
                          e18,                                                                                         \
                          e19,                                                                                         \
                          e20,                                                                                         \
                          e21,                                                                                         \
                          e22,                                                                                         \
                          e23,                                                                                         \
                          e24,                                                                                         \
                          e25,                                                                                         \
                          e26,                                                                                         \
                          e27,                                                                                         \
                          e28,                                                                                         \
                          e29,                                                                                         \
                          e30,                                                                                         \
                          e31,                                                                                         \
                          e32)                                                                                         \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, \
        e25, e26, e27, e28, e29, e30, e31, e32
#define SIMD_TUPLE_REM_34(e0,                                                                                          \
                          e1,                                                                                          \
                          e2,                                                                                          \
                          e3,                                                                                          \
                          e4,                                                                                          \
                          e5,                                                                                          \
                          e6,                                                                                          \
                          e7,                                                                                          \
                          e8,                                                                                          \
                          e9,                                                                                          \
                          e10,                                                                                         \
                          e11,                                                                                         \
                          e12,                                                                                         \
                          e13,                                                                                         \
                          e14,                                                                                         \
                          e15,                                                                                         \
                          e16,                                                                                         \
                          e17,                                                                                         \
                          e18,                                                                                         \
                          e19,                                                                                         \
                          e20,                                                                                         \
                          e21,                                                                                         \
                          e22,                                                                                         \
                          e23,                                                                                         \
                          e24,                                                                                         \
                          e25,                                                                                         \
                          e26,                                                                                         \
                          e27,                                                                                         \
                          e28,                                                                                         \
                          e29,                                                                                         \
                          e30,                                                                                         \
                          e31,                                                                                         \
                          e32,                                                                                         \
                          e33)                                                                                         \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, \
        e25, e26, e27, e28, e29, e30, e31, e32, e33
#define SIMD_TUPLE_REM_35(e0,                                                                                          \
                          e1,                                                                                          \
                          e2,                                                                                          \
                          e3,                                                                                          \
                          e4,                                                                                          \
                          e5,                                                                                          \
                          e6,                                                                                          \
                          e7,                                                                                          \
                          e8,                                                                                          \
                          e9,                                                                                          \
                          e10,                                                                                         \
                          e11,                                                                                         \
                          e12,                                                                                         \
                          e13,                                                                                         \
                          e14,                                                                                         \
                          e15,                                                                                         \
                          e16,                                                                                         \
                          e17,                                                                                         \
                          e18,                                                                                         \
                          e19,                                                                                         \
                          e20,                                                                                         \
                          e21,                                                                                         \
                          e22,                                                                                         \
                          e23,                                                                                         \
                          e24,                                                                                         \
                          e25,                                                                                         \
                          e26,                                                                                         \
                          e27,                                                                                         \
                          e28,                                                                                         \
                          e29,                                                                                         \
                          e30,                                                                                         \
                          e31,                                                                                         \
                          e32,                                                                                         \
                          e33,                                                                                         \
                          e34)                                                                                         \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, \
        e25, e26, e27, e28, e29, e30, e31, e32, e33, e34
#define SIMD_TUPLE_REM_36(e0,                                                                                          \
                          e1,                                                                                          \
                          e2,                                                                                          \
                          e3,                                                                                          \
                          e4,                                                                                          \
                          e5,                                                                                          \
                          e6,                                                                                          \
                          e7,                                                                                          \
                          e8,                                                                                          \
                          e9,                                                                                          \
                          e10,                                                                                         \
                          e11,                                                                                         \
                          e12,                                                                                         \
                          e13,                                                                                         \
                          e14,                                                                                         \
                          e15,                                                                                         \
                          e16,                                                                                         \
                          e17,                                                                                         \
                          e18,                                                                                         \
                          e19,                                                                                         \
                          e20,                                                                                         \
                          e21,                                                                                         \
                          e22,                                                                                         \
                          e23,                                                                                         \
                          e24,                                                                                         \
                          e25,                                                                                         \
                          e26,                                                                                         \
                          e27,                                                                                         \
                          e28,                                                                                         \
                          e29,                                                                                         \
                          e30,                                                                                         \
                          e31,                                                                                         \
                          e32,                                                                                         \
                          e33,                                                                                         \
                          e34,                                                                                         \
                          e35)                                                                                         \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, \
        e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35
#define SIMD_TUPLE_REM_37(e0,                                                                                          \
                          e1,                                                                                          \
                          e2,                                                                                          \
                          e3,                                                                                          \
                          e4,                                                                                          \
                          e5,                                                                                          \
                          e6,                                                                                          \
                          e7,                                                                                          \
                          e8,                                                                                          \
                          e9,                                                                                          \
                          e10,                                                                                         \
                          e11,                                                                                         \
                          e12,                                                                                         \
                          e13,                                                                                         \
                          e14,                                                                                         \
                          e15,                                                                                         \
                          e16,                                                                                         \
                          e17,                                                                                         \
                          e18,                                                                                         \
                          e19,                                                                                         \
                          e20,                                                                                         \
                          e21,                                                                                         \
                          e22,                                                                                         \
                          e23,                                                                                         \
                          e24,                                                                                         \
                          e25,                                                                                         \
                          e26,                                                                                         \
                          e27,                                                                                         \
                          e28,                                                                                         \
                          e29,                                                                                         \
                          e30,                                                                                         \
                          e31,                                                                                         \
                          e32,                                                                                         \
                          e33,                                                                                         \
                          e34,                                                                                         \
                          e35,                                                                                         \
                          e36)                                                                                         \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, \
        e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36
#define SIMD_TUPLE_REM_38(e0,                                                                                          \
                          e1,                                                                                          \
                          e2,                                                                                          \
                          e3,                                                                                          \
                          e4,                                                                                          \
                          e5,                                                                                          \
                          e6,                                                                                          \
                          e7,                                                                                          \
                          e8,                                                                                          \
                          e9,                                                                                          \
                          e10,                                                                                         \
                          e11,                                                                                         \
                          e12,                                                                                         \
                          e13,                                                                                         \
                          e14,                                                                                         \
                          e15,                                                                                         \
                          e16,                                                                                         \
                          e17,                                                                                         \
                          e18,                                                                                         \
                          e19,                                                                                         \
                          e20,                                                                                         \
                          e21,                                                                                         \
                          e22,                                                                                         \
                          e23,                                                                                         \
                          e24,                                                                                         \
                          e25,                                                                                         \
                          e26,                                                                                         \
                          e27,                                                                                         \
                          e28,                                                                                         \
                          e29,                                                                                         \
                          e30,                                                                                         \
                          e31,                                                                                         \
                          e32,                                                                                         \
                          e33,                                                                                         \
                          e34,                                                                                         \
                          e35,                                                                                         \
                          e36,                                                                                         \
                          e37)                                                                                         \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, \
        e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37
#define SIMD_TUPLE_REM_39(e0,                                                                                          \
                          e1,                                                                                          \
                          e2,                                                                                          \
                          e3,                                                                                          \
                          e4,                                                                                          \
                          e5,                                                                                          \
                          e6,                                                                                          \
                          e7,                                                                                          \
                          e8,                                                                                          \
                          e9,                                                                                          \
                          e10,                                                                                         \
                          e11,                                                                                         \
                          e12,                                                                                         \
                          e13,                                                                                         \
                          e14,                                                                                         \
                          e15,                                                                                         \
                          e16,                                                                                         \
                          e17,                                                                                         \
                          e18,                                                                                         \
                          e19,                                                                                         \
                          e20,                                                                                         \
                          e21,                                                                                         \
                          e22,                                                                                         \
                          e23,                                                                                         \
                          e24,                                                                                         \
                          e25,                                                                                         \
                          e26,                                                                                         \
                          e27,                                                                                         \
                          e28,                                                                                         \
                          e29,                                                                                         \
                          e30,                                                                                         \
                          e31,                                                                                         \
                          e32,                                                                                         \
                          e33,                                                                                         \
                          e34,                                                                                         \
                          e35,                                                                                         \
                          e36,                                                                                         \
                          e37,                                                                                         \
                          e38)                                                                                         \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, \
        e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38
#define SIMD_TUPLE_REM_40(e0,                                                                                          \
                          e1,                                                                                          \
                          e2,                                                                                          \
                          e3,                                                                                          \
                          e4,                                                                                          \
                          e5,                                                                                          \
                          e6,                                                                                          \
                          e7,                                                                                          \
                          e8,                                                                                          \
                          e9,                                                                                          \
                          e10,                                                                                         \
                          e11,                                                                                         \
                          e12,                                                                                         \
                          e13,                                                                                         \
                          e14,                                                                                         \
                          e15,                                                                                         \
                          e16,                                                                                         \
                          e17,                                                                                         \
                          e18,                                                                                         \
                          e19,                                                                                         \
                          e20,                                                                                         \
                          e21,                                                                                         \
                          e22,                                                                                         \
                          e23,                                                                                         \
                          e24,                                                                                         \
                          e25,                                                                                         \
                          e26,                                                                                         \
                          e27,                                                                                         \
                          e28,                                                                                         \
                          e29,                                                                                         \
                          e30,                                                                                         \
                          e31,                                                                                         \
                          e32,                                                                                         \
                          e33,                                                                                         \
                          e34,                                                                                         \
                          e35,                                                                                         \
                          e36,                                                                                         \
                          e37,                                                                                         \
                          e38,                                                                                         \
                          e39)                                                                                         \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, \
        e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39
#define SIMD_TUPLE_REM_41(e0,                                                                                          \
                          e1,                                                                                          \
                          e2,                                                                                          \
                          e3,                                                                                          \
                          e4,                                                                                          \
                          e5,                                                                                          \
                          e6,                                                                                          \
                          e7,                                                                                          \
                          e8,                                                                                          \
                          e9,                                                                                          \
                          e10,                                                                                         \
                          e11,                                                                                         \
                          e12,                                                                                         \
                          e13,                                                                                         \
                          e14,                                                                                         \
                          e15,                                                                                         \
                          e16,                                                                                         \
                          e17,                                                                                         \
                          e18,                                                                                         \
                          e19,                                                                                         \
                          e20,                                                                                         \
                          e21,                                                                                         \
                          e22,                                                                                         \
                          e23,                                                                                         \
                          e24,                                                                                         \
                          e25,                                                                                         \
                          e26,                                                                                         \
                          e27,                                                                                         \
                          e28,                                                                                         \
                          e29,                                                                                         \
                          e30,                                                                                         \
                          e31,                                                                                         \
                          e32,                                                                                         \
                          e33,                                                                                         \
                          e34,                                                                                         \
                          e35,                                                                                         \
                          e36,                                                                                         \
                          e37,                                                                                         \
                          e38,                                                                                         \
                          e39,                                                                                         \
                          e40)                                                                                         \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, \
        e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40
#define SIMD_TUPLE_REM_42(e0,                                                                                          \
                          e1,                                                                                          \
                          e2,                                                                                          \
                          e3,                                                                                          \
                          e4,                                                                                          \
                          e5,                                                                                          \
                          e6,                                                                                          \
                          e7,                                                                                          \
                          e8,                                                                                          \
                          e9,                                                                                          \
                          e10,                                                                                         \
                          e11,                                                                                         \
                          e12,                                                                                         \
                          e13,                                                                                         \
                          e14,                                                                                         \
                          e15,                                                                                         \
                          e16,                                                                                         \
                          e17,                                                                                         \
                          e18,                                                                                         \
                          e19,                                                                                         \
                          e20,                                                                                         \
                          e21,                                                                                         \
                          e22,                                                                                         \
                          e23,                                                                                         \
                          e24,                                                                                         \
                          e25,                                                                                         \
                          e26,                                                                                         \
                          e27,                                                                                         \
                          e28,                                                                                         \
                          e29,                                                                                         \
                          e30,                                                                                         \
                          e31,                                                                                         \
                          e32,                                                                                         \
                          e33,                                                                                         \
                          e34,                                                                                         \
                          e35,                                                                                         \
                          e36,                                                                                         \
                          e37,                                                                                         \
                          e38,                                                                                         \
                          e39,                                                                                         \
                          e40,                                                                                         \
                          e41)                                                                                         \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, \
        e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41
#define SIMD_TUPLE_REM_43(e0,                                                                                          \
                          e1,                                                                                          \
                          e2,                                                                                          \
                          e3,                                                                                          \
                          e4,                                                                                          \
                          e5,                                                                                          \
                          e6,                                                                                          \
                          e7,                                                                                          \
                          e8,                                                                                          \
                          e9,                                                                                          \
                          e10,                                                                                         \
                          e11,                                                                                         \
                          e12,                                                                                         \
                          e13,                                                                                         \
                          e14,                                                                                         \
                          e15,                                                                                         \
                          e16,                                                                                         \
                          e17,                                                                                         \
                          e18,                                                                                         \
                          e19,                                                                                         \
                          e20,                                                                                         \
                          e21,                                                                                         \
                          e22,                                                                                         \
                          e23,                                                                                         \
                          e24,                                                                                         \
                          e25,                                                                                         \
                          e26,                                                                                         \
                          e27,                                                                                         \
                          e28,                                                                                         \
                          e29,                                                                                         \
                          e30,                                                                                         \
                          e31,                                                                                         \
                          e32,                                                                                         \
                          e33,                                                                                         \
                          e34,                                                                                         \
                          e35,                                                                                         \
                          e36,                                                                                         \
                          e37,                                                                                         \
                          e38,                                                                                         \
                          e39,                                                                                         \
                          e40,                                                                                         \
                          e41,                                                                                         \
                          e42)                                                                                         \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, \
        e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42
#define SIMD_TUPLE_REM_44(e0,                                                                                          \
                          e1,                                                                                          \
                          e2,                                                                                          \
                          e3,                                                                                          \
                          e4,                                                                                          \
                          e5,                                                                                          \
                          e6,                                                                                          \
                          e7,                                                                                          \
                          e8,                                                                                          \
                          e9,                                                                                          \
                          e10,                                                                                         \
                          e11,                                                                                         \
                          e12,                                                                                         \
                          e13,                                                                                         \
                          e14,                                                                                         \
                          e15,                                                                                         \
                          e16,                                                                                         \
                          e17,                                                                                         \
                          e18,                                                                                         \
                          e19,                                                                                         \
                          e20,                                                                                         \
                          e21,                                                                                         \
                          e22,                                                                                         \
                          e23,                                                                                         \
                          e24,                                                                                         \
                          e25,                                                                                         \
                          e26,                                                                                         \
                          e27,                                                                                         \
                          e28,                                                                                         \
                          e29,                                                                                         \
                          e30,                                                                                         \
                          e31,                                                                                         \
                          e32,                                                                                         \
                          e33,                                                                                         \
                          e34,                                                                                         \
                          e35,                                                                                         \
                          e36,                                                                                         \
                          e37,                                                                                         \
                          e38,                                                                                         \
                          e39,                                                                                         \
                          e40,                                                                                         \
                          e41,                                                                                         \
                          e42,                                                                                         \
                          e43)                                                                                         \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, \
        e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43
#define SIMD_TUPLE_REM_45(e0,                                                                                          \
                          e1,                                                                                          \
                          e2,                                                                                          \
                          e3,                                                                                          \
                          e4,                                                                                          \
                          e5,                                                                                          \
                          e6,                                                                                          \
                          e7,                                                                                          \
                          e8,                                                                                          \
                          e9,                                                                                          \
                          e10,                                                                                         \
                          e11,                                                                                         \
                          e12,                                                                                         \
                          e13,                                                                                         \
                          e14,                                                                                         \
                          e15,                                                                                         \
                          e16,                                                                                         \
                          e17,                                                                                         \
                          e18,                                                                                         \
                          e19,                                                                                         \
                          e20,                                                                                         \
                          e21,                                                                                         \
                          e22,                                                                                         \
                          e23,                                                                                         \
                          e24,                                                                                         \
                          e25,                                                                                         \
                          e26,                                                                                         \
                          e27,                                                                                         \
                          e28,                                                                                         \
                          e29,                                                                                         \
                          e30,                                                                                         \
                          e31,                                                                                         \
                          e32,                                                                                         \
                          e33,                                                                                         \
                          e34,                                                                                         \
                          e35,                                                                                         \
                          e36,                                                                                         \
                          e37,                                                                                         \
                          e38,                                                                                         \
                          e39,                                                                                         \
                          e40,                                                                                         \
                          e41,                                                                                         \
                          e42,                                                                                         \
                          e43,                                                                                         \
                          e44)                                                                                         \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, \
        e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44
#define SIMD_TUPLE_REM_46(e0,                                                                                          \
                          e1,                                                                                          \
                          e2,                                                                                          \
                          e3,                                                                                          \
                          e4,                                                                                          \
                          e5,                                                                                          \
                          e6,                                                                                          \
                          e7,                                                                                          \
                          e8,                                                                                          \
                          e9,                                                                                          \
                          e10,                                                                                         \
                          e11,                                                                                         \
                          e12,                                                                                         \
                          e13,                                                                                         \
                          e14,                                                                                         \
                          e15,                                                                                         \
                          e16,                                                                                         \
                          e17,                                                                                         \
                          e18,                                                                                         \
                          e19,                                                                                         \
                          e20,                                                                                         \
                          e21,                                                                                         \
                          e22,                                                                                         \
                          e23,                                                                                         \
                          e24,                                                                                         \
                          e25,                                                                                         \
                          e26,                                                                                         \
                          e27,                                                                                         \
                          e28,                                                                                         \
                          e29,                                                                                         \
                          e30,                                                                                         \
                          e31,                                                                                         \
                          e32,                                                                                         \
                          e33,                                                                                         \
                          e34,                                                                                         \
                          e35,                                                                                         \
                          e36,                                                                                         \
                          e37,                                                                                         \
                          e38,                                                                                         \
                          e39,                                                                                         \
                          e40,                                                                                         \
                          e41,                                                                                         \
                          e42,                                                                                         \
                          e43,                                                                                         \
                          e44,                                                                                         \
                          e45)                                                                                         \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, \
        e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45
#define SIMD_TUPLE_REM_47(e0,                                                                                          \
                          e1,                                                                                          \
                          e2,                                                                                          \
                          e3,                                                                                          \
                          e4,                                                                                          \
                          e5,                                                                                          \
                          e6,                                                                                          \
                          e7,                                                                                          \
                          e8,                                                                                          \
                          e9,                                                                                          \
                          e10,                                                                                         \
                          e11,                                                                                         \
                          e12,                                                                                         \
                          e13,                                                                                         \
                          e14,                                                                                         \
                          e15,                                                                                         \
                          e16,                                                                                         \
                          e17,                                                                                         \
                          e18,                                                                                         \
                          e19,                                                                                         \
                          e20,                                                                                         \
                          e21,                                                                                         \
                          e22,                                                                                         \
                          e23,                                                                                         \
                          e24,                                                                                         \
                          e25,                                                                                         \
                          e26,                                                                                         \
                          e27,                                                                                         \
                          e28,                                                                                         \
                          e29,                                                                                         \
                          e30,                                                                                         \
                          e31,                                                                                         \
                          e32,                                                                                         \
                          e33,                                                                                         \
                          e34,                                                                                         \
                          e35,                                                                                         \
                          e36,                                                                                         \
                          e37,                                                                                         \
                          e38,                                                                                         \
                          e39,                                                                                         \
                          e40,                                                                                         \
                          e41,                                                                                         \
                          e42,                                                                                         \
                          e43,                                                                                         \
                          e44,                                                                                         \
                          e45,                                                                                         \
                          e46)                                                                                         \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, \
        e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46
#define SIMD_TUPLE_REM_48(e0,                                                                                          \
                          e1,                                                                                          \
                          e2,                                                                                          \
                          e3,                                                                                          \
                          e4,                                                                                          \
                          e5,                                                                                          \
                          e6,                                                                                          \
                          e7,                                                                                          \
                          e8,                                                                                          \
                          e9,                                                                                          \
                          e10,                                                                                         \
                          e11,                                                                                         \
                          e12,                                                                                         \
                          e13,                                                                                         \
                          e14,                                                                                         \
                          e15,                                                                                         \
                          e16,                                                                                         \
                          e17,                                                                                         \
                          e18,                                                                                         \
                          e19,                                                                                         \
                          e20,                                                                                         \
                          e21,                                                                                         \
                          e22,                                                                                         \
                          e23,                                                                                         \
                          e24,                                                                                         \
                          e25,                                                                                         \
                          e26,                                                                                         \
                          e27,                                                                                         \
                          e28,                                                                                         \
                          e29,                                                                                         \
                          e30,                                                                                         \
                          e31,                                                                                         \
                          e32,                                                                                         \
                          e33,                                                                                         \
                          e34,                                                                                         \
                          e35,                                                                                         \
                          e36,                                                                                         \
                          e37,                                                                                         \
                          e38,                                                                                         \
                          e39,                                                                                         \
                          e40,                                                                                         \
                          e41,                                                                                         \
                          e42,                                                                                         \
                          e43,                                                                                         \
                          e44,                                                                                         \
                          e45,                                                                                         \
                          e46,                                                                                         \
                          e47)                                                                                         \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, \
        e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46,  \
        e47
#define SIMD_TUPLE_REM_49(e0,                                                                                          \
                          e1,                                                                                          \
                          e2,                                                                                          \
                          e3,                                                                                          \
                          e4,                                                                                          \
                          e5,                                                                                          \
                          e6,                                                                                          \
                          e7,                                                                                          \
                          e8,                                                                                          \
                          e9,                                                                                          \
                          e10,                                                                                         \
                          e11,                                                                                         \
                          e12,                                                                                         \
                          e13,                                                                                         \
                          e14,                                                                                         \
                          e15,                                                                                         \
                          e16,                                                                                         \
                          e17,                                                                                         \
                          e18,                                                                                         \
                          e19,                                                                                         \
                          e20,                                                                                         \
                          e21,                                                                                         \
                          e22,                                                                                         \
                          e23,                                                                                         \
                          e24,                                                                                         \
                          e25,                                                                                         \
                          e26,                                                                                         \
                          e27,                                                                                         \
                          e28,                                                                                         \
                          e29,                                                                                         \
                          e30,                                                                                         \
                          e31,                                                                                         \
                          e32,                                                                                         \
                          e33,                                                                                         \
                          e34,                                                                                         \
                          e35,                                                                                         \
                          e36,                                                                                         \
                          e37,                                                                                         \
                          e38,                                                                                         \
                          e39,                                                                                         \
                          e40,                                                                                         \
                          e41,                                                                                         \
                          e42,                                                                                         \
                          e43,                                                                                         \
                          e44,                                                                                         \
                          e45,                                                                                         \
                          e46,                                                                                         \
                          e47,                                                                                         \
                          e48)                                                                                         \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, \
        e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46,  \
        e47, e48
#define SIMD_TUPLE_REM_50(e0,                                                                                          \
                          e1,                                                                                          \
                          e2,                                                                                          \
                          e3,                                                                                          \
                          e4,                                                                                          \
                          e5,                                                                                          \
                          e6,                                                                                          \
                          e7,                                                                                          \
                          e8,                                                                                          \
                          e9,                                                                                          \
                          e10,                                                                                         \
                          e11,                                                                                         \
                          e12,                                                                                         \
                          e13,                                                                                         \
                          e14,                                                                                         \
                          e15,                                                                                         \
                          e16,                                                                                         \
                          e17,                                                                                         \
                          e18,                                                                                         \
                          e19,                                                                                         \
                          e20,                                                                                         \
                          e21,                                                                                         \
                          e22,                                                                                         \
                          e23,                                                                                         \
                          e24,                                                                                         \
                          e25,                                                                                         \
                          e26,                                                                                         \
                          e27,                                                                                         \
                          e28,                                                                                         \
                          e29,                                                                                         \
                          e30,                                                                                         \
                          e31,                                                                                         \
                          e32,                                                                                         \
                          e33,                                                                                         \
                          e34,                                                                                         \
                          e35,                                                                                         \
                          e36,                                                                                         \
                          e37,                                                                                         \
                          e38,                                                                                         \
                          e39,                                                                                         \
                          e40,                                                                                         \
                          e41,                                                                                         \
                          e42,                                                                                         \
                          e43,                                                                                         \
                          e44,                                                                                         \
                          e45,                                                                                         \
                          e46,                                                                                         \
                          e47,                                                                                         \
                          e48,                                                                                         \
                          e49)                                                                                         \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, \
        e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46,  \
        e47, e48, e49
#define SIMD_TUPLE_REM_51(e0,                                                                                          \
                          e1,                                                                                          \
                          e2,                                                                                          \
                          e3,                                                                                          \
                          e4,                                                                                          \
                          e5,                                                                                          \
                          e6,                                                                                          \
                          e7,                                                                                          \
                          e8,                                                                                          \
                          e9,                                                                                          \
                          e10,                                                                                         \
                          e11,                                                                                         \
                          e12,                                                                                         \
                          e13,                                                                                         \
                          e14,                                                                                         \
                          e15,                                                                                         \
                          e16,                                                                                         \
                          e17,                                                                                         \
                          e18,                                                                                         \
                          e19,                                                                                         \
                          e20,                                                                                         \
                          e21,                                                                                         \
                          e22,                                                                                         \
                          e23,                                                                                         \
                          e24,                                                                                         \
                          e25,                                                                                         \
                          e26,                                                                                         \
                          e27,                                                                                         \
                          e28,                                                                                         \
                          e29,                                                                                         \
                          e30,                                                                                         \
                          e31,                                                                                         \
                          e32,                                                                                         \
                          e33,                                                                                         \
                          e34,                                                                                         \
                          e35,                                                                                         \
                          e36,                                                                                         \
                          e37,                                                                                         \
                          e38,                                                                                         \
                          e39,                                                                                         \
                          e40,                                                                                         \
                          e41,                                                                                         \
                          e42,                                                                                         \
                          e43,                                                                                         \
                          e44,                                                                                         \
                          e45,                                                                                         \
                          e46,                                                                                         \
                          e47,                                                                                         \
                          e48,                                                                                         \
                          e49,                                                                                         \
                          e50)                                                                                         \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, \
        e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46,  \
        e47, e48, e49, e50
#define SIMD_TUPLE_REM_52(e0,                                                                                          \
                          e1,                                                                                          \
                          e2,                                                                                          \
                          e3,                                                                                          \
                          e4,                                                                                          \
                          e5,                                                                                          \
                          e6,                                                                                          \
                          e7,                                                                                          \
                          e8,                                                                                          \
                          e9,                                                                                          \
                          e10,                                                                                         \
                          e11,                                                                                         \
                          e12,                                                                                         \
                          e13,                                                                                         \
                          e14,                                                                                         \
                          e15,                                                                                         \
                          e16,                                                                                         \
                          e17,                                                                                         \
                          e18,                                                                                         \
                          e19,                                                                                         \
                          e20,                                                                                         \
                          e21,                                                                                         \
                          e22,                                                                                         \
                          e23,                                                                                         \
                          e24,                                                                                         \
                          e25,                                                                                         \
                          e26,                                                                                         \
                          e27,                                                                                         \
                          e28,                                                                                         \
                          e29,                                                                                         \
                          e30,                                                                                         \
                          e31,                                                                                         \
                          e32,                                                                                         \
                          e33,                                                                                         \
                          e34,                                                                                         \
                          e35,                                                                                         \
                          e36,                                                                                         \
                          e37,                                                                                         \
                          e38,                                                                                         \
                          e39,                                                                                         \
                          e40,                                                                                         \
                          e41,                                                                                         \
                          e42,                                                                                         \
                          e43,                                                                                         \
                          e44,                                                                                         \
                          e45,                                                                                         \
                          e46,                                                                                         \
                          e47,                                                                                         \
                          e48,                                                                                         \
                          e49,                                                                                         \
                          e50,                                                                                         \
                          e51)                                                                                         \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, \
        e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46,  \
        e47, e48, e49, e50, e51
#define SIMD_TUPLE_REM_53(e0,                                                                                          \
                          e1,                                                                                          \
                          e2,                                                                                          \
                          e3,                                                                                          \
                          e4,                                                                                          \
                          e5,                                                                                          \
                          e6,                                                                                          \
                          e7,                                                                                          \
                          e8,                                                                                          \
                          e9,                                                                                          \
                          e10,                                                                                         \
                          e11,                                                                                         \
                          e12,                                                                                         \
                          e13,                                                                                         \
                          e14,                                                                                         \
                          e15,                                                                                         \
                          e16,                                                                                         \
                          e17,                                                                                         \
                          e18,                                                                                         \
                          e19,                                                                                         \
                          e20,                                                                                         \
                          e21,                                                                                         \
                          e22,                                                                                         \
                          e23,                                                                                         \
                          e24,                                                                                         \
                          e25,                                                                                         \
                          e26,                                                                                         \
                          e27,                                                                                         \
                          e28,                                                                                         \
                          e29,                                                                                         \
                          e30,                                                                                         \
                          e31,                                                                                         \
                          e32,                                                                                         \
                          e33,                                                                                         \
                          e34,                                                                                         \
                          e35,                                                                                         \
                          e36,                                                                                         \
                          e37,                                                                                         \
                          e38,                                                                                         \
                          e39,                                                                                         \
                          e40,                                                                                         \
                          e41,                                                                                         \
                          e42,                                                                                         \
                          e43,                                                                                         \
                          e44,                                                                                         \
                          e45,                                                                                         \
                          e46,                                                                                         \
                          e47,                                                                                         \
                          e48,                                                                                         \
                          e49,                                                                                         \
                          e50,                                                                                         \
                          e51,                                                                                         \
                          e52)                                                                                         \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, \
        e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46,  \
        e47, e48, e49, e50, e51, e52
#define SIMD_TUPLE_REM_54(e0,                                                                                          \
                          e1,                                                                                          \
                          e2,                                                                                          \
                          e3,                                                                                          \
                          e4,                                                                                          \
                          e5,                                                                                          \
                          e6,                                                                                          \
                          e7,                                                                                          \
                          e8,                                                                                          \
                          e9,                                                                                          \
                          e10,                                                                                         \
                          e11,                                                                                         \
                          e12,                                                                                         \
                          e13,                                                                                         \
                          e14,                                                                                         \
                          e15,                                                                                         \
                          e16,                                                                                         \
                          e17,                                                                                         \
                          e18,                                                                                         \
                          e19,                                                                                         \
                          e20,                                                                                         \
                          e21,                                                                                         \
                          e22,                                                                                         \
                          e23,                                                                                         \
                          e24,                                                                                         \
                          e25,                                                                                         \
                          e26,                                                                                         \
                          e27,                                                                                         \
                          e28,                                                                                         \
                          e29,                                                                                         \
                          e30,                                                                                         \
                          e31,                                                                                         \
                          e32,                                                                                         \
                          e33,                                                                                         \
                          e34,                                                                                         \
                          e35,                                                                                         \
                          e36,                                                                                         \
                          e37,                                                                                         \
                          e38,                                                                                         \
                          e39,                                                                                         \
                          e40,                                                                                         \
                          e41,                                                                                         \
                          e42,                                                                                         \
                          e43,                                                                                         \
                          e44,                                                                                         \
                          e45,                                                                                         \
                          e46,                                                                                         \
                          e47,                                                                                         \
                          e48,                                                                                         \
                          e49,                                                                                         \
                          e50,                                                                                         \
                          e51,                                                                                         \
                          e52,                                                                                         \
                          e53)                                                                                         \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, \
        e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46,  \
        e47, e48, e49, e50, e51, e52, e53
#define SIMD_TUPLE_REM_55(e0,                                                                                          \
                          e1,                                                                                          \
                          e2,                                                                                          \
                          e3,                                                                                          \
                          e4,                                                                                          \
                          e5,                                                                                          \
                          e6,                                                                                          \
                          e7,                                                                                          \
                          e8,                                                                                          \
                          e9,                                                                                          \
                          e10,                                                                                         \
                          e11,                                                                                         \
                          e12,                                                                                         \
                          e13,                                                                                         \
                          e14,                                                                                         \
                          e15,                                                                                         \
                          e16,                                                                                         \
                          e17,                                                                                         \
                          e18,                                                                                         \
                          e19,                                                                                         \
                          e20,                                                                                         \
                          e21,                                                                                         \
                          e22,                                                                                         \
                          e23,                                                                                         \
                          e24,                                                                                         \
                          e25,                                                                                         \
                          e26,                                                                                         \
                          e27,                                                                                         \
                          e28,                                                                                         \
                          e29,                                                                                         \
                          e30,                                                                                         \
                          e31,                                                                                         \
                          e32,                                                                                         \
                          e33,                                                                                         \
                          e34,                                                                                         \
                          e35,                                                                                         \
                          e36,                                                                                         \
                          e37,                                                                                         \
                          e38,                                                                                         \
                          e39,                                                                                         \
                          e40,                                                                                         \
                          e41,                                                                                         \
                          e42,                                                                                         \
                          e43,                                                                                         \
                          e44,                                                                                         \
                          e45,                                                                                         \
                          e46,                                                                                         \
                          e47,                                                                                         \
                          e48,                                                                                         \
                          e49,                                                                                         \
                          e50,                                                                                         \
                          e51,                                                                                         \
                          e52,                                                                                         \
                          e53,                                                                                         \
                          e54)                                                                                         \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, \
        e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46,  \
        e47, e48, e49, e50, e51, e52, e53, e54
#define SIMD_TUPLE_REM_56(e0,                                                                                          \
                          e1,                                                                                          \
                          e2,                                                                                          \
                          e3,                                                                                          \
                          e4,                                                                                          \
                          e5,                                                                                          \
                          e6,                                                                                          \
                          e7,                                                                                          \
                          e8,                                                                                          \
                          e9,                                                                                          \
                          e10,                                                                                         \
                          e11,                                                                                         \
                          e12,                                                                                         \
                          e13,                                                                                         \
                          e14,                                                                                         \
                          e15,                                                                                         \
                          e16,                                                                                         \
                          e17,                                                                                         \
                          e18,                                                                                         \
                          e19,                                                                                         \
                          e20,                                                                                         \
                          e21,                                                                                         \
                          e22,                                                                                         \
                          e23,                                                                                         \
                          e24,                                                                                         \
                          e25,                                                                                         \
                          e26,                                                                                         \
                          e27,                                                                                         \
                          e28,                                                                                         \
                          e29,                                                                                         \
                          e30,                                                                                         \
                          e31,                                                                                         \
                          e32,                                                                                         \
                          e33,                                                                                         \
                          e34,                                                                                         \
                          e35,                                                                                         \
                          e36,                                                                                         \
                          e37,                                                                                         \
                          e38,                                                                                         \
                          e39,                                                                                         \
                          e40,                                                                                         \
                          e41,                                                                                         \
                          e42,                                                                                         \
                          e43,                                                                                         \
                          e44,                                                                                         \
                          e45,                                                                                         \
                          e46,                                                                                         \
                          e47,                                                                                         \
                          e48,                                                                                         \
                          e49,                                                                                         \
                          e50,                                                                                         \
                          e51,                                                                                         \
                          e52,                                                                                         \
                          e53,                                                                                         \
                          e54,                                                                                         \
                          e55)                                                                                         \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, \
        e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46,  \
        e47, e48, e49, e50, e51, e52, e53, e54, e55
#define SIMD_TUPLE_REM_57(e0,                                                                                          \
                          e1,                                                                                          \
                          e2,                                                                                          \
                          e3,                                                                                          \
                          e4,                                                                                          \
                          e5,                                                                                          \
                          e6,                                                                                          \
                          e7,                                                                                          \
                          e8,                                                                                          \
                          e9,                                                                                          \
                          e10,                                                                                         \
                          e11,                                                                                         \
                          e12,                                                                                         \
                          e13,                                                                                         \
                          e14,                                                                                         \
                          e15,                                                                                         \
                          e16,                                                                                         \
                          e17,                                                                                         \
                          e18,                                                                                         \
                          e19,                                                                                         \
                          e20,                                                                                         \
                          e21,                                                                                         \
                          e22,                                                                                         \
                          e23,                                                                                         \
                          e24,                                                                                         \
                          e25,                                                                                         \
                          e26,                                                                                         \
                          e27,                                                                                         \
                          e28,                                                                                         \
                          e29,                                                                                         \
                          e30,                                                                                         \
                          e31,                                                                                         \
                          e32,                                                                                         \
                          e33,                                                                                         \
                          e34,                                                                                         \
                          e35,                                                                                         \
                          e36,                                                                                         \
                          e37,                                                                                         \
                          e38,                                                                                         \
                          e39,                                                                                         \
                          e40,                                                                                         \
                          e41,                                                                                         \
                          e42,                                                                                         \
                          e43,                                                                                         \
                          e44,                                                                                         \
                          e45,                                                                                         \
                          e46,                                                                                         \
                          e47,                                                                                         \
                          e48,                                                                                         \
                          e49,                                                                                         \
                          e50,                                                                                         \
                          e51,                                                                                         \
                          e52,                                                                                         \
                          e53,                                                                                         \
                          e54,                                                                                         \
                          e55,                                                                                         \
                          e56)                                                                                         \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, \
        e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46,  \
        e47, e48, e49, e50, e51, e52, e53, e54, e55, e56
#define SIMD_TUPLE_REM_58(e0,                                                                                          \
                          e1,                                                                                          \
                          e2,                                                                                          \
                          e3,                                                                                          \
                          e4,                                                                                          \
                          e5,                                                                                          \
                          e6,                                                                                          \
                          e7,                                                                                          \
                          e8,                                                                                          \
                          e9,                                                                                          \
                          e10,                                                                                         \
                          e11,                                                                                         \
                          e12,                                                                                         \
                          e13,                                                                                         \
                          e14,                                                                                         \
                          e15,                                                                                         \
                          e16,                                                                                         \
                          e17,                                                                                         \
                          e18,                                                                                         \
                          e19,                                                                                         \
                          e20,                                                                                         \
                          e21,                                                                                         \
                          e22,                                                                                         \
                          e23,                                                                                         \
                          e24,                                                                                         \
                          e25,                                                                                         \
                          e26,                                                                                         \
                          e27,                                                                                         \
                          e28,                                                                                         \
                          e29,                                                                                         \
                          e30,                                                                                         \
                          e31,                                                                                         \
                          e32,                                                                                         \
                          e33,                                                                                         \
                          e34,                                                                                         \
                          e35,                                                                                         \
                          e36,                                                                                         \
                          e37,                                                                                         \
                          e38,                                                                                         \
                          e39,                                                                                         \
                          e40,                                                                                         \
                          e41,                                                                                         \
                          e42,                                                                                         \
                          e43,                                                                                         \
                          e44,                                                                                         \
                          e45,                                                                                         \
                          e46,                                                                                         \
                          e47,                                                                                         \
                          e48,                                                                                         \
                          e49,                                                                                         \
                          e50,                                                                                         \
                          e51,                                                                                         \
                          e52,                                                                                         \
                          e53,                                                                                         \
                          e54,                                                                                         \
                          e55,                                                                                         \
                          e56,                                                                                         \
                          e57)                                                                                         \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, \
        e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46,  \
        e47, e48, e49, e50, e51, e52, e53, e54, e55, e56, e57
#define SIMD_TUPLE_REM_59(e0,                                                                                          \
                          e1,                                                                                          \
                          e2,                                                                                          \
                          e3,                                                                                          \
                          e4,                                                                                          \
                          e5,                                                                                          \
                          e6,                                                                                          \
                          e7,                                                                                          \
                          e8,                                                                                          \
                          e9,                                                                                          \
                          e10,                                                                                         \
                          e11,                                                                                         \
                          e12,                                                                                         \
                          e13,                                                                                         \
                          e14,                                                                                         \
                          e15,                                                                                         \
                          e16,                                                                                         \
                          e17,                                                                                         \
                          e18,                                                                                         \
                          e19,                                                                                         \
                          e20,                                                                                         \
                          e21,                                                                                         \
                          e22,                                                                                         \
                          e23,                                                                                         \
                          e24,                                                                                         \
                          e25,                                                                                         \
                          e26,                                                                                         \
                          e27,                                                                                         \
                          e28,                                                                                         \
                          e29,                                                                                         \
                          e30,                                                                                         \
                          e31,                                                                                         \
                          e32,                                                                                         \
                          e33,                                                                                         \
                          e34,                                                                                         \
                          e35,                                                                                         \
                          e36,                                                                                         \
                          e37,                                                                                         \
                          e38,                                                                                         \
                          e39,                                                                                         \
                          e40,                                                                                         \
                          e41,                                                                                         \
                          e42,                                                                                         \
                          e43,                                                                                         \
                          e44,                                                                                         \
                          e45,                                                                                         \
                          e46,                                                                                         \
                          e47,                                                                                         \
                          e48,                                                                                         \
                          e49,                                                                                         \
                          e50,                                                                                         \
                          e51,                                                                                         \
                          e52,                                                                                         \
                          e53,                                                                                         \
                          e54,                                                                                         \
                          e55,                                                                                         \
                          e56,                                                                                         \
                          e57,                                                                                         \
                          e58)                                                                                         \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, \
        e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46,  \
        e47, e48, e49, e50, e51, e52, e53, e54, e55, e56, e57, e58
#define SIMD_TUPLE_REM_60(e0,                                                                                          \
                          e1,                                                                                          \
                          e2,                                                                                          \
                          e3,                                                                                          \
                          e4,                                                                                          \
                          e5,                                                                                          \
                          e6,                                                                                          \
                          e7,                                                                                          \
                          e8,                                                                                          \
                          e9,                                                                                          \
                          e10,                                                                                         \
                          e11,                                                                                         \
                          e12,                                                                                         \
                          e13,                                                                                         \
                          e14,                                                                                         \
                          e15,                                                                                         \
                          e16,                                                                                         \
                          e17,                                                                                         \
                          e18,                                                                                         \
                          e19,                                                                                         \
                          e20,                                                                                         \
                          e21,                                                                                         \
                          e22,                                                                                         \
                          e23,                                                                                         \
                          e24,                                                                                         \
                          e25,                                                                                         \
                          e26,                                                                                         \
                          e27,                                                                                         \
                          e28,                                                                                         \
                          e29,                                                                                         \
                          e30,                                                                                         \
                          e31,                                                                                         \
                          e32,                                                                                         \
                          e33,                                                                                         \
                          e34,                                                                                         \
                          e35,                                                                                         \
                          e36,                                                                                         \
                          e37,                                                                                         \
                          e38,                                                                                         \
                          e39,                                                                                         \
                          e40,                                                                                         \
                          e41,                                                                                         \
                          e42,                                                                                         \
                          e43,                                                                                         \
                          e44,                                                                                         \
                          e45,                                                                                         \
                          e46,                                                                                         \
                          e47,                                                                                         \
                          e48,                                                                                         \
                          e49,                                                                                         \
                          e50,                                                                                         \
                          e51,                                                                                         \
                          e52,                                                                                         \
                          e53,                                                                                         \
                          e54,                                                                                         \
                          e55,                                                                                         \
                          e56,                                                                                         \
                          e57,                                                                                         \
                          e58,                                                                                         \
                          e59)                                                                                         \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, \
        e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46,  \
        e47, e48, e49, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59
#define SIMD_TUPLE_REM_61(e0,                                                                                          \
                          e1,                                                                                          \
                          e2,                                                                                          \
                          e3,                                                                                          \
                          e4,                                                                                          \
                          e5,                                                                                          \
                          e6,                                                                                          \
                          e7,                                                                                          \
                          e8,                                                                                          \
                          e9,                                                                                          \
                          e10,                                                                                         \
                          e11,                                                                                         \
                          e12,                                                                                         \
                          e13,                                                                                         \
                          e14,                                                                                         \
                          e15,                                                                                         \
                          e16,                                                                                         \
                          e17,                                                                                         \
                          e18,                                                                                         \
                          e19,                                                                                         \
                          e20,                                                                                         \
                          e21,                                                                                         \
                          e22,                                                                                         \
                          e23,                                                                                         \
                          e24,                                                                                         \
                          e25,                                                                                         \
                          e26,                                                                                         \
                          e27,                                                                                         \
                          e28,                                                                                         \
                          e29,                                                                                         \
                          e30,                                                                                         \
                          e31,                                                                                         \
                          e32,                                                                                         \
                          e33,                                                                                         \
                          e34,                                                                                         \
                          e35,                                                                                         \
                          e36,                                                                                         \
                          e37,                                                                                         \
                          e38,                                                                                         \
                          e39,                                                                                         \
                          e40,                                                                                         \
                          e41,                                                                                         \
                          e42,                                                                                         \
                          e43,                                                                                         \
                          e44,                                                                                         \
                          e45,                                                                                         \
                          e46,                                                                                         \
                          e47,                                                                                         \
                          e48,                                                                                         \
                          e49,                                                                                         \
                          e50,                                                                                         \
                          e51,                                                                                         \
                          e52,                                                                                         \
                          e53,                                                                                         \
                          e54,                                                                                         \
                          e55,                                                                                         \
                          e56,                                                                                         \
                          e57,                                                                                         \
                          e58,                                                                                         \
                          e59,                                                                                         \
                          e60)                                                                                         \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, \
        e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46,  \
        e47, e48, e49, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e60
#define SIMD_TUPLE_REM_62(e0,                                                                                          \
                          e1,                                                                                          \
                          e2,                                                                                          \
                          e3,                                                                                          \
                          e4,                                                                                          \
                          e5,                                                                                          \
                          e6,                                                                                          \
                          e7,                                                                                          \
                          e8,                                                                                          \
                          e9,                                                                                          \
                          e10,                                                                                         \
                          e11,                                                                                         \
                          e12,                                                                                         \
                          e13,                                                                                         \
                          e14,                                                                                         \
                          e15,                                                                                         \
                          e16,                                                                                         \
                          e17,                                                                                         \
                          e18,                                                                                         \
                          e19,                                                                                         \
                          e20,                                                                                         \
                          e21,                                                                                         \
                          e22,                                                                                         \
                          e23,                                                                                         \
                          e24,                                                                                         \
                          e25,                                                                                         \
                          e26,                                                                                         \
                          e27,                                                                                         \
                          e28,                                                                                         \
                          e29,                                                                                         \
                          e30,                                                                                         \
                          e31,                                                                                         \
                          e32,                                                                                         \
                          e33,                                                                                         \
                          e34,                                                                                         \
                          e35,                                                                                         \
                          e36,                                                                                         \
                          e37,                                                                                         \
                          e38,                                                                                         \
                          e39,                                                                                         \
                          e40,                                                                                         \
                          e41,                                                                                         \
                          e42,                                                                                         \
                          e43,                                                                                         \
                          e44,                                                                                         \
                          e45,                                                                                         \
                          e46,                                                                                         \
                          e47,                                                                                         \
                          e48,                                                                                         \
                          e49,                                                                                         \
                          e50,                                                                                         \
                          e51,                                                                                         \
                          e52,                                                                                         \
                          e53,                                                                                         \
                          e54,                                                                                         \
                          e55,                                                                                         \
                          e56,                                                                                         \
                          e57,                                                                                         \
                          e58,                                                                                         \
                          e59,                                                                                         \
                          e60,                                                                                         \
                          e61)                                                                                         \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, \
        e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46,  \
        e47, e48, e49, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e60, e61
#define SIMD_TUPLE_REM_63(e0,                                                                                          \
                          e1,                                                                                          \
                          e2,                                                                                          \
                          e3,                                                                                          \
                          e4,                                                                                          \
                          e5,                                                                                          \
                          e6,                                                                                          \
                          e7,                                                                                          \
                          e8,                                                                                          \
                          e9,                                                                                          \
                          e10,                                                                                         \
                          e11,                                                                                         \
                          e12,                                                                                         \
                          e13,                                                                                         \
                          e14,                                                                                         \
                          e15,                                                                                         \
                          e16,                                                                                         \
                          e17,                                                                                         \
                          e18,                                                                                         \
                          e19,                                                                                         \
                          e20,                                                                                         \
                          e21,                                                                                         \
                          e22,                                                                                         \
                          e23,                                                                                         \
                          e24,                                                                                         \
                          e25,                                                                                         \
                          e26,                                                                                         \
                          e27,                                                                                         \
                          e28,                                                                                         \
                          e29,                                                                                         \
                          e30,                                                                                         \
                          e31,                                                                                         \
                          e32,                                                                                         \
                          e33,                                                                                         \
                          e34,                                                                                         \
                          e35,                                                                                         \
                          e36,                                                                                         \
                          e37,                                                                                         \
                          e38,                                                                                         \
                          e39,                                                                                         \
                          e40,                                                                                         \
                          e41,                                                                                         \
                          e42,                                                                                         \
                          e43,                                                                                         \
                          e44,                                                                                         \
                          e45,                                                                                         \
                          e46,                                                                                         \
                          e47,                                                                                         \
                          e48,                                                                                         \
                          e49,                                                                                         \
                          e50,                                                                                         \
                          e51,                                                                                         \
                          e52,                                                                                         \
                          e53,                                                                                         \
                          e54,                                                                                         \
                          e55,                                                                                         \
                          e56,                                                                                         \
                          e57,                                                                                         \
                          e58,                                                                                         \
                          e59,                                                                                         \
                          e60,                                                                                         \
                          e61,                                                                                         \
                          e62)                                                                                         \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, \
        e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46,  \
        e47, e48, e49, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e60, e61, e62
#define SIMD_TUPLE_REM_64(e0,                                                                                          \
                          e1,                                                                                          \
                          e2,                                                                                          \
                          e3,                                                                                          \
                          e4,                                                                                          \
                          e5,                                                                                          \
                          e6,                                                                                          \
                          e7,                                                                                          \
                          e8,                                                                                          \
                          e9,                                                                                          \
                          e10,                                                                                         \
                          e11,                                                                                         \
                          e12,                                                                                         \
                          e13,                                                                                         \
                          e14,                                                                                         \
                          e15,                                                                                         \
                          e16,                                                                                         \
                          e17,                                                                                         \
                          e18,                                                                                         \
                          e19,                                                                                         \
                          e20,                                                                                         \
                          e21,                                                                                         \
                          e22,                                                                                         \
                          e23,                                                                                         \
                          e24,                                                                                         \
                          e25,                                                                                         \
                          e26,                                                                                         \
                          e27,                                                                                         \
                          e28,                                                                                         \
                          e29,                                                                                         \
                          e30,                                                                                         \
                          e31,                                                                                         \
                          e32,                                                                                         \
                          e33,                                                                                         \
                          e34,                                                                                         \
                          e35,                                                                                         \
                          e36,                                                                                         \
                          e37,                                                                                         \
                          e38,                                                                                         \
                          e39,                                                                                         \
                          e40,                                                                                         \
                          e41,                                                                                         \
                          e42,                                                                                         \
                          e43,                                                                                         \
                          e44,                                                                                         \
                          e45,                                                                                         \
                          e46,                                                                                         \
                          e47,                                                                                         \
                          e48,                                                                                         \
                          e49,                                                                                         \
                          e50,                                                                                         \
                          e51,                                                                                         \
                          e52,                                                                                         \
                          e53,                                                                                         \
                          e54,                                                                                         \
                          e55,                                                                                         \
                          e56,                                                                                         \
                          e57,                                                                                         \
                          e58,                                                                                         \
                          e59,                                                                                         \
                          e60,                                                                                         \
                          e61,                                                                                         \
                          e62,                                                                                         \
                          e63)                                                                                         \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, \
        e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46,  \
        e47, e48, e49, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e60, e61, e62, e63
#
#/* SIMD_TUPLE_REM_CTOR */
#
#if SIMD_VARIADICS
#if SIMD_VARIADICS_MSVC
#define SIMD_TUPLE_REM_CTOR(...) \
    SIMD_TUPLE_REM_CTOR_I(SIMD_OVERLOAD(SIMD_TUPLE_REM_CTOR_O_, __VA_ARGS__), (__VA_ARGS__))
#define SIMD_TUPLE_REM_CTOR_I(m, args) SIMD_TUPLE_REM_CTOR_II(m, args)
#define SIMD_TUPLE_REM_CTOR_II(m, args) SIMD_CAT(m##args, )
#define SIMD_TUPLE_REM_CTOR_O_1(tuple) SIMD_EXPAND(SIMD_TUPLE_IS_SINGLE_RETURN(SIMD_REM_CAT, SIMD_REM, tuple) tuple)
#else
#define SIMD_TUPLE_REM_CTOR(...) SIMD_OVERLOAD(SIMD_TUPLE_REM_CTOR_O_, __VA_ARGS__)(__VA_ARGS__)
#define SIMD_TUPLE_REM_CTOR_O_1(tuple) SIMD_REM tuple
#endif
#define SIMD_TUPLE_REM_CTOR_O_2(size, tuple) SIMD_TUPLE_REM_CTOR_O_1(tuple)
#else
#if ~SIMD_CONFIG_FLAGS() & SIMD_CONFIG_EDG()
#define SIMD_TUPLE_REM_CTOR(size, tuple) SIMD_TUPLE_REM_CTOR_I(SIMD_TUPLE_REM(size), tuple)
#else
#define SIMD_TUPLE_REM_CTOR(size, tuple) SIMD_TUPLE_REM_CTOR_D(size, tuple)
#define SIMD_TUPLE_REM_CTOR_D(size, tuple) SIMD_TUPLE_REM_CTOR_I(SIMD_TUPLE_REM(size), tuple)
#endif
#if ~SIMD_CONFIG_FLAGS() & SIMD_CONFIG_MWCC()
#define SIMD_TUPLE_REM_CTOR_I(ext, tuple) ext tuple
#else
#define SIMD_TUPLE_REM_CTOR_I(ext, tuple) SIMD_TUPLE_REM_CTOR_OO((ext, tuple))
#define SIMD_TUPLE_REM_CTOR_OO(par) SIMD_TUPLE_REM_CTOR_II##par
#define SIMD_TUPLE_REM_CTOR_II(ext, tuple) ext##tuple
#endif
#endif
#
#endif
