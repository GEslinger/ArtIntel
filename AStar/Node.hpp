#ifndef NODE_H
#define NODE_H
#include <vector>

class Node{
public:
	Node(Node* p, int ps, double d, std::vector<int> v);
	Node(const Node& copy);
	void bury();
	void print();
	Node* prev;
	int pos;
	double dist;
	std::vector<int> val;
};

#endif