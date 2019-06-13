#ifndef COMMENT_H
#define COMMENT_H
#include "automata.h"

class Comment : public Automaton {
private:
	int s0(size_t i, const std::string& input) const {
		if (i >= input.size()) {
			throw input;
		}
		const auto& c = input.at(i);
		if (i < input.size() && c == '#') {
			if (input.at(i + 1) == '|') {
				return multi1(i + 2, input);
			}
			return single1(++i, input);
		}
		return 0;
	}

	int single1(size_t i, const std::string& input) const {
		const auto& c = input.at(i);
		if (i < input.size() && c != '\n') {
			return single1(++i, input);
		}
		return i;
	}

	int multi1(size_t i, const std::string& input) const {
		if (i >= input.size()) {
			throw input;
		}
		const auto& c = input.at(i);
		if (i < input.size() && c == '|') {
			return multi2(++i, input);
		}
		return multi1(++i, input);
	}

	int multi2(size_t i, const std::string& input) const {
		if (i >= input.size()) {
			throw input;
		}
		const auto& c = input.at(i);
		if (i < input.size() && c == '#') {
			return ++i;
		}
		else if (i < input.size() && c == '|') {
			return multi2(++i, input);
		}
		return multi1(++i, input);
	}

public:
	int read(const std::string& input) const {
		return s0(0, input);
	}

	Token makeToken(std::string s, size_t givenLine) const {
		if (s.back() == '\r') {
			s.pop_back();
		}
		return Token(COMMENT, s, givenLine);
	}
};

#endif //end Comment.h