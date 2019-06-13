#ifndef WHITESPACE_H
#define WHITESPACE_H
#include "automata.h"

class Whitespace : public Automaton {
public:
	int read(const std::string& input) const {
		size_t i = 0;
		while (isspace(input.at(i))) {
			i++;
			if (i >= input.size()) {
				return i;
			}
		}
		return i;
	}
	Token makeToken(const std::string s, size_t givenLine) const {
		// std::cout << "(Whitespace,\"" << s << "\",#)" << std::endl;
		return Token(WHITESPACE, s, givenLine);
	}
};

#endif // end Whitespace.h