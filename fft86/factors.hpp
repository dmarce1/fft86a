/*
 * factors.hpp
 *
 *  Created on: Aug 22, 2023
 *      Author: dmarce1
 */

#ifndef FACTORS_HPP_
#define FACTORS_HPP_

#include <vector>

struct factorization {
	std::vector<int> middle;
	std::vector<int> ends;
};

class digits {
	std::vector<int> facts;
	std::vector<int> digs;
public:
	digits(const std::vector<int>&);
	digits& operator=(int n);
	digits& operator++();
	int to_int() const;
	int to_int_reverse() const;
};

factorization factorize(int N);

#endif /* FACTORS_HPP_ */