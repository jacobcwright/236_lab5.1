#ifndef TUPLES_H
#define TUPLES_H
#include "facts.h"
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

/*
 * @brief  Inherited from vector, so also have all of vectors methods.
 * @note   i.e. push_back, clear, size, etc.
 * @retval Varies
 */

class Tuple : public std::vector<std::string> {
public:
	Tuple(Facts givenFact) {
		for (size_t i = 0; i < givenFact.stringList.size(); i++) {
			this->push_back(givenFact.stringList.at(i));
		}
	}

	Tuple() {}
	/**
	 * @brief  format output for tuples
	 * @note
	 * @retval string
	 */
	std::string toString() const {
		std::stringstream ss;
		ss << "(";
		for (size_t i = 0; i < size(); i++) {
			if (i == size() - 1) {
				ss << at(i) << ")";
				break;
			}
			ss << at(i) << ",";
		}
		return ss.str();
	}
	size_t find(std::string s) {
		std::vector<std::string>::iterator it = std::find(this->begin(), this->end(), s);
		if (it == this->end()) return -1;
		return std::distance(this->begin(), it);
	}

	/*void insert(std::vector<std::string>::iterator it, std::string value) {
		this->insert(it, value);
	}*/
};

#endif