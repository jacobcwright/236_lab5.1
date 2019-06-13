#ifndef GRAPH_H
#define GRAPH_H
#include "node.h"
#include <map>
#include <string>
#include <sstream>
#include <stack>
#include <set>


class Graph : public std::map<int, Node>{
private:
	std::stack<int> dfsReverseRecursive(Node& n, std::stack<int>&);
	std::vector<std::set<int>> dfsRecursive(std::stack<int>);
public:
    Graph() : map<int, Node>(){}
    ~Graph(){}
    std::string toString()const;
	std::string toStringReverse()const;
	std::string topToString(std::stack<int>);
	std::vector<std::set<int>> dfs(std::stack<int>);
	std::stack<int> dfsReverse();


};

#endif //graph.h