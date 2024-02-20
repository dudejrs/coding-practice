#include <iostream>
#include <random>
#include <vector>
#include <map>

#define TEST_CASES 10
#define N 1000
#define MAX_VAL 987654321

using namespace std;


vector<pair<int,int>> partSum(vector<int>& l){

	vector<pair<int,int>> ret(l.size());

	ret[0] = make_pair(l[0], 0);
	for(int i=1; i<l.size(); i++)
		ret[i] = make_pair(ret[i-1].first + l[i], i);

	return ret;
}


pair<int,int> solve(vector<int>& l){
	int min_val = MAX_VAL;
	int cur = 0;
	vector<pair<int,int>> ret = partSum(l);
	sort(begin(ret), end(ret), [](auto a, auto b){ return a.first < b.first; });


	for(int i= 1; i<ret.size(); i++){
		if(abs(ret[i].first - ret[i-1].first) < min_val){
			min_val = abs(ret[i].first - ret[i-1].first);
			cur = i;
		}
	}
	
	int first = min(ret[cur].second, ret[cur-1].second) + 1;
	int second = max(ret[cur].second, ret[cur-1].second);
	
	return make_pair(first, second);
}

int main(void){

	default_random_engine gen(43);

	for(int it=0; it<TEST_CASES; it++){
		normal_distribution<float> dis(0, 400);

		vector<int> l;

		for(int i=0; i<N; i++)
			l.push_back(floor(dis(gen)));

		pair<int,int> result = solve(l) ;
		cout << result.first << "," << result.second<< endl;

	}


	return 0;
}