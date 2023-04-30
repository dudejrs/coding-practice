#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#define MAX_ 987654321

using namespace std;



int classify(int cur, int n, const string& s ){

	string m = s.substr(cur, n);

	if( m == string(n,m[0])) return 1;

	bool progressive = true;
	for(int i=0; i<n-1; i++){
		if((m[i+1]-m[i]) != m[1]-m[0]) progressive =false;
	}
	if(progressive && abs(m[1]-m[0]) == 1) return 2;
	bool alternating = true;
	for(int i=0; i<n; i++){
		if(m[i] != m[i%2]) alternating=false;
	}
	if(alternating) return 4;
	if(progressive) return 5;

	return 10;
}


int memorize(int cur, const string& s){
	
	if(cur == s.size()) return 0;

	int ret = MAX_;


	for(int i =3; i < 6; i++){
		if(cur+i <= s.size()){
			ret = min(ret, memorize(cur+i, s) + classify(cur,i,s));
		}
	}

	return ret;
}

int solve(const string& s){
	return memorize(0,s);
}

int main(void){
	fstream fd("data/원주율외우기.txt");
	string buf;

	getline(fd,buf);
	int test_cases = stoi(buf);

	while( test_cases > 0 ){

		getline(fd,buf);
		cout << solve(buf) << endl;

		test_cases--;
	}

	return 0;
}