#include <iostream>
#include <random>
#include <string>
#include <algorithm>

#define TEST_CASES 10
#define M 5

using namespace std;

string initialize(default_random_engine& gen){

	string ret;

	uniform_int_distribution<int> dis('a','c');

	for(int i=0; i<M; i++)
		ret += dis(gen);

	return ret;
}

vector<int> get_partial_match(const string& s){
	vector<int> pi(s.size(), 0) ;

	for(int begin =1; begin < s.size(); begin++){
		for(int i=0; i< s.size()-begin; i++){
			if(s[begin+i] != s[i]) continue;
			pi[begin+i] = max( pi[begin+i], i+1);
		}
	}

	return pi;
}

void solve(const string& s, const string& sprime){
	
	int begin = 0, matched = 0;
	vector<int> pi = get_partial_match(sprime);

	while(begin< s.size()){

		if(s[begin + matched] == sprime[matched]){
			matched++;
			if(begin + matched == s.size()){
				for(int i=0; i<begin; i++){
					cout << s[i] ;
				}
				cout << sprime << endl;
				return ;
			}
		} else {
			if(matched == 0)
				begin ++;
			else {
				begin += matched - pi[matched-1];
				matched = pi[matched-1];
			}

		}
	}

}

int main(void){

	default_random_engine gen(43);

	for(int it= 0; it<TEST_CASES; it++){
		string s = initialize(gen);
		string sprime(s.size(),'a');
		copy(begin(s),end(s),begin(sprime));
		reverse(begin(sprime),end(sprime));
		cout << s << "," << sprime << ">>";
		solve(s,sprime);
	}

	return 0;
}