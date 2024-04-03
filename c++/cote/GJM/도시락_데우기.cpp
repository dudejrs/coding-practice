#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

#define N 10000

using namespace std;

vector<int>& split(const string& s){
	stringstream ss(s);
	string tmp;
	vector<int>* ret = new vector<int>();

	while(getline(ss,tmp,' ')){
		ret->push_back(stoi(tmp)); 
	}

	return *ret;
}

int solve(vector<int>& m, vector<int>& e, int n){
	
	vector<pair<int,int>> order;

	for(int i =0; i<n; i++){
		order.push_back(make_pair(e[i],m[i]));
	}

	sort(begin(order),end(order), [](pair<int,int>& a, pair<int,int>& b){return a.first > b.first;});
	int ret = 0;
	int beginEat = 0;
	for(int i=0; i<n;i++){
		beginEat += order[i].first;
		ret = max(ret, beginEat+order[i].second);
	}


	return ret;
}

int main(void){

	fstream fd("./data/도시락_데우기.txt");
	string buf;
	
	getline(fd,buf);
	int test_cases = stoi(buf);

	while(test_cases > 0 ){
		getline(fd,buf);
		int n = stoi(buf);

		getline(fd,buf);
		vector<int> m = split(buf);
		getline(fd,buf);
		vector<int> e = split(buf);

		cout << solve(m,e,n) << endl;

		test_cases--;

	}

	return 0;
}