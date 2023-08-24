#include <fft86/defs.hpp>
#include <fft86/scramble.hpp>

#include <algorithm>
#include <cassert>
#include <cstring>
#include <numeric>
#include <unordered_map>

struct hash {
	size_t operator()(const std::vector<int>& p) const {
		size_t rc = 0;
		for (int i = 0; i < p.size(); i++) {
			rc *= 22695477;
			rc += p[i];
		}
		return rc;
	}
};

const std::vector<int>& get_permutation(const std::vector<int>& facts) {
	static thread_local std::unordered_map<std::vector<int>, std::vector<int>, hash> values;
	auto i = values.find(facts);
	if (i == values.end()) {
		const int imax = std::reduce(facts.begin(), facts.end(), 1, std::multiplies<int>());
		std::vector<int> p;
		for (digits I(facts); I.to_int() < imax; ++I) {
			p.push_back(I.to_int_reverse());
		}
		values[facts] = std::move(p);
		i = values.find(facts);
	}
	return i->second;
}

const std::vector<std::vector<int>>& get_cycles(const std::vector<int>& facts) {
	static thread_local std::unordered_map<std::vector<int>, std::vector<std::vector<int>>, hash> values;
	auto i = values.find(facts);
	if (i == values.end()) {
		const int imax = std::reduce(facts.begin(), facts.end(), 1, std::multiplies<int>());
		std::vector<std::vector<int>> cycles;
		std::vector<bool> visited(imax, false);
		int j = 0;
		const auto P = get_permutation(facts);
		while (j < imax) {
			std::vector<int> cycle;
			int l = j;
			int k = j;
			do {
				if (!visited[k]) {
					visited[k] = true;
					cycle.push_back(k);
				}
				k = P[k];
			} while (k != l);
			std::reverse(cycle.begin(), cycle.end());
			cycles.push_back(std::move(cycle));
			while (j < imax && visited[j]) {
				j++;
			}
		}
		values[facts] = std::move(cycles);
		i = values.find(facts);
	}
	return i->second;
}

template<class T>
void scramble_hi(T* X, const std::vector<int>& hifacts, int N) {
	const int NHI = std::reduce(hifacts.begin(), hifacts.end(), 1, std::multiplies<int>());
	const int NLO = N / NHI;
	const auto& cycles = get_cycles(hifacts);
	static thread_local std::vector<T> tmp;
	constexpr int CHUNK_SIZE = L1SIZE / 4 / sizeof(T);
	tmp.resize(CHUNK_SIZE);
	for (const auto& cycle : cycles) {
		for (int ci = 0; ci < cycle.size() - 1; ci++) {
			for (int n = 0; n < NLO; n += CHUNK_SIZE) {
				const int nchunk = std::min(CHUNK_SIZE, NLO - n);
				const int i = NLO * cycle[ci] + n;
				const int j = NLO * cycle[ci + 1] + n;
				std::memcpy(tmp.data(), X + i, sizeof(T) * nchunk);
				std::memcpy(X + i, X + j, sizeof(T) * nchunk);
				std::memcpy(X + j, tmp.data(), sizeof(T) *nchunk);
			}
		}
	}
}

template<class T>
void scramble(T* X, int N) {
	const auto& facts = factorize(N);
	std::vector<int> hifacts;
	std::vector<int> midfacts;
	std::vector<int> lofacts;
	int i = 0;
	int NHI = 1;
	int& NLO = NHI;
	int j = facts.size() - 1;
	while (i < j && facts[i] == facts[j]) {
		hifacts.push_back(facts[i]);
		NHI *= facts[i];
		i++;
		j--;
	}
	lofacts = hifacts;
	std::reverse(hifacts.begin(), hifacts.end());
	for (; i <= j; i++) {
		midfacts.push_back(facts[i]);
	}
	const int NMID = N / (NHI * NLO);
	assert(NMID == std::reduce(midfacts.begin(), midfacts.end(), 1, std::multiplies<double>()));
	if (hifacts.size() > 1) {
		scramble_hi(X, hifacts, N);
	}
	if (NLO != 1) {
		transpose(X, NHI, NMID);
	}
	if (lofacts.size() > 1) {
		scramble_hi(X, lofacts, N);
	}
	if (midfacts.size() > 1) {
		for (int ihi = 0; ihi < NHI; ihi++) {
			const int iii = ihi * NMID * NLO;
			scramble_hi(X + iii, midfacts, NMID * NLO);
		}
	}
//	printf( "%i = %i x %i x %i\n", N, NHI, NMID, NLO);
}

void scramble(double* X, int N) {
	scramble<double>(X, N);

}

void scramble(std::complex<double>* X, int N) {
	scramble<std::complex<double>>(X, N);
}
