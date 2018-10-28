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
#ifndef SIMD_PREPROCESSOR_DETAIL_SPLIT_HPP
#define SIMD_PREPROCESSOR_DETAIL_SPLIT_HPP
#
#include <bigmath/simd/detail/preprocessor/config/config.hpp>
#
#/* SIMD_SPLIT */
#
#if SIMD_CONFIG_FLAGS() & SIMD_CONFIG_MWCC()
#define SIMD_SPLIT(n, im) SIMD_SPLIT_I((n, im))
#define SIMD_SPLIT_I(par) SIMD_SPLIT_II##par
#define SIMD_SPLIT_II(n, a, b) SIMD_SPLIT_##n(a, b)
#elif SIMD_CONFIG_FLAGS() & SIMD_CONFIG_MSVC()
#define SIMD_SPLIT(n, im) SIMD_SPLIT_I(n((im)))
#define SIMD_SPLIT_I(n) SIMD_SPLIT_ID(SIMD_SPLIT_II_##n)
#define SIMD_SPLIT_II_0(s) SIMD_SPLIT_ID(SIMD_SPLIT_0 s)
#define SIMD_SPLIT_II_1(s) SIMD_SPLIT_ID(SIMD_SPLIT_1 s)
#define SIMD_SPLIT_ID(id) id
#else
#define SIMD_SPLIT(n, im) SIMD_SPLIT_I(n)(im)
#define SIMD_SPLIT_I(n) SIMD_SPLIT_##n
#endif
#
#define SIMD_SPLIT_0(a, b) a
#define SIMD_SPLIT_1(a, b) b
#
#endif
