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

#ifndef SIMD_DETAIL_EXPR_VEC_H
#define SIMD_DETAIL_EXPR_VEC_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {

            template <class R, unsigned N> struct expr_eval<R, uint8<N>> {
                static inline R eval(const uint8<N> &e) {
                    return (R)e;
                }
            };
            template <class R, unsigned N> struct expr_eval<R, int8<N>> {
                static inline R eval(const int8<N> &e) {
                    return (R)e;
                }
            };
            template <class R, unsigned N> struct expr_eval<R, mask_int8<N>> {
                static inline R eval(const mask_int8<N> &e) {
                    return (R)e;
                }
            };

            template <class R, unsigned N> struct expr_eval<R, uint16<N>> {
                static inline R eval(const uint16<N> &e) {
                    return (R)e;
                }
            };
            template <class R, unsigned N> struct expr_eval<R, int16<N>> {
                static inline R eval(const int16<N> &e) {
                    return (R)e;
                }
            };
            template <class R, unsigned N> struct expr_eval<R, mask_int16<N>> {
                static inline R eval(const mask_int16<N> &e) {
                    return (R)e;
                }
            };

            template <class R, unsigned N> struct expr_eval<R, uint32<N>> {
                static inline R eval(const uint32<N> &e) {
                    return (R)e;
                }
            };
            template <class R, unsigned N> struct expr_eval<R, int32<N>> {
                static inline R eval(const int32<N> &e) {
                    return (R)e;
                }
            };
            template <class R, unsigned N> struct expr_eval<R, mask_int32<N>> {
                static inline R eval(const mask_int32<N> &e) {
                    return (R)e;
                }
            };

            template <class R, unsigned N> struct expr_eval<R, uint64<N>> {
                static inline R eval(const uint64<N> &e) {
                    return (R)e;
                }
            };
            template <class R, unsigned N> struct expr_eval<R, int64<N>> {
                static inline R eval(const int64<N> &e) {
                    return (R)e;
                }
            };
            template <class R, unsigned N> struct expr_eval<R, mask_int64<N>> {
                static inline R eval(const mask_int64<N> &e) {
                    return (R)e;
                }
            };

            template <class R, unsigned N> struct expr_eval<R, float32<N>> {
                static inline R eval(const float32<N> &e) {
                    return (R)e;
                }
            };
            template <class R, unsigned N> struct expr_eval<R, mask_float32<N>> {
                static inline R eval(const mask_float32<N> &e) {
                    return (R)e;
                }
            };

            template <class R, unsigned N> struct expr_eval<R, float64<N>> {
                static inline R eval(const float64<N> &e) {
                    return (R)e;
                }
            };
            template <class R, unsigned N> struct expr_eval<R, mask_float64<N>> {
                static inline R eval(const mask_float64<N> &e) {
                    return (R)e;
                }
            };

            template <class R, unsigned N> struct expr_eval<R, uint8<N, expr_empty>> {
                static inline R eval(const uint8<N, expr_empty> &e) {
                    return (R)e.e;
                }
            };
            template <class R, unsigned N> struct expr_eval<R, int8<N, expr_empty>> {
                static inline R eval(const int8<N, expr_empty> &e) {
                    return (R)e.e;
                }
            };
            template <class R, unsigned N> struct expr_eval<R, mask_int8<N, expr_empty>> {
                static inline R eval(const mask_int8<N, expr_empty> &e) {
                    return (R)e.e;
                }
            };

            template <class R, unsigned N> struct expr_eval<R, uint16<N, expr_empty>> {
                static inline R eval(const uint16<N, expr_empty> &e) {
                    return (R)e.e;
                }
            };
            template <class R, unsigned N> struct expr_eval<R, int16<N, expr_empty>> {
                static inline R eval(const int16<N, expr_empty> &e) {
                    return (R)e.e;
                }
            };
            template <class R, unsigned N> struct expr_eval<R, mask_int16<N, expr_empty>> {
                static inline R eval(const mask_int16<N, expr_empty> &e) {
                    return (R)e.e;
                }
            };

            template <class R, unsigned N> struct expr_eval<R, uint32<N, expr_empty>> {
                static inline R eval(const uint32<N, expr_empty> &e) {
                    return (R)e.e;
                }
            };
            template <class R, unsigned N> struct expr_eval<R, int32<N, expr_empty>> {
                static inline R eval(const int32<N, expr_empty> &e) {
                    return (R)e.e;
                }
            };
            template <class R, unsigned N> struct expr_eval<R, mask_int32<N, expr_empty>> {
                static inline R eval(const mask_int32<N, expr_empty> &e) {
                    return (R)e.e;
                }
            };

            template <class R, unsigned N> struct expr_eval<R, uint64<N, expr_empty>> {
                static inline R eval(const uint64<N, expr_empty> &e) {
                    return (R)e.e;
                }
            };
            template <class R, unsigned N> struct expr_eval<R, int64<N, expr_empty>> {
                static inline R eval(const int64<N, expr_empty> &e) {
                    return (R)e.e;
                }
            };
            template <class R, unsigned N> struct expr_eval<R, mask_int64<N, expr_empty>> {
                static inline R eval(const mask_int64<N, expr_empty> &e) {
                    return (R)e.e;
                }
            };

            template <class R, unsigned N> struct expr_eval<R, float32<N, expr_empty>> {
                static inline R eval(const float32<N, expr_empty> &e) {
                    return (R)e.e;
                }
            };
            template <class R, unsigned N> struct expr_eval<R, mask_float32<N, expr_empty>> {
                static inline R eval(const mask_float32<N, expr_empty> &e) {
                    return (R)e.e;
                }
            };

            template <class R, unsigned N> struct expr_eval<R, float64<N, expr_empty>> {
                static inline R eval(const float64<N, expr_empty> &e) {
                    return (R)e.e;
                }
            };
            template <class R, unsigned N> struct expr_eval<R, mask_float64<N, expr_empty>> {
                static inline R eval(const mask_float64<N, expr_empty> &e) {
                    return (R)e.e;
                }
            };


        } // namespace detail
    }     // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
