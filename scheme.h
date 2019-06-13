#ifndef SCHEME_H
#define SCHEME_H
#include <vector>
#include <string>
#include "tuples.h"

class Scheme {
private:
	//std::string schemeName;
	Tuple schemaList;
public:
	std::vector<size_t> matchedSchema;
	std::vector<size_t> unMatchedSchema;
	Scheme(Tuple givenTuple) {
		schemaList = givenTuple;
	}
	Scheme() {}
	Tuple* getSchemaList() {
		return &schemaList;
	}
	void removeScheme(size_t index) {
		if (index < schemaList.size()) {
			schemaList.erase(schemaList.begin() + index);
		}
	}
	std::string getScheme(size_t index) {
		if (index >= schemaList.size()) {
			return "";
		}
		return schemaList.at(index);
	}
	void addSchema(std::string newTuple) {
		schemaList.push_back(newTuple);
	}
	void setScheme(size_t index, std::string newScheme) {
		if (index < schemaList.size()) {
			schemaList.at(index) = newScheme;
		}
	}
	size_t getSize() const {
		return schemaList.size();
	}
	size_t find(std::string s) {
		return schemaList.find(s);
	}
};

#endif // end scheme.h