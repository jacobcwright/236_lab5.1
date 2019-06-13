#ifndef DATABASE_H
#define DATABASE_H
#include <map>
#include "scheme.h"
#include "relations.h"

/**
 * @brief  Map of relations and relation's name
 * @note   collection of tables, tables being relations
 * @retval None
 */
class Database {
	//map from string to relation* or relation&
	//when you get a relation, it should return a deep copy, and manipulate that one copy in select, project, rename. (saves time)
	// vector of relation selectParameters, or probably in interpreter.
	/*
		for(auto& kv : myMap){
			kv.first = key
			kv.second = value
		}
		//inserting:
		map["what you want to insert"] = new Relation();

		getting stuff out:
		relation R = map["key"]; or .at()

	*/
public:
	std::map<std::string, Relation> relationsMap;

	Database() {}

	void add(Relation newRelation) {
		relationsMap[newRelation.getName()] = newRelation;
	}

	Relation get(std::string str) {
		return relationsMap.at(str);
	}
};

#endif //end Database.h