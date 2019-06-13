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
        for(size_t j = 0; j < this->at(i)->edges.size(); j++){
            if(j == this->at(i)->edges.size() - 1){
                ss << "R" << this->at(i)->edges.at(j)->ID << std::endl;
                break;
            }
            ss << "R" << this->at(i)->edges.at(j)->ID << ",";
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
		for (size_t j = 0; j < this->at(i)->reverseEdges.size(); j++) {
			if (j == this->at(i)->reverseEdges.size() - 1) {
				ss << "R" << this->at(i)->reverseEdges.at(j)->ID << std::endl;
				break;
			}
			ss << "R" << this->at(i)->reverseEdges.at(j)->ID << ",";
		}
	}
	return ss.str();
}

// do dfs on reverse graph
std::stack<int> Graph::dfsReverse() {
	std::stack<int> post;
	//Node* start = this->at(0);
	
	//mark as visited
	//start->visited = true;
	//
	for (map<int, Node*>::iterator it = this->begin(); it != end(); it++) {
		//if not already visited
		if (!it->second->visited) {
			//mark as visited
			it->second->visited = true;
			//iterate through all possible edges
			for (auto& n : it->second->reverseEdges) {
				//if not visited, visit
				if (!n->visited) {
					dfsReverseRecursive(n, post);
				}
			}
			//once all have been visited, add to stack
			post.push(it->second->ID);
		}
	}
	return post;
}

//recursive function for dfs on reverse graph
std::stack<int> Graph::dfsReverseRecursive(Node* n, std::stack<int>& post) {
	//mark as visited
	n->visited = true;

	//iterate through all possible edges
	for (auto& e : n->reverseEdges) {
		//if not visited, visit
		if (!e->visited) {
			dfsReverseRecursive(e, post);
		}
	}
	//once all have been visited, add to stack
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

