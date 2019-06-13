#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <iostream>
#include <sstream>

enum token {
	COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON,
	COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, IDENTIFIER, STRING, COMMENT, WHITESPACE, UNDEFINED, END
};

class Token {
private:
	token tokenType;
	std::string value;
	int lineNum;
public:
	Token(token t) {
		tokenType = t;
	}
	Token(token t, std::string s, int num) {
		tokenType = t;
		value = s;
		lineNum = num;
	}
	Token() {}
	std::string toString() const {
		std::stringstream ss;
		switch (tokenType) {
		case COMMA:
			return "COMMA";
		case PERIOD:
			return "PERIOD";
		case Q_MARK:
			return "Q_MARK";
		case LEFT_PAREN:
			return "LEFT_PAREN";
		case RIGHT_PAREN:
			return "RIGHT_PAREN";
		case COLON:
			return "COLON";
		case COLON_DASH:
			return "COLON_DASH";
		case MULTIPLY:
			return "MULTIPLY";
		case ADD:
			return "ADD";
		case SCHEMES:
			return "SCHEMES";
		case FACTS:
			return "FACTS";
		case RULES:
			return "RULES";
		case QUERIES:
			return "QUERIES";
		case IDENTIFIER:
			return "ID";
		case STRING:
			return "STRING";
		case COMMENT:
			return "COMMENT";
		case WHITESPACE:
			return "WHITESPACE";
		case END:
			return "EOF";
		default:
			return "UNDEFINED";
		}
		return ss.str();
	}
	friend std::ostream& operator<< (std::ostream& os, const Token& token) {
		os << "(" << token.toString() << ",\"" << token.value << "\"," << token.lineNum << ")";
		return os;
	}

	token getTokenType() {
		return tokenType;
	}

	std::string getTokenValue() {
		return value;
	}
};

#endif // END TOKEN