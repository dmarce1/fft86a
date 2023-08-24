#include <fft86/butterfly.hpp>
#include <fft86/scramble.hpp>
#include <fft86/timer.hpp>
#include <fft86/twiddles.hpp>
#include <fft86/util.hpp>
#include <fft86/vec.hpp>

#include <algorithm>
#include <complex>
#include <cstring>
#include <vector>

#define L1SIZE (32 * 1024)
#define L2SIZE (512 * 1024)
#define L3SIZE (16384 * 1024)

template<int N1>
void fft_1d_batch_dit(double* Z, int N, int NLO, int level, const std::vector<int>& factors);

template<int N1>
void fft_1d_batch_dif(double* Z, int N, int NLO, int level, const std::vector<int>& factors);

void fft_1d_batch_dit_dispatch(double* Z, int N, int NLO, int level, const std::vector<int>& factors) {
	const int N1 = factors[factors.size() - level - 1];
	switch (N1) {
	case 2:
		return fft_1d_batch_dit<2>(Z, N, NLO, level, factors);
	case 4:
		return fft_1d_batch_dit<4>(Z, N, NLO, level, factors);
	case 8:
		return fft_1d_batch_dit<8>(Z, N, NLO, level, factors);
	case 3:
		return fft_1d_batch_dit<3>(Z, N, NLO, level, factors);
	case 5:
		return fft_1d_batch_dit<5>(Z, N, NLO, level, factors);
	case 7:
		return fft_1d_batch_dit<7>(Z, N, NLO, level, factors);
	case 11:
		return fft_1d_batch_dit<11>(Z, N, NLO, level, factors);
	case 13:
		return fft_1d_batch_dit<13>(Z, N, NLO, level, factors);
	}
}

void fft_1d_batch_dif_dispatch(double* Z, int N, int NLO, int level, const std::vector<int>& factors) {
	const int N1 = factors[level];
	switch (N1) {
	case 2:
		return fft_1d_batch_dif<2>(Z, N, NLO, level, factors);
	case 4:
		return fft_1d_batch_dif<4>(Z, N, NLO, level, factors);
	case 8:
		return fft_1d_batch_dif<8>(Z, N, NLO, level, factors);
	case 3:
		return fft_1d_batch_dif<3>(Z, N, NLO, level, factors);
	case 5:
		return fft_1d_batch_dif<5>(Z, N, NLO, level, factors);
	case 7:
		return fft_1d_batch_dif<7>(Z, N, NLO, level, factors);
	case 11:
		return fft_1d_batch_dif<11>(Z, N, NLO, level, factors);
	case 13:
		return fft_1d_batch_dif<13>(Z, N, NLO, level, factors);
	}

}

template<int N1>
void fft_1d_batch_dit(double* Z, int N, int NLO, int level, const std::vector<int>& factors) {
	const int NLO4 = round_down(NLO, v4df::size());
	const int NLO2 = round_down(NLO, v2df::size());
	const int& NLO1 = NLO;
	const int N2 = N / N1;
	if (N2 > 1) {
		for (int n1 = 0; n1 < N1; n1++) {
			fft_1d_batch_dit_dispatch(Z + 2 * n1 * NLO * N2, N2, NLO, level + 1, factors);
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
void fft_1d_batch_dif(double* Z, int N, int NLO, int level, const std::vector<int>& factors) {
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
			fft_1d_batch_dif_dispatch(Z + 2 * n1 * NLO * N2, N2, NLO, level + 1, factors);
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

std::vector<int> find_composite_radices(std::vector<int>&& f) {
	std::vector<int> g;
	for (int n = 0; n < f.size(); n++) {
		int N2 = f[n];
		while (n + 1 < f.size() && f[n + 1] == 2 && N2 < 4) {
			N2 *= 2;
			n++;
		}
		g.push_back(N2);
	}
	return std::move(g);
}

double fft_1d(std::complex<double>* Z, int N) {
	timer tm;
	tm.start();
	auto facts = factorize(N);
	std::vector<int> facts1, facts2;
	int N1 = 1;
	int N2 = 1;
	int sqrtN = std::lround(std::sqrt(N));
	std::reverse(facts.begin(), facts.end());

	for (int l = 0; l < facts.size(); l++) {
		if (N2 < sqrtN && !(!facts1.size() && l == facts.size() - 1)) {
			N2 *= facts[l];
			facts2.push_back(facts[l]);
		} else {
			N1 *= facts[l];
			facts1.push_back(facts[l]);
		}
	}
	const auto twfacts = facts2;
	facts1 = find_composite_radices(std::move(facts1));
	facts2 = find_composite_radices(std::move(facts2));
	fft_1d_batch_dif_dispatch((double*) Z, N2, N1, 0, facts2);
	apply_twiddles(Z, twfacts, N1, N2);
	scramble(Z, N);
	fft_1d_batch_dit_dispatch((double*) Z, N1, N2, 0, facts1);
	tm.stop();
	return tm.read();
}
