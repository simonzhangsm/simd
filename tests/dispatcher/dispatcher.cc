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

#define SIMD_USER_ARCH_INFO get_supported_arch()
#include "dispatcher.h"
#include <bigmath/simd/simd.h>

namespace SIMD_ARCH_NAMESPACE {

simd::Arch test_dispatcher_get_arch()
{
    return simd::this_compile_arch();
}

int test_dispatcher1(int arg)
{
    return arg;
}

int test_dispatcher2(int arg, int arg2)
{
    return arg + arg2;
}

int test_dispatcher3(int arg, int arg2, int arg3)
{
    return arg + arg2 + arg3;
}

int test_dispatcher4(int arg, int arg2, int arg3, int arg4)
{
    return arg + arg2 + arg3 + arg4;
}

int test_dispatcher_old_ret0()
{
    return 42;
}

int test_dispatcher_old_ret1(int arg)
{
    return arg;
}

int test_dispatcher_old_ret2(int arg, int arg2)
{
    return arg + arg2;
}

int test_dispatcher_old_ret3(int arg, int arg2, int arg3)
{
    return arg + arg2 + arg3;
}

int test_dispatcher_old_ret4(int arg, int arg2, int arg3, int arg4)
{
    return arg + arg2 + arg3 + arg4;
}

void test_dispatcher_old_void0()
{
    g_test_dispatcher_val = 42;
}

void test_dispatcher_old_void1(int arg)
{
    g_test_dispatcher_val = arg;
}

void test_dispatcher_old_void2(int arg, int arg2)
{
    g_test_dispatcher_val = arg + arg2;
}

void test_dispatcher_old_void3(int arg, int arg2, int arg3)
{
    g_test_dispatcher_val = arg + arg2 + arg3;
}

void test_dispatcher_old_void4(int arg, int arg2, int arg3, int arg4)
{
    g_test_dispatcher_val = arg + arg2 + arg3 + arg4;
}

int test_dispatcher_ret0()
{
    return 42;
}

int test_dispatcher_ret1(int arg)
{
    return arg;
}

int test_dispatcher_ret2(int arg, int arg2)
{
    return arg + arg2;
}

int test_dispatcher_ret3(int arg, int arg2, int arg3)
{
    return arg + arg2 + arg3;
}

int test_dispatcher_ret4(int arg, int arg2, int arg3, int arg4)
{
    return arg + arg2 + arg3 + arg4;
}

void test_dispatcher_void0()
{
    g_test_dispatcher_val = 42;
}

void test_dispatcher_void1(int arg)
{
    g_test_dispatcher_val = arg;
}

void test_dispatcher_void2(int arg, int arg2)
{
    g_test_dispatcher_val = arg + arg2;
}

void test_dispatcher_void3(int arg, int arg2, int arg3)
{
    g_test_dispatcher_val = arg + arg2 + arg3;
}

void test_dispatcher_void4(int arg, int arg2, int arg3, int arg4)
{
    g_test_dispatcher_val = arg + arg2 + arg3 + arg4;
}

void* test_dispatcher_ret_voidptr(void* x)
{
    return x;
}

void test_dispatcher_void_pair(const std::pair<int, int>& pair)
{
    g_test_dispatcher_val = pair.first + pair.second;
}

void test_dispatcher_void_pair2(const std::pair<int, int>& pair1,
                                const std::pair<int, int>& pair2)
{
    g_test_dispatcher_val = pair1.first + pair1.second + pair2.first + pair2.second;
}

std::pair<int, int> test_dispatcher_ret_pair(const std::pair<int, int>& pair)
{
    return pair;
}

std::pair<int, int> test_dispatcher_ret_pair2(const std::pair<int, int>& pair1,
                                              const std::pair<int, int>& pair2)

{
    return std::make_pair(pair1.first + pair2.first, pair1.second + pair2.second);
}

template<class T>
void test_dispatcher_void_template_pair(const std::pair<T, T>& pair)
{
    g_test_dispatcher_val = pair.first + pair.second;
}

template<class T>
void test_dispatcher_void_template_pair2(const std::pair<T, T>& pair1,
                                         const std::pair<T, T>& pair2)
{
    g_test_dispatcher_val = pair1.first + pair1.second + pair2.first + pair2.second;
}

template<class T, class U>
void test_dispatcher_void_template2_pair(const std::pair<T, U>& pair)
{
    g_test_dispatcher_val = pair.first + pair.second;
}

template<class T, class U>
void test_dispatcher_void_template2_pair2(const std::pair<T, U>& pair1,
                                          const std::pair<T, U>& pair2)
{
    g_test_dispatcher_val = pair1.first + pair1.second + pair2.first + pair2.second;
}

template<class T>
std::pair<T, T> test_dispatcher_ret_template_pair(const std::pair<T, T>& pair)
{
    return pair;
}

template<class T>
std::pair<T, T> test_dispatcher_ret_template_pair2(const std::pair<T, T>& pair1,
                                                   const std::pair<T, T>& pair2)
{
    return std::make_pair(pair1.first + pair2.first, pair1.second + pair2.second);
}

template<class T, class U>
std::pair<T, U> test_dispatcher_ret_template2_pair(const std::pair<T, U>& pair)
{
    return pair;
}

template<class T, class U>
std::pair<T, U> test_dispatcher_ret_template2_pair2(const std::pair<T, U>& pair1,
                                                   const std::pair<T, U>& pair2)
{
    return std::make_pair(pair1.first + pair2.first, pair1.second + pair2.second);
}

template<class T>
void test_dispatcher_void_template_nondeductible()
{
    g_test_dispatcher_val = sizeof(T);
}

template<class T, class U>
void test_dispatcher_void_template2_nondeductible()
{
    g_test_dispatcher_val = sizeof(T) + sizeof(U);
}

template<class T>
std::pair<T, T> test_dispatcher_ret_template_nondeductible()
{
    return std::pair<T, T>(sizeof(T), sizeof(T));
}

template<class T, class U>
std::pair<T, U> test_dispatcher_ret_template2_nondeductible()
{
    return std::pair<T, U>(sizeof(T), sizeof(U));
}

} // namespace SIMD_ARCH_NAMESPACE

SIMD_MAKE_DISPATCHER_RET0(test_dispatcher_get_arch, simd::Arch)
SIMD_MAKE_DISPATCHER_RET0(test_dispatcher_old_ret0, int)
SIMD_MAKE_DISPATCHER_RET1(test_dispatcher_old_ret1, int, int)
SIMD_MAKE_DISPATCHER_RET2(test_dispatcher_old_ret2, int, int, int)
SIMD_MAKE_DISPATCHER_RET3(test_dispatcher_old_ret3, int, int, int, int)
SIMD_MAKE_DISPATCHER_RET4(test_dispatcher_old_ret4, int, int, int, int, int)

SIMD_MAKE_DISPATCHER_VOID0(test_dispatcher_old_void0)
SIMD_MAKE_DISPATCHER_VOID1(test_dispatcher_old_void1, int)
SIMD_MAKE_DISPATCHER_VOID2(test_dispatcher_old_void2, int, int)
SIMD_MAKE_DISPATCHER_VOID3(test_dispatcher_old_void3, int, int, int)
SIMD_MAKE_DISPATCHER_VOID4(test_dispatcher_old_void4, int, int, int, int)

SIMD_MAKE_DISPATCHER((int)(test_dispatcher_ret0)())
SIMD_MAKE_DISPATCHER((int)(test_dispatcher_ret1)((int) arg))
SIMD_MAKE_DISPATCHER((int)(test_dispatcher_ret2)((int) arg, (int) arg2))
SIMD_MAKE_DISPATCHER((int)(test_dispatcher_ret3)((int) arg, (int) arg2,
                                                   (int) arg3))
SIMD_MAKE_DISPATCHER((int)(test_dispatcher_ret4)((int) arg, (int) arg2,
                                                   (int) arg3, (int) arg4))

SIMD_MAKE_DISPATCHER((void)(test_dispatcher_void0)())
SIMD_MAKE_DISPATCHER((void)(test_dispatcher_void1)((int) arg))
SIMD_MAKE_DISPATCHER((void)(test_dispatcher_void2)((int) arg, (int) arg2))
SIMD_MAKE_DISPATCHER((void)(test_dispatcher_void3)((int) arg, (int) arg2,
                                                     (int) arg3))
SIMD_MAKE_DISPATCHER((void)(test_dispatcher_void4)((int) arg, (int) arg2,
                                                     (int) arg3, (int) arg4))

SIMD_MAKE_DISPATCHER((void*)(test_dispatcher_ret_voidptr)((void*) x))

SIMD_MAKE_DISPATCHER((void)(test_dispatcher_void_pair)
                       ((const std::pair<int, int>&) pair))
SIMD_MAKE_DISPATCHER((void)(test_dispatcher_void_pair2)
                       ((const std::pair<int, int>&) pair,
                        (const std::pair<int, int>&) pair2))

SIMD_MAKE_DISPATCHER((std::pair<int, int>)(test_dispatcher_ret_pair)
                       ((const std::pair<int, int>&) pair))
SIMD_MAKE_DISPATCHER((std::pair<int, int>)(test_dispatcher_ret_pair2)
                       ((const std::pair<int, int>&) pair,
                        (const std::pair<int, int>&) pair2))

SIMD_MAKE_DISPATCHER((template<class T>) (<T>)
                       (void) (test_dispatcher_void_template_pair)
                       ((const std::pair<T, T>&) pair))

SIMD_INSTANTIATE_DISPATCHER(
    (template void
        test_dispatcher_void_template_pair<int>(const std::pair<int, int>& pair)),
    (template void
        test_dispatcher_void_template_pair<char>(const std::pair<char, char>& pair))
)


SIMD_MAKE_DISPATCHER((template<class T>) (<T>)
                       (void) (test_dispatcher_void_template_pair2)
                       ((const std::pair<T, T>&) pair, (const std::pair<T, T>&) pair2))

SIMD_INSTANTIATE_DISPATCHER(
    (template void
        test_dispatcher_void_template_pair2<int>(const std::pair<int, int>& pair1,
                                                 const std::pair<int, int>& pair2)),
    (template void
        test_dispatcher_void_template_pair2<char>(const std::pair<char, char>& pair1,
                                                  const std::pair<char, char>& pair2))
)


SIMD_MAKE_DISPATCHER((template<class T, class U>) (<T, U>)
                       (void) (test_dispatcher_void_template2_pair)
                       ((const std::pair<T, U>&) pair))

SIMD_INSTANTIATE_DISPATCHER(
    (template void
        test_dispatcher_void_template2_pair<int, int>(const std::pair<int, int>& pair)),
    (template void
        test_dispatcher_void_template2_pair<char, int>(const std::pair<char, int>& pair)),
    (template void
        test_dispatcher_void_template2_pair<int, char>(const std::pair<int, char>& pair)),
    (template void
        test_dispatcher_void_template2_pair<char, char>(const std::pair<char, char>& pair))
)

SIMD_MAKE_DISPATCHER((template<class T, class U>) (<T, U>)
                       (void) (test_dispatcher_void_template2_pair2)
                       ((const std::pair<T, U>&) pair, (const std::pair<T, U>&) pair2))

SIMD_INSTANTIATE_DISPATCHER(
    (template void
        test_dispatcher_void_template2_pair2<int, int>(const std::pair<int, int>& pair1,
                                                       const std::pair<int, int>& pair2)),
    (template void
        test_dispatcher_void_template2_pair2<char, int>(const std::pair<char, int>& pair1,
                                                        const std::pair<char, int>& pair2)),
    (template void
        test_dispatcher_void_template2_pair2<int, char>(const std::pair<int, char>& pair1,
                                                        const std::pair<int, char>& pair2)),
    (template void
        test_dispatcher_void_template2_pair2<char, char>(const std::pair<char, char>& pair1,
                                                         const std::pair<char, char>& pair2))
)

SIMD_MAKE_DISPATCHER((template<class T>) (<T>)
                       (std::pair<T, T>) (test_dispatcher_ret_template_pair)
                       ((const std::pair<T, T>&) pair))

SIMD_INSTANTIATE_DISPATCHER(
    (template std::pair<int, int>
        test_dispatcher_ret_template_pair<int>(const std::pair<int, int>& pair)),
    (template std::pair<char, char>
        test_dispatcher_ret_template_pair<char>(const std::pair<char, char>& pair))
)

SIMD_MAKE_DISPATCHER((template<class T>) (<T>)
                       (std::pair<T, T>) (test_dispatcher_ret_template_pair2)
                       ((const std::pair<T, T>&) pair, (const std::pair<T, T>&) pair2))

SIMD_INSTANTIATE_DISPATCHER(
    (template std::pair<int, int>
        test_dispatcher_ret_template_pair2<int>(const std::pair<int, int>& pair1,
                                                const std::pair<int, int>& pair2)),
    (template std::pair<char, char>
        test_dispatcher_ret_template_pair2<char>(const std::pair<char, char>& pair1,
                                                 const std::pair<char, char>& pair2))
)

SIMD_MAKE_DISPATCHER((template<class T, class U>) (<T, U>)
                       (std::pair<T, U>) (test_dispatcher_ret_template2_pair)
                       ((const std::pair<T, U>&) pair))

SIMD_INSTANTIATE_DISPATCHER(
    (template std::pair<int, int>
        test_dispatcher_ret_template2_pair<int, int>(const std::pair<int, int>& pair)),
    (template std::pair<char, int>
        test_dispatcher_ret_template2_pair<char, int>(const std::pair<char, int>& pair)),
    (template std::pair<int, char>
        test_dispatcher_ret_template2_pair<int, char>(const std::pair<int, char>& pair)),
    (template std::pair<char, char>
        test_dispatcher_ret_template2_pair<char, char>(const std::pair<char, char>& pair))
)

SIMD_MAKE_DISPATCHER((template<class T, class U>) (<T, U>)
                       (std::pair<T, U>) (test_dispatcher_ret_template2_pair2)
                       ((const std::pair<T, U>&) pair, (const std::pair<T, U>&) pair2))

SIMD_INSTANTIATE_DISPATCHER(
    (template std::pair<int, int>
        test_dispatcher_ret_template2_pair2<int, int>(const std::pair<int, int>& pair1,
                                                      const std::pair<int, int>& pair2)),
    (template std::pair<char, int>
        test_dispatcher_ret_template2_pair2<char, int>(const std::pair<char, int>& pair1,
                                                       const std::pair<char, int>& pair2)),
    (template std::pair<int, char>
        test_dispatcher_ret_template2_pair2<int, char>(const std::pair<int, char>& pair1,
                                                       const std::pair<int, char>& pair2)),
    (template std::pair<char, char>
        test_dispatcher_ret_template2_pair2<char, char>(const std::pair<char, char>& pair1,
                                                        const std::pair<char, char>& pair2))
)

SIMD_MAKE_DISPATCHER((template<class T>) (<T>)
                       (void) (test_dispatcher_void_template_nondeductible) ())

SIMD_INSTANTIATE_DISPATCHER(
    (template void test_dispatcher_void_template_nondeductible<char>()),
    (template void test_dispatcher_void_template_nondeductible<int>())
)

SIMD_MAKE_DISPATCHER((template<class T, class U>) (<T,U>)
                       (void) (test_dispatcher_void_template2_nondeductible) ())

SIMD_INSTANTIATE_DISPATCHER(
    (template void test_dispatcher_void_template2_nondeductible<char, char>()),
    (template void test_dispatcher_void_template2_nondeductible<char, int>()),
    (template void test_dispatcher_void_template2_nondeductible<int, char>()),
    (template void test_dispatcher_void_template2_nondeductible<int, int>())
)

SIMD_MAKE_DISPATCHER((template<class T>) (<T>)
                       (std::pair<T, T>) (test_dispatcher_ret_template_nondeductible) ())

SIMD_INSTANTIATE_DISPATCHER(
    (template std::pair<char, char> test_dispatcher_ret_template_nondeductible<char>()),
    (template std::pair<int, int> test_dispatcher_ret_template_nondeductible<int>())
)

SIMD_MAKE_DISPATCHER((template<class T, class U>) (<T,U>)
                       (std::pair<T, U>) (test_dispatcher_ret_template2_nondeductible) ())

SIMD_INSTANTIATE_DISPATCHER(
    (template std::pair<char, char>
        test_dispatcher_ret_template2_nondeductible<char, char>()),
    (template std::pair<char, int>
        test_dispatcher_ret_template2_nondeductible<char, int>()),
    (template std::pair<int, char>
        test_dispatcher_ret_template2_nondeductible<int, char>()),
    (template std::pair<int, int>
        test_dispatcher_ret_template2_nondeductible<int, int>())
)
