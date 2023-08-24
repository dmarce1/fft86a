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

#include <array>

void butterfly(v4df* X, v4df* Y, int stride, int N);
void butterfly(v2df* X, v2df* Y, int stride, int N);
void butterfly(double* X, double* Y, int stride, int N);

#define SHUF     1
#define INV_SHUF 2

template<class T, int N1>
void butterfly_dit(double* X, int s, const T* Wr, const T* Wi, int sf) {
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
			const int l = j * k;
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
void butterfly_dif(double* X, int s, const T* Wr, const T* Wi, int sf) {
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
			const int l = j * k;
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
		if (sf & SHUF) {
			perf_shuf(x[n], y[n]);
		}
		tmp = x[n];
		x[n] = tmp * Wr[n] - y[n] * Wi[n];
		y[n] = tmp * Wi[n] + y[n] * Wr[n];
		x[n].store(X + s * n);
		y[n].store(X + T::size() + s * n);
	}
}

/*
 template<class T, int N1>
 void butterfly(double* X, double* Y, int stride, const double* wr, const double* wi, int k2, int N2) {
 std::array<T, N1> x;
 std::array<T, N1> y;
 std::array<T, N1> a;
 std::array<T, N1> b;
 for (int n = 0; n < N1; n++) {
 x[n].load(X + stride * n);
 y[n].load(Y + stride * n);
 }
 for (int k1 = 0; k1 < N1; k1++) {
 a[k1] = x[0];
 b[k1] = y[0];
 for (int n1 = 1; n1 < N1; n1++) {
 const int l = (N2 * k1 + k2) * n1;
 a[k1] += x[n1] * wr[l];
 a[k1] -= y[n1] * wi[l];
 b[k1] += y[n1] * wr[l];
 b[k1] += x[n1] * wi[l];
 }
 }
 for (int n = 0; n < N1; n++) {
 a[n].store(X + stride * n);
 b[n].store(Y + stride * n);
 }
 }*/

#endif /* FFT_HPP_ */
