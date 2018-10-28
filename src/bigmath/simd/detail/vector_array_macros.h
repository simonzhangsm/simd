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

#ifndef SIMD_DETAIL_VECTOR_ARRAY_MACROS_H
#define SIMD_DETAIL_VECTOR_ARRAY_MACROS_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>

#define SIMD_VEC_ARRAY_IMPL1(RTYPE, OP, V1)       \
    RTYPE r;                                      \
    for (unsigned i = 0; i < r.vec_length; ++i) { \
        r.vec(i) = OP((V1).vec(i));               \
    }                                             \
    return r;

#define SIMD_VEC_ARRAY_IMPL2(RTYPE, OP, V1, V2)   \
    RTYPE r;                                      \
    for (unsigned i = 0; i < r.vec_length; ++i) { \
        r.vec(i) = OP((V1).vec(i), (V2).vec(i));  \
    }                                             \
    return r;

#define SIMD_VEC_ARRAY_IMPL2S(RTYPE, OP, V1, A2)  \
    RTYPE r;                                      \
    for (unsigned i = 0; i < r.vec_length; ++i) { \
        r.vec(i) = OP((V1).vec(i), (A2));         \
    }                                             \
    return r;

#define SIMD_VEC_ARRAY_IMPL3(RTYPE, OP, V1, V2, V3)           \
    RTYPE r;                                                  \
    for (unsigned i = 0; i < r.vec_length; ++i) {             \
        r.vec(i) = OP((V1).vec(i), (V2).vec(i), (V3).vec(i)); \
    }                                                         \
    return r;

#define SIMD_VEC_ARRAY_IMPL_REF1(RTYPE, OP, V1)        \
    for (unsigned i = 0; i < RTYPE::vec_length; ++i) { \
        OP((V1).vec(i));                               \
    }

#define SIMD_VEC_ARRAY_IMPL_REF2(RTYPE, OP, V1, V2)    \
    for (unsigned i = 0; i < RTYPE::vec_length; ++i) { \
        OP((V1).vec(i), (V2).vec(i));                  \
    }

#define SIMD_VEC_ARRAY_IMPL_REF3(RTYPE, OP, V1, V2, V3) \
    for (unsigned i = 0; i < RTYPE::vec_length; ++i) {  \
        OP((V1).vec(i), (V2).vec(i), (V3).vec(i));      \
    }

#define SIMD_VEC_ARRAY_IMPL_REF4(RTYPE, OP, V1, V2, V3, V4)     \
    for (unsigned i = 0; i < RTYPE::vec_length; ++i) {          \
        OP((V1).vec(i), (V2).vec(i), (V3).vec(i), (V4).vec(i)); \
    }

#endif
