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

#ifndef SIMD_DETAIL_ARRAY_H
#define SIMD_DETAIL_ARRAY_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {

            /*  A compile-time array that uses variables instead of array for underlying
                storage when element count is small.

                Variables are used as a workaround because arrays are too opaque for most
                older compilers to be able to figure out whith store corresponds to which
                load.
            */
            template <class T, unsigned N> class vararray {
            public:
                inline T &operator[](unsigned id) {
                    return d[id];
                }
                inline const T &operator[](unsigned id) const {
                    return d[id];
                }

            private:
                T d[N];
            };


            template <class T> class vararray<T, 2> {
            public:
                inline T &operator[](unsigned id) {
                    return id == 0 ? d0 : d1;
                }
                inline const T &operator[](unsigned id) const {
                    return id == 0 ? d0 : d1;
                }

            private:
                T d0, d1;
            };

            template <class T> class vararray<T, 4> {
            public:
                inline T &operator[](unsigned id) {
                    switch (id) {
                        case 0:
                            return d0;
                        case 1:
                            return d1;
                        case 2:
                            return d2;
                        default:
                            return d3;
                    }
                }

                inline const T &operator[](unsigned id) const {
                    switch (id) {
                        case 0:
                            return d0;
                        case 1:
                            return d1;
                        case 2:
                            return d2;
                        default:
                            return d3;
                    }
                }

            private:
                T d0, d1, d2, d3;
            };

        } // namespace detail
    }     // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
