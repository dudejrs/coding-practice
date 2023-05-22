#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

#define M 20
#define MOD 1000000007

using namespace std;

int cache[1<<14][20][2];

vector<long>& split(const string& s){

	vector<long>* ret = new vector<long>();
	stringstream ss(s);
	string tmp;

	while( getline(ss, tmp, ' ') ){
		ret->push_back(stod(tmp));
	}

	return *ret;
}


int solve(const string& digits,const string& p, int m, string price, vector<bool>& taken){

	if( price.size() == digits.size() && price <p && stol(price) % m == 0){

		return 1;
	}

	int ret = 0;

	for(int i=0; i< digits.size(); i++){
		if(taken[i]) continue;
		if( i == 0 || digits[i] != digits[i-1] || taken[i-1]){
			taken[i] = true;
			ret += solve(digits, p, m, price+ digits[i], taken);
			ret = ret % MOD;
			taken[i] = false;
		}
	}

	return ret ;
}

int solve2(const string& digits,const string& p, const int m,  int idx, int less, int mod, int taken){

	if(idx == digits.size()){
		return (less && (mod == 0)) ? 1 : 0;
	}

	int& ret = cache[taken][mod][less];

	if(ret != -1) return ret;

	ret = 0;

	for(int i=0; i< digits.size(); i++){
		if(taken & (1 << i)) continue;
		// 크거나 같은데 지금숫자를 추가하면 클때
		if( !less && p[idx] < digits[i]) continue;
		if( i > 0 && digits[i] == digits[i-1] && ((taken & (1 << (i-1))) == 0 )) continue;
		
		int nextLess = less || p[idx] > digits[i];
		int nextMod = (mod * 10 + (digits[i]  - '0')) % m;
		int nextTaken = taken | (1 << i);

		ret += solve2(digits, p, m,  idx+1, nextLess, nextMod,  nextTaken);
		ret = ret % MOD;
		
	}

	return ret;
}

int main(void){

	fstream fd("data/웨브바짐.txt");
	string buf;
	
	getline(fd, buf);
	int test_cases = stoi(buf);

	while( test_cases > 0 ){
		getline(fd, buf);
		vector<long> s = split(buf);

		string p = to_string(s[0]);
		string digits = p;
		sort(begin(digits),end(digits));
		string price = "";

		vector<bool> taken(p.size());
		cout << solve(digits, p, s[1], price, taken)<< endl;

		memset(cache, -1, sizeof(cache));
		cout << solve2(digits, p, s[1], 0, 0, 0, 0)<< endl;
		test_cases --;
	}

	return 0;
}