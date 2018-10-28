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

import re

''' Prints a template substituting the given variables with given replacements.
    The substitution variables in template should be surrounded by $ characters,
    e.g. $variable$. The vars parameter must be a dictionary mapping variable
    names to replacement values.

    One special variable is defined: "n" ($n$ in the template). It is replaced
    by a backslash at 80th column by stripping or padding whitespace as
    required.
'''
def output_template(template, vars):
    text = template
    for var in vars:
        text = text.replace('$'+var+'$', vars[var])

    # make the position of the backslash fixed
    lines = text.split('\n')
    text = []
    for line in lines:
        line = re.sub(' *\$n\$', '$n$', line)
        padlen = 80 + 3 - 2 - len(line)
        pad = ''
        if padlen > 0:
            pad = ' ' * padlen
        line = line.replace('$n$', pad + '\\')
        text.append(line)

    text = '\n'.join(text)
    print(text)
