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

#ifndef SIMD_CONFIG_H_
#define SIMD_CONFIG_H_

#ifndef CORPORATION_NAMESPACE
#define CORPORATION_NAMESPACE bigmath
#endif

#if defined(_MSC_VER)
#define FORCEINLINE __forceinline
#elif defined(__GNUC__) || defined(__INTEL_COMPILER)
// Intel compiler also implies __GNUC__ flag. For that reason we have to check it first.
#define FORCEINLINE __attribute__((__always_inline__)) inline
#else
// Default fallback: if the compiler is unrecognized, simply try to ask it to inline.
#define FORCEINLINE inline
#endif

#if defined(__GNUC__)
#define SIMDALIGN(X) __attribute__((__aligned__(X)))
#elif defined(_MSC_VER)
#define SIMDALIGN(X) __declspec(align(X))
#else
#define SIMDALIGN(X) alignas(x)
#endif

// Define target specific attributes
#ifdef __NVCC__
#ifdef __CUDA_ARCH__
// For CUDA we need to mark each function as device code.
#define ENV_FUNC_ATTRIB __device__
#else
#define ENV_FUNC_ATTRIB __host__
#endif
#else
#define ENV_FUNC_ATTRIB
#endif

#define FUNC_ATTRIB inline ENV_FUNC_ATTRIB

#endif /* SIMD_CONFIG_H_ */
