#include <iostream>
#include "DataTable.hpp"
using namespace std;

int main(){
	DataTable iris("data.csv");

	auto d = iris.getData();

	auto setosa = getAvgVec(d,4,0,40);
	auto versicolor = getAvgVec(d,4,51,90);
	auto virginica = getAvgVec(d,4,101,140);

	for(double d : setosa)
		cout << d << "\t";
	cout << endl;
	for(double d : versicolor)
		cout << d << "\t";
	cout << endl;
	for(double d : virginica)
		cout << d << "\t";
	cout << endl;

	cout << testClassify(setosa,versicolor,virginica,d,41,50,4,0)*100 << "% correct for setosa\n";
	cout << testClassify(setosa,versicolor,virginica,d,91,100,4,1)*100 << "% correct for versicolor\n";
	cout << testClassify(setosa,versicolor,virginica,d,141,150,4,2)*100 << "% correct for virginica\n";

	// for(double d : setosa){
	// 	cout << d << "\t";
	// }
	// cout << endl;
	// for(double d : versicolor){
	// 	cout << d << "\t";
	// }
	// cout << endl;
	// for(double d : virginica){
	// 	cout << d << "\t";
	// }
	// cout << endl;

	return 0;
}