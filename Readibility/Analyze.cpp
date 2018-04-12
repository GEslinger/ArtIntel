#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

const string INFILE = "Examples/washington.txt";

vector<string> split(const string& s, char delimiter){	// Splits a string
	vector<string> tokens;
	string token;
	istringstream tokenStream(s);
	while (getline(tokenStream, token, delimiter)){
		if(token != ""){
			tokens.push_back(token);
		}
	}
	return tokens;
}

double getASL(string& text){							// Average length of sentences in words
	vector<string> sentences = split(text,'.');
	int avgLen = 0;
	int numSentences = 0;

	for(string str : sentences){
		vector<string> words = split(str,' ');
		avgLen += words.size();
		numSentences++;
	}

	return (double)avgLen / (double)numSentences;
}

int getNumSyllables(string& word){
	int posLastSyl = 0;
	vector<int> vowelPos;

	// cout << "adding vowels\n";

	size_t found = word.find_first_of("aeiouy");
	while(found != string::npos){
		posLastSyl = (int)found;
		vowelPos.push_back(found);
		found=word.find_first_of("aeioyu",found+1);
	}


	if(vowelPos.size() >= 2){

		found = word.find_last_of("e");
		// cout << int(found) << " : " << vowelPos.back() << endl;
		if((int)found == vowelPos.back() && (int)found != word.size()){
			// cout << "removing silent e\n";
			vowelPos.erase(vowelPos.end()-1);
		}
	}

	int i = 0;
	int max = vowelPos.size()-1;
	while(i < max){
		if(vowelPos[i]+1 == vowelPos[i+1]){
			// cout << "removing a pair\n";
			vowelPos.erase(vowelPos.begin()+i);
			max--;
			i--;
		}
		i++;
	}



	// cout << "done\n";

	return vowelPos.size();
}

double getASW(string& text){
	vector<string> sentences = split(text,'.');
	int numWords = 0;
	int avgSyl = 0;

	for(string str : sentences){
		vector<string> words = split(str,' ');
		for(string word : words){
			if(word.length() > 0 && getNumSyllables(word) > 0){
				avgSyl += getNumSyllables(word);
				// cout << word << "\t" << getNumSyllables(word) << endl << flush;
				numWords++;
			}
		}
	}

	return (double)avgSyl / (double)numWords;
}

string inputFile(string fname){
	ifstream in(fname);
	stringstream strStream;
	strStream << in.rdbuf();//read the file
	string text = strStream.str();//str holds the content of the file
	return text;
}



int main(){
	string passage = inputFile(INFILE);

	cout << "File: " << INFILE << endl;
	cout << "Average sentence length: " << getASL(passage) << " words.\n";
	cout << "Average syllables per word: " << getASW(passage) << endl;
	double score = 0.39*getASL(passage) + 11.8*getASW(passage) - 15.59;
	cout << "Flesch-Kincaid readability score: " << score << endl;

	return 0;
}