#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

vector<int> get_partial_match(const string& m){

	vector<int> pi(m.size(), 0);

	for(int begin = 1; begin< m.size(); begin++){
		for(int i=0; i<m.size()-begin; i++){
			if(m[begin+i] != m[i]) break;
			pi[begin+i] = max(pi[begin+i], i+1);
		}
	}

	return pi;
}


int kmpSearch(const string& h, const string& m){

	vector<int> pi = get_partial_match(m);

	int begin =0, matched=0;
	while( begin <= h.size() - m.size()){
		if( matched < m.size() && h[begin+matched] == m[matched]){
			matched++;
			if(matched == m.size())
				return begin;
		} else {
			if(matched == 0) begin++;
			else {
				begin += matched - pi[matched-1];
				matched = pi[matched-1];
			}
		}
	}

	return 987654321;
}


int shift(const string& original, const string& target){
	return kmpSearch(original+original, target);
}


int solve(vector<string>& dials){

	int ret =0;

	string original = dials[0];

	for(int i=1; i< dials.size(); i++){
		ret += min(shift(original, dials[i]), shift(dials[i], original));
		original = dials[i];
	}
	
	return ret;
}


int main(void){

	fstream fd("data/재하의_금고.txt");
	string buf;

	getline(fd,buf);

	int test_cases = stoi(buf);

	while(test_cases > 0){
		getline(fd, buf);
		int n = stoi(buf);
		vector<string> dials;

		for(int i=0; i<= n; i++){
			getline(fd,buf);
			dials.push_back(buf);
		}

		cout << solve(dials) << endl;

		test_cases --;
	}


	return 0;
}