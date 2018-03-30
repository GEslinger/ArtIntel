#include "AStar.hpp"
#include <vector>
#include <fstream>
#include <cmath>
#include <iostream>
using namespace std;


double getEulerDist(vector<int> a, vector<int> b){
	if(a.size() != b.size()){
		return 0;
	}

	double sum = 0;
	for(int i = 0; i < a.size(); i++){
		sum += pow(a[i]-b[i],2);
	}
	return sqrt(sum);
}

AStar::AStar(string fname, vector<int> iPos, vector<int> goal){
	ifstream in(fname);
	string line;

	while(in.is_open() && getline(in,line)){
		maze.push_back(vector<int>());
		explored.push_back(vector<int>());
		for(int i = 0; i < line.length(); i++){
			maze.back().push_back((int)(line[i]-'0'));
			explored.back().push_back(0);
		}
	}

	// cout << endl << maze[2][177] << endl;

	// for(int i = 0; i < maze.size(); i++){
	// 	for(int j = 0; j < maze[i].size(); j++){
	// 		cout << maze[i][j];
	// 	}
	// 	cout << endl;
	// }

	// cout << "next" << flush;

	Node* start = new Node(NULL,0,getEulerDist(iPos,goal),iPos);
	path.push(start);

	in.close();

	begin = iPos;
	end = goal;
}

AStar::~AStar(){
	while(path.size() > 0){
		delete path.top();
		path.pop();
	}

	for(int i = 0; i < oldNodes.size(); i++){
		delete oldNodes[i];
	}
}

vector<vector<int>> AStar::getPath(){
	Node* n = path.top();
	int x = n->val[1];
	int y = n->val[0];

	int steps = 0;
	// cout << "starting\n";

	while(n->val != end ){

		addNode(n,vector<int>{y,(x+1)});
		addNode(n,vector<int>{(y+1),x});
		addNode(n,vector<int>{y,(x-1)});
		addNode(n,vector<int>{(y-1),x});
		oldNodes.push_back(n);
		path.pop();
		path.reHeap();



		n = path.top();

		// n->print();
		x = n->val[1];
		y = n->val[0];
		steps++;
	}

	// cout << "solved\n" << flush;
	vector<vector<int>> crap = vector<vector<int>>();


	Node* pathTrace = n;
	do{
		maze[pathTrace->val[0]][pathTrace->val[1]] = 2;
		pathTrace = pathTrace->prev;
	}while(pathTrace->prev != NULL);


	for(int i = 0; i < maze.size(); i++){
		for(int j = 0; j < maze[i].size(); j++){
			cout << maze[i][j];
		}
		cout << endl;
	}


	return crap;
}

void AStar::addNode(Node* parent, vector<int> target){
	if(target[0] < 0 || target[0] > maze.size()-1){
		return;
	}
	if(target[1] < 0 || target[1] > maze[0].size()-1){
		return;
	}

	// cout << "Maze: " << maze[target[0]][target[1]] << endl;
	// cout << "Explored[" << target[0] << "][" << target[1] << "]: " << explored[target[0]][target[1]] << endl;

	if(maze[target[0]][target[1]] && !explored[target[0]][target[1]]){
		Node* newNode = new Node(parent,parent->pos+1,getEulerDist(target,end),target);
		path.push(newNode);
		explored[target[0]][target[1]] = 1;
		// cout << "Added node at " << target[0] << ", " << target[1] << endl;
	}
}