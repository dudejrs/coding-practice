#include <iostream>
#include <random>

#define N 20
#define MAX_VALUE 100
#define TEST_CASES 10

using namespace std;

int cache[N+1];


vector<int>& initialize(default_random_engine& gen){

	vector<int>* v = new vector<int>();
	uniform_int_distribution<int> dis(0, MAX_VALUE);

	for(int i=0; i<N; i++){
		v->push_back(dis(gen));
	}

	return *v;
}

int solve(vector<int>& v){
	
	if(v.empty()) return 0;
	
	int ret = 0;

	for(int i=0; i< v.size(); i++){
		vector<int> a;

		for(int j=i+1; j<v.size(); j++){
			if(v[i]<v[j]){
				a.push_back(v[j]);
			}
		}
		ret = max(ret, 1+solve(a));
	}

	return ret;
}


int solve2(int cur, vector<int>& v){
	
	int& ret = cache[cur+1];

	if(ret != -1) return ret;

	ret = 1; 

	for(int j = cur+1; j<N; j++){
		if(cur == -1 || v[cur] < v[j]){
			ret = max(ret, solve2(j,v)+ 1);
		}
	}


	return ret;
}

int main(void){

	default_random_engine gen(43);

	for (int i=0; i< TEST_CASES; i++){
		vector<int>v = initialize(gen);
		memset(cache, -1, sizeof(cache));
		cout << solve(v) << " ";
		
		memset(cache, -1, sizeof(cache));
		cout << solve2(-1,v)-1 << endl;

	}

	return 0;
}