#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <vector>

using namespace std;

vector<int>& split(const string& s){
	stringstream ss(s);
	string tmp;

	vector<int>* ret = new vector<int>();

	while(getline(ss, tmp, ' ')){
		ret->push_back(stoi(tmp));
	}

	return *ret;
}

int solve(vector<int>& v, int n){

	priority_queue<int,vector<int>, greater<int>> pq;

	for(int x : v){
		pq.push(x);
	}

	int ret = 0;

	while(pq.size() > 1){
		int m1 = pq.top(); 
		pq.pop();
		int m2 = pq.top();
		pq.pop();

		pq.push(m1+m2);
		ret += m1 + m2;
	}

	return ret;
}

int main(void){

	fstream fd("data/문자열_합치기.txt");
	string buf;

	getline(fd,buf);
	int test_cases = stoi(buf);

	while(test_cases > 0){
		getline(fd,buf);
		int n = stoi(buf);

		getline(fd, buf);
		vector<int> v = split(buf);


		cout << solve(v,n)<< endl;

		test_cases--;
	}

	return 0;
}