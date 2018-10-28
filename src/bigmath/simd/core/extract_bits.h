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

#ifndef SIMD_CORE_EXTRACT_BITS_H
#define SIMD_CORE_EXTRACT_BITS_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <bigmath/simd/types.h>
#include <bigmath/simd/detail/insn/extract_bits.h>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {

        /** Extracts a bit from each byte of each element of a vector containing 8-bit
            elements.

            This operation is only sensible if each byte within the vector is either
            0x00 or 0xff.

            @code
            r = ((a[0] & 0x??) ? 0x01 : 0) |
                ((a[1] & 0x??) ? 0x02 : 0) |
                ...
                ((a[15] & 0x??) ? 0x80 : 0)
            @endcode
        */
        inline uint16_t extract_bits_any(const uint8<16> &a) {
            return detail::insn::i_extract_bits_any(a);
        }
        inline uint32_t extract_bits_any(const uint8<32> &a) {
            return detail::insn::i_extract_bits_any(a);
        }

        /** Extracts specific bit from each byte of each element of a int8x16 vector.

            @code
            r = (a[0] & 0x80 >> 7) | (a[1] & 0x80 >> 6) | ...  | (a[15] & 0x80 << 8)
            @endcode
        */
        template <unsigned id> inline uint16_t extract_bits(const uint8<16> &a) {
            static_assert(id < 8, "index out of bounds");
            return detail::insn::i_extract_bits<id>(a);
        }
        template <unsigned id> inline uint32_t extract_bits(const uint8<32> &a) {
            static_assert(id < 8, "index out of bounds");
            return detail::insn::i_extract_bits<id>(a);
        }

    } // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
