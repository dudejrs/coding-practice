#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#define N 100000
#define K 100000
#define D 100000
#define MOD 20091101

using namespace std;

vector<int> split(const string& s){
	
	vector<int> ret;
	stringstream ss(s);
	string buf;

	while(getline(ss, buf,' ')){
		ret.push_back(stoi(buf));
	}

	return ret;
}

vector<int> get_partial_sum(int k, const vector<int>& toys){
	vector<int> ret(toys.size()+1);

	ret[0] = 0;
	ret[1] = toys[0] % k;
	for(int i =1; i<toys.size(); i++){
		ret[i+1] = (ret[i] + toys[i] ) % k;
	}

	return ret;
}

int waysToBuy(int k, const vector<int>& psum){

	int ret = 0;
	vector<long long> count(k, 0);
	
	for(int i =0; i<psum.size(); i++)
		count[psum[i]] +=1;

	for(int i=0; i<k; i++)
		if(count[i] >= 2){
			ret += ((count[i]* (count[i]-1))/2) % MOD; 
		}


	return ret;
}	

int maxBuys(int k, const vector<int>& psum){

	vector<int> ret(psum.size(), 0);
	vector<int> prev(k, -1);

	for(int i=0; i<psum.size(); i++){
		ret[i]= (i>0) ? ret[i-1] : 0;

		int loc = prev[psum[i]];
		if(loc != -1)
			ret[i] = max(ret[i], ret[loc]+1);
		prev[psum[i]] = i;

	}

	return ret[psum.size()-1];
}

pair<int,int> solve(int n, int k, const vector<int>& toys){

	vector<int> psum = get_partial_sum(k, toys);
	return make_pair(waysToBuy(k, psum), maxBuys(k,psum));
}

int main(void){

	fstream fd("data/크리스마스_인형.txt");
	string buf;

	getline(fd,buf);
	int test_cases = stoi(buf);
	
	while(test_cases > 0){
		getline(fd,buf);
		vector<int> n = split(buf);
		getline(fd,buf);
		vector<int> toys = split(buf);

		pair<int,int> result = solve(n[0], n[1], toys);
		cout << result.first << "," << result.second << endl;

		test_cases--;
	}

	return 0;
}