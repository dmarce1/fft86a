/*
 * fft.hpp
 *
 *  Created on: Aug 23, 2023
 *      Author: dmarce1
 */

#ifndef FFT321_HPP_
#define FFT321_HPP_

#include <complex>

double fft_1d(std::complex<double>* Z, int N);
void fft_pfa(std::complex<double>* X, int N1, int N2);


#endif /* FFT_HPP_ */
