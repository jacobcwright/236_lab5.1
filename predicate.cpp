#include "predicate.h"

void Predicate::clear() {
	paramaterList.clear();
	ID = "";
}

void Predicate::add(std::string given) {
	paramaterList.push_back(Parameter(given));
}