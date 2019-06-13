#ifndef RULES_H
#define RULES_H
#include "predicate.h"
#include <vector>
#include <sstream>

class Rules {
private:
	Predicate head;
public:
	std::vector<Predicate> predicateList;
	int graphID;
	Rules() {
		predicateList = {};
		graphID = -1;
	}
	void clear();
	std::string getHead() const {
		return head.getID();
	}
	Predicate getHeadPred() {
		return head;
	}
	void setHead(Predicate given) { head = given; }
	friend std::ostream& operator<< (std::ostream& os, const Rules& r) {
		os << r.toString();
		return os;
	}
	std::string toString() const {
		std::stringstream ss;
		ss << getHead() << "(";
		for (auto& p : head.paramaterList) {
			if (p.getValue() == head.paramaterList.back().getValue()) {
				ss << p << ") :- ";
				break;
			}
			ss << p << ",";
		}
		for (auto& p : predicateList) {
			ss << p.getID() << "(";
			for (auto& s : p.paramaterList) {
				if (s.getValue() == p.paramaterList.back().getValue()) {
					ss << s << "),";
					break;
				}
				ss << s << ",";
			}
		}
		std::string temp = ss.str();
		temp.pop_back();
		temp.push_back('.');
		return temp;
	}
	Predicate getHead() {
		return head;
	}
};

#endif // end rules.h