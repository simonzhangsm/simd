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

#ifndef SIMD_DETAIL_INSN_DETAIL_CAST_INL
#define SIMD_DETAIL_INSN_DETAIL_CAST_INL

#ifndef SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/cast.h>
#include <bigmath/simd/detail/cast_bitwise.h>
#include <bigmath/simd/core/to_mask.h>

namespace simd {
namespace SIMD_ARCH_NAMESPACE {
namespace detail {

template<class T> struct base_mask_vector_type { using type = T; };
template<unsigned N> struct base_mask_vector_type<mask_int8<N>> { using type = uint8<N>; };
template<unsigned N> struct base_mask_vector_type<mask_int16<N>> { using type = uint16<N>; };
template<unsigned N> struct base_mask_vector_type<mask_int32<N>> { using type = uint32<N>; };
template<unsigned N> struct base_mask_vector_type<mask_int64<N>> { using type = uint64<N>; };
template<unsigned N> struct base_mask_vector_type<mask_float32<N>> { using type = float32<N>; };
template<unsigned N> struct base_mask_vector_type<mask_float64<N>> { using type = float64<N>; };

template<class T, class R> inline
void cast_bitwise_unmask(const T& t, R& r)
{
    using TT = typename base_mask_vector_type<T>::type;
    TT tt = t.unmask();
    cast_bitwise_vector(tt, r);
}

template<class T, class R> inline
void cast_bitwise_remask(const T& t, R& r)
{
    using BaseMaskVector = typename base_mask_vector_type<R>::type;
    BaseMaskVector rr;
    cast_bitwise_vector(t.unmask(), rr);
    r = to_mask(rr);
}

template<>
struct cast_wrapper<CAST_TYPE_OTHER> {
    template<class T, class R> inline
    static void run(const T& t, R& r)
    {
        cast_bitwise(t, r);
    }
};

template<>
struct cast_wrapper<CAST_TYPE_MASK_TO_MASK_BITWISE> {
    template<class T, class R> inline
    static void run(const T& t, R& r)
    {
        static_assert(R::size_tag == T::size_tag,
                      "Conversions between masks with different element size is"
                      " not allowed");
        cast_bitwise_vector(t.eval(), r);
    }
};

template<>
struct cast_wrapper<CAST_TYPE_MASK_TO_MASK_UNMASK> {
    template<class R, class T> inline
    static void run(const T& t, R& r)
    {
        static_assert(R::size_tag == T::size_tag,
                      "Conversions between masks with different element size is"
                      " not allowed");
        cast_bitwise_unmask(t.eval(), r);
    }
};

template<>
struct cast_wrapper<CAST_TYPE_MASK_TO_MASK_REMASK> {
    template<class R, class T> inline
    static void run(const T& t, R& r)
    {
        static_assert(R::size_tag == T::size_tag,
                      "Conversions between masks with different element size is"
                      " not allowed");
        cast_bitwise_remask(t.eval(), r);
    }
};

template<>
struct cast_wrapper<CAST_TYPE_VECTOR_TO_MASK> {
    template<class R, class T> inline
    static void run(const T& t, R& r)
    {
        (void) t; (void) r;
        static_assert(!std::is_same<T,T>::value, // fake dependency
                      "Conversion from non-mask type to a mask type is not allowed");
    }
};

template<>
struct cast_wrapper<CAST_TYPE_MASK_TO_VECTOR> {
    template<class R, class T> inline
    static void run(const T& t, R& r)
    {
        cast_bitwise_unmask(t.eval(), r);
    }
};

template<>
struct cast_wrapper<CAST_TYPE_VECTOR_TO_VECTOR> {
    template<class R, class T> inline
    static void run(const T& t, R& r)
    {
        cast_bitwise_vector(t.eval(), r);
    }
};

} // namespace detail
} // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif

