/**********************************************************************
 * BIGMATH INSIGHT CONFIDENTIAL
 *
 * Copyright (C) 2016-2018 BIGMATH CORPORATION, All Rights Reserved.
 *
 * @Author: Simon Zhang on 19 Oct 2018
 * @EMail: simon.zhangsm@hotmail.com
 * @Version: $SIMD_LIB_VERSION
 *
 * Description:
 * Header file defining vector classes as interface to intrinsic functions
 * in x86 microprocessors with SSE2 and later instruction sets up to AVX512.
 *
 * Instructions:
 * Use Gnu, Clang, Intel or Microsoft C++ compiler. Compile for the desired
 * instruction set, which must be at least SSE2. Specify the supported
 * instruction set by a command line define, e.g. __SSE4_1__ if the
 * compiler does not automatically do so.
 *
 * Each vector object is represented internally in the CPU as a vector
 * register with 128, 256 or 512 bits.
 *
 * This header file includes the appropriate header files depending on the
 * supported instruction set
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

#ifndef VECTORCLASS_H
#define VECTORCLASS_H 129

// Maximum vector size, bits. Allowed values are 128, 256, 512
#ifndef MAX_VECTOR_SIZE
#define MAX_VECTOR_SIZE 256
#endif

// Get version number
#include "bigmath/simd/version.h"

// Select supported instruction set
#include "bigmath/simd/instrset.h"
#include "bigmath/simd/config.h"


#if INSTRSET < 2 // SSE2 required
#error Please compile for the SSE2 instruction set or higher
#else

#include "bigmath/simd/vectori128.h" // 128-bit integer vectors
#include "bigmath/simd/vectorf128.h" // 128-bit floating point vectors

#if MAX_VECTOR_SIZE >= 256
#if INSTRSET >= 8
#include "bigmath/simd/vectori256.h" // 256-bit integer vectors, requires AVX2 instruction set
#else
#include "bigmath/simd/vectori256e.h" // 256-bit integer vectors, emulated
#endif                                // INSTRSET >= 8
#if INSTRSET >= 7
#include "bigmath/simd/vectorf256.h" // 256-bit floating point vectors, requires AVX instruction set
#else
#include "bigmath/simd/vectorf256e.h" // 256-bit floating point vectors, emulated
#endif                                //  INSTRSET >= 7
#endif                                //  MAX_VECTOR_SIZE >= 256

#if MAX_VECTOR_SIZE >= 512
#if INSTRSET >= 9
#include "bigmath/simd/vectori512.h" // 512-bit integer vectors, requires AVX512 instruction set
#include "bigmath/simd/vectorf512.h" // 512-bit floating point vectors, requires AVX512 instruction set
#else
#include "bigmath/simd/vectori512e.h" // 512-bit integer vectors, emulated
#include "bigmath/simd/vectorf512e.h" // 512-bit floating point vectors, emulated
#endif                                //  INSTRSET >= 9
#endif                                //  MAX_VECTOR_SIZE >= 512

#endif // INSTRSET >= 2

namespace CORPORATION_NAMESPACE {
    namespace simd {}
} // namespace CORPORATION_NAMESPACE

#endif // VECTORCLASS_H
