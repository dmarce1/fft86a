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

template<class T, int N>
void butterfly(double* X, double* Y, int stride) {
	constexpr int M = (N - 1) >> 1;
	constexpr cos_twiddle_array<N> C;
	constexpr sin_twiddle_array<N> S;
	std::array<T, N> x;
	std::array<T, N> y;
	std::array<T, N> ap;
	std::array<T, N> am;
	std::array<T, N> bp;
	std::array<T, N> bm;
	for (int n = 0; n < N; n++) {
		x[n].load(X + stride * n);
		y[n].load(Y + stride * n);
	}
	for (int n = 1; n <= M; n++) {
		const T tmpx = x[n];
		const T tmpy = y[n];
		x[n] = x[n] + x[N - n];
		y[n] = y[n] + y[N - n];
		x[N - n] = x[N - n] - tmpx;
		y[N - n] = y[N - n] - tmpy;
	}
	ap[0] = x[0];
	bp[0] = y[0];
	am[0] = bm[0] = 0.0;
	for (int j = 1; j <= M; j++) {
		ap[0] += x[j];
		bp[0] += y[j];
	}
	for (int k = 1; k < N; k++) {
		ap[k] = x[0];
		bp[k] = y[0];
		am[k] = bm[k] = 0.0;
		for (int j = 1; j <= M; j++) {
			const int l = j * k;
			ap[k] += x[j] * C.W[l];
			bp[k] += y[j] * C.W[l];
			am[k] += y[N - j] * S.W[l];
			bm[k] += x[N - j] * S.W[l];
		}
	}
	x[0] = ap[0];
	y[0] = bp[0];
	for (int k = 1; k <= M; k++) {
		x[k] = ap[k] - am[k];
		y[k] = bp[k] + bm[k];
		x[N - k] = ap[k] + am[k];
		y[N - k] = bp[k] - bm[k];
	}
	for (int n = 0; n < N; n++) {
		x[n].store(X + stride * n);
		y[n].store(Y + stride * n);
	}
}

template<int N>
void butterfly(double* X, double* Y, int stride) {
	constexpr int M = (N - 1) >> 1;
	constexpr cos_twiddle_array<N> C;
	constexpr sin_twiddle_array<N> S;
	std::array<double, N> x;
	std::array<double, N> y;
	std::array<double, N> ap;
	std::array<double, N> am;
	std::array<double, N> bp;
	std::array<double, N> bm;
	for (int n = 0; n < N; n++) {
		x[n] = *(X + stride * n);
		y[n] = *(Y + stride * n);
	}
	for (int n = 1; n <= M; n++) {
		const double tmpx = x[n];
		const double tmpy = y[n];
		x[n] = x[n] + x[N - n];
		y[n] = y[n] + y[N - n];
		x[N - n] = x[N - n] - tmpx;
		y[N - n] = y[N - n] - tmpy;
	}
	for (int k = 0; k < N; k++) {
		ap[k] = x[0];
		bp[k] = y[0];
		am[k] = bm[k] = 0.0;
		for (int j = 1; j <= M; j++) {
			const int l = (j * k) % N;
			ap[k] += x[j] * C.W[l];
			bp[k] += y[j] * C.W[l];
			am[k] += y[N - j] * S.W[l];
			bm[k] += x[N - j] * S.W[l];
		}
	}
	x[0] = ap[0];
	y[0] = bp[0];
	for (int k = 1; k <= M; k++) {
		x[k] = ap[k] - am[k];
		y[k] = bp[k] + bm[k];
		x[N - k] = ap[k] + am[k];
		y[N - k] = bp[k] - bm[k];
	}
	for (int n = 0; n < N; n++) {
		*(X + stride * n) = x[n];
		*(Y + stride * n) = y[n];
	}
}

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
}

#endif /* FFT_HPP_ */
