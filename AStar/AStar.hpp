#ifndef ASTAR_H
#define ASTAR_H
#include "Node.hpp"
#include "pQueue.hpp"
#include <vector>
#include <string>

class AStar{
public:
	AStar(std::string fname, std::vector<int> iPos, std::vector<int> goal);
	~AStar();
	std::vector<std::vector<int>> getPath();
private:
	void addNode(Node* parent, std::vector<int> pos);
	std::vector<int> begin;
	std::vector<int> end;
	std::vector<std::vector<int>> maze;
	std::vector<std::vector<int>> explored;
	pQueue<Node*> path;
	std::vector<Node*> oldNodes;
};

#endif