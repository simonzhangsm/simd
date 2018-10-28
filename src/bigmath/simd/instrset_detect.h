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
 * Functions for checking which instruction sets are supported.
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

#include "bigmath/simd/instrset.h"
#include "bigmath/simd/config.h"

namespace CORPORATION_NAMESPACE {
    namespace simd {

        // Define interface to cpuid instruction.
        // input:  eax = functionnumber, ecx = 0
        // output: eax = output[0], ebx = output[1], ecx = output[2], edx = output[3]
        static inline void cpuid(int output[4], int functionnumber) {
#if defined(__GNUC__) || defined(__clang__) // use inline assembly, Gnu/AT&T syntax

            int a, b, c, d;
            __asm("cpuid" : "=a"(a), "=b"(b), "=c"(c), "=d"(d) : "a"(functionnumber), "c"(0) :);
            output[0] = a;
            output[1] = b;
            output[2] = c;
            output[3] = d;

#elif defined(_MSC_VER) || defined(__INTEL_COMPILER) // Microsoft or Intel compiler, intrin.h included

            __cpuidex(output, functionnumber, 0); // intrinsic function for CPUID

#else // unknown platform. try inline assembly with masm/intel syntax

            __asm {
				mov eax, functionnumber
				xor ecx, ecx
				cpuid;
				mov esi, output
				mov [esi], eax
				mov [esi+4], ebx
				mov [esi+8], ecx
				mov [esi+12], edx
            }

#endif
        }

        // Define interface to xgetbv instruction
        static inline int64_t xgetbv(int ctr) {
#if (defined(_MSC_FULL_VER) && _MSC_FULL_VER >= 160040000) \
    || (defined(__INTEL_COMPILER)                          \
        && __INTEL_COMPILER >= 1200) // Microsoft or Intel compiler supporting _xgetbv intrinsic

            return _xgetbv(ctr); // intrinsic function for XGETBV

#elif defined(__GNUC__) // use inline assembly, Gnu/AT&T syntax

            uint32_t a, d;
            __asm("xgetbv" : "=a"(a), "=d"(d) : "c"(ctr) :);
            return a | (uint64_t(d) << 32);

#else // #elif defined (_WIN32)                           // other compiler. try inline assembly with masm/intel/MS
      // syntax

            uint32_t a, d;
            __asm {
				mov ecx, ctr
				_emit 0x0f
				_emit 0x01
				_emit 0xd0; // xgetbv
				mov a, eax
				mov d, edx
            }
            return a | (uint64_t(d) << 32);

#endif
        }

        /* find supported instruction set
         return value:
         0           = 80386 instruction set
         1  or above = SSE (XMM) supported by CPU (not testing for O.S. support)
         2  or above = SSE2
         3  or above = SSE3
         4  or above = Supplementary SSE3 (SSSE3)
         5  or above = SSE4.1
         6  or above = SSE4.2
         7  or above = AVX supported by CPU and operating system
         8  or above = AVX2
         9  or above = AVX512F
         10 or above = AVX512VL
         11 or above = AVX512BW, AVX512DQ
         */
        int instrset_detect();

        // detect if CPU supports the FMA3 instruction set
        bool hasFMA3(void);

        // detect if CPU supports the FMA4 instruction set
        bool hasFMA4(void);

        // detect if CPU supports the XOP instruction set
        bool hasXOP(void);

        // detect if CPU supports the F16C instruction set
        bool hasF16C(void);

        // detect if CPU supports the AVX512ER instruction set
        bool hasAVX512ER(void);

    } // namespace simd
} // namespace CORPORATION_NAMESPACE
