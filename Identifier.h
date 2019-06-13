#ifndef IDENTIFIER_H
#define IDENTIFIER_H
#include "automata.h"

class Identifier : public Automaton {
private:
	//insert finite state automata
	int s0(size_t i, const std::string& input) const {
		const auto& c = input.at(i);
		if (i < input.size() && isalpha(c)) {
			return s1(++i, input);
		}
		return 0;
	}

	int s1(size_t i, const std::string& input) const {
		const auto& c = input[i];
		if (i < input.size() && (isalnum(c))) {
			return s1(++i, input);
		}
		return i;
	}

public:
	int read(const std::string& input) const {
		return s0(0, input);
	}
	Token makeToken(const std::string s, size_t givenLine) const {
		return Token(IDENTIFIER, s, givenLine);
	}
};

#endif // end Identifier.h