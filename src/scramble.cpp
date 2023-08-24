#include <fft86/scramble.hpp>

#include <algorithm>
#include <numeric>



template<class T>
void scramble_mid(T* X, const std::vector<int>& midfacts, int NHI, int NMID,
		int NLO) {
	digits I(midfacts);
	I = 0;
	bool done = false;
	for (int k = 0; k < NHI; k++) {
		while (1) {
			++I;
			const int i = I.to_int();
			const int j = I.to_int_reverse();
			if (i >= NHI) {
				break;
			} else if (i < j) {
				const int n = (NMID * k + i) * NLO;
				const int m = (NMID * k + j) * NLO;
				for (int l = 0; l < NLO; l++) {
					std::swap(X[l + n], X[l + m]);
				}
			}
		}
	}
}

template<class T>
std::vector<int> scramble_(T* X, int N) {
	factorization factors = factorize(N);
	const int NLO = std::reduce(factors.ends.begin(), factors.ends.end(), 1,
			std::multiplies<int>());
	const int NMID = std::reduce(factors.middle.begin(), factors.middle.end(),
			1, std::multiplies<int>());
	const int& NHI = NLO;
	if (factors.ends.size() > 1) {
		scramble_hi(X, factors.ends, NHI, NLO * NMID);
	}
	if (factors.ends.size() >= 1) {
		transpose(X, NHI, NMID);
	}
	if (factors.ends.size() > 1) {
		scramble_hi(X, factors.ends, NHI, NLO * NMID);
	}
	if (factors.middle.size() > 1) {
		scramble_mid(X, factors.middle, NHI, NMID, NLO);
	}
	std::vector<int> rc;
	rc.insert(rc.end(), factors.ends.begin(), factors.ends.end());
	rc.insert(rc.end(), factors.middle.begin(), factors.middle.end());
	rc.insert(rc.end(), factors.ends.begin(), factors.ends.end());
	std::reverse(rc.begin(), rc.end());
	return std::move(rc);
}

std::vector<int> scramble(double* X, int N) {
	return scramble_<double>(X, N);
}

std::vector<int> scramble(std::complex<double>* X, int N) {
	return scramble_<std::complex<double>>(X, N);
}
