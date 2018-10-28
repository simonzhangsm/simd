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

file(GLOB_RECURSE HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h *.inl)

foreach(FILE ${HEADERS})
    get_filename_component(FILE_PATH "${FILE}" PATH)
    install(FILES "${FILE}" DESTINATION "${SIMD_INCLUDEDIR}/${FILE_PATH}")
endforeach()

SET (VECHEADER
	bigmath/simd/instrset.h
	bigmath/simd/instrset_detect.h
	bigmath/simd/math/common.h
	bigmath/simd/math/exp.h
	bigmath/simd/math/hyp.h
	bigmath/simd/math/lib.h
	bigmath/simd/math/trig.h
	bigmath/simd/special/complexvec.h
	bigmath/simd/special/decimal.h
	bigmath/simd/special/quaternion.h
	bigmath/simd/special/ranvec1.h
	bigmath/simd/special/vector3d.h
	bigmath/simd/vectorf128.h
	bigmath/simd/vectorf256.h
	bigmath/simd/vectorf256e.h
	bigmath/simd/vectorf512.h
	bigmath/simd/vectorf512e.h
	bigmath/simd/vectori128.h
	bigmath/simd/vectori256.h
	bigmath/simd/vectori256e.h
	bigmath/simd/vectori512.h
	bigmath/simd/vectori512e.h
)

SET (VECSRC
	bigmath/simd/instrset_detect.cpp
	bigmath/simd/special/ranvec1.cpp
)

ADD_LIBRARY(libvecsimd OBJECT ${VECSRC})

TARGET_INCLUDE_DIRECTORIES(libvecsimd
  PUBLIC
  ${CMAKE_SOURCE_DIR}
  ${${PROJECT_NAME}_SOURCE_DIR}
 )

########################################################################
SET (LIBNAME lib${PKG_NAME}-${PROJECT_VERSION})
ADD_LIBRARY(${LIBNAME}
  SHARED
  $<TARGET_OBJECTS:libvecsimd>
)

INSTALL(TARGETS ${LIBNAME}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

# Don't enable header tests by default because configuring it takes excessive
# amount of time
set(ENABLE_HEADER_TESTS "1")

if(${ENABLE_HEADER_TESTS} STREQUAL "1")

    simd_get_compilable_archs(COMPILABLE_ARCHS)

    set(HEADER_TESTS "")
    add_custom_target(check_headers)

    foreach(ARCH ${COMPILABLE_ARCHS})
        simd_get_arch_info(CXX_FLAGS DEFINES_LIST SUFFIX ${ARCH})
        foreach(FILE ${HEADERS})

            if("${FILE}" STREQUAL ".inl")
                continue()
            endif()

            string(REPLACE "/" "_" TEST "${FILE}")
            string(REPLACE "." "_" TEST "${TEST}")
            set(TEST "${TEST}${SUFFIX}")
            set(TEST_OUT "check_headers/test_header_compiles_${TEST}")
            string(REPLACE "-" "_" TEST_TARGET "check_headers_${TEST}")


            file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/check_headers")
            separate_arguments(CXX_FLAGS)
            add_custom_command(
                OUTPUT ${TEST_OUT}
                COMMAND ${CMAKE_CXX_COMPILER}
                        -DSIMD_H
                        -I "${CMAKE_SOURCE_DIR}"
                        ${CXX_FLAGS} -x c++ -std=c++11 -g2 -Wall
                        ${CMAKE_SOURCE_DIR}/simd/${FILE}
                        -c -o ${CMAKE_BINARY_DIR}/${TEST_OUT}
                DEPENDS ${FILE} )
            add_custom_target(${TEST_TARGET} DEPENDS ${TEST_OUT})
            add_dependencies(check_headers "${TEST_TARGET}")
        endforeach()
    endforeach()

endif()

