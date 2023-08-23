/*
 * transpose.h
 *
 *  Created on: Aug 21, 2023
 *      Author: dmarce1
 */

#ifndef TRANSPOSE_H_
#define TRANSPOSE_H_

#include <complex>

void transpose(double* X, int N, int NMID);
void transpose(std::complex<double>* X, int N, int NMID);

#endif /* TRANSPOSE_H_ */
