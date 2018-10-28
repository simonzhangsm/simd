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

#include <bigmath/simd/dispatch/arch.h>
#include <utility>

simd::Arch get_supported_arch(); // in main_dispatcher.cc
simd::Arch test_dispatcher_get_arch();

extern int g_test_dispatcher_val;
int test_dispatcher_old_ret0();
int test_dispatcher_old_ret1(int arg);
int test_dispatcher_old_ret2(int arg, int arg2);
int test_dispatcher_old_ret3(int arg, int arg2, int arg3);
int test_dispatcher_old_ret4(int arg, int arg2, int arg3, int arg4);

void test_dispatcher_old_void0();
void test_dispatcher_old_void1(int arg);
void test_dispatcher_old_void2(int arg, int arg2);
void test_dispatcher_old_void3(int arg, int arg2, int arg3);
void test_dispatcher_old_void4(int arg, int arg2, int arg3, int arg4);

int test_dispatcher_ret0();
int test_dispatcher_ret1(int arg);
int test_dispatcher_ret2(int arg, int arg2);
int test_dispatcher_ret3(int arg, int arg2, int arg3);
int test_dispatcher_ret4(int arg, int arg2, int arg3, int arg4);

void test_dispatcher_void0();
void test_dispatcher_void1(int arg);
void test_dispatcher_void2(int arg, int arg2);
void test_dispatcher_void3(int arg, int arg2, int arg3);
void test_dispatcher_void4(int arg, int arg2, int arg3, int arg4);

void *test_dispatcher_ret_voidptr(void *x);

void test_dispatcher_void_pair(const std::pair<int, int> &pair);
void test_dispatcher_void_pair2(const std::pair<int, int> &pair1, const std::pair<int, int> &pair2);

std::pair<int, int> test_dispatcher_ret_pair(const std::pair<int, int> &pair);
std::pair<int, int> test_dispatcher_ret_pair2(const std::pair<int, int> &pair1, const std::pair<int, int> &pair2);

template <class T> void test_dispatcher_void_template_pair(const std::pair<T, T> &pair);
template <class T> void test_dispatcher_void_template_pair2(const std::pair<T, T> &pair1, const std::pair<T, T> &pair2);

template <class T, class U> void test_dispatcher_void_template2_pair(const std::pair<T, U> &pair);
template <class T, class U>
void test_dispatcher_void_template2_pair2(const std::pair<T, U> &pair1, const std::pair<T, U> &pair2);

template <class T> std::pair<T, T> test_dispatcher_ret_template_pair(const std::pair<T, T> &pair);
template <class T>
std::pair<T, T> test_dispatcher_ret_template_pair2(const std::pair<T, T> &pair1, const std::pair<T, T> &pair2);

template <class T, class U> std::pair<T, U> test_dispatcher_ret_template2_pair(const std::pair<T, U> &pair);
template <class T, class U>
std::pair<T, U> test_dispatcher_ret_template2_pair2(const std::pair<T, U> &pair1, const std::pair<T, U> &pair2);

template <class T> void test_dispatcher_void_template_nondeductible();
template <class T, class U> void test_dispatcher_void_template2_nondeductible();

template <class T> std::pair<T, T> test_dispatcher_ret_template_nondeductible();
template <class T, class U> std::pair<T, U> test_dispatcher_ret_template2_nondeductible();
