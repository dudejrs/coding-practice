#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#define EXPAND_X "X+YF"
#define EXPAND_Y "FX-Y"
#define MAX 1000000000+1

using namespace std;


int skip = 0;
int length[51];

vector<int>& split(const string& s){
	vector<int>* ret = new vector<int>();
	stringstream ss(s);
	string tmp;

	while(getline(ss, tmp,' ')){
		ret->push_back(stoi(tmp));
	}
	return *ret;
}

void makeDragonCurve(const string& seed, int generation, ostringstream& oss){
	if(generation == 0){
		oss << seed;
		return;
	}

	for(int i=0; i< seed.size(); i++){
		if(seed[i] == 'X')
			makeDragonCurve(EXPAND_X, generation-1, oss);
		else if (seed[i] == 'Y')
			makeDragonCurve(EXPAND_Y, generation-1, oss);
		else 
			oss << seed[i];
	}
}

void makeDragonCurve2(const string& seed, int generation, ostringstream& oss){
	if(skip < 0) return;
	
	if(generation == 0){
		if (skip == 0 )
			oss << seed;
		skip -= seed.size();
		return;
	}

	for(int i=0; i< seed.size(); i++){
		if(seed[i] == 'X')
			makeDragonCurve(EXPAND_X, generation-1, oss);
		else if (seed[i] == 'Y')
			makeDragonCurve(EXPAND_Y, generation-1, oss);
		else 
			oss << seed[i];
	}
}



string solve(int n, int p, int l){
  	ostringstream oss;
  	makeDragonCurve("FX", n, oss);

	return oss.str();
}


string solve2(int n, int p, int l){
  	ostringstream oss;
  	skip = p-1;
  	makeDragonCurve("FX", n, oss);

	return oss.str();
}


void precalc(){
	length[0] = 1;
	 for(int i=1; i<=50;++i){
	 	length[i] = min (MAX, length[i-1]*2 +2);
	 }
}

char expand(const string& s, int generation, int skip){
	if(generation == 0){
		assert(skip < s.size());
		return s[skip];
	}

	for(int i=0; i< s.size(); i++){
		if( s[i] == 'X' || s[i] == 'Y'){
			if( skip >= length[generation])
				skip -= length[generation];
			else if(s[i] == 'X')
				return expand(EXPAND_X, generation-1, skip);
			else
				return expand(EXPAND_Y, generation-1, skip);
		} 
		else if(skip > 0)
			skip--;
		else
			return s[i];
	}
	return '#';
}

string solve3(int n, int p, int l){
	ostringstream oss;
	precalc();
	for(int i =p-1; i < p+l-1; i++)
		oss << expand("FX", n, i);

	return oss.str();
}

int main(void){

	fstream fd("data/드래곤커브.txt");
	string buf;
	string c = "Hello";


	getline(fd, buf);

	int test_cases = stoi(buf);

	while(test_cases > 0 ){

		getline(fd, buf);
		vector<int> n = split(buf);
		
		cout << solve3(n[0],n[1],n[2]) << endl;

		test_cases--;
	}

	return 0;
}