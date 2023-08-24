#include <fft86/defs.hpp>
#include <fft86/scramble.hpp>

#include <algorithm>
#include <cassert>
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
	for (const auto& cycle : cycles) {
		for (int ci = 0; ci < cycle.size() - 1; ci++) {
			const int i = cycle[ci];
			const int j = cycle[ci + 1];
			for (int ilo = 0; ilo < NLO; ilo++) {
				const int iii = i * NLO + ilo;
				const int jjj = j * NLO + ilo;
				std::swap(X[iii], X[jjj]);
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
	size_t size = sizeof(T);
	int i = 0;
	int j = facts.size() - 1;
	if (facts.size() < 2) {
		return;
	}
	int NLO = 1;
	int NHI = 1;
	while (i <= j) {
		if (NLO < NHI) {
			size *= facts[i];
			if (size > L1SIZE) {
				break;
			}
			lofacts.push_back(facts[i]);
			NLO *= facts[i];
			i++;
		} else {
			size *= facts[j];
			if (size > L1SIZE) {
				break;
			}
			hifacts.push_back(facts[j]);
			NHI *= facts[j];
			j--;
		}
	}
	std::reverse(hifacts.begin(), hifacts.end());
	for (; i <= j; i++) {
		midfacts.push_back(facts[i]);
	}
	const int NMID = std::reduce(midfacts.begin(), midfacts.end(), 1, std::multiplies<int>());
	//printf("%i %i %i %i\n", N, NHI, NMID, NLO);
	assert(N == NMID * NLO * NHI);
	if (hifacts.size() > 1) {
		scramble_hi(X, hifacts, N);
	}
	if (NLO != 1 || NHI != 1) {
		transpose(X, NLO, NMID, NHI);
	}
	std::swap(NHI, NLO);
	std::swap(hifacts, lofacts);
	if (hifacts.size() > 1) {
		scramble_hi(X, hifacts, N);
	}
	if (midfacts.size() > 1) {
		for (int ihi = 0; ihi < NHI; ihi++) {
			const int iii = ihi * NMID * NLO;
			scramble_hi(X + iii, midfacts, NMID * NLO);
		}
	}
}

void scramble(double* X, int N) {
	scramble<double>(X, N);

}

void scramble(std::complex<double>* X, int N) {
	scramble<std::complex<double>>(X, N);
}
