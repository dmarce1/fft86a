#include <fft86/fft.hpp>
#include <cstring>
#include <vector>

void fft_rotated(std::complex<double>* X, int R, int N) {
	std::vector<std::complex<double>> Y(N);
	int l = 0;
	for (int k = 0; k < N; k++) {
		Y[l] = 0.0;
		int m = 0;
		for (int n = 0; n < N; n++) {
			const auto W = std::polar(1.0, -2.0 * M_PI * R * n * k / N);
			Y[l] += X[m] * W;
			m += R;
			m %= N;
		}
		l += R;
		l %= N;
	}
	std::memcpy(X, Y.data(), sizeof(std::complex<double>) * N);
}

void fft_pfa(std::complex<double>* X, int N1, int N2) {
	const int N = N1 * N2;
	std::vector<std::complex<double>> Y(N);
	/*	for (int n1 = 0; n1 < N1; n1++) {
	 for (int n2 = 0; n2 < N2; n2++) {
	 Y[n1 * N2 + n2] = X[(n1 * N2 + n2 * N1) % N];
	 }
	 }*/
	for (int n1 = 0; n1 < N1; n1++) {
		fft_rotated(X + n1 * N2, N1, N2);
	}
	for (int n1 = 0; n1 < N1; n1++) {
		for (int k2 = 0; k2 < N2; k2++) {
			Y[n1 * N2 + k2] = X[n1 + k2 * N1];
		}
	}
	std::memcpy(X, Y.data(), sizeof(std::complex<double>) * N);
	for (int k2 = 0; k2 < N2; k2++) {
		fft_rotated(X + k2 * N1, N2, N1);
	}
	for (int k1 = 0; k1 < N1; k1++) {
		for (int k2 = 0; k2 < N2; k2++) {
			Y[k1 * N2 + k2] = X[k1 + k2 * N1];
		}
	}
	std::memcpy(X, Y.data(), sizeof(std::complex<double>) * N);
	/*	for (int n1 = 0; n1 < N1; n1++) {
	 for (int n2 = 0; n2 < N2; n2++) {
	 X[(n1 * N2 + n2 * N1) % N] = Y[n1 * N2 + n2];
	 }
	 }*/
}
