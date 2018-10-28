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
#ifndef SIMD_PREPROCESSOR_SEQ_ELEM_HPP
#define SIMD_PREPROCESSOR_SEQ_ELEM_HPP
#
#include <bigmath/simd/detail/preprocessor/cat.hpp>
#include <bigmath/simd/detail/preprocessor/config/config.hpp>
#include <bigmath/simd/detail/preprocessor/facilities/empty.hpp>
#
#/* SIMD_SEQ_ELEM */
#
#if ~SIMD_CONFIG_FLAGS() & SIMD_CONFIG_MWCC()
#define SIMD_SEQ_ELEM(i, seq) SIMD_SEQ_ELEM_I(i, seq)
#else
#define SIMD_SEQ_ELEM(i, seq) SIMD_SEQ_ELEM_I((i, seq))
#endif
#
#if SIMD_CONFIG_FLAGS() & SIMD_CONFIG_MSVC()
#define SIMD_SEQ_ELEM_I(i, seq) SIMD_SEQ_ELEM_II((SIMD_SEQ_ELEM_##i seq))
#define SIMD_SEQ_ELEM_II(res) SIMD_SEQ_ELEM_IV(SIMD_SEQ_ELEM_III res)
#define SIMD_SEQ_ELEM_III(x, _) x SIMD_EMPTY()
#define SIMD_SEQ_ELEM_IV(x) x
#elif SIMD_CONFIG_FLAGS() & SIMD_CONFIG_MWCC()
#define SIMD_SEQ_ELEM_I(par) SIMD_SEQ_ELEM_II##par
#define SIMD_SEQ_ELEM_II(i, seq) SIMD_SEQ_ELEM_III(SIMD_SEQ_ELEM_##i##seq)
#define SIMD_SEQ_ELEM_III(im) SIMD_SEQ_ELEM_IV(im)
#define SIMD_SEQ_ELEM_IV(x, _) x
#else
#if defined(__IBMC__) || defined(__IBMCPP__)
#define SIMD_SEQ_ELEM_I(i, seq) SIMD_SEQ_ELEM_II(SIMD_CAT(SIMD_SEQ_ELEM_##i, seq))
#else
#define SIMD_SEQ_ELEM_I(i, seq) SIMD_SEQ_ELEM_II(SIMD_SEQ_ELEM_##i seq)
#endif
#define SIMD_SEQ_ELEM_II(im) SIMD_SEQ_ELEM_III(im)
#define SIMD_SEQ_ELEM_III(x, _) x
#endif
#
#define SIMD_SEQ_ELEM_0(x) x, SIMD_NIL
#define SIMD_SEQ_ELEM_1(_) SIMD_SEQ_ELEM_0
#define SIMD_SEQ_ELEM_2(_) SIMD_SEQ_ELEM_1
#define SIMD_SEQ_ELEM_3(_) SIMD_SEQ_ELEM_2
#define SIMD_SEQ_ELEM_4(_) SIMD_SEQ_ELEM_3
#define SIMD_SEQ_ELEM_5(_) SIMD_SEQ_ELEM_4
#define SIMD_SEQ_ELEM_6(_) SIMD_SEQ_ELEM_5
#define SIMD_SEQ_ELEM_7(_) SIMD_SEQ_ELEM_6
#define SIMD_SEQ_ELEM_8(_) SIMD_SEQ_ELEM_7
#define SIMD_SEQ_ELEM_9(_) SIMD_SEQ_ELEM_8
#define SIMD_SEQ_ELEM_10(_) SIMD_SEQ_ELEM_9
#define SIMD_SEQ_ELEM_11(_) SIMD_SEQ_ELEM_10
#define SIMD_SEQ_ELEM_12(_) SIMD_SEQ_ELEM_11
#define SIMD_SEQ_ELEM_13(_) SIMD_SEQ_ELEM_12
#define SIMD_SEQ_ELEM_14(_) SIMD_SEQ_ELEM_13
#define SIMD_SEQ_ELEM_15(_) SIMD_SEQ_ELEM_14
#define SIMD_SEQ_ELEM_16(_) SIMD_SEQ_ELEM_15
#define SIMD_SEQ_ELEM_17(_) SIMD_SEQ_ELEM_16
#define SIMD_SEQ_ELEM_18(_) SIMD_SEQ_ELEM_17
#define SIMD_SEQ_ELEM_19(_) SIMD_SEQ_ELEM_18
#define SIMD_SEQ_ELEM_20(_) SIMD_SEQ_ELEM_19
#define SIMD_SEQ_ELEM_21(_) SIMD_SEQ_ELEM_20
#define SIMD_SEQ_ELEM_22(_) SIMD_SEQ_ELEM_21
#define SIMD_SEQ_ELEM_23(_) SIMD_SEQ_ELEM_22
#define SIMD_SEQ_ELEM_24(_) SIMD_SEQ_ELEM_23
#define SIMD_SEQ_ELEM_25(_) SIMD_SEQ_ELEM_24
#define SIMD_SEQ_ELEM_26(_) SIMD_SEQ_ELEM_25
#define SIMD_SEQ_ELEM_27(_) SIMD_SEQ_ELEM_26
#define SIMD_SEQ_ELEM_28(_) SIMD_SEQ_ELEM_27
#define SIMD_SEQ_ELEM_29(_) SIMD_SEQ_ELEM_28
#define SIMD_SEQ_ELEM_30(_) SIMD_SEQ_ELEM_29
#define SIMD_SEQ_ELEM_31(_) SIMD_SEQ_ELEM_30
#define SIMD_SEQ_ELEM_32(_) SIMD_SEQ_ELEM_31
#define SIMD_SEQ_ELEM_33(_) SIMD_SEQ_ELEM_32
#define SIMD_SEQ_ELEM_34(_) SIMD_SEQ_ELEM_33
#define SIMD_SEQ_ELEM_35(_) SIMD_SEQ_ELEM_34
#define SIMD_SEQ_ELEM_36(_) SIMD_SEQ_ELEM_35
#define SIMD_SEQ_ELEM_37(_) SIMD_SEQ_ELEM_36
#define SIMD_SEQ_ELEM_38(_) SIMD_SEQ_ELEM_37
#define SIMD_SEQ_ELEM_39(_) SIMD_SEQ_ELEM_38
#define SIMD_SEQ_ELEM_40(_) SIMD_SEQ_ELEM_39
#define SIMD_SEQ_ELEM_41(_) SIMD_SEQ_ELEM_40
#define SIMD_SEQ_ELEM_42(_) SIMD_SEQ_ELEM_41
#define SIMD_SEQ_ELEM_43(_) SIMD_SEQ_ELEM_42
#define SIMD_SEQ_ELEM_44(_) SIMD_SEQ_ELEM_43
#define SIMD_SEQ_ELEM_45(_) SIMD_SEQ_ELEM_44
#define SIMD_SEQ_ELEM_46(_) SIMD_SEQ_ELEM_45
#define SIMD_SEQ_ELEM_47(_) SIMD_SEQ_ELEM_46
#define SIMD_SEQ_ELEM_48(_) SIMD_SEQ_ELEM_47
#define SIMD_SEQ_ELEM_49(_) SIMD_SEQ_ELEM_48
#define SIMD_SEQ_ELEM_50(_) SIMD_SEQ_ELEM_49
#define SIMD_SEQ_ELEM_51(_) SIMD_SEQ_ELEM_50
#define SIMD_SEQ_ELEM_52(_) SIMD_SEQ_ELEM_51
#define SIMD_SEQ_ELEM_53(_) SIMD_SEQ_ELEM_52
#define SIMD_SEQ_ELEM_54(_) SIMD_SEQ_ELEM_53
#define SIMD_SEQ_ELEM_55(_) SIMD_SEQ_ELEM_54
#define SIMD_SEQ_ELEM_56(_) SIMD_SEQ_ELEM_55
#define SIMD_SEQ_ELEM_57(_) SIMD_SEQ_ELEM_56
#define SIMD_SEQ_ELEM_58(_) SIMD_SEQ_ELEM_57
#define SIMD_SEQ_ELEM_59(_) SIMD_SEQ_ELEM_58
#define SIMD_SEQ_ELEM_60(_) SIMD_SEQ_ELEM_59
#define SIMD_SEQ_ELEM_61(_) SIMD_SEQ_ELEM_60
#define SIMD_SEQ_ELEM_62(_) SIMD_SEQ_ELEM_61
#define SIMD_SEQ_ELEM_63(_) SIMD_SEQ_ELEM_62
#define SIMD_SEQ_ELEM_64(_) SIMD_SEQ_ELEM_63
#define SIMD_SEQ_ELEM_65(_) SIMD_SEQ_ELEM_64
#define SIMD_SEQ_ELEM_66(_) SIMD_SEQ_ELEM_65
#define SIMD_SEQ_ELEM_67(_) SIMD_SEQ_ELEM_66
#define SIMD_SEQ_ELEM_68(_) SIMD_SEQ_ELEM_67
#define SIMD_SEQ_ELEM_69(_) SIMD_SEQ_ELEM_68
#define SIMD_SEQ_ELEM_70(_) SIMD_SEQ_ELEM_69
#define SIMD_SEQ_ELEM_71(_) SIMD_SEQ_ELEM_70
#define SIMD_SEQ_ELEM_72(_) SIMD_SEQ_ELEM_71
#define SIMD_SEQ_ELEM_73(_) SIMD_SEQ_ELEM_72
#define SIMD_SEQ_ELEM_74(_) SIMD_SEQ_ELEM_73
#define SIMD_SEQ_ELEM_75(_) SIMD_SEQ_ELEM_74
#define SIMD_SEQ_ELEM_76(_) SIMD_SEQ_ELEM_75
#define SIMD_SEQ_ELEM_77(_) SIMD_SEQ_ELEM_76
#define SIMD_SEQ_ELEM_78(_) SIMD_SEQ_ELEM_77
#define SIMD_SEQ_ELEM_79(_) SIMD_SEQ_ELEM_78
#define SIMD_SEQ_ELEM_80(_) SIMD_SEQ_ELEM_79
#define SIMD_SEQ_ELEM_81(_) SIMD_SEQ_ELEM_80
#define SIMD_SEQ_ELEM_82(_) SIMD_SEQ_ELEM_81
#define SIMD_SEQ_ELEM_83(_) SIMD_SEQ_ELEM_82
#define SIMD_SEQ_ELEM_84(_) SIMD_SEQ_ELEM_83
#define SIMD_SEQ_ELEM_85(_) SIMD_SEQ_ELEM_84
#define SIMD_SEQ_ELEM_86(_) SIMD_SEQ_ELEM_85
#define SIMD_SEQ_ELEM_87(_) SIMD_SEQ_ELEM_86
#define SIMD_SEQ_ELEM_88(_) SIMD_SEQ_ELEM_87
#define SIMD_SEQ_ELEM_89(_) SIMD_SEQ_ELEM_88
#define SIMD_SEQ_ELEM_90(_) SIMD_SEQ_ELEM_89
#define SIMD_SEQ_ELEM_91(_) SIMD_SEQ_ELEM_90
#define SIMD_SEQ_ELEM_92(_) SIMD_SEQ_ELEM_91
#define SIMD_SEQ_ELEM_93(_) SIMD_SEQ_ELEM_92
#define SIMD_SEQ_ELEM_94(_) SIMD_SEQ_ELEM_93
#define SIMD_SEQ_ELEM_95(_) SIMD_SEQ_ELEM_94
#define SIMD_SEQ_ELEM_96(_) SIMD_SEQ_ELEM_95
#define SIMD_SEQ_ELEM_97(_) SIMD_SEQ_ELEM_96
#define SIMD_SEQ_ELEM_98(_) SIMD_SEQ_ELEM_97
#define SIMD_SEQ_ELEM_99(_) SIMD_SEQ_ELEM_98
#define SIMD_SEQ_ELEM_100(_) SIMD_SEQ_ELEM_99
#define SIMD_SEQ_ELEM_101(_) SIMD_SEQ_ELEM_100
#define SIMD_SEQ_ELEM_102(_) SIMD_SEQ_ELEM_101
#define SIMD_SEQ_ELEM_103(_) SIMD_SEQ_ELEM_102
#define SIMD_SEQ_ELEM_104(_) SIMD_SEQ_ELEM_103
#define SIMD_SEQ_ELEM_105(_) SIMD_SEQ_ELEM_104
#define SIMD_SEQ_ELEM_106(_) SIMD_SEQ_ELEM_105
#define SIMD_SEQ_ELEM_107(_) SIMD_SEQ_ELEM_106
#define SIMD_SEQ_ELEM_108(_) SIMD_SEQ_ELEM_107
#define SIMD_SEQ_ELEM_109(_) SIMD_SEQ_ELEM_108
#define SIMD_SEQ_ELEM_110(_) SIMD_SEQ_ELEM_109
#define SIMD_SEQ_ELEM_111(_) SIMD_SEQ_ELEM_110
#define SIMD_SEQ_ELEM_112(_) SIMD_SEQ_ELEM_111
#define SIMD_SEQ_ELEM_113(_) SIMD_SEQ_ELEM_112
#define SIMD_SEQ_ELEM_114(_) SIMD_SEQ_ELEM_113
#define SIMD_SEQ_ELEM_115(_) SIMD_SEQ_ELEM_114
#define SIMD_SEQ_ELEM_116(_) SIMD_SEQ_ELEM_115
#define SIMD_SEQ_ELEM_117(_) SIMD_SEQ_ELEM_116
#define SIMD_SEQ_ELEM_118(_) SIMD_SEQ_ELEM_117
#define SIMD_SEQ_ELEM_119(_) SIMD_SEQ_ELEM_118
#define SIMD_SEQ_ELEM_120(_) SIMD_SEQ_ELEM_119
#define SIMD_SEQ_ELEM_121(_) SIMD_SEQ_ELEM_120
#define SIMD_SEQ_ELEM_122(_) SIMD_SEQ_ELEM_121
#define SIMD_SEQ_ELEM_123(_) SIMD_SEQ_ELEM_122
#define SIMD_SEQ_ELEM_124(_) SIMD_SEQ_ELEM_123
#define SIMD_SEQ_ELEM_125(_) SIMD_SEQ_ELEM_124
#define SIMD_SEQ_ELEM_126(_) SIMD_SEQ_ELEM_125
#define SIMD_SEQ_ELEM_127(_) SIMD_SEQ_ELEM_126
#define SIMD_SEQ_ELEM_128(_) SIMD_SEQ_ELEM_127
#define SIMD_SEQ_ELEM_129(_) SIMD_SEQ_ELEM_128
#define SIMD_SEQ_ELEM_130(_) SIMD_SEQ_ELEM_129
#define SIMD_SEQ_ELEM_131(_) SIMD_SEQ_ELEM_130
#define SIMD_SEQ_ELEM_132(_) SIMD_SEQ_ELEM_131
#define SIMD_SEQ_ELEM_133(_) SIMD_SEQ_ELEM_132
#define SIMD_SEQ_ELEM_134(_) SIMD_SEQ_ELEM_133
#define SIMD_SEQ_ELEM_135(_) SIMD_SEQ_ELEM_134
#define SIMD_SEQ_ELEM_136(_) SIMD_SEQ_ELEM_135
#define SIMD_SEQ_ELEM_137(_) SIMD_SEQ_ELEM_136
#define SIMD_SEQ_ELEM_138(_) SIMD_SEQ_ELEM_137
#define SIMD_SEQ_ELEM_139(_) SIMD_SEQ_ELEM_138
#define SIMD_SEQ_ELEM_140(_) SIMD_SEQ_ELEM_139
#define SIMD_SEQ_ELEM_141(_) SIMD_SEQ_ELEM_140
#define SIMD_SEQ_ELEM_142(_) SIMD_SEQ_ELEM_141
#define SIMD_SEQ_ELEM_143(_) SIMD_SEQ_ELEM_142
#define SIMD_SEQ_ELEM_144(_) SIMD_SEQ_ELEM_143
#define SIMD_SEQ_ELEM_145(_) SIMD_SEQ_ELEM_144
#define SIMD_SEQ_ELEM_146(_) SIMD_SEQ_ELEM_145
#define SIMD_SEQ_ELEM_147(_) SIMD_SEQ_ELEM_146
#define SIMD_SEQ_ELEM_148(_) SIMD_SEQ_ELEM_147
#define SIMD_SEQ_ELEM_149(_) SIMD_SEQ_ELEM_148
#define SIMD_SEQ_ELEM_150(_) SIMD_SEQ_ELEM_149
#define SIMD_SEQ_ELEM_151(_) SIMD_SEQ_ELEM_150
#define SIMD_SEQ_ELEM_152(_) SIMD_SEQ_ELEM_151
#define SIMD_SEQ_ELEM_153(_) SIMD_SEQ_ELEM_152
#define SIMD_SEQ_ELEM_154(_) SIMD_SEQ_ELEM_153
#define SIMD_SEQ_ELEM_155(_) SIMD_SEQ_ELEM_154
#define SIMD_SEQ_ELEM_156(_) SIMD_SEQ_ELEM_155
#define SIMD_SEQ_ELEM_157(_) SIMD_SEQ_ELEM_156
#define SIMD_SEQ_ELEM_158(_) SIMD_SEQ_ELEM_157
#define SIMD_SEQ_ELEM_159(_) SIMD_SEQ_ELEM_158
#define SIMD_SEQ_ELEM_160(_) SIMD_SEQ_ELEM_159
#define SIMD_SEQ_ELEM_161(_) SIMD_SEQ_ELEM_160
#define SIMD_SEQ_ELEM_162(_) SIMD_SEQ_ELEM_161
#define SIMD_SEQ_ELEM_163(_) SIMD_SEQ_ELEM_162
#define SIMD_SEQ_ELEM_164(_) SIMD_SEQ_ELEM_163
#define SIMD_SEQ_ELEM_165(_) SIMD_SEQ_ELEM_164
#define SIMD_SEQ_ELEM_166(_) SIMD_SEQ_ELEM_165
#define SIMD_SEQ_ELEM_167(_) SIMD_SEQ_ELEM_166
#define SIMD_SEQ_ELEM_168(_) SIMD_SEQ_ELEM_167
#define SIMD_SEQ_ELEM_169(_) SIMD_SEQ_ELEM_168
#define SIMD_SEQ_ELEM_170(_) SIMD_SEQ_ELEM_169
#define SIMD_SEQ_ELEM_171(_) SIMD_SEQ_ELEM_170
#define SIMD_SEQ_ELEM_172(_) SIMD_SEQ_ELEM_171
#define SIMD_SEQ_ELEM_173(_) SIMD_SEQ_ELEM_172
#define SIMD_SEQ_ELEM_174(_) SIMD_SEQ_ELEM_173
#define SIMD_SEQ_ELEM_175(_) SIMD_SEQ_ELEM_174
#define SIMD_SEQ_ELEM_176(_) SIMD_SEQ_ELEM_175
#define SIMD_SEQ_ELEM_177(_) SIMD_SEQ_ELEM_176
#define SIMD_SEQ_ELEM_178(_) SIMD_SEQ_ELEM_177
#define SIMD_SEQ_ELEM_179(_) SIMD_SEQ_ELEM_178
#define SIMD_SEQ_ELEM_180(_) SIMD_SEQ_ELEM_179
#define SIMD_SEQ_ELEM_181(_) SIMD_SEQ_ELEM_180
#define SIMD_SEQ_ELEM_182(_) SIMD_SEQ_ELEM_181
#define SIMD_SEQ_ELEM_183(_) SIMD_SEQ_ELEM_182
#define SIMD_SEQ_ELEM_184(_) SIMD_SEQ_ELEM_183
#define SIMD_SEQ_ELEM_185(_) SIMD_SEQ_ELEM_184
#define SIMD_SEQ_ELEM_186(_) SIMD_SEQ_ELEM_185
#define SIMD_SEQ_ELEM_187(_) SIMD_SEQ_ELEM_186
#define SIMD_SEQ_ELEM_188(_) SIMD_SEQ_ELEM_187
#define SIMD_SEQ_ELEM_189(_) SIMD_SEQ_ELEM_188
#define SIMD_SEQ_ELEM_190(_) SIMD_SEQ_ELEM_189
#define SIMD_SEQ_ELEM_191(_) SIMD_SEQ_ELEM_190
#define SIMD_SEQ_ELEM_192(_) SIMD_SEQ_ELEM_191
#define SIMD_SEQ_ELEM_193(_) SIMD_SEQ_ELEM_192
#define SIMD_SEQ_ELEM_194(_) SIMD_SEQ_ELEM_193
#define SIMD_SEQ_ELEM_195(_) SIMD_SEQ_ELEM_194
#define SIMD_SEQ_ELEM_196(_) SIMD_SEQ_ELEM_195
#define SIMD_SEQ_ELEM_197(_) SIMD_SEQ_ELEM_196
#define SIMD_SEQ_ELEM_198(_) SIMD_SEQ_ELEM_197
#define SIMD_SEQ_ELEM_199(_) SIMD_SEQ_ELEM_198
#define SIMD_SEQ_ELEM_200(_) SIMD_SEQ_ELEM_199
#define SIMD_SEQ_ELEM_201(_) SIMD_SEQ_ELEM_200
#define SIMD_SEQ_ELEM_202(_) SIMD_SEQ_ELEM_201
#define SIMD_SEQ_ELEM_203(_) SIMD_SEQ_ELEM_202
#define SIMD_SEQ_ELEM_204(_) SIMD_SEQ_ELEM_203
#define SIMD_SEQ_ELEM_205(_) SIMD_SEQ_ELEM_204
#define SIMD_SEQ_ELEM_206(_) SIMD_SEQ_ELEM_205
#define SIMD_SEQ_ELEM_207(_) SIMD_SEQ_ELEM_206
#define SIMD_SEQ_ELEM_208(_) SIMD_SEQ_ELEM_207
#define SIMD_SEQ_ELEM_209(_) SIMD_SEQ_ELEM_208
#define SIMD_SEQ_ELEM_210(_) SIMD_SEQ_ELEM_209
#define SIMD_SEQ_ELEM_211(_) SIMD_SEQ_ELEM_210
#define SIMD_SEQ_ELEM_212(_) SIMD_SEQ_ELEM_211
#define SIMD_SEQ_ELEM_213(_) SIMD_SEQ_ELEM_212
#define SIMD_SEQ_ELEM_214(_) SIMD_SEQ_ELEM_213
#define SIMD_SEQ_ELEM_215(_) SIMD_SEQ_ELEM_214
#define SIMD_SEQ_ELEM_216(_) SIMD_SEQ_ELEM_215
#define SIMD_SEQ_ELEM_217(_) SIMD_SEQ_ELEM_216
#define SIMD_SEQ_ELEM_218(_) SIMD_SEQ_ELEM_217
#define SIMD_SEQ_ELEM_219(_) SIMD_SEQ_ELEM_218
#define SIMD_SEQ_ELEM_220(_) SIMD_SEQ_ELEM_219
#define SIMD_SEQ_ELEM_221(_) SIMD_SEQ_ELEM_220
#define SIMD_SEQ_ELEM_222(_) SIMD_SEQ_ELEM_221
#define SIMD_SEQ_ELEM_223(_) SIMD_SEQ_ELEM_222
#define SIMD_SEQ_ELEM_224(_) SIMD_SEQ_ELEM_223
#define SIMD_SEQ_ELEM_225(_) SIMD_SEQ_ELEM_224
#define SIMD_SEQ_ELEM_226(_) SIMD_SEQ_ELEM_225
#define SIMD_SEQ_ELEM_227(_) SIMD_SEQ_ELEM_226
#define SIMD_SEQ_ELEM_228(_) SIMD_SEQ_ELEM_227
#define SIMD_SEQ_ELEM_229(_) SIMD_SEQ_ELEM_228
#define SIMD_SEQ_ELEM_230(_) SIMD_SEQ_ELEM_229
#define SIMD_SEQ_ELEM_231(_) SIMD_SEQ_ELEM_230
#define SIMD_SEQ_ELEM_232(_) SIMD_SEQ_ELEM_231
#define SIMD_SEQ_ELEM_233(_) SIMD_SEQ_ELEM_232
#define SIMD_SEQ_ELEM_234(_) SIMD_SEQ_ELEM_233
#define SIMD_SEQ_ELEM_235(_) SIMD_SEQ_ELEM_234
#define SIMD_SEQ_ELEM_236(_) SIMD_SEQ_ELEM_235
#define SIMD_SEQ_ELEM_237(_) SIMD_SEQ_ELEM_236
#define SIMD_SEQ_ELEM_238(_) SIMD_SEQ_ELEM_237
#define SIMD_SEQ_ELEM_239(_) SIMD_SEQ_ELEM_238
#define SIMD_SEQ_ELEM_240(_) SIMD_SEQ_ELEM_239
#define SIMD_SEQ_ELEM_241(_) SIMD_SEQ_ELEM_240
#define SIMD_SEQ_ELEM_242(_) SIMD_SEQ_ELEM_241
#define SIMD_SEQ_ELEM_243(_) SIMD_SEQ_ELEM_242
#define SIMD_SEQ_ELEM_244(_) SIMD_SEQ_ELEM_243
#define SIMD_SEQ_ELEM_245(_) SIMD_SEQ_ELEM_244
#define SIMD_SEQ_ELEM_246(_) SIMD_SEQ_ELEM_245
#define SIMD_SEQ_ELEM_247(_) SIMD_SEQ_ELEM_246
#define SIMD_SEQ_ELEM_248(_) SIMD_SEQ_ELEM_247
#define SIMD_SEQ_ELEM_249(_) SIMD_SEQ_ELEM_248
#define SIMD_SEQ_ELEM_250(_) SIMD_SEQ_ELEM_249
#define SIMD_SEQ_ELEM_251(_) SIMD_SEQ_ELEM_250
#define SIMD_SEQ_ELEM_252(_) SIMD_SEQ_ELEM_251
#define SIMD_SEQ_ELEM_253(_) SIMD_SEQ_ELEM_252
#define SIMD_SEQ_ELEM_254(_) SIMD_SEQ_ELEM_253
#define SIMD_SEQ_ELEM_255(_) SIMD_SEQ_ELEM_254
#
#endif