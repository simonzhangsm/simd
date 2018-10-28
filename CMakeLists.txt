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

cmake_minimum_required(VERSION 3.2)
project(SIMD)
set(PROJECT_VERSION "1.18.10.000")
set(SIMD_API_VERSION "1.18.10.000")

set(PKG_NAME "simd")
set(PKG_FULL_NAME "${simd}-${PROJECT_VERSION}")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
# ------------------------------------------------------------------------------
# Custom make dist target. Assumes source directory is a git repository.

set(ARCHIVE_NAME "${PKG_FULL_NAME}")
set(ARCHIVE_DIR "${PKG_FULL_NAME}")

add_custom_target(dist
    COMMAND cd "${CMAKE_SOURCE_DIR}" && ./make_dist.sh "${ARCHIVE_DIR}" "${CMAKE_BINARY_DIR}/${ARCHIVE_NAME}.tar.gz"
    # we may append to the archive now if needed
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
)

# ------------------------------------------------------------------------------
# Check what instruction sets the current host supports. Use them for testing
include(SIMDMultiArch)
message(STATUS "Checking instruction set support in the compiler...")
simd_get_compilable_archs(COMPILABLE_ARCHS)
message(STATUS "Checking instruction sets to run tests for on this host...")
simd_get_runnable_archs(NATIVE_ARCHS)
# ------------------------------------------------------------------------------

set(SIMD_INCLUDEDIR "${CMAKE_INSTALL_PREFIX}/include")
set(SIMD_DOCDIR "${CMAKE_INSTALL_PREFIX}/share/doc")
set(SIMD_PKGCONFIGDIR "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig")

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/simd.pc.in"
    "${CMAKE_CURRENT_BINARY_DIR}/${PKG_NAME}-${SIMD_API_VERSION}.pc" @ONLY
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${PKG_NAME}-${SIMD_API_VERSION}.pc"
    DESTINATION "${SIMD_PKGCONFIGDIR}"
)


# LIST_CONTAINS(<var> ENTRY [LIST...])
#
# Helper macro that checks whether a list contains a specific entry. It sets
# ${VAR} to TRUE if VALUE is within LIST.
#
macro(list_contains VAR VALUE)
    set(${VAR})
    foreach(IV ${ARGN})
        if(${VALUE} STREQUAL ${IV})
            SET(${VAR} TRUE)
        endif()
    endforeach()
endmacro()

# ------------------------------------------------------------------------------
# check available architectures

list_contains(HAS_SSE2 X86_SSE2 ${NATIVE_ARCHS})
list_contains(HAS_SSE3 X86_SSE3 ${NATIVE_ARCHS})
list_contains(HAS_SSSE3 X86_SSSE3 ${NATIVE_ARCHS})
list_contains(HAS_SSE4_1 X86_SSE4_1 ${NATIVE_ARCHS})
list_contains(HAS_SSE4_2 X86_SSE4_2 ${NATIVE_ARCHS})
list_contains(HAS_SSE4A X86_SSE4A ${NATIVE_ARCHS})
list_contains(HAS_AVX X86_AVX ${NATIVE_ARCHS})
list_contains(HAS_AVX2 X86_AVX2 ${NATIVE_ARCHS})
list_contains(HAS_AVX512F X86_AVX512F ${NATIVE_ARCHS})
list_contains(HAS_AVX512BW X86_AVX512BW ${NATIVE_ARCHS})
list_contains(HAS_AVX512DQ X86_AVX512DQ ${NATIVE_ARCHS})
list_contains(HAS_AVX512VL X86_AVX512VL ${NATIVE_ARCHS})
list_contains(HAS_NEON X86_NEON ${NATIVE_ARCHS})

# print compiler detection information
message(STATUS "Checking detected compiler for tests...")
message(STATUS "CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "MSVC: ${MSVC}")
message(STATUS "Detected compiler:")
message(STATUS "SIMD_CLANG: ${SIMD_CLANG}")
message(STATUS "SIMD_GCC: ${SIMD_GCC}")
message(STATUS "SIMD_MSVC: ${SIMD_MSVC}")
message(STATUS "SIMD_INTEL: ${SIMD_INTEL}")
message(STATUS "SIMD_MSVC_INTEL: ${SIMD_MSVC_INTEL}")

# don't use x87 in any of the tests because it performs calculations with
# different precision
if(HAS_SSE2)
    set(DEFAULT_FLAGS "")
    if(SIMD_CLANG)
        set(DEFAULT_FLAGS " -msse2")
    elseif(SIMD_GCC)
        set(DEFAULT_FLAGS " -mfpmath=sse -msse2")
    elseif(SIMD_INTEL)
        set(DEFAULT_FLAGS " -msse2")
    elseif(SIMD_MSVC OR SIMD_MSVC_INTEL)
        set(DEFAULT_FLAGS " /arch:SSE2")
    endif()

    foreach(GENSRC ${TEST_INSN_ARCH_GEN_SOURCES})
        get_property(CURRENT_COMPILE_FLAGS
                     SOURCE "${GENSRC}" PROPERTY COMPILE_FLAGS)
        set_property(SOURCE "${GENSRC}" PROPERTY COMPILE_FLAGS
                     "${DEFAULT_FLAGS} ${CURRENT_COMPILE_FLAGS}")
    endforeach()
endif()

ADD_COMPILE_OPTIONS(-fPIC -g3 -Wno-sign-compare)

if(SIMD_MSVC)
    if(CMAKE_SIZEOF_VOID_P EQUAL 4)
        # enable _vectorcall on i386 builds (only works on MSVC 2013)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Gv")
    endif()
elseif(SIMD_MSVC_INTEL)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Qstd=c++11")
else()
    # Xcode clang linker spends very long time in deduplication pass when
    # linking the test executable unless -fvisibility-inlines-hidden is passed.
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2 -Wall -Wextra -fvisibility-inlines-hidden")
endif()

include_directories ("${PROJECT_SOURCE_DIR}/src")
add_subdirectory(src)
########################################################################
#
# Configure the tests.
#
########################################################################
ENABLE_TESTING()
ADD_SUBDIRECTORY(tests)
