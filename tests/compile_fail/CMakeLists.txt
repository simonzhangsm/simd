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

cmake_minimum_required(VERSION 2.8.0)
project(simd_compile_fail_tests)

SET(SIMD_SOURCE_DIR "source_dir_not_specified" CACHE STRING "Root directory of simd")

include(CheckCXXSourceCompiles)

function(test_compile_fail DESC FLAGS CODE)
    set(CMAKE_REQUIRED_FLAGS "-std=c++11 ${FLAGS}")
    set(CMAKE_REQUIRED_DEFINITIONS "-DSIMD_ARCH_X86_SSE2 -DSIMD_DISABLE_DEPRECATED_CONVERSION_OPERATOR_TO_NATIVE_TYPES=1")
    set(CMAKE_REQUIRED_INCLUDES "${simd_SOURCE_DIR}")
    set(CHECK_VAR "VERIFY_FAILS_TO_COMPILE_${DESC}")
    check_cxx_source_compiles("${CODE}" ${CHECK_VAR})
    if(${CHECK_VAR})
        message(FATAL_ERROR "Test ${CHECK_VAR} should have failed to compile, but it did not")
    endif()
endfunction()

set(COMPILE_FLAGS "")

test_compile_fail(when_using_unsupported_implicit_conversion_with_functions_float32x4_int32x4
                  "${COMPILE_FLAGS}" "
	#include <bigmath/simd/simd.h>
	
	using namespace simd;
	
	float32x4 test_fails(float32<4> a, int32<4> b)
	{
	    return add(a, b);
	}
	
	int main()
	{
	    float32<4> a;
	    int32<4> b;
	    a = test_fails(a, b);
	}
")

test_compile_fail(when_using_unsupported_implicit_conversion_with_operators_float32x4_int32x4
                  "${COMPILE_FLAGS}" "
	#include <bigmath/simd/simd.h>
	
	using namespace simd;
	
	float32x4 test_fails(float32<4> a, int32<4> b)
	{
	    return a + b;
	}
	
	int main()
	{
	    float32<4> a;
	    int32<4> b;
	    a = test_fails(a, b);
	}
")

test_compile_fail(when_using_unsupported_implicit_conversion_with_functions_int8x16_int32x4
                  "${COMPILE_FLAGS}" "
	#include <bigmath/simd/simd.h>
	
	using namespace simd;
	
	int8<16> test_fails(int8<16> a, int32<4> b)
	{
	    return add(a, b);
	}
	
	int main()
	{
	    int8<16> a;
	    int32<4> b;
	    a = test_fails(a, b);
	}
")

test_compile_fail(when_using_unsupported_implicit_conversion_with_operators_int8x16_int32x4
                  "${COMPILE_FLAGS}" "
	#include <bigmath/simd/simd.h>
	
	using namespace simd;
	
	int8<16> test_fails(int8<16> a, int32<4> b)
	{
	    return a + b;
	}
	
	int main()
	{
	    int8<16> a;
	    int32<4> b;
	    a = test_fails(a, b);
	}
")
