#ifndef PARAMETER_H
#define PARAMETER_H
#include <string>

enum paramType { PARAMETER, EXPRESSION };

class Parameter {
	std::string value;
	paramType type;
	bool isConstant;
public:
	virtual ~Parameter() {}
	Parameter(std::string given = "", paramType givenType = PARAMETER, bool givenConstant = true) {
		value = given;
		type = givenType;
		isConstant = givenConstant;
	}
	virtual void clear() { value = ""; }
	void setValue(std::string given) { value = given; }
	void setValue(std::string given, paramType givenType) {
		value = given;
		type = givenType;
	}
	void setValue(std::string given, bool givenConst) {
		value = given;
		isConstant = givenConst;
	}
	std::string getValue() const { return value; }
	friend std::ostream& operator<< (std::ostream& os, const Parameter& p) {
		os << p.toString();
		return os;
	}
	virtual std::string toString() const {
		return getValue();
	}
	bool getConstant() {
		return isConstant;
	}
};

#endif //end Parameter.h