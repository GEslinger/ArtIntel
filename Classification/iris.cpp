#include <iostream>
#include "DataTable.hpp"
using namespace std;

int main(){
	DataTable iris("data.csv");

	auto d = iris.getData();

	auto setosa = getAvgVec(d,4,0,40);
	auto versicolor = getAvgVec(d,4,50,90);
	auto virginica = getAvgVec(d,4,100,140);

	cout << "Averages vectors for each species\nSetosa:   \t";

	for(double d : setosa)
		cout << d << "\t";
	cout << "\nVersicolor:\t";
	for(double d : versicolor)
		cout << d << "\t";
	cout << "\nVirginica:\t";
	for(double d : virginica)
		cout << d << "\t";
	cout << "\n\nTesting classification on remaining data with Euler distance\n";

	cout << testClassify(setosa,versicolor,virginica,d,40,49,4,0,getEulerDist)*100 << "% correct for setosa\n";
	cout << testClassify(setosa,versicolor,virginica,d,90,99,4,1,getEulerDist)*100 << "% correct for versicolor\n";
	cout << testClassify(setosa,versicolor,virginica,d,140,149,4,2,getEulerDist)*100 << "% correct for virginica\n";


	cout << "\nTesting classification on remaining data with Euler distance\n";

	cout << testClassify(setosa,versicolor,virginica,d,40,49,4,0,getManDist)*100 << "% correct for setosa\n";
	cout << testClassify(setosa,versicolor,virginica,d,90,99,4,1,getManDist)*100 << "% correct for versicolor\n";
	cout << testClassify(setosa,versicolor,virginica,d,140,149,4,2,getManDist)*100 << "% correct for virginica\n";

	cout << "\nTesting classification on remaining data with Chebyshev distance\n";

	cout << testClassify(setosa,versicolor,virginica,d,40,49,4,0,getChebyDist)*100 << "% correct for setosa\n";
	cout << testClassify(setosa,versicolor,virginica,d,90,99,4,1,getChebyDist)*100 << "% correct for versicolor\n";
	cout << testClassify(setosa,versicolor,virginica,d,140,149,4,2,getChebyDist)*100 << "% correct for virginica\n";

	return 0;
}