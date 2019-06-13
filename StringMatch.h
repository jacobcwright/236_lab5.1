#ifndef STRINGMATCH_H
#define STRINGMATCH_H
#include "automata.h"

/**
 * @brief  class for reserved words: COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON,
 *         COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES
 *
 */
class StringMatch : public Automaton {
private:
	std::string stringToMatch;
	token tokenToMake;

public:
	StringMatch(const std::string s, token t) : stringToMatch(s), tokenToMake(t) {}

	/**
	 * @brief  compares input with string to match (keyword)
	 * @param  in: input string
	 * @retval INT, 0 if does not match keyword, keyword size if matches
	 */
	int read(const std::string& in) const {
		if (in.size() < stringToMatch.size()) {
			return 0;
		}

		int i = 0;
		for (const auto& c : stringToMatch) {
			if (c != in.at(i)) {
				return 0;
			}
			i++;
		}
		return stringToMatch.size();
	}

	/**
	 * @brief  outputs token
	 * @note
	 * @param  s: string of token value
	 * @retval returns token
	 */
	Token makeToken(const std::string s, size_t givenLine) const {
		// std::cout << "(" << tokenToMake.toString()  << ",\"" << s << "\",#)" << std::endl;
		// return tokenToMake;
		return Token(tokenToMake, s, givenLine);
	}
};

#endif // END StringMatch