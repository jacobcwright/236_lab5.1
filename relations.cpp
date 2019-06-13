#include "relations.h"

Relation Relation::naturalJoin(Relation& givenRelation) {
	Relation newRelation;
	//add matched schema and mark matched schema
	for (size_t i = 0; i < relationScheme.getSize(); i++) {
		bool match = false;
		for (size_t j = 0; j < givenRelation.relationScheme.getSize(); j++) {
			if (relationScheme.getScheme(i) == givenRelation.relationScheme.getScheme(j)) {
				match = true;
				relationScheme.matchedSchema.push_back(i);
				givenRelation.relationScheme.matchedSchema.push_back(j);
				newRelation.relationScheme.addSchema(relationScheme.getScheme(i));
			}
		}
		// add unmatched schema from *this* relation and mark them as unMatched
		if (!match) {
			relationScheme.unMatchedSchema.push_back(i);
			newRelation.relationScheme.addSchema(relationScheme.getScheme(i));
		}
	}

	//add non-matched schema from givenRelation
	for (size_t i = 0; i < givenRelation.relationScheme.getSize(); i++) {
		bool match = false;
		for (size_t j = 0; j < newRelation.relationScheme.getSize(); j++) {
			if (givenRelation.relationScheme.getScheme(i) == newRelation.relationScheme.getScheme(j)) {
				//givenRelation.relationScheme.unMatchedSchema.push_back(j);
				//newRelation.relationScheme.addSchema(givenRelation.relationScheme.getScheme(i));
				match = true;
				break;
			}
		}
		if (!match) {
			givenRelation.relationScheme.unMatchedSchema.push_back(i);
			newRelation.relationScheme.addSchema(givenRelation.relationScheme.getScheme(i));
		}
	}

	// add tuples to new Relation
	naturalJoin2(givenRelation, newRelation);

	return newRelation;
}

Relation Relation::naturalJoin2(Relation& givenRelation, Relation& newRelation) {
	//add matched tuples
	for (auto& t1 : relationTuples) {
		bool match = true;
		for (auto& t2 : givenRelation.relationTuples) {
			Tuple newTuple = {};
			for (size_t i = 0; i < relationScheme.matchedSchema.size(); i++) {
				//if this tuple at matched location = given tuple at matched location
				if (t1.at(relationScheme.matchedSchema.at(i)) == t2.at(givenRelation.relationScheme.matchedSchema.at(i))) {
					// add to new tuple
					newTuple.push_back(t1.at(relationScheme.matchedSchema.at(i))); //join adds joined scheme tuple first
					match = true;
				}
				else {
					// no match, reset tuple and break
					match = false;
					newTuple.clear();
					break;
				}
			}
			//add unmatched tuples to new tuple if match is found
			if (match) {
				//add unmatched tuple location from this relation
				for (size_t j = 0; j < relationScheme.unMatchedSchema.size(); j++) {
					newTuple.push_back(t1.at(relationScheme.unMatchedSchema.at(j)));
					//newTuple.insert(newTuple.begin() + j, t1.at(relationScheme.unMatchedSchema.at(j)));
				}
				//add unmatched tuple location from given relation
				for (size_t k = 0; k < givenRelation.relationScheme.unMatchedSchema.size(); k++) {
					newTuple.push_back(t2.at(givenRelation.relationScheme.unMatchedSchema.at(k))); //out of bounds
				}
				//insert tuple into relation
				newRelation.relationTuples.insert(newTuple);
			}
		}
	}

	return newRelation;
}

int Relation::Union(Relation& givenRelation) {
	/***PSEUDO***
	 * check that schemas match
	 * for loop of givenRelation
	 * thisRelation.addTuple(givenRelation)
	 * return integer of number of new things actually added
	*/
	int numInsert = 0;

	// check schema size
	if (relationScheme.getSize() != givenRelation.relationScheme.getSize()) {
		std::cout << "SCHEMES DO NOT MATCH, EXITING" << std::endl;
		return 0;
	}

	// check schemes match
	for (size_t i = 0; i < relationScheme.getSize(); i++) {
		if (relationScheme.getScheme(i) != givenRelation.relationScheme.getScheme(i)) {
			std::cout << "SCHEMES DO NOT MATCH, EXITING" << std::endl;
			return 0;
		}
	}

	for (auto& t : givenRelation.relationTuples) {
		if (relationTuples.insert(t).second) {
			numInsert++;
			//std::cout << "Added new tuple:" << std::endl << "\t" << relationName << t.toString() << std::endl;
		}
	}

	return numInsert;
}

void Relation::select(std::vector<selectParam*> sp) {
	//std::set<Tuple>::iterator tupleIt = relationTuples.begin();
	for (auto tupleIt = relationTuples.begin(); tupleIt != relationTuples.end();) {
		bool found = false;
		for (auto& s : sp) {
			if (tupleIt == relationTuples.end()) break;
			if (!(s->isSelected(*tupleIt))) {
				found = true;
				tupleIt = relationTuples.erase(tupleIt);
				break;
			}
		}
		if (!found) {
			tupleIt++;
		}
	}
}

// CURRENTLY USING ORIGINAL
void Relation::rename(const std::vector<size_t>& indeces, const Predicate& query) {
	for (size_t i = 0; i < indeces.size(); i++) {
		//relationScheme.setScheme(i, query.paramaterList.at(i).getValue());
		relationScheme.setScheme(i, query.paramaterList.at(indeces.at(i)).getValue());
	}
}

void Relation::rename(Relation& givenRelation) {
	for (size_t i = 0; i < givenRelation.relationScheme.getSize(); i++) {
		relationScheme.setScheme(i, givenRelation.relationScheme.getScheme(i));
	}
}

//vector of indeces is indeces you want to keep.
Relation Relation::project(std::vector<size_t> indeces) {
	//set Name
	Relation newRelation(this->relationName);

	//add Schema
	for (size_t i = 0; i < indeces.size(); i++) {
		newRelation.relationScheme.addSchema(this->relationScheme.getScheme(indeces.at(i)));
	}

	//add tuples
	Tuple tuple;
	for (auto t : relationTuples) {
		for (size_t i = 0; i < indeces.size(); i++) {
			if (i < t.size()) {
				tuple.push_back(t.at(indeces.at(i)));
			}
		}
		newRelation.addTuple(tuple);
		tuple.clear();
	}

	return newRelation;
}

std::string Relation::toString() {
	std::stringstream ss;
	ss << "\nScheme:" << relationScheme.getSchemaList()->toString() << std::endl << "Tuples:" << std::endl;
	for (auto& t : relationTuples) {
		ss << "\t" << t.toString() << std::endl;
	}
	return ss.str();
}