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

#include "bigmath/simd/instrset_detect.h"

namespace CORPORATION_NAMESPACE {
    namespace simd {

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
        int instrset_detect() {

            static int iset = -1; // remember value for next call
            if (iset >= 0) {
                return iset; // called before
            }
            iset = 0;                   // default value
            int abcd[4] = {0, 0, 0, 0}; // cpuid results
            cpuid(abcd, 0);             // call cpuid function 0
            if (abcd[0] == 0)
                return iset; // no further cpuid function supported
            cpuid(abcd, 1);  // call cpuid function 1 for feature flags
            if ((abcd[3] & (1 << 0)) == 0)
                return iset; // no floating point
            if ((abcd[3] & (1 << 23)) == 0)
                return iset; // no MMX
            if ((abcd[3] & (1 << 15)) == 0)
                return iset; // no conditional move
            if ((abcd[3] & (1 << 24)) == 0)
                return iset; // no FXSAVE
            if ((abcd[3] & (1 << 25)) == 0)
                return iset; // no SSE
            iset = 1;        // 1: SSE supported
            if ((abcd[3] & (1 << 26)) == 0)
                return iset; // no SSE2
            iset = 2;        // 2: SSE2 supported
            if ((abcd[2] & (1 << 0)) == 0)
                return iset; // no SSE3
            iset = 3;        // 3: SSE3 supported
            if ((abcd[2] & (1 << 9)) == 0)
                return iset; // no SSSE3
            iset = 4;        // 4: SSSE3 supported
            if ((abcd[2] & (1 << 19)) == 0)
                return iset; // no SSE4.1
            iset = 5;        // 5: SSE4.1 supported
            if ((abcd[2] & (1 << 23)) == 0)
                return iset; // no POPCNT
            if ((abcd[2] & (1 << 20)) == 0)
                return iset; // no SSE4.2
            iset = 6;        // 6: SSE4.2 supported
            if ((abcd[2] & (1 << 27)) == 0)
                return iset; // no OSXSAVE
            if ((xgetbv(0) & 6) != 6)
                return iset; // AVX not enabled in O.S.
            if ((abcd[2] & (1 << 28)) == 0)
                return iset; // no AVX
            iset = 7;        // 7: AVX supported
            cpuid(abcd, 7);  // call cpuid leaf 7 for feature flags
            if ((abcd[1] & (1 << 5)) == 0)
                return iset; // no AVX2
            iset = 8;
            if ((abcd[1] & (1 << 16)) == 0)
                return iset;  // no AVX512
            cpuid(abcd, 0xD); // call cpuid leaf 0xD for feature flags
            if ((abcd[0] & 0x60) != 0x60)
                return iset; // no AVX512
            iset = 9;
            cpuid(abcd, 7); // call cpuid leaf 7 for feature flags
            if ((abcd[1] & (1 << 31)) == 0)
                return iset; // no AVX512VL
            iset = 10;
            if ((abcd[1] & 0x40020000) != 0x40020000)
                return iset; // no AVX512BW, AVX512DQ
            iset = 11;
            return iset;
        }

        // detect if CPU supports the FMA3 instruction set
        bool hasFMA3(void) {
            if (instrset_detect() < 7)
                return false;                    // must have AVX
            int abcd[4];                         // cpuid results
            cpuid(abcd, 1);                      // call cpuid function 1
            return ((abcd[2] & (1 << 12)) != 0); // ecx bit 12 indicates FMA3
        }

        // detect if CPU supports the FMA4 instruction set
        bool hasFMA4(void) {
            if (instrset_detect() < 7)
                return false;                    // must have AVX
            int abcd[4];                         // cpuid results
            cpuid(abcd, 0x80000001);             // call cpuid function 0x80000001
            return ((abcd[2] & (1 << 16)) != 0); // ecx bit 16 indicates FMA4
        }

        // detect if CPU supports the XOP instruction set
        bool hasXOP(void) {
            if (instrset_detect() < 7)
                return false;                    // must have AVX
            int abcd[4];                         // cpuid results
            cpuid(abcd, 0x80000001);             // call cpuid function 0x80000001
            return ((abcd[2] & (1 << 11)) != 0); // ecx bit 11 indicates XOP
        }

        // detect if CPU supports the F16C instruction set
        bool hasF16C(void) {
            if (instrset_detect() < 7)
                return false;                    // must have AVX
            int abcd[4];                         // cpuid results
            cpuid(abcd, 1);                      // call cpuid function 1
            return ((abcd[2] & (1 << 29)) != 0); // ecx bit 29 indicates F16C
        }

        // detect if CPU supports the AVX512ER instruction set
        bool hasAVX512ER(void) {
            if (instrset_detect() < 9)
                return false;                    // must have AVX512F
            int abcd[4];                         // cpuid results
            cpuid(abcd, 7);                      // call cpuid function 7
            return ((abcd[1] & (1 << 27)) != 0); // ebx bit 27 indicates AVX512ER
        }

    } // namespace simd
} // namespace CORPORATION_NAMESPACE
