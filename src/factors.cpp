#include <fft86/factors.hpp>

#include <algorithm>
#include <limits>
#include <map>
#include <unordered_map>
#include <cmath>
#include <stdio.h>

bool is_prime(int n) {
	static thread_local std::unordered_map<int, bool> values;
	auto i = values.find(n);
	if (i == values.end()) {
		bool v = true;
		if (n == 1) {
			v = false;
		} else {
			int kmax = std::floor(std::sqrt(n));
			for (auto i = 2; i <= kmax; i++) {
				if (n % i == 0) {
					v = false;
					break;
				}
				if (i > kmax) {
					break;
				}
			}
		}
		values[n] = v;
		i = values.find(n);
	}
	return i->second;
}

std::vector<int> factorize(int N) {
	static thread_local std::unordered_map<int, std::vector<int>> values;
	auto i = values.find(N);
	if (i == values.end()) {
		std::vector<int> factors;
		std::map<int, int> factor_map;
		std::vector<int> ends;
		std::vector<int> middle;
		int M = N;
		while (M > 1) {
			for (int n = 2; n <= M; n++) {
				if (M % n == 0 && is_prime(n)) {
					if (factor_map.find(n) == factor_map.end()) {
						factor_map[n] = 0;
					}
					factor_map[n]++;
					M /= n;
				}
			}
		}
	//	int N2 = factor_map[2] & (~1);
	//	factor_map[2] -= N2;
	//	factor_map[4] = N2 >> 1;
		for (auto i = factor_map.begin(); i != factor_map.end(); i++) {
			int m;
			for (m = i->second; m > 1; m -= 2) {
				ends.push_back(i->first);
			}
			if (m == 1) {
				middle.push_back(i->first);
			}
		}
		std::vector<int> f(ends.begin(), ends.end());
		f.insert(f.end(), middle.begin(), middle.end());
		std::reverse(ends.begin(), ends.end());
		f.insert(f.end(), ends.begin(), ends.end());
		values[N] = std::move(f);
		i = values.find(N);
	}
	return i->second;
}

digits& digits::operator=(int n) {
	digs.resize(facts.size());
	for (int i = 0; i < facts.size(); i++) {
		digs[i] = n % facts[i];
		n /= facts[i];
	}
	return *this;
}

digits& digits::operator++() {
	int i = 0;
	while (i < digs.size() && (digs[i] == facts[i] - 1)) {
		digs[i] = 0;
		i++;
	}
	if (i == digs.size()) {
		digs.back() = facts.back();
	} else {
		digs[i]++;
	}
	return *this;
}

int digits::to_int() const {
	int n = digs.back();
	for (int i = facts.size() - 2; i >= 0; i--) {
		n *= facts[i];
		n += digs[i];
	}
	return n;
}

int digits::to_int_reverse() const {
	int n = digs[0];
	for (int i = 1; i < facts.size(); i++) {
		n *= facts[i];
		n += digs[i];
	}
	return n;
}

digits::digits(const std::vector<int>& f) {
	facts = f;
	digs.resize(f.size(), 0);
}
