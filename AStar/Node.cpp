#include "Node.hpp"
#include <vector>
#include <cstring>
#include <iostream>
using namespace std;

Node::Node(Node* p, int ps, double d, vector<int> v){
	prev = p;
	pos = ps;
	dist = d;
	val = v;
}

Node::Node(const Node& copy){
	prev = copy.prev;
	pos = copy.pos;
	dist = copy.dist;
	val = vector<int>();
	std::copy(copy.val.begin(),copy.val.end(),val.begin());
}

void Node::bury(){
	dist = 100000;
	pos = 100000;
}

void Node::print(){
	cout << pos << "\t";
	cout << dist << "\t";
	cout << val[0] << "\t" << val[1] << endl;
}