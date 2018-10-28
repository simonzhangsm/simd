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
#ifndef SIMD_PREPROCESSOR_ARITHMETIC_DEC_HPP
#define SIMD_PREPROCESSOR_ARITHMETIC_DEC_HPP
#
#include <bigmath/simd/detail/preprocessor/config/config.hpp>
#
#/* SIMD_DEC */
#
#if ~SIMD_CONFIG_FLAGS() & SIMD_CONFIG_MWCC()
#define SIMD_DEC(x) SIMD_DEC_I(x)
#else
#define SIMD_DEC(x) SIMD_DEC_OO((x))
#define SIMD_DEC_OO(par) SIMD_DEC_I##par
#endif
#
#define SIMD_DEC_I(x) SIMD_DEC_##x
#
#define SIMD_DEC_0 0
#define SIMD_DEC_1 0
#define SIMD_DEC_2 1
#define SIMD_DEC_3 2
#define SIMD_DEC_4 3
#define SIMD_DEC_5 4
#define SIMD_DEC_6 5
#define SIMD_DEC_7 6
#define SIMD_DEC_8 7
#define SIMD_DEC_9 8
#define SIMD_DEC_10 9
#define SIMD_DEC_11 10
#define SIMD_DEC_12 11
#define SIMD_DEC_13 12
#define SIMD_DEC_14 13
#define SIMD_DEC_15 14
#define SIMD_DEC_16 15
#define SIMD_DEC_17 16
#define SIMD_DEC_18 17
#define SIMD_DEC_19 18
#define SIMD_DEC_20 19
#define SIMD_DEC_21 20
#define SIMD_DEC_22 21
#define SIMD_DEC_23 22
#define SIMD_DEC_24 23
#define SIMD_DEC_25 24
#define SIMD_DEC_26 25
#define SIMD_DEC_27 26
#define SIMD_DEC_28 27
#define SIMD_DEC_29 28
#define SIMD_DEC_30 29
#define SIMD_DEC_31 30
#define SIMD_DEC_32 31
#define SIMD_DEC_33 32
#define SIMD_DEC_34 33
#define SIMD_DEC_35 34
#define SIMD_DEC_36 35
#define SIMD_DEC_37 36
#define SIMD_DEC_38 37
#define SIMD_DEC_39 38
#define SIMD_DEC_40 39
#define SIMD_DEC_41 40
#define SIMD_DEC_42 41
#define SIMD_DEC_43 42
#define SIMD_DEC_44 43
#define SIMD_DEC_45 44
#define SIMD_DEC_46 45
#define SIMD_DEC_47 46
#define SIMD_DEC_48 47
#define SIMD_DEC_49 48
#define SIMD_DEC_50 49
#define SIMD_DEC_51 50
#define SIMD_DEC_52 51
#define SIMD_DEC_53 52
#define SIMD_DEC_54 53
#define SIMD_DEC_55 54
#define SIMD_DEC_56 55
#define SIMD_DEC_57 56
#define SIMD_DEC_58 57
#define SIMD_DEC_59 58
#define SIMD_DEC_60 59
#define SIMD_DEC_61 60
#define SIMD_DEC_62 61
#define SIMD_DEC_63 62
#define SIMD_DEC_64 63
#define SIMD_DEC_65 64
#define SIMD_DEC_66 65
#define SIMD_DEC_67 66
#define SIMD_DEC_68 67
#define SIMD_DEC_69 68
#define SIMD_DEC_70 69
#define SIMD_DEC_71 70
#define SIMD_DEC_72 71
#define SIMD_DEC_73 72
#define SIMD_DEC_74 73
#define SIMD_DEC_75 74
#define SIMD_DEC_76 75
#define SIMD_DEC_77 76
#define SIMD_DEC_78 77
#define SIMD_DEC_79 78
#define SIMD_DEC_80 79
#define SIMD_DEC_81 80
#define SIMD_DEC_82 81
#define SIMD_DEC_83 82
#define SIMD_DEC_84 83
#define SIMD_DEC_85 84
#define SIMD_DEC_86 85
#define SIMD_DEC_87 86
#define SIMD_DEC_88 87
#define SIMD_DEC_89 88
#define SIMD_DEC_90 89
#define SIMD_DEC_91 90
#define SIMD_DEC_92 91
#define SIMD_DEC_93 92
#define SIMD_DEC_94 93
#define SIMD_DEC_95 94
#define SIMD_DEC_96 95
#define SIMD_DEC_97 96
#define SIMD_DEC_98 97
#define SIMD_DEC_99 98
#define SIMD_DEC_100 99
#define SIMD_DEC_101 100
#define SIMD_DEC_102 101
#define SIMD_DEC_103 102
#define SIMD_DEC_104 103
#define SIMD_DEC_105 104
#define SIMD_DEC_106 105
#define SIMD_DEC_107 106
#define SIMD_DEC_108 107
#define SIMD_DEC_109 108
#define SIMD_DEC_110 109
#define SIMD_DEC_111 110
#define SIMD_DEC_112 111
#define SIMD_DEC_113 112
#define SIMD_DEC_114 113
#define SIMD_DEC_115 114
#define SIMD_DEC_116 115
#define SIMD_DEC_117 116
#define SIMD_DEC_118 117
#define SIMD_DEC_119 118
#define SIMD_DEC_120 119
#define SIMD_DEC_121 120
#define SIMD_DEC_122 121
#define SIMD_DEC_123 122
#define SIMD_DEC_124 123
#define SIMD_DEC_125 124
#define SIMD_DEC_126 125
#define SIMD_DEC_127 126
#define SIMD_DEC_128 127
#define SIMD_DEC_129 128
#define SIMD_DEC_130 129
#define SIMD_DEC_131 130
#define SIMD_DEC_132 131
#define SIMD_DEC_133 132
#define SIMD_DEC_134 133
#define SIMD_DEC_135 134
#define SIMD_DEC_136 135
#define SIMD_DEC_137 136
#define SIMD_DEC_138 137
#define SIMD_DEC_139 138
#define SIMD_DEC_140 139
#define SIMD_DEC_141 140
#define SIMD_DEC_142 141
#define SIMD_DEC_143 142
#define SIMD_DEC_144 143
#define SIMD_DEC_145 144
#define SIMD_DEC_146 145
#define SIMD_DEC_147 146
#define SIMD_DEC_148 147
#define SIMD_DEC_149 148
#define SIMD_DEC_150 149
#define SIMD_DEC_151 150
#define SIMD_DEC_152 151
#define SIMD_DEC_153 152
#define SIMD_DEC_154 153
#define SIMD_DEC_155 154
#define SIMD_DEC_156 155
#define SIMD_DEC_157 156
#define SIMD_DEC_158 157
#define SIMD_DEC_159 158
#define SIMD_DEC_160 159
#define SIMD_DEC_161 160
#define SIMD_DEC_162 161
#define SIMD_DEC_163 162
#define SIMD_DEC_164 163
#define SIMD_DEC_165 164
#define SIMD_DEC_166 165
#define SIMD_DEC_167 166
#define SIMD_DEC_168 167
#define SIMD_DEC_169 168
#define SIMD_DEC_170 169
#define SIMD_DEC_171 170
#define SIMD_DEC_172 171
#define SIMD_DEC_173 172
#define SIMD_DEC_174 173
#define SIMD_DEC_175 174
#define SIMD_DEC_176 175
#define SIMD_DEC_177 176
#define SIMD_DEC_178 177
#define SIMD_DEC_179 178
#define SIMD_DEC_180 179
#define SIMD_DEC_181 180
#define SIMD_DEC_182 181
#define SIMD_DEC_183 182
#define SIMD_DEC_184 183
#define SIMD_DEC_185 184
#define SIMD_DEC_186 185
#define SIMD_DEC_187 186
#define SIMD_DEC_188 187
#define SIMD_DEC_189 188
#define SIMD_DEC_190 189
#define SIMD_DEC_191 190
#define SIMD_DEC_192 191
#define SIMD_DEC_193 192
#define SIMD_DEC_194 193
#define SIMD_DEC_195 194
#define SIMD_DEC_196 195
#define SIMD_DEC_197 196
#define SIMD_DEC_198 197
#define SIMD_DEC_199 198
#define SIMD_DEC_200 199
#define SIMD_DEC_201 200
#define SIMD_DEC_202 201
#define SIMD_DEC_203 202
#define SIMD_DEC_204 203
#define SIMD_DEC_205 204
#define SIMD_DEC_206 205
#define SIMD_DEC_207 206
#define SIMD_DEC_208 207
#define SIMD_DEC_209 208
#define SIMD_DEC_210 209
#define SIMD_DEC_211 210
#define SIMD_DEC_212 211
#define SIMD_DEC_213 212
#define SIMD_DEC_214 213
#define SIMD_DEC_215 214
#define SIMD_DEC_216 215
#define SIMD_DEC_217 216
#define SIMD_DEC_218 217
#define SIMD_DEC_219 218
#define SIMD_DEC_220 219
#define SIMD_DEC_221 220
#define SIMD_DEC_222 221
#define SIMD_DEC_223 222
#define SIMD_DEC_224 223
#define SIMD_DEC_225 224
#define SIMD_DEC_226 225
#define SIMD_DEC_227 226
#define SIMD_DEC_228 227
#define SIMD_DEC_229 228
#define SIMD_DEC_230 229
#define SIMD_DEC_231 230
#define SIMD_DEC_232 231
#define SIMD_DEC_233 232
#define SIMD_DEC_234 233
#define SIMD_DEC_235 234
#define SIMD_DEC_236 235
#define SIMD_DEC_237 236
#define SIMD_DEC_238 237
#define SIMD_DEC_239 238
#define SIMD_DEC_240 239
#define SIMD_DEC_241 240
#define SIMD_DEC_242 241
#define SIMD_DEC_243 242
#define SIMD_DEC_244 243
#define SIMD_DEC_245 244
#define SIMD_DEC_246 245
#define SIMD_DEC_247 246
#define SIMD_DEC_248 247
#define SIMD_DEC_249 248
#define SIMD_DEC_250 249
#define SIMD_DEC_251 250
#define SIMD_DEC_252 251
#define SIMD_DEC_253 252
#define SIMD_DEC_254 253
#define SIMD_DEC_255 254
#define SIMD_DEC_256 255
#define SIMD_DEC_257 256
#
#endif
