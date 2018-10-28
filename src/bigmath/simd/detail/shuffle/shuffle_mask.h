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

#ifndef SIMD_DETAIL_SHUFFLE_SHUFFLE_MASK_H
#define SIMD_DETAIL_SHUFFLE_SHUFFLE_MASK_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#if SIMD_LITTLE_ENDIAN
#define SIMD_VSX_SHUFFLE_MASK_2x2(x0, x1) ((((x0) << 1) | (x1)) & 0x3)
#else
#define SIMD_VSX_SHUFFLE_MASK_2x2(x0, x1) ((((x1) << 1) | (x0)) & 0x3)
#endif

#define SIMD_SHUFFLE_MASK_2x2(x0, x1) ((((x1) << 1) | (x0)) & 0x3)

#define SIMD_SHUFFLE_MASK_2x2_2(x0, x1) ((SIMD_SHUFFLE_MASK_2x2(x0, x1) << 2) | SIMD_SHUFFLE_MASK_2x2(x0, x1))

#define SIMD_SHUFFLE_MASK_2x2_4(x0, x1) ((SIMD_SHUFFLE_MASK_2x2_2(x0, x1) << 4) | SIMD_SHUFFLE_MASK_2x2_2(x0, x1))

#define SIMD_SHUFFLE_MASK_4x2(x0, x1, x2, x3) ((((x3) << 3) | ((x2) << 2) | ((x1) << 1) | (x0)) & 0xf)

#define SIMD_SHUFFLE_MASK_4x2_2(x0, x1, x2, x3) \
    ((SIMD_SHUFFLE_MASK_4x2(x0, x1, x2, x3) << 4) | SIMD_SHUFFLE_MASK_4x2(x0, x1, x2, x3))

#define SIMD_SHUFFLE_MASK_4x2_4(x0, x1, x2, x3) \
    ((SIMD_SHUFFLE_MASK_4x2_2(x0, x1, x2, x3) << 8) | SIMD_SHUFFLE_MASK_4x2_2(x0, x1, x2, x3))

#define SIMD_SHUFFLE_MASK_4x4(x0, x1, x2, x3) ((((x3) << 6) | ((x2) << 4) | ((x1) << 2) | (x0)) & 0xff)

#endif
