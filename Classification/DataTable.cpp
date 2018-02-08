#include <vector>
#include <fstream>
#include <string>
#include <utility>
#include "DataTable.hpp"
using namespace std;

DataTable::DataTable(string fname){
	ifstream in(fname);
	string line;

	if(in.is_open() && getline(in,line)){
		vector<string> t = split(line,(char)44);
		titles = vector<string>(t.begin(),t.end());
	}


	while(in.is_open() && getline(in,line)){
		data.push_back(split(line,(char)44));
	}

	in.close();
}

pair<int,int> DataTable::getDims(){
	return pair<int,int>(data.size(),data[0].size());
}

string DataTable::getPoint(int i, int j) const {
	return data[i][j];
}

vector<vector<string>> DataTable::getData() const {
	return data;
}

vector<string> DataTable::getTitles() const {
	return titles;
}