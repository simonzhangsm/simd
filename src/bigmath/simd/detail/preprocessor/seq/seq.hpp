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
#ifndef SIMD_PREPROCESSOR_SEQ_SEQ_HPP
#define SIMD_PREPROCESSOR_SEQ_SEQ_HPP
#
#include <bigmath/simd/detail/preprocessor/config/config.hpp>
#include <bigmath/simd/detail/preprocessor/seq/elem.hpp>
#
#/* SIMD_SEQ_HEAD */
#
#define SIMD_SEQ_HEAD(seq) SIMD_SEQ_ELEM(0, seq)
#
#/* SIMD_SEQ_TAIL */
#
#if SIMD_CONFIG_FLAGS() & SIMD_CONFIG_MWCC()
#define SIMD_SEQ_TAIL(seq) SIMD_SEQ_TAIL_1((seq))
#define SIMD_SEQ_TAIL_1(par) SIMD_SEQ_TAIL_2##par
#define SIMD_SEQ_TAIL_2(seq) SIMD_SEQ_TAIL_I##seq
#elif SIMD_CONFIG_FLAGS() & SIMD_CONFIG_MSVC()
#define SIMD_SEQ_TAIL(seq) SIMD_SEQ_TAIL_ID(SIMD_SEQ_TAIL_I seq)
#define SIMD_SEQ_TAIL_ID(id) id
#elif SIMD_CONFIG_FLAGS() & SIMD_CONFIG_EDG()
#define SIMD_SEQ_TAIL(seq) SIMD_SEQ_TAIL_D(seq)
#define SIMD_SEQ_TAIL_D(seq) SIMD_SEQ_TAIL_I seq
#else
#define SIMD_SEQ_TAIL(seq) SIMD_SEQ_TAIL_I seq
#endif
#
#define SIMD_SEQ_TAIL_I(x)
#
#/* SIMD_SEQ_NIL */
#
#define SIMD_SEQ_NIL(x) (x)
#
#endif
