#!/usr/bin/env python2

#/**********************************************************************
# * BIGMATH INSIGHT CONFIDENTIAL
# *
# * Copyright (C) 2016-2018 BIGMATH CORPORATION, All Rights Reserved.
# *
# * @Author: Simon Zhang on 19 Oct 2018
# * @EMail: simon.zhangsm@hotmail.com
# * @Version: $SIMD_LIB_VERSION
# *
# * These source codes are subject to the terms and conditions defined
# * in 'LICENSE', which is part of this source code package. Write to
# * LICENSE@BIGMATH.COM for more authorization requirements, or obtain
# * an entire copy of license agreement at http://bigmath.com/license.
# *
# * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
# * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# * **********************************************************************/

# Generates the simd/dispatch/collect_macros_generated.h file
# Use as $ ./tools/gen_dispatcher_collect_macros.py > simd/dispatch/collect_macros_generated.h

from gen_common import output_template

num_archs = 15

single_arch_template = '''
#ifdef SIMD_DISPATCH_ARCH$num$
    #define SIMD_ARCH_LIST SIMD_DISPATCH_ARCH$num$
    #include <bigmath/simd/detail/preprocess_single_arch.h>

    // Use the results of preprocess_single_arch.h to define
    // SIMD_DISPATCH_$num$_NAMESPACE

    #if SIMD_ARCH_NS_USE_NULL
    #define SIMD_DISPATCH_$num$_NS_ID_NULL SIMD_INSN_ID_NULL
    #else
    #define SIMD_DISPATCH_$num$_NS_ID_NULL
    #endif
    
    #if SIMD_ARCH_NS_USE_SSE2
    #define SIMD_DISPATCH_$num$_NS_ID_SSE2 SIMD_INSN_ID_SSE2
    #else
    #define SIMD_DISPATCH_$num$_NS_ID_SSE2
    #endif
    
    #if SIMD_ARCH_NS_USE_SSE3
    #define SIMD_DISPATCH_$num$_NS_ID_SSE3 SIMD_INSN_ID_SSE3
    #else
    #define SIMD_DISPATCH_$num$_NS_ID_SSE3
    #endif
    
    #if SIMD_ARCH_NS_USE_SSSE3
    #define SIMD_DISPATCH_$num$_NS_ID_SSSE3 SIMD_INSN_ID_SSSE3
    #else
    #define SIMD_DISPATCH_$num$_NS_ID_SSSE3
    #endif
    
    #if SIMD_ARCH_NS_USE_SSE4_1
    #define SIMD_DISPATCH_$num$_NS_ID_SSE4_1 SIMD_INSN_ID_SSE4_1
    #else
    #define SIMD_DISPATCH_$num$_NS_ID_SSE4_1
    #endif
    
    #if SIMD_ARCH_NS_USE_SSE4_2
    #define SIMD_DISPATCH_$num$_NS_ID_SSE4_2 SIMD_INSN_ID_SSE4_2
    #else
    #define SIMD_DISPATCH_$num$_NS_ID_SSE4_2
    #endif
    
    #if SIMD_ARCH_NS_USE_SSE4A
    #define SIMD_DISPATCH_$num$_NS_ID_SSE4A SIMD_INSN_ID_SSE4A
    #else
    #define SIMD_DISPATCH_$num$_NS_ID_SSE4A
    #endif
    
    #if SIMD_ARCH_NS_USE_POPCNT_INSN
    #define SIMD_DISPATCH_$num$_NS_ID_POPCNT_INSN SIMD_INSN_ID_POPCNT_INSN
    #else
    #define SIMD_DISPATCH_$num$_NS_ID_POPCNT_INSN
    #endif
    
    #if SIMD_ARCH_NS_USE_AVX
    #define SIMD_DISPATCH_$num$_NS_ID_AVX SIMD_INSN_ID_AVX
    #else
    #define SIMD_DISPATCH_$num$_NS_ID_AVX
    #endif
    
    #if SIMD_ARCH_NS_USE_AVX2
    #define SIMD_DISPATCH_$num$_NS_ID_AVX2 SIMD_INSN_ID_AVX2
    #else
    #define SIMD_DISPATCH_$num$_NS_ID_AVX2
    #endif
    
    #if SIMD_ARCH_NS_USE_FMA3
    #define SIMD_DISPATCH_$num$_NS_ID_FMA3 SIMD_INSN_ID_FMA3
    #else
    #define SIMD_DISPATCH_$num$_NS_ID_FMA3
    #endif
    
    #if SIMD_ARCH_NS_USE_FMA4
    #define SIMD_DISPATCH_$num$_NS_ID_FMA4 SIMD_INSN_ID_FMA4
    #else
    #define SIMD_DISPATCH_$num$_NS_ID_FMA4
    #endif
    
    #if SIMD_ARCH_NS_USE_XOP
    #define SIMD_DISPATCH_$num$_NS_ID_XOP SIMD_INSN_ID_XOP
    #else
    #define SIMD_DISPATCH_$num$_NS_ID_XOP
    #endif
    
    #if SIMD_ARCH_NS_USE_AVX512F
    #define SIMD_DISPATCH_$num$_NS_ID_AVX512F SIMD_INSN_ID_AVX512F
    #else
    #define SIMD_DISPATCH_$num$_NS_ID_AVX512F
    #endif
    
    #if SIMD_ARCH_NS_USE_AVX512BW
    #define SIMD_DISPATCH_$num$_NS_ID_AVX512BW SIMD_INSN_ID_AVX512BW
    #else
    #define SIMD_DISPATCH_$num$_NS_ID_AVX512BW
    #endif
    
    #if SIMD_ARCH_NS_USE_AVX512DQ
    #define SIMD_DISPATCH_$num$_NS_ID_AVX512DQ SIMD_INSN_ID_AVX512DQ
    #else
    #define SIMD_DISPATCH_$num$_NS_ID_AVX512DQ
    #endif
    
    #if SIMD_ARCH_NS_USE_AVX512VL
    #define SIMD_DISPATCH_$num$_NS_ID_AVX512VL SIMD_INSN_ID_AVX512VL
    #else
    #define SIMD_DISPATCH_$num$_NS_ID_AVX512VL
    #endif
    
    #if SIMD_ARCH_NS_USE_NEON
    #define SIMD_DISPATCH_$num$_NS_ID_NEON SIMD_INSN_ID_NEON
    #else
    #define SIMD_DISPATCH_$num$_NS_ID_NEON
    #endif
    
    #if SIMD_ARCH_NS_USE_NEON_FLT_SP
    #define SIMD_DISPATCH_$num$_NS_ID_NEON_FLT_SP SIMD_INSN_ID_NEON_FLT_SP
    #else
    #define SIMD_DISPATCH_$num$_NS_ID_NEON_FLT_SP
    #endif
    
    #if SIMD_ARCH_NS_USE_MSA
    #define SIMD_DISPATCH_$num$_NS_ID_MSA SIMD_INSN_ID_MSA
    #else
    #define SIMD_DISPATCH_$num$_NS_ID_MSA
    #endif
    
    #if SIMD_ARCH_NS_USE_ALTIVEC
    #define SIMD_DISPATCH_$num$_NS_ID_ALTIVEC SIMD_INSN_ID_ALTIVEC
    #else
    #define SIMD_DISPATCH_$num$_NS_ID_ALTIVEC
    #endif
    
    #if SIMD_ARCH_NS_USE_VSX_206
    #define SIMD_DISPATCH_$num$_NS_ID_VSX_206 SIMD_INSN_ID_VSX_206
    #else
    #define SIMD_DISPATCH_$num$_NS_ID_VSX_206
    #endif
    
    #if SIMD_ARCH_NS_USE_VSX_207
    #define SIMD_DISPATCH_$num$_NS_ID_VSX_207 SIMD_INSN_ID_VSX_207
    #else
    #define SIMD_DISPATCH_$num$_NS_ID_VSX_207
    #endif

    #define SIMD_DISPATCH_$num$_NAMESPACE SIMD_PASTE24(arch,              $n$
        SIMD_DISPATCH_$num$_NS_ID_NULL,                                   $n$
        SIMD_DISPATCH_$num$_NS_ID_SSE2,                                   $n$
        SIMD_DISPATCH_$num$_NS_ID_SSE3,                                   $n$
        SIMD_DISPATCH_$num$_NS_ID_SSSE3,                                  $n$
        SIMD_DISPATCH_$num$_NS_ID_SSE4_1,                                 $n$
        SIMD_DISPATCH_$num$_NS_ID_SSE4_2,                                 $n$
        SIMD_DISPATCH_$num$_NS_ID_SSE4A,                                  $n$
        SIMD_DISPATCH_$num$_NS_ID_POPCNT_INSN,                            $n$
        SIMD_DISPATCH_$num$_NS_ID_AVX,                                    $n$
        SIMD_DISPATCH_$num$_NS_ID_AVX2,                                   $n$
        SIMD_DISPATCH_$num$_NS_ID_AVX512F,                                $n$
        SIMD_DISPATCH_$num$_NS_ID_AVX512BW,                               $n$
        SIMD_DISPATCH_$num$_NS_ID_AVX512DQ,                               $n$
        SIMD_DISPATCH_$num$_NS_ID_AVX512VL,                               $n$
        SIMD_DISPATCH_$num$_NS_ID_FMA3,                                   $n$
        SIMD_DISPATCH_$num$_NS_ID_FMA4,                                   $n$
        SIMD_DISPATCH_$num$_NS_ID_XOP,                                    $n$
        SIMD_DISPATCH_$num$_NS_ID_NEON,                                   $n$
        SIMD_DISPATCH_$num$_NS_ID_NEON_FLT_SP,                            $n$
        SIMD_DISPATCH_$num$_NS_ID_MSA,                                    $n$
        SIMD_DISPATCH_$num$_NS_ID_ALTIVEC,                                $n$
        SIMD_DISPATCH_$num$_NS_ID_VSX_206,                                $n$
        SIMD_DISPATCH_$num$_NS_ID_VSX_207)

    #define SIMD_ARCH_THIS_COMPILE_ARCH_NAMESPACE SIMD_DISPATCH_$num$_NAMESPACE
    #define SIMD_ARCH_THIS_COMPILE_ARCH_FOR_DISPATCH 1
    #include <bigmath/simd/dispatch/preprocess_single_compile_arch.h>
    #undef SIMD_ARCH_THIS_COMPILE_ARCH_FOR_DISPATCH
    #undef SIMD_ARCH_THIS_COMPILE_ARCH_NAMESPACE

    #define SIMD_DISPATCH_$num$_FN_REGISTER(ARRAY,NAME,FUN_TYPE)                                        $n$
        {   /* the following will fail if the overload is not available */                              $n$
            FUN_TYPE fun_ptr = &SIMD_DISPATCH_$num$_NAMESPACE::SIMD_REMOVE_PARENS(NAME);                $n$
            ARRAY[$num$-1] = ::simd::SIMD_DISPATCH_$num$_NAMESPACE::detail::create_fn_version(fun_ptr); $n$
        }

    #define SIMD_DISPATCH_$num$_FN_DECLARE(SIGNATURE)                     $n$
        namespace SIMD_DISPATCH_$num$_NAMESPACE {                         $n$
            SIMD_REMOVE_PARENS(SIGNATURE);                                $n$
        }
    #undef SIMD_ARCH_LIST
#else
    #define SIMD_DISPATCH_$num$_FN_REGISTER(ARRAY,NAME,FUN_TYPE)
    #define SIMD_DISPATCH_$num$_FN_DECLARE(SIGNATURE)
#endif'''

single_fn_register_template = '    SIMD_DISPATCH_$num$_FN_REGISTER(ARRAY,NAME,FUN_TYPE)   $n$'
single_fn_declare_template = '''\
        SIMD_DISPATCH_$num$_FN_DECLARE(SIGNATURE)                                         $n$'''

# print the actual file

print('''/**********************************************************************
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


// This file is generated automatically. See tools/gen_dispatcher_collect_macros.py

#ifndef DISPATCH_COLLECT_MACROS_GENERATED_H
#define DISPATCH_COLLECT_MACROS_GENERATED_H

#ifndef SIMD_H
    #error "This file must be included through simd.h"
#endif

// We rely on setup_arch.h being included before this file to undefine
// all SIMD_ARCH_* macros
#include <bigmath/simd/setup_arch.h>

#if SIMD_EMIT_DISPATCHER
#include <bigmath/simd/detail/preprocessor/punctuation/remove_parens.hpp>
''')

print('#define SIMD_DISPATCH_MAX_ARCHS ' + str(num_archs) + '\n')

for i in range(0, num_archs):
    vars = { 'num' : str(i) }
    output_template(single_arch_template, vars)

print('''

#define SIMD_DISPATCH_DECLARE_FUNCTIONS(SIGNATURE)                        \\''')
for i in range(0, num_archs):
    vars = { 'num' : str(i) }
    output_template(single_fn_declare_template, vars)

print('''

#define SIMD_DISPATCH_COLLECT_FUNCTIONS(ARRAY,NAME,FUN_TYPE)              \\''')
for i in range(0, num_archs):
    vars = { 'num' : str(i) }
    output_template(single_fn_register_template, vars)

print('''

#endif // SIMD_EMIT_DISPATCHER
#endif
''')
