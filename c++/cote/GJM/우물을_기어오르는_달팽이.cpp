#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <random>
#include <iomanip>
#include <cmath>

#define TEST_CASES 10
#define N 10
#define M 5


using namespace std;


int cache[N][M];

int count(int climbed, int days, int n, int m){
	int& ret = cache[climbed][days];
	if(ret != -1 ) return ret;
	if(days == n ) return climbed > n;
	return (ret = count(climbed+1, days+1, n, m) + count(climbed+2, days+1, n, m));
}


float solve(int n, int m){
	return count(0,0,n,m) / pow(2,n);
}



int main(void){

	default_random_engine gen(43);

	for(int i=0; i<TEST_CASES; i++){
		int n = gen() % N;
		int m = gen() % M;

		memset(cache, -1, sizeof(cache));

		cout << fixed << setprecision(3)  << solve(n,m) << endl;
	}

	return 0;
}