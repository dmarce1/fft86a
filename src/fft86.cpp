//============================================================================
// Name        : fft86.cpp
// Author      : Dominic Marcello
// Version     :
// Copyright   : Copyright 2023
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <fft86/factors.hpp>
#include <fft86/fftw.hpp>
#include <fft86/fft.hpp>
#include <fft86/util.hpp>
#include <fft86/defs.hpp>

#include <algorithm>
#include <complex>
#include <vector>
#include <numeric>
#include <cstdlib>
#include <cstdio>

#define NTRIAL 100
double test(int N) {
	double err, t0 = 0, t1 = 0;
	for (int n = 0; n < NTRIAL + 1; n++) {
		std::vector<std::complex<double>> Z1(N), Z2(N);
		for (int n = 0; n < N; n++) {
			Z1[n] = Z2[n] = std::complex<double>(rand1(), rand1());
		}
		Z1[2] = Z2[2] = 1.0;
		t0 += fftw(Z2.data(), N);
		t1 += fft_1d(Z1.data(), N);
		if (n == 0) {
			t1 = t0 = 0.0;
		}
		err = 0.0;
		auto facts = factorize(N);
		std::reverse(facts.begin(), facts.end());
		digits I(facts);
		for (int n = 0; n < N; n++) {
			//Z2[n].real(I.to_int_reverse());
			//++I;
			//Z2[n].imag(I.to_int_reverse());
			err += std::abs(Z1[n] - Z2[n]);
		//	printf("%3i | %15e %15e  | %15e %15e  | %15e %15e |\n", n, Z1[n].real(), Z1[n].imag(), Z2[n].real(),
		//			Z2[n].imag(), Z2[n].real() - Z1[n].real(), Z2[n].imag() - Z1[n].imag());
			++I;
		}
		err /= N;
	//	abort();
	}
	printf("%20i %20e %20e %20e\n", N, err, t0, t1);
	return t1;
}

int main() {
	double tm = 0.0;
	int M = 2;
	int L = 3;
	int O = 5;
	for (int N = M * M; N <= 1024 * 1024 * 1024; N *= M) {
		tm += test(N);
		N *= L;
		tm += test(N);
		N *= O;
		tm += test(N);
	}
	printf("%e\n", tm);
	return 0;
}
