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


void scramble(double* X, int N);
void scramble(std::complex<double>* X, int N);

#endif /* SCRAMBLE_HPP_ */
