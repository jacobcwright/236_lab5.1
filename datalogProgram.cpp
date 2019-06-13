#include "datalogProgram.h"

/*
 * @brief  compares current Token's type and givenType
 * @note   iterator is always advanced prior to function call
 * @param  givenType: enum token
 * @retval None, throws if no match
 */
void datalogProgram::match(token givenType) {
	if (currentToken->getTokenType() != givenType) {
		throw *currentToken;
	}
	currentToken++;
}

void datalogProgram::myStringList() {
	switch (currentToken->getTokenType()) {
	case RIGHT_PAREN:
	case STRING:
		return;
	case COMMA:
		currentToken++;
		match(STRING);
		currentFact.stringList.push_back((currentToken - 1)->getTokenValue());
		myDomain.insert((currentToken - 1)->getTokenValue());
		myStringList();
		break;
	default:
		throw *currentToken;
	}
}

void datalogProgram::myQueryList() {
	switch (currentToken->getTokenType()) {
	case END:
		return;
	case Q_MARK:
		currentToken++;
		return;
	case IDENTIFIER:
		myQuery();
		myQueryList();
		break;
	default:
		throw *currentToken;
	}
}
void datalogProgram::myQuery() {
	switch (currentToken->getTokenType()) {
	case IDENTIFIER:
		myPredicate();
		match(Q_MARK);
		myQueries.push_back(currentPredicate);
		currentPredicate.clear();
		break;
	default:
		throw *currentToken;
	}
}

void datalogProgram::myOperator() {
	switch (currentToken->getTokenType()) {
	case ADD:
		currentToken++;
		helper += "+";
		break;
	case MULTIPLY:
		currentToken++;
		helper += "*";
		break;
	default:
		throw *currentToken;
	}
}

void datalogProgram::myExpression() {
	switch (currentToken->getTokenType()) {
	case LEFT_PAREN:
		helper += "(";
		currentToken++;
		myParameter();
		helper += currentParameter.getValue();
		myOperator();
		myParameter();
		helper += currentParameter.getValue();
		match(RIGHT_PAREN);
		helper += ")";
		break;
	default:
		throw *currentToken;
	}
}

void datalogProgram::myParameterList() {
	switch (currentToken->getTokenType()) {
	case STRING:
	case IDENTIFIER:
	case RIGHT_PAREN:
		return;
	case COMMA:
		currentToken++;
		myParameter();
		currentPredicate.paramaterList.push_back(currentParameter); //###############
		myParameterList();
		break;
	default:
		throw *currentToken;
	}
}

void datalogProgram::myParameter() {
	switch (currentToken->getTokenType()) {
	case STRING:
		currentParameter.setValue(currentToken->getTokenValue(), true);
		currentToken++;
		return;
	case IDENTIFIER:
		currentParameter.setValue(currentToken->getTokenValue(), false);
		currentToken++;
		return;
	case LEFT_PAREN:
		myExpression();
		currentParameter.setValue(helper, EXPRESSION);
		helper = "";
		break;
	default:
		throw *currentToken;
	}
}

void datalogProgram::myPredicateList() {
	switch (currentToken->getTokenType()) {
	case PERIOD:
	case RIGHT_PAREN:
		return;
	case COMMA:
		currentToken++;
		myPredicate();
		currentPredicate.clear();
		myPredicateList();
		break;
	default:
		throw *currentToken;
	}
}

void datalogProgram::myPredicate() {
	switch (currentToken->getTokenType()) {
	case IDENTIFIER:
		currentPredicate.setID(currentToken->getTokenValue());
		currentToken++;
		match(LEFT_PAREN);
		myParameter();
		currentPredicate.paramaterList.push_back(currentParameter);
		currentParameter.clear();
		myParameterList();
		match(RIGHT_PAREN);
		currentRule.predicateList.push_back(currentPredicate);
		break;
	default:
		throw *currentToken;
	}
}

void datalogProgram::myHeadPredicate() {
	switch (currentToken->getTokenType()) {
	case IDENTIFIER:
		currentPredicate.setID((currentToken)->getTokenValue());
		currentToken++;
		match(LEFT_PAREN);
		match(IDENTIFIER);
		currentPredicate.paramaterList.push_back(((currentToken - 1)->getTokenValue()));
		myIdList();
		match(RIGHT_PAREN);
		currentRule.setHead(currentPredicate);
		currentPredicate.clear();
		break;
	default:
		throw *currentToken;
	}
}

void datalogProgram::myRuleList() {
	switch (currentToken->getTokenType()) {
	case QUERIES:
	case PERIOD:
		return;
	case IDENTIFIER:
		myRule();
		myRuleList();
		break;
	default:
		throw *currentToken;
	}
}

void datalogProgram::myRule() {
	switch (currentToken->getTokenType()) {
	case IDENTIFIER:
		myHeadPredicate();
		match(COLON_DASH);
		myPredicate();
		currentPredicate.clear();
		myPredicateList();
		currentPredicate.clear();
		match(PERIOD);
		myRules.push_back(currentRule);
		currentRule.clear();
		break;
	default:
		throw *currentToken;
	}
}

void datalogProgram::myFactList() {
	switch (currentToken->getTokenType()) {
	case RULES:
	case PERIOD:
		return;
	case IDENTIFIER:
		myFact();
		myFactList();
		break;
	default:
		throw *currentToken;
	}
}

void datalogProgram::myFact() {
	switch (currentToken->getTokenType()) {
	case IDENTIFIER:
		currentFact.setID(currentToken->getTokenValue());
		currentToken++;
		match(LEFT_PAREN);
		match(STRING);
		currentFact.stringList.push_back((currentToken - 1)->getTokenValue());
		myDomain.insert((currentToken - 1)->getTokenValue());
		myStringList();
		match(RIGHT_PAREN);
		match(PERIOD);
		myFacts.push_back(currentFact);
		currentFact.clear();
		break;
	default:
		throw *currentToken;
	}
}

void datalogProgram::myIdList() {
	switch (currentToken->getTokenType()) {
	case RIGHT_PAREN:
		return;
	case COMMA:
		currentToken++;
		match(IDENTIFIER);
		currentPredicate.add((currentToken - 1)->getTokenValue());
		myIdList();
		break;
	default:
		throw *currentToken;
	}
}

void datalogProgram::mySchemeList() {
	switch (currentToken->getTokenType()) {
	case IDENTIFIER:
		myScheme();
		mySchemeList();
		break;
	case FACTS:
	case RIGHT_PAREN:
		return;
	default:
		throw *currentToken;
	}
}

void datalogProgram::myScheme() {
	switch (currentToken->getTokenType()) {
	case IDENTIFIER:
		currentPredicate.setID((currentToken)->getTokenValue());
		currentToken++;
		match(LEFT_PAREN);
		match(IDENTIFIER);
		currentPredicate.add((currentToken - 1)->getTokenValue());
		myIdList();
		match(RIGHT_PAREN);
		mySchema.push_back(currentPredicate);
		currentPredicate.clear();
		break;
	default:
		throw *currentToken;
	}
}

void datalogProgram::myDatalog() {
	switch (currentToken->getTokenType()) {
	case SCHEMES:
		currentToken++;
		match(COLON);
		myScheme();
		mySchemeList();
		match(FACTS);
		match(COLON);
		myFactList();
		match(RULES);
		match(COLON);
		myRuleList();
		match(QUERIES);
		match(COLON);
		myQuery();
		myQueryList();
		break;
	default:
		throw *currentToken;
	}
}

bool datalogProgram::parse() {
	try {
		datalogProgram::myDatalog();
		return true;
	}
	catch (Token e) {
		std::cout << "Failure!\n    " << e << std::endl;
		return false;
	}
}

std::string datalogProgram::schemeString() {
	std::stringstream ss;
	ss << "Schemes(" << mySchema.size() << "):" << std::endl;
	for (const auto& s : mySchema) {
		ss << "    " << s << "(";
		for (const auto& p : s.paramaterList) {
			if (p.getValue() == s.paramaterList.back().getValue()) {
				ss << p << ")" << std::endl;
				break;
			}
			ss << p << ",";
		}
	}
	return ss.str();
}

std::string datalogProgram::queryString() {
	std::stringstream ss;
	ss << "Queries(" << myQueries.size() << "):" << std::endl;
	for (const auto& q : myQueries) {
		ss << "    " << q << "(";
		for (const auto& p : q.paramaterList) {
			if (p.getValue() == q.paramaterList.back().getValue()) {
				ss << p << ")?" << std::endl;
				break;
			}
			ss << p << ",";
		}
	}
	return ss.str();
}

std::string datalogProgram::toString() {
	std::stringstream ss;

	ss << schemeString();

	ss << "Facts(" << myFacts.size() << "):" << std::endl;
	for (const auto& f : myFacts) {
		ss << "    " << f << "(";
		for (const auto& s : f.stringList) {
			if (s == f.stringList.back()) {
				ss << s << ")." << std::endl;
				break;
			}
			ss << s << ",";
		}
	}

	ss << "Rules(" << myRules.size() << "):" << std::endl;
	for (const auto& r : myRules) {
		ss << "    " << r << std::endl;
	}

	ss << queryString();

	ss << "Domain(" << myDomain.size() << "):" << std::endl;
	for (const auto& d : myDomain) {
		ss << "    " << d << std::endl;
	}

	return ss.str();
}