#include "graph.h"

//output graph
std::string Graph::toString()const{
    std::stringstream ss;
    ss << "Dependency Graph" << std::endl;
    for(size_t i = 0; i < this->size(); i++){
        ss << "R" << this->at(i)->ID << ":";
        if(this->at(i)->edges.size() == 0){
            ss << std::endl;
			continue;
        }
		std::set<Node*>::iterator last = --(this->at(i)->edges.end());
		for (std::set<Node*>::iterator j = this->at(i)->edges.begin(); j != this->at(i)->edges.end(); j++) {
            if(j == last){
                ss << "R" << (*j)->ID << std::endl;
                break;
            }
            ss << "R" << (*j)->ID << ",";
        }
    }
    return ss.str();
}

//output reverse graph
std::string Graph::toStringReverse() const {
	std::stringstream ss;
	ss << "\nReverse Dependency Graph" << std::endl;
	for (size_t i = 0; i < this->size(); i++) {
		ss << "R" << this->at(i)->ID << ":";
		if (this->at(i)->reverseEdges.size() == 0) {
			ss << std::endl;
			continue;
		}
		std::set<Node*>::iterator last = --(this->at(i)->reverseEdges.end());
		for (std::set<Node*>::iterator j = this->at(i)->reverseEdges.begin(); j != this->at(i)->reverseEdges.end(); j++) {
			if (j == last) {
				ss << "R" << (*j)->ID << std::endl;
				break;
			}
			ss << "R" << (*j)->ID << ",";
		}
	}
	return ss.str();
}

// do dfs on reverse graph
std::stack<int> Graph::dfsReverse() {
	std::stack<int> post;
	//Node* start = this->at(0);
	
	//mark as reverseVisited
	//start->reverseVisited = true;
	//
	for (map<int, Node*>::iterator it = this->begin(); it != end(); it++) {
		//if not already reverseVisited
		if (!it->second->reverseVisited) {
			//mark as reverseVisited
			it->second->reverseVisited = true;
			//iterate through all possible edges
			for (auto& n : it->second->reverseEdges) {
				//if not reverseVisited, visit
				if (!n->reverseVisited) {
					dfsReverseRecursive(n, post);
				}
			}
			//once all have been reverseVisited, add to stack
			post.push(it->second->ID);
		}
	}
	return post;
}

//recursive function for dfs on reverse graph
std::stack<int> Graph::dfsReverseRecursive(Node* n, std::stack<int>& post) {
	//mark as reverseVisited
	n->reverseVisited = true;

	//iterate through all possible edges
	for (auto& e : n->reverseEdges) {
		//if not reverseVisited, visit
		if (!e->reverseVisited) {
			dfsReverseRecursive(e, post);
		}
	}
	//once all have been reverseVisited, add to stack
	post.push(n->ID);
	return post;
}

//Function to output topological ordering after reverse dfs
std::string Graph::topToString(std::stack<int> post) {
	std::stringstream ss;
	size_t size = post.size();
	for (size_t i = 0; i < size; i++) {
		ss << "POTN(R" << post.top() << ") = " << (size - 1) - i << std::endl;
		post.pop();
	}
	return ss.str();
}

//dfs on original to get SCC
std::vector<std::set<int>> Graph::dfs(std::stack<int>& post) {
	std::vector<std::set<int>> SCC;
	std::set<int> tempSet;
	while (!post.empty()) {
		Node* n = this->at(post.top());
		post.pop();
		if (n->forwardVisited) {
			continue;
		}
		n->forwardVisited = true;
		for (auto& e : n->edges) {
			if (!e->forwardVisited) {
				dfsRecursive(e, tempSet);
			}
		}
		tempSet.insert(n->ID);
		SCC.push_back(tempSet);
		tempSet.clear();
	}
	return SCC;
}

//recursive function for DFS
void Graph::dfsRecursive(Node* n, std::set<int>& tempSet) {
	//forward visited = true
	n->forwardVisited = true;

	//iterate through all forward edges
	for (auto& e : n->edges) {
		//if not visited, visit
		if (!e->forwardVisited) {
			dfsRecursive(e, tempSet);
		}
	}
	//once all have been visited, add to SCC
	tempSet.insert(n->ID);
	return;
}
