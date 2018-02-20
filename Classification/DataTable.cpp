#include <vector>
#include <fstream>
#include <string>
#include <utility>
#include "DataTable.hpp"
using namespace std;

DataTable::DataTable(string fname){					// Implementation of DataTable class
	ifstream in(fname);
	string line;

	if(in.is_open() && getline(in,line)){			// Import first line from file, which should contain titles
		vector<string> t = split(line,(char)44);	// Split along commas (csv format)
		titles = vector<string>(t.begin(),t.end());
	}


	while(in.is_open() && getline(in,line)){		// Import remaining lines, split along commas, into data matrix
		data.push_back(split(line,(char)44));
	}

	in.close();	// Don't forget to close
}

pair<int,int> DataTable::getDims(){						// Fun stuff
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