#include <fft86/butterfly.hpp>
#include <fft86/scramble.hpp>
#include <fft86/timer.hpp>
#include <fft86/twiddles.hpp>
#include <fft86/util.hpp>
#include <fft86/vec.hpp>

#include <complex>
#include <cstring>
#include <vector>

#define L1SIZE (32 * 1024)
#define L2SIZE (512 * 1024)
#define L3SIZE (16384 * 1024)

template<int N1>
void fft_1d_batch_dit(double* Z, int N, int NLO, int level) {
	const int NLO4 = round_down(NLO, v4df::size());
	const int NLO2 = round_down(NLO, v2df::size());
	const int& NLO1 = NLO;
	const int N2 = N / N1;
	if (N2 > 1) {
		for (int n1 = 0; n1 < N1; n1++) {
			fft_1d_batch_dit<N1>(Z + 2 * n1 * NLO * N2, N2, NLO, level + 1);
		}
	}
	const int s = 2 * NLO * N2;
	const double* Wr = get_cos_twiddles(N1 * N2);
	const double* Wi = get_sin_twiddles(N1 * N2);
	const int flags = (N2 == 1 ? INV_SHUF : 0) | (level == 0 ? SHUF : 0);
	for (int k2 = 0; k2 < N2; k2++) {
		std::array<v4df, N1> wr4, wi4;
		for (int n1 = 1; n1 < N1; n1++) {
			const int k2n1 = k2 * n1;
			wr4[n1] = Wr[k2n1];
			wi4[n1] = Wi[k2n1];
		}
		for (int ilo = 0; ilo < NLO4; ilo += v4df::size()) {
			const int iii = 2 * (ilo + NLO * k2);
			double* X = Z + iii;
			double* Y = X + v4df::size();
			butterfly_dit<v4df, N1>(X, s, wr4.data(), wi4.data(), flags);
		}
		if (NLO2 > NLO4) {
			std::array<v2df, N1> wr2, wi2;
			for (int n1 = 1; n1 < N1; n1++) {
				const int k2n1 = k2 * n1;
				wr2[n1] = Wr[k2n1];
				wi2[n1] = Wi[k2n1];
			}
			const int& ilo = NLO4;
			const int iii = 2 * (ilo + NLO * k2);
			double* X = Z + iii;
			double* Y = X + v2df::size();
			butterfly_dit<v2df, N1>(X, s, wr2.data(), wi2.data(), flags);
		}
		if (NLO1 > NLO4 && NLO1 != NLO2) {
			std::array<v1df, N1> wr1, wi1;
			for (int n1 = 1; n1 < N1; n1++) {
				const int k2n1 = k2 * n1;
				wr1[n1] = Wr[k2n1];
				wi1[n1] = Wi[k2n1];
			}
			const int& ilo = NLO2;
			const int iii = 2 * (ilo + NLO * k2);
			double* X = Z + iii;
			double* Y = X + v1df::size();
			butterfly_dit<v1df, N1>(X, s, wr1.data(), wi1.data(), flags);
		}
	}
}

template<int N1>
void fft_1d_batch_dif(double* Z, int N, int NLO, int level) {
	const int NLO4 = round_down(NLO, v4df::size());
	const int NLO2 = round_down(NLO, v2df::size());
	const int& NLO1 = NLO;
	const int N2 = N / N1;
	const int s = 2 * NLO * N2;
	const double* Wr = get_cos_twiddles(N1 * N2);
	const double* Wi = get_sin_twiddles(N1 * N2);
	const int flags = (N2 == 1 ? SHUF : 0) | (level == 0 ? INV_SHUF : 0);
	for (int k2 = 0; k2 < N2; k2++) {
		std::array<v4df, N1> wr4, wi4;
		for (int n1 = 1; n1 < N1; n1++) {
			const int k2n1 = k2 * n1;
			wr4[n1] = Wr[k2n1];
			wi4[n1] = Wi[k2n1];
		}
		for (int ilo = 0; ilo < NLO4; ilo += v4df::size()) {
			const int iii = 2 * (ilo + NLO * k2);
			double* X = Z + iii;
			double* Y = X + v4df::size();
			butterfly_dif<v4df, N1>(X, s, wr4.data(), wi4.data(), flags);
		}
		if (NLO2 > NLO4) {
			std::array<v2df, N1> wr2, wi2;
			for (int n1 = 1; n1 < N1; n1++) {
				const int k2n1 = k2 * n1;
				wr2[n1] = Wr[k2n1];
				wi2[n1] = Wi[k2n1];
			}
			const int& ilo = NLO4;
			const int iii = 2 * (ilo + NLO * k2);
			double* X = Z + iii;
			double* Y = X + v2df::size();
			butterfly_dif<v2df, N1>(X, s, wr2.data(), wi2.data(), flags);
		}
		if (NLO1 > NLO4 && NLO1 != NLO2) {
			std::array<v1df, N1> wr1, wi1;
			for (int n1 = 1; n1 < N1; n1++) {
				const int k2n1 = k2 * n1;
				wr1[n1] = Wr[k2n1];
				wi1[n1] = Wi[k2n1];
			}
			const int& ilo = NLO2;
			const int iii = 2 * (ilo + NLO * k2);
			double* X = Z + iii;
			double* Y = X + v1df::size();
			butterfly_dif<v1df, N1>(X, s, wr1.data(), wi1.data(), flags);
		}
	}
	if (N2 > 1) {
		for (int n1 = 0; n1 < N1; n1++) {
			fft_1d_batch_dif<N1>(Z + 2 * n1 * NLO * N2, N2, NLO, level + 1);
		}
	}
}

void apply_twiddles(std::complex<double>* Z, const std::vector<int>& facts2, int N1, int N2) {
	const auto& Wr = get_6step_cos_twiddles(N2, N1);
	const auto& Wi = get_6step_sin_twiddles(N2, N1);
	const int N = N1 * N2;
	const int end4 = round_down(N1, v4df::size());
	const int end2 = round_down(N1, v2df::size());
	for (digits k2(facts2); k2.to_int() < N2; ++k2) {
		const int k2r = k2.to_int_reverse();
		const int k20 = k2.to_int();
		for (int n1 = 0; n1 < end4; n1 += v4df::size()) {
			double* X = (double*) Z + 2 * (n1 + N1 * k2r);
			double* Y = (double*) X + v4df::size();
			v4df x, y, tmp, wr, wi;
			wr.load(Wr[k20].data() + n1);
			wi.load(Wi[k20].data() + n1);
			x.load(X);
			y.load(Y);
			inv_perf_shuf(x, y);
			tmp = x;
			x = tmp * wr - y * wi;
			y = tmp * wi + y * wr;
			perf_shuf(x, y);
			x.store(X);
			y.store(Y);
		}
		if (end2 > end4) {
			const int& n1 = end4;
			double* X = (double*) Z + 2 * (n1 + N1 * k2r);
			double* Y = (double*) X + v2df::size();
			v2df x, y, tmp, wr, wi;
			wr.load(Wr[k20].data() + n1);
			wi.load(Wi[k20].data() + n1);
			x.load(X);
			y.load(Y);
			inv_perf_shuf(x, y);
			tmp = x;
			x = tmp * wr - y * wi;
			y = tmp * wi + y * wr;
			perf_shuf(x, y);
			x.store(X);
			y.store(Y);
		}
		if (N1 > end4 && N1 != end2) {
			const int& n1 = end2;
			double* X = (double*) Z + 2 * (n1 + N1 * k2r);
			double* Y = (double*) X + v1df::size();
			double x, y, tmp, wr, wi;
			wr = *(Wr[k20].data() + n1);
			wi = *(Wi[k20].data() + n1);
			x = *X;
			y = *Y;
			tmp = x;
			x = tmp * wr - y * wi;
			y = tmp * wi + y * wr;
			*X = x;
			*Y = y;
		}
	}
}

double fft_1d_3(std::complex<double>* Z, int N) {
	timer tm;
	tm.start();
	const int log3N = std::lround(std::log(N) / std::log(3));
	const int log3N1 = (log3N + 1) >> 1;
	const int log3N2 = log3N - log3N1;
	const int N1 = std::lround(std::pow(3, log3N1));
	const int N2 = std::lround(std::pow(3, log3N2));
	const std::vector<int> facts1(log3N1, 3);
	const std::vector<int> facts2(log3N2, 3);


/*	scramble_hi(Z, facts2, N2, N1);
	fft_1d_batch_dit<3>((double*) Z, N2, N1, 0);
	apply_twiddles(Z, N1, N2);
	transpose(Z, N2, N / (N2 * N2));
	scramble_hi(Z, facts2, N2, N1);
	fft_1d_batch_dit<3>((double*) Z, N1, N2, 0);
*/
	fft_1d_batch_dif<3>((double*) Z, N2, N1, 0);
	apply_twiddles(Z, facts2, N1, N2);
	scramble(Z, N);
	fft_1d_batch_dit<3>((double*) Z, N1, N2, 0);

	tm.stop();
	return tm.read();
}
