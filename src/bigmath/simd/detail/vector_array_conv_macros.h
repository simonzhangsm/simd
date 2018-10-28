/**********************************************************************
 * BIGMATH INSIGHT CONFIDENTIAL
 *
 * Copyright (C) 2016-2018 BIGMATH CORPORATION, All Rights Reserved.
 *
 * @Author: Simon Zhang on 19 Oct 2018
 * @EMail: simon.zhangsm@hotmail.com
 * @Version: $SIMD_LIB_VERSION
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

#ifndef SIMD_DETAIL_VECTOR_ARRAY_CONV_MACROS_H
#define SIMD_DETAIL_VECTOR_ARRAY_CONV_MACROS_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/core/detail/subvec_insert.h>
#include <bigmath/simd/core/detail/subvec_extract.h>

// Used when the native vector of source vector corresponds to multiple native
// vectors in the destination vector. This happens when a vector type of
// smaller element size is converted to a vector type with larger element size
#define SIMD_VEC_ARRAY_IMPL_CONV_INSERT(RTYPE, OP, A) \
    RTYPE r;                                          \
    for (unsigned i = 0; i < (A).vec_length; ++i) {   \
        detail::subvec_insert(r, OP(a.vec(i)), i);    \
    }                                                 \
    return r;

// Used when the native vector of destination vector corresponds to multiple
// native vectors in the source vector. This happens when a vector type of
// larger element size is converted to a vector type with smaller element size.
#define SIMD_VEC_ARRAY_IMPL_CONV_EXTRACT(RTYPE, OP, A)                     \
    RTYPE r;                                                               \
    for (unsigned i = 0; i < r.vec_length; ++i) {                          \
        r.vec(i) = OP(detail::subvec_extract<RTYPE::base_length>((A), i)); \
    }                                                                      \
    return r;

#endif
