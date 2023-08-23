/*
 * twiddles.hpp
 *
 *  Created on: Aug 22, 2023
 *      Author: dmarce1
 */

#ifndef TWIDDLES_HPP_
#define TWIDDLES_HPP_

#include <complex>
#include <vector>

const std::complex<double>* get_twiddles(int N);
const double* get_cos_twiddles(int N);
const double* get_sin_twiddles(int N);
const std::vector<std::vector<double>>& get_6step_cos_twiddles(int N1, int N2);
const std::vector<std::vector<double>>& get_6step_sin_twiddles(int N1, int N2);

template<int N>
struct cos_twiddle_array {
	static constexpr int M = N * N;
	double W[M];
	constexpr cos_twiddle_array() :
			W() {
		for (int n = 0; n < M; n++) {
			W[n] = std::cos(2.0 * M_PI * n / N);
		}
	}
};

template<int N>
struct sin_twiddle_array {
	static constexpr int M = N * N;
	double W[M];
	constexpr sin_twiddle_array() :
			W() {
		for (int n = 0; n < M; n++) {
			W[n] = std::sin(2.0 * M_PI * n / N);
		}
	}
};

#endif /* TWIDDLES_HPP_ */
