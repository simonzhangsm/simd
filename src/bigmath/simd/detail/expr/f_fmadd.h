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

#ifndef SIMD_DETAIL_EXPR_F_FMADD_H
#define SIMD_DETAIL_EXPR_F_FMADD_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/insn/f_fmadd.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {

            template <class R, class E1, class E2, class E3> struct expr_eval<R, expr_fmadd<E1, E2, E3>> {
                static inline R eval(const expr_fmadd<E1, E2, E3> &e) {
                    return (R)insn::i_fmadd(e.a.eval(), e.b.eval(), e.c.eval());
                }
            };

        } // namespace detail
    }     // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
