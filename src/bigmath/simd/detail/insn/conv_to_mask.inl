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

#ifndef SIMD_DETAIL_INSN_CONV_TO_MASK_INL
#define SIMD_DETAIL_INSN_CONV_TO_MASK_INL

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/insn/conv_to_mask.h>
#include <bigmath/simd/core/cmp_neq.h>
#include <bigmath/simd/detail/vector_array_macros.h>

namespace simd {
namespace SIMD_ARCH_NAMESPACE {
namespace detail {
namespace insn {

static inline
mask_int8<16> i_to_mask(const uint8<16>& a)
{
#if SIMD_USE_NULL
    return cmp_neq(a, (uint8<16>) make_zero());
#elif SIMD_USE_AVX512VL
    return _mm_movepi8_mask(a.native());
#else
    return a.native();
#endif
}

#if SIMD_USE_AVX2
static inline
mask_int8<32> i_to_mask(const uint8<32>& a)
{
#if SIMD_USE_AVX512VL
    return _mm256_movepi8_mask(a.native());
#else
    return a.native();
#endif
}
#endif

#if SIMD_USE_AVX512BW
static inline
mask_int8<64> i_to_mask(const uint8<64>& a)
{
    return _mm512_movepi8_mask(a.native());
}
#endif

// -----------------------------------------------------------------------------

static inline
mask_int16<8> i_to_mask(const uint16<8>& a)
{
#if SIMD_USE_NULL
    return cmp_neq(a, (uint16<8>) make_zero());
#elif SIMD_USE_AVX512VL
    return _mm_movepi16_mask(a.native());
#else
    return a.native();
#endif
}

#if SIMD_USE_AVX2
static inline
mask_int16<16> i_to_mask(const uint16<16>& a)
{
#if SIMD_USE_AVX512VL
    return _mm256_movepi16_mask(a.native());
#else
    return a.native();
#endif
}
#endif

#if SIMD_USE_AVX512BW
static inline
mask_int16<32> i_to_mask(const uint16<32>& a)
{
    return _mm512_movepi16_mask(a.native());
}
#endif

// -----------------------------------------------------------------------------

static inline
mask_int32<4> i_to_mask(const uint32<4>& a)
{
#if SIMD_USE_NULL
    return cmp_neq(a, (uint32<4>) make_zero());
#elif SIMD_USE_AVX512VL
    return _mm_movepi32_mask(a.native());
#else
    return a.native();
#endif
}

#if SIMD_USE_AVX2
static inline
mask_int32<8> i_to_mask(const uint32<8>& a)
{
#if SIMD_USE_AVX512VL
    return _mm256_movepi32_mask(a.native());
#else
    return a.native();
#endif
}
#endif

#if SIMD_USE_AVX512F
static inline
mask_int32<16> i_to_mask(const uint32<16>& a)
{
    return _mm512_test_epi32_mask(a.native(), a.native());
}
#endif

// -----------------------------------------------------------------------------

static inline
mask_int64<2> i_to_mask(const uint64<2>& a)
{
#if SIMD_USE_AVX512VL
    return _mm_movepi64_mask(a.native());
#elif SIMD_USE_SSE2 || SIMD_USE_NEON || SIMD_USE_VSX_207 || SIMD_USE_MSA
    return a.native();
#else
    return cmp_neq(a, (uint64<2>) make_zero());
#endif
}

#if SIMD_USE_AVX2
static inline
mask_int64<4> i_to_mask(const uint64<4>& a)
{
#if SIMD_USE_AVX512VL
    return _mm256_movepi64_mask(a.native());
#else
    return a.native();
#endif
}
#endif

#if SIMD_USE_AVX512F
static inline
mask_int64<8> i_to_mask(const uint64<8>& a)
{
    return _mm512_test_epi64_mask(a.native(), a.native());
}
#endif

// -----------------------------------------------------------------------------

static inline
mask_float32<4> i_to_mask(const float32<4>& a)
{
#if SIMD_USE_AVX512VL
    __m128i ia = _mm_castps_si128(a.native());
    return _mm_test_epi32_mask(ia, ia);
#elif SIMD_USE_NULL || (SIMD_USE_NEON && !SIMD_USE_NEON_FLT_SP)
    return cmp_neq(a, (float32<4>) make_zero());
#else
    return a.native();
#endif
}

#if SIMD_USE_AVX
static inline
mask_float32<8> i_to_mask(const float32<8>& a)
{
#if SIMD_USE_AVX512VL
    __m256i ia = _mm256_castps_si256(a.native());
    return _mm256_test_epi32_mask(ia, ia);
#else
    return a.native();
#endif
}
#endif

#if SIMD_USE_AVX512F
static inline
mask_float32<16> i_to_mask(const float32<16>& a)
{
    __m512i ia = _mm512_castps_si512(a.native());
    return _mm512_test_epi32_mask(ia, ia);
}
#endif

// -----------------------------------------------------------------------------

static inline
mask_float64<2> i_to_mask(const float64<2>& a)
{
#if SIMD_USE_AVX512VL
    __m128i ia = _mm_castpd_si128(a.native());
    return _mm_test_epi64_mask(ia, ia);
#elif SIMD_USE_SSE2 || SIMD_USE_NEON64 || SIMD_USE_VSX_206 || SIMD_USE_MSA
    return a.native();
#else
    return cmp_neq(a, (float64<2>) make_zero());
#endif
}

#if SIMD_USE_AVX
static inline
mask_float64<4> i_to_mask(const float64<4>& a)
{
#if SIMD_USE_AVX512VL
    __m256i ia = _mm256_castpd_si256(a.native());
    return _mm256_test_epi64_mask(ia, ia);
#else
    return a.native();
#endif
}
#endif

#if SIMD_USE_AVX512F
static inline
mask_float64<8> i_to_mask(const float64<8>& a)
{
    __m512i ia = _mm512_castpd_si512(a.native());
    return _mm512_test_epi64_mask(ia, ia);
}
#endif

// -----------------------------------------------------------------------------

template<class V> inline
typename V::mask_vector_type i_to_mask(const V& a)
{
    SIMD_VEC_ARRAY_IMPL1(typename V::mask_vector_type, i_to_mask, a)
}

} // namespace insn
} // namespace detail
} // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif // SIMD_DETAIL_TO_MASK_INL
