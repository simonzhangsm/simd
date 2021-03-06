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
#include <bigmath/simd/detail/preprocessor/config/config.hpp>
#
#ifndef SIMD_PREPROCESSOR_DETAIL_AUTO_REC_HPP
#define SIMD_PREPROCESSOR_DETAIL_AUTO_REC_HPP
#
#include <bigmath/simd/detail/preprocessor/control/iif.hpp>
#
#/* SIMD_AUTO_REC */
#
#define SIMD_AUTO_REC(pred, n) SIMD_NODE_ENTRY_##n(pred)
#
#define SIMD_NODE_ENTRY_256(p) SIMD_NODE_128(p)(p)(p)(p)(p)(p)(p)(p)
#define SIMD_NODE_ENTRY_128(p) SIMD_NODE_64(p)(p)(p)(p)(p)(p)(p)
#define SIMD_NODE_ENTRY_64(p) SIMD_NODE_32(p)(p)(p)(p)(p)(p)
#define SIMD_NODE_ENTRY_32(p) SIMD_NODE_16(p)(p)(p)(p)(p)
#define SIMD_NODE_ENTRY_16(p) SIMD_NODE_8(p)(p)(p)(p)
#define SIMD_NODE_ENTRY_8(p) SIMD_NODE_4(p)(p)(p)
#define SIMD_NODE_ENTRY_4(p) SIMD_NODE_2(p)(p)
#define SIMD_NODE_ENTRY_2(p) SIMD_NODE_1(p)
#
#define SIMD_NODE_128(p) SIMD_IIF(p(128), SIMD_NODE_64, SIMD_NODE_192)
#define SIMD_NODE_64(p) SIMD_IIF(p(64), SIMD_NODE_32, SIMD_NODE_96)
#define SIMD_NODE_32(p) SIMD_IIF(p(32), SIMD_NODE_16, SIMD_NODE_48)
#define SIMD_NODE_16(p) SIMD_IIF(p(16), SIMD_NODE_8, SIMD_NODE_24)
#define SIMD_NODE_8(p) SIMD_IIF(p(8), SIMD_NODE_4, SIMD_NODE_12)
#define SIMD_NODE_4(p) SIMD_IIF(p(4), SIMD_NODE_2, SIMD_NODE_6)
#define SIMD_NODE_2(p) SIMD_IIF(p(2), SIMD_NODE_1, SIMD_NODE_3)
#define SIMD_NODE_1(p) SIMD_IIF(p(1), 1, 2)
#define SIMD_NODE_3(p) SIMD_IIF(p(3), 3, 4)
#define SIMD_NODE_6(p) SIMD_IIF(p(6), SIMD_NODE_5, SIMD_NODE_7)
#define SIMD_NODE_5(p) SIMD_IIF(p(5), 5, 6)
#define SIMD_NODE_7(p) SIMD_IIF(p(7), 7, 8)
#define SIMD_NODE_12(p) SIMD_IIF(p(12), SIMD_NODE_10, SIMD_NODE_14)
#define SIMD_NODE_10(p) SIMD_IIF(p(10), SIMD_NODE_9, SIMD_NODE_11)
#define SIMD_NODE_9(p) SIMD_IIF(p(9), 9, 10)
#define SIMD_NODE_11(p) SIMD_IIF(p(11), 11, 12)
#define SIMD_NODE_14(p) SIMD_IIF(p(14), SIMD_NODE_13, SIMD_NODE_15)
#define SIMD_NODE_13(p) SIMD_IIF(p(13), 13, 14)
#define SIMD_NODE_15(p) SIMD_IIF(p(15), 15, 16)
#define SIMD_NODE_24(p) SIMD_IIF(p(24), SIMD_NODE_20, SIMD_NODE_28)
#define SIMD_NODE_20(p) SIMD_IIF(p(20), SIMD_NODE_18, SIMD_NODE_22)
#define SIMD_NODE_18(p) SIMD_IIF(p(18), SIMD_NODE_17, SIMD_NODE_19)
#define SIMD_NODE_17(p) SIMD_IIF(p(17), 17, 18)
#define SIMD_NODE_19(p) SIMD_IIF(p(19), 19, 20)
#define SIMD_NODE_22(p) SIMD_IIF(p(22), SIMD_NODE_21, SIMD_NODE_23)
#define SIMD_NODE_21(p) SIMD_IIF(p(21), 21, 22)
#define SIMD_NODE_23(p) SIMD_IIF(p(23), 23, 24)
#define SIMD_NODE_28(p) SIMD_IIF(p(28), SIMD_NODE_26, SIMD_NODE_30)
#define SIMD_NODE_26(p) SIMD_IIF(p(26), SIMD_NODE_25, SIMD_NODE_27)
#define SIMD_NODE_25(p) SIMD_IIF(p(25), 25, 26)
#define SIMD_NODE_27(p) SIMD_IIF(p(27), 27, 28)
#define SIMD_NODE_30(p) SIMD_IIF(p(30), SIMD_NODE_29, SIMD_NODE_31)
#define SIMD_NODE_29(p) SIMD_IIF(p(29), 29, 30)
#define SIMD_NODE_31(p) SIMD_IIF(p(31), 31, 32)
#define SIMD_NODE_48(p) SIMD_IIF(p(48), SIMD_NODE_40, SIMD_NODE_56)
#define SIMD_NODE_40(p) SIMD_IIF(p(40), SIMD_NODE_36, SIMD_NODE_44)
#define SIMD_NODE_36(p) SIMD_IIF(p(36), SIMD_NODE_34, SIMD_NODE_38)
#define SIMD_NODE_34(p) SIMD_IIF(p(34), SIMD_NODE_33, SIMD_NODE_35)
#define SIMD_NODE_33(p) SIMD_IIF(p(33), 33, 34)
#define SIMD_NODE_35(p) SIMD_IIF(p(35), 35, 36)
#define SIMD_NODE_38(p) SIMD_IIF(p(38), SIMD_NODE_37, SIMD_NODE_39)
#define SIMD_NODE_37(p) SIMD_IIF(p(37), 37, 38)
#define SIMD_NODE_39(p) SIMD_IIF(p(39), 39, 40)
#define SIMD_NODE_44(p) SIMD_IIF(p(44), SIMD_NODE_42, SIMD_NODE_46)
#define SIMD_NODE_42(p) SIMD_IIF(p(42), SIMD_NODE_41, SIMD_NODE_43)
#define SIMD_NODE_41(p) SIMD_IIF(p(41), 41, 42)
#define SIMD_NODE_43(p) SIMD_IIF(p(43), 43, 44)
#define SIMD_NODE_46(p) SIMD_IIF(p(46), SIMD_NODE_45, SIMD_NODE_47)
#define SIMD_NODE_45(p) SIMD_IIF(p(45), 45, 46)
#define SIMD_NODE_47(p) SIMD_IIF(p(47), 47, 48)
#define SIMD_NODE_56(p) SIMD_IIF(p(56), SIMD_NODE_52, SIMD_NODE_60)
#define SIMD_NODE_52(p) SIMD_IIF(p(52), SIMD_NODE_50, SIMD_NODE_54)
#define SIMD_NODE_50(p) SIMD_IIF(p(50), SIMD_NODE_49, SIMD_NODE_51)
#define SIMD_NODE_49(p) SIMD_IIF(p(49), 49, 50)
#define SIMD_NODE_51(p) SIMD_IIF(p(51), 51, 52)
#define SIMD_NODE_54(p) SIMD_IIF(p(54), SIMD_NODE_53, SIMD_NODE_55)
#define SIMD_NODE_53(p) SIMD_IIF(p(53), 53, 54)
#define SIMD_NODE_55(p) SIMD_IIF(p(55), 55, 56)
#define SIMD_NODE_60(p) SIMD_IIF(p(60), SIMD_NODE_58, SIMD_NODE_62)
#define SIMD_NODE_58(p) SIMD_IIF(p(58), SIMD_NODE_57, SIMD_NODE_59)
#define SIMD_NODE_57(p) SIMD_IIF(p(57), 57, 58)
#define SIMD_NODE_59(p) SIMD_IIF(p(59), 59, 60)
#define SIMD_NODE_62(p) SIMD_IIF(p(62), SIMD_NODE_61, SIMD_NODE_63)
#define SIMD_NODE_61(p) SIMD_IIF(p(61), 61, 62)
#define SIMD_NODE_63(p) SIMD_IIF(p(63), 63, 64)
#define SIMD_NODE_96(p) SIMD_IIF(p(96), SIMD_NODE_80, SIMD_NODE_112)
#define SIMD_NODE_80(p) SIMD_IIF(p(80), SIMD_NODE_72, SIMD_NODE_88)
#define SIMD_NODE_72(p) SIMD_IIF(p(72), SIMD_NODE_68, SIMD_NODE_76)
#define SIMD_NODE_68(p) SIMD_IIF(p(68), SIMD_NODE_66, SIMD_NODE_70)
#define SIMD_NODE_66(p) SIMD_IIF(p(66), SIMD_NODE_65, SIMD_NODE_67)
#define SIMD_NODE_65(p) SIMD_IIF(p(65), 65, 66)
#define SIMD_NODE_67(p) SIMD_IIF(p(67), 67, 68)
#define SIMD_NODE_70(p) SIMD_IIF(p(70), SIMD_NODE_69, SIMD_NODE_71)
#define SIMD_NODE_69(p) SIMD_IIF(p(69), 69, 70)
#define SIMD_NODE_71(p) SIMD_IIF(p(71), 71, 72)
#define SIMD_NODE_76(p) SIMD_IIF(p(76), SIMD_NODE_74, SIMD_NODE_78)
#define SIMD_NODE_74(p) SIMD_IIF(p(74), SIMD_NODE_73, SIMD_NODE_75)
#define SIMD_NODE_73(p) SIMD_IIF(p(73), 73, 74)
#define SIMD_NODE_75(p) SIMD_IIF(p(75), 75, 76)
#define SIMD_NODE_78(p) SIMD_IIF(p(78), SIMD_NODE_77, SIMD_NODE_79)
#define SIMD_NODE_77(p) SIMD_IIF(p(77), 77, 78)
#define SIMD_NODE_79(p) SIMD_IIF(p(79), 79, 80)
#define SIMD_NODE_88(p) SIMD_IIF(p(88), SIMD_NODE_84, SIMD_NODE_92)
#define SIMD_NODE_84(p) SIMD_IIF(p(84), SIMD_NODE_82, SIMD_NODE_86)
#define SIMD_NODE_82(p) SIMD_IIF(p(82), SIMD_NODE_81, SIMD_NODE_83)
#define SIMD_NODE_81(p) SIMD_IIF(p(81), 81, 82)
#define SIMD_NODE_83(p) SIMD_IIF(p(83), 83, 84)
#define SIMD_NODE_86(p) SIMD_IIF(p(86), SIMD_NODE_85, SIMD_NODE_87)
#define SIMD_NODE_85(p) SIMD_IIF(p(85), 85, 86)
#define SIMD_NODE_87(p) SIMD_IIF(p(87), 87, 88)
#define SIMD_NODE_92(p) SIMD_IIF(p(92), SIMD_NODE_90, SIMD_NODE_94)
#define SIMD_NODE_90(p) SIMD_IIF(p(90), SIMD_NODE_89, SIMD_NODE_91)
#define SIMD_NODE_89(p) SIMD_IIF(p(89), 89, 90)
#define SIMD_NODE_91(p) SIMD_IIF(p(91), 91, 92)
#define SIMD_NODE_94(p) SIMD_IIF(p(94), SIMD_NODE_93, SIMD_NODE_95)
#define SIMD_NODE_93(p) SIMD_IIF(p(93), 93, 94)
#define SIMD_NODE_95(p) SIMD_IIF(p(95), 95, 96)
#define SIMD_NODE_112(p) SIMD_IIF(p(112), SIMD_NODE_104, SIMD_NODE_120)
#define SIMD_NODE_104(p) SIMD_IIF(p(104), SIMD_NODE_100, SIMD_NODE_108)
#define SIMD_NODE_100(p) SIMD_IIF(p(100), SIMD_NODE_98, SIMD_NODE_102)
#define SIMD_NODE_98(p) SIMD_IIF(p(98), SIMD_NODE_97, SIMD_NODE_99)
#define SIMD_NODE_97(p) SIMD_IIF(p(97), 97, 98)
#define SIMD_NODE_99(p) SIMD_IIF(p(99), 99, 100)
#define SIMD_NODE_102(p) SIMD_IIF(p(102), SIMD_NODE_101, SIMD_NODE_103)
#define SIMD_NODE_101(p) SIMD_IIF(p(101), 101, 102)
#define SIMD_NODE_103(p) SIMD_IIF(p(103), 103, 104)
#define SIMD_NODE_108(p) SIMD_IIF(p(108), SIMD_NODE_106, SIMD_NODE_110)
#define SIMD_NODE_106(p) SIMD_IIF(p(106), SIMD_NODE_105, SIMD_NODE_107)
#define SIMD_NODE_105(p) SIMD_IIF(p(105), 105, 106)
#define SIMD_NODE_107(p) SIMD_IIF(p(107), 107, 108)
#define SIMD_NODE_110(p) SIMD_IIF(p(110), SIMD_NODE_109, SIMD_NODE_111)
#define SIMD_NODE_109(p) SIMD_IIF(p(109), 109, 110)
#define SIMD_NODE_111(p) SIMD_IIF(p(111), 111, 112)
#define SIMD_NODE_120(p) SIMD_IIF(p(120), SIMD_NODE_116, SIMD_NODE_124)
#define SIMD_NODE_116(p) SIMD_IIF(p(116), SIMD_NODE_114, SIMD_NODE_118)
#define SIMD_NODE_114(p) SIMD_IIF(p(114), SIMD_NODE_113, SIMD_NODE_115)
#define SIMD_NODE_113(p) SIMD_IIF(p(113), 113, 114)
#define SIMD_NODE_115(p) SIMD_IIF(p(115), 115, 116)
#define SIMD_NODE_118(p) SIMD_IIF(p(118), SIMD_NODE_117, SIMD_NODE_119)
#define SIMD_NODE_117(p) SIMD_IIF(p(117), 117, 118)
#define SIMD_NODE_119(p) SIMD_IIF(p(119), 119, 120)
#define SIMD_NODE_124(p) SIMD_IIF(p(124), SIMD_NODE_122, SIMD_NODE_126)
#define SIMD_NODE_122(p) SIMD_IIF(p(122), SIMD_NODE_121, SIMD_NODE_123)
#define SIMD_NODE_121(p) SIMD_IIF(p(121), 121, 122)
#define SIMD_NODE_123(p) SIMD_IIF(p(123), 123, 124)
#define SIMD_NODE_126(p) SIMD_IIF(p(126), SIMD_NODE_125, SIMD_NODE_127)
#define SIMD_NODE_125(p) SIMD_IIF(p(125), 125, 126)
#define SIMD_NODE_127(p) SIMD_IIF(p(127), 127, 128)
#define SIMD_NODE_192(p) SIMD_IIF(p(192), SIMD_NODE_160, SIMD_NODE_224)
#define SIMD_NODE_160(p) SIMD_IIF(p(160), SIMD_NODE_144, SIMD_NODE_176)
#define SIMD_NODE_144(p) SIMD_IIF(p(144), SIMD_NODE_136, SIMD_NODE_152)
#define SIMD_NODE_136(p) SIMD_IIF(p(136), SIMD_NODE_132, SIMD_NODE_140)
#define SIMD_NODE_132(p) SIMD_IIF(p(132), SIMD_NODE_130, SIMD_NODE_134)
#define SIMD_NODE_130(p) SIMD_IIF(p(130), SIMD_NODE_129, SIMD_NODE_131)
#define SIMD_NODE_129(p) SIMD_IIF(p(129), 129, 130)
#define SIMD_NODE_131(p) SIMD_IIF(p(131), 131, 132)
#define SIMD_NODE_134(p) SIMD_IIF(p(134), SIMD_NODE_133, SIMD_NODE_135)
#define SIMD_NODE_133(p) SIMD_IIF(p(133), 133, 134)
#define SIMD_NODE_135(p) SIMD_IIF(p(135), 135, 136)
#define SIMD_NODE_140(p) SIMD_IIF(p(140), SIMD_NODE_138, SIMD_NODE_142)
#define SIMD_NODE_138(p) SIMD_IIF(p(138), SIMD_NODE_137, SIMD_NODE_139)
#define SIMD_NODE_137(p) SIMD_IIF(p(137), 137, 138)
#define SIMD_NODE_139(p) SIMD_IIF(p(139), 139, 140)
#define SIMD_NODE_142(p) SIMD_IIF(p(142), SIMD_NODE_141, SIMD_NODE_143)
#define SIMD_NODE_141(p) SIMD_IIF(p(141), 141, 142)
#define SIMD_NODE_143(p) SIMD_IIF(p(143), 143, 144)
#define SIMD_NODE_152(p) SIMD_IIF(p(152), SIMD_NODE_148, SIMD_NODE_156)
#define SIMD_NODE_148(p) SIMD_IIF(p(148), SIMD_NODE_146, SIMD_NODE_150)
#define SIMD_NODE_146(p) SIMD_IIF(p(146), SIMD_NODE_145, SIMD_NODE_147)
#define SIMD_NODE_145(p) SIMD_IIF(p(145), 145, 146)
#define SIMD_NODE_147(p) SIMD_IIF(p(147), 147, 148)
#define SIMD_NODE_150(p) SIMD_IIF(p(150), SIMD_NODE_149, SIMD_NODE_151)
#define SIMD_NODE_149(p) SIMD_IIF(p(149), 149, 150)
#define SIMD_NODE_151(p) SIMD_IIF(p(151), 151, 152)
#define SIMD_NODE_156(p) SIMD_IIF(p(156), SIMD_NODE_154, SIMD_NODE_158)
#define SIMD_NODE_154(p) SIMD_IIF(p(154), SIMD_NODE_153, SIMD_NODE_155)
#define SIMD_NODE_153(p) SIMD_IIF(p(153), 153, 154)
#define SIMD_NODE_155(p) SIMD_IIF(p(155), 155, 156)
#define SIMD_NODE_158(p) SIMD_IIF(p(158), SIMD_NODE_157, SIMD_NODE_159)
#define SIMD_NODE_157(p) SIMD_IIF(p(157), 157, 158)
#define SIMD_NODE_159(p) SIMD_IIF(p(159), 159, 160)
#define SIMD_NODE_176(p) SIMD_IIF(p(176), SIMD_NODE_168, SIMD_NODE_184)
#define SIMD_NODE_168(p) SIMD_IIF(p(168), SIMD_NODE_164, SIMD_NODE_172)
#define SIMD_NODE_164(p) SIMD_IIF(p(164), SIMD_NODE_162, SIMD_NODE_166)
#define SIMD_NODE_162(p) SIMD_IIF(p(162), SIMD_NODE_161, SIMD_NODE_163)
#define SIMD_NODE_161(p) SIMD_IIF(p(161), 161, 162)
#define SIMD_NODE_163(p) SIMD_IIF(p(163), 163, 164)
#define SIMD_NODE_166(p) SIMD_IIF(p(166), SIMD_NODE_165, SIMD_NODE_167)
#define SIMD_NODE_165(p) SIMD_IIF(p(165), 165, 166)
#define SIMD_NODE_167(p) SIMD_IIF(p(167), 167, 168)
#define SIMD_NODE_172(p) SIMD_IIF(p(172), SIMD_NODE_170, SIMD_NODE_174)
#define SIMD_NODE_170(p) SIMD_IIF(p(170), SIMD_NODE_169, SIMD_NODE_171)
#define SIMD_NODE_169(p) SIMD_IIF(p(169), 169, 170)
#define SIMD_NODE_171(p) SIMD_IIF(p(171), 171, 172)
#define SIMD_NODE_174(p) SIMD_IIF(p(174), SIMD_NODE_173, SIMD_NODE_175)
#define SIMD_NODE_173(p) SIMD_IIF(p(173), 173, 174)
#define SIMD_NODE_175(p) SIMD_IIF(p(175), 175, 176)
#define SIMD_NODE_184(p) SIMD_IIF(p(184), SIMD_NODE_180, SIMD_NODE_188)
#define SIMD_NODE_180(p) SIMD_IIF(p(180), SIMD_NODE_178, SIMD_NODE_182)
#define SIMD_NODE_178(p) SIMD_IIF(p(178), SIMD_NODE_177, SIMD_NODE_179)
#define SIMD_NODE_177(p) SIMD_IIF(p(177), 177, 178)
#define SIMD_NODE_179(p) SIMD_IIF(p(179), 179, 180)
#define SIMD_NODE_182(p) SIMD_IIF(p(182), SIMD_NODE_181, SIMD_NODE_183)
#define SIMD_NODE_181(p) SIMD_IIF(p(181), 181, 182)
#define SIMD_NODE_183(p) SIMD_IIF(p(183), 183, 184)
#define SIMD_NODE_188(p) SIMD_IIF(p(188), SIMD_NODE_186, SIMD_NODE_190)
#define SIMD_NODE_186(p) SIMD_IIF(p(186), SIMD_NODE_185, SIMD_NODE_187)
#define SIMD_NODE_185(p) SIMD_IIF(p(185), 185, 186)
#define SIMD_NODE_187(p) SIMD_IIF(p(187), 187, 188)
#define SIMD_NODE_190(p) SIMD_IIF(p(190), SIMD_NODE_189, SIMD_NODE_191)
#define SIMD_NODE_189(p) SIMD_IIF(p(189), 189, 190)
#define SIMD_NODE_191(p) SIMD_IIF(p(191), 191, 192)
#define SIMD_NODE_224(p) SIMD_IIF(p(224), SIMD_NODE_208, SIMD_NODE_240)
#define SIMD_NODE_208(p) SIMD_IIF(p(208), SIMD_NODE_200, SIMD_NODE_216)
#define SIMD_NODE_200(p) SIMD_IIF(p(200), SIMD_NODE_196, SIMD_NODE_204)
#define SIMD_NODE_196(p) SIMD_IIF(p(196), SIMD_NODE_194, SIMD_NODE_198)
#define SIMD_NODE_194(p) SIMD_IIF(p(194), SIMD_NODE_193, SIMD_NODE_195)
#define SIMD_NODE_193(p) SIMD_IIF(p(193), 193, 194)
#define SIMD_NODE_195(p) SIMD_IIF(p(195), 195, 196)
#define SIMD_NODE_198(p) SIMD_IIF(p(198), SIMD_NODE_197, SIMD_NODE_199)
#define SIMD_NODE_197(p) SIMD_IIF(p(197), 197, 198)
#define SIMD_NODE_199(p) SIMD_IIF(p(199), 199, 200)
#define SIMD_NODE_204(p) SIMD_IIF(p(204), SIMD_NODE_202, SIMD_NODE_206)
#define SIMD_NODE_202(p) SIMD_IIF(p(202), SIMD_NODE_201, SIMD_NODE_203)
#define SIMD_NODE_201(p) SIMD_IIF(p(201), 201, 202)
#define SIMD_NODE_203(p) SIMD_IIF(p(203), 203, 204)
#define SIMD_NODE_206(p) SIMD_IIF(p(206), SIMD_NODE_205, SIMD_NODE_207)
#define SIMD_NODE_205(p) SIMD_IIF(p(205), 205, 206)
#define SIMD_NODE_207(p) SIMD_IIF(p(207), 207, 208)
#define SIMD_NODE_216(p) SIMD_IIF(p(216), SIMD_NODE_212, SIMD_NODE_220)
#define SIMD_NODE_212(p) SIMD_IIF(p(212), SIMD_NODE_210, SIMD_NODE_214)
#define SIMD_NODE_210(p) SIMD_IIF(p(210), SIMD_NODE_209, SIMD_NODE_211)
#define SIMD_NODE_209(p) SIMD_IIF(p(209), 209, 210)
#define SIMD_NODE_211(p) SIMD_IIF(p(211), 211, 212)
#define SIMD_NODE_214(p) SIMD_IIF(p(214), SIMD_NODE_213, SIMD_NODE_215)
#define SIMD_NODE_213(p) SIMD_IIF(p(213), 213, 214)
#define SIMD_NODE_215(p) SIMD_IIF(p(215), 215, 216)
#define SIMD_NODE_220(p) SIMD_IIF(p(220), SIMD_NODE_218, SIMD_NODE_222)
#define SIMD_NODE_218(p) SIMD_IIF(p(218), SIMD_NODE_217, SIMD_NODE_219)
#define SIMD_NODE_217(p) SIMD_IIF(p(217), 217, 218)
#define SIMD_NODE_219(p) SIMD_IIF(p(219), 219, 220)
#define SIMD_NODE_222(p) SIMD_IIF(p(222), SIMD_NODE_221, SIMD_NODE_223)
#define SIMD_NODE_221(p) SIMD_IIF(p(221), 221, 222)
#define SIMD_NODE_223(p) SIMD_IIF(p(223), 223, 224)
#define SIMD_NODE_240(p) SIMD_IIF(p(240), SIMD_NODE_232, SIMD_NODE_248)
#define SIMD_NODE_232(p) SIMD_IIF(p(232), SIMD_NODE_228, SIMD_NODE_236)
#define SIMD_NODE_228(p) SIMD_IIF(p(228), SIMD_NODE_226, SIMD_NODE_230)
#define SIMD_NODE_226(p) SIMD_IIF(p(226), SIMD_NODE_225, SIMD_NODE_227)
#define SIMD_NODE_225(p) SIMD_IIF(p(225), 225, 226)
#define SIMD_NODE_227(p) SIMD_IIF(p(227), 227, 228)
#define SIMD_NODE_230(p) SIMD_IIF(p(230), SIMD_NODE_229, SIMD_NODE_231)
#define SIMD_NODE_229(p) SIMD_IIF(p(229), 229, 230)
#define SIMD_NODE_231(p) SIMD_IIF(p(231), 231, 232)
#define SIMD_NODE_236(p) SIMD_IIF(p(236), SIMD_NODE_234, SIMD_NODE_238)
#define SIMD_NODE_234(p) SIMD_IIF(p(234), SIMD_NODE_233, SIMD_NODE_235)
#define SIMD_NODE_233(p) SIMD_IIF(p(233), 233, 234)
#define SIMD_NODE_235(p) SIMD_IIF(p(235), 235, 236)
#define SIMD_NODE_238(p) SIMD_IIF(p(238), SIMD_NODE_237, SIMD_NODE_239)
#define SIMD_NODE_237(p) SIMD_IIF(p(237), 237, 238)
#define SIMD_NODE_239(p) SIMD_IIF(p(239), 239, 240)
#define SIMD_NODE_248(p) SIMD_IIF(p(248), SIMD_NODE_244, SIMD_NODE_252)
#define SIMD_NODE_244(p) SIMD_IIF(p(244), SIMD_NODE_242, SIMD_NODE_246)
#define SIMD_NODE_242(p) SIMD_IIF(p(242), SIMD_NODE_241, SIMD_NODE_243)
#define SIMD_NODE_241(p) SIMD_IIF(p(241), 241, 242)
#define SIMD_NODE_243(p) SIMD_IIF(p(243), 243, 244)
#define SIMD_NODE_246(p) SIMD_IIF(p(246), SIMD_NODE_245, SIMD_NODE_247)
#define SIMD_NODE_245(p) SIMD_IIF(p(245), 245, 246)
#define SIMD_NODE_247(p) SIMD_IIF(p(247), 247, 248)
#define SIMD_NODE_252(p) SIMD_IIF(p(252), SIMD_NODE_250, SIMD_NODE_254)
#define SIMD_NODE_250(p) SIMD_IIF(p(250), SIMD_NODE_249, SIMD_NODE_251)
#define SIMD_NODE_249(p) SIMD_IIF(p(249), 249, 250)
#define SIMD_NODE_251(p) SIMD_IIF(p(251), 251, 252)
#define SIMD_NODE_254(p) SIMD_IIF(p(254), SIMD_NODE_253, SIMD_NODE_255)
#define SIMD_NODE_253(p) SIMD_IIF(p(253), 253, 254)
#define SIMD_NODE_255(p) SIMD_IIF(p(255), 255, 256)
#
#endif
