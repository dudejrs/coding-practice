#include <iostream>
#include <string>
#include <random>
#define TEST_CASES 10
#define MAX_LENGTH 10
#define MIN_LENGTH 5

using namespace std;


string initialize(default_random_engine& gen){

	string s;
	uniform_int_distribution<int> dis('a', 'f');

	int n = gen() % (MAX_LENGTH - MIN_LENGTH +1) +MIN_LENGTH ;

	for(int i=0; i<n; i++)
		s += dis(gen);

	return s;
}

struct Comparator{

	vector<int>& group;
	int t;

	Comparator(vector<int>& group, int t) : group(group), t(t){}

	bool operator()(int a, int b){
		if(group[a] != group[b]) return group[a] < group[b];
		return group[a+t] < group[b+t];
	}

};


vector<int> getSuffixArray(const string& s){
	int n = s.size(), t=1;

	vector<int> group(n+1);
	for(int i=0; i<n; i++) group[i] = s[i];
	group[n] = -1;

	vector<int> perm(n,0);
	for(int i=0; i<n; i++) perm[i]= i;

	while(t < n){
		Comparator comp(group,t);
		sort(begin(perm), end(perm), comp);

		t *=2;
		if(t >= n) break;
		vector<int> newGroup(n+1);
		newGroup[n] = -1;
		newGroup[0] = 0;
		for(int i=1; i<n; i++){
			if(comp(perm[i-1], perm[i]))
				newGroup[perm[i]] = newGroup[perm[i-1]] +1;
			else 
				newGroup[perm[i]]= newGroup[perm[i-1]];
		}
		group = newGroup;
	}

	return perm;
}

string solve(const string& s){

	string s2 = s+s;
	vector<int> a = getSuffixArray(s2);

	for(int i=0; i<a.size(); i++)
		if(a[i] < s.size())
			return s2.substr(a[i], s.size());
	
	return "";
}

int main(void){

	default_random_engine gen(43);

	for(int it =0; it <TEST_CASES; it++){

		string target = initialize(gen);
		cout << target << " ";
		cout << solve(target) << endl;
	}

	return 0;
}