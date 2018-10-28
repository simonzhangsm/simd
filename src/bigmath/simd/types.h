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

#ifndef SIMD_TYPES_H
#define SIMD_TYPES_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif
#include <bigmath/simd/setup_arch.h>

#include <bigmath/simd/expr.h>
#include <bigmath/simd/types/fwd.h>
#include <bigmath/simd/types/any.h>
#include <bigmath/simd/types/int8x16.h>
#include <bigmath/simd/types/int8x32.h>
#include <bigmath/simd/types/int8x64.h>
#include <bigmath/simd/types/int16x8.h>
#include <bigmath/simd/types/int16x16.h>
#include <bigmath/simd/types/int16x32.h>
#include <bigmath/simd/types/int32x4.h>
#include <bigmath/simd/types/int32x8.h>
#include <bigmath/simd/types/int32x16.h>
#include <bigmath/simd/types/int64x2.h>
#include <bigmath/simd/types/int64x4.h>
#include <bigmath/simd/types/int64x8.h>
#include <bigmath/simd/types/float32x4.h>
#include <bigmath/simd/types/float32x8.h>
#include <bigmath/simd/types/float32x16.h>
#include <bigmath/simd/types/float64x2.h>
#include <bigmath/simd/types/float64x4.h>
#include <bigmath/simd/types/float64x8.h>
#include <bigmath/simd/types/int8.h>
#include <bigmath/simd/types/int16.h>
#include <bigmath/simd/types/int32.h>
#include <bigmath/simd/types/int64.h>
#include <bigmath/simd/types/float32.h>
#include <bigmath/simd/types/float64.h>
#include <bigmath/simd/types/generic.h>
#include <bigmath/simd/types/empty_expr.h>

#endif
