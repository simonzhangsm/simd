#include "test.h"
#include <bigmath/simd/simd.h>
#include <iostream>
#include <bigmath/simd/dispatch/get_arch_gcc_builtin_cpu_supports.h>
#include <bigmath/simd/dispatch/get_arch_raw_cpuid.h>
#include <bigmath/simd/dispatch/get_arch_linux_cpuinfo.h>

#if SIMD_HAS_GET_ARCH_RAW_CPUID
#define SIMD_USER_ARCH_INFO ::simd::get_arch_raw_cpuid()
#elif SIMD_HAS_GET_ARCH_GCC_BUILTIN_CPU_SUPPORTS
#define SIMD_USER_ARCH_INFO ::simd::get_arch_gcc_builtin_cpu_supports()
#elif SIMD_HAS_GET_ARCH_LINUX_CPUINFO
#define SIMD_USER_ARCH_INFO ::simd::get_arch_linux_cpuinfo()
#else
#error "Unsupported platform"
#endif

namespace SIMD_ARCH_NAMESPACE {

void print_arch()
{
	std::cout << static_cast<unsigned>(simd::this_compile_arch()) << '\n';
}

} // namespace SIMD_ARCH_NAMESPACE

SIMD_MAKE_DISPATCHER_VOID0(print_arch);
