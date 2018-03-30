#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int L = 8;

class Layer{
public:
	Layer(int i, int s, double start);
	vector<double> generate(vector<double> input);
	vector<double> getWeights();
private:
	int in;
	int size;
	vector<double> weights;
};

Layer::Layer(int i, int s, double start){
	for(int j = 0; j < size; j++){
		weights.push_back(start);
	}

	in = i;
	size = s;
}

vector<double> Layer::generate(vector<double> input){
	if(input.size() != in){
		return vector<double>{0};
	}

	vector<double> out;
	for(int i = 0; i < size; i++){
		double temp = 0;
		for(int j = 0; j < in; j++){
			temp += input[j];
		}
		out.push_back(temp*weights[i]);
	}

	return out;
}

vector<double> toInput(string input){
	vector<char> inbtwn(input.begin(),input.end());
	return vector<double>(inbtwn.begin(),inbtwn.end());
}

vector<double> toOutput(vector<double> probs){
	int max = 0;
	for(int i = 0; i < probs.size(); i++){
		if(probs[max] < probs[i]){
			max = i;
		}
	}


}

class ConvoText(){
public:
	ConvoText(int w, int l, double start);
	~ConvoText();
	void convoText(string train);
	string generate(int len, string seed);
private:
	vector<Layer*> net;
	int width;
	int length;
};

ConvoText::ConvoText(int w, int l, double start){
	width = w;
	length = l;

	Layer* first = new Layer(L,w,start);
	net.push_back(first);

	for(int i = 0; i < l; i++){
		Layer* l = new Layer(w,w,start);
		net.push_back(l);
	}

	Layer* last = new Layer(w,256,start);
	net.push_back(last);

}

ConvoText::~ConvoText(){
	delete[] net;
}

string ConvoText::generate(int len, string seed){
	if(seed.length() <= len || seed.length() <= L || len <= L){
		return seed;
	}

	string out = seed;
	string more = "";

	for(int i = 0; i < len-seed.length()-1; i++){
		
		cLayer = net[0];
		vector<double> current = cLayer->generate(toInput(seed.append(more)));
		for(int j = 0; j < l; j++){
			cLayer = net[j+1];
			current = cLayer->generate(current);
		}

		vector<double> final = cLayer[l+1]->generate(current);
		more.append(toOuptut(final));
	}


}


int main(){

	return 0;
}