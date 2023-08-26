#include <fft86/butterfly.hpp>
#include <fft86/scramble.hpp>
#include <fft86/timer.hpp>
#include <fft86/twiddles.hpp>
#include <fft86/util.hpp>
#include <fft86/vec.hpp>

#include <algorithm>
#include <numeric>
#include <cassert>
#include <complex>
#include <cstring>
#include <vector>

#define L1SIZE (32 * 1024)
#define L2SIZE (512 * 1024)
#define L3SIZE (16384 * 1024)

struct params_t {
	int N;
	const std::vector<double>* WR;
	const std::vector<double>* WI;
	const double* wr;
	const double* wi;
	const int* P;
	const int* factors;
	int num_radix;
};

template<int N1>
void fft_1d_batch_dit(const params_t* params, double* Z, int N, int NLO, int leve);

template<int N1>
void fft_1d_batch_dif(const params_t* params, double* Z, int k2_offset, int N, int NLO, int level);

inline void fft_1d_batch_dit_dispatch(const params_t* params, double* Z, int N, int NLO, int level) {
	const int N1 = params->factors[params->num_radix - level - 1];
	switch (N1) {
	case 2:
		return fft_1d_batch_dit<2>(params, Z, N, NLO, level);
	case 4:
		return fft_1d_batch_dit<4>(params, Z, N, NLO, level);
	case 8:
		return fft_1d_batch_dit<8>(params, Z, N, NLO, level);
	case 16:
		return fft_1d_batch_dit<16>(params, Z, N, NLO, level);
	case 32:
		return fft_1d_batch_dit<32>(params, Z, N, NLO, level);
	case 3:
		return fft_1d_batch_dit<3>(params, Z, N, NLO, level);
	case 5:
		return fft_1d_batch_dit<5>(params, Z, N, NLO, level);
	case 7:
		return fft_1d_batch_dit<7>(params, Z, N, NLO, level);
	case 11:
		return fft_1d_batch_dit<11>(params, Z, N, NLO, level);
	case 13:
		return fft_1d_batch_dit<13>(params, Z, N, NLO, level);
	}
}

inline void fft_1d_batch_dif_dispatch(const params_t* params, double* Z, int k2_offset, int N, int NLO, int level) {
	const int N1 = params->factors[level];
	switch (N1) {
	case 2:
		return fft_1d_batch_dif<2>(params, Z, k2_offset, N, NLO, level);
	case 4:
		return fft_1d_batch_dif<4>(params, Z, k2_offset, N, NLO, level);
	case 8:
		return fft_1d_batch_dif<8>(params, Z, k2_offset, N, NLO, level);
	case 16:
		return fft_1d_batch_dif<16>(params, Z, k2_offset, N, NLO, level);
	case 32:
		return fft_1d_batch_dif<32>(params, Z, k2_offset, N, NLO, level);
	case 3:
		return fft_1d_batch_dif<3>(params, Z, k2_offset, N, NLO, level);
	case 5:
		return fft_1d_batch_dif<5>(params, Z, k2_offset, N, NLO, level);
	case 7:
		return fft_1d_batch_dif<7>(params, Z, k2_offset, N, NLO, level);
	case 11:
		return fft_1d_batch_dif<11>(params, Z, k2_offset, N, NLO, level);
	case 13:
		return fft_1d_batch_dif<13>(params, Z, k2_offset, N, NLO, level);
	}

}

template<int N1>
void fft_1d_batch_dit(const params_t* params, double* Z, int N, int NLO, int level) {
	const int NLO4 = round_down(NLO, v4df::size());
	const int NLO2 = round_down(NLO, v2df::size());
	const int& NLO1 = NLO;
	const int N2 = N / N1;
	if (N2 > 1) {
		for (int n1 = 0; n1 < N1; n1++) {
			fft_1d_batch_dit_dispatch(params, Z + 2 * n1 * NLO * N2, N2, NLO, level + 1);
		}
	}
	const int s = 2 * NLO * N2;
	const double* Wr = params->wr;
	const double* Wi = params->wi;
	const int NTW = params->N / N;
	const int flags = (N2 == 1 ? INV_SHUF : 0) | (level == 0 ? SHUF : 0);
	for (int k2 = 0; k2 < N2; k2++) {
		std::array<v4df, N1> wr4, wi4;
		for (int n1 = 1; n1 < N1; n1++) {
			const int k2n1 = NTW * k2 * n1;
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
				const int k2n1 = NTW * k2 * n1;
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
				const int k2n1 = NTW * k2 * n1;
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
void fft_1d_batch_dif(const params_t* params, double* Z, int k2_offset, int N, int NLO, int level) {
	const int NLO4 = round_down(NLO, v4df::size());
	const int NLO2 = round_down(NLO, v2df::size());
	const int& NLO1 = NLO;
	const int N2 = N / N1;
	const int s = 2 * NLO * N2;
	const double* Wr = params->wr;
	const double* Wi = params->wi;
	const int NTW = params->N / N;
	const int flags = level == 0 ? INV_SHUF : 0;
	for (int k2 = 0; k2 < N2; k2++) {
		std::array<v4df, N1> wr4, wi4;
		for (int n1 = 1; n1 < N1; n1++) {
			const int k2n1 = NTW * k2 * n1;
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
				const int k2n1 = NTW * k2 * n1;
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
				const int k2n1 = NTW * k2 * n1;
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
			fft_1d_batch_dif_dispatch(params, Z + 2 * n1 * NLO * N2, N1 * k2_offset + n1, N2, NLO, level + 1);
		}
	} else {
		const auto* P = params->P;
		const auto* WR = params->WR;
		const auto* WI = params->WI;
		for (int k2 = N1 * k2_offset; k2 < N1 * k2_offset + N1; k2++) {
			const int k2r = P[k2];
			for (int n1 = 0; n1 < NLO4; n1 += v4df::size()) {
				double* X = (double*) Z + 2 * (n1 + NLO * (k2 - N1 * k2_offset));
				double* Y = (double*) X + v4df::size();
				v4df x, y, tmp, wr, wi;
				wr.load(WR[k2r].data() + n1);
				wi.load(WI[k2r].data() + n1);
				x.load(X);
				y.load(Y);
				tmp = x;
				x = tmp * wr - y * wi;
				y = tmp * wi + y * wr;
				perf_shuf(x, y);
				x.store(X);
				y.store(Y);
			}
			if (NLO2 > NLO4) {
				const int& n1 = NLO4;
				double* X = (double*) Z + 2 * (n1 + NLO * (k2 - N1 * k2_offset));
				double* Y = (double*) X + v2df::size();
				v2df x, y, tmp, wr, wi;
				wr.load(WR[k2r].data() + n1);
				wi.load(WI[k2r].data() + n1);
				x.load(X);
				y.load(Y);
				tmp = x;
				x = tmp * wr - y * wi;
				y = tmp * wi + y * wr;
				perf_shuf(x, y);
				x.store(X);
				y.store(Y);
			}
			if (NLO > NLO4 && NLO != NLO2) {
				const int& n1 = NLO2;
				double* X = (double*) Z + 2 * (n1 + NLO * (k2 - N1 * k2_offset));
				double* Y = (double*) X + v1df::size();
				double x, y, tmp, wr, wi;
				wr = *(WR[k2r].data() + n1);
				wi = *(WI[k2r].data() + n1);
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
}

std::vector<int> find_composite_radices(std::vector<int>&& f, int NLO) {
	std::vector<int> g;
	for (int n = 0; n < f.size(); n++) {
		int N2 = f[n];
		while (n + 1 < f.size() && f[n + 1] == 2 && (N2 % 2 == 0 && N2 < 4)) {
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
	auto twfacts = facts2;
	std::reverse(twfacts.begin(), twfacts.end());
	facts1 = find_composite_radices(std::move(facts1), N2);
	facts2 = find_composite_radices(std::move(facts2), N1);
	const auto& Wr = get_6step_cos_twiddles(N2, N1);
	const auto& Wi = get_6step_sin_twiddles(N2, N1);
	assert(N1 * N2 == N);
	assert(N1 = std::reduce(facts1.begin(), facts1.end(), 1, std::multiplies<int>()));
	assert(N2 = std::reduce(facts2.begin(), facts2.end(), 1, std::multiplies<int>()));
	const auto& P = get_permutation(twfacts);
	params_t dif_params;
	params_t dit_params;
	dif_params.N = N2;
	dif_params.WR = Wr.data();
	dif_params.WI = Wi.data();
	dif_params.P = P.data();
	dif_params.num_radix = facts2.size();
	dif_params.wr = get_cos_twiddles(N2);
	dif_params.wi = get_sin_twiddles(N2);
	dif_params.factors = facts2.data();
	dit_params.N = N1;
	dit_params.wr = get_cos_twiddles(N1);
	dit_params.wi = get_sin_twiddles(N1);
	dit_params.factors = facts1.data();
	dit_params.num_radix = facts1.size();
	fft_1d_batch_dif_dispatch(&dif_params, (double*) Z, 0, N2, N1, 0);
	scramble(Z, N);
	fft_1d_batch_dit_dispatch(&dit_params, (double*) Z, N1, N2, 0);
	tm.stop();
	return tm.read();
}
