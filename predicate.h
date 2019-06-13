#ifndef PREDICATE_H
#define PREDICATE_H
#include "parameter.h"
#include <string>
#include <sstream>
#include <vector>

class Predicate {
private:
	std::string ID;
public:
	std::vector<Parameter> paramaterList;
	Predicate(std::string given = "") {
		ID = given;
	}
	void clear();
	void setID(std::string given) { ID = given; }
	void add(std::string given);
	std::string getID()const { return ID; }
	std::string toString() {
		std::stringstream ss;
		ss << getID() << "(";
		for (size_t i = 0; i < paramaterList.size(); i++) {
			if (i == paramaterList.size() - 1) {
				ss << paramaterList.at(i) << ")?";
				break;
			}
			ss << paramaterList.at(i) << ",";
		}
		return ss.str();
	}
	friend std::ostream& operator<< (std::ostream& os, const Predicate& p) {
		os << p.getID();
		return os;
	}
};

#endif //end predicate.h