#include "AStar.hpp"
#include <vector>
using namespace std;

int main(){
	AStar solveMaze("./Mazes/maze.dat",vector<int>{2,177},vector<int>{365,193});	// Warning: takes forever
	// AStar solveMaze("./Mazes/crap.dat",vector<int>{0,3},vector<int>{4,1});
	// AStar solveMaze("./Mazes/small.dat",vector<int>{12,3},vector<int>{20,34});

	solveMaze.getPath();
	return 0;
}