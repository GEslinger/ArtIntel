#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// bool ratioColumns[] = {1,0,1,1,1,1,0,0,0,0};
// const int dataCols = 5;
// const int dataRows = 392;


// class KMeans{

// }

class Observation{
public:
	Observation(vector<double> iVal);
	double eulerDist(Observation& o) const;
	double eulerDist(vector<double> o) const;
	int getSize() const;
	vector<double> getVal() const;
private:
	vector<double> val;
};

Observation::Observation(vector<double> iVal){
	val = iVal;
}

double Observation::eulerDist(Observation& o) const {
	if(o.getSize() != this->getSize()) return 0;

	vector<double> v = o.getVal();

	double sum = 0;
	for(int i = 0; i < this->getSize(); i++){
		sum += pow(val[i]-v[i], 2);
	}

	return sqrt(sum);
}

double Observation::eulerDist(vector<double> v) const {
	if(v.size() != this->getSize()) return 0;

	double sum = 0;
	for(int i = 0; i < this->getSize(); i++){
		sum += pow(val[i]-v[i], 2);
	}

	return sqrt(sum);
}

int Observation::getSize() const {
	return val.size();
}

vector<double> Observation::getVal() const {
	return val;
}

class Cluster{
public:
	Cluster();
	bool addObs(int ob);
	bool remObs(int ob);
	void findCentroid(vector<Observation>& obs);
	vector<double> getCentroid() const;
private:
	vector<double> centroid;
	vector<int> obsHeld; 
};

Cluster::Cluster(){}

bool Cluster::addObs(int ob){
	for(int i = 0; i < obsHeld.size(); i++){
		if(obsHeld[i] == ob) return false;
	}
	obsHeld.push_back(ob);
	return true;
}

bool Cluster::remObs(int ob){
	for(int i = 0; i < obsHeld.size(); i++){
		if(obsHeld[i] == ob){
			obsHeld.erase(obsHeld.begin()+i);
			return true;
		}
	}
	return false;
}

void Cluster::findCentroid(vector<Observation>& obs){
	vector<double> avgPos;
	for(int i = 0; i < obs[0].getSize(); i++){
		avgPos.push_back(0);
	}

	for(int i = 0; i < obs.size(); i++){
		vector<double> v = obs[i].getVal();
		for(int j = 0; j < v.size(); j++){
			avgPos[j] += v[j]; 
		}
	}

	for(int i = 0; i < obs[0].getSize(); i++){
		avgPos[i] /= obs[0].getSize();
	}

	centroid = avgPos;
}

vector<double> Cluster::getCentroid() const{
	return centroid;
}



class KMeans{
public:
	KMeans(int c, vector<Observation>& o);
	~KMeans();
	void assignRandom();
	bool cluster();
	void printClusters() const;
private:
	vector<Observation> obs;
	vector<int> clsHeld;
	vector<Cluster*> cls;
	// int size;
};

KMeans::KMeans(int c, vector<Observation>& o){
	if(c > o.size()){
		cerr << "Too many clusters\n";
		exit(1);
	} else if (c < 1){
		cerr << "Too few clusters\n";
		exit(1);
	}
	// size = c;

	for(int i = 0; i < o.size(); i++){
		if(obs[i].getSize() != obs[0].getSize()){
			cerr << "Inconsistent observations\n";
			exit(1);
		}
	}
	obs = o;

	for(int i = 0; i < c; i++){
		Cluster* c = new Cluster();
		cls.push_back(c);
	}

	for(int i = 0; i < obs.size(); i++){
		clsHeld.push_back(-1);
	}
}

KMeans::~KMeans(){
	for(int i = 0; i < cls.size(); i++){
		delete cls[i];
	}
}

void KMeans::assignRandom(){
	vector<Observation> obsLeft = obs;
	int num = 0;
	while(true){
		int r = rand()%obsLeft.size();
		cls[num]->addObs(r);
		clsHeld.erase(clsHeld.begin()+r);
		clsHeld.insert(clsHeld.begin()+r,num);

		num %= cls.size();
	}
}

bool KMeans::cluster(){
	bool done = true;

	for(int i = 0; i < cls.size(); i++){
		cls[i]->findCentroid(obs);
	}

	for(int i = 0; i < obs.size(); i++){
		int closest = 0;
		for(int j = 0; j < cls.size(); j++){
			double testDist = obs[i].eulerDist(cls[j]->getCentroid());
			double bestDist = obs[i].eulerDist(cls[closest]->getCentroid());
			if(testDist < bestDist){
				closest = j;
			}
		}
		if(closest != clsHeld[i]){
			done = false;
		}
		if(!cls[clsHeld[i]]->remObs(i)) return true;
		if(!cls[closest]->addObs(i)) return true;
		clsHeld.erase(clsHeld.begin()+i);
		clsHeld.insert(clsHeld.begin()+i,closest);
	}

	return done;
}

void KMeans::printClusters() const{
	for(int i = 0; i < cls.size(); i++){
		cout << "Cluster " << i+1 << ":\n";
		vector<double> v = cls[i]->getCentroid();
		for(int j = 0; j < v.size(); j++){
			cout << v[j] << "\t";
		}
		cout << endl;
	}
}


int main(){
	// DataSet hello("cars.csv",dataCols,dataRows,ratioColumns);
	// hello.printData();
	vector<Observation> data;

	ifstream in("cars.csv");
	string line;

	if(in.is_open() && getline(in,line)){			// Import first line from file, which should contain titles
	}

	vector<vector<string>> dataStr;
	while(in.is_open() && getline(in,line)){		// Import remaining lines, split along commas, into data matrix
		stringstream ss << line;
		dataStr.push_back(getlines(ss,line,','));

	}

	in.close();	// Don't forget to close

	for(int i = 0; i < dataStr[0].size(); i++){
		dataStr[i].resize(6);
		vector<double> nums;
		for(int j = 0; j < dataStr[i].size(); j++){
			nums.push_back(stod(dataStr[i][j]));
		}
		Observation o(nums);
		data.push_back(o);
	}

	KMeans(3,data);
	

	// invalid_argument
	return 0;
}