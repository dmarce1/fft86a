//============================================================================
// Name        : fft86.cpp
// Author      : Dominic Marcello
// Version     :
// Copyright   : Copyright 2023
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <fft86/fftw.hpp>
#include <fft86/fft.hpp>
#include <fft86/util.hpp>

#include <complex>
#include <vector>
#include <numeric>
#include <cstdlib>
#include <cstdio>

#define NTRIAL 32

double test(int N) {
	double err, t0 = 0, t1 = 0;
	for (int n = 0; n < NTRIAL + 1; n++) {
		std::vector<std::complex<double>> Z1(N), Z2(N);
		for (int n = 0; n < N; n++) {
			Z1[n] = Z2[n] = std::complex<double>(rand1(), rand1());
		}
		Z1[4] = Z2[4] = 1.0;
		t0 += fftw(Z2.data(), N);
		t1 += fft_1d_3(Z1.data(), N);
		if (n == 0) {
			t1 = t0 = 0.0;
		}
		err = 0.0;
		for (int n = 0; n < N; n++) {
			err += std::abs(Z1[n] - Z2[n]);
//			printf("%3i | %15e %15e  | %15e %15e  | %15e %15e |\n", n, Z1[n].real(), Z1[n].imag(), Z2[n].real(),
			//				Z2[n].imag(), Z2[n].real() - Z1[n].real(), Z2[n].imag() - Z1[n].imag());
		}
		err /= N;
	}
	printf("3^%i %i %e %e %e\n", lround(log(N) / log(3)), N, err, t0, t1);
//	abort();
	return t1;
}

int main() {
	double tm = 0.0;
	for (int N = 81; N <= std::pow(3,16); N *= 3) {
		tm += test(N);
		tm *= 3.0 * std::log2(N) / std::log2(N-1);
	}
	printf( "%e\n", tm);
	return 0;
}
