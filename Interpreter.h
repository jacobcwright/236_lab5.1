#ifndef INTERPRETER_H
#define INTERPRETER_H
#include <algorithm>
#include <sstream>
#include <stack>
#include "Database.h"
#include "datalogProgram.h"
#include "graph.h"
#include <fstream>

/**
 * @brief  Runs the program, fills relations and tuples
 * @note
 * @retval None
 */
class Interpreter {
private:
	// 2 data members datalogProgram and Database.
	datalogProgram dlp;
	Database db;
	Graph myGraph;
	//std::map<std::string, int> queryHelp;
	std::vector<size_t> queryHelp;
	std::vector<selectParam*> selects;
	std::map<std::string, size_t> renameMap;
	// runs datalogProgram then fills Database.
public:
	Interpreter(std::vector<Token>& givenTokens);
	~Interpreter() {
		for (size_t i = 0; i < selects.size(); i++) {
			delete selects.at(i);
		}
	}
	/**
	 * @brief  runs datalogProgram
	 * @note   epic
	 * @retval true/false (valid parse, invalid parse).
	 */
	bool doEpicStuff();
	void makeRelations();
	void makeTuples();
	void evaluate();
	std::string evaluateOne(Predicate givenQuery);
	void createSelects(Predicate);
	std::string toString();
	void clearSelects() {
		for (auto s : selects) {
			delete s;
		}
		selects.clear();
	}

	Relation evaluateRule(Predicate);
	void evaluateRules();
	void createGraph();
	void createNodes();
	std::string sccToString(std::vector<std::set<int>>&);

};

#endif // end Interpreter.h