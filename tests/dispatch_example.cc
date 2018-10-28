/**********************************************************************
 * BIGMATH INSIGHT CONFIDENTIAL
 *
 * Copyright (C) 2016-2018 BIGMATH CORPORATION, All Rights Reserved.
 *
 * @Author: Simon Zhang on 19 Oct 2018
 * @EMail: simon.zhangsm@hotmail.com
 * @Version: $SIMD_LIB_VERSION
 *
 * Description:
 * Example of CPU dispatching.
 *
 * # Example of compiling this with GCC compiler:
 * # Compile dispatch_example.cpp five times for different instruction sets:
 * g++ -O3 -msse2    -c dispatch_example.cpp -o sse2.o
 * g++ -O3 -msse3    -c dispatch_example.cpp -o sse3.o
 * g++ -O3 -mssse3   -c dispatch_example.cpp -o ssse3.o
 * g++ -O3 -msse4.1  -c dispatch_example.cpp -o sse4.1.o
 * g++ -O3 -msse4.2  -c dispatch_example.cpp -o sse4.2.o
 * g++ -O3 -mavx     -c dispatch_example.cpp -o avx.o
 * g++ -O3 -mavx2    -c dispatch_example.cpp -o avx2.o
 * g++ -O3 -mavx512f -c dispatch_example.cpp -o avx512f.o
 * g++ -O3 -msse2 -o dispatch_example instrset_detect.cpp sse2.o sse3.o ssse3.o sse4.1.o sse4.2.o avx.o avx2.o avx512f.o
 * ./test
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

#include <stdio.h>

#define MAX_VECTOR_SIZE 512
#include "bigmath/simd/vectorsimd.h"
#include "bigmath/simd/vectorsimd.h"

namespace CORPORATION_NAMESPACE {
    namespace simd {

        // define function type (change this to fit your purpose. Should not contain vector types)
        typedef float MyFuncType(float *);

        // function prototypes for each version
        MyFuncType myfunc, myfunc_SSE2, myfunc_SSE2, myfunc_SSE3, myfunc_SSE41, myfunc_SSE42, myfunc_AVX, myfunc_AVX2,
            myfunc_AVX512, myfunc_dispatch;

// Define function name depending on which instruction set we compile for
#if INSTRSET == 2 // SSE2
#define FUNCNAME myfunc_SSE2
#elif INSTRSET == 3 // SSE3
#define FUNCNAME myfunc_SSE3
#elif INSTRSET == 4 // SSSE3
#define FUNCNAME myfunc_SSSE3
#elif INSTRSET == 5 // SSSE3
#define FUNCNAME myfunc_SSE41
#elif INSTRSET == 6 // SSE42
#define FUNCNAME myfunc_SSE42
#elif INSTRSET == 7 // AVX
#define FUNCNAME myfunc_AVX
#elif INSTRSET == 8 // AVX2
#define FUNCNAME myfunc_AVX2
#elif INSTRSET == 9 // AVX512
#define FUNCNAME myfunc_AVX512
#endif

        // specific version of the function. Compile once for each version
        float FUNCNAME(float *f) {
            Vec16f a;                 // vector of 16 floats
            a.load(f);                // load array into vector
            return horizontal_add(a); // return sum of 16 elements
        }


#if INSTRSET == 2
        // make dispatcher in only the lowest of the compiled versions

        // Function pointer initially points to the dispatcher.
        // After first call it points to the selected version
        MyFuncType *myfunc_pointer = &myfunc_dispatch; // function pointer

        // Dispatcher
        float myfunc_dispatch(float *f) {
            int iset = instrset_detect(); // Detect supported instruction set
            if (iset >= 9)
                myfunc_pointer = &myfunc_AVX512; // AVX512 version
            else if (iset >= 8)
                myfunc_pointer = &myfunc_AVX2; // AVX2 version
            else if (iset >= 7)
                myfunc_pointer = &myfunc_AVX; // AVX version
            else if (iset >= 6)
                myfunc_pointer = &myfunc_SSE42; // SSE4.2 version
            else if (iset >= 5)
                myfunc_pointer = &myfunc_SSE41; // SSE4.1 version
            else if (iset >= 4)
                myfunc_pointer = &myfunc_SSSE3; // SSSE3 version
            else if (iset >= 3)
                myfunc_pointer = &myfunc_SSE3; // SSE3 version
            else if (iset >= 2)
                myfunc_pointer = &myfunc_SSE2; // SSE2 version
            else {
                // Error: lowest instruction set not supported (put your own error message here:)
                fprintf(stderr, "\nError: Instruction set SSE2 not supported on this computer");
                return 0.f;
            }
            // continue in dispatched version
            return (*myfunc_pointer)(f);
        }


        // Entry to dispatched function call
        inline float myfunc(float *f) {
            return (*myfunc_pointer)(f); // go to dispatched version
        }


        // Example: main calls myfunc
        int main(int argc, char *argv[]) {
            float a[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}; // array of 16 floats

            float sum = myfunc(a); // call function with dispatching

            printf("\nsum = %8.3f \n", sum); // print result
            return 0;
        }

#endif // INSTRSET == 2

    } // namespace simd
} // namespace CORPORATION_NAMESPACE
