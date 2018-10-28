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
#ifndef SIMD_PREPROCESSOR_REPETITION_FOR_HPP
#define SIMD_PREPROCESSOR_REPETITION_FOR_HPP
#
#include <bigmath/simd/detail/preprocessor/cat.hpp>
#include <bigmath/simd/detail/preprocessor/debug/error.hpp>
#include <bigmath/simd/detail/preprocessor/facilities/empty.hpp>
#include <bigmath/simd/detail/preprocessor/logical/bool.hpp>
#include <bigmath/simd/detail/preprocessor/detail/auto_rec.hpp>
#
#/* SIMD_FOR */
#
#if 0
#define SIMD_FOR(state, pred, op, macro)
#endif
#
#define SIMD_FOR SIMD_CAT(SIMD_FOR_, SIMD_AUTO_REC(SIMD_FOR_P, 256))
#
#define SIMD_FOR_P(n) SIMD_CAT(SIMD_FOR_CHECK_, SIMD_FOR_##n(1, SIMD_FOR_SR_P, SIMD_FOR_SR_O, SIMD_FOR_SR_M))
#
#define SIMD_FOR_SR_P(r, s) s
#define SIMD_FOR_SR_O(r, s) 0
#define SIMD_FOR_SR_M(r, s) SIMD_NIL
#
#if SIMD_CONFIG_FLAGS() & SIMD_CONFIG_MSVC()
#include <bigmath/simd/detail/preprocessor/repetition/detail/msvc/for.hpp>
#else
#include <bigmath/simd/detail/preprocessor/repetition/detail/for.hpp>
#endif
#
#if SIMD_CONFIG_FLAGS() & SIMD_CONFIG_DMC()
#define SIMD_FOR_257_PR(s, p) SIMD_BOOL(p##(257, s))
#else
#define SIMD_FOR_257_PR(s, p) SIMD_BOOL(p(257, s))
#endif

#define SIMD_FOR_257_ERROR() SIMD_ERROR(0x0002)
#define SIMD_FOR_257(s, p, o, m)                                    \
    SIMD_IIF(SIMD_FOR_257_PR(s, p), SIMD_FOR_257_ERROR, SIMD_EMPTY) \
    () /**/
// # define SIMD_FOR_257(s, p, o, m) SIMD_ERROR(0x0002)
#
#define SIMD_FOR_CHECK_SIMD_NIL 1
#
#define SIMD_FOR_CHECK_SIMD_FOR_1(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_2(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_3(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_4(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_5(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_6(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_7(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_8(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_9(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_10(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_11(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_12(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_13(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_14(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_15(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_16(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_17(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_18(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_19(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_20(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_21(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_22(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_23(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_24(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_25(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_26(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_27(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_28(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_29(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_30(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_31(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_32(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_33(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_34(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_35(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_36(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_37(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_38(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_39(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_40(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_41(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_42(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_43(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_44(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_45(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_46(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_47(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_48(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_49(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_50(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_51(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_52(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_53(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_54(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_55(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_56(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_57(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_58(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_59(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_60(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_61(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_62(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_63(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_64(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_65(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_66(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_67(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_68(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_69(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_70(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_71(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_72(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_73(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_74(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_75(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_76(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_77(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_78(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_79(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_80(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_81(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_82(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_83(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_84(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_85(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_86(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_87(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_88(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_89(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_90(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_91(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_92(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_93(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_94(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_95(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_96(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_97(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_98(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_99(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_100(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_101(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_102(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_103(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_104(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_105(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_106(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_107(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_108(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_109(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_110(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_111(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_112(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_113(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_114(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_115(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_116(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_117(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_118(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_119(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_120(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_121(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_122(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_123(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_124(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_125(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_126(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_127(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_128(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_129(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_130(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_131(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_132(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_133(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_134(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_135(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_136(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_137(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_138(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_139(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_140(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_141(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_142(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_143(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_144(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_145(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_146(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_147(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_148(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_149(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_150(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_151(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_152(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_153(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_154(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_155(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_156(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_157(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_158(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_159(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_160(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_161(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_162(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_163(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_164(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_165(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_166(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_167(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_168(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_169(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_170(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_171(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_172(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_173(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_174(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_175(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_176(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_177(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_178(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_179(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_180(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_181(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_182(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_183(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_184(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_185(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_186(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_187(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_188(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_189(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_190(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_191(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_192(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_193(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_194(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_195(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_196(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_197(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_198(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_199(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_200(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_201(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_202(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_203(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_204(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_205(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_206(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_207(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_208(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_209(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_210(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_211(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_212(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_213(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_214(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_215(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_216(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_217(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_218(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_219(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_220(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_221(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_222(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_223(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_224(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_225(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_226(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_227(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_228(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_229(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_230(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_231(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_232(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_233(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_234(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_235(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_236(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_237(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_238(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_239(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_240(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_241(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_242(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_243(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_244(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_245(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_246(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_247(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_248(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_249(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_250(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_251(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_252(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_253(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_254(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_255(s, p, o, m) 0
#define SIMD_FOR_CHECK_SIMD_FOR_256(s, p, o, m) 0
#
#endif
