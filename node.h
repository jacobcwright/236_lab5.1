#ifndef NODE_H
#define NODE_H
#include "rules.h"
#include <vector>

class Node {
public:
    int ID;
    std::vector<Node*> edges;
	std::vector<Node*> reverseEdges;
    Rules rule;
    bool reverseVisited;
	bool forwardVisited;
    Node(int givenID, Rules& givenRule){
        ID = givenID;
        rule = givenRule;
        reverseVisited = false;
		forwardVisited = false;
    }
    Node(){
        ID = INT8_MIN;
        reverseVisited = false;
		forwardVisited = false;
    }
	//Node() {}
    ~Node(){
		/*for (size_t i = 0; i < edges.size(); i++) {
			if (edges.at(i) != nullptr) {
				delete edges.at(i);
			}
		}
		for (size_t i = 0; i < reverseEdges.size(); i++) {
			if (reverseEdges.at(i) != nullptr) {
				delete reverseEdges.at(i);
			}
		}*/
        edges.clear();
		reverseEdges.clear();
    }
};

#endif // end node.h