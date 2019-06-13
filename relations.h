#ifndef RELATIONS_H
#define RELATIONS_H
#include "predicate.h"
#include "scheme.h"
#include "tuples.h"
#include "type1Select.h"
#include "type2Select.h"
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <map>
#include <iostream>
#include <sstream>

/**
 * @brief
 * @note
 * @retval None
 */

class Relation {
private:
	std::string relationName;
	std::set<Tuple> relationTuples;

public:
	Scheme relationScheme;
	/**
	 * @brief  Relation Constructor
	 * @note
	 * @retval Relation object
	 */
	Relation(std::string givenName = "") {
		relationName = givenName;
		if (relationTuples.size() > 0) {
			std::cout << "GREATER THAN 0" << std::endl;
			relationTuples.clear();
		}
	}
	Relation(Predicate givenPred) {
		relationName = givenPred.getID();
		for (size_t i = 0; i < givenPred.paramaterList.size(); i++) {
			relationScheme.addSchema(givenPred.paramaterList.at(i).getValue());
		}
	}

	/**
	 * @brief  Relation Destructor
	 * @note
	 * @retval none
	 */
	~Relation() {}

	/**
	 * @brief  select operator
	 * @note
	 * @retval None
	 */
	void select(std::vector<selectParam*> sp);

	/**
	 * @brief  rename operator
	 * @note   renames to query
	 * @retval None
	 */
	 //void rename(std::map<std::string, size_t>& renameMap);
	void rename(const std::vector<size_t>& indeces, const Predicate& query);

	void rename(Relation& givenRelation);

	/**
	 * @brief  project operator
	 * @note   creates new relation and copies over corresponding columns
	 * @retval copy of relation
	 */
	Relation project(std::vector<size_t>);

	/**
	 * @brief  natural join operator
	 * @note
	 * @retval
	 */
	Relation naturalJoin(Relation&);
	Relation naturalJoin2(Relation&, Relation&);

	/**
	 * @brief  union operator
	 * @note
	 * @retval
	 */
	int Union(Relation&);

	std::string getName() { return relationName; }

	void addTuple(Tuple givenTuple) {
		relationTuples.insert(givenTuple);
	}
	size_t getTupleSize() {
		return relationTuples.size();
	}

	Tuple getTuple(size_t index) {
		std::set<Tuple>::iterator it = relationTuples.begin();
		std::advance(it, index);
		return *it;
	}

	void setTuples(std::set<Tuple> givenTuples) {
		relationTuples = givenTuples;
	}

	std::string toString();
};

#endif // end relations.h