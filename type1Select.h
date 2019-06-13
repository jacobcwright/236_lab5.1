#ifndef TYPE1SELECT_H
#define TYPE1SELECT_H
#include "select.h"
#include <string>

class type1 : public selectParam {
private:
	std::string constant;
	// std::string identifier;
	size_t index;

public:
	type1(std::string givenStr, size_t givenIndex) {
		constant = givenStr;
		index = givenIndex;
	}

	~type1() {}
	/**
	 * @brief  1 constant
	 * @note
	 * @retval true - matches given string / false - doesn't match given string
	 */
	bool isSelected(Tuple t) {
		if (index >= t.size()) return false;
		if (t.at(index) == constant) {
			return true;
		}

		return false;
	}
};

#endif