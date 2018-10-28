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
#ifndef SIMD_PREPROCESSOR_LOGICAL_COMPL_HPP
#define SIMD_PREPROCESSOR_LOGICAL_COMPL_HPP
#
#include <bigmath/simd/detail/preprocessor/config/config.hpp>
#
#/* SIMD_COMPL */
#
#if ~SIMD_CONFIG_FLAGS() & SIMD_CONFIG_MWCC()
#define SIMD_COMPL(x) SIMD_COMPL_I(x)
#else
#define SIMD_COMPL(x) SIMD_COMPL_OO((x))
#define SIMD_COMPL_OO(par) SIMD_COMPL_I##par
#endif
#
#if ~SIMD_CONFIG_FLAGS() & SIMD_CONFIG_MSVC()
#define SIMD_COMPL_I(x) SIMD_COMPL_##x
#else
#define SIMD_COMPL_I(x) SIMD_COMPL_ID(SIMD_COMPL_##x)
#define SIMD_COMPL_ID(id) id
#endif
#
#define SIMD_COMPL_0 1
#define SIMD_COMPL_1 0
#
#endif
