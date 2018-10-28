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

#ifndef DETAIL_SHUFFLE_NEON_INT64x2_H
#define DETAIL_SHUFFLE_NEON_INT64x2_H
#if SIMD_USE_NEON

#include <type_traits>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace neon_shuffle_int64x2 {

#if SIMD_USE_NEON32

                /*
                    The code below implements generalized permutations of elements within
                    int64x2 vectors using half-vector move instructions available on NEON.
                */
                using T = uint64x2;   // full vector
                using H = uint64x1_t; // half vector


                /// Returns the lower/higher part of a vector. Cost: 0
                inline H lo(T a) {
                    return vget_low_u64(a.native());
                }
                inline H hi(T a) {
                    return vget_high_u64(a.native());
                }

                /// Combines two half vectors. Cost: 0
                inline T co(H lo, H hi) {
                    return vcombine_u64(lo, hi);
                }

                // 2-element permutation
                template <unsigned s0, unsigned s1> inline T permute2(T a) {
                    const unsigned sel = s0 * 2 + s1;
                    switch (sel) {
                        default:
                        case 0: /*00*/
                            return co(lo(a), lo(a));
                        case 1: /*01*/
                            return a;
                        case 2: /*10*/
                            return co(hi(a), lo(a));
                        case 3: /*11*/
                            return co(hi(a), hi(a));
                    }
                }

                // 2-element shuffle: the first element must come from a, the second - from b
                template <unsigned s0, unsigned s1> inline T shuffle1(T a, T b) {
                    const unsigned sel = s0 * 2 + s1;
                    switch (sel) {
                        default:
                        case 0: /*00*/
                            return co(lo(a), lo(b));
                        case 1: /*01*/
                            return co(lo(a), hi(b));
                        case 2: /*10*/
                            return co(hi(a), lo(b));
                        case 3: /*11*/
                            return co(hi(a), hi(b));
                    }
                }

                template <unsigned s0, unsigned s1> inline T shuffle2x2(const T &a, const T &b) {
                    const unsigned sel = s0 * 4 + s1;
                    switch (sel) {
                        default:
                        case 0: /*00*/
                            return co(lo(a), lo(a));
                        case 1: /*01*/
                            return a;
                        case 2: /*02*/
                            return co(lo(a), lo(b));
                        case 3: /*03*/
                            return co(lo(a), hi(b));
                        case 4: /*10*/
                            return co(hi(a), lo(a));
                        case 5: /*11*/
                            return co(hi(a), hi(a));
                        case 6: /*12*/
                            return co(hi(a), lo(b));
                        case 7: /*13*/
                            return co(hi(a), hi(b));
                        case 8: /*20*/
                            return co(lo(b), lo(a));
                        case 9: /*21*/
                            return co(lo(b), hi(a));
                        case 10: /*22*/
                            return co(lo(b), lo(b));
                        case 11: /*23*/
                            return b;
                        case 12: /*30*/
                            return co(hi(b), lo(a));
                        case 13: /*31*/
                            return co(hi(b), hi(a));
                        case 14: /*32*/
                            return co(hi(b), lo(b));
                        case 15: /*33*/
                            return co(hi(b), hi(b));
                    }
                }

#else // SIMD_USE_NEON64

                using T = uint64x2; // full vector

                // Moves the high half of b onto high half of a
                inline T move_hi(const T &a, const T &b) {
                    T mask = make_uint(0xffffffffffffffff, 0x0);
                    return vbslq_u64(mask.native(), a.native(), b.native());
                }

                // 2-element permutation
                template <unsigned s0, unsigned s1> inline T permute2(const T &a) {
                    const unsigned sel = s0 * 2 + s1;
                    switch (sel) {
                        default:
                        case 0: /*00*/
                            return vzip1q_u64(a.native(), a.native());
                        case 1: /*01*/
                            return a;
                        case 2: /*10*/
                            return vextq_u64(a.native(), a.native(), 1);
                        case 3: /*11*/
                            return vzip2q_u64(a.native(), a.native());
                    }
                }

                // 2-element shuffle: the first element must come from a, the second - from b
                template <unsigned s0, unsigned s1> inline T shuffle1(const T &a, const T &b) {
                    const unsigned sel = s0 * 2 + s1;
                    switch (sel) {
                        default:
                        case 0: /*00*/
                            return vzip1q_u64(a.native(), b.native());
                        case 1: /*01*/
                            return move_hi(a, b);
                        case 2: /*10*/
                            return vextq_u64(a.native(), b.native(), 1);
                        case 3: /*11*/
                            return vzip2q_u64(a.native(), b.native());
                    }
                }

                template <unsigned s0, unsigned s1> inline T shuffle2x2(const T &a, const T &b) {
                    const unsigned sel = s0 * 4 + s1;
                    switch (sel) {
                        default:
                        case 0: /*00*/
                            return vzip1q_u64(a.native(), a.native());
                        case 1: /*01*/
                            return a;
                        case 2: /*02*/
                            return vzip1q_u64(a.native(), b.native());
                        case 3: /*03*/
                            return move_hi(a, b);
                        case 4: /*10*/
                            return vextq_u64(a.native(), a.native(), 1);
                        case 5: /*11*/
                            return vzip2q_u64(a.native(), a.native());
                        case 6: /*12*/
                            return vextq_u64(a.native(), b.native(), 1);
                        case 7: /*13*/
                            return vzip2q_u64(a.native(), b.native());
                        case 8: /*20*/
                            return vzip1q_u64(b.native(), a.native());
                        case 9: /*21*/
                            return move_hi(b, a);
                        case 10: /*22*/
                            return vzip1q_u64(b.native(), b.native());
                        case 11: /*23*/
                            return b;
                        case 12: /*30*/
                            return vextq_u64(b.native(), a.native(), 1);
                        case 13: /*31*/
                            return vzip2q_u64(b.native(), a.native());
                        case 14: /*32*/
                            return vextq_u64(b.native(), b.native(), 1);
                        case 15: /*33*/
                            return vzip2q_u64(b.native(), b.native());
                    }
                }

#endif

            } // namespace neon_shuffle_int64x2
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
#endif
