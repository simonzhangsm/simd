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

#ifndef SIMD_TYPES_FWD_H
#define SIMD_TYPES_FWD_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif
#include <bigmath/simd/setup_arch.h>
#include <bigmath/simd/types/tag.h>

/*  This is an internal helper file that contains forward declarations of the
    vector templates and typedefs of specific vector types urcoah
*/
namespace simd {
    namespace SIMD_ARCH_NAMESPACE {

        namespace detail {
            // template<int> void construct_eval();
        } // namespace detail

        // types
        template <unsigned N, class E = void> class float32;
        template <unsigned N, class E = void> class mask_float32;

        using float32x4 = float32<4>;
        using float32x8 = float32<8>;
        using mask_float32x4 = mask_float32<4>;
        using mask_float32x8 = mask_float32<8>;

        template <unsigned N, class E = void> class float64;
        template <unsigned N, class E = void> class mask_float64;

        using float64x2 = float64<2>;
        using float64x4 = float64<4>;
        using mask_float64x2 = mask_float64<2>;
        using mask_float64x4 = mask_float64<4>;

        template <unsigned N, class E = void> class int8;
        template <unsigned N, class E = void> class uint8;
        template <unsigned N, class E = void> class mask_int8;

        using int8x16 = int8<16>;
        using int8x32 = int8<32>;
        using uint8x16 = uint8<16>;
        using uint8x32 = uint8<32>;
        using mask_int8x16 = mask_int8<16>;
        using mask_int8x32 = mask_int8<32>;

        template <unsigned N, class E = void> class int16;
        template <unsigned N, class E = void> class uint16;
        template <unsigned N, class E = void> class mask_int16;

        using int16x8 = int16<8>;
        using int16x16 = int16<16>;
        using uint16x8 = uint16<8>;
        using uint16x16 = uint16<16>;
        using mask_int16x8 = mask_int16<8>;
        using mask_int16x16 = mask_int16<16>;

        template <unsigned N, class E = void> class int32;
        template <unsigned N, class E = void> class uint32;
        template <unsigned N, class E = void> class mask_int32;

        using int32x4 = int32<4>;
        using int32x8 = int32<8>;
        using uint32x4 = uint32<4>;
        using uint32x8 = uint32<8>;
        using mask_int32x4 = mask_int32<4>;
        using mask_int32x8 = mask_int32<8>;

        template <unsigned N, class E = void> class int64;
        template <unsigned N, class E = void> class uint64;
        template <unsigned N, class E = void> class mask_int64;

        using int64x2 = int64<2>;
        using int64x4 = int64<4>;
        using uint64x2 = uint64<2>;
        using uint64x4 = uint64<4>;
        using mask_int64x2 = mask_int64<2>;
        using mask_int64x4 = mask_int64<4>;

#if SIMD_USE_AVX512F
#define SIMD_FAST_FLOAT32_SIZE 16
#define SIMD_FAST_FLOAT64_SIZE 8
#elif SIMD_USE_AVX
#define SIMD_FAST_FLOAT32_SIZE 8
#define SIMD_FAST_FLOAT64_SIZE 4
#elif SIMD_USE_SSE2 || SIMD_USE_NEON || SIMD_USE_ALTIVEC || SIMD_USE_MSA || SIMD_USE_NULL
#define SIMD_FAST_FLOAT32_SIZE 4
#define SIMD_FAST_FLOAT64_SIZE 2
#endif

#if SIMD_USE_AVX512BW
#define SIMD_FAST_INT8_SIZE 64
#define SIMD_FAST_INT16_SIZE 32
#define SIMD_FAST_INT32_SIZE 16
#define SIMD_FAST_INT64_SIZE 8
#elif SIMD_USE_AVX512F
#define SIMD_FAST_INT8_SIZE 32
#define SIMD_FAST_INT16_SIZE 16
#define SIMD_FAST_INT32_SIZE 16
#define SIMD_FAST_INT64_SIZE 8
#elif SIMD_USE_AVX2
#define SIMD_FAST_INT8_SIZE 32
#define SIMD_FAST_INT16_SIZE 16
#define SIMD_FAST_INT32_SIZE 8
#define SIMD_FAST_INT64_SIZE 4
#elif SIMD_USE_SSE2 || SIMD_USE_NEON || SIMD_USE_ALTIVEC || SIMD_USE_MSA || SIMD_USE_NULL
#define SIMD_FAST_INT8_SIZE 16
#define SIMD_FAST_INT16_SIZE 8
#define SIMD_FAST_INT32_SIZE 4
#define SIMD_FAST_INT64_SIZE 2
#endif

        using float32v = float32<SIMD_FAST_FLOAT32_SIZE>;
        using mask_float32v = mask_float32<SIMD_FAST_FLOAT32_SIZE>;
        using float64v = float64<SIMD_FAST_FLOAT64_SIZE>;
        using mask_float64v = mask_float64<SIMD_FAST_FLOAT64_SIZE>;

        using int8v = int8<SIMD_FAST_INT8_SIZE>;
        using uint8v = uint8<SIMD_FAST_INT8_SIZE>;
        using mask_int8v = mask_int8<SIMD_FAST_INT8_SIZE>;

        using int16v = int16<SIMD_FAST_INT16_SIZE>;
        using uint16v = uint16<SIMD_FAST_INT16_SIZE>;
        using mask_int16v = mask_int16<SIMD_FAST_INT16_SIZE>;

        using int32v = int32<SIMD_FAST_INT32_SIZE>;
        using uint32v = uint32<SIMD_FAST_INT32_SIZE>;
        using mask_int32v = mask_int32<SIMD_FAST_INT32_SIZE>;

        using int64v = int64<SIMD_FAST_INT64_SIZE>;
        using uint64v = uint64<SIMD_FAST_INT64_SIZE>;
        using mask_int64v = mask_int64<SIMD_FAST_INT64_SIZE>;

        using mask_float32v2 = mask_float32<SIMD_FAST_FLOAT32_SIZE * 2>;
        using float64v2 = float64<SIMD_FAST_FLOAT64_SIZE * 2>;
        using mask_float64v2 = mask_float64<SIMD_FAST_FLOAT64_SIZE * 2>;

        using int8v2 = int8<SIMD_FAST_INT8_SIZE * 2>;
        using uint8v2 = uint8<SIMD_FAST_INT8_SIZE * 2>;
        using mask_int8v2 = mask_int8<SIMD_FAST_INT8_SIZE * 2>;

        using int16v2 = int16<SIMD_FAST_INT16_SIZE * 2>;
        using uint16v2 = uint16<SIMD_FAST_INT16_SIZE * 2>;
        using mask_int16v2 = mask_int16<SIMD_FAST_INT16_SIZE * 2>;

        using int32v2 = int32<SIMD_FAST_INT32_SIZE * 2>;
        using uint32v2 = uint32<SIMD_FAST_INT32_SIZE * 2>;
        using mask_int32v2 = mask_int32<SIMD_FAST_INT32_SIZE * 2>;

        using int64v2 = int64<SIMD_FAST_INT64_SIZE * 2>;
        using uint64v2 = uint64<SIMD_FAST_INT64_SIZE * 2>;
        using mask_int64v2 = mask_int64<SIMD_FAST_INT64_SIZE * 2>;


        using float32v4 = float32<SIMD_FAST_FLOAT32_SIZE * 4>;
        using mask_float32v4 = mask_float32<SIMD_FAST_FLOAT32_SIZE * 4>;
        using float64v4 = float64<SIMD_FAST_FLOAT64_SIZE * 4>;
        using mask_float64v4 = mask_float64<SIMD_FAST_FLOAT64_SIZE * 4>;

        using int8v4 = int8<SIMD_FAST_INT8_SIZE * 4>;
        using uint8v4 = uint8<SIMD_FAST_INT8_SIZE * 4>;
        using mask_int8v4 = mask_int8<SIMD_FAST_INT8_SIZE * 4>;

        using int16v4 = int16<SIMD_FAST_INT16_SIZE * 4>;
        using uint16v4 = uint16<SIMD_FAST_INT16_SIZE * 4>;
        using mask_int16v4 = mask_int16<SIMD_FAST_INT16_SIZE * 4>;

        using int32v4 = int32<SIMD_FAST_INT32_SIZE * 4>;
        using uint32v4 = uint32<SIMD_FAST_INT32_SIZE * 4>;
        using mask_int32v4 = mask_int32<SIMD_FAST_INT32_SIZE * 4>;

        using int64v4 = int64<SIMD_FAST_INT64_SIZE * 4>;
        using uint64v4 = uint64<SIMD_FAST_INT64_SIZE * 4>;
        using mask_int64v4 = mask_int64<SIMD_FAST_INT64_SIZE * 4>;

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
