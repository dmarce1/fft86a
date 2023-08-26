#include <fft86/defs.hpp>
#include <fft86/fft.hpp>
#include <fft86/factors.hpp>
#include <fft86/scramble.hpp>
#include <fft86/twiddles.hpp>
#include <fft86/vec.hpp>
#include <fft86/timer.hpp>

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
			const auto W = std::complex(C[nk], -S[nk]);
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
void fft_selfsort(const std::vector<int>& factors, std::complex<double>* X, int N, int N2a, int level) {
	const static v4df two = v4df(2);
	const auto* Wa = get_twiddles(N2a * N1);
	const auto* Wb = get_twiddles(N);
	const int N2b = N / N1;
	const auto& P = get_permutation(std::vector<int>(2, 2));
	const int NHI = N / (N1 * N1 * N2a);
	std::array<std::array<std::complex<double>, N1>, N1> U;
	if (N2a != N2b) {
		for (int ihi = 0; ihi < NHI; ihi++) {
			int n2a = 0;
			for (int n2imid = 0; n2imid < N2a * N1; n2imid += v4df::size() >> 1) {
				const int n2 = n2imid + N2a * N1 * ihi;
				v4df u0, u1, u2, u3, w1, w2, w3;
				const int i0 = n2;
				const int i1 = i0 + N2b;
				const int i2 = i1 + N2b;
				const int i3 = i2 + N2b;
				u0.load(X + i0);
				u1.load(X + i2);
				u2.load(X + i1);
				u3.load(X + i3);
				if (N2a > 1) {
					w1.load(Wa + n2a);
					n2a += (v4df::size() >> 1);
					while (n2a >= N2a) {
						n2a -= N2a;
					}
					w2 = complex_multiply(w1, w1);
					w3 = complex_multiply(w1, w2);
					u1 = complex_multiply(u1, w2);
					u2 = complex_multiply(u2, w1);
					u3 = complex_multiply(u3, w3);
				}
				u1 = u0 - u1;
				u3 = u2 - u3;
				u0 += u0 - u1;
				u2 += u2 - u3;
				u3 = rotate90(u3);
				u2 = u0 - u2;
				u3 = u1 - u3;
				u0 += u0 - u2;
				u1 += u1 - u3;
				u0.store(X + i0);
				u1.store(X + i2);
				u2.store(X + i1);
				u3.store(X + i3);
			}
			if (N2a == 1) {
				for (int imid = 0; imid < N1; imid++) {
					for (int n1 = 0; n1 < N1; n1++) {
						const int na = imid + N1 * (ihi + NHI * n1);
						const int nb = P[n1] + N1 * (ihi + NHI * P[imid]);
						if (na > nb) {
							v2df tmpa, tmpb;
							tmpa.load(X + na);
							tmpb.load(X + nb);
							tmpa.store(X + nb);
							tmpb.store(X + na);
						}
					}
				}
			} else {
				for (int imid = 0; imid < N1; imid++) {
					for (int n1 = 0; n1 < N1; n1++) {
						const int na = N2a * (imid + N1 * (ihi + NHI * n1));
						const int nb = N2a * (P[n1] + N1 * (ihi + NHI * P[imid]));
						if (na > nb) {
							for (int n2 = 0; n2 < N2a; n2 += v4df::size() >> 1) {
								std::swap(*((v4df*) &X[na + n2]), *((v4df*) &X[nb + n2]));
							}
						}
					}
				}
			}
		}
	}
	if (NHI > 1) {
		for (int n1 = 0; n1 < N1; n1++) {
			fft_selfsort_dispatch(factors, X + n1 * N2b, N2b, N1 * N2a, level + 1);
		}
	}
	for (int k2 = 0; k2 < N2b; k2 += (v4df::size() >> 1)) {
		v4df u0, u1, u2, u3, w1, w2, w3;
		const int i0 = k2;
		const int i1 = i0 + N2b;
		const int i2 = i1 + N2b;
		const int i3 = i2 + N2b;
		if (N2a == N2b) {
			u0.load(X + i0);
			u1.load(X + i2);
			u2.load(X + i1);
			u3.load(X + i3);
		} else {
			u0.load(X + i0);
			u1.load(X + i1);
			u2.load(X + i2);
			u3.load(X + i3);
		}
		w1.load(Wb + k2);
		w2 = complex_multiply(w1, w1);
		w3 = complex_multiply(w1, w2);
		u1 = complex_multiply(u1, w2);
		u2 = complex_multiply(u2, w1);
		u3 = complex_multiply(u3, w3);
		u1 = u0 - u1;
		u3 = u2 - u3;
		u0 += u0 - u1;
		u2 += u2 - u3;
		u3 = rotate90(u3);
		u2 = u0 - u2;
		u3 = u1 - u3;
		u0 += u0 - u2;
		u1 += u1 - u3;
		u0.store(X + i0);
		u1.store(X + i1);
		u2.store(X + i2);
		u3.store(X + i3);
	}
}

double fft_selfsort(std::complex<double>* X, int N) {
	timer tm;
	tm.start();
	fft_selfsort_dispatch(std::vector<int>(std::ilogb(N) / 2, 4), X, N, 1, 0);
	tm.stop();
	return tm.read();
}
