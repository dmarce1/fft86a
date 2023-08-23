
#include <fft86/butterfly.hpp>



void butterfly(double* X, double* Y, int stride, int N) {
	if (N % 2 == 1) {
		switch (N) {
		case 3:
			return butterfly<3>((double*) X, (double*) Y, stride);
		case 5:
			return butterfly<5>((double*) X, (double*) Y, stride);
		case 7:
			return butterfly<7>((double*) X, (double*) Y, stride);
		case 11:
			return butterfly<11>((double*) X, (double*) Y, stride);
		case 13:
			return butterfly<13>((double*) X, (double*) Y, stride);
		}
	}
}
