#include <iostream>
#include <random>

#define TEST_CASE 10
#define MAX_VALUE 13
#define MAX_N 15

using namespace std;


int cache[MAX_N][MAX_N];

int** initialize(default_random_engine& gen,int n){

	uniform_int_distribution<int> dis(1,MAX_VALUE);
	
	int**  map = new int*[n];
	for(int i=0; i<n; i++){ map[i] =  new int[n];}

	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			map[i][j] = dis(gen);
	}} 

	return map;
}

int maximum(int y, int x, int** map, int n){
	int& ret = cache[y][x];
	if(ret != -1) return ret;
	if( y == n-1) return map[y][x];	
	return ret = maximum(y+1,x,map,n) + maximum(y+1,x+1,map,n);
}

int count (int y, int x, int** map, int n){
	
	if(y == n-1) return 1;

	int left = maximum(y+1,x,map,n);
	int right = maximum(y+1,x+1,map,n);
	
	if(left > right ){
		return count(y+1, x, map, n);
	}else if (left < right){
		return count(y+1, x+1, map, n);
	}
	return count(y+1, x, map, n)+ count(y+1, x+1, map, n);
}

int solve(int** map, int n){
	return count(0,0,map,n);
}

int main(void){
	default_random_engine gen(43);
	for(int i=0; i<TEST_CASE; i++){

		memset(cache,-1,sizeof(cache));
		int n = gen() % MAX_N;
		int** map = initialize(gen,n);

		cout << solve(map,n) << endl;

		for(int i =0; i<n; i++){
			delete[] map[i];
		}
		delete[] map;
	}

	return 0;
}