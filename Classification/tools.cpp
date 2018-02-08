#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
using namespace std;

vector<string> split(const string &s, char delim) {
    stringstream ss(s);
    string item;
    vector<string> tokens;
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}

vector<double> getAvgVec(vector<vector<string>> data, int cols, int rowStart, int rowStop){
	vector<double> avgsum;
	for(int j = 0; j < cols; j++){
		avgsum.push_back(0);
	}

	for(int i = rowStart; i < rowStop; i++){
		for(int j = 0; j < cols; j++){
			avgsum[j] += stod(data[i][j]);
		}
	}

	double correction = 1./(double)(rowStop-rowStart);

	for(int i = 0; i < cols; i++){
		avgsum[i] *= correction;
	}

	return avgsum;
}

double getEulerDist(vector<double> v1, vector<double> v2){
	double diffsq = 0;
	for(int i = 0; i < v1.size(); i++){
		// cout << "( " << v1[i] << " - " << v2[i] << " )^2 =" << pow(v1[i]-v2[i],2) << endl;
		diffsq += pow(v1[i]-v2[i],2);
	}
	// cout << "sum: " << diffsq << endl;
	// cout << "final: " << sqrt(diffsq) << endl << endl;

	return sqrt(diffsq);
}

vector<double> toVecDouble(vector<string> vs, int cols){
	vector<double> out;
	for(int i = 0; i < cols; i++){
		// cout << vs[i] << endl;
		out.push_back(stod(vs[i]));
	}
	return out;
}

double testClassify(vector<double> v1, vector<double> v2, vector<double> v3, vector<vector<string>> data, int rowStart, int rowStop, int cols, int correct){

	double numRight = 0;
	for(int i = rowStart; i < rowStop; i++){
		vector<double> d = toVecDouble(data[i],cols);
		double d1 = getEulerDist(v1,d);
		double d2 = getEulerDist(v2,d);
		double d3 = getEulerDist(v3,d);

		// cout << d1 << "\t" << d2 << "\t" << d3 << endl;
		if(d1 <= d2 && d1 <= d3 && correct == 0){
			numRight++;
		}
		else if(d2 <= d1 && d2 <= d3 && correct == 1){
			numRight++;
		}
		else if(d3 <= d1 && d3 <= d2 && correct == 2){
			numRight++;
		}
	}

	return numRight/(double)(rowStop-rowStart);
}