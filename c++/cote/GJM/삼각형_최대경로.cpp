#include <iostream>
#include <random>
#define N 10
#define MAX_VALUE 15
#define TEST_CASES 10

using namespace std;

int** initialize(default_random_engine& gen){
	uniform_int_distribution<int> dis(1, MAX_VALUE);

	int** map = new int*[N];

	for(int i =0; i<N; i++){
		map[i] = new int[N];
	}


	for(int i =0; i< N; i++){
		for(int j=0; j<= N; j++){
			map[i][j] = dis(gen);
		}
	}

	return map;
}


int path(int x, int y, int sum, int** map){
	if(y == N-1) return sum + map[y][x];
	sum += map[y][x];
	return max(path(x,y+1,sum,map), path(x+1,y+1,sum, map));
}

int solve(int** map){

	return path(0,0,0,map);
}


int path2(int x, int y, int sum, int** map, int cache[N][N][MAX_VALUE*100+1]){
	
	if(y == N-1) return sum + map[y][x];
	int& ret = cache[y][x][sum];
	if( ret != -1) return ret;
	sum += map[y][x];
	return (ret = max(path2(x,y+1,sum,map,cache), path2(x+1,y+1,sum, map,cache)));
}

int solve2(int** map){
	int cache[N][N][MAX_VALUE*100+1];
	memset(cache, -1, sizeof(cache));

	return path2(0,0,0,map,cache);
}

int path3(int x, int y, int** map, int cache[N][N]){
	
	if(y == N-1) return map[y][x];
	int& ret = cache[y][x];
	if( ret != -1) return ret;
	return (ret = max(path3(x,y+1,map,cache), path3(x+1,y+1, map,cache)) + map[y][x]);
}

int solve3(int** map){
	int cache[N][N];
	memset(cache, -1, sizeof(cache));

	return path3(0,0,map,cache);
}

int main(void){
	default_random_engine gen(43);

	for(int i =0; i<TEST_CASES; i++){

		int** map = initialize(gen);


		cout << solve3(map) << endl;

		for(int i=0; i<N; i++){
			delete[] map[i];
		}
		delete[] map;
	}


	return 0;
}