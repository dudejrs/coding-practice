#include <iostream>
#include <random>
#include <iomanip>

#define TEST_CASES 10
#define N 5
#define K 3
#define MAX_VALUE 987654321

using namespace std;


int dy[4] = {-1,0,0,1};
int dx[4] = {0,-1,1,0};

int cache [N][N][K+1];

int search(int y, int x, int n, int k, int** board){

	if( k <= 0 ) return 0;

	int& ret = cache[y][x][k];
	if(ret != -1) return ret;
	
	ret = 0;

	for(int d=0; d<4; d++){
		int ny = y + dy[d];
		int nx = x + dx[d];

		if(ny <0 || ny >= n || nx<0 || nx>= n) continue;
		ret = max(ret, board[ny][nx] + search(ny,nx,n,k-1,board));
	}

	return ret;
}

int solve(int** board, int n, int k){

	memset(cache, -1, sizeof(cache));

	int ret = MAX_VALUE;
	cout << "[maximum]" << endl;
	for(int i=0; i<n; i++){

		for(int j=0; j<n; j++){
			ret = min(ret, search(i,j,n,k,board));
			cout << setw(3) << search(i,j,n,k,board) << " ";
		}
		cout << endl;
	}


	return ret;
}

int main(void){

	default_random_engine gen(43);
	normal_distribution<float> dis(10,5);

	for(int it =0; it < TEST_CASES; it++){
		int n = gen() % (N+1-5) + 5; 
		// int k = gen() % (K+1-2) + 2;
		int k = 3;

		int** board = new int*[n];


		for(int i=0; i<n; i++){
			board[i] = new int[n];
			for(int j=0; j<n; j++)
				board[i][j] = floor(abs(dis(gen)));
		}
		cout << "[board]"<< endl;
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++)
				cout << setw(3) << board[i][j] << " ";
			cout << endl;
		}
		cout <<endl;

		cout <<  solve(board, n, k) << endl << endl;
		

		for(int i=0; i<n; i++)
			delete[] board[i];
		delete[] board;

	}



	return 0;
}