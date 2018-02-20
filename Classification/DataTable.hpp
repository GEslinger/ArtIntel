#ifndef DATATABLE_H
#define DATATABLE_H

#include <string>
#include <vector>
#include <functional>


std::vector<std::string> split(const std::string &s, char delim);
std::vector<double> getAvgVec(std::vector<std::vector<std::string>> data, int cols, int rowStart, int rowStop);
double testClassify(std::vector<double> v1, std::vector<double> v2, std::vector<double> v3, std::vector<std::vector<std::string>> data, int rowStart, int rowStop, int cols, int correct, std::function<double(std::vector<double>&,std::vector<double>&)> f);
double getEulerDist(std::vector<double>& v1, std::vector<double>& v2);
double getManDist(std::vector<double>& v1, std::vector<double>& v2);
double getChebyDist(std::vector<double>& v1, std::vector<double>& v2);

class DataTable{											// DataTable class holds the information from the file
public:
	DataTable(std::string fname);
	std::pair<int,int> getDims();
	std::string getPoint(int i, int j) const;
	std::vector<std::vector<std::string>> getData() const;
	std::vector<std::string> getTitles() const;
private:
	std::vector<std::vector<std::string>> data;
	std::vector<std::string> titles;
};

#endif