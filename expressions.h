#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H
#include "parameter.h"
#include <sstream>

class Expressions : public Parameter {
private:
	Parameter* param1;
	Parameter* op;
	Parameter* param2;
public:
	Expressions() {
		param1 = nullptr;
		op = nullptr;
		param2 = nullptr;
	}
	~Expressions() {
		delete param1;
		delete op;
		delete param2;
	}
	std::string toString()const {
		std::stringstream ss;
		ss << "(" << param1->getValue() << op->getValue() << param2->getValue() << ")";
		return ss.str();
	}
	friend std::ostream& operator<< (std::ostream& os, const Expressions& e) {
		os << e.toString();
		return os;
	}
	void clear() {
		delete param1;
		delete op;
		delete param2;
		param1 = nullptr;
		op = nullptr;
		param2 = nullptr;
	}
	void setParam1(Parameter* given) { param1 = given; }
	void setParam2(Parameter* given) { param2 = given; }
	void setOp(Parameter* given) { op = given; }
	Parameter* getParam1() { return param1; }
	Parameter* getParam2() { return param2; }
	Parameter* getOp() { return op; }
};

#endif //end expressions.h