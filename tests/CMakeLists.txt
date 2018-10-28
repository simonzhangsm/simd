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


include_directories(${SIMD_SOURCE_DIR})

# ------------------------------------------------------------------------------

# We need to specify test configuration to be able to test compilation failure
# tests on MSVC.
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} -C Debug --verbose)

set(TEST_INSN_SOURCES
    utils/test_results_set.cc
    main_insn.cc
)

set(TEST_INSN_HEADERS
    utils/test_helpers.h
    utils/test_results.h
    utils/test_results_set.h
    insn/tests.h
    common/masks.h
    common/vectors.h
    common/aligned_allocator.h
)

set(TEST_INSN_ARCH_SOURCES
    insn/bitwise.cc
    insn/blend.cc
    insn/compare.cc
    insn/construct.cc
    insn/convert.cc
    insn/for_each.cc
    insn/math_fp.cc
    insn/math_int.cc
    insn/math_shift.cc
    insn/memory_load.cc
    insn/memory_store.cc
    insn/shuffle.cc
    insn/shuffle_bytes.cc
    insn/permute_generic.cc
    insn/shuffle_generic.cc
    insn/test_utils.cc
    insn/tests.cc
    insn/transpose.cc
)

set(TEST_INSN_ARCH_GEN_SOURCES "")

foreach(SRC ${TEST_INSN_ARCH_SOURCES})
    simd_multiarch(TEST_INSN_ARCH_GEN_SOURCES ${SRC} ${COMPILABLE_ARCHS})
endforeach()


add_executable(test_insn EXCLUDE_FROM_ALL
    ${TEST_INSN_SOURCES}
    ${TEST_INSN_ARCH_GEN_SOURCES}
)

if("${CMAKE_VERSION}" VERSION_GREATER 2.8.12)
    # We don't want to break testing on old environments where newer cmake
    # versions are not easily available.
    target_compile_definitions(test_insn PUBLIC "-DSIMD_DISABLE_DEPRECATED_IN_2_1_AND_OLDER=1")
endif()

add_test(s_test_insn test_insn)
add_dependencies(check test_insn)

# ------------------------------------------------------------------------------
# Dispatcher test

set(TEST_DISPATCHER_SOURCES
    main_dispatcher.cc
    utils/test_results_set.cc
)

set(TEST_DISPATCHER_ARCH_SOURCES
    dispatcher/dispatcher.cc
)

set(TEST_DISPATCHER_ARCH_GEN_SOURCES "")

foreach(SRC ${TEST_DISPATCHER_ARCH_SOURCES})
    simd_multiarch(TEST_DISPATCHER_ARCH_GEN_SOURCES ${SRC} ${NATIVE_ARCHS})
endforeach()

add_executable(test_dispatcher EXCLUDE_FROM_ALL
    ${TEST_DISPATCHER_SOURCES}
    ${TEST_DISPATCHER_ARCH_GEN_SOURCES}
)

if("${CMAKE_VERSION}" VERSION_GREATER 2.8.12)
    target_compile_definitions(test_dispatcher PUBLIC "-DSIMD_DISABLE_DEPRECATED_IN_2_1_AND_OLDER=1")
endif()

add_test(dispatcher_NONE_NULL test_dispatcher "NONE_NULL")
if(HAS_SSE2)
    add_test(dispatcher_X86_SSE2 test_dispatcher "X86_SSE2")
endif()

if(HAS_SSE3)
    add_test(dispatcher_X86_SSE3 test_dispatcher "X86_SSE3")
endif()

if(HAS_SSSE3)
    add_test(dispatcher_X86_SSSE3 test_dispatcher "X86_SSSE3")
endif()

if(HAS_SSE4_1)
    add_test(dispatcher_X86_SSE4_1 test_dispatcher "X86_SSE4_1")
endif()

if(HAS_SSE4_2)
    add_test(dispatcher_X86_SSE4_2 test_dispatcher "X86_SSE4_2")
endif()

if(HAS_SSE4A)
    add_test(dispatcher_X86_SSE4A test_dispatcher "X86_SSE4A")
endif()

if(HAS_AVX)
    add_test(dispatcher_X86_AVX test_dispatcher "X86_AVX")
endif()

if(HAS_AVX2)
    add_test(dispatcher_X86_AVX2 test_dispatcher "X86_AVX2")
endif()

if(HAS_AVX512F)
    add_test(dispatcher_X86_AVX512F test_dispatcher "X86_AVX512F")
endif()

if(HAS_AVX512BW)
    add_test(dispatcher_X86_AVX512BW test_dispatcher "X86_AVX512BW")
endif()

if(HAS_AVX512DQ)
    add_test(dispatcher_X86_AVX512DQ test_dispatcher "X86_AVX512DQ")
endif()

if(HAS_AVX512VL)
    add_test(dispatcher_X86_AVX512VL test_dispatcher "X86_AVX512VL")
endif()

if(HAS_NEON)
    add_test(dispatcher_ARM_NEON test_dispatcher "ARM_NEON")
    add_test(dispatcher_ARM_NEON_FLT_SP test_dispatcher "ARM_NEON_FLT_SP")
endif()

add_dependencies(check test_dispatcher)

# ------------------------------------------------------------------------------
# Expression test

set(TEST_EXPR_SOURCES
    main_expr.cc
    expr/tests.cc
    expr/bitwise.cc
    expr/compare.cc
    expr/math_float.cc
    expr/math_int.cc
    utils/test_results_set.cc
)

add_executable(test_expr EXCLUDE_FROM_ALL
    ${TEST_EXPR_SOURCES}
)

add_test(s_test_expr1 test_expr)
add_dependencies(check test_expr)

add_custom_target(create_dir_for_compile_fail
                  COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/compile_fail")
add_dependencies(check create_dir_for_compile_fail)

add_test(NAME test_compile_fail
         COMMAND ${CMAKE_COMMAND} ${SIMD_SOURCE_DIR}/tests/compile_fail
            -G "${CMAKE_GENERATOR}"
            -T "${CMAKE_GENERATOR_TOOLSET}"
            "-DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}"
            "-DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}"
            "-DSIMD_SOURCE_DIR=${SIMD_SOURCE_DIR}"
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/compile_fail)
