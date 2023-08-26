/*
 * fft.hpp
 *
 *  Created on: Aug 22, 2023
 *      Author: dmarce1
 */

#ifndef FFT123_HPP_
#define FFT123_HPP_

#include <fft86/vec.hpp>
#include <fft86/twiddles.hpp>
#include <fft86/vec.hpp>
#include <fft86/util.hpp>

#include <array>

void butterfly(v4df* X, v4df* Y, int stride, int N);
void butterfly(v2df* X, v2df* Y, int stride, int N);
void butterfly(double* X, double* Y, int stride, int N);

#define SHUF     1
#define INV_SHUF 2

constexpr int bit_reverse(int j, int N) {
	int l = 0;
	for (int k = 0; k < std::ilogb(N); k++) {
		l <<= 1;
		l |= j & 1;
		j >>= 1;
	}
	return l;
}

extern "C" {
void radix4_dit(double* X, size_t s, const double* Wr, const double* Wi, size_t sf);
void radix4_dif(double* X, size_t s, const double* Wr, const double* Wi, size_t sf);
void radix2_dit(double* X, size_t s, const double* Wr, const double* Wi, size_t sf);
void radix2_dif(double* X, size_t s, const double* Wr, const double* Wi, size_t sf);
}

template<class T, int N>
inline void radix2_dit(double* X, int s, const T* Wr, const T* Wi, int sf) {
	constexpr cos_twiddle_array<N> C;
	constexpr sin_twiddle_array<N> S;
	std::array<T, N> x, y;
	T tmp;
	x[0].load(X);
	y[0].load(X + T::size());
	if (sf & INV_SHUF) {
		inv_perf_shuf(x[0], y[0]);
	}
	for (int n = 1; n < N; n++) {
		x[n].load(X + s * n);
		y[n].load(X + T::size() + s * n);
		if (sf & INV_SHUF) {
			inv_perf_shuf(x[n], y[n]);
		}
		tmp = x[n];
		const int n1 = bit_reverse(n, N);
		x[n] = tmp * Wr[n1] - y[n] * Wi[n1];
		y[n] = tmp * Wi[n1] + y[n] * Wr[n1];
	}
	constexpr int N1 = 2;
	constexpr int logN = std::ilogb(N);
	const T two = T(2);
	for (int logN2 = 0; logN2 < logN; logN2++) {
		const int N2 = 1 << logN2;
		const int NHI = 1 << (logN - logN2 - 1);
		for (int k2 = 0; k2 < N2; k2++) {
			const T wr = C[NHI * k2];
			const T wi = S[NHI * k2];
			for (int ihi = 0; ihi < NHI; ihi++) {
				const int i0 = ihi * N1 * N2 + k2;
				const int i1 = i0 + N2;
				T er0 = x[i0];
				T er1 = x[i1];
				T ei0 = y[i0];
				T ei1 = y[i1];
				const T tr1 = er1;
				er1 = er0 - tr1 * wr - ei1 * wi;
				ei1 = ei0 - ei1 * wr + tr1 * wi;
				x[i0] = two * er0 - er1;
				y[i0] = two * ei0 - ei1;
				x[i1] = er1;
				y[i1] = ei1;
			}
		}
	}
	for (int n = 0; n < N; n++) {
		if (sf & SHUF) {
			perf_shuf(x[n], y[n]);
		}
		x[n].store(X + s * n);
		y[n].store(X + T::size() + s * n);
	}
}
#define INV_SHUF 2

template<class T, int N>
inline void radix2_dif(double* X, int s, const T* Wr, const T* Wi, int sf) {
	constexpr cos_twiddle_array<N> C;
	constexpr sin_twiddle_array<N> S;
	std::array<T, N> x, y;
	T tmp;
	x[0].load(X);
	y[0].load(X + T::size());
	if (sf & INV_SHUF) {
		inv_perf_shuf(x[0], y[0]);
	}
	for (int n = 1; n < N; n++) {
		x[n].load(X + s * n);
		y[n].load(X + T::size() + s * n);
		if (sf & INV_SHUF) {
			inv_perf_shuf(x[n], y[n]);
		}
	}
	constexpr int N1 = 2;
	constexpr int logN = std::ilogb(N);
	for (int logN2 = logN - 1; logN2 >= 0; logN2--) {
		const int N2 = 1 << logN2;
		const int NHI = 1 << (logN - logN2 - 1);
		for (int k2 = 0; k2 < N2; k2++) {
			const T wr = C[NHI * k2];
			const T wi = S[NHI * k2];
			for (int ihi = 0; ihi < NHI; ihi++) {
				const int i0 = ihi * N1 * N2 + k2;
				const int i1 = i0 + N2;
				T er0 = x[i0];
				T er1 = x[i1];
				T ei0 = y[i0];
				T ei1 = y[i1];
				const T tr0 = er0;
				const T ti0 = ei0;
				er0 += er1;
				ei0 += ei1;
				er1 = tr0 - er1;
				ei1 = ti0 - ei1;
				x[i0] = er0;
				y[i0] = ei0;
				x[i1] = er1 * wr + ei1 * wi;
				y[i1] = ei1 * wr - er1 * wi;
			}
		}
	}
	if (sf & SHUF) {
		perf_shuf(x[0], y[0]);
	}
	x[0].store(X);
	y[0].store(X + T::size());
	for (int n = 1; n < N; n++) {
		tmp = x[n];
		const int n1 = bit_reverse(n, N);
		x[n] = tmp * Wr[n1] - y[n] * Wi[n1];
		y[n] = tmp * Wi[n1] + y[n] * Wr[n1];
		if (sf & SHUF) {
			perf_shuf(x[n], y[n]);
		}
		x[n].store(X + s * n);
		y[n].store(X + T::size() + s * n);
	}
}

template<class T, int N1>
inline void singleton_dit(double* X, int s, const T* Wr, const T* Wi, int sf) {
	constexpr int M = (N1 - 1) >> 1;
	constexpr cos_twiddle_array<N1> C;
	constexpr sin_twiddle_array<N1> S;
	std::array<T, N1> x, y, ap, am, bp, bm;
	T tmp;
	x[0].load(X);
	y[0].load(X + T::size());
	if (sf & INV_SHUF) {
		inv_perf_shuf(x[0], y[0]);
	}
	for (int n = 1; n < N1; n++) {
		x[n].load(X + s * n);
		y[n].load(X + T::size() + s * n);
		if (sf & INV_SHUF) {
			inv_perf_shuf(x[n], y[n]);
		}
		tmp = x[n];
		x[n] = tmp * Wr[n] - y[n] * Wi[n];
		y[n] = tmp * Wi[n] + y[n] * Wr[n];
	}
	for (int n = 1; n <= M; n++) {
		const T tmpx = x[n];
		const T tmpy = y[n];
		x[n] = x[n] + x[N1 - n];
		y[n] = y[n] + y[N1 - n];
		x[N1 - n] -= tmpx;
		y[N1 - n] -= tmpy;
	}
	ap[0] = x[0];
	bp[0] = y[0];
	for (int j = 1; j <= M; j++) {
		ap[0] += x[j];
		bp[0] += y[j];
	}
	for (int k = 1; k < N1; k++) {
		ap[k] = x[0];
		bp[k] = y[0];
		am[k] = bm[k] = 0.0;
		for (int j = 1; j <= M; j++) {
			const int l = (j * k) % N1;
			ap[k] += x[j] * C[l];
			bp[k] += y[j] * C[l];
			am[k] += y[N1 - j] * S[l];
			bm[k] += x[N1 - j] * S[l];
		}
	}
	x[0] = ap[0];
	y[0] = bp[0];
	for (int k = 1; k <= M; k++) {
		x[k] = ap[k] - am[k];
		y[k] = bp[k] + bm[k];
		x[N1 - k] = ap[k] + am[k];
		y[N1 - k] = bp[k] - bm[k];
	}
	for (int n = 0; n < N1; n++) {
		if (sf & SHUF) {
			perf_shuf(x[n], y[n]);
		}
		x[n].store(X + s * n);
		y[n].store(X + T::size() + s * n);
	}
}

template<class T, int N1>
inline void singleton_dif(double* X, int s, const T* Wr, const T* Wi, int sf) {
	constexpr int M = (N1 - 1) >> 1;
	constexpr cos_twiddle_array<N1> C;
	constexpr sin_twiddle_array<N1> S;
	std::array<T, N1> x, y, ap, am, bp, bm;
	T tmp;
	x[0].load(X);
	y[0].load(X + T::size());
	if (sf & INV_SHUF) {
		inv_perf_shuf(x[0], y[0]);
	}
	for (int n = 1; n < N1; n++) {
		x[n].load(X + s * n);
		y[n].load(X + T::size() + s * n);
		if (sf & INV_SHUF) {
			inv_perf_shuf(x[n], y[n]);
		}
	}
	for (int n = 1; n <= M; n++) {
		const T tmpx = x[n];
		const T tmpy = y[n];
		x[n] = x[n] + x[N1 - n];
		y[n] = y[n] + y[N1 - n];
		x[N1 - n] -= tmpx;
		y[N1 - n] -= tmpy;
	}
	ap[0] = x[0];
	bp[0] = y[0];
	for (int j = 1; j <= M; j++) {
		ap[0] += x[j];
		bp[0] += y[j];
	}
	for (int k = 1; k < N1; k++) {
		ap[k] = x[0];
		bp[k] = y[0];
		am[k] = bm[k] = 0.0;
		for (int j = 1; j <= M; j++) {
			const int l = (j * k) % N1;
			ap[k] += x[j] * C[l];
			bp[k] += y[j] * C[l];
			am[k] += y[N1 - j] * S[l];
			bm[k] += x[N1 - j] * S[l];
		}
	}
	x[0] = ap[0];
	y[0] = bp[0];
	for (int k = 1; k <= M; k++) {
		x[k] = ap[k] - am[k];
		y[k] = bp[k] + bm[k];
		x[N1 - k] = ap[k] + am[k];
		y[N1 - k] = bp[k] - bm[k];
	}
	if (sf & SHUF) {
		perf_shuf(x[0], y[0]);
	}
	x[0].store(X);
	y[0].store(X + T::size());
	for (int n = 1; n < N1; n++) {
		tmp = x[n];
		x[n] = tmp * Wr[n] - y[n] * Wi[n];
		y[n] = tmp * Wi[n] + y[n] * Wr[n];
		if (sf & SHUF) {
			perf_shuf(x[n], y[n]);
		}
		x[n].store(X + s * n);
		y[n].store(X + T::size() + s * n);
	}
}

template<class T, int N1>
inline void butterfly_dit(double* X, int s, const T* Wr, const T* Wi, int sf) {
if constexpr(N1 % 2 == 0) {
	radix2_dit<T, N1>(X, s, Wr, Wi, sf);
} else if constexpr(N1 == 3 || N1 == 5 || N1 == 7 || N1 == 11 || N1 == 13) {
	singleton_dit<T, N1>(X, s, Wr, Wi, sf);
}
}

template<class T, int N1>
inline void butterfly_dif(double* X, int s, const T* Wr, const T* Wi, int sf) {
if (N1 % 2 == 0) {
	radix2_dif<T, N1>(X, s, Wr, Wi, sf);
} else if (N1 == 3 || N1 == 5 || N1 == 7 || N1 == 11 || N1 == 13) {
	singleton_dif<T, N1>(X, s, Wr, Wi, sf);
}
}

#endif /* FFT_HPP_ */
