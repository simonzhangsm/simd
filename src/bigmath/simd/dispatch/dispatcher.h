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

#ifndef SIMD_DISPATCH_DISPATCHER_H
#define SIMD_DISPATCH_DISPATCHER_H

#ifndef SIMD_H
#error "This file must be included through simd.h"
#endif

#include <algorithm>
#include <cstdlib>
#include <bigmath/simd/dispatch/arch.h>

namespace simd {

    /** @def SIMD_USER_ARCH_INFO
        The user must define this macro if he wants to use the dispatcher
        infrastructure. The macro must evaluate to a constant expression that could
        implicitly initialize an object of type @c std::function<Arch()>.

        The macro is used by @c SIMD_MAKE_DISPATCHER_* to specify function which
        is invoked to determine which version of the dispatched function to
        dispatch. The macro is just a more convenient method to pass a parameter
        which has high chance to be the same in the majority of use cases. The user
        may redefine the macro and use different definitions for each site of
        @c SIMD_MAKE_DISPATCHER_* expansion.

        The function identified by the @c SIMD_USER_ARCH_INFO is called at the
        first time the specific dispatcher is invoked. The user must ensure that
        proper synchronization is used if the dispatcher is called concurrently.

        The user must ensure that the returned information is sensible: e.g. SSE2
        must be supported if SSE3 support is indicated.

        The @c simd/dispatch/get_arch_*.h files provide several ready
        implementations of CPU features detection.
    */

    namespace detail {

        using VoidFunPtr = void (*)();

        struct FnVersion {
            /*  Identifies the instruction support that is needed for this version to
                run.
            */
            Arch needed_arch;

            /*  The type-erased function pointer. Only non-member functions are
                supported.

                We type-erase this pointer to reduce the code bloat by allowing @c
                select_version to be shared across all dispatchers.

                Note, that we can't reinterpret_cast to void*, as that is undefined
                behavior in C++. reinterpret_cast to another function pointer
                type is allowed fortunately.
            */
            VoidFunPtr fun_ptr;

            /*  Optional string identifier identifying the architecture. */
            const char *arch_name;
        };

        inline FnVersion select_version_any(FnVersion *versions, unsigned size, Arch arch) {
            // No need to try to be very efficient here.
            std::sort(versions, versions + size, [](const FnVersion &lhs, const FnVersion &rhs) {
                return lhs.needed_arch > rhs.needed_arch;
            });

            unsigned i;
            for (i = 0; i < size; ++i) {
                if (versions[i].fun_ptr == nullptr)
                    continue;
                if (test_arch_subset(arch, versions[i].needed_arch)) {
                    break;
                }
            }
            if (i == size) {
                // The user didn't provide the NONE_NULL version and no SIMD
                // architecture is supported. We can't do anything except to abort
                std::abort();
            }
            return versions[i];
        }

    } // namespace detail
} // namespace simd

#endif // SIMD_DISPATCH_DISPATCHER_H
