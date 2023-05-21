#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <sstream>

#define TEST_CASES 10
#define M 20
#define MAX_VALUE 100
#define MAX 200000001
#define K 3

using namespace std;


int cache[M+1];
int countCache[M+1];

vector<int>& initialize(default_random_engine& gen){
	vector<int>* ret = new vector<int>();

	uniform_int_distribution<int> dis(0, MAX_VALUE);

	for(int i =0; i<M; i++){
		ret->push_back(dis(gen));
	}

	return *ret;
}


int findMax(int prv,vector<int>& v){
	int& ret = cache[prv+1];
	if(ret != -1) return ret;
	if(prv == v.size()) return 1; 

	for(int i=prv+1; i < v.size(); i++ ){
		if( prv == -1 || v[prv] < v[i] ) {
			ret = max(ret, findMax(i, v)+1);
		}
	}

	return ret;
}⁄

int count(int prv, vector<int>& v){
	if(findMax(prv, v) == 1) return 1;
	int& ret = countCache[prv+1];
	if(ret != -1) return ret;
	
	ret = 0;
	for(int i =prv+1; i<v.size(); i++){
		if((prv== -1 || v[prv] < v[i]) && findMax(prv,v) == findMax(i, v) +1){
			ret = min<long long>(MAX, (long long)ret + count(i, v));
		}
	}
	return ret;
}

void reconstruct(int prv, int skip, vector<int>& v, ostringstream& oss){
	
	if(prv != -1) oss << v[prv] << " ";

	vector<pair<int,int>> followers;

	for(int i = prv+1; i < v.size();i++){
		if((prv == -1 || v[prv] < v[i])&& findMax(prv,v) == findMax(i,v) + 1){
			followers.push_back(make_pair(v[i],i));
		}
	}

	sort(followers.begin(), followers.end());

	for(int i =0; i<followers.size(); i++){
		int idx = followers[i].second;
		int cnt = count(idx,v);

		if(cnt <= skip) skip -= cnt;
		else {
			reconstruct(idx, skip, v, oss);
			break;
		}
	}


}

string solve(vector<int>& v, int k){
	ostringstream oss;

	memset(cache, -1, sizeof(cache));
	memset(countCache, -1, sizeof(countCache));

	int n = findMax(-1, v ) -1;
	count(-1, v);
	reconstruct(-1, (k - 1 )% n, v, oss);

	// oss << findMax(-1, v )-1;
	// oss <<"," << count(-1, v);

	return oss.str();
}


int main(void){

	default_random_engine gen(43);

	for(int i=0; i< TEST_CASES; i++){
		vector<int> v = initialize(gen);
		int k = gen() % K;

		cout << solve(v, k) << endl;

	}

	return 0;
}