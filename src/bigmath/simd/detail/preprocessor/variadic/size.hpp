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
#ifndef SIMD_PREPROCESSOR_VARIADIC_SIZE_HPP
#define SIMD_PREPROCESSOR_VARIADIC_SIZE_HPP
#
#include <bigmath/simd/detail/preprocessor/cat.hpp>
#include <bigmath/simd/detail/preprocessor/config/config.hpp>
#
#/* SIMD_VARIADIC_SIZE */
#
#if SIMD_VARIADICS
#if SIMD_VARIADICS_MSVC
#define SIMD_VARIADIC_SIZE(...)                \
    SIMD_CAT(SIMD_VARIADIC_SIZE_I(__VA_ARGS__, \
                                  64,          \
                                  63,          \
                                  62,          \
                                  61,          \
                                  60,          \
                                  59,          \
                                  58,          \
                                  57,          \
                                  56,          \
                                  55,          \
                                  54,          \
                                  53,          \
                                  52,          \
                                  51,          \
                                  50,          \
                                  49,          \
                                  48,          \
                                  47,          \
                                  46,          \
                                  45,          \
                                  44,          \
                                  43,          \
                                  42,          \
                                  41,          \
                                  40,          \
                                  39,          \
                                  38,          \
                                  37,          \
                                  36,          \
                                  35,          \
                                  34,          \
                                  33,          \
                                  32,          \
                                  31,          \
                                  30,          \
                                  29,          \
                                  28,          \
                                  27,          \
                                  26,          \
                                  25,          \
                                  24,          \
                                  23,          \
                                  22,          \
                                  21,          \
                                  20,          \
                                  19,          \
                                  18,          \
                                  17,          \
                                  16,          \
                                  15,          \
                                  14,          \
                                  13,          \
                                  12,          \
                                  11,          \
                                  10,          \
                                  9,           \
                                  8,           \
                                  7,           \
                                  6,           \
                                  5,           \
                                  4,           \
                                  3,           \
                                  2,           \
                                  1, ), )
#else
#define SIMD_VARIADIC_SIZE(...)       \
    SIMD_VARIADIC_SIZE_I(__VA_ARGS__, \
                         64,          \
                         63,          \
                         62,          \
                         61,          \
                         60,          \
                         59,          \
                         58,          \
                         57,          \
                         56,          \
                         55,          \
                         54,          \
                         53,          \
                         52,          \
                         51,          \
                         50,          \
                         49,          \
                         48,          \
                         47,          \
                         46,          \
                         45,          \
                         44,          \
                         43,          \
                         42,          \
                         41,          \
                         40,          \
                         39,          \
                         38,          \
                         37,          \
                         36,          \
                         35,          \
                         34,          \
                         33,          \
                         32,          \
                         31,          \
                         30,          \
                         29,          \
                         28,          \
                         27,          \
                         26,          \
                         25,          \
                         24,          \
                         23,          \
                         22,          \
                         21,          \
                         20,          \
                         19,          \
                         18,          \
                         17,          \
                         16,          \
                         15,          \
                         14,          \
                         13,          \
                         12,          \
                         11,          \
                         10,          \
                         9,           \
                         8,           \
                         7,           \
                         6,           \
                         5,           \
                         4,           \
                         3,           \
                         2,           \
                         1, )
#endif
#define SIMD_VARIADIC_SIZE_I(e0,   \
                             e1,   \
                             e2,   \
                             e3,   \
                             e4,   \
                             e5,   \
                             e6,   \
                             e7,   \
                             e8,   \
                             e9,   \
                             e10,  \
                             e11,  \
                             e12,  \
                             e13,  \
                             e14,  \
                             e15,  \
                             e16,  \
                             e17,  \
                             e18,  \
                             e19,  \
                             e20,  \
                             e21,  \
                             e22,  \
                             e23,  \
                             e24,  \
                             e25,  \
                             e26,  \
                             e27,  \
                             e28,  \
                             e29,  \
                             e30,  \
                             e31,  \
                             e32,  \
                             e33,  \
                             e34,  \
                             e35,  \
                             e36,  \
                             e37,  \
                             e38,  \
                             e39,  \
                             e40,  \
                             e41,  \
                             e42,  \
                             e43,  \
                             e44,  \
                             e45,  \
                             e46,  \
                             e47,  \
                             e48,  \
                             e49,  \
                             e50,  \
                             e51,  \
                             e52,  \
                             e53,  \
                             e54,  \
                             e55,  \
                             e56,  \
                             e57,  \
                             e58,  \
                             e59,  \
                             e60,  \
                             e61,  \
                             e62,  \
                             e63,  \
                             size, \
                             ...)  \
    size
#endif
#
#endif
