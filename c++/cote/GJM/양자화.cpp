#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cmath>

#define N 1000
#define S 10
#define MAX_ 987654321

using namespace std;

int pSum[N+1], pSqSum[N+1];

vector<int>& split(const string& s){
	stringstream ss(s);
	string temp;
	vector<int>* v = new vector<int>();

	while(getline(ss,temp, ' ')){
		v->push_back(stoi(temp));
	}
	return *v;
}

void precalc(vector<int>&v){
	sort(begin(v),end(v));
	pSum[0] = v[0];
	pSqSum[0] = v[0] * v[0];
	for(int i=1; i<v.size();i++){
		pSum[i] = pSum[i-1] + v[i];
		pSqSum[i] = pSqSum[i-1] + v[i]* v[i];
	}
}


int minError(int start, int end, vector<int>& v){
	int sum = pSum[end-1] - (start == 0 ? 0 : pSum[start-1]);
	int sqSum = pSqSum[end-1] - (start ==0 ? 0 : pSqSum[start-1]);

	int m = ceil((double) sum / (end-start));

	return sqSum - 2*m*sum + m*m*(end-start);
}


int quantize(int cur, int n, vector<int>& v){
	if(cur == v.size()) return 0;
	if(n == 0) return MAX_;

	int ret = MAX_;
	for(int i=cur+1; i<=v.size()-(n-1); i++){
		ret = min(ret, quantize(i,n-1,v) + minError(cur,i,v));
	}

	return ret;
}

int solve(int n, vector<int>& v){
	
	precalc(v);
	return quantize(0,n,v);
}


int main(void){

	fstream fd("data/양자화.txt");
	string buf;

	getline(fd,buf);
	int test_cases  = stoi(buf);

	while(test_cases > 0){
		getline(fd,buf);
		vector<int> n= split(buf);
		getline(fd,buf);
		vector<int> v = split(buf);

		cout << solve(n[1], v) << endl;

		test_cases--;
	}

	return 0;
}