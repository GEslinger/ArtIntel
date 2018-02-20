#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <functional>
using namespace std;

vector<string> split(const string &s, char delim) {	// Split a string with a character delimiter
    stringstream ss(s);
    string item;
    vector<string> tokens;
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}

vector<double> getAvgVec(vector<vector<string>> data, int cols, int rowStart, int rowStop){	// Average a series of vectors
	vector<double> avgsum;								// Vector holding the sum
	for(int j = 0; j < cols; j++){						// Initialize with zeroes
		avgsum.push_back(0);
	}

	for(int i = rowStart; i < rowStop; i++){			// Sum up every column
		for(int j = 0; j < cols; j++){
			avgsum[j] += stod(data[i][j]);
		}
	}

	double correction = 1./(double)(rowStop-rowStart);	// Correction (division by n)

	for(int i = 0; i < cols; i++){
		avgsum[i] *= correction;						// Correct each element
	}

	return avgsum;
}

double getEulerDist(vector<double>& v1, vector<double>& v2){	// Euler distance algorithm
	double diffsq = 0;
	for(int i = 0; i < v1.size(); i++){
		diffsq += pow(v1[i]-v2[i],2);
	}

	return sqrt(diffsq);
}
double getManDist(vector<double>& v1, vector<double>& v2){		// Manhattan distance algorithm
	double diff = 0;
	for(int i = 0; i < v1.size(); i++){
		diff += v1[i]-v2[i];
	}

	return fabs(diff);
}
double getChebyDist(vector<double>& v1, vector<double>& v2){	// Chebyshev distance algorithm
	vector<double> diff;
	for(int i = 0; i < v1.size(); i++){
		diff.push_back(fabs(v1[i]-v2[i]));
	}

	double maxdiff = diff[0];
	for(double i : diff){
		if(i > maxdiff){
			maxdiff = i;
		}
	}

	return maxdiff;
}

vector<double> toVecDouble(vector<string> vs, int cols){		// Turn a vector of strings into a vector of doubles
	vector<double> out;
	for(int i = 0; i < cols; i++){
		out.push_back(stod(vs[i]));
	}
	return out;
}

double testClassify(vector<double> v1, vector<double> v2, vector<double> v3, vector<vector<string>> data, int rowStart, int rowStop, int cols, int correct, function<double(vector<double>&,vector<double>&)> f){
														// Function to perform a bunch of classifications
	double numRight = 0;								// Keep track of # correctly guessed
	for(int i = rowStart; i < rowStop; i++){			// Loop through the test rows
		vector<double> d = toVecDouble(data[i],cols);	// Turn the row into doubles
		double d1 = f(v1,d);							// Find the distance compared to the 3 clusters
		double d2 = f(v2,d);
		double d3 = f(v3,d);

		if(d1 <= d2 && d1 <= d3 && correct == 0){		// If it matches which should be correct, increase numRight
			numRight++;
		}
		if(d2 <= d1 && d2 <= d3 && correct == 1){
			numRight++;
		}
		if(d3 <= d1 && d3 <= d2 && correct == 2){
			numRight++;
		}
	}

	return numRight/(double)(rowStop-rowStart);			// Return the proportion of correctly identified
}

