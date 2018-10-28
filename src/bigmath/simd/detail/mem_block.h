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

#ifndef SIMD_DETAIL_MEM_BLOCK_H
#define SIMD_DETAIL_MEM_BLOCK_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/types/traits.h>
#include <bigmath/simd/core/store.h>
#include <bigmath/simd/core/load.h>
#include <cstring>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {

            /** A block of memory that stores a vector and allows access to its elements.
                Data transfer is not explicit -- the compiler is allowed to optimize it
                however it wants, failing back to storing and loading from memory, if
                necessary.
            */
            template <class V> class mem_block {
            public:
                static_assert(is_vector<V>::value, "Non-vector types are not supported");

                using element_type = typename V::element_type;
                static const unsigned length = V::length;

                inline mem_block() = default;
                inline mem_block(const mem_block &) = default;
                inline mem_block(const V &v) {
                    store(d_, v);
                }

                inline mem_block &operator=(const V &v) {
                    store(d_, v);
                    return *this;
                }

                inline operator V() const {
                    V r = load(d_);
                    return r;
                }

                inline const element_type &operator[](unsigned id) const {
                    return d_[id];
                }
                inline element_type &operator[](unsigned id) {
                    return d_[id];
                }

                inline const element_type *data() const {
                    return d_;
                }

            private:
#if SIMD_USE_NEON32
                // On NEON the stack and vector types are not themselves 16-byte aligned
                SIMDALIGN(16) element_type d_[length];
#else
                union {
                    element_type d_[length];
                    V align_;
                };
#endif
            };

        } // namespace detail
    }     // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
