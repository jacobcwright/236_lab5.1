#ifndef DATALOGPROGRAM_H
#define DATALOGPROGRAM_H
#include "token.h"
#include "facts.h"
#include "rules.h"
#include "predicate.h"
#include "expressions.h"
#include <set>
#include <vector>
#include <iterator>
#include <sstream>

class datalogProgram {
private:
	std::vector<Token> tokens;
	std::vector<Token>::iterator currentToken;

	// functions for parse table
	void myDatalog();
	void myScheme();
	void mySchemeList();
	void myIdList();
	void myFact();
	void myFactList();
	void myRule();
	void myRuleList();
	void myHeadPredicate();
	void myPredicate();
	void myPredicateList();
	void myParameter();
	void myParameterList();
	void myExpression();
	void myOperator();
	void myQuery();
	void myQueryList();
	void myStringList();
	void match(token);
	bool myCompare();
	std::string schemeString();

	std::string helper;
	Rules currentRule;
	Predicate currentPredicate;
	Parameter currentParameter;
	Expressions currentExpression;
	Facts currentFact;

public:
	std::vector<Predicate> mySchema;
	std::vector<Facts> myFacts;
	std::vector<Rules> myRules;
	std::vector<Predicate> myQueries;
	std::set<std::string> myDomain;

	datalogProgram(std::vector<Token>& givenTokens) {
		tokens = givenTokens;
		currentToken = tokens.begin();
	}

	~datalogProgram() {}

	/*
	 * @brief  Parse through vector of tokens
	 * @retval bool
	 */
	bool parse();
	std::string toString();
	std::string queryString();
};

#endif // end datalogProgram.h