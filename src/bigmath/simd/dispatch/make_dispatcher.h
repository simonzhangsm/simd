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

#ifndef DISPATCH_MAKE_DISPATCHER_H
#define DISPATCH_MAKE_DISPATCHER_H

#include <bigmath/simd/dispatch/macros_generated.h>
#include <bigmath/simd/detail/preprocessor/punctuation/remove_parens.hpp>
#include <bigmath/simd/detail/preprocessor/seq/for_each.hpp>
#include <bigmath/simd/detail/preprocessor/variadic/to_seq.hpp>

#if SIMD_EMIT_DISPATCHER
#include <bigmath/simd/detail/preprocessor/punctuation/comma_if.hpp>
#include <bigmath/simd/detail/preprocessor/seq/elem.hpp>
#include <bigmath/simd/detail/preprocessor/seq/for_each_i.hpp>
#include <bigmath/simd/detail/preprocessor/tuple/rem.hpp>
#include <bigmath/simd/dispatch/collect_macros_generated.h>

// When debugging this code, it's a good idea to familiarize yourself with
// advanced preprocessor techniques first. Several resources follow:
// http://jhnet.co.uk/articles/cpp_magic
// https://github.com/pfultz2/Cloak/wiki/C-Preprocessor-tricks,-tips,-and-idioms
// Some ideas have been taken from these pages.

// The simd library includes a partial copy of boost.preprocessor library
// with BOOST_ prefix replaced with SIMD_ and variadics support enabled
// unconditionally. If implementing new features, feel free to add any headers
// that are needed but are missing. In case a header becomes no longer used,
// please remove it from the repository.

// The implementation has been affected by the following MSVC preprocessor
// bugs / non-standard behavior:
//
// - MSVC treats expanded variadic arguments as single token in other function
// argument lists. SIMD_DETAIL_MSVC_DEFER_MACRO_ARGS has been used as a
// workaround in these cases.
//
// - MSVC does not accept empty token as valid argument in function macros. In
// cases when this matter, SIMD_EMPTY() was passed after the real
// arguments.
//
// - MSVC is eager to expand function macros before its arguments are fully
// expanded. This has been worked around with placing one or more
// SIMD_EMPTY between the function macro and its argument list to defer
// the expansion.
//
// - MSVC sometimes stops the expansion of macros even when the expansion should
// continue. This is worked around by wrapping the code in SIMD_EXPAND

#define SIMD_DETAIL_MSVC_DEFER_MACRO_ARGS(macro, args) macro args

#if ~SIMD_CONFIG_FLAGS() & SIMD_CONFIG_MSVC()
#define SIMD_DETAIL_IGNORE_PARENS(x) SIMD_EAT x
#else
#define SIMD_DETAIL_IGNORE_PARENS_DEFER(x) SIMD_EAT x
#define SIMD_DETAIL_IGNORE_PARENS(x) SIMD_DETAIL_IGNORE_PARENS_DEFER(x)
#endif

#define SIMD_DETAIL_EXTRACT_PARENS_IGNORE_REST(x) \
    SIMD_DETAIL_EXTRACT_PARENS_IGNORE_REST_STRIP_REST_DEFER(SIMD_DETAIL_EXTRACT_PARENS_IGNORE_REST_ADD_COMMA x, )

#if ~SIMD_CONFIG_FLAGS() & SIMD_CONFIG_MSVC()
#define SIMD_DETAIL_EXTRACT_PARENS_IGNORE_REST_STRIP_REST_DEFER(...) \
    SIMD_DETAIL_EXTRACT_PARENS_IGNORE_REST_STRIP_REST(__VA_ARGS__)

#define SIMD_DETAIL_EXTRACT_PARENS_IGNORE_REST_STRIP_REST(x, ...) SIMD_REM x
#else
#define SIMD_DETAIL_EXTRACT_PARENS_IGNORE_REST_STRIP_REST_DEFER(...) \
    SIMD_DETAIL_MSVC_DEFER_MACRO_ARGS(SIMD_DETAIL_EXTRACT_PARENS_IGNORE_REST_STRIP_REST, (__VA_ARGS__))

#define SIMD_DETAIL_EXTRACT_PARENS_IGNORE_REST_STRIP_REST(x, ...) SIMD_DETAIL_MSVC_DEFER_MACRO_ARGS(SIMD_REM, x)
#endif

#define SIMD_DETAIL_EXTRACT_PARENS_IGNORE_REST_ADD_COMMA(...) (__VA_ARGS__),

// We can't just use SIMD_DETAIL_EXTRACT_PARENS_IGNORE_REST or
// SIMD_DETAIL_EXTRACT_ARG_IMPL directly, because the argument list may be
// empty, so SIMD_DETAIL_EXTRACT_* may be invoked with the argument being
// empty token. The argument otherwise always starts with a parenthesis, so
// let's check that.
#define SIMD_DETAIL_EXTRACT_TYPE(T) \
    SIMD_IIF(SIMD_IS_BEGIN_PARENS(T), SIMD_DETAIL_EXTRACT_PARENS_IGNORE_REST, SIMD_EAT)(T)

#define SIMD_DETAIL_EXTRACT_ARG_IMPL(T) SIMD_REM T
#define SIMD_DETAIL_EXTRACT_ARG(T) SIMD_IIF(SIMD_IS_BEGIN_PARENS(T), SIMD_DETAIL_EXTRACT_ARG_IMPL, SIMD_EAT)(T)

#define SIMD_DETAIL_EXTRACT_FORWARD_IMPL(T) SIMD_EAT T
#define SIMD_DETAIL_EXTRACT_FORWARD(T) SIMD_IIF(SIMD_IS_BEGIN_PARENS(T), SIMD_DETAIL_EXTRACT_FORWARD_IMPL, SIMD_EAT)(T)

#define SIMD_DETAIL_TYPES_EACH(r, data, i, x) SIMD_COMMA_IF(i) SIMD_DETAIL_EXTRACT_TYPE(x)

#define SIMD_DETAIL_ARGS_EACH(r, data, i, x) SIMD_COMMA_IF(i) SIMD_DETAIL_EXTRACT_ARG(x)

#define SIMD_DETAIL_FORWARD_EACH(r, data, i, x) SIMD_COMMA_IF(i) SIMD_DETAIL_EXTRACT_FORWARD(x)

// The following 3 macros expand a given function argument list with the
// following format '(A) a, (B) b, (C) c' into different results.

// Will expand to 'A, B, C'
#define SIMD_DETAIL_TYPES(args) SIMD_SEQ_FOR_EACH_I(SIMD_DETAIL_TYPES_EACH, data, SIMD_VARIADIC_TO_SEQ args)

// Will expand to 'A a, B b, C c'
#define SIMD_DETAIL_ARGS(args) SIMD_SEQ_FOR_EACH_I(SIMD_DETAIL_ARGS_EACH, data, SIMD_VARIADIC_TO_SEQ args)

// Will expand to 'a, b, c'
#define SIMD_DETAIL_FORWARD(args) SIMD_SEQ_FOR_EACH_I(SIMD_DETAIL_FORWARD_EACH, data, SIMD_VARIADIC_TO_SEQ args)

// Will expand to 1 if argument contains SIMD_PROBE macro anywhere, 0 otherwise
#if ~SIMD_CONFIG_FLAGS() & SIMD_CONFIG_MSVC()
#define SIMD_PROBE_TO_BOOL(...) SIMD_PROBE_TO_BOOL_I(__VA_ARGS__, 0)

#else
// Note that we can't use SIMD_DETAIL_MSVC_DEFER_MACRO_ARGS because this
// would interfere with the expansion of that macro itself

#define SIMD_PROBE_TO_BOOL(...) SIMD_PROBE_TO_BOOL_MSVC_DEFER(SIMD_PROBE_TO_BOOL_I, (__VA_ARGS__, 0))
#define SIMD_PROBE_TO_BOOL_MSVC_DEFER(macro, args) macro args
#endif

#define SIMD_PROBE_TO_BOOL_I(n1, n2, ...) n2
#define SIMD_PROBE() ~, 1, 0

// Given a single argument R, potentially consisting of multiple tokens,
// expands to SIMD_PROBE() if R is empty, otherwise expands to nothing.
#if ~SIMD_CONFIG_FLAGS() & SIMD_CONFIG_MSVC()
#define SIMD_DETAIL_PROBE_IF_VOID_EMPTY(R) \
    SIMD_IIF(SIMD_PROBE_TO_BOOL(SIMD_DETAIL_IS_EMPTY_PROBE R()), SIMD_PROBE, SIMD_EMPTY)()
#else
#define SIMD_DETAIL_PROBE_IF_VOID_EMPTY(R) \
    SIMD_IIF SIMD_EMPTY()(SIMD_PROBE_TO_BOOL(SIMD_DETAIL_IS_EMPTY_PROBE R()), SIMD_PROBE, SIMD_EMPTY)()
#endif

#define SIMD_DETAIL_IS_EMPTY_PROBE(...) SIMD_PROBE()

// Given a single argument R, potentially consisting of multiple tokens or
// parenthesized token groups, expands to nothing if R starts with a parenthesis.
// Otherwise expands to SIMD_DETAIL_PROBE_IF_VOID_EMPTY with R
// passed as an argument.
#if ~SIMD_CONFIG_FLAGS() & SIMD_CONFIG_MSVC()
#define SIMD_DETAIL_PROBE_IF_VOID_1PAREN(R) \
    SIMD_IIF(SIMD_IS_BEGIN_PARENS(R), SIMD_EAT, SIMD_DETAIL_PROBE_IF_VOID_EMPTY)(R)
#else
// R might be empty token, thus workarounds are needed (see top of the file)

#define SIMD_DETAIL_PROBE_IF_VOID_1PAREN(R) \
    SIMD_IIF(SIMD_IS_BEGIN_PARENS(R), SIMD_EAT, SIMD_DETAIL_PROBE_IF_VOID_EMPTY)(R SIMD_EMPTY())
#endif

// Given a single argument R, potentially consisting of multiple tokens or
// parenthesized token groups, expands to nothing if R starts with a 'void'
// token. Otherwise expands to SIMD_DETAIL_PROBE_IF_VOID_1PAREN
// passing R with the first 'void' token removed as an argument.

#if ~SIMD_CONFIG_FLAGS() & SIMD_CONFIG_MSVC()
#define SIMD_DETAIL_PROBE_IF_VOID_1PARAM(R)                                                                         \
    SIMD_IIF(SIMD_PROBE_TO_BOOL(SIMD_DETAIL_STARTS_WITH_VOID_PROBE(R)), SIMD_DETAIL_PROBE_IF_VOID_1PAREN, SIMD_EAT) \
    (SIMD_CAT(SIMD_DETAIL_STARTS_WITH_VOID_STRIP_, R))
#else
// SIMD_IIF is expanded one expansion too early and R might be empty
// token, thus workarounds are needed (see top of the file)

#define SIMD_DETAIL_PROBE_IF_VOID_1PARAM(R)                                                       \
    SIMD_IIF SIMD_EMPTY()(SIMD_PROBE_TO_BOOL(SIMD_DETAIL_STARTS_WITH_VOID_PROBE(R SIMD_EMPTY())), \
                          SIMD_DETAIL_PROBE_IF_VOID_1PAREN,                                       \
                          SIMD_EAT)(SIMD_CAT(SIMD_DETAIL_STARTS_WITH_VOID_STRIP_, R) SIMD_EMPTY SIMD_EMPTY()())
#endif

#define SIMD_DETAIL_STARTS_WITH_VOID_CHECK_void SIMD_PROBE()
#define SIMD_DETAIL_STARTS_WITH_VOID_STRIP_void
#define SIMD_DETAIL_STARTS_WITH_VOID_PROBE(R) \
    SIMD_DETAIL_STARTS_WITH_VOID_PROBE_I(SIMD_DETAIL_STARTS_WITH_VOID_CHECK_##R)
#define SIMD_DETAIL_STARTS_WITH_VOID_PROBE_I(R) R

// Given a parenthesized list of arguments R, expands to nothing if R contains
// more than one argument. Otherwise expands SIMD_DETAIL_PROBE_IF_VOID_1PARAM
// passing R with removed outer parentheses
#define SIMD_DETAIL_PROBE_IF_VOID(R) \
    SIMD_IF(SIMD_DEC(SIMD_VARIADIC_SIZE(SIMD_REM R)), SIMD_EAT, SIMD_DETAIL_PROBE_IF_VOID_1PARAM)(SIMD_REMOVE_PARENS(R))

// Given a parenthesized list of arguments R, expands to nothing if R is
// parenthesized void token, otherwise expands to return token
#if ~SIMD_CONFIG_FLAGS() & SIMD_CONFIG_MSVC()

#define SIMD_DETAIL_RETURN_IF_NOT_VOID(R) \
    SIMD_IIF(SIMD_PROBE_TO_BOOL(SIMD_DETAIL_PROBE_IF_VOID(R)), SIMD_EMPTY, SIMD_DETAIL_RETURN_TOKEN)()
#else
// The following problems have been worked around on MSVC (see top of the
// file):
//  - SIMD_IIF is expanded two expansions too early
//  - the result of SIMD_DETAIL_PROBE_IF_VOID is not passed back to
// SIMD_PROBE_TO_BOOL properly
//  - the final SIMD_IIF is not expanded for some reason.

#define SIMD_DETAIL_RETURN_IF_NOT_VOID(R)                                                                             \
    SIMD_EXPAND(SIMD_IIF SIMD_EMPTY SIMD_EMPTY()()(SIMD_DETAIL_MSVC_DEFER_MACRO_ARGS(SIMD_PROBE_TO_BOOL,              \
                                                                                     (SIMD_DETAIL_PROBE_IF_VOID(R))), \
                                                   SIMD_EMPTY,                                                        \
                                                   SIMD_DETAIL_RETURN_TOKEN)())
#endif

#define SIMD_DETAIL_RETURN_TOKEN() return

#define SIMD_DETAIL_MAKE_DISPATCHER_IMPL(TEMPLATE_PREFIX, TEMPLATE_ARGS, R, NAME, ARGS)                     \
                                                                                                            \
    SIMD_DISPATCH_DECLARE_FUNCTIONS(                                                                        \
        (SIMD_REMOVE_PARENS(TEMPLATE_PREFIX) SIMD_REMOVE_PARENS(R) NAME(SIMD_DETAIL_TYPES(ARGS))))          \
                                                                                                            \
    SIMD_REMOVE_PARENS(TEMPLATE_PREFIX)                                                                     \
    SIMD_REMOVE_PARENS(R) NAME(SIMD_DETAIL_ARGS(ARGS)) {                                                    \
        using FunPtr = SIMD_REMOVE_PARENS(R) (*)(SIMD_DETAIL_TYPES(ARGS));                                  \
        static FunPtr selected = nullptr;                                                                   \
        if (selected == nullptr) {                                                                          \
            ::simd::detail::FnVersion versions[SIMD_DISPATCH_MAX_ARCHS] = {};                               \
            SIMD_DISPATCH_COLLECT_FUNCTIONS(versions, (NAME SIMD_REMOVE_PARENS(TEMPLATE_ARGS)), FunPtr)     \
            ::simd::detail::FnVersion version =                                                             \
                ::simd::detail::select_version_any(versions, SIMD_DISPATCH_MAX_ARCHS, SIMD_USER_ARCH_INFO); \
            selected = reinterpret_cast<FunPtr>(version.fun_ptr);                                           \
        }                                                                                                   \
        SIMD_DETAIL_RETURN_IF_NOT_VOID(R) selected(SIMD_DETAIL_FORWARD(ARGS));                              \
    }

#define SIMD_DETAIL_IGNORE_PARENS2(x) SIMD_DETAIL_IGNORE_PARENS(SIMD_DETAIL_IGNORE_PARENS(x))

#define SIMD_DETAIL_IGNORE_PARENS3(x) SIMD_DETAIL_IGNORE_PARENS(SIMD_DETAIL_IGNORE_PARENS(SIMD_DETAIL_IGNORE_PARENS(x)))

#define SIMD_DETAIL_IGNORE_PARENS4(x) \
    SIMD_DETAIL_IGNORE_PARENS(SIMD_DETAIL_IGNORE_PARENS(SIMD_DETAIL_IGNORE_PARENS(SIMD_DETAIL_IGNORE_PARENS(x))))

// SIMD_SEQ_ELEM does not work with sequence elements containing commas,
// so we use a workaround
#define SIMD_DETAIL_MAKE_DISPATCHER1(DESC) SIMD_ERROR_INCORRECT_NUMBER_OF_ARGUMENTS
#define SIMD_DETAIL_MAKE_DISPATCHER2(DESC) SIMD_ERROR_INCORRECT_NUMBER_OF_ARGUMENTS
#define SIMD_DETAIL_MAKE_DISPATCHER3(DESC)                                                                    \
    SIMD_DETAIL_MAKE_DISPATCHER_IMPL((),                                                                      \
                                     (),                                                                      \
                                     (SIMD_DETAIL_EXTRACT_PARENS_IGNORE_REST(DESC)),                          \
                                     SIMD_DETAIL_EXTRACT_PARENS_IGNORE_REST(SIMD_DETAIL_IGNORE_PARENS(DESC)), \
                                     (SIMD_DETAIL_EXTRACT_PARENS_IGNORE_REST(SIMD_DETAIL_IGNORE_PARENS2(DESC))))

#define SIMD_DETAIL_MAKE_DISPATCHER4(DESC) SIMD_ERROR_INCORRECT_NUMBER_OF_ARGUMENTS
#define SIMD_DETAIL_MAKE_DISPATCHER5(DESC)                                                                       \
    SIMD_DETAIL_MAKE_DISPATCHER_IMPL((SIMD_DETAIL_EXTRACT_PARENS_IGNORE_REST(DESC)),                             \
                                     (SIMD_DETAIL_EXTRACT_PARENS_IGNORE_REST(SIMD_DETAIL_IGNORE_PARENS(DESC))),  \
                                     (SIMD_DETAIL_EXTRACT_PARENS_IGNORE_REST(SIMD_DETAIL_IGNORE_PARENS2(DESC))), \
                                     SIMD_DETAIL_EXTRACT_PARENS_IGNORE_REST(SIMD_DETAIL_IGNORE_PARENS3(DESC)),   \
                                     (SIMD_DETAIL_EXTRACT_PARENS_IGNORE_REST(SIMD_DETAIL_IGNORE_PARENS4(DESC))))


#define SIMD_DETAIL_MAKE_DISPATCHER6(DESC) SIMD_ERROR_INCORRECT_NUMBER_OF_ARGUMENTS
#define SIMD_DETAIL_MAKE_DISPATCHER7(DESC) SIMD_ERROR_INCORRECT_NUMBER_OF_ARGUMENTS

/** Builds a dispatcher for a specific non-member function. The same macro is
    used for functions with or without return value, with different parameter
    counts and for template functions.

    The function accepts a sequence of 3 or 5 parenthesized token groups. Each
    group conveys the following information:
     - (optional) the full template prefix, e.g. (template<class T>)
     - (optional) the template argument list enclosed in brackets, e.g. (<T,U>)
     - the return type, e.g. (void), or (float)
     - the function name, e.g. (my_function)
     - comma separated list of function arguments. Each argument is specified as
        a parenthesized type name and argument name which follows immediately.
        For example ((float) x, (int) y, (std::pair<int, int>) z).

    The following examples show several ways to invoke the
    SIMD_MAKE_DISPATCHER macro:

    SIMD_MAKE_DISPATCHER((void)(my_function1)())
    SIMD_MAKE_DISPATCHER((void)(my_function1)((int) x, (float)z))
    SIMD_MAKE_DISPATCHER((int)(my_function1)((int) x, (float)z))
    SIMD_MAKE_DISPATCHER((template<class A, class B>)(<A,B>)(A)(my_function1)())
    SIMD_MAKE_DISPATCHER((template<class A, class B>)(<A,B>)(A)(my_function1)((B) x, (B)z))

    SIMD_ARCH_NAMESPACE::NAME (where NAME refers to the name of the function
    supplied to the SIMD_MAKE_DISPATCHER macro) must refer to the function to
    be disptached relative to the namespace in which the SIMD_MAKE_DISPATCHER
    macro is used in. That is, the macro must be used in a namespace one level
    up than the dispatched function, and that namespace must be
    SIMD_ARCH_NAMESPACE.

    The return and parameter types must be exactly the same as those of the
    function to be dispatched. The dispatched function may be overloaded.

    When dispatching function templates, each used template must be explicitly
    dispatched in all architecture-specific compilation units. For example,
    when using simd_multiarch (see cmake/SIMDMultiArch.cmake), these
    instantiations must be defined in SRC_FILE source file.

    The macro defines a function with the same signature as the dispatched
    function in the namespace the macro is used. The body of that function
    implements the dispatch mechanism.

    The dispatch functions check the enabled instruction set and select the
    best function on first call. The initialization does not introduce race
    conditions when done concurrently.

    The generated dispatching code links to all versions of the dispatched
    function statically, so techniques to prevent linkers from stripping
    unreferenced object files are not needed.
*/
#define SIMD_MAKE_DISPATCHER(DESC) SIMD_CAT(SIMD_DETAIL_MAKE_DISPATCHER, SIMD_SEQ_SIZE(DESC))(DESC)
#else // #if SIMD_EMIT_DISPATCHER
#define SIMD_MAKE_DISPATCHER(DESC)
#endif

#define SIMD_DETAIL_SIGNATURE_EACH(r, data, x) SIMD_REMOVE_PARENS(x);
#define SIMD_DETAIL_SIGNATURES(signatures) \
    SIMD_SEQ_FOR_EACH(SIMD_DETAIL_SIGNATURE_EACH, data, SIMD_VARIADIC_TO_SEQ signatures)

#if SIMD_EMIT_DISPATCHER
/** Defines a one or more template instantiations for a dispatcher. Accepts one
    or more parenthesized token groups separated by commas defining one or more
    full template instantiations. For example:
    SIMD_INSTANTIATE_DISPATCHER((template void foo<int>(int x))

    or

    SIMD_INSTANTIATE_DISPATCHER(
        (template void foo<int>(int x)),
        (template void foo<char>(char x))
    )

    The macro forces instantiation of the dispatch function defined by the
    SIMD_MAKE_DISPATCHER macro and also of the functions referenced by the
    dispatcher function. The latter is necessary because the dispatcher is
    compiled into a only single object file out of the set of multiversioned
    object files. The referenced functions will be instantiated in all of them.
*/
// Implementation note: we can't accept the signatures as a sequence, e.g.
// (a)(b)(c), because SIMD_SEQ_FOR_EACH does not support sequence elements
// containing commas at the top level
#define SIMD_INSTANTIATE_DISPATCHER(...)      \
    SIMD_DETAIL_SIGNATURES((__VA_ARGS__))     \
    namespace SIMD_ARCH_NAMESPACE {           \
        SIMD_DETAIL_SIGNATURES((__VA_ARGS__)) \
    }
#else // SIMD_EMIT_DISPATCHER
#define SIMD_INSTANTIATE_DISPATCHER(...)      \
    namespace SIMD_ARCH_NAMESPACE {           \
        SIMD_DETAIL_SIGNATURES((__VA_ARGS__)) \
    }
#endif

#endif // DISPATCH_MAKE_DISPATCHER_H
