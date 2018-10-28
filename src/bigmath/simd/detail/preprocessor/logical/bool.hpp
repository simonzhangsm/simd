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
#ifndef SIMD_PREPROCESSOR_LOGICAL_BOOL_HPP
#define SIMD_PREPROCESSOR_LOGICAL_BOOL_HPP
#
#include <bigmath/simd/detail/preprocessor/config/config.hpp>
#
#/* SIMD_BOOL */
#
#if ~SIMD_CONFIG_FLAGS() & SIMD_CONFIG_MWCC()
#define SIMD_BOOL(x) SIMD_BOOL_I(x)
#else
#define SIMD_BOOL(x) SIMD_BOOL_OO((x))
#define SIMD_BOOL_OO(par) SIMD_BOOL_I##par
#endif
#
#define SIMD_BOOL_I(x) SIMD_BOOL_##x
#
#define SIMD_BOOL_0 0
#define SIMD_BOOL_1 1
#define SIMD_BOOL_2 1
#define SIMD_BOOL_3 1
#define SIMD_BOOL_4 1
#define SIMD_BOOL_5 1
#define SIMD_BOOL_6 1
#define SIMD_BOOL_7 1
#define SIMD_BOOL_8 1
#define SIMD_BOOL_9 1
#define SIMD_BOOL_10 1
#define SIMD_BOOL_11 1
#define SIMD_BOOL_12 1
#define SIMD_BOOL_13 1
#define SIMD_BOOL_14 1
#define SIMD_BOOL_15 1
#define SIMD_BOOL_16 1
#define SIMD_BOOL_17 1
#define SIMD_BOOL_18 1
#define SIMD_BOOL_19 1
#define SIMD_BOOL_20 1
#define SIMD_BOOL_21 1
#define SIMD_BOOL_22 1
#define SIMD_BOOL_23 1
#define SIMD_BOOL_24 1
#define SIMD_BOOL_25 1
#define SIMD_BOOL_26 1
#define SIMD_BOOL_27 1
#define SIMD_BOOL_28 1
#define SIMD_BOOL_29 1
#define SIMD_BOOL_30 1
#define SIMD_BOOL_31 1
#define SIMD_BOOL_32 1
#define SIMD_BOOL_33 1
#define SIMD_BOOL_34 1
#define SIMD_BOOL_35 1
#define SIMD_BOOL_36 1
#define SIMD_BOOL_37 1
#define SIMD_BOOL_38 1
#define SIMD_BOOL_39 1
#define SIMD_BOOL_40 1
#define SIMD_BOOL_41 1
#define SIMD_BOOL_42 1
#define SIMD_BOOL_43 1
#define SIMD_BOOL_44 1
#define SIMD_BOOL_45 1
#define SIMD_BOOL_46 1
#define SIMD_BOOL_47 1
#define SIMD_BOOL_48 1
#define SIMD_BOOL_49 1
#define SIMD_BOOL_50 1
#define SIMD_BOOL_51 1
#define SIMD_BOOL_52 1
#define SIMD_BOOL_53 1
#define SIMD_BOOL_54 1
#define SIMD_BOOL_55 1
#define SIMD_BOOL_56 1
#define SIMD_BOOL_57 1
#define SIMD_BOOL_58 1
#define SIMD_BOOL_59 1
#define SIMD_BOOL_60 1
#define SIMD_BOOL_61 1
#define SIMD_BOOL_62 1
#define SIMD_BOOL_63 1
#define SIMD_BOOL_64 1
#define SIMD_BOOL_65 1
#define SIMD_BOOL_66 1
#define SIMD_BOOL_67 1
#define SIMD_BOOL_68 1
#define SIMD_BOOL_69 1
#define SIMD_BOOL_70 1
#define SIMD_BOOL_71 1
#define SIMD_BOOL_72 1
#define SIMD_BOOL_73 1
#define SIMD_BOOL_74 1
#define SIMD_BOOL_75 1
#define SIMD_BOOL_76 1
#define SIMD_BOOL_77 1
#define SIMD_BOOL_78 1
#define SIMD_BOOL_79 1
#define SIMD_BOOL_80 1
#define SIMD_BOOL_81 1
#define SIMD_BOOL_82 1
#define SIMD_BOOL_83 1
#define SIMD_BOOL_84 1
#define SIMD_BOOL_85 1
#define SIMD_BOOL_86 1
#define SIMD_BOOL_87 1
#define SIMD_BOOL_88 1
#define SIMD_BOOL_89 1
#define SIMD_BOOL_90 1
#define SIMD_BOOL_91 1
#define SIMD_BOOL_92 1
#define SIMD_BOOL_93 1
#define SIMD_BOOL_94 1
#define SIMD_BOOL_95 1
#define SIMD_BOOL_96 1
#define SIMD_BOOL_97 1
#define SIMD_BOOL_98 1
#define SIMD_BOOL_99 1
#define SIMD_BOOL_100 1
#define SIMD_BOOL_101 1
#define SIMD_BOOL_102 1
#define SIMD_BOOL_103 1
#define SIMD_BOOL_104 1
#define SIMD_BOOL_105 1
#define SIMD_BOOL_106 1
#define SIMD_BOOL_107 1
#define SIMD_BOOL_108 1
#define SIMD_BOOL_109 1
#define SIMD_BOOL_110 1
#define SIMD_BOOL_111 1
#define SIMD_BOOL_112 1
#define SIMD_BOOL_113 1
#define SIMD_BOOL_114 1
#define SIMD_BOOL_115 1
#define SIMD_BOOL_116 1
#define SIMD_BOOL_117 1
#define SIMD_BOOL_118 1
#define SIMD_BOOL_119 1
#define SIMD_BOOL_120 1
#define SIMD_BOOL_121 1
#define SIMD_BOOL_122 1
#define SIMD_BOOL_123 1
#define SIMD_BOOL_124 1
#define SIMD_BOOL_125 1
#define SIMD_BOOL_126 1
#define SIMD_BOOL_127 1
#define SIMD_BOOL_128 1
#define SIMD_BOOL_129 1
#define SIMD_BOOL_130 1
#define SIMD_BOOL_131 1
#define SIMD_BOOL_132 1
#define SIMD_BOOL_133 1
#define SIMD_BOOL_134 1
#define SIMD_BOOL_135 1
#define SIMD_BOOL_136 1
#define SIMD_BOOL_137 1
#define SIMD_BOOL_138 1
#define SIMD_BOOL_139 1
#define SIMD_BOOL_140 1
#define SIMD_BOOL_141 1
#define SIMD_BOOL_142 1
#define SIMD_BOOL_143 1
#define SIMD_BOOL_144 1
#define SIMD_BOOL_145 1
#define SIMD_BOOL_146 1
#define SIMD_BOOL_147 1
#define SIMD_BOOL_148 1
#define SIMD_BOOL_149 1
#define SIMD_BOOL_150 1
#define SIMD_BOOL_151 1
#define SIMD_BOOL_152 1
#define SIMD_BOOL_153 1
#define SIMD_BOOL_154 1
#define SIMD_BOOL_155 1
#define SIMD_BOOL_156 1
#define SIMD_BOOL_157 1
#define SIMD_BOOL_158 1
#define SIMD_BOOL_159 1
#define SIMD_BOOL_160 1
#define SIMD_BOOL_161 1
#define SIMD_BOOL_162 1
#define SIMD_BOOL_163 1
#define SIMD_BOOL_164 1
#define SIMD_BOOL_165 1
#define SIMD_BOOL_166 1
#define SIMD_BOOL_167 1
#define SIMD_BOOL_168 1
#define SIMD_BOOL_169 1
#define SIMD_BOOL_170 1
#define SIMD_BOOL_171 1
#define SIMD_BOOL_172 1
#define SIMD_BOOL_173 1
#define SIMD_BOOL_174 1
#define SIMD_BOOL_175 1
#define SIMD_BOOL_176 1
#define SIMD_BOOL_177 1
#define SIMD_BOOL_178 1
#define SIMD_BOOL_179 1
#define SIMD_BOOL_180 1
#define SIMD_BOOL_181 1
#define SIMD_BOOL_182 1
#define SIMD_BOOL_183 1
#define SIMD_BOOL_184 1
#define SIMD_BOOL_185 1
#define SIMD_BOOL_186 1
#define SIMD_BOOL_187 1
#define SIMD_BOOL_188 1
#define SIMD_BOOL_189 1
#define SIMD_BOOL_190 1
#define SIMD_BOOL_191 1
#define SIMD_BOOL_192 1
#define SIMD_BOOL_193 1
#define SIMD_BOOL_194 1
#define SIMD_BOOL_195 1
#define SIMD_BOOL_196 1
#define SIMD_BOOL_197 1
#define SIMD_BOOL_198 1
#define SIMD_BOOL_199 1
#define SIMD_BOOL_200 1
#define SIMD_BOOL_201 1
#define SIMD_BOOL_202 1
#define SIMD_BOOL_203 1
#define SIMD_BOOL_204 1
#define SIMD_BOOL_205 1
#define SIMD_BOOL_206 1
#define SIMD_BOOL_207 1
#define SIMD_BOOL_208 1
#define SIMD_BOOL_209 1
#define SIMD_BOOL_210 1
#define SIMD_BOOL_211 1
#define SIMD_BOOL_212 1
#define SIMD_BOOL_213 1
#define SIMD_BOOL_214 1
#define SIMD_BOOL_215 1
#define SIMD_BOOL_216 1
#define SIMD_BOOL_217 1
#define SIMD_BOOL_218 1
#define SIMD_BOOL_219 1
#define SIMD_BOOL_220 1
#define SIMD_BOOL_221 1
#define SIMD_BOOL_222 1
#define SIMD_BOOL_223 1
#define SIMD_BOOL_224 1
#define SIMD_BOOL_225 1
#define SIMD_BOOL_226 1
#define SIMD_BOOL_227 1
#define SIMD_BOOL_228 1
#define SIMD_BOOL_229 1
#define SIMD_BOOL_230 1
#define SIMD_BOOL_231 1
#define SIMD_BOOL_232 1
#define SIMD_BOOL_233 1
#define SIMD_BOOL_234 1
#define SIMD_BOOL_235 1
#define SIMD_BOOL_236 1
#define SIMD_BOOL_237 1
#define SIMD_BOOL_238 1
#define SIMD_BOOL_239 1
#define SIMD_BOOL_240 1
#define SIMD_BOOL_241 1
#define SIMD_BOOL_242 1
#define SIMD_BOOL_243 1
#define SIMD_BOOL_244 1
#define SIMD_BOOL_245 1
#define SIMD_BOOL_246 1
#define SIMD_BOOL_247 1
#define SIMD_BOOL_248 1
#define SIMD_BOOL_249 1
#define SIMD_BOOL_250 1
#define SIMD_BOOL_251 1
#define SIMD_BOOL_252 1
#define SIMD_BOOL_253 1
#define SIMD_BOOL_254 1
#define SIMD_BOOL_255 1
#define SIMD_BOOL_256 1
#
#endif
