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

#ifndef SIMD_TYPES_TAG_H
#define SIMD_TYPES_TAG_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

/*  The values of the tags are such that it is easy to retrieve the result type
    of an operation that involves two different types. That is, if the
    arguments have types with type tags A and B then the type tag of the result
    type will be max(A, B). Similarly, if the arguments have types with size
    tags P and Q then the size tag of the result type will be max(P, Q).

    The only exception is operation on masks with masks with different size
    tags. In that case the type tag of the result type is always TAG_UINT.

    The following list illustrates the conversion rules. The first two items
    are the argument types and the third item is the result type.

    [ Same element sizes ]

           intXX |        intXX ->        intXX
           intXX |       uintXX ->       uintXX
          uintXX |       uintXX ->       uintXX
         floatXX |        intXX ->      floatXX
         floatXX |       uintXX ->      floatXX
         floatXX |      floatXX ->      floatXX
      mask_intXX |        intXX ->       uintXX
      mask_intXX |       uintXX ->       uintXX
      mask_intXX |   mask_intXX ->   mask_intXX
      mask_intXX |      floatXX ->      floatXX
      mask_intXX | mask_floatXX -> mask_floatXX
    mask_floatXX |      floatXX ->      floatXX
    mask_floatXX | mask_floatXX -> mask_floatXX

    [ Different element sizes ]

           intXX |        intYY ->        int{ max(XX, YY) }
           intXX |       uintYY ->       uint{ max(XX, YY) }
          uintXX |       uintYY ->       uint{ max(XX, YY) }
         floatXX |        intYY ->      float{ max(XX, YY) }
         floatXX |       uintYY ->      float{ max(XX, YY) }
         floatXX |      floatYY ->      float{ max(XX, YY) }
      mask_intXX |        intYY ->       uint{ max(XX, YY) }
      mask_intXX |       uintYY ->       uint{ max(XX, YY) }
      mask_intXX |   mask_intYY ->       uint{ max(XX, YY) }
      mask_intXX |      floatYY ->      float{ max(XX, YY) }
      mask_intXX | mask_floatYY ->       uint{ max(XX, YY) }
    mask_floatXX |      floatYY ->      float{ max(XX, YY) }
    mask_floatXX | mask_floatYY ->       uint{ max(XX, YY) }

    See also simd/detail/get_expr.h

    If particular operation does not support masks, the masks are expanded
    internally. If both arguments are masks, then the result type is the
    underlying type of the mask type which would be retrieved using the usual
    rules (see get_expr2_nomask).

    Several examples:

    mask_int32 + mask_int32 -> uint32
    int32 + mask_int32 -> int32
    uint32 + mask_int32 -> uint32
*/
#define SIMD_TAG_MASK_INT 1
#define SIMD_TAG_MASK_FLOAT 2
#define SIMD_TAG_INT 3
#define SIMD_TAG_UINT 4
#define SIMD_TAG_FLOAT 5
#define SIMD_TAG_SIZE8 10
#define SIMD_TAG_SIZE16 20
#define SIMD_TAG_SIZE32 30
#define SIMD_TAG_SIZE64 40

#endif
