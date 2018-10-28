#!/usr/bin/env python3

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

# Generates the simd/dispatch/macros_generated.h file
# Use as $ ./tools/gen_dispatcher_macros.py > simd/dispatch/macros_generated.h

from gen_common import output_template

num_args = 10

''' The following defines a template for each macro. $xxx$ are template
    parameters that are later replaced in output_template function.

    $macro_end$ - last part of the name of the macro.
    $ret_param$ - the return type macro parameter, with a preceding comma, if
        defined.
    $type_params$ - the same as $types$, just contains a preceding comma, if
        not empty.
    $ret_type$ - the return type -- 'void' if $ret_param$ not defined,
        $ret_param$ minus the preceding comma otherwise.
    $types_vars$ - same as $types$, just parenthesized type is followed with
        some identifier
    $n$ - identifies the backslash character
'''

# Define the dispatched function only for NULL architecture to avoid defining
# the same non-inline function several times.

redirect_template = '''
#define SIMD_MAKE_DISPATCHER_$macro_end$(NAME$ret_param$$type_params$)    $n$
    SIMD_MAKE_DISPATCHER(($ret_type$)(NAME)($type_arg_params$))'''

# Returns a string T1,T2,T3,...,T_num
def get_Tn_list(num):
    if num == 0:
        return ''
    identifiers = [ 'T{0}'.format(i+1) for i in range(num) ]
    return ','.join(identifiers)

# Returns a string (T1) a1, (T2) a2, (T3) a3,...,(T_num) a_num
def get_Tn_an_list(num):
    if num == 0:
        return ''
    identifiers = [ '(T{0}) a{0}'.format(i+1) for i in range(num) ]
    return ','.join(identifiers)

# Prints the macros given a template
def do_template(template):
    # void, no callback
    for i in range(0,num_args):
        Tn = get_Tn_list(i)
        Tn_an = get_Tn_an_list(i)

        vars = {}
        vars['macro_end'] = 'VOID' + str(i)
        vars['ret_param'] = ''
        vars['type_params'] = '' if i == 0 else ',' + Tn
        vars['ret_type'] = 'void'
        vars['types'] = Tn
        vars['type_arg_params'] = Tn_an
        output_template(template, vars)

    # R, no callback
    for i in range(0,num_args):
        Tn = get_Tn_list(i)
        Tn_an = get_Tn_an_list(i)

        vars = {}
        vars['macro_end'] = 'RET' + str(i)
        vars['ret_param'] = ',R'
        vars['type_params'] = '' if i == 0 else ',' + Tn
        vars['ret_type'] = 'R'
        vars['types'] = Tn
        vars['type_arg_params'] = Tn_an
        output_template(template, vars)

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
''')
do_template(redirect_template)
print('''

#endif
''')
