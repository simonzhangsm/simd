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
#ifndef SIMD_PREPROCESSOR_ARITHMETIC_INC_HPP
#define SIMD_PREPROCESSOR_ARITHMETIC_INC_HPP
#
#include <bigmath/simd/detail/preprocessor/config/config.hpp>
#
#/* SIMD_INC */
#
#if ~SIMD_CONFIG_FLAGS() & SIMD_CONFIG_MWCC()
#define SIMD_INC(x) SIMD_INC_I(x)
#else
#define SIMD_INC(x) SIMD_INC_OO((x))
#define SIMD_INC_OO(par) SIMD_INC_I##par
#endif
#
#define SIMD_INC_I(x) SIMD_INC_##x
#
#define SIMD_INC_0 1
#define SIMD_INC_1 2
#define SIMD_INC_2 3
#define SIMD_INC_3 4
#define SIMD_INC_4 5
#define SIMD_INC_5 6
#define SIMD_INC_6 7
#define SIMD_INC_7 8
#define SIMD_INC_8 9
#define SIMD_INC_9 10
#define SIMD_INC_10 11
#define SIMD_INC_11 12
#define SIMD_INC_12 13
#define SIMD_INC_13 14
#define SIMD_INC_14 15
#define SIMD_INC_15 16
#define SIMD_INC_16 17
#define SIMD_INC_17 18
#define SIMD_INC_18 19
#define SIMD_INC_19 20
#define SIMD_INC_20 21
#define SIMD_INC_21 22
#define SIMD_INC_22 23
#define SIMD_INC_23 24
#define SIMD_INC_24 25
#define SIMD_INC_25 26
#define SIMD_INC_26 27
#define SIMD_INC_27 28
#define SIMD_INC_28 29
#define SIMD_INC_29 30
#define SIMD_INC_30 31
#define SIMD_INC_31 32
#define SIMD_INC_32 33
#define SIMD_INC_33 34
#define SIMD_INC_34 35
#define SIMD_INC_35 36
#define SIMD_INC_36 37
#define SIMD_INC_37 38
#define SIMD_INC_38 39
#define SIMD_INC_39 40
#define SIMD_INC_40 41
#define SIMD_INC_41 42
#define SIMD_INC_42 43
#define SIMD_INC_43 44
#define SIMD_INC_44 45
#define SIMD_INC_45 46
#define SIMD_INC_46 47
#define SIMD_INC_47 48
#define SIMD_INC_48 49
#define SIMD_INC_49 50
#define SIMD_INC_50 51
#define SIMD_INC_51 52
#define SIMD_INC_52 53
#define SIMD_INC_53 54
#define SIMD_INC_54 55
#define SIMD_INC_55 56
#define SIMD_INC_56 57
#define SIMD_INC_57 58
#define SIMD_INC_58 59
#define SIMD_INC_59 60
#define SIMD_INC_60 61
#define SIMD_INC_61 62
#define SIMD_INC_62 63
#define SIMD_INC_63 64
#define SIMD_INC_64 65
#define SIMD_INC_65 66
#define SIMD_INC_66 67
#define SIMD_INC_67 68
#define SIMD_INC_68 69
#define SIMD_INC_69 70
#define SIMD_INC_70 71
#define SIMD_INC_71 72
#define SIMD_INC_72 73
#define SIMD_INC_73 74
#define SIMD_INC_74 75
#define SIMD_INC_75 76
#define SIMD_INC_76 77
#define SIMD_INC_77 78
#define SIMD_INC_78 79
#define SIMD_INC_79 80
#define SIMD_INC_80 81
#define SIMD_INC_81 82
#define SIMD_INC_82 83
#define SIMD_INC_83 84
#define SIMD_INC_84 85
#define SIMD_INC_85 86
#define SIMD_INC_86 87
#define SIMD_INC_87 88
#define SIMD_INC_88 89
#define SIMD_INC_89 90
#define SIMD_INC_90 91
#define SIMD_INC_91 92
#define SIMD_INC_92 93
#define SIMD_INC_93 94
#define SIMD_INC_94 95
#define SIMD_INC_95 96
#define SIMD_INC_96 97
#define SIMD_INC_97 98
#define SIMD_INC_98 99
#define SIMD_INC_99 100
#define SIMD_INC_100 101
#define SIMD_INC_101 102
#define SIMD_INC_102 103
#define SIMD_INC_103 104
#define SIMD_INC_104 105
#define SIMD_INC_105 106
#define SIMD_INC_106 107
#define SIMD_INC_107 108
#define SIMD_INC_108 109
#define SIMD_INC_109 110
#define SIMD_INC_110 111
#define SIMD_INC_111 112
#define SIMD_INC_112 113
#define SIMD_INC_113 114
#define SIMD_INC_114 115
#define SIMD_INC_115 116
#define SIMD_INC_116 117
#define SIMD_INC_117 118
#define SIMD_INC_118 119
#define SIMD_INC_119 120
#define SIMD_INC_120 121
#define SIMD_INC_121 122
#define SIMD_INC_122 123
#define SIMD_INC_123 124
#define SIMD_INC_124 125
#define SIMD_INC_125 126
#define SIMD_INC_126 127
#define SIMD_INC_127 128
#define SIMD_INC_128 129
#define SIMD_INC_129 130
#define SIMD_INC_130 131
#define SIMD_INC_131 132
#define SIMD_INC_132 133
#define SIMD_INC_133 134
#define SIMD_INC_134 135
#define SIMD_INC_135 136
#define SIMD_INC_136 137
#define SIMD_INC_137 138
#define SIMD_INC_138 139
#define SIMD_INC_139 140
#define SIMD_INC_140 141
#define SIMD_INC_141 142
#define SIMD_INC_142 143
#define SIMD_INC_143 144
#define SIMD_INC_144 145
#define SIMD_INC_145 146
#define SIMD_INC_146 147
#define SIMD_INC_147 148
#define SIMD_INC_148 149
#define SIMD_INC_149 150
#define SIMD_INC_150 151
#define SIMD_INC_151 152
#define SIMD_INC_152 153
#define SIMD_INC_153 154
#define SIMD_INC_154 155
#define SIMD_INC_155 156
#define SIMD_INC_156 157
#define SIMD_INC_157 158
#define SIMD_INC_158 159
#define SIMD_INC_159 160
#define SIMD_INC_160 161
#define SIMD_INC_161 162
#define SIMD_INC_162 163
#define SIMD_INC_163 164
#define SIMD_INC_164 165
#define SIMD_INC_165 166
#define SIMD_INC_166 167
#define SIMD_INC_167 168
#define SIMD_INC_168 169
#define SIMD_INC_169 170
#define SIMD_INC_170 171
#define SIMD_INC_171 172
#define SIMD_INC_172 173
#define SIMD_INC_173 174
#define SIMD_INC_174 175
#define SIMD_INC_175 176
#define SIMD_INC_176 177
#define SIMD_INC_177 178
#define SIMD_INC_178 179
#define SIMD_INC_179 180
#define SIMD_INC_180 181
#define SIMD_INC_181 182
#define SIMD_INC_182 183
#define SIMD_INC_183 184
#define SIMD_INC_184 185
#define SIMD_INC_185 186
#define SIMD_INC_186 187
#define SIMD_INC_187 188
#define SIMD_INC_188 189
#define SIMD_INC_189 190
#define SIMD_INC_190 191
#define SIMD_INC_191 192
#define SIMD_INC_192 193
#define SIMD_INC_193 194
#define SIMD_INC_194 195
#define SIMD_INC_195 196
#define SIMD_INC_196 197
#define SIMD_INC_197 198
#define SIMD_INC_198 199
#define SIMD_INC_199 200
#define SIMD_INC_200 201
#define SIMD_INC_201 202
#define SIMD_INC_202 203
#define SIMD_INC_203 204
#define SIMD_INC_204 205
#define SIMD_INC_205 206
#define SIMD_INC_206 207
#define SIMD_INC_207 208
#define SIMD_INC_208 209
#define SIMD_INC_209 210
#define SIMD_INC_210 211
#define SIMD_INC_211 212
#define SIMD_INC_212 213
#define SIMD_INC_213 214
#define SIMD_INC_214 215
#define SIMD_INC_215 216
#define SIMD_INC_216 217
#define SIMD_INC_217 218
#define SIMD_INC_218 219
#define SIMD_INC_219 220
#define SIMD_INC_220 221
#define SIMD_INC_221 222
#define SIMD_INC_222 223
#define SIMD_INC_223 224
#define SIMD_INC_224 225
#define SIMD_INC_225 226
#define SIMD_INC_226 227
#define SIMD_INC_227 228
#define SIMD_INC_228 229
#define SIMD_INC_229 230
#define SIMD_INC_230 231
#define SIMD_INC_231 232
#define SIMD_INC_232 233
#define SIMD_INC_233 234
#define SIMD_INC_234 235
#define SIMD_INC_235 236
#define SIMD_INC_236 237
#define SIMD_INC_237 238
#define SIMD_INC_238 239
#define SIMD_INC_239 240
#define SIMD_INC_240 241
#define SIMD_INC_241 242
#define SIMD_INC_242 243
#define SIMD_INC_243 244
#define SIMD_INC_244 245
#define SIMD_INC_245 246
#define SIMD_INC_246 247
#define SIMD_INC_247 248
#define SIMD_INC_248 249
#define SIMD_INC_249 250
#define SIMD_INC_250 251
#define SIMD_INC_251 252
#define SIMD_INC_252 253
#define SIMD_INC_253 254
#define SIMD_INC_254 255
#define SIMD_INC_255 256
#define SIMD_INC_256 256
#
#endif
