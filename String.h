#ifndef STRING_H
#define STRING_H
#include "automata.h"

class String : public Automaton {
private:
	int s0(size_t i, const std::string& input) const {
		const auto& c = input.at(i);
		if (i < input.size() && c == '\'') {
			return s1(++i, input);
		}
		return 0;
	}

	int s1(size_t i, const std::string& input) const {
		if (i == input.size()) {
			throw input;
		}
		const auto& c = input.at(i);
		if (i < input.size() && (c != '\'')) {
			return s1(++i, input);
		}
		return s2(++i, input);
	}

	int s2(size_t i, const std::string& input) const {
		if (i == input.size()) {
			throw input;
		}
		const auto& c = input.at(i);
		if (i < input.size() && (c == '\'')) {
			return s1(++i, input);
		}
		return i;
	}

public:
	int read(const std::string& input) const {
		return s0(0, input);
	}
	Token makeToken(const std::string s, size_t givenLine) const {
		return Token(STRING, s, givenLine);
	}
};

#endif //end String.h