#include "Interpreter.h"

Interpreter::Interpreter(std::vector<Token>& givenTokens) : dlp(givenTokens) {}

std::string Interpreter::toString() {
	return "";
}

std::string Interpreter::sccToString(std::vector<std::set<int>>& scc) {
	std::stringstream ss;
	ss << "Strongly Connected Components:" << std::endl;
	for (size_t i = 0; i < scc.size(); i++) {
		ss << "{";
		std::set<int>::iterator last = --(scc.at(i).end());
		for (std::set<int>::iterator it = scc.at(i).begin(); it != scc.at(i).end(); it++) {
			if (it == last) {
				ss << "R" << *it;
				break;
			}
			ss << "R" << *it << ", ";
		}
		ss << "}" << std::endl;
	}

	return ss.str();
}


void Interpreter::makeTuples() {
	for (auto r : dlp.myFacts) {
		Tuple temp(r);
		try {
			db.relationsMap[r.getID()].addTuple(temp);
		}
		catch (...) {
			std::cout << "FAIL" << std::endl;
		}
	}
}

void Interpreter::makeRelations() {
	for (auto r : dlp.mySchema) {
		Relation newRelation(r);
		db.add(newRelation);
	}
}

bool Interpreter::doEpicStuff() {
	// use datalogProgram to parse
	if (!dlp.parse()) return false;

	makeRelations();
	makeTuples();
	createGraph();

	//dfs reverse
	std::stack<int> post = myGraph.dfsReverse();

	//output topological ordering
	std::cout << std::endl << myGraph.topToString(post) << std::endl;

	//get SCC
	std::vector<std::set<int>> scc;
	scc = myGraph.dfs(post);

	//output SCC
	std::cout << sccToString(scc);

	//evaluateRules();
	//evaluate();

	return true;
}

std::string Interpreter::evaluateOne(Predicate givenQuery) {
	Relation copy = db.relationsMap[givenQuery.getID()];
	std::stringstream ss;
	createSelects(givenQuery);
	ss << givenQuery.toString();

	//select on relation object from database
	copy.select(selects);

	//project indeces on relation
	copy = copy.project(queryHelp);

	//rename
	copy.rename(queryHelp, givenQuery);

	size_t found = copy.getTupleSize();
	if (found > 0) {
		ss << " Yes(" << found << ")" << std::endl;

		for (size_t i = 0; i < found; i++) {
			if (copy.relationScheme.getSize() == 0) {
				break;
			}
			ss << "  ";
			for (size_t j = 0; j < copy.relationScheme.getSize(); j++) {
				if (j != copy.relationScheme.getSize() - 1) {
					ss << copy.relationScheme.getSchemaList()->at(j) << "=" << copy.getTuple(i).at(j) << ", ";
				}
				else {
					ss << copy.relationScheme.getSchemaList()->at(j) << "=" << copy.getTuple(i).at(j) << std::endl;
				}
			}
		}
	}
	else {
		ss << " No" << std::endl;
	}
	clearSelects();
	renameMap.clear();
	queryHelp.clear();

	return ss.str();
}

void Interpreter::createSelects(Predicate givenQuery) {
	for (size_t j = 0; j < givenQuery.paramaterList.size(); j++) {
		if (givenQuery.paramaterList.at(j).getConstant()) {
			//add to type1 select
			type1* tempSelect = new type1(givenQuery.paramaterList.at(j).getValue(), j);
			selects.push_back(tempSelect);
		}
		else {
			std::map<std::string, size_t>::iterator queryIt = renameMap.find(givenQuery.paramaterList.at(j).getValue());
			if (queryIt != renameMap.end()) {
				//type2 select
				type2* temp2Select = new type2(j, queryIt->second);
				selects.push_back(temp2Select);
			}
			else {
				//add to renameMap
				renameMap[givenQuery.paramaterList.at(j).getValue()] = j;
				//push back to queryHelp to keep
				queryHelp.push_back(j);
			}
		}
	}
}

void Interpreter::evaluate() {
	std::stringstream ss;
	for (size_t i = 0; i < dlp.myQueries.size(); i++) {
		ss << evaluateOne(dlp.myQueries.at(i));
	}
	std::string temp = ss.str();
	temp.pop_back();
	std::cout << temp;
}

/**
 * @brief takes in Predicate, evaluates, returns relation
 * @note
 * @retval None
 */
Relation Interpreter::evaluateRule(Predicate givenRule) {
	Relation copy = db.relationsMap[givenRule.getID()]; // ???
	createSelects(givenRule);

	//select on relation object from database
	copy.select(selects);

	//project indeces on relation
	copy = copy.project(queryHelp);

	//rename
	copy.rename(queryHelp, givenRule);

	clearSelects();
	renameMap.clear();
	queryHelp.clear();

	return copy;
}

/**
 * @brief  evaluates all rules
 * @note   adds relations to db
 * @retval None
 */
void Interpreter::evaluateRules() {
	/*
	1. Evaluate predicates on right-hand side of rule (calling evaluateRule).
	2. Join the resulting relations (natural join).
	3. Project the columns that appear in the head predicate.
	4. Rename the relation to match the one in the database so it is union compatible.
	5. Union relation with relation in Database.
	*/
	std::vector<Rules>& rules = dlp.myRules;
	/*std::vector<Relation> temps;
	Relation result;*/

	//evaluate predicates and store resulting relations
	int numAdded = 0;
	size_t loopNum = 0;
	do {
		if (rules.size() == 0) break;
		numAdded = 0;
		for (auto& r : rules) {
			std::vector<Relation> temps;
			Relation result;
			for (auto& p : r.predicateList) {
				result = evaluateRule(p);
				temps.push_back(result);
			}

			//join relations
			if (temps.size() > 0) {
				result = temps.at(0);
			}
			for (size_t i = 1; i < temps.size(); i++) {
				//result = result.naturalJoin(temps.at(i)); //joining incorrectly... adding into wrong column ?
				result = temps.at(i).naturalJoin(result);
			}

			//project columns that appear in the head predicate
			Predicate head = r.getHeadPred();
			std::vector<size_t> projectIndeces;
			for (size_t i = 0; i < head.paramaterList.size(); i++) {
				if (result.relationScheme.find(head.paramaterList.at(i).getValue()) != size_t(-1)) {
					projectIndeces.push_back(result.relationScheme.find(head.paramaterList.at(i).getValue()));
				}
			}
			result = result.project(projectIndeces);

			//rename
	//***GOT TO BE CAERFUL HERE, PASSED BY REFERENCE, AND GETS SOME NON-CONST FUNCTIONS CALLED ON IT***
			Relation& dbRelation = db.relationsMap[r.getHead().getID()];
			result.rename(dbRelation);

			//union
			//numAdded = 0;
			numAdded += dbRelation.Union(result);
		}
		loopNum++;
	} while (numAdded > 0);
	std::cout << "Schemes populated after " << loopNum << " passes through the Rules." << std::endl;
}

 /**
  * @brief creates dependencies for graph  
  * @note   
  * @retval None
  */
void Interpreter::createGraph(){
	std::vector<Rules>& rules = dlp.myRules;
	createNodes();	

	for(auto& r : rules){
		for(auto& p : r.predicateList){
			for(auto& r2 : rules){
				if(p.getID() == r2.getHead().getID() /*&& (p.toString() == r2.getHead().toString())*/){
					Node* temp = myGraph[r.graphID];
					Node* temp2 = myGraph[(r2.graphID)];
					temp->edges.push_back(temp2);
					temp2->reverseEdges.push_back(temp);
					/*myGraph[r.graphID].edges.push_back(myGraph[r2.graphID]);
					myGraph[r2.graphID].reverseEdges.push_back(myGraph[r.graphID]);*/
				}
			}	
		}
	}
	std::cout << myGraph.toString();
	std::cout << myGraph.toStringReverse();
}


 /**
  * @brief  creates node for dependency graph
  * @note   
  * @retval None
  */
void Interpreter::createNodes(){
	std::vector<Rules>& rules = dlp.myRules;
	
	//create nodes
	int counter = 0; 
	for(auto& r : rules){
		//set ID, and give pointer to rule
		Node* temp = new Node(counter, r);
		r.graphID = counter;

		//add Node to graph
		myGraph.insert(std::pair<int, Node*>(counter, temp));
		counter++;
	}
}