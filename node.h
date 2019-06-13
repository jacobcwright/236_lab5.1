#ifndef NODE_H
#define NODE_H
#include "rules.h"
#include <vector>

class Node {
public:
    int ID;
    std::vector<Node> edges;
	std::vector<Node> reverseEdges;
    Rules rule;
    bool visited;
    Node(int givenID, Rules& givenRule){
        ID = givenID;
        rule = givenRule;
        visited = false;
    }
    Node(){
        ID = INT8_MIN;
        visited = false;
    }
	//Node() {}
    ~Node(){
        edges.clear();
    }
};

#endif // end node.h