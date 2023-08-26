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

#define NTRIAL 101
double test(int N) {
	double err, t0 = 0, t1 = 0;
	for (int n = 0; n < NTRIAL + 1; n++) {
		std::vector<std::complex<double>> Z1(N), Z2(N);
		for (int n = 0; n < N; n++) {
			Z1[n] = Z2[n] = std::complex<double>(0,0);
		}
		Z1[1] = Z2[1] = 1.0;
		t0 += fftw(Z2.data(), N);
//		t1 += fft_1d(Z1.data(), N);
		fft_selfsort(Z1.data(), N);
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
				printf("%3i | %15e %15e  | %15e %15e  | %15e %15e |\n", n, Z1[n].real(), Z1[n].imag(), Z2[n].real(),
						Z2[n].imag(), Z2[n].real() - Z1[n].real(), Z2[n].imag() - Z1[n].imag());
			++I;
		}
		err /= N;
	abort();
	}
	printf("%20i %20e %20e %20e %20f\n", N, err, t0, t1, t0 / t1);
	return t1;
}

double test_pfa(int N1, int N2) {
	const int N = N1 * N2;
	double err, t0 = 0, t1 = 0;
	for (int n = 0; n < NTRIAL + 1; n++) {
		std::vector<std::complex<double>> Z1(N), Z2(N);
		for (int n = 0; n < N; n++) {
			Z1[n] = Z2[n] = std::complex<double>(0, 0);
		}
		Z1[1] = Z2[1] = 1.0;
		t0 += fftw(Z2.data(), N);
		fft_pfa(Z1.data(), N1, N2);
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
			printf("%3i | %15e %15e  | %15e %15e  | %15e %15e |\n", n, Z1[n].real(), Z1[n].imag(), Z2[n].real(),
					Z2[n].imag(), Z2[n].real() - Z1[n].real(), Z2[n].imag() - Z1[n].imag());
			++I;
		}
		err /= N;
		abort();
	}
	return t1;
}

void * operator new(std::size_t n) {
	void* memptr;
	posix_memalign(&memptr, 32, round_up(n, 32));
	return memptr;
}

void operator delete(void * p) {
	free(p);
}

void *operator new[](std::size_t n) {
	void* memptr;
	posix_memalign(&memptr, 32, round_up(n, 32));
	return memptr;
}

void operator delete[](void *p) {
	free(p);
}

bool usenum(int N) {
	int M = N;
	int cnt = 0;
	while (M > 1) {
		if (M % 5 == 0) {
			M /= 5;
		} else if (M % 3 == 0) {
			M /= 3;
		} else if (M % 2 == 0) {
			M /= 2;
		} else {
			return false;
		}
		cnt++;
	}
	return cnt > 1;
}

int main() {
	double tm = 0.0;
	for (int N = 5*5*2*2*3*3; N <= 1024 * 1024 * 1024; N*=2) {
			tm += test(N);

	}
	return 0;
}
