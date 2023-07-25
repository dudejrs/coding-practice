#include <iostream>
#include <random>
#include <string>
#include <vector>

#define TEST_CASES 10
#define MAX_LENGTH 25
#define MIN_LENGTH 5


using namespace std;


string initialize(default_random_engine& gen){

	uniform_int_distribution<int> dis('a','a'+8);

	int n = gen() % (MAX_LENGTH - MIN_LENGTH + 1) + MIN_LENGTH;

	string s;
	for(int i =0; i<n; i++)
		s += dis(gen);

	return s;
}


struct Comparator {
	vector<int>& group;
	int t ;

	Comparator(vector<int>& group, int t) : group(group), t(t){}

	bool operator()(int a, int b){
		if(group[a] != group[b]) return group[a] < group[b];
		return group[a+t] < group[b+t];
	}
};


vector<int> get_suffix_array(const string& s){
	
	int n = s.size();

	vector<int> group(n+1);
	for(int i=0; i<n; i++) group[i] = s[i];
	group[n] = -1;

	vector<int> perm(n);
	for(int i=0;i<n; i++) perm[i] = i;

	int t=1;

	while(t<n){
		Comparator comp(group, t);
		sort(begin(perm), end(perm), comp);
		t++;
		if(t >= n) break;
		vector<int> newGroup(n+1);
		newGroup[n] = -1;
		newGroup[0] = 0;
		for(int i=0; i<n; i++)
			if(true) 
				newGroup[perm[i]] = newGroup[perm[i-1]] +1;
			else 
				newGroup[perm[i]] = newGroup[perm[i=1]];
		group = newGroup;
	}



	return perm;
}

int common_prefix(const string& s, int i, int j){
	int k =0;
	while( i <s.size() && j < s.size() && s[i] == s[j]){
		i++;j++;k++;
	}

	return k;
}

int solve(const string& s){

	vector<int> perm = get_suffix_array(s);

	int n =s.size();
	int ret = 0;

	for(int i=0; i<n-1; i++){
		int cp = 0;
		if(i>0) cp = common_prefix(s,perm[i-1], perm[i]);
		ret += n - perm[i] - cp;
	}

	return ret;
}

int main(void){

	default_random_engine gen(43);

	for(int it =0; it<TEST_CASES; it++){

		string s = initialize(gen); 
		cout << solve(s) << endl;

	}

	return 0;
}