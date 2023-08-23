#include <fft86/butterfly.hpp>
#include <fft86/scramble.hpp>
#include <fft86/timer.hpp>
#include <fft86/twiddles.hpp>
#include <fft86/util.hpp>
#include <fft86/vec.hpp>

#include <complex>
#include <cstring>
#include <vector>

void inv_perf_shuf(double* Z, int N) {
	static thread_local std::vector<double> tmp;
	double* X = Z;
	double* Y = Z + N;
	tmp.resize(2 * N);
	std::memcpy(tmp.data(), Z, 2 * N * sizeof(double));
	const int end4 = round_down(N, v4df::size());
	const int end2 = round_down(N, v2df::size());
	const int& end = N;
	for (int n = 0; n < end4; n += v4df::size()) {
		v4df x, y;
		x.load(tmp.data() + 2 * n);
		y.load(tmp.data() + 2 * n + v4df::size());
		inv_perf_shuf(x, y);
		x.store(X + n);
		y.store(Y + n);
	}
	if (end2 > end4) {
		v2df x, y;
		const int& n = end4;
		x.load(tmp.data() + 2 * n);
		y.load(tmp.data() + 2 * n + v2df::size());
		inv_perf_shuf(x, y);
		x.store(X + n);
		y.store(Y + n);
	}
	if (end > end4 && end != end2) {
		const int& n = end2;
		X[n] = tmp[2 * n];
		Y[n] = tmp[2 * n + 1];
	}
}

void perf_shuf(double* X, int N) {
	static thread_local std::vector<double> tmpx;
	static thread_local std::vector<double> tmpy;
	double* Z = X;
	double* Y = X + N;
	tmpx.resize(N);
	tmpy.resize(N);
	std::memcpy(tmpx.data(), X, N * sizeof(double));
	std::memcpy(tmpy.data(), Y, N * sizeof(double));
	const int end4 = round_down(N, v4df::size());
	const int end2 = round_down(N, v2df::size());
	const int& end0 = N;
	for (int n = 0; n < end4; n += v4df::size()) {
		v4df x, y;
		x.load(tmpx.data() + n);
		y.load(tmpy.data() + n);
		perf_shuf(x, y);
		x.store(X + 2 * n);
		y.store(X + 2 * n + v4df::size());
	}
	if (end2 > end4) {
		v2df x, y;
		const int& n = end4;
		x.load(tmpx.data() + n);
		y.load(tmpy.data() + n);
		perf_shuf(x, y);
		x.store(X + 2 * n);
		y.store(X + 2 * n + v2df::size());
	}
	if (end0 > end4 && end0 != end2) {
		const int& n = end2;
		X[2 * n] = tmpx[n];
		X[2 * n + 1] = tmpy[n];
	}
}
/*
 template<int N1>
 void fft_1d_batch(double* Z, int N, int NLO) {
 static thread_local std::vector<double> wr;
 static thread_local std::vector<double> wi;
 wr.resize(N1);
 wi.resize(N1);
 int N2 = 1;
 int NHI = N / N2 / N1;
 while (N2 < N) {
 const double* Wr = get_cos_twiddles(N1 * N2);
 const double* Wi = get_sin_twiddles(N1 * N2);
 const int s = 2 * NLO * N2;
 const int NLO4 = round_down(NLO, v4df::size());
 const int NLO2 = round_down(NLO, v2df::size());
 const int& NLO1 = NLO;
 for (int ihi = 0; ihi < NHI; ihi++) {
 for (int k2 = 0; k2 < N2; k2++) {
 for (int n1 = 1; n1 < N1; n1++) {
 wr[n1] = Wr[k2 * n1];
 wi[n1] = Wi[k2 * n1];
 }
 for (int ilo = 0; ilo < NLO4; ilo += v4df::size()) {
 const int iii = (ilo + 2 * NLO * (k2 + N2 * (0 + N1 * ihi)));
 double* X = Z + iii;
 double* Y = X + NLO;
 for (int n1 = 1; n1 < N1; n1++) {
 const int sn1 = s * n1;
 v4df x, y, tmp;
 x.load(X + sn1);
 y.load(Y + sn1);
 tmp = x;
 x = v4df(wr[n1]) * tmp - v4df(wi[n1]) * y;
 y = v4df(wi[n1]) * tmp + v4df(wr[n1]) * y;
 x.store(X + sn1);
 y.store(Y + sn1);
 }
 butterfly<v4df, N1>(X, Y, s);
 }
 if (NLO2 > NLO4) {
 const int& ilo = NLO4;
 const int iii = (ilo + 2 * NLO * (k2 + N2 * (0 + N1 * ihi)));
 double* X = Z + iii;
 double* Y = X + NLO;
 for (int n1 = 1; n1 < N1; n1++) {
 const int sn1 = s * n1;
 v2df x, y, tmp;
 x.load(X + sn1);
 y.load(Y + sn1);
 tmp = x;
 x = v2df(wr[n1]) * tmp - v2df(wi[n1]) * y;
 y = v2df(wi[n1]) * tmp + v2df(wr[n1]) * y;
 x.store(X + sn1);
 y.store(Y + sn1);
 }
 butterfly<v2df, N1>(X, Y, s);
 }
 if (NLO1 > NLO4 && NLO1 != NLO2) {
 const int& ilo = NLO2;
 const int iii = (ilo + 2 * NLO * (k2 + N2 * (0 + N1 * ihi)));
 double* X = Z + iii;
 double* Y = X + NLO;
 for (int n1 = 1; n1 < N1; n1++) {
 const int sn1 = s * n1;
 double x, y, tmp;
 x = *(X + sn1);
 y = *(Y + sn1);
 tmp = x;
 x = wr[n1] * tmp - wi[n1] * y;
 y = wi[n1] * tmp + wr[n1] * y;
 *(X + sn1) = x;
 *(Y + sn1) = y;
 }
 butterfly<N1>(X, Y, s);
 }
 }
 }
 N2 *= N1;
 NHI /= N1;
 }
 }*/

template<int N1>
void fft_1d_batch(double* Z, int N, int NLO) {
	const int N2 = N / N1;
	static thread_local std::vector<double> wr;
	static thread_local std::vector<double> wi;
	if (N2 > 1) {
		for (int n1 = 0; n1 < N1; n1++) {
			fft_1d_batch<N1>(Z + 2 * n1 * NLO * N2, N2, NLO);
		}
	}
	const int s = 2 * NLO * N2;
	const int NLO4 = round_down(NLO, v4df::size());
	const int NLO2 = round_down(NLO, v2df::size());
	const int& NLO1 = NLO;
	const double* Wr = get_cos_twiddles(N1 * N2);
	const double* Wi = get_sin_twiddles(N1 * N2);
	wr.resize(N1);
	wi.resize(N1);
	for (int k2 = 0; k2 < N2; k2++) {
		for (int n1 = 1; n1 < N1; n1++) {
			wr[n1] = Wr[k2 * n1];
			wi[n1] = Wi[k2 * n1];
		}
		for (int ilo = 0; ilo < NLO4; ilo += v4df::size()) {
			const int iii = ilo + 2 * NLO * k2;
			double* X = Z + iii;
			double* Y = X + NLO;
			for (int n1 = 1; n1 < N1; n1++) {
				const int sn1 = s * n1;
				v4df x, y, tmp;
				x.load(X + sn1);
				y.load(Y + sn1);
				tmp = x;
				x = v4df(wr[n1]) * tmp - v4df(wi[n1]) * y;
				y = v4df(wi[n1]) * tmp + v4df(wr[n1]) * y;
				x.store(X + sn1);
				y.store(Y + sn1);
			}
			butterfly<v4df, N1>(X, Y, s);
		}
		if (NLO2 > NLO4) {
			const int& ilo = NLO4;
			const int iii = ilo + 2 * NLO * k2;
			double* X = Z + iii;
			double* Y = X + NLO;
			for (int n1 = 1; n1 < N1; n1++) {
				const int sn1 = s * n1;
				v2df x, y, tmp;
				x.load(X + sn1);
				y.load(Y + sn1);
				tmp = x;
				x = v2df(wr[n1]) * tmp - v2df(wi[n1]) * y;
				y = v2df(wi[n1]) * tmp + v2df(wr[n1]) * y;
				x.store(X + sn1);
				y.store(Y + sn1);
			}
			butterfly<v2df, N1>(X, Y, s);
		}
		if (NLO1 > NLO4 && NLO1 != NLO2) {
			const int& ilo = NLO2;
			const int iii = ilo + 2 * NLO * k2;
			double* X = Z + iii;
			double* Y = X + NLO;
			for (int n1 = 1; n1 < N1; n1++) {
				const int sn1 = s * n1;
				double x, y, tmp;
				x = *(X + sn1);
				y = *(Y + sn1);
				tmp = x;
				x = wr[n1] * tmp - wi[n1] * y;
				y = wi[n1] * tmp + wr[n1] * y;
				*(X + sn1) = x;
				*(Y + sn1) = y;
			}
			butterfly<N1>(X, Y, s);
		}
	}
}

void inv_perf_shuf(std::complex<double>* Z, int N, int M) {
	for (int n = 0; n < N; n++) {
		double* X = (double*) Z + M * 2 * n;
		inv_perf_shuf(X, M);
	}
}

void perf_shuf(std::complex<double>* Z, int N, int M) {
	for (int n = 0; n < N; n++) {
		double* X = (double*) Z + M * 2 * n;
		perf_shuf(X, M);
	}
}

void fft_1d_batch_3(std::complex<double>* Z, int N, int M) {
}

double fft_1d_3(std::complex<double>* Z, int N) {
	timer tm;
	tm.start();
	const int log3N = std::lround(std::log(N) / std::log(3));
	const int log3N1 = (log3N + 1) >> 1;
	const int log3N2 = log3N - log3N1;
	const std::vector<int> facts1(log3N1, 3);
	const std::vector<int> facts2(log3N2, 3);
	const int N1 = std::lround(std::pow(3, log3N1));
	const int N2 = std::lround(std::pow(3, log3N2));
	const auto& Wr = get_6step_cos_twiddles(N2, N1);
	const auto& Wi = get_6step_sin_twiddles(N2, N1);
	timer tm0, tm1, tm2, tm3, tm4;
	scramble_hi(Z, facts2, N2, N1);
	inv_perf_shuf(Z, N2, N1);
	fft_1d_batch<3>((double*) Z, N2, N1);

	const int end4 = round_down(N1, v4df::size());
	const int end2 = round_down(N1, v2df::size());
	for (int k2 = 0; k2 < N2; k2++) {
		for (int n1 = 0; n1 < end4; n1 += v4df::size()) {
			double* X = (double*) Z + n1 + 2 * N1 * k2;
			double* Y = (double*) X + N1;
			v4df x, y, tmp, wr, wi;
			wr.load(Wr[k2].data() + n1);
			wi.load(Wi[k2].data() + n1);
			x.load(X);
			y.load(Y);
			tmp = x;
			x = tmp * wr - y * wi;
			y = tmp * wi + y * wr;
			x.store(X);
			y.store(Y);
		}
		if (end2 > end4) {
			const int& n1 = end4;
			double* X = (double*) Z + n1 + 2 * N1 * k2;
			double* Y = (double*) X + N1;
			v2df x, y, tmp, wr, wi;
			wr.load(Wr[k2].data() + n1);
			wi.load(Wi[k2].data() + n1);
			x.load(X);
			y.load(Y);
			tmp = x;
			x = tmp * wr - y * wi;
			y = tmp * wi + y * wr;
			x.store(X);
			y.store(Y);
		}
		if (N1 > end4 && N1 != end2) {
			const int& n1 = end2;
			double* X = (double*) Z + n1 + 2 * N1 * k2;
			double* Y = (double*) X + N1;
			double x, y, tmp, wr, wi;
			wr = *(Wr[k2].data() + n1);
			wi = *(Wi[k2].data() + n1);
			x = *X;
			y = *Y;
			tmp = x;
			x = tmp * wr - y * wi;
			y = tmp * wi + y * wr;
			*X = x;
			*Y = y;
		}

	}
	perf_shuf(Z, N2, N1);
	transpose(Z, N2, N / (N2 * N2));
	scramble_hi(Z, facts2, N2, N1);
	inv_perf_shuf(Z, N1, N2);
	fft_1d_batch<3>((double*) Z, N1, N2);
	perf_shuf(Z, N1, N2);
	tm.stop();
	return tm.read();
}
