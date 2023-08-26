/*
 * vec.h
 *
 *  Created on: Aug 22, 2023
 *      Author: dmarce1
 */

#pragma once

#include <immintrin.h>

#include <complex>
#include <utility>

class v4df {
	__m256d v;
public:
	static constexpr int size() {
		return 4;
	}
	inline v4df() {
	}
	inline v4df(const v4df& other) {
		v = other.v;
	}
	inline v4df(double other) {
		v = _mm256_set1_pd(other);
	}
	inline v4df& operator=(double other) {
		v = _mm256_set1_pd(other);
		return *this;
	}
	inline v4df& operator=(const v4df& other) {
		v = other.v;
		return *this;
	}
	inline v4df& store(double* ptr) {
		_mm256_storeu_pd(ptr, v);
		return *this;
	}
	inline v4df& load(const double* ptr) {
		v = _mm256_loadu_pd(ptr);
		return *this;
	}
	inline v4df& store(std::complex<double>* ptr) {
		_mm256_storeu_pd((double*) ptr, v);
		return *this;
	}
	inline v4df& load(const std::complex<double>* ptr) {
		v = _mm256_loadu_pd((double*) ptr);
		return *this;
	}
	inline v4df& operator+=(const v4df& other) {
		v = _mm256_add_pd(v, other.v);
		return *this;
	}
	inline v4df& operator-=(const v4df& other) {
		v = _mm256_sub_pd(v, other.v);
		return *this;
	}
	inline v4df& operator*=(const v4df& other) {
		v = _mm256_mul_pd(v, other.v);
		return *this;
	}
	inline v4df& operator/=(const v4df& other) {
		v = _mm256_div_pd(v, other.v);
		return *this;
	}
	inline v4df operator+(const v4df& other) const {
		v4df rc = *this;
		rc += other;
		return rc;
	}
	inline v4df operator-(const v4df& other) const {
		v4df rc = *this;
		rc -= other;
		return rc;
	}
	inline v4df operator*(const v4df& other) const {
		v4df rc = *this;
		rc *= other;
		return rc;
	}
	inline v4df operator/(const v4df& other) const {
		v4df rc = *this;
		rc /= other;
		return rc;
	}
	inline v4df operator-() const {
		v4df rc = v4df(0.0) - *this;
		return rc;
	}
	inline double& operator[](int i) {
		return v[i];
	}
	inline double operator[](int i) const {
		return v[i];
	}
	friend inline void perf_shuf(v4df& a, v4df& b) {
		v4df c, d;
		c.v = _mm256_permute2f128_pd(a.v, b.v, 0x20);
		d.v = _mm256_permute2f128_pd(a.v, b.v, 0x31);
		a.v = _mm256_permute4x64_pd(c.v, 216);
		b.v = _mm256_permute4x64_pd(d.v, 216);
	}
	friend inline void inv_perf_shuf(v4df& a, v4df& b) {
		v4df c, d;
		c.v = _mm256_permute4x64_pd(a.v, 216);
		d.v = _mm256_permute4x64_pd(b.v, 216);
		a.v = _mm256_permute2f128_pd(c.v, d.v, 0x20);
		b.v = _mm256_permute2f128_pd(c.v, d.v, 0x31);
	}
	friend inline void transpose_4x4(v4df& X0, v4df& X1, v4df& X2, v4df& X3) {
		v4df Y0, Y1, Y2, Y3;
		Y0.v = _mm256_unpacklo_pd(X0.v, X1.v);
		Y1.v = _mm256_unpackhi_pd(X0.v, X1.v);
		Y2.v = _mm256_unpacklo_pd(X0.v, X1.v);
		Y3.v = _mm256_unpackhi_pd(X0.v, X1.v);
		X0.v = _mm256_permute2f128_pd(Y0.v, Y2.v, 0x20);
		X1.v = _mm256_permute2f128_pd(Y0.v, Y2.v, 0x31);
		X2.v = _mm256_permute2f128_pd(Y1.v, Y3.v, 0x20);
		X3.v = _mm256_permute2f128_pd(Y1.v, Y3.v, 0x31);
	}

	friend inline void transpose_2x2x2(v4df& X0, v4df& X1) {
		v4df Y0;
		Y0.v = _mm256_permute2f128_pd(X0.v, X1.v, 0x20);
		X1.v = _mm256_permute2f128_pd(X0.v, X1.v, 0x31);
		X0 = Y0;
	}
};

class v2df {
	__m128d v;
public:
	static constexpr int size() {
		return 2;
	}
	inline v2df() {
	}
	inline v2df(const v2df& other) {
		v = other.v;
	}
	inline v2df(double other) {
		v = _mm_set1_pd(other);
	}
	inline v2df& operator=(double other) {
		v = _mm_set1_pd(other);
		return *this;
	}
	inline v2df& operator=(const v2df& other) {
		v = other.v;
		return *this;
	}
	inline v2df& store(double* ptr) {
		_mm_storeu_pd(ptr, v);
		return *this;
	}
	inline v2df& load(const double* ptr) {
		v = _mm_loadu_pd(ptr);
		return *this;
	}
	inline v2df& store(std::complex<double>* ptr) {
		_mm_storeu_pd((double*) ptr, v);
		return *this;
	}
	inline v2df& load(const std::complex<double>* ptr) {
		v = _mm_loadu_pd((double*) ptr);
		return *this;
	}
	inline v2df& operator+=(const v2df& other) {
		v = _mm_add_pd(v, other.v);
		return *this;
	}
	inline v2df& operator-=(const v2df& other) {
		v = _mm_sub_pd(v, other.v);
		return *this;
	}
	inline v2df& operator*=(const v2df& other) {
		v = _mm_mul_pd(v, other.v);
		return *this;
	}
	inline v2df& operator/=(const v2df& other) {
		v = _mm_div_pd(v, other.v);
		return *this;
	}
	inline v2df operator+(const v2df& other) const {
		v2df rc = *this;
		rc += other;
		return rc;
	}
	inline v2df operator-(const v2df& other) const {
		v2df rc = *this;
		rc -= other;
		return rc;
	}
	inline v2df operator*(const v2df& other) const {
		v2df rc = *this;
		rc *= other;
		return rc;
	}
	inline v2df operator/(const v2df& other) const {
		v2df rc = *this;
		rc /= other;
		return rc;
	}
	inline v2df operator-() const {
		v2df rc = v2df(0.0) - *this;
		return rc;
	}
	inline double& operator[](int i) {
		return v[i];
	}
	inline double operator[](int i) const {
		return v[i];
	}
	friend inline void perf_shuf(v2df& a, v2df& b) {
		std::swap(a.v[1], b.v[0]);
	}
	friend inline void inv_perf_shuf(v2df& a, v2df& b) {
		std::swap(a.v[1], b.v[0]);
	}
	friend inline void transpose_2x2(v2df& X0, v2df& X1) {
		std::swap(X0.v[1], X1.v[0]);
	}
};

class v1df {
	double v;
public:
	static constexpr int size() {
		return 1;
	}
	inline v1df() {
	}
	inline v1df(const v1df& other) {
		v = other.v;
	}
	inline v1df(double other) {
		v = other;
	}
	inline v1df& operator=(double other) {
		v = other;
		return *this;
	}
	inline v1df& operator=(const v1df& other) {
		v = other.v;
		return *this;
	}
	inline v1df& store(double* ptr) {
		*ptr = v;
		return *this;
	}
	inline v1df& load(const double* ptr) {
		v = *ptr;
		return *this;
	}
	inline v1df& operator+=(const v1df& other) {
		v = (v + other.v);
		return *this;
	}
	inline v1df& operator-=(const v1df& other) {
		v = (v - other.v);
		return *this;
	}
	inline v1df& operator*=(const v1df& other) {
		v = (v * other.v);
		return *this;
	}
	inline v1df& operator/=(const v1df& other) {
		v = (v / other.v);
		return *this;
	}
	inline v1df operator+(const v1df& other) const {
		v1df rc = *this;
		rc += other;
		return rc;
	}
	inline v1df operator-(const v1df& other) const {
		v1df rc = *this;
		rc -= other;
		return rc;
	}
	inline v1df operator*(const v1df& other) const {
		v1df rc = *this;
		rc *= other;
		return rc;
	}
	inline v1df operator/(const v1df& other) const {
		v1df rc = *this;
		rc /= other;
		return rc;
	}
	inline v1df operator-() const {
		v1df rc(-v);
		return rc;
	}
	inline double& operator[](int i) {
		return v;
	}
	inline double operator[](int i) const {
		return v;
	}
	friend inline void perf_shuf(v1df& a, v1df& b) {
	}
	friend inline void inv_perf_shuf(v1df& a, v1df& b) {
	}
	friend inline void transpose_2x2(v1df& X0, v1df& X1) {
	}
};
