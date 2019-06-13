#include <fstream>
#include <vector>
#include "StringMatch.h"
#include "Whitespace.h"
#include "Identifier.h"
#include "String.h"
#include "Comment.h"
#include "datalogProgram.h"
#include "scheme.h"
#include "tuples.h"
#include "relations.h"
#include "Interpreter.h"
using namespace std;

void countLine(size_t& line, const string& input) {
	for (auto s : input) {
		if (s == '\n') {
			line++;
		}
	}
}

void generateTokens(const vector<Automaton*>& machines, string& input, vector<Token>& tokens) {
	static size_t line = 1;
	while (input.size() > 0) {
		try {
			int max = 0;
			Automaton* maxAutomaton = nullptr;
			for (const auto& m : machines) {
				int i = m->read(input);
				if (i > max) {
					max = i;
					maxAutomaton = m;
				}
			}

			if (max > 0) {
				Token newToken = maxAutomaton->makeToken(input.substr(0, max), line);
				if (newToken.getTokenType() != WHITESPACE && newToken.getTokenType() != COMMENT) {
					tokens.push_back(newToken);
				}
				countLine(line, input.substr(0, max));
				input.erase(0, max);
			}
			else {
				string s;
				s.push_back(input.at(0));
				tokens.push_back(Token(UNDEFINED, s, line));
				input.erase(input.begin());
			}
		}
		catch (string e) {
			tokens.push_back(Token(UNDEFINED, e, line));
			countLine(line, input);
			input.erase(input.begin(), input.end());
		}
	}
	tokens.push_back(Token(END, "", line));
}

int main(int argc, char** argv) {
	ifstream in(argv[1]);
	string input;
	input.assign((istreambuf_iterator<char>(in)), (istreambuf_iterator<char>())); //write input file to input string

	vector<Token> tokens;
	vector<Automaton*> automata;

	automata.push_back(new StringMatch(",", COMMA));
	automata.push_back(new StringMatch(".", PERIOD));
	automata.push_back(new StringMatch("?", Q_MARK));
	automata.push_back(new StringMatch("(", LEFT_PAREN));
	automata.push_back(new StringMatch(")", RIGHT_PAREN));
	automata.push_back(new StringMatch(":", COLON));
	automata.push_back(new StringMatch(":-", COLON_DASH));
	automata.push_back(new StringMatch("*", MULTIPLY));
	automata.push_back(new StringMatch("+", ADD));
	automata.push_back(new StringMatch("Schemes", SCHEMES));
	automata.push_back(new StringMatch("Facts", FACTS));
	automata.push_back(new StringMatch("Rules", RULES));
	automata.push_back(new StringMatch("Queries", QUERIES));
	automata.push_back(new Identifier());
	automata.push_back(new String());
	automata.push_back(new Comment());
	automata.push_back(new Whitespace());

	generateTokens(automata, input, tokens);

	Interpreter interp(tokens);
	interp.doEpicStuff();

	for (auto a : automata) {
		delete a;
	}

	return 0;
}