CXXFLAGS = -std=c++11 -I../../

test: main.o test_null.o test_sse2.o test_sse3.o test_sse4_1.o test_sse4_2.o test_avx.o test_avx2.o
	g++ $^ -o test

main.o: main.cc
	g++ main.cc $(CXXFLAGS) -c -o main.o

# Uncomment this if you want to check the non-vectorized variant.
test_null.o: test.cc
	g++ test.cc -c $(CXXFLAGS) -o test_null.o

test_sse2.o: test.cc
	g++ test.cc -c $(CXXFLAGS) -DSIMD_ARCH_X86_SSE2 -msse2 \
        -DSIMD_EMIT_DISPATCHER=1 \
        -DSIMD_DISPATCH_ARCH0=SIMD_ARCH_NONE_NULL \
        -DSIMD_DISPATCH_ARCH1=SIMD_ARCH_X86_SSE2 \
        -DSIMD_DISPATCH_ARCH2=SIMD_ARCH_X86_SSE3 \
        -DSIMD_DISPATCH_ARCH3=SIMD_ARCH_X86_SSE4_1 \
        -DSIMD_DISPATCH_ARCH4=SIMD_ARCH_X86_SSE4_2 \
        -DSIMD_DISPATCH_ARCH5=SIMD_ARCH_X86_AVX \
        -DSIMD_DISPATCH_ARCH6=SIMD_ARCH_X86_AVX2 \
        -o test_sse2.o

test_sse3.o: test.cc
	g++ test.cc -c $(CXXFLAGS) -DSIMD_ARCH_X86_SSE3 -msse3 -o test_sse3.o

test_sse4_1.o: test.cc
	g++ test.cc -c $(CXXFLAGS) -DSIMD_ARCH_X86_SSE4_1 -msse4.1 -o test_sse4_1.o

test_sse4_2.o: test.cc
	g++ test.cc -c $(CXXFLAGS) -DSIMD_ARCH_X86_SSE4_2 -msse4.2 -o test_sse4_2.o

test_avx.o: test.cc
	g++ test.cc -c $(CXXFLAGS) -DSIMD_ARCH_X86_AVX -mavx -o test_avx.o

test_avx2.o: test.cc
	g++ test.cc -c $(CXXFLAGS) -DSIMD_ARCH_X86_AVX2 -mavx2 -o test_avx2.o
	
clean:
	rm -f *.o test

