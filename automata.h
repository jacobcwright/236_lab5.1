/**
 * @brief  class definitions of Automaton (abstract), and StringMatch,
 *         which will be used as helper classes for automata.
 */
#ifndef AUTOMATA_H
#define AUTOMATA_H
#include "token.h"

 /**
  * @brief  base abstract automata class
  */
class Automaton {
public:
	virtual ~Automaton() {}
	virtual int read(const std::string&) const = 0;
	virtual Token makeToken(const std::string, size_t givenLine) const = 0;
	// virtual size_t getLineNum(const std::string&, const std::string) const = 0;
};

#endif //end AUTOMATA