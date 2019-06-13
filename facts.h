#ifndef FACTS_H
#define FACTS_H
#include <string>
#include <vector>

class Facts {
private:
	std::string ID;
public:
	std::vector<std::string> stringList;
	Facts(std::string givenID = "") {
		ID = givenID;
	}
	void clear();
	std::string getID()const { return ID; }
	void setID(std::string given) { ID = given; }
	friend std::ostream& operator<< (std::ostream& os, const Facts& f) {
		os << f.getID();
		return os;
	}
};

#endif // end facts.h