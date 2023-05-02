#include <iostream>
#include <fstream>
#include <string>
#define N 100
#define MOD 10000000

using namespace std;

int cache[N][N];

int polynomio(int k, int n){

	int& ret = cache[k][n];

	if(ret != -1) return ret;

	if( n == 0 || k == n) return 1;

	ret = 0;

	for(int i=1; i <= n-k; i++){
		ret += ((i+k-1) * (polynomio(i,n-k) % MOD) % MOD);
	}

	return (ret % MOD);
}

int solve(int n){
	
	memset(cache, -1, sizeof(cache));

	int sum = 0;
	for(int i=1; i<=n; i++){
		sum += (polynomio(i,n) % MOD );
	}

	return sum % MOD;
}

int main(void){

	fstream fd("data/폴리오미노.txt");
	string buf;

	getline(fd,buf);
	int test_cases = stoi(buf);
	
	while(test_cases > 0){
		getline(fd,buf);
		int n = stoi(buf);
		cout << solve(n) << endl;

		test_cases--;
	}

	return 0;
}