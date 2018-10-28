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

#ifndef DISPATCH_GET_ARCH_LINUX_CPUINFO_H
#define DISPATCH_GET_ARCH_LINUX_CPUINFO_H

#if __linux__ && (__arm__ || __aarch64__ || __i386__ || __amd64__)
#define SIMD_HAS_GET_ARCH_LINUX_CPUINFO 1

#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include <map>
#include <vector>
#include <bigmath/simd/dispatch/arch.h>

namespace simd {

    /** Retrieves supported architecture from Linux /proc/cpuinfo file.

        Works on X86 and ARM.
    */
    inline Arch get_arch_linux_cpuinfo() {
        Arch res = Arch::NONE_NULL;

        std::map<std::string, Arch> features;
        std::string ident;

#if __arm__
        ident = "Features\t";
        features["neon"] = Arch::ARM_NEON | Arch::ARM_NEON_FLT_SP;

#elif __aarch64__
        ident = "Features\t";
        features["asimd"] = Arch::ARM_NEON | Arch::ARM_NEON_FLT_SP;

#elif __i386__ || __amd64__
        Arch a_sse2 = Arch::X86_SSE2;
        Arch a_sse3 = a_sse2 | Arch::X86_SSE3;
        Arch a_ssse3 = a_sse3 | Arch::X86_SSSE3;
        Arch a_sse4_1 = a_ssse3 | Arch::X86_SSE4_1;
        Arch a_sse4_2 = a_sse4_1 | Arch::X86_SSE4_2;
        Arch a_sse4a = a_sse4_2 | Arch::X86_SSE4A;
        Arch a_popcnt = Arch::X86_POPCNT_INSN;
        Arch a_avx = a_sse4a | Arch::X86_AVX;
        Arch a_avx2 = a_avx | Arch::X86_AVX2;
        Arch a_fma3 = a_sse3 | Arch::X86_FMA3;
        Arch a_fma4 = a_sse3 | Arch::X86_FMA4;
        Arch a_xop = a_sse3 | Arch::X86_XOP;
        Arch a_avx512f = a_avx2 | Arch::X86_AVX512F;
        Arch a_avx512bw = a_avx512f | Arch::X86_AVX512BW;
        Arch a_avx512dq = a_avx512f | Arch::X86_AVX512DQ;
        Arch a_avx512vl = a_avx512f | Arch::X86_AVX512VL;

        ident = "flags\t";
        features["sse2"] = a_sse2;
        features["pni"] = a_sse3;
        features["ssse3"] = a_ssse3;
        features["sse4_1"] = a_sse4_1;
        features["sse4_2"] = a_sse4_2;
        features["sse4a"] = a_sse4a;
        features["avx"] = a_avx;
        features["avx2"] = a_avx2;
        features["popcnt"] = a_popcnt;
        features["fma"] = a_fma3;
        features["fma4"] = a_fma4;
        features["xop"] = a_xop;
        features["avx512f"] = a_avx512f;
        features["avx512bw"] = a_avx512bw;
        features["avx512dq"] = a_avx512dq;
        features["avx512vl"] = a_avx512vl;
#else
        return res;
#endif

        std::ifstream in("/proc/cpuinfo");

        if (!in) {
            return res;
        }

        std::string line;
        while (std::getline(in, line)) {
            // Check whether identification string matches
            if (line.length() < ident.length()) {
                continue;
            }
            auto r = std::mismatch(ident.begin(), ident.end(), line.begin());
            if (r.first != ident.end()) {
                continue;
            }

            // Get the items
            std::istringstream sin(std::string(r.second, line.end()));
            std::vector<std::string> items;

            std::copy(std::istream_iterator<std::string>(sin),
                      std::istream_iterator<std::string>(),
                      std::back_inserter(items));

            // Match items to known features
            for (auto &item : items) {
                auto it = features.find(item);
                if (it == features.end()) {
                    continue;
                }
                res |= it->second;
            }
        }

        return res;
    }

} // namespace simd

#endif
#endif // DISPATCH_GET_ARCH_LINUX_CPUINFO_H
