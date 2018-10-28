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

#ifndef SIMD_CACHE_H
#define SIMD_CACHE_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif
#include <bigmath/simd/setup_arch.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {

        /** Prefetches data to the lowest level cache for reading.

            @param ptr pointer to the data to prefetch
        */
        template <class T> inline void prefetch_read(const T *ptr) {
#if SIMD_USE_SSE2
            _mm_prefetch(reinterpret_cast<const char *>(ptr), _MM_HINT_T0);
#elif SIMD_USE_NEON || SIMD_USE_ALTIVEC || SIMD_USE_MSA
#if __GNUC__
            // on NEON results in PLD
            // on Altivec results in DST
            // on MSA results in PREF
            __builtin_prefetch(ptr, 0);
#endif
#endif
            (void)ptr;
        }

        /** Prefetches data to the lowest level cache for writing.

            @param ptr pointer to the data to prefetch
        */
        template <class T> inline void prefetch_write(const T *ptr) {
#if SIMD_USE_SSE2
            _mm_prefetch(reinterpret_cast<const char *>(ptr), _MM_HINT_T0);
#elif SIMD_USE_NEON || SIMD_USE_ALTIVEC || SIMD_USE_MSA
#if __GNUC__
            // on NEON results in PLDW
            // on Altivec results in DSTST
            // on MSA results in PREF
            __builtin_prefetch(ptr, 1);
#endif
#endif
            (void)ptr;
        }

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
