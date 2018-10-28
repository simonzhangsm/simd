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

import fnmatch
import re
import os
import sys
import shutil
import urllib.parse

# copy the source tree
os.system('rm -rf output/reference')
os.system('mkdir -p output/reference')
os.system('cp -r reference/* output/reference ')

# find files that need to be preprocessed
html_files = []
for root, dirnames, filenames in os.walk('output/reference/'):
    for filename in fnmatch.filter(filenames, '*.html'):
        html_files.append(os.path.join(root, filename))

# clean the html files
for fn in html_files:
    f = open(fn, "r")
    text = f.read()
    f.close()

    f = open(fn, "w")
    f.write(text)
    f.close()

    tmpfile = fn + '.tmp';
    ret = os.system('xsltproc --novalid --html --encoding UTF-8 preprocess.xsl "' + fn + '" > "' + tmpfile + '"')
    if ret != 0:
        print("FAIL: " + fn)
        continue
    os.system('mv "' + tmpfile + '" "' + fn + '"')


