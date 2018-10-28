/**********************************************************************
 * BIGMATH INSIGHT CONFIDENTIAL
 *
 * Copyright (C) 2016-2018 BIGMATH CORPORATION, All Rights Reserved.
 *
 * @Author: Simon Zhang on 19 Oct 2018
 * @EMail: simon.zhangsm@hotmail.com
 * @Version: $BIGMATH_SIMD_LIB_VERSION
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
#ifndef SIMD_PREPROCESSOR_REPETITION_DETAIL_MSVC_FOR_HPP
#define SIMD_PREPROCESSOR_REPETITION_DETAIL_MSVC_FOR_HPP
#
#include <bigmath/simd/detail/preprocessor/control/if.hpp>
#include <bigmath/simd/detail/preprocessor/tuple/eat.hpp>
#
#define SIMD_FOR_1(s, p, o, m) \
    SIMD_IF(p(2, s), m, SIMD_TUPLE_EAT_2)(2, s) SIMD_IF(p(2, s), SIMD_FOR_2, SIMD_TUPLE_EAT_4)(o(2, s), p, o, m)
#define SIMD_FOR_2(s, p, o, m) \
    SIMD_IF(p(3, s), m, SIMD_TUPLE_EAT_2)(3, s) SIMD_IF(p(3, s), SIMD_FOR_3, SIMD_TUPLE_EAT_4)(o(3, s), p, o, m)
#define SIMD_FOR_3(s, p, o, m) \
    SIMD_IF(p(4, s), m, SIMD_TUPLE_EAT_2)(4, s) SIMD_IF(p(4, s), SIMD_FOR_4, SIMD_TUPLE_EAT_4)(o(4, s), p, o, m)
#define SIMD_FOR_4(s, p, o, m) \
    SIMD_IF(p(5, s), m, SIMD_TUPLE_EAT_2)(5, s) SIMD_IF(p(5, s), SIMD_FOR_5, SIMD_TUPLE_EAT_4)(o(5, s), p, o, m)
#define SIMD_FOR_5(s, p, o, m) \
    SIMD_IF(p(6, s), m, SIMD_TUPLE_EAT_2)(6, s) SIMD_IF(p(6, s), SIMD_FOR_6, SIMD_TUPLE_EAT_4)(o(6, s), p, o, m)
#define SIMD_FOR_6(s, p, o, m) \
    SIMD_IF(p(7, s), m, SIMD_TUPLE_EAT_2)(7, s) SIMD_IF(p(7, s), SIMD_FOR_7, SIMD_TUPLE_EAT_4)(o(7, s), p, o, m)
#define SIMD_FOR_7(s, p, o, m) \
    SIMD_IF(p(8, s), m, SIMD_TUPLE_EAT_2)(8, s) SIMD_IF(p(8, s), SIMD_FOR_8, SIMD_TUPLE_EAT_4)(o(8, s), p, o, m)
#define SIMD_FOR_8(s, p, o, m) \
    SIMD_IF(p(9, s), m, SIMD_TUPLE_EAT_2)(9, s) SIMD_IF(p(9, s), SIMD_FOR_9, SIMD_TUPLE_EAT_4)(o(9, s), p, o, m)
#define SIMD_FOR_9(s, p, o, m) \
    SIMD_IF(p(10, s), m, SIMD_TUPLE_EAT_2)(10, s) SIMD_IF(p(10, s), SIMD_FOR_10, SIMD_TUPLE_EAT_4)(o(10, s), p, o, m)
#define SIMD_FOR_10(s, p, o, m) \
    SIMD_IF(p(11, s), m, SIMD_TUPLE_EAT_2)(11, s) SIMD_IF(p(11, s), SIMD_FOR_11, SIMD_TUPLE_EAT_4)(o(11, s), p, o, m)
#define SIMD_FOR_11(s, p, o, m) \
    SIMD_IF(p(12, s), m, SIMD_TUPLE_EAT_2)(12, s) SIMD_IF(p(12, s), SIMD_FOR_12, SIMD_TUPLE_EAT_4)(o(12, s), p, o, m)
#define SIMD_FOR_12(s, p, o, m) \
    SIMD_IF(p(13, s), m, SIMD_TUPLE_EAT_2)(13, s) SIMD_IF(p(13, s), SIMD_FOR_13, SIMD_TUPLE_EAT_4)(o(13, s), p, o, m)
#define SIMD_FOR_13(s, p, o, m) \
    SIMD_IF(p(14, s), m, SIMD_TUPLE_EAT_2)(14, s) SIMD_IF(p(14, s), SIMD_FOR_14, SIMD_TUPLE_EAT_4)(o(14, s), p, o, m)
#define SIMD_FOR_14(s, p, o, m) \
    SIMD_IF(p(15, s), m, SIMD_TUPLE_EAT_2)(15, s) SIMD_IF(p(15, s), SIMD_FOR_15, SIMD_TUPLE_EAT_4)(o(15, s), p, o, m)
#define SIMD_FOR_15(s, p, o, m) \
    SIMD_IF(p(16, s), m, SIMD_TUPLE_EAT_2)(16, s) SIMD_IF(p(16, s), SIMD_FOR_16, SIMD_TUPLE_EAT_4)(o(16, s), p, o, m)
#define SIMD_FOR_16(s, p, o, m) \
    SIMD_IF(p(17, s), m, SIMD_TUPLE_EAT_2)(17, s) SIMD_IF(p(17, s), SIMD_FOR_17, SIMD_TUPLE_EAT_4)(o(17, s), p, o, m)
#define SIMD_FOR_17(s, p, o, m) \
    SIMD_IF(p(18, s), m, SIMD_TUPLE_EAT_2)(18, s) SIMD_IF(p(18, s), SIMD_FOR_18, SIMD_TUPLE_EAT_4)(o(18, s), p, o, m)
#define SIMD_FOR_18(s, p, o, m) \
    SIMD_IF(p(19, s), m, SIMD_TUPLE_EAT_2)(19, s) SIMD_IF(p(19, s), SIMD_FOR_19, SIMD_TUPLE_EAT_4)(o(19, s), p, o, m)
#define SIMD_FOR_19(s, p, o, m) \
    SIMD_IF(p(20, s), m, SIMD_TUPLE_EAT_2)(20, s) SIMD_IF(p(20, s), SIMD_FOR_20, SIMD_TUPLE_EAT_4)(o(20, s), p, o, m)
#define SIMD_FOR_20(s, p, o, m) \
    SIMD_IF(p(21, s), m, SIMD_TUPLE_EAT_2)(21, s) SIMD_IF(p(21, s), SIMD_FOR_21, SIMD_TUPLE_EAT_4)(o(21, s), p, o, m)
#define SIMD_FOR_21(s, p, o, m) \
    SIMD_IF(p(22, s), m, SIMD_TUPLE_EAT_2)(22, s) SIMD_IF(p(22, s), SIMD_FOR_22, SIMD_TUPLE_EAT_4)(o(22, s), p, o, m)
#define SIMD_FOR_22(s, p, o, m) \
    SIMD_IF(p(23, s), m, SIMD_TUPLE_EAT_2)(23, s) SIMD_IF(p(23, s), SIMD_FOR_23, SIMD_TUPLE_EAT_4)(o(23, s), p, o, m)
#define SIMD_FOR_23(s, p, o, m) \
    SIMD_IF(p(24, s), m, SIMD_TUPLE_EAT_2)(24, s) SIMD_IF(p(24, s), SIMD_FOR_24, SIMD_TUPLE_EAT_4)(o(24, s), p, o, m)
#define SIMD_FOR_24(s, p, o, m) \
    SIMD_IF(p(25, s), m, SIMD_TUPLE_EAT_2)(25, s) SIMD_IF(p(25, s), SIMD_FOR_25, SIMD_TUPLE_EAT_4)(o(25, s), p, o, m)
#define SIMD_FOR_25(s, p, o, m) \
    SIMD_IF(p(26, s), m, SIMD_TUPLE_EAT_2)(26, s) SIMD_IF(p(26, s), SIMD_FOR_26, SIMD_TUPLE_EAT_4)(o(26, s), p, o, m)
#define SIMD_FOR_26(s, p, o, m) \
    SIMD_IF(p(27, s), m, SIMD_TUPLE_EAT_2)(27, s) SIMD_IF(p(27, s), SIMD_FOR_27, SIMD_TUPLE_EAT_4)(o(27, s), p, o, m)
#define SIMD_FOR_27(s, p, o, m) \
    SIMD_IF(p(28, s), m, SIMD_TUPLE_EAT_2)(28, s) SIMD_IF(p(28, s), SIMD_FOR_28, SIMD_TUPLE_EAT_4)(o(28, s), p, o, m)
#define SIMD_FOR_28(s, p, o, m) \
    SIMD_IF(p(29, s), m, SIMD_TUPLE_EAT_2)(29, s) SIMD_IF(p(29, s), SIMD_FOR_29, SIMD_TUPLE_EAT_4)(o(29, s), p, o, m)
#define SIMD_FOR_29(s, p, o, m) \
    SIMD_IF(p(30, s), m, SIMD_TUPLE_EAT_2)(30, s) SIMD_IF(p(30, s), SIMD_FOR_30, SIMD_TUPLE_EAT_4)(o(30, s), p, o, m)
#define SIMD_FOR_30(s, p, o, m) \
    SIMD_IF(p(31, s), m, SIMD_TUPLE_EAT_2)(31, s) SIMD_IF(p(31, s), SIMD_FOR_31, SIMD_TUPLE_EAT_4)(o(31, s), p, o, m)
#define SIMD_FOR_31(s, p, o, m) \
    SIMD_IF(p(32, s), m, SIMD_TUPLE_EAT_2)(32, s) SIMD_IF(p(32, s), SIMD_FOR_32, SIMD_TUPLE_EAT_4)(o(32, s), p, o, m)
#define SIMD_FOR_32(s, p, o, m) \
    SIMD_IF(p(33, s), m, SIMD_TUPLE_EAT_2)(33, s) SIMD_IF(p(33, s), SIMD_FOR_33, SIMD_TUPLE_EAT_4)(o(33, s), p, o, m)
#define SIMD_FOR_33(s, p, o, m) \
    SIMD_IF(p(34, s), m, SIMD_TUPLE_EAT_2)(34, s) SIMD_IF(p(34, s), SIMD_FOR_34, SIMD_TUPLE_EAT_4)(o(34, s), p, o, m)
#define SIMD_FOR_34(s, p, o, m) \
    SIMD_IF(p(35, s), m, SIMD_TUPLE_EAT_2)(35, s) SIMD_IF(p(35, s), SIMD_FOR_35, SIMD_TUPLE_EAT_4)(o(35, s), p, o, m)
#define SIMD_FOR_35(s, p, o, m) \
    SIMD_IF(p(36, s), m, SIMD_TUPLE_EAT_2)(36, s) SIMD_IF(p(36, s), SIMD_FOR_36, SIMD_TUPLE_EAT_4)(o(36, s), p, o, m)
#define SIMD_FOR_36(s, p, o, m) \
    SIMD_IF(p(37, s), m, SIMD_TUPLE_EAT_2)(37, s) SIMD_IF(p(37, s), SIMD_FOR_37, SIMD_TUPLE_EAT_4)(o(37, s), p, o, m)
#define SIMD_FOR_37(s, p, o, m) \
    SIMD_IF(p(38, s), m, SIMD_TUPLE_EAT_2)(38, s) SIMD_IF(p(38, s), SIMD_FOR_38, SIMD_TUPLE_EAT_4)(o(38, s), p, o, m)
#define SIMD_FOR_38(s, p, o, m) \
    SIMD_IF(p(39, s), m, SIMD_TUPLE_EAT_2)(39, s) SIMD_IF(p(39, s), SIMD_FOR_39, SIMD_TUPLE_EAT_4)(o(39, s), p, o, m)
#define SIMD_FOR_39(s, p, o, m) \
    SIMD_IF(p(40, s), m, SIMD_TUPLE_EAT_2)(40, s) SIMD_IF(p(40, s), SIMD_FOR_40, SIMD_TUPLE_EAT_4)(o(40, s), p, o, m)
#define SIMD_FOR_40(s, p, o, m) \
    SIMD_IF(p(41, s), m, SIMD_TUPLE_EAT_2)(41, s) SIMD_IF(p(41, s), SIMD_FOR_41, SIMD_TUPLE_EAT_4)(o(41, s), p, o, m)
#define SIMD_FOR_41(s, p, o, m) \
    SIMD_IF(p(42, s), m, SIMD_TUPLE_EAT_2)(42, s) SIMD_IF(p(42, s), SIMD_FOR_42, SIMD_TUPLE_EAT_4)(o(42, s), p, o, m)
#define SIMD_FOR_42(s, p, o, m) \
    SIMD_IF(p(43, s), m, SIMD_TUPLE_EAT_2)(43, s) SIMD_IF(p(43, s), SIMD_FOR_43, SIMD_TUPLE_EAT_4)(o(43, s), p, o, m)
#define SIMD_FOR_43(s, p, o, m) \
    SIMD_IF(p(44, s), m, SIMD_TUPLE_EAT_2)(44, s) SIMD_IF(p(44, s), SIMD_FOR_44, SIMD_TUPLE_EAT_4)(o(44, s), p, o, m)
#define SIMD_FOR_44(s, p, o, m) \
    SIMD_IF(p(45, s), m, SIMD_TUPLE_EAT_2)(45, s) SIMD_IF(p(45, s), SIMD_FOR_45, SIMD_TUPLE_EAT_4)(o(45, s), p, o, m)
#define SIMD_FOR_45(s, p, o, m) \
    SIMD_IF(p(46, s), m, SIMD_TUPLE_EAT_2)(46, s) SIMD_IF(p(46, s), SIMD_FOR_46, SIMD_TUPLE_EAT_4)(o(46, s), p, o, m)
#define SIMD_FOR_46(s, p, o, m) \
    SIMD_IF(p(47, s), m, SIMD_TUPLE_EAT_2)(47, s) SIMD_IF(p(47, s), SIMD_FOR_47, SIMD_TUPLE_EAT_4)(o(47, s), p, o, m)
#define SIMD_FOR_47(s, p, o, m) \
    SIMD_IF(p(48, s), m, SIMD_TUPLE_EAT_2)(48, s) SIMD_IF(p(48, s), SIMD_FOR_48, SIMD_TUPLE_EAT_4)(o(48, s), p, o, m)
#define SIMD_FOR_48(s, p, o, m) \
    SIMD_IF(p(49, s), m, SIMD_TUPLE_EAT_2)(49, s) SIMD_IF(p(49, s), SIMD_FOR_49, SIMD_TUPLE_EAT_4)(o(49, s), p, o, m)
#define SIMD_FOR_49(s, p, o, m) \
    SIMD_IF(p(50, s), m, SIMD_TUPLE_EAT_2)(50, s) SIMD_IF(p(50, s), SIMD_FOR_50, SIMD_TUPLE_EAT_4)(o(50, s), p, o, m)
#define SIMD_FOR_50(s, p, o, m) \
    SIMD_IF(p(51, s), m, SIMD_TUPLE_EAT_2)(51, s) SIMD_IF(p(51, s), SIMD_FOR_51, SIMD_TUPLE_EAT_4)(o(51, s), p, o, m)
#define SIMD_FOR_51(s, p, o, m) \
    SIMD_IF(p(52, s), m, SIMD_TUPLE_EAT_2)(52, s) SIMD_IF(p(52, s), SIMD_FOR_52, SIMD_TUPLE_EAT_4)(o(52, s), p, o, m)
#define SIMD_FOR_52(s, p, o, m) \
    SIMD_IF(p(53, s), m, SIMD_TUPLE_EAT_2)(53, s) SIMD_IF(p(53, s), SIMD_FOR_53, SIMD_TUPLE_EAT_4)(o(53, s), p, o, m)
#define SIMD_FOR_53(s, p, o, m) \
    SIMD_IF(p(54, s), m, SIMD_TUPLE_EAT_2)(54, s) SIMD_IF(p(54, s), SIMD_FOR_54, SIMD_TUPLE_EAT_4)(o(54, s), p, o, m)
#define SIMD_FOR_54(s, p, o, m) \
    SIMD_IF(p(55, s), m, SIMD_TUPLE_EAT_2)(55, s) SIMD_IF(p(55, s), SIMD_FOR_55, SIMD_TUPLE_EAT_4)(o(55, s), p, o, m)
#define SIMD_FOR_55(s, p, o, m) \
    SIMD_IF(p(56, s), m, SIMD_TUPLE_EAT_2)(56, s) SIMD_IF(p(56, s), SIMD_FOR_56, SIMD_TUPLE_EAT_4)(o(56, s), p, o, m)
#define SIMD_FOR_56(s, p, o, m) \
    SIMD_IF(p(57, s), m, SIMD_TUPLE_EAT_2)(57, s) SIMD_IF(p(57, s), SIMD_FOR_57, SIMD_TUPLE_EAT_4)(o(57, s), p, o, m)
#define SIMD_FOR_57(s, p, o, m) \
    SIMD_IF(p(58, s), m, SIMD_TUPLE_EAT_2)(58, s) SIMD_IF(p(58, s), SIMD_FOR_58, SIMD_TUPLE_EAT_4)(o(58, s), p, o, m)
#define SIMD_FOR_58(s, p, o, m) \
    SIMD_IF(p(59, s), m, SIMD_TUPLE_EAT_2)(59, s) SIMD_IF(p(59, s), SIMD_FOR_59, SIMD_TUPLE_EAT_4)(o(59, s), p, o, m)
#define SIMD_FOR_59(s, p, o, m) \
    SIMD_IF(p(60, s), m, SIMD_TUPLE_EAT_2)(60, s) SIMD_IF(p(60, s), SIMD_FOR_60, SIMD_TUPLE_EAT_4)(o(60, s), p, o, m)
#define SIMD_FOR_60(s, p, o, m) \
    SIMD_IF(p(61, s), m, SIMD_TUPLE_EAT_2)(61, s) SIMD_IF(p(61, s), SIMD_FOR_61, SIMD_TUPLE_EAT_4)(o(61, s), p, o, m)
#define SIMD_FOR_61(s, p, o, m) \
    SIMD_IF(p(62, s), m, SIMD_TUPLE_EAT_2)(62, s) SIMD_IF(p(62, s), SIMD_FOR_62, SIMD_TUPLE_EAT_4)(o(62, s), p, o, m)
#define SIMD_FOR_62(s, p, o, m) \
    SIMD_IF(p(63, s), m, SIMD_TUPLE_EAT_2)(63, s) SIMD_IF(p(63, s), SIMD_FOR_63, SIMD_TUPLE_EAT_4)(o(63, s), p, o, m)
#define SIMD_FOR_63(s, p, o, m) \
    SIMD_IF(p(64, s), m, SIMD_TUPLE_EAT_2)(64, s) SIMD_IF(p(64, s), SIMD_FOR_64, SIMD_TUPLE_EAT_4)(o(64, s), p, o, m)
#define SIMD_FOR_64(s, p, o, m) \
    SIMD_IF(p(65, s), m, SIMD_TUPLE_EAT_2)(65, s) SIMD_IF(p(65, s), SIMD_FOR_65, SIMD_TUPLE_EAT_4)(o(65, s), p, o, m)
#define SIMD_FOR_65(s, p, o, m) \
    SIMD_IF(p(66, s), m, SIMD_TUPLE_EAT_2)(66, s) SIMD_IF(p(66, s), SIMD_FOR_66, SIMD_TUPLE_EAT_4)(o(66, s), p, o, m)
#define SIMD_FOR_66(s, p, o, m) \
    SIMD_IF(p(67, s), m, SIMD_TUPLE_EAT_2)(67, s) SIMD_IF(p(67, s), SIMD_FOR_67, SIMD_TUPLE_EAT_4)(o(67, s), p, o, m)
#define SIMD_FOR_67(s, p, o, m) \
    SIMD_IF(p(68, s), m, SIMD_TUPLE_EAT_2)(68, s) SIMD_IF(p(68, s), SIMD_FOR_68, SIMD_TUPLE_EAT_4)(o(68, s), p, o, m)
#define SIMD_FOR_68(s, p, o, m) \
    SIMD_IF(p(69, s), m, SIMD_TUPLE_EAT_2)(69, s) SIMD_IF(p(69, s), SIMD_FOR_69, SIMD_TUPLE_EAT_4)(o(69, s), p, o, m)
#define SIMD_FOR_69(s, p, o, m) \
    SIMD_IF(p(70, s), m, SIMD_TUPLE_EAT_2)(70, s) SIMD_IF(p(70, s), SIMD_FOR_70, SIMD_TUPLE_EAT_4)(o(70, s), p, o, m)
#define SIMD_FOR_70(s, p, o, m) \
    SIMD_IF(p(71, s), m, SIMD_TUPLE_EAT_2)(71, s) SIMD_IF(p(71, s), SIMD_FOR_71, SIMD_TUPLE_EAT_4)(o(71, s), p, o, m)
#define SIMD_FOR_71(s, p, o, m) \
    SIMD_IF(p(72, s), m, SIMD_TUPLE_EAT_2)(72, s) SIMD_IF(p(72, s), SIMD_FOR_72, SIMD_TUPLE_EAT_4)(o(72, s), p, o, m)
#define SIMD_FOR_72(s, p, o, m) \
    SIMD_IF(p(73, s), m, SIMD_TUPLE_EAT_2)(73, s) SIMD_IF(p(73, s), SIMD_FOR_73, SIMD_TUPLE_EAT_4)(o(73, s), p, o, m)
#define SIMD_FOR_73(s, p, o, m) \
    SIMD_IF(p(74, s), m, SIMD_TUPLE_EAT_2)(74, s) SIMD_IF(p(74, s), SIMD_FOR_74, SIMD_TUPLE_EAT_4)(o(74, s), p, o, m)
#define SIMD_FOR_74(s, p, o, m) \
    SIMD_IF(p(75, s), m, SIMD_TUPLE_EAT_2)(75, s) SIMD_IF(p(75, s), SIMD_FOR_75, SIMD_TUPLE_EAT_4)(o(75, s), p, o, m)
#define SIMD_FOR_75(s, p, o, m) \
    SIMD_IF(p(76, s), m, SIMD_TUPLE_EAT_2)(76, s) SIMD_IF(p(76, s), SIMD_FOR_76, SIMD_TUPLE_EAT_4)(o(76, s), p, o, m)
#define SIMD_FOR_76(s, p, o, m) \
    SIMD_IF(p(77, s), m, SIMD_TUPLE_EAT_2)(77, s) SIMD_IF(p(77, s), SIMD_FOR_77, SIMD_TUPLE_EAT_4)(o(77, s), p, o, m)
#define SIMD_FOR_77(s, p, o, m) \
    SIMD_IF(p(78, s), m, SIMD_TUPLE_EAT_2)(78, s) SIMD_IF(p(78, s), SIMD_FOR_78, SIMD_TUPLE_EAT_4)(o(78, s), p, o, m)
#define SIMD_FOR_78(s, p, o, m) \
    SIMD_IF(p(79, s), m, SIMD_TUPLE_EAT_2)(79, s) SIMD_IF(p(79, s), SIMD_FOR_79, SIMD_TUPLE_EAT_4)(o(79, s), p, o, m)
#define SIMD_FOR_79(s, p, o, m) \
    SIMD_IF(p(80, s), m, SIMD_TUPLE_EAT_2)(80, s) SIMD_IF(p(80, s), SIMD_FOR_80, SIMD_TUPLE_EAT_4)(o(80, s), p, o, m)
#define SIMD_FOR_80(s, p, o, m) \
    SIMD_IF(p(81, s), m, SIMD_TUPLE_EAT_2)(81, s) SIMD_IF(p(81, s), SIMD_FOR_81, SIMD_TUPLE_EAT_4)(o(81, s), p, o, m)
#define SIMD_FOR_81(s, p, o, m) \
    SIMD_IF(p(82, s), m, SIMD_TUPLE_EAT_2)(82, s) SIMD_IF(p(82, s), SIMD_FOR_82, SIMD_TUPLE_EAT_4)(o(82, s), p, o, m)
#define SIMD_FOR_82(s, p, o, m) \
    SIMD_IF(p(83, s), m, SIMD_TUPLE_EAT_2)(83, s) SIMD_IF(p(83, s), SIMD_FOR_83, SIMD_TUPLE_EAT_4)(o(83, s), p, o, m)
#define SIMD_FOR_83(s, p, o, m) \
    SIMD_IF(p(84, s), m, SIMD_TUPLE_EAT_2)(84, s) SIMD_IF(p(84, s), SIMD_FOR_84, SIMD_TUPLE_EAT_4)(o(84, s), p, o, m)
#define SIMD_FOR_84(s, p, o, m) \
    SIMD_IF(p(85, s), m, SIMD_TUPLE_EAT_2)(85, s) SIMD_IF(p(85, s), SIMD_FOR_85, SIMD_TUPLE_EAT_4)(o(85, s), p, o, m)
#define SIMD_FOR_85(s, p, o, m) \
    SIMD_IF(p(86, s), m, SIMD_TUPLE_EAT_2)(86, s) SIMD_IF(p(86, s), SIMD_FOR_86, SIMD_TUPLE_EAT_4)(o(86, s), p, o, m)
#define SIMD_FOR_86(s, p, o, m) \
    SIMD_IF(p(87, s), m, SIMD_TUPLE_EAT_2)(87, s) SIMD_IF(p(87, s), SIMD_FOR_87, SIMD_TUPLE_EAT_4)(o(87, s), p, o, m)
#define SIMD_FOR_87(s, p, o, m) \
    SIMD_IF(p(88, s), m, SIMD_TUPLE_EAT_2)(88, s) SIMD_IF(p(88, s), SIMD_FOR_88, SIMD_TUPLE_EAT_4)(o(88, s), p, o, m)
#define SIMD_FOR_88(s, p, o, m) \
    SIMD_IF(p(89, s), m, SIMD_TUPLE_EAT_2)(89, s) SIMD_IF(p(89, s), SIMD_FOR_89, SIMD_TUPLE_EAT_4)(o(89, s), p, o, m)
#define SIMD_FOR_89(s, p, o, m) \
    SIMD_IF(p(90, s), m, SIMD_TUPLE_EAT_2)(90, s) SIMD_IF(p(90, s), SIMD_FOR_90, SIMD_TUPLE_EAT_4)(o(90, s), p, o, m)
#define SIMD_FOR_90(s, p, o, m) \
    SIMD_IF(p(91, s), m, SIMD_TUPLE_EAT_2)(91, s) SIMD_IF(p(91, s), SIMD_FOR_91, SIMD_TUPLE_EAT_4)(o(91, s), p, o, m)
#define SIMD_FOR_91(s, p, o, m) \
    SIMD_IF(p(92, s), m, SIMD_TUPLE_EAT_2)(92, s) SIMD_IF(p(92, s), SIMD_FOR_92, SIMD_TUPLE_EAT_4)(o(92, s), p, o, m)
#define SIMD_FOR_92(s, p, o, m) \
    SIMD_IF(p(93, s), m, SIMD_TUPLE_EAT_2)(93, s) SIMD_IF(p(93, s), SIMD_FOR_93, SIMD_TUPLE_EAT_4)(o(93, s), p, o, m)
#define SIMD_FOR_93(s, p, o, m) \
    SIMD_IF(p(94, s), m, SIMD_TUPLE_EAT_2)(94, s) SIMD_IF(p(94, s), SIMD_FOR_94, SIMD_TUPLE_EAT_4)(o(94, s), p, o, m)
#define SIMD_FOR_94(s, p, o, m) \
    SIMD_IF(p(95, s), m, SIMD_TUPLE_EAT_2)(95, s) SIMD_IF(p(95, s), SIMD_FOR_95, SIMD_TUPLE_EAT_4)(o(95, s), p, o, m)
#define SIMD_FOR_95(s, p, o, m) \
    SIMD_IF(p(96, s), m, SIMD_TUPLE_EAT_2)(96, s) SIMD_IF(p(96, s), SIMD_FOR_96, SIMD_TUPLE_EAT_4)(o(96, s), p, o, m)
#define SIMD_FOR_96(s, p, o, m) \
    SIMD_IF(p(97, s), m, SIMD_TUPLE_EAT_2)(97, s) SIMD_IF(p(97, s), SIMD_FOR_97, SIMD_TUPLE_EAT_4)(o(97, s), p, o, m)
#define SIMD_FOR_97(s, p, o, m) \
    SIMD_IF(p(98, s), m, SIMD_TUPLE_EAT_2)(98, s) SIMD_IF(p(98, s), SIMD_FOR_98, SIMD_TUPLE_EAT_4)(o(98, s), p, o, m)
#define SIMD_FOR_98(s, p, o, m) \
    SIMD_IF(p(99, s), m, SIMD_TUPLE_EAT_2)(99, s) SIMD_IF(p(99, s), SIMD_FOR_99, SIMD_TUPLE_EAT_4)(o(99, s), p, o, m)
#define SIMD_FOR_99(s, p, o, m)             \
    SIMD_IF(p(100, s), m, SIMD_TUPLE_EAT_2) \
    (100, s) SIMD_IF(p(100, s), SIMD_FOR_100, SIMD_TUPLE_EAT_4)(o(100, s), p, o, m)
#define SIMD_FOR_100(s, p, o, m)            \
    SIMD_IF(p(101, s), m, SIMD_TUPLE_EAT_2) \
    (101, s) SIMD_IF(p(101, s), SIMD_FOR_101, SIMD_TUPLE_EAT_4)(o(101, s), p, o, m)
#define SIMD_FOR_101(s, p, o, m)            \
    SIMD_IF(p(102, s), m, SIMD_TUPLE_EAT_2) \
    (102, s) SIMD_IF(p(102, s), SIMD_FOR_102, SIMD_TUPLE_EAT_4)(o(102, s), p, o, m)
#define SIMD_FOR_102(s, p, o, m)            \
    SIMD_IF(p(103, s), m, SIMD_TUPLE_EAT_2) \
    (103, s) SIMD_IF(p(103, s), SIMD_FOR_103, SIMD_TUPLE_EAT_4)(o(103, s), p, o, m)
#define SIMD_FOR_103(s, p, o, m)            \
    SIMD_IF(p(104, s), m, SIMD_TUPLE_EAT_2) \
    (104, s) SIMD_IF(p(104, s), SIMD_FOR_104, SIMD_TUPLE_EAT_4)(o(104, s), p, o, m)
#define SIMD_FOR_104(s, p, o, m)            \
    SIMD_IF(p(105, s), m, SIMD_TUPLE_EAT_2) \
    (105, s) SIMD_IF(p(105, s), SIMD_FOR_105, SIMD_TUPLE_EAT_4)(o(105, s), p, o, m)
#define SIMD_FOR_105(s, p, o, m)            \
    SIMD_IF(p(106, s), m, SIMD_TUPLE_EAT_2) \
    (106, s) SIMD_IF(p(106, s), SIMD_FOR_106, SIMD_TUPLE_EAT_4)(o(106, s), p, o, m)
#define SIMD_FOR_106(s, p, o, m)            \
    SIMD_IF(p(107, s), m, SIMD_TUPLE_EAT_2) \
    (107, s) SIMD_IF(p(107, s), SIMD_FOR_107, SIMD_TUPLE_EAT_4)(o(107, s), p, o, m)
#define SIMD_FOR_107(s, p, o, m)            \
    SIMD_IF(p(108, s), m, SIMD_TUPLE_EAT_2) \
    (108, s) SIMD_IF(p(108, s), SIMD_FOR_108, SIMD_TUPLE_EAT_4)(o(108, s), p, o, m)
#define SIMD_FOR_108(s, p, o, m)            \
    SIMD_IF(p(109, s), m, SIMD_TUPLE_EAT_2) \
    (109, s) SIMD_IF(p(109, s), SIMD_FOR_109, SIMD_TUPLE_EAT_4)(o(109, s), p, o, m)
#define SIMD_FOR_109(s, p, o, m)            \
    SIMD_IF(p(110, s), m, SIMD_TUPLE_EAT_2) \
    (110, s) SIMD_IF(p(110, s), SIMD_FOR_110, SIMD_TUPLE_EAT_4)(o(110, s), p, o, m)
#define SIMD_FOR_110(s, p, o, m)            \
    SIMD_IF(p(111, s), m, SIMD_TUPLE_EAT_2) \
    (111, s) SIMD_IF(p(111, s), SIMD_FOR_111, SIMD_TUPLE_EAT_4)(o(111, s), p, o, m)
#define SIMD_FOR_111(s, p, o, m)            \
    SIMD_IF(p(112, s), m, SIMD_TUPLE_EAT_2) \
    (112, s) SIMD_IF(p(112, s), SIMD_FOR_112, SIMD_TUPLE_EAT_4)(o(112, s), p, o, m)
#define SIMD_FOR_112(s, p, o, m)            \
    SIMD_IF(p(113, s), m, SIMD_TUPLE_EAT_2) \
    (113, s) SIMD_IF(p(113, s), SIMD_FOR_113, SIMD_TUPLE_EAT_4)(o(113, s), p, o, m)
#define SIMD_FOR_113(s, p, o, m)            \
    SIMD_IF(p(114, s), m, SIMD_TUPLE_EAT_2) \
    (114, s) SIMD_IF(p(114, s), SIMD_FOR_114, SIMD_TUPLE_EAT_4)(o(114, s), p, o, m)
#define SIMD_FOR_114(s, p, o, m)            \
    SIMD_IF(p(115, s), m, SIMD_TUPLE_EAT_2) \
    (115, s) SIMD_IF(p(115, s), SIMD_FOR_115, SIMD_TUPLE_EAT_4)(o(115, s), p, o, m)
#define SIMD_FOR_115(s, p, o, m)            \
    SIMD_IF(p(116, s), m, SIMD_TUPLE_EAT_2) \
    (116, s) SIMD_IF(p(116, s), SIMD_FOR_116, SIMD_TUPLE_EAT_4)(o(116, s), p, o, m)
#define SIMD_FOR_116(s, p, o, m)            \
    SIMD_IF(p(117, s), m, SIMD_TUPLE_EAT_2) \
    (117, s) SIMD_IF(p(117, s), SIMD_FOR_117, SIMD_TUPLE_EAT_4)(o(117, s), p, o, m)
#define SIMD_FOR_117(s, p, o, m)            \
    SIMD_IF(p(118, s), m, SIMD_TUPLE_EAT_2) \
    (118, s) SIMD_IF(p(118, s), SIMD_FOR_118, SIMD_TUPLE_EAT_4)(o(118, s), p, o, m)
#define SIMD_FOR_118(s, p, o, m)            \
    SIMD_IF(p(119, s), m, SIMD_TUPLE_EAT_2) \
    (119, s) SIMD_IF(p(119, s), SIMD_FOR_119, SIMD_TUPLE_EAT_4)(o(119, s), p, o, m)
#define SIMD_FOR_119(s, p, o, m)            \
    SIMD_IF(p(120, s), m, SIMD_TUPLE_EAT_2) \
    (120, s) SIMD_IF(p(120, s), SIMD_FOR_120, SIMD_TUPLE_EAT_4)(o(120, s), p, o, m)
#define SIMD_FOR_120(s, p, o, m)            \
    SIMD_IF(p(121, s), m, SIMD_TUPLE_EAT_2) \
    (121, s) SIMD_IF(p(121, s), SIMD_FOR_121, SIMD_TUPLE_EAT_4)(o(121, s), p, o, m)
#define SIMD_FOR_121(s, p, o, m)            \
    SIMD_IF(p(122, s), m, SIMD_TUPLE_EAT_2) \
    (122, s) SIMD_IF(p(122, s), SIMD_FOR_122, SIMD_TUPLE_EAT_4)(o(122, s), p, o, m)
#define SIMD_FOR_122(s, p, o, m)            \
    SIMD_IF(p(123, s), m, SIMD_TUPLE_EAT_2) \
    (123, s) SIMD_IF(p(123, s), SIMD_FOR_123, SIMD_TUPLE_EAT_4)(o(123, s), p, o, m)
#define SIMD_FOR_123(s, p, o, m)            \
    SIMD_IF(p(124, s), m, SIMD_TUPLE_EAT_2) \
    (124, s) SIMD_IF(p(124, s), SIMD_FOR_124, SIMD_TUPLE_EAT_4)(o(124, s), p, o, m)
#define SIMD_FOR_124(s, p, o, m)            \
    SIMD_IF(p(125, s), m, SIMD_TUPLE_EAT_2) \
    (125, s) SIMD_IF(p(125, s), SIMD_FOR_125, SIMD_TUPLE_EAT_4)(o(125, s), p, o, m)
#define SIMD_FOR_125(s, p, o, m)            \
    SIMD_IF(p(126, s), m, SIMD_TUPLE_EAT_2) \
    (126, s) SIMD_IF(p(126, s), SIMD_FOR_126, SIMD_TUPLE_EAT_4)(o(126, s), p, o, m)
#define SIMD_FOR_126(s, p, o, m)            \
    SIMD_IF(p(127, s), m, SIMD_TUPLE_EAT_2) \
    (127, s) SIMD_IF(p(127, s), SIMD_FOR_127, SIMD_TUPLE_EAT_4)(o(127, s), p, o, m)
#define SIMD_FOR_127(s, p, o, m)            \
    SIMD_IF(p(128, s), m, SIMD_TUPLE_EAT_2) \
    (128, s) SIMD_IF(p(128, s), SIMD_FOR_128, SIMD_TUPLE_EAT_4)(o(128, s), p, o, m)
#define SIMD_FOR_128(s, p, o, m)            \
    SIMD_IF(p(129, s), m, SIMD_TUPLE_EAT_2) \
    (129, s) SIMD_IF(p(129, s), SIMD_FOR_129, SIMD_TUPLE_EAT_4)(o(129, s), p, o, m)
#define SIMD_FOR_129(s, p, o, m)            \
    SIMD_IF(p(130, s), m, SIMD_TUPLE_EAT_2) \
    (130, s) SIMD_IF(p(130, s), SIMD_FOR_130, SIMD_TUPLE_EAT_4)(o(130, s), p, o, m)
#define SIMD_FOR_130(s, p, o, m)            \
    SIMD_IF(p(131, s), m, SIMD_TUPLE_EAT_2) \
    (131, s) SIMD_IF(p(131, s), SIMD_FOR_131, SIMD_TUPLE_EAT_4)(o(131, s), p, o, m)
#define SIMD_FOR_131(s, p, o, m)            \
    SIMD_IF(p(132, s), m, SIMD_TUPLE_EAT_2) \
    (132, s) SIMD_IF(p(132, s), SIMD_FOR_132, SIMD_TUPLE_EAT_4)(o(132, s), p, o, m)
#define SIMD_FOR_132(s, p, o, m)            \
    SIMD_IF(p(133, s), m, SIMD_TUPLE_EAT_2) \
    (133, s) SIMD_IF(p(133, s), SIMD_FOR_133, SIMD_TUPLE_EAT_4)(o(133, s), p, o, m)
#define SIMD_FOR_133(s, p, o, m)            \
    SIMD_IF(p(134, s), m, SIMD_TUPLE_EAT_2) \
    (134, s) SIMD_IF(p(134, s), SIMD_FOR_134, SIMD_TUPLE_EAT_4)(o(134, s), p, o, m)
#define SIMD_FOR_134(s, p, o, m)            \
    SIMD_IF(p(135, s), m, SIMD_TUPLE_EAT_2) \
    (135, s) SIMD_IF(p(135, s), SIMD_FOR_135, SIMD_TUPLE_EAT_4)(o(135, s), p, o, m)
#define SIMD_FOR_135(s, p, o, m)            \
    SIMD_IF(p(136, s), m, SIMD_TUPLE_EAT_2) \
    (136, s) SIMD_IF(p(136, s), SIMD_FOR_136, SIMD_TUPLE_EAT_4)(o(136, s), p, o, m)
#define SIMD_FOR_136(s, p, o, m)            \
    SIMD_IF(p(137, s), m, SIMD_TUPLE_EAT_2) \
    (137, s) SIMD_IF(p(137, s), SIMD_FOR_137, SIMD_TUPLE_EAT_4)(o(137, s), p, o, m)
#define SIMD_FOR_137(s, p, o, m)            \
    SIMD_IF(p(138, s), m, SIMD_TUPLE_EAT_2) \
    (138, s) SIMD_IF(p(138, s), SIMD_FOR_138, SIMD_TUPLE_EAT_4)(o(138, s), p, o, m)
#define SIMD_FOR_138(s, p, o, m)            \
    SIMD_IF(p(139, s), m, SIMD_TUPLE_EAT_2) \
    (139, s) SIMD_IF(p(139, s), SIMD_FOR_139, SIMD_TUPLE_EAT_4)(o(139, s), p, o, m)
#define SIMD_FOR_139(s, p, o, m)            \
    SIMD_IF(p(140, s), m, SIMD_TUPLE_EAT_2) \
    (140, s) SIMD_IF(p(140, s), SIMD_FOR_140, SIMD_TUPLE_EAT_4)(o(140, s), p, o, m)
#define SIMD_FOR_140(s, p, o, m)            \
    SIMD_IF(p(141, s), m, SIMD_TUPLE_EAT_2) \
    (141, s) SIMD_IF(p(141, s), SIMD_FOR_141, SIMD_TUPLE_EAT_4)(o(141, s), p, o, m)
#define SIMD_FOR_141(s, p, o, m)            \
    SIMD_IF(p(142, s), m, SIMD_TUPLE_EAT_2) \
    (142, s) SIMD_IF(p(142, s), SIMD_FOR_142, SIMD_TUPLE_EAT_4)(o(142, s), p, o, m)
#define SIMD_FOR_142(s, p, o, m)            \
    SIMD_IF(p(143, s), m, SIMD_TUPLE_EAT_2) \
    (143, s) SIMD_IF(p(143, s), SIMD_FOR_143, SIMD_TUPLE_EAT_4)(o(143, s), p, o, m)
#define SIMD_FOR_143(s, p, o, m)            \
    SIMD_IF(p(144, s), m, SIMD_TUPLE_EAT_2) \
    (144, s) SIMD_IF(p(144, s), SIMD_FOR_144, SIMD_TUPLE_EAT_4)(o(144, s), p, o, m)
#define SIMD_FOR_144(s, p, o, m)            \
    SIMD_IF(p(145, s), m, SIMD_TUPLE_EAT_2) \
    (145, s) SIMD_IF(p(145, s), SIMD_FOR_145, SIMD_TUPLE_EAT_4)(o(145, s), p, o, m)
#define SIMD_FOR_145(s, p, o, m)            \
    SIMD_IF(p(146, s), m, SIMD_TUPLE_EAT_2) \
    (146, s) SIMD_IF(p(146, s), SIMD_FOR_146, SIMD_TUPLE_EAT_4)(o(146, s), p, o, m)
#define SIMD_FOR_146(s, p, o, m)            \
    SIMD_IF(p(147, s), m, SIMD_TUPLE_EAT_2) \
    (147, s) SIMD_IF(p(147, s), SIMD_FOR_147, SIMD_TUPLE_EAT_4)(o(147, s), p, o, m)
#define SIMD_FOR_147(s, p, o, m)            \
    SIMD_IF(p(148, s), m, SIMD_TUPLE_EAT_2) \
    (148, s) SIMD_IF(p(148, s), SIMD_FOR_148, SIMD_TUPLE_EAT_4)(o(148, s), p, o, m)
#define SIMD_FOR_148(s, p, o, m)            \
    SIMD_IF(p(149, s), m, SIMD_TUPLE_EAT_2) \
    (149, s) SIMD_IF(p(149, s), SIMD_FOR_149, SIMD_TUPLE_EAT_4)(o(149, s), p, o, m)
#define SIMD_FOR_149(s, p, o, m)            \
    SIMD_IF(p(150, s), m, SIMD_TUPLE_EAT_2) \
    (150, s) SIMD_IF(p(150, s), SIMD_FOR_150, SIMD_TUPLE_EAT_4)(o(150, s), p, o, m)
#define SIMD_FOR_150(s, p, o, m)            \
    SIMD_IF(p(151, s), m, SIMD_TUPLE_EAT_2) \
    (151, s) SIMD_IF(p(151, s), SIMD_FOR_151, SIMD_TUPLE_EAT_4)(o(151, s), p, o, m)
#define SIMD_FOR_151(s, p, o, m)            \
    SIMD_IF(p(152, s), m, SIMD_TUPLE_EAT_2) \
    (152, s) SIMD_IF(p(152, s), SIMD_FOR_152, SIMD_TUPLE_EAT_4)(o(152, s), p, o, m)
#define SIMD_FOR_152(s, p, o, m)            \
    SIMD_IF(p(153, s), m, SIMD_TUPLE_EAT_2) \
    (153, s) SIMD_IF(p(153, s), SIMD_FOR_153, SIMD_TUPLE_EAT_4)(o(153, s), p, o, m)
#define SIMD_FOR_153(s, p, o, m)            \
    SIMD_IF(p(154, s), m, SIMD_TUPLE_EAT_2) \
    (154, s) SIMD_IF(p(154, s), SIMD_FOR_154, SIMD_TUPLE_EAT_4)(o(154, s), p, o, m)
#define SIMD_FOR_154(s, p, o, m)            \
    SIMD_IF(p(155, s), m, SIMD_TUPLE_EAT_2) \
    (155, s) SIMD_IF(p(155, s), SIMD_FOR_155, SIMD_TUPLE_EAT_4)(o(155, s), p, o, m)
#define SIMD_FOR_155(s, p, o, m)            \
    SIMD_IF(p(156, s), m, SIMD_TUPLE_EAT_2) \
    (156, s) SIMD_IF(p(156, s), SIMD_FOR_156, SIMD_TUPLE_EAT_4)(o(156, s), p, o, m)
#define SIMD_FOR_156(s, p, o, m)            \
    SIMD_IF(p(157, s), m, SIMD_TUPLE_EAT_2) \
    (157, s) SIMD_IF(p(157, s), SIMD_FOR_157, SIMD_TUPLE_EAT_4)(o(157, s), p, o, m)
#define SIMD_FOR_157(s, p, o, m)            \
    SIMD_IF(p(158, s), m, SIMD_TUPLE_EAT_2) \
    (158, s) SIMD_IF(p(158, s), SIMD_FOR_158, SIMD_TUPLE_EAT_4)(o(158, s), p, o, m)
#define SIMD_FOR_158(s, p, o, m)            \
    SIMD_IF(p(159, s), m, SIMD_TUPLE_EAT_2) \
    (159, s) SIMD_IF(p(159, s), SIMD_FOR_159, SIMD_TUPLE_EAT_4)(o(159, s), p, o, m)
#define SIMD_FOR_159(s, p, o, m)            \
    SIMD_IF(p(160, s), m, SIMD_TUPLE_EAT_2) \
    (160, s) SIMD_IF(p(160, s), SIMD_FOR_160, SIMD_TUPLE_EAT_4)(o(160, s), p, o, m)
#define SIMD_FOR_160(s, p, o, m)            \
    SIMD_IF(p(161, s), m, SIMD_TUPLE_EAT_2) \
    (161, s) SIMD_IF(p(161, s), SIMD_FOR_161, SIMD_TUPLE_EAT_4)(o(161, s), p, o, m)
#define SIMD_FOR_161(s, p, o, m)            \
    SIMD_IF(p(162, s), m, SIMD_TUPLE_EAT_2) \
    (162, s) SIMD_IF(p(162, s), SIMD_FOR_162, SIMD_TUPLE_EAT_4)(o(162, s), p, o, m)
#define SIMD_FOR_162(s, p, o, m)            \
    SIMD_IF(p(163, s), m, SIMD_TUPLE_EAT_2) \
    (163, s) SIMD_IF(p(163, s), SIMD_FOR_163, SIMD_TUPLE_EAT_4)(o(163, s), p, o, m)
#define SIMD_FOR_163(s, p, o, m)            \
    SIMD_IF(p(164, s), m, SIMD_TUPLE_EAT_2) \
    (164, s) SIMD_IF(p(164, s), SIMD_FOR_164, SIMD_TUPLE_EAT_4)(o(164, s), p, o, m)
#define SIMD_FOR_164(s, p, o, m)            \
    SIMD_IF(p(165, s), m, SIMD_TUPLE_EAT_2) \
    (165, s) SIMD_IF(p(165, s), SIMD_FOR_165, SIMD_TUPLE_EAT_4)(o(165, s), p, o, m)
#define SIMD_FOR_165(s, p, o, m)            \
    SIMD_IF(p(166, s), m, SIMD_TUPLE_EAT_2) \
    (166, s) SIMD_IF(p(166, s), SIMD_FOR_166, SIMD_TUPLE_EAT_4)(o(166, s), p, o, m)
#define SIMD_FOR_166(s, p, o, m)            \
    SIMD_IF(p(167, s), m, SIMD_TUPLE_EAT_2) \
    (167, s) SIMD_IF(p(167, s), SIMD_FOR_167, SIMD_TUPLE_EAT_4)(o(167, s), p, o, m)
#define SIMD_FOR_167(s, p, o, m)            \
    SIMD_IF(p(168, s), m, SIMD_TUPLE_EAT_2) \
    (168, s) SIMD_IF(p(168, s), SIMD_FOR_168, SIMD_TUPLE_EAT_4)(o(168, s), p, o, m)
#define SIMD_FOR_168(s, p, o, m)            \
    SIMD_IF(p(169, s), m, SIMD_TUPLE_EAT_2) \
    (169, s) SIMD_IF(p(169, s), SIMD_FOR_169, SIMD_TUPLE_EAT_4)(o(169, s), p, o, m)
#define SIMD_FOR_169(s, p, o, m)            \
    SIMD_IF(p(170, s), m, SIMD_TUPLE_EAT_2) \
    (170, s) SIMD_IF(p(170, s), SIMD_FOR_170, SIMD_TUPLE_EAT_4)(o(170, s), p, o, m)
#define SIMD_FOR_170(s, p, o, m)            \
    SIMD_IF(p(171, s), m, SIMD_TUPLE_EAT_2) \
    (171, s) SIMD_IF(p(171, s), SIMD_FOR_171, SIMD_TUPLE_EAT_4)(o(171, s), p, o, m)
#define SIMD_FOR_171(s, p, o, m)            \
    SIMD_IF(p(172, s), m, SIMD_TUPLE_EAT_2) \
    (172, s) SIMD_IF(p(172, s), SIMD_FOR_172, SIMD_TUPLE_EAT_4)(o(172, s), p, o, m)
#define SIMD_FOR_172(s, p, o, m)            \
    SIMD_IF(p(173, s), m, SIMD_TUPLE_EAT_2) \
    (173, s) SIMD_IF(p(173, s), SIMD_FOR_173, SIMD_TUPLE_EAT_4)(o(173, s), p, o, m)
#define SIMD_FOR_173(s, p, o, m)            \
    SIMD_IF(p(174, s), m, SIMD_TUPLE_EAT_2) \
    (174, s) SIMD_IF(p(174, s), SIMD_FOR_174, SIMD_TUPLE_EAT_4)(o(174, s), p, o, m)
#define SIMD_FOR_174(s, p, o, m)            \
    SIMD_IF(p(175, s), m, SIMD_TUPLE_EAT_2) \
    (175, s) SIMD_IF(p(175, s), SIMD_FOR_175, SIMD_TUPLE_EAT_4)(o(175, s), p, o, m)
#define SIMD_FOR_175(s, p, o, m)            \
    SIMD_IF(p(176, s), m, SIMD_TUPLE_EAT_2) \
    (176, s) SIMD_IF(p(176, s), SIMD_FOR_176, SIMD_TUPLE_EAT_4)(o(176, s), p, o, m)
#define SIMD_FOR_176(s, p, o, m)            \
    SIMD_IF(p(177, s), m, SIMD_TUPLE_EAT_2) \
    (177, s) SIMD_IF(p(177, s), SIMD_FOR_177, SIMD_TUPLE_EAT_4)(o(177, s), p, o, m)
#define SIMD_FOR_177(s, p, o, m)            \
    SIMD_IF(p(178, s), m, SIMD_TUPLE_EAT_2) \
    (178, s) SIMD_IF(p(178, s), SIMD_FOR_178, SIMD_TUPLE_EAT_4)(o(178, s), p, o, m)
#define SIMD_FOR_178(s, p, o, m)            \
    SIMD_IF(p(179, s), m, SIMD_TUPLE_EAT_2) \
    (179, s) SIMD_IF(p(179, s), SIMD_FOR_179, SIMD_TUPLE_EAT_4)(o(179, s), p, o, m)
#define SIMD_FOR_179(s, p, o, m)            \
    SIMD_IF(p(180, s), m, SIMD_TUPLE_EAT_2) \
    (180, s) SIMD_IF(p(180, s), SIMD_FOR_180, SIMD_TUPLE_EAT_4)(o(180, s), p, o, m)
#define SIMD_FOR_180(s, p, o, m)            \
    SIMD_IF(p(181, s), m, SIMD_TUPLE_EAT_2) \
    (181, s) SIMD_IF(p(181, s), SIMD_FOR_181, SIMD_TUPLE_EAT_4)(o(181, s), p, o, m)
#define SIMD_FOR_181(s, p, o, m)            \
    SIMD_IF(p(182, s), m, SIMD_TUPLE_EAT_2) \
    (182, s) SIMD_IF(p(182, s), SIMD_FOR_182, SIMD_TUPLE_EAT_4)(o(182, s), p, o, m)
#define SIMD_FOR_182(s, p, o, m)            \
    SIMD_IF(p(183, s), m, SIMD_TUPLE_EAT_2) \
    (183, s) SIMD_IF(p(183, s), SIMD_FOR_183, SIMD_TUPLE_EAT_4)(o(183, s), p, o, m)
#define SIMD_FOR_183(s, p, o, m)            \
    SIMD_IF(p(184, s), m, SIMD_TUPLE_EAT_2) \
    (184, s) SIMD_IF(p(184, s), SIMD_FOR_184, SIMD_TUPLE_EAT_4)(o(184, s), p, o, m)
#define SIMD_FOR_184(s, p, o, m)            \
    SIMD_IF(p(185, s), m, SIMD_TUPLE_EAT_2) \
    (185, s) SIMD_IF(p(185, s), SIMD_FOR_185, SIMD_TUPLE_EAT_4)(o(185, s), p, o, m)
#define SIMD_FOR_185(s, p, o, m)            \
    SIMD_IF(p(186, s), m, SIMD_TUPLE_EAT_2) \
    (186, s) SIMD_IF(p(186, s), SIMD_FOR_186, SIMD_TUPLE_EAT_4)(o(186, s), p, o, m)
#define SIMD_FOR_186(s, p, o, m)            \
    SIMD_IF(p(187, s), m, SIMD_TUPLE_EAT_2) \
    (187, s) SIMD_IF(p(187, s), SIMD_FOR_187, SIMD_TUPLE_EAT_4)(o(187, s), p, o, m)
#define SIMD_FOR_187(s, p, o, m)            \
    SIMD_IF(p(188, s), m, SIMD_TUPLE_EAT_2) \
    (188, s) SIMD_IF(p(188, s), SIMD_FOR_188, SIMD_TUPLE_EAT_4)(o(188, s), p, o, m)
#define SIMD_FOR_188(s, p, o, m)            \
    SIMD_IF(p(189, s), m, SIMD_TUPLE_EAT_2) \
    (189, s) SIMD_IF(p(189, s), SIMD_FOR_189, SIMD_TUPLE_EAT_4)(o(189, s), p, o, m)
#define SIMD_FOR_189(s, p, o, m)            \
    SIMD_IF(p(190, s), m, SIMD_TUPLE_EAT_2) \
    (190, s) SIMD_IF(p(190, s), SIMD_FOR_190, SIMD_TUPLE_EAT_4)(o(190, s), p, o, m)
#define SIMD_FOR_190(s, p, o, m)            \
    SIMD_IF(p(191, s), m, SIMD_TUPLE_EAT_2) \
    (191, s) SIMD_IF(p(191, s), SIMD_FOR_191, SIMD_TUPLE_EAT_4)(o(191, s), p, o, m)
#define SIMD_FOR_191(s, p, o, m)            \
    SIMD_IF(p(192, s), m, SIMD_TUPLE_EAT_2) \
    (192, s) SIMD_IF(p(192, s), SIMD_FOR_192, SIMD_TUPLE_EAT_4)(o(192, s), p, o, m)
#define SIMD_FOR_192(s, p, o, m)            \
    SIMD_IF(p(193, s), m, SIMD_TUPLE_EAT_2) \
    (193, s) SIMD_IF(p(193, s), SIMD_FOR_193, SIMD_TUPLE_EAT_4)(o(193, s), p, o, m)
#define SIMD_FOR_193(s, p, o, m)            \
    SIMD_IF(p(194, s), m, SIMD_TUPLE_EAT_2) \
    (194, s) SIMD_IF(p(194, s), SIMD_FOR_194, SIMD_TUPLE_EAT_4)(o(194, s), p, o, m)
#define SIMD_FOR_194(s, p, o, m)            \
    SIMD_IF(p(195, s), m, SIMD_TUPLE_EAT_2) \
    (195, s) SIMD_IF(p(195, s), SIMD_FOR_195, SIMD_TUPLE_EAT_4)(o(195, s), p, o, m)
#define SIMD_FOR_195(s, p, o, m)            \
    SIMD_IF(p(196, s), m, SIMD_TUPLE_EAT_2) \
    (196, s) SIMD_IF(p(196, s), SIMD_FOR_196, SIMD_TUPLE_EAT_4)(o(196, s), p, o, m)
#define SIMD_FOR_196(s, p, o, m)            \
    SIMD_IF(p(197, s), m, SIMD_TUPLE_EAT_2) \
    (197, s) SIMD_IF(p(197, s), SIMD_FOR_197, SIMD_TUPLE_EAT_4)(o(197, s), p, o, m)
#define SIMD_FOR_197(s, p, o, m)            \
    SIMD_IF(p(198, s), m, SIMD_TUPLE_EAT_2) \
    (198, s) SIMD_IF(p(198, s), SIMD_FOR_198, SIMD_TUPLE_EAT_4)(o(198, s), p, o, m)
#define SIMD_FOR_198(s, p, o, m)            \
    SIMD_IF(p(199, s), m, SIMD_TUPLE_EAT_2) \
    (199, s) SIMD_IF(p(199, s), SIMD_FOR_199, SIMD_TUPLE_EAT_4)(o(199, s), p, o, m)
#define SIMD_FOR_199(s, p, o, m)            \
    SIMD_IF(p(200, s), m, SIMD_TUPLE_EAT_2) \
    (200, s) SIMD_IF(p(200, s), SIMD_FOR_200, SIMD_TUPLE_EAT_4)(o(200, s), p, o, m)
#define SIMD_FOR_200(s, p, o, m)            \
    SIMD_IF(p(201, s), m, SIMD_TUPLE_EAT_2) \
    (201, s) SIMD_IF(p(201, s), SIMD_FOR_201, SIMD_TUPLE_EAT_4)(o(201, s), p, o, m)
#define SIMD_FOR_201(s, p, o, m)            \
    SIMD_IF(p(202, s), m, SIMD_TUPLE_EAT_2) \
    (202, s) SIMD_IF(p(202, s), SIMD_FOR_202, SIMD_TUPLE_EAT_4)(o(202, s), p, o, m)
#define SIMD_FOR_202(s, p, o, m)            \
    SIMD_IF(p(203, s), m, SIMD_TUPLE_EAT_2) \
    (203, s) SIMD_IF(p(203, s), SIMD_FOR_203, SIMD_TUPLE_EAT_4)(o(203, s), p, o, m)
#define SIMD_FOR_203(s, p, o, m)            \
    SIMD_IF(p(204, s), m, SIMD_TUPLE_EAT_2) \
    (204, s) SIMD_IF(p(204, s), SIMD_FOR_204, SIMD_TUPLE_EAT_4)(o(204, s), p, o, m)
#define SIMD_FOR_204(s, p, o, m)            \
    SIMD_IF(p(205, s), m, SIMD_TUPLE_EAT_2) \
    (205, s) SIMD_IF(p(205, s), SIMD_FOR_205, SIMD_TUPLE_EAT_4)(o(205, s), p, o, m)
#define SIMD_FOR_205(s, p, o, m)            \
    SIMD_IF(p(206, s), m, SIMD_TUPLE_EAT_2) \
    (206, s) SIMD_IF(p(206, s), SIMD_FOR_206, SIMD_TUPLE_EAT_4)(o(206, s), p, o, m)
#define SIMD_FOR_206(s, p, o, m)            \
    SIMD_IF(p(207, s), m, SIMD_TUPLE_EAT_2) \
    (207, s) SIMD_IF(p(207, s), SIMD_FOR_207, SIMD_TUPLE_EAT_4)(o(207, s), p, o, m)
#define SIMD_FOR_207(s, p, o, m)            \
    SIMD_IF(p(208, s), m, SIMD_TUPLE_EAT_2) \
    (208, s) SIMD_IF(p(208, s), SIMD_FOR_208, SIMD_TUPLE_EAT_4)(o(208, s), p, o, m)
#define SIMD_FOR_208(s, p, o, m)            \
    SIMD_IF(p(209, s), m, SIMD_TUPLE_EAT_2) \
    (209, s) SIMD_IF(p(209, s), SIMD_FOR_209, SIMD_TUPLE_EAT_4)(o(209, s), p, o, m)
#define SIMD_FOR_209(s, p, o, m)            \
    SIMD_IF(p(210, s), m, SIMD_TUPLE_EAT_2) \
    (210, s) SIMD_IF(p(210, s), SIMD_FOR_210, SIMD_TUPLE_EAT_4)(o(210, s), p, o, m)
#define SIMD_FOR_210(s, p, o, m)            \
    SIMD_IF(p(211, s), m, SIMD_TUPLE_EAT_2) \
    (211, s) SIMD_IF(p(211, s), SIMD_FOR_211, SIMD_TUPLE_EAT_4)(o(211, s), p, o, m)
#define SIMD_FOR_211(s, p, o, m)            \
    SIMD_IF(p(212, s), m, SIMD_TUPLE_EAT_2) \
    (212, s) SIMD_IF(p(212, s), SIMD_FOR_212, SIMD_TUPLE_EAT_4)(o(212, s), p, o, m)
#define SIMD_FOR_212(s, p, o, m)            \
    SIMD_IF(p(213, s), m, SIMD_TUPLE_EAT_2) \
    (213, s) SIMD_IF(p(213, s), SIMD_FOR_213, SIMD_TUPLE_EAT_4)(o(213, s), p, o, m)
#define SIMD_FOR_213(s, p, o, m)            \
    SIMD_IF(p(214, s), m, SIMD_TUPLE_EAT_2) \
    (214, s) SIMD_IF(p(214, s), SIMD_FOR_214, SIMD_TUPLE_EAT_4)(o(214, s), p, o, m)
#define SIMD_FOR_214(s, p, o, m)            \
    SIMD_IF(p(215, s), m, SIMD_TUPLE_EAT_2) \
    (215, s) SIMD_IF(p(215, s), SIMD_FOR_215, SIMD_TUPLE_EAT_4)(o(215, s), p, o, m)
#define SIMD_FOR_215(s, p, o, m)            \
    SIMD_IF(p(216, s), m, SIMD_TUPLE_EAT_2) \
    (216, s) SIMD_IF(p(216, s), SIMD_FOR_216, SIMD_TUPLE_EAT_4)(o(216, s), p, o, m)
#define SIMD_FOR_216(s, p, o, m)            \
    SIMD_IF(p(217, s), m, SIMD_TUPLE_EAT_2) \
    (217, s) SIMD_IF(p(217, s), SIMD_FOR_217, SIMD_TUPLE_EAT_4)(o(217, s), p, o, m)
#define SIMD_FOR_217(s, p, o, m)            \
    SIMD_IF(p(218, s), m, SIMD_TUPLE_EAT_2) \
    (218, s) SIMD_IF(p(218, s), SIMD_FOR_218, SIMD_TUPLE_EAT_4)(o(218, s), p, o, m)
#define SIMD_FOR_218(s, p, o, m)            \
    SIMD_IF(p(219, s), m, SIMD_TUPLE_EAT_2) \
    (219, s) SIMD_IF(p(219, s), SIMD_FOR_219, SIMD_TUPLE_EAT_4)(o(219, s), p, o, m)
#define SIMD_FOR_219(s, p, o, m)            \
    SIMD_IF(p(220, s), m, SIMD_TUPLE_EAT_2) \
    (220, s) SIMD_IF(p(220, s), SIMD_FOR_220, SIMD_TUPLE_EAT_4)(o(220, s), p, o, m)
#define SIMD_FOR_220(s, p, o, m)            \
    SIMD_IF(p(221, s), m, SIMD_TUPLE_EAT_2) \
    (221, s) SIMD_IF(p(221, s), SIMD_FOR_221, SIMD_TUPLE_EAT_4)(o(221, s), p, o, m)
#define SIMD_FOR_221(s, p, o, m)            \
    SIMD_IF(p(222, s), m, SIMD_TUPLE_EAT_2) \
    (222, s) SIMD_IF(p(222, s), SIMD_FOR_222, SIMD_TUPLE_EAT_4)(o(222, s), p, o, m)
#define SIMD_FOR_222(s, p, o, m)            \
    SIMD_IF(p(223, s), m, SIMD_TUPLE_EAT_2) \
    (223, s) SIMD_IF(p(223, s), SIMD_FOR_223, SIMD_TUPLE_EAT_4)(o(223, s), p, o, m)
#define SIMD_FOR_223(s, p, o, m)            \
    SIMD_IF(p(224, s), m, SIMD_TUPLE_EAT_2) \
    (224, s) SIMD_IF(p(224, s), SIMD_FOR_224, SIMD_TUPLE_EAT_4)(o(224, s), p, o, m)
#define SIMD_FOR_224(s, p, o, m)            \
    SIMD_IF(p(225, s), m, SIMD_TUPLE_EAT_2) \
    (225, s) SIMD_IF(p(225, s), SIMD_FOR_225, SIMD_TUPLE_EAT_4)(o(225, s), p, o, m)
#define SIMD_FOR_225(s, p, o, m)            \
    SIMD_IF(p(226, s), m, SIMD_TUPLE_EAT_2) \
    (226, s) SIMD_IF(p(226, s), SIMD_FOR_226, SIMD_TUPLE_EAT_4)(o(226, s), p, o, m)
#define SIMD_FOR_226(s, p, o, m)            \
    SIMD_IF(p(227, s), m, SIMD_TUPLE_EAT_2) \
    (227, s) SIMD_IF(p(227, s), SIMD_FOR_227, SIMD_TUPLE_EAT_4)(o(227, s), p, o, m)
#define SIMD_FOR_227(s, p, o, m)            \
    SIMD_IF(p(228, s), m, SIMD_TUPLE_EAT_2) \
    (228, s) SIMD_IF(p(228, s), SIMD_FOR_228, SIMD_TUPLE_EAT_4)(o(228, s), p, o, m)
#define SIMD_FOR_228(s, p, o, m)            \
    SIMD_IF(p(229, s), m, SIMD_TUPLE_EAT_2) \
    (229, s) SIMD_IF(p(229, s), SIMD_FOR_229, SIMD_TUPLE_EAT_4)(o(229, s), p, o, m)
#define SIMD_FOR_229(s, p, o, m)            \
    SIMD_IF(p(230, s), m, SIMD_TUPLE_EAT_2) \
    (230, s) SIMD_IF(p(230, s), SIMD_FOR_230, SIMD_TUPLE_EAT_4)(o(230, s), p, o, m)
#define SIMD_FOR_230(s, p, o, m)            \
    SIMD_IF(p(231, s), m, SIMD_TUPLE_EAT_2) \
    (231, s) SIMD_IF(p(231, s), SIMD_FOR_231, SIMD_TUPLE_EAT_4)(o(231, s), p, o, m)
#define SIMD_FOR_231(s, p, o, m)            \
    SIMD_IF(p(232, s), m, SIMD_TUPLE_EAT_2) \
    (232, s) SIMD_IF(p(232, s), SIMD_FOR_232, SIMD_TUPLE_EAT_4)(o(232, s), p, o, m)
#define SIMD_FOR_232(s, p, o, m)            \
    SIMD_IF(p(233, s), m, SIMD_TUPLE_EAT_2) \
    (233, s) SIMD_IF(p(233, s), SIMD_FOR_233, SIMD_TUPLE_EAT_4)(o(233, s), p, o, m)
#define SIMD_FOR_233(s, p, o, m)            \
    SIMD_IF(p(234, s), m, SIMD_TUPLE_EAT_2) \
    (234, s) SIMD_IF(p(234, s), SIMD_FOR_234, SIMD_TUPLE_EAT_4)(o(234, s), p, o, m)
#define SIMD_FOR_234(s, p, o, m)            \
    SIMD_IF(p(235, s), m, SIMD_TUPLE_EAT_2) \
    (235, s) SIMD_IF(p(235, s), SIMD_FOR_235, SIMD_TUPLE_EAT_4)(o(235, s), p, o, m)
#define SIMD_FOR_235(s, p, o, m)            \
    SIMD_IF(p(236, s), m, SIMD_TUPLE_EAT_2) \
    (236, s) SIMD_IF(p(236, s), SIMD_FOR_236, SIMD_TUPLE_EAT_4)(o(236, s), p, o, m)
#define SIMD_FOR_236(s, p, o, m)            \
    SIMD_IF(p(237, s), m, SIMD_TUPLE_EAT_2) \
    (237, s) SIMD_IF(p(237, s), SIMD_FOR_237, SIMD_TUPLE_EAT_4)(o(237, s), p, o, m)
#define SIMD_FOR_237(s, p, o, m)            \
    SIMD_IF(p(238, s), m, SIMD_TUPLE_EAT_2) \
    (238, s) SIMD_IF(p(238, s), SIMD_FOR_238, SIMD_TUPLE_EAT_4)(o(238, s), p, o, m)
#define SIMD_FOR_238(s, p, o, m)            \
    SIMD_IF(p(239, s), m, SIMD_TUPLE_EAT_2) \
    (239, s) SIMD_IF(p(239, s), SIMD_FOR_239, SIMD_TUPLE_EAT_4)(o(239, s), p, o, m)
#define SIMD_FOR_239(s, p, o, m)            \
    SIMD_IF(p(240, s), m, SIMD_TUPLE_EAT_2) \
    (240, s) SIMD_IF(p(240, s), SIMD_FOR_240, SIMD_TUPLE_EAT_4)(o(240, s), p, o, m)
#define SIMD_FOR_240(s, p, o, m)            \
    SIMD_IF(p(241, s), m, SIMD_TUPLE_EAT_2) \
    (241, s) SIMD_IF(p(241, s), SIMD_FOR_241, SIMD_TUPLE_EAT_4)(o(241, s), p, o, m)
#define SIMD_FOR_241(s, p, o, m)            \
    SIMD_IF(p(242, s), m, SIMD_TUPLE_EAT_2) \
    (242, s) SIMD_IF(p(242, s), SIMD_FOR_242, SIMD_TUPLE_EAT_4)(o(242, s), p, o, m)
#define SIMD_FOR_242(s, p, o, m)            \
    SIMD_IF(p(243, s), m, SIMD_TUPLE_EAT_2) \
    (243, s) SIMD_IF(p(243, s), SIMD_FOR_243, SIMD_TUPLE_EAT_4)(o(243, s), p, o, m)
#define SIMD_FOR_243(s, p, o, m)            \
    SIMD_IF(p(244, s), m, SIMD_TUPLE_EAT_2) \
    (244, s) SIMD_IF(p(244, s), SIMD_FOR_244, SIMD_TUPLE_EAT_4)(o(244, s), p, o, m)
#define SIMD_FOR_244(s, p, o, m)            \
    SIMD_IF(p(245, s), m, SIMD_TUPLE_EAT_2) \
    (245, s) SIMD_IF(p(245, s), SIMD_FOR_245, SIMD_TUPLE_EAT_4)(o(245, s), p, o, m)
#define SIMD_FOR_245(s, p, o, m)            \
    SIMD_IF(p(246, s), m, SIMD_TUPLE_EAT_2) \
    (246, s) SIMD_IF(p(246, s), SIMD_FOR_246, SIMD_TUPLE_EAT_4)(o(246, s), p, o, m)
#define SIMD_FOR_246(s, p, o, m)            \
    SIMD_IF(p(247, s), m, SIMD_TUPLE_EAT_2) \
    (247, s) SIMD_IF(p(247, s), SIMD_FOR_247, SIMD_TUPLE_EAT_4)(o(247, s), p, o, m)
#define SIMD_FOR_247(s, p, o, m)            \
    SIMD_IF(p(248, s), m, SIMD_TUPLE_EAT_2) \
    (248, s) SIMD_IF(p(248, s), SIMD_FOR_248, SIMD_TUPLE_EAT_4)(o(248, s), p, o, m)
#define SIMD_FOR_248(s, p, o, m)            \
    SIMD_IF(p(249, s), m, SIMD_TUPLE_EAT_2) \
    (249, s) SIMD_IF(p(249, s), SIMD_FOR_249, SIMD_TUPLE_EAT_4)(o(249, s), p, o, m)
#define SIMD_FOR_249(s, p, o, m)            \
    SIMD_IF(p(250, s), m, SIMD_TUPLE_EAT_2) \
    (250, s) SIMD_IF(p(250, s), SIMD_FOR_250, SIMD_TUPLE_EAT_4)(o(250, s), p, o, m)
#define SIMD_FOR_250(s, p, o, m)            \
    SIMD_IF(p(251, s), m, SIMD_TUPLE_EAT_2) \
    (251, s) SIMD_IF(p(251, s), SIMD_FOR_251, SIMD_TUPLE_EAT_4)(o(251, s), p, o, m)
#define SIMD_FOR_251(s, p, o, m)            \
    SIMD_IF(p(252, s), m, SIMD_TUPLE_EAT_2) \
    (252, s) SIMD_IF(p(252, s), SIMD_FOR_252, SIMD_TUPLE_EAT_4)(o(252, s), p, o, m)
#define SIMD_FOR_252(s, p, o, m)            \
    SIMD_IF(p(253, s), m, SIMD_TUPLE_EAT_2) \
    (253, s) SIMD_IF(p(253, s), SIMD_FOR_253, SIMD_TUPLE_EAT_4)(o(253, s), p, o, m)
#define SIMD_FOR_253(s, p, o, m)            \
    SIMD_IF(p(254, s), m, SIMD_TUPLE_EAT_2) \
    (254, s) SIMD_IF(p(254, s), SIMD_FOR_254, SIMD_TUPLE_EAT_4)(o(254, s), p, o, m)
#define SIMD_FOR_254(s, p, o, m)            \
    SIMD_IF(p(255, s), m, SIMD_TUPLE_EAT_2) \
    (255, s) SIMD_IF(p(255, s), SIMD_FOR_255, SIMD_TUPLE_EAT_4)(o(255, s), p, o, m)
#define SIMD_FOR_255(s, p, o, m)            \
    SIMD_IF(p(256, s), m, SIMD_TUPLE_EAT_2) \
    (256, s) SIMD_IF(p(256, s), SIMD_FOR_256, SIMD_TUPLE_EAT_4)(o(256, s), p, o, m)
#define SIMD_FOR_256(s, p, o, m)            \
    SIMD_IF(p(257, s), m, SIMD_TUPLE_EAT_2) \
    (257, s) SIMD_IF(p(257, s), SIMD_FOR_257, SIMD_TUPLE_EAT_4)(o(257, s), p, o, m)
#
#endif
