#include <fft86/fft.hpp>
#include <fft86/twiddles.hpp>
#include <fft86/vec.hpp>

#include <array>
#include <cassert>
#include <cstring>
#include <complex>
#include <vector>

//k + NLO * (b0 + N1 * (i + b1 * NMID));

template<int N>
void fft_small(std::complex<double>* X, int s) {
	std::array<std::complex<double>, N> Y;
	static constexpr cos_twiddle_array<N> C;
	static constexpr sin_twiddle_array<N> S;
	Y[0] = X[0];
	for (int n = 1; n < N; n++) {
		Y[0] += X[s * n];
	}
	for (int k = 1; k < N; k++) {
		Y[k] = X[0];
		for (int n = 1; n < N; n++) {
			const int nk = (n * k) % N;
			const auto W = std::complex(C[nk], S[nk]);
			Y[k] += X[s * n] * W;
		}
	}
	for (int k = 0; k < N; k++) {
		X[s * k] = Y[k];
	}
}

template<int N1>
void fft_selfsort(const std::vector<int>& factors, std::complex<double>* X, int N, int NLO, int level);

void fft_selfsort_dispatch(const std::vector<int>& factors, std::complex<double>* X, int N, int NLO, int level) {
	const int N1 = factors[level];
	switch (N1) {
	case 2:
		return fft_selfsort<2>(factors, X, N, NLO, level);
	case 3:
		return fft_selfsort<3>(factors, X, N, NLO, level);
	case 4:
		return fft_selfsort<4>(factors, X, N, NLO, level);
	case 5:
		return fft_selfsort<5>(factors, X, N, NLO, level);
	}
}

template<int N1>
void fft_selfsort(const std::vector<int>& factors, std::complex<double>* X, int N, int NLO, int level) {
	const auto& Wr0 = get_cos_twiddles(NLO * N1);
	const auto& Wi0 = get_sin_twiddles(NLO * N1);
	const auto& Wr1 = get_cos_twiddles(N);
	const auto& Wi1 = get_sin_twiddles(N);
	const int N2 = N / N1;
	const int NMID = N / (N1 * N1 * NLO);
	for (int nmid = 0; nmid < NMID; nmid++) {
		for (int n2 = 0; n2 < NLO; n2++) {
			for (int n0 = 0; n0 < N1; n0++) {
				const int nn = n2 + NLO * (n0 + N1 * nmid);
				for (int n1 = 1; n1 < N1; n1++) {
					X[nn + n1 * N2] *= std::complex<double>(Wr0[n1 * n2], Wi0[n1 * n2]);
				}
				fft_small<N1>(X + nn, N2);
			}
		}
	}
	for (int i = 0; i < NMID; i++) {
		for (int j = 0; j < NLO; j++) {
			for (int n = 0; n < N1; n++) {
				for (int m = n + 1; m < N1; m++) {
					const int p = j + NLO * (n + N1 * (i + NMID * m));
					const int q = j + NLO * (m + N1 * (i + NMID * n));
					std::swap(X[p], X[q]);
				}
			}
		}
	}
	if (NMID > 1) {
		for (int n1 = 0; n1 < N1; n1++) {
			fft_selfsort_dispatch(factors, X + n1 * N2, N2, N1 * NLO, level + 1);
		}
	}
	for (int k2 = 0; k2 < N2; k2++) {
		for (int n1 = 1; n1 < N1; n1++) {
			X[k2 + n1 * N2] *= std::complex<double>(Wr1[n1 * k2], Wi1[n1 * k2]);
		}
		fft_small<N1>(X + k2, N2);
	}
}
