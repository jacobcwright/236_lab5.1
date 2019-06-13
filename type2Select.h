#ifndef TYPE2SELECT_H
#define TYPE2SELECT_H
#include "select.h"
#include <string>

class type2 : public selectParam {
private:
	// map or vector to store identifiers seen
		// std::string identifier1;
		// std::string identifier2;
	size_t index1;
	size_t index2;

public:
	type2(size_t given1, size_t given2) {
		index1 = given1;
		index2 = given2;
	}
	~type2() {}
	/**
	 * @brief
	 * @note
	 * @retval true - given indeces values match / false - don't match
	 */
	bool isSelected(Tuple t) {
		if (index1 >= t.size() || index2 >= t.size()) {
			return false;
		}
		if (t.at(index1) == t.at(index2)) {
			return true;
		}
		return false;
	}
};

#endif // end type2Select.h