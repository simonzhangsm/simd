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

#ifndef SIMD_DETAIL_NOT_IMPLEMENTED_H
#define SIMD_DETAIL_NOT_IMPLEMENTED_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <type_traits>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {

        namespace detail {

            /** A data type that can be implicitly converted to all types used in the
                library. Used to silence 'no return value' warnings
            */
            class dummy_value {
            public:
                template <unsigned N> operator int8<N>() {
                    return int8<N>();
                }
                template <unsigned N> operator uint8<N>() {
                    return uint8<N>();
                }
                template <unsigned N> operator mask_int8<N>() {
                    return mask_int8<N>();
                }
                template <unsigned N> operator int16<N>() {
                    return int16<N>();
                }
                template <unsigned N> operator uint16<N>() {
                    return uint16<N>();
                }
                template <unsigned N> operator mask_int16<N>() {
                    return mask_int16<N>();
                }
                template <unsigned N> operator int32<N>() {
                    return int32<N>();
                }
                template <unsigned N> operator uint32<N>() {
                    return uint32<N>();
                }
                template <unsigned N> operator mask_int32<N>() {
                    return mask_int32<N>();
                }
                template <unsigned N> operator int64<N>() {
                    return int64<N>();
                }
                template <unsigned N> operator uint64<N>() {
                    return uint64<N>();
                }
                template <unsigned N> operator mask_int64<N>() {
                    return mask_int64<N>();
                }
                template <unsigned N> operator float32<N>() {
                    return float32<N>();
                }
                template <unsigned N> operator mask_float32<N>() {
                    return mask_float32<N>();
                }
                template <unsigned N> operator float64<N>() {
                    return float64<N>();
                }
                template <unsigned N> operator mask_float64<N>() {
                    return mask_float64<N>();
                }

                template <unsigned N> operator int8<N, expr_empty>() {
                    return int8<N>();
                }
                template <unsigned N> operator uint8<N, expr_empty>() {
                    return uint8<N>();
                }
                template <unsigned N> operator mask_int8<N, expr_empty>() {
                    return mask_int8<N>();
                }
                template <unsigned N> operator int16<N, expr_empty>() {
                    return int16<N>();
                }
                template <unsigned N> operator uint16<N, expr_empty>() {
                    return uint16<N>();
                }
                template <unsigned N> operator mask_int16<N, expr_empty>() {
                    return mask_int16<N>();
                }
                template <unsigned N> operator int32<N, expr_empty>() {
                    return int32<N>();
                }
                template <unsigned N> operator uint32<N, expr_empty>() {
                    return uint32<N>();
                }
                template <unsigned N> operator mask_int32<N, expr_empty>() {
                    return mask_int32<N>();
                }
                template <unsigned N> operator int64<N, expr_empty>() {
                    return int64<N>();
                }
                template <unsigned N> operator uint64<N, expr_empty>() {
                    return uint64<N>();
                }
                template <unsigned N> operator mask_int64<N, expr_empty>() {
                    return mask_int64<N>();
                }
                template <unsigned N> operator float32<N, expr_empty>() {
                    return float32<N>();
                }
                template <unsigned N> operator mask_float32<N, expr_empty>() {
                    return mask_float32<N>();
                }
                template <unsigned N> operator float64<N, expr_empty>() {
                    return float64<N>();
                }
                template <unsigned N> operator mask_float64<N, expr_empty>() {
                    return mask_float64<N>();
                }

                operator int32_t() {
                    return 0;
                }
                operator uint32_t() {
                    return 0;
                }
                operator int64_t() {
                    return 0;
                }
                operator uint64_t() {
                    return 0;
                }
                operator float() {
                    return 0;
                }
                operator double() {
                    return 0;
                }
            };

        } // namespace detail

        /** Causes compile-time error whenever unimplemented functionality is used.
            The function may only be used in templates which are not instantiated by
            default.
        */
        template <class T> void simd_instruction_not_available_template() {
            static_assert(!std::is_same<T, T>::value, "The instruction is not available");
        }

        /** Causes linker error whenever unimplemented functionality is used. Compared
            to simd_instruction_not_available, this function is not limited to
            template contexts, but the errors are much harder to track down.
        */
        void simd_instruction_not_available0();
        void simd_instruction_not_available1();
        void simd_instruction_not_available2();
        void simd_instruction_not_available3();
        void simd_instruction_not_available4();

#define SIMD_NOT_IMPLEMENTED_TEMPLATE0(T) \
    (simd_instruction_not_available_template<T>(), ::simd::SIMD_ARCH_NAMESPACE::detail::dummy_value())

#define SIMD_NOT_IMPLEMENTED_TEMPLATE1(T, A) \
    ((void)A, simd_instruction_not_available_template<T>(), ::simd::SIMD_ARCH_NAMESPACE::detail::dummy_value())

#define SIMD_NOT_IMPLEMENTED_TEMPLATE2(T, A, B) \
    ((void)A, (void)B, simd_instruction_not_available_template<T>(), ::simd::SIMD_ARCH_NAMESPACE::detail::dummy_value())

#define SIMD_NOT_IMPLEMENTED_TEMPLATE3(T, A, B, C) \
    ((void)A,                                      \
     (void)B,                                      \
     (void)C,                                      \
     simd_instruction_not_available_template<T>(), \
     ::simd::SIMD_ARCH_NAMESPACE::detail::dummy_value())

#define SIMD_NOT_IMPLEMENTED_TEMPLATE4(T, A, B, C, D) \
    ((void)A,                                         \
     (void)B,                                         \
     (void)C,                                         \
     (void)D,                                         \
     simd_instruction_not_available_template<T>(),    \
     ::simd::SIMD_ARCH_NAMESPACE::detail::dummy_value())

#define SIMD_NOT_IMPLEMENTED0() (simd_instruction_not_available0(), ::simd::SIMD_ARCH_NAMESPACE::detail::dummy_value())

#define SIMD_NOT_IMPLEMENTED1(A) \
    ((void)A, simd_instruction_not_available1(), ::simd::SIMD_ARCH_NAMESPACE::detail::dummy_value())

#define SIMD_NOT_IMPLEMENTED2(A, B) \
    ((void)A, (void)B, simd_instruction_not_available2(), ::simd::SIMD_ARCH_NAMESPACE::detail::dummy_value())

#define SIMD_NOT_IMPLEMENTED3(A, B, C) \
    ((void)A, (void)B, (void)C, simd_instruction_not_available3(), ::simd::SIMD_ARCH_NAMESPACE::detail::dummy_value())

#define SIMD_NOT_IMPLEMENTED4(A, B, C, D) \
    ((void)A,                             \
     (void)B,                             \
     (void)C,                             \
     (void)D,                             \
     simd_instruction_not_available4(),   \
     ::simd::SIMD_ARCH_NAMESPACE::detail::dummy_value())

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
