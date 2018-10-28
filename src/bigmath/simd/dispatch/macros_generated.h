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


// This file is generated automatically. See tools/gen_dispatcher_macros.py

#ifndef DISPATCH_MACROS_GENERATED_H
#define DISPATCH_MACROS_GENERATED_H

#include <bigmath/simd/dispatch/collect_macros_generated.h>
#include <bigmath/simd/dispatch/make_dispatcher.h>

/** Note: the following macros are deprecated and provided only for backwards
    compatibility. See SIMD_MAKE_DISPATCHER for a more versatile replacement.

    Builds a dispatcher for a specific non-member function. Different macros
    are provided for functions with or without return value and for each
    parameter count.

    Macros in the form @a SIMD_MAKE_DISPATCHER_VOID# are to be used for
    functions with no return value. It accepts the following macro parameters:

    * NAME: the unqualified name of the function to dispatch.

    * T1, T2, ..., T#: the types of the parameters of the function that is
      dispatched.

    Macros in the form @a SIMD_MAKE_DISPATCHER_RET# are to be used for
    functions that return a value. It accepts the following macro parameters:

    * NAME: the unqualified name of the function to dispatch.

    * R: the type of the return value

    * T1, T2, ..., T#: the types of the parameters of the function that is
      dispatcher.


    @c SIMD_ARCH_NAMESPACE::NAME must refer to the function to be disptached
    relative to the namespace in which the @a MAKE_DISPATCHER* macro is used in.
    That is, the macro must be used in a namespace one level up than the
    dispatched function, and that namespace must be @c SIMD_ARCH_NAMESPACE

    @a R, T1, T2, ..., T# must be exactly the same as those of the function
    to be dispatched. The dispatched function may be overloaded.

    The macro defines a function with the same signature as the dispatched
    function in the namespace the macro is used. The body of that function
    implements the dispatch mechanism.

    The dispatch functions check the enabled instruction set and select the
    best function on first call. The initialization does not introduce race
    conditions when done concurrently.
*/


#define SIMD_MAKE_DISPATCHER_VOID0(NAME) SIMD_MAKE_DISPATCHER((void)(NAME)())

#define SIMD_MAKE_DISPATCHER_VOID1(NAME, T1) SIMD_MAKE_DISPATCHER((void)(NAME)((T1)a1))

#define SIMD_MAKE_DISPATCHER_VOID2(NAME, T1, T2) SIMD_MAKE_DISPATCHER((void)(NAME)((T1)a1, (T2)a2))

#define SIMD_MAKE_DISPATCHER_VOID3(NAME, T1, T2, T3) SIMD_MAKE_DISPATCHER((void)(NAME)((T1)a1, (T2)a2, (T3)a3))

#define SIMD_MAKE_DISPATCHER_VOID4(NAME, T1, T2, T3, T4) \
    SIMD_MAKE_DISPATCHER((void)(NAME)((T1)a1, (T2)a2, (T3)a3, (T4)a4))

#define SIMD_MAKE_DISPATCHER_VOID5(NAME, T1, T2, T3, T4, T5) \
    SIMD_MAKE_DISPATCHER((void)(NAME)((T1)a1, (T2)a2, (T3)a3, (T4)a4, (T5)a5))

#define SIMD_MAKE_DISPATCHER_VOID6(NAME, T1, T2, T3, T4, T5, T6) \
    SIMD_MAKE_DISPATCHER((void)(NAME)((T1)a1, (T2)a2, (T3)a3, (T4)a4, (T5)a5, (T6)a6))

#define SIMD_MAKE_DISPATCHER_VOID7(NAME, T1, T2, T3, T4, T5, T6, T7) \
    SIMD_MAKE_DISPATCHER((void)(NAME)((T1)a1, (T2)a2, (T3)a3, (T4)a4, (T5)a5, (T6)a6, (T7)a7))

#define SIMD_MAKE_DISPATCHER_VOID8(NAME, T1, T2, T3, T4, T5, T6, T7, T8) \
    SIMD_MAKE_DISPATCHER((void)(NAME)((T1)a1, (T2)a2, (T3)a3, (T4)a4, (T5)a5, (T6)a6, (T7)a7, (T8)a8))

#define SIMD_MAKE_DISPATCHER_VOID9(NAME, T1, T2, T3, T4, T5, T6, T7, T8, T9) \
    SIMD_MAKE_DISPATCHER((void)(NAME)((T1)a1, (T2)a2, (T3)a3, (T4)a4, (T5)a5, (T6)a6, (T7)a7, (T8)a8, (T9)a9))

#define SIMD_MAKE_DISPATCHER_RET0(NAME, R) SIMD_MAKE_DISPATCHER((R)(NAME)())

#define SIMD_MAKE_DISPATCHER_RET1(NAME, R, T1) SIMD_MAKE_DISPATCHER((R)(NAME)((T1)a1))

#define SIMD_MAKE_DISPATCHER_RET2(NAME, R, T1, T2) SIMD_MAKE_DISPATCHER((R)(NAME)((T1)a1, (T2)a2))

#define SIMD_MAKE_DISPATCHER_RET3(NAME, R, T1, T2, T3) SIMD_MAKE_DISPATCHER((R)(NAME)((T1)a1, (T2)a2, (T3)a3))

#define SIMD_MAKE_DISPATCHER_RET4(NAME, R, T1, T2, T3, T4) \
    SIMD_MAKE_DISPATCHER((R)(NAME)((T1)a1, (T2)a2, (T3)a3, (T4)a4))

#define SIMD_MAKE_DISPATCHER_RET5(NAME, R, T1, T2, T3, T4, T5) \
    SIMD_MAKE_DISPATCHER((R)(NAME)((T1)a1, (T2)a2, (T3)a3, (T4)a4, (T5)a5))

#define SIMD_MAKE_DISPATCHER_RET6(NAME, R, T1, T2, T3, T4, T5, T6) \
    SIMD_MAKE_DISPATCHER((R)(NAME)((T1)a1, (T2)a2, (T3)a3, (T4)a4, (T5)a5, (T6)a6))

#define SIMD_MAKE_DISPATCHER_RET7(NAME, R, T1, T2, T3, T4, T5, T6, T7) \
    SIMD_MAKE_DISPATCHER((R)(NAME)((T1)a1, (T2)a2, (T3)a3, (T4)a4, (T5)a5, (T6)a6, (T7)a7))

#define SIMD_MAKE_DISPATCHER_RET8(NAME, R, T1, T2, T3, T4, T5, T6, T7, T8) \
    SIMD_MAKE_DISPATCHER((R)(NAME)((T1)a1, (T2)a2, (T3)a3, (T4)a4, (T5)a5, (T6)a6, (T7)a7, (T8)a8))

#define SIMD_MAKE_DISPATCHER_RET9(NAME, R, T1, T2, T3, T4, T5, T6, T7, T8, T9) \
    SIMD_MAKE_DISPATCHER((R)(NAME)((T1)a1, (T2)a2, (T3)a3, (T4)a4, (T5)a5, (T6)a6, (T7)a7, (T8)a8, (T9)a9))


#endif
