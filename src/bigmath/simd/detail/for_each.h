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

#ifndef DETAIL_FOR_EACH_H
#define DETAIL_FOR_EACH_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/core/extract.h>
#include <bigmath/simd/detail/mem_block.h>
#include <type_traits>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {

#if SIMD_USE_SSE2 || SIMD_USE_NEON || SIMD_USE_MSA
            template <class V, class F>
            inline void foreach_impl(std::integral_constant<unsigned, 2>, const V &v, F function) {
                function(extract<0>(v));
                function(extract<1>(v));
            }

            template <class V, class F>
            inline void foreach_impl(std::integral_constant<unsigned, 4>, const V &v, F function) {
                function(extract<0>(v));
                function(extract<1>(v));
                function(extract<2>(v));
                function(extract<3>(v));
            }

            template <unsigned N, class V, class F>
            inline void foreach_impl(std::integral_constant<unsigned, N>, const V &v, F function) {
                // When we're operating on more than 4-5 elements it makes sense to move
                // the vector to memory and load data from there. This has higher latency,
                // but this is masked by extracting the first several elements directly
                // from the SIMD register set. For the rest of elements it's very likely
                // that loading through memory has higher throughput.
                //
                // Recent x86 (since Sandy Bridge) and NEON (since Cortex A73) processors
                // are able to sustain more than one load memory access per cycle.
                // All x86 processors (at least up to Skylake, newer not checked) are only
                // able to sustain single cross domain data access instruction per cycle.

                // TODO: needs tuning on ARM and MIPS
                function(extract<0>(v));
                function(extract<1>(v));
                mem_block<V> mem(v);
                for (unsigned i = 2; i < N; ++i)
                    function(mem[i]);
            }
#else
            template <unsigned N, class V, class F>
            inline void foreach_impl(std::integral_constant<unsigned, N>, const V &v, F function) {
                mem_block<V> mem(v);
                for (unsigned i = 0; i < N; ++i)
                    function(mem[i]);
            }
#endif

            template <unsigned N, class V, class F> inline void for_each(const any_vec<N, V> &v, F function) {
                using size_tag = std::integral_constant<unsigned, V::base_vector_type::length>;
                for (unsigned i = 0; i < V::vec_length; ++i)
                    foreach_impl(size_tag(), v.wrapped().vec(i), function);
            }


        } // namespace detail
    }     // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
