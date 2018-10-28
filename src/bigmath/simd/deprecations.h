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

#ifndef SIMD_DEPRETATIONS_H
#define SIMD_DEPRETATIONS_H

// Compatibility macro introduced in 2.1 development cycle, but never released
// Will be removed in the future
#ifdef SIMD_DEFINE_IMPLICIT_CONVERSION_OPERATOR_TO_NATIVE_TYPES
#if SIMD_DEFINE_IMPLICIT_CONVERSION_OPERATOR_TO_NATIVE_TYPES
#define SIMD_DISABLE_DEPRECATED_CONVERSION_OPERATOR_TO_NATIVE_TYPES 0
#else
#define SIMD_DISABLE_DEPRECATED_CONVERSION_OPERATOR_TO_NATIVE_TYPES 1
#endif
#endif

// Disables all APIs deprecated in 2.1 and older releases
#ifndef SIMD_DISABLE_DEPRECATED_IN_2_1_AND_OLDER
#define SIMD_DISABLE_DEPRECATED_IN_2_1_AND_OLDER 0
#endif

#if SIMD_DISABLE_DEPRECATED_IN_2_1_AND_OLDER
#ifndef SIMD_DISABLE_DEPRECATED_CONVERSION_OPERATOR_TO_NATIVE_TYPES
#define SIMD_DISABLE_DEPRECATED_CONVERSION_OPERATOR_TO_NATIVE_TYPES 1
#endif
#endif

/*  Clang supports a native vector extension that defines operators between
    vector types. SSE types such as __m128 and __m128i are implemented on top
    of this extension, which causes code like this being possible:

__m128i a, b; a = a + b;

    Previously, all simd types had an implicit conversion operator to
    native vector type. For example, both uint8<16> and uint16<8> could be
    implicitly converted to __m128i. This leads to code like this being
    accepted on clang.

uint8<16> a;
uint16<8> b;
a = a + b;

    Here, both a and b are implicitly converted to __m128i values and they are
    added using an operator provided by the clang vector extension.
    Unexpectedly, the result is paddq instruction (64-bit integer addition).

    Because of this, the implicit native vector type conversion operators are
    deprecated and a native() method is provided as a replacement in simd
    vector types. This change only affects code that interacts with native
    intrinsics. Altivec/VSX and MSA are affected only slightly, because
    intrinsics of those instruction sets never accepted implicit conversions
    from simd types.
*/
#ifndef SIMD_DISABLE_DEPRECATED_CONVERSION_OPERATOR_TO_NATIVE_TYPES
#define SIMD_DISABLE_DEPRECATED_CONVERSION_OPERATOR_TO_NATIVE_TYPES 0
#endif
#if !SIMD_DISABLE_DEPRECATED_CONVERSION_OPERATOR_TO_NATIVE_TYPES
#define SIMD_IMPLICIT_CONVERSION_DEPRECATION_MSG                       \
    SIMD_DEPRECATED(                                                   \
        "Implicit conversion operators may lead to wrong code being "  \
        "accepted without a compile error on Clang. Use the native() " \
        "method as a replacement.")
#endif

#endif
