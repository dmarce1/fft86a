/*
 * scramble.hpp
 *
 *  Created on: Aug 22, 2023
 *      Author: dmarce1
 */

#ifndef SCRAMBLE_HPP_
#define SCRAMBLE_HPP_

#include <complex>
#include <vector>

#include <fft86/factors.hpp>
#include <fft86/transpose.hpp>
#include <fft86/vec.hpp>


std::vector<int> scramble(double* X, int N);
std::vector<int> scramble(std::complex<double>* X, int N);

template<class T>
void scramble_hi(T* X, const std::vector<int>& hifacts, int NHI, int NLO) {
	digits I(hifacts);
	I = 0;
	bool done = false;
	while (1) {
		++I;
		const int i = I.to_int();
		const int j = I.to_int_reverse();
		if (i >= NHI) {
			break;
		} else if (i < j) {
			const int n = i * NLO;
			const int m = j * NLO;
			for (int l = 0; l < NLO; l++) {
				std::swap(X[l + n], X[l + m]);
			}
		}
	}
}

#endif /* SCRAMBLE_HPP_ */
