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

#ifndef TEST_UTILS_ELEMENT_TYPE_H
#define TEST_UTILS_ELEMENT_TYPE_H

#include <bigmath/simd/simd.h>
#include <cstdint>

// Types of vector elements
enum ElementType : uint8_t {
    TYPE_INT8 = 0,
    TYPE_UINT8,
    TYPE_INT16,
    TYPE_UINT16,
    TYPE_UINT32,
    TYPE_INT32,
    TYPE_UINT64,
    TYPE_INT64,
    TYPE_FLOAT32,
    TYPE_FLOAT64
};

// Returns size of the element of a vector of given type
static inline std::size_t element_size_for_type(ElementType t) {
    switch (t) {
        case TYPE_INT8:
        case TYPE_UINT8:
            return 1;
        case TYPE_INT16:
        case TYPE_UINT16:
            return 2;
        case TYPE_UINT32:
        case TYPE_INT32:
            return 4;
        case TYPE_UINT64:
        case TYPE_INT64:
            return 8;
        case TYPE_FLOAT32:
            return 4;
        case TYPE_FLOAT64:
            return 8;
    }
    std::abort();
    return 0;
}

template <class V> struct GetElementType {
    static_assert(sizeof(V) <= 8, "Unsupported element size");
    static const ElementType value =
        sizeof(V) == 1 ? TYPE_UINT8 : sizeof(V) == 2 ? TYPE_UINT16 : sizeof(V) == 4 ? TYPE_UINT32 : TYPE_UINT64;
};
template <unsigned N, class E> struct GetElementType<simd::uint8<N, E>> {
    static const ElementType value = TYPE_UINT8;
};
template <unsigned N, class E> struct GetElementType<simd::int8<N, E>> { static const ElementType value = TYPE_INT8; };
template <unsigned N, class E> struct GetElementType<simd::uint16<N, E>> {
    static const ElementType value = TYPE_UINT16;
};
template <unsigned N, class E> struct GetElementType<simd::int16<N, E>> {
    static const ElementType value = TYPE_INT16;
};
template <unsigned N, class E> struct GetElementType<simd::uint32<N, E>> {
    static const ElementType value = TYPE_UINT32;
};
template <unsigned N, class E> struct GetElementType<simd::int32<N, E>> {
    static const ElementType value = TYPE_INT32;
};
template <unsigned N, class E> struct GetElementType<simd::float32<N, E>> {
    static const ElementType value = TYPE_FLOAT32;
};
template <unsigned N, class E> struct GetElementType<simd::uint64<N, E>> {
    static const ElementType value = TYPE_UINT64;
};
template <unsigned N, class E> struct GetElementType<simd::int64<N, E>> {
    static const ElementType value = TYPE_INT64;
};
template <unsigned N, class E> struct GetElementType<simd::float64<N, E>> {
    static const ElementType value = TYPE_FLOAT64;
};

template <> struct GetElementType<uint8_t> { static const ElementType value = TYPE_UINT8; };
template <> struct GetElementType<int8_t> { static const ElementType value = TYPE_INT8; };
template <> struct GetElementType<uint16_t> { static const ElementType value = TYPE_UINT16; };
template <> struct GetElementType<int16_t> { static const ElementType value = TYPE_INT16; };
template <> struct GetElementType<uint32_t> { static const ElementType value = TYPE_UINT32; };
template <> struct GetElementType<int32_t> { static const ElementType value = TYPE_INT32; };
template <> struct GetElementType<float> { static const ElementType value = TYPE_FLOAT32; };
template <> struct GetElementType<uint64_t> { static const ElementType value = TYPE_UINT64; };
template <> struct GetElementType<int64_t> { static const ElementType value = TYPE_INT64; };
template <> struct GetElementType<double> { static const ElementType value = TYPE_FLOAT64; };

#endif
