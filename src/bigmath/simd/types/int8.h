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

#ifndef SIMD_TYPES_INT8_H
#define SIMD_TYPES_INT8_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/setup_arch.h>
#include <bigmath/simd/types/any.h>
#include <bigmath/simd/types/fwd.h>
#include <bigmath/simd/core/cast.h>
#include <bigmath/simd/detail/array.h>
#include <bigmath/simd/detail/construct_eval.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {

        /** Class representing an signed @a int8 vector of arbitrary length. The vector
            always contains at least one native vector.
        */
        template <unsigned N> class int8<N, void> : public any_int8<N, int8<N, void>> {
        public:
            static const unsigned type_tag = SIMD_TAG_INT;
            using element_type = int8_t;
            using base_vector_type = int8v;
            using expr_type = void;

            inline int8<N>() = default;
            inline int8<N>(const int8<N> &) = default;
            inline int8<N> &operator=(const int8<N> &) = default;

            template <class E> inline int8<N>(const int8<N, E> &d) {
                *this = d.eval();
            }
            template <class E> inline int8<N>(const uint8<N, E> &d) {
                *this = d.eval();
            }
            template <class V> inline explicit int8<N>(const any_vec<N, V> &d) {
                *this = bit_cast<int8<N>>(d.wrapped().eval());
            }
            template <class V> inline int8<N> &operator=(const any_vec<N, V> &d) {
                *this = bit_cast<int8<N>>(d.wrapped().eval());
                return *this;
            }

            template <class E> inline int8<N>(const expr_vec_construct<E> &e) {
                detail::construct_eval_wrapper(*this, e.expr());
            }
            template <class E> inline int8<N> &operator=(const expr_vec_construct<E> &e) {
                detail::construct_eval_wrapper(*this, e.expr());
                return *this;
            }

            inline const int8v &vec(unsigned i) const {
                return d_[i];
            }
            inline int8v &vec(unsigned i) {
                return d_[i];
            }

            inline int8<N> eval() const {
                return *this;
            }

        private:
            /// Creates a signed int8 vector with the contents set to copy of native
            /// register
            static inline int8<N> set_vec(const int8v &a) {
                int8<N> r;
                for (auto &v : r.d_) {
                    v = a;
                }
                return r;
            }

        private:
            detail::vararray<int8v, int8::vec_length> d_;
        };

        /** Class representing an unsigned @a int8 vector of arbitrary length. The vector
            always contains at least one native vector.
        */
        template <unsigned N> class uint8<N, void> : public any_int8<N, uint8<N, void>> {
        public:
            static const unsigned type_tag = SIMD_TAG_UINT;
            using element_type = uint8_t;
            using base_vector_type = uint8v;
            using expr_type = void;

            inline uint8<N>() = default;
            inline uint8<N>(const uint8<N> &) = default;
            inline uint8<N> &operator=(const uint8<N> &) = default;

            template <class E> inline uint8<N>(const uint8<N, E> &d) {
                *this = d.eval();
            }
            template <class E> inline uint8<N>(const int8<N, E> &d) {
                *this = d.eval();
            }
            template <class V> inline explicit uint8<N>(const any_vec<N, V> &d) {
                *this = bit_cast<uint8<N>>(d.wrapped().eval());
            }
            template <class V> inline uint8<N> &operator=(const any_vec<N, V> &d) {
                *this = bit_cast<uint8<N>>(d.wrapped().eval());
                return *this;
            }

            template <class E> inline uint8<N>(const expr_vec_construct<E> &e) {
                detail::construct_eval_wrapper(*this, e.expr());
            }
            template <class E> inline uint8<N> &operator=(const expr_vec_construct<E> &e) {
                detail::construct_eval_wrapper(*this, e.expr());
                return *this;
            }

            inline const uint8v &vec(unsigned i) const {
                return d_[i];
            }
            inline uint8v &vec(unsigned i) {
                return d_[i];
            }

            inline uint8<N> eval() const {
                return *this;
            }

        private:
            /// Creates a unsigned int8 vector with the contents set to copy of native
            /// register
            static inline uint8<N> set_vec(const uint8v &a) {
                uint8<N> r;
                for (auto &v : r.d_) {
                    v = a;
                }
                return r;
            }

        private:
            detail::vararray<uint8v, uint8::vec_length> d_;
        };

        /// Class representing a mask for 8-bit integer vector of arbitrary
        /// length.
        template <unsigned N> class mask_int8<N, void> : public any_int8<N, mask_int8<N, void>> {
        public:
            static const unsigned type_tag = SIMD_TAG_MASK_INT;
            using base_vector_type = mask_int8v;
            using expr_type = void;

            inline mask_int8<N>() = default;
            inline mask_int8<N>(const mask_int8<N> &) = default;
            inline mask_int8<N> &operator=(const mask_int8<N> &) = default;

            /// Access the underlying type
            inline uint8<N> unmask() const {
                uint8<N> r;
                for (unsigned i = 0; i < mask_int8::vec_length; ++i) {
                    r.vec(i) = d_[i].unmask();
                }
                return r;
            }

            inline const mask_int8v &vec(unsigned i) const {
                return d_[i];
            }
            inline mask_int8v &vec(unsigned i) {
                return d_[i];
            }

            inline mask_int8<N> eval() const {
                return *this;
            }

        private:
            detail::vararray<mask_int8v, mask_int8::vec_length> d_;
        };

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
