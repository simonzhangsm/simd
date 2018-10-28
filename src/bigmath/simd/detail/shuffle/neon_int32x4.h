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

#ifndef DETAIL_SHUFFLE_NEON_INT32x4_H
#define DETAIL_SHUFFLE_NEON_INT32x4_H
#if SIMD_USE_NEON

#include <type_traits>

namespace simd {
    namespace SIMD_ARCH_NAMESPACE {
        namespace detail {
            namespace neon_shuffle_int32x4 {

                /*
                    The code below implements generalized permutations of elements within
                    int32x4 vectors using various shuffling instructions available on NEON.
                */
                using _0 = std::integral_constant<unsigned, 0>;
                using _1 = std::integral_constant<unsigned, 1>;
                using _2 = std::integral_constant<unsigned, 2>;
                using _3 = std::integral_constant<unsigned, 3>;
                using T = uint32x4;   // full vector
                using H = uint32x2_t; // half vector


                /// Returns the lower/higher part of a vector. Cost: 0
                inline H lo(T a) {
                    return vget_low_u32(a.native());
                }
                inline H hi(T a) {
                    return vget_high_u32(a.native());
                }

                /// Cost: 1
                template <unsigned N> inline T bcast(T a) {
                    H h = (N < 2) ? lo(a) : hi(a);
                    return (uint32x4_t)vdupq_lane_u32(h, N % 2);
                }

                /// Combines two half vectors. Cost: 0
                inline T co(H lo, H hi) {
                    return vcombine_u32(lo, hi);
                }

                /// Reverses the elements in half-vector or half-vectors in a vector. Cost: 1
                inline H rev(H a) {
                    return vrev64_u32(a);
                }
                inline T rev(T a) {
                    return vrev64q_u32(a.native());
                }

                /// Duplicates the lower/higher element in the half-vector. Cost: 1
                inline H dup_lo(H a) {
                    return vdup_lane_u32(a, 0);
                }
                inline H dup_hi(H a) {
                    return vdup_lane_u32(a, 1);
                }

                /** Shuffles two half-vectors or one vector
                    Cost: If s0,s1 == 0,3 or 2,1 then 2, otherwise 0-1.
                */
                template <unsigned s0, unsigned s1> inline H shf2x2(H a, H b) {
                    const unsigned sel = s0 * 4 + s1;
                    switch (sel) {
                        default:
                        case 0: /*00*/
                            return dup_lo(a);
                        case 1: /*01*/
                            return a;
                        case 2: /*02*/
                            return vzip_u32(a, b).val[0];
                        case 3: /*03*/
                            return rev(vext_u32(b, a, 1));
                        case 4: /*10*/
                            return rev(a);
                        case 5: /*11*/
                            return dup_hi(a);
                        case 6: /*12*/
                            return vext_u32(a, b, 1);
                        case 7: /*13*/
                            return vzip_u32(a, b).val[1];
                        case 8: /*20*/
                            return vzip_u32(b, a).val[0];
                        case 9: /*21*/
                            return rev(vext_u32(a, b, 1));
                        case 10: /*22*/
                            return dup_lo(b);
                        case 11: /*23*/
                            return b;
                        case 12: /*30*/
                            return vext_u32(b, a, 1);
                        case 13: /*31*/
                            return vzip_u32(b, a).val[1];
                        case 14: /*32*/
                            return rev(b);
                        case 15: /*33*/
                            return dup_hi(b);
                    }
                }

                // The first element comes from a, the second from b.
                template <unsigned s0, unsigned s1> inline H shf_1x2(H a, H b) {
                    const unsigned sel = s0 * 2 + s1;
                    switch (sel) {
                        default:
                        case 0: /*00*/
                            return vzip_u32(a, b).val[0];
                            ;
                        case 1: /*01*/
                            return rev(vext_u32(b, a, 1));
                        case 2: /*10*/
                            return vext_u32(a, b, 1);
                        case 3: /*11*/
                            return vzip_u32(a, b).val[1];
                    }
                }

                template <unsigned sel> H sel_lo_hi(T a, T b) {
                    switch (sel) {
                        default:
                        case 0:
                            return lo(a);
                        case 1:
                            return hi(a);
                        case 2:
                            return lo(b);
                        case 3:
                            return hi(b);
                    }
                }

                template <unsigned s0, unsigned s1> inline H shf4x2(T a, T b) {
                    return shf_1x2<s0 % 2, s1 % 2>(sel_lo_hi<s0 / 2>(a, b), sel_lo_hi<s1 / 2>(a, b));
                }

                // 4-element permutations
                inline T perm4(_0, _0, _0, _0, T a) {
                    return bcast<0>(a);
                }
                inline T perm4(_1, _1, _1, _1, T a) {
                    return bcast<1>(a);
                }
                inline T perm4(_2, _2, _2, _2, T a) {
                    return bcast<2>(a);
                }
                inline T perm4(_3, _3, _3, _3, T a) {
                    return bcast<3>(a);
                }
                inline T perm4(_1, _0, _3, _2, T a) {
                    return rev(a);
                }

                template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                inline T perm4(std::integral_constant<unsigned, s0>,
                               std::integral_constant<unsigned, s1>,
                               std::integral_constant<unsigned, s2>,
                               std::integral_constant<unsigned, s3>,
                               const T &a) {
                    return co(shf2x2<s0, s1>(lo(a), hi(a)), shf2x2<s2, s3>(lo(a), hi(a)));
                }

                template <unsigned s0, unsigned s1, unsigned s2, unsigned s3> inline T permute4(T a) {
                    return perm4(std::integral_constant<unsigned, s0>{},
                                 std::integral_constant<unsigned, s1>{},
                                 std::integral_constant<unsigned, s2>{},
                                 std::integral_constant<unsigned, s3>{},
                                 a);
                }

                // 2-element shuffle: the first two elements must come from a, the last two -
                // from b
                template <unsigned s0, unsigned s1> inline T shuffle2(T a, T b) {
                    return co(shf2x2<s0, s1>(lo(a), hi(a)), shf2x2<s0, s1>(lo(b), hi(b)));
                }

                template <unsigned s0, unsigned s1, unsigned s2, unsigned s3> inline T shuffle2(T a, T b) {
                    return co(shf2x2<s0, s1>(lo(a), hi(a)), shf2x2<s2, s3>(lo(b), hi(b)));
                }

                // 4-element shuffle among two 2-element (sub) vectors
                template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                inline T shuffle2x2(const T &a, const T &b) {
                    return co(shf2x2<s0, s1>(lo(a), lo(b)), shf2x2<s2, s3>(hi(a), hi(b)));
                }

                // 8-element shuffle among two 4-element vectors
                template <unsigned s0, unsigned s1, unsigned s2, unsigned s3>
                inline T shuffle4x2(const T &a, const T &b) {
                    return co(shf4x2<s0, s1>(a, b), shf4x2<s2, s3>(a, b));
                }

            } // namespace neon_shuffle_int32x4
        }     // namespace detail
    }         // namespace SIMD_ARCH_NAMESPACE
} // namespace simd

#endif
#endif
