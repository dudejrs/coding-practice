#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#define N 20
#define WHITE 1
#define ROW 0
#define COL 1

using namespace std;


int candidates[10][46][1024];


int getSize(int mask){
	int count = 0;

	int cur = 0;
	while(cur < 10){
		if( mask & 1 ){
			count += 1;
		}
		mask = mask >> 1;
		cur++;
	}
	
	return count;
}

int getSum(int mask){
	int sum = 0;

	int cur = 0;
	while(cur < 10){
		if( mask & 1 ){
			sum += cur;
		}
		mask = mask >> 1;
		cur++;
	}
	
	return sum;
}

int getCandidates(int len, int sum, int known){
	int allSets = 0;

	for(int set= 0; set < 1024; set += 2){
		if((set & known) == known && getSize(set) == len && getSum(set) == sum){
			allSets |= set;
		}
	}

	return allSets & (~known);
}

void generateCandidates(){

	memset(candidates, 0, sizeof(candidates));

	for(int set = 0; set < 1024; set += 2){
		int l = getSize(set), s = getSum(set);
		int subset = set;

		while(true){
			candidates[l][s][subset] |= (set & ~subset);
			if(subset == 0) break;
			subset = (subset -1) & set;
		}
	}
}

void print_solution(int n, int** value){
	cout << setw(4*n-5) << "[solution]" << endl;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cout << setw(4) << value[i][j] << " ";
		}
		cout << endl;
	}
		
}

void put(int y, int x, int val,  int** value, int*** hint,  int* known){
	for(int h= 0; h<2; h++){
		known[hint[y][x][h]] += (1<< val);
	}
	value[y][x] = val;
}

void remove(int y, int x, int val,  int** value, int*** hint,  int* known){
	for(int h= 0; h<2; h++){
		known[hint[y][x][h]] -= (1<< val);
	}
	value[y][x] = 0;
}

int getCandHint(int hint, int* sum, int* length,  int* known){
	return candidates[length[hint]][sum[hint]][known[hint]];
}

int getCandCoord(int y, int x, int*** hint, int* sum, int* length, int* known){
	return getCandHint(hint[y][x][0], sum, length, known) & getCandHint(hint[y][x][1], sum, length, known);
}



void initialize(fstream& fd, int n, int** color, int** value, int*** hint, int& q, int* sum, int* length, int* known){


	for(int i=0; i<n; i++){
		color[i] = new int[n];
	}

	for(int i=0; i<n; i++){
		value[i] = new int[n];
	}


	for(int i=0; i<n; i++){
		hint[i] = new int* [n];
		for(int j=0; j<n; j++){
			hint[i][j] = new int [2]{-1, -1};
		}
	}

	string buf;
	
	for(int i=0; i<n; i++){
		getline(fd, buf);
		stringstream ss(buf);
		for(int j=0; j<n; j++){
			getline(ss, buf, ' ');
			color[i][j] = stoi(buf);
		}

	}

	getline(fd, buf);
	q = stoi(buf);

	for(int i=0; i<q; i++){
		getline(fd, buf);
		stringstream ss(buf);

		getline(ss, buf, ' ');
		int y = stoi(buf);
		getline(ss, buf, ' ');
		int x = stoi(buf);
		getline(ss, buf, ' ');
		int direction = stoi(buf);
		hint[y-1][x-1][direction] = i;
		getline(ss, buf, ' ');
		sum[i] = stoi(buf);

		int count = 0;
		if(direction == ROW){
			int cur = x;
			
			
			while(count < 10 && cur < n){
				if(color[y-1][cur] != WHITE) 
					break;
				cur++;
				count++;
			}

		}else {
			int cur = y;
			while(count < 10 && cur < n){
				if(color[cur][x-1] != WHITE) 
					break;
				cur++;
				count++;
			}

		}
		length[i] = count;

	}




}



bool search(int n, int** color, int** value, int*** hint, int& q, int* sum, int* length, int* known){
	int y = -1, x = -1, minCands = 1023;
	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++)
			if(color[i][j] == WHITE && value[i][j] == 0){
				int cands = getCandCoord(i,j,hint,sum,length,known);
				if(getSize(minCands) > getSize(cands)){
					minCands = cands;
					y=i; x=j;
				}
			}

	if(minCands == 0) return false;

	if(y == -1){
		print_solution(n, value);
		return true;
	}

	for(int val = 1; val < 10; ++val){
		if(minCands & (1<<val)){
			put(y,x,val,value,hint,known);
			if(search(n, color, value, hint, q, sum, length, known)) return true;
			remove(y,x,val,value,hint,known);
		}
	}

	return false;

}



void finalize(int n, int** color, int** value, int*** hint){

	for(int i=0; i<n; i++){
		delete[] color[i];
	}

	for(int i=0; i<n; i++){
		delete[] value[i];
	}


	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			delete[] hint[i][j];
		}
		delete hint[i];
	}

}


int main(void){

	fstream fd("data/카쿠로.txt");
	string buf;

	generateCandidates();

	getline(fd, buf);
	int test_cases  = stoi(buf); 

	while(test_cases > 0){

		getline(fd, buf);
		int n = stoi(buf);

		int** color = new int* [n];
		int**value = new int* [n];
		int*** hint = new int** [n];
		int q, sum[n*n], length[n*n], known[n*n];

		// memset(known, 0, sizeof(known));

		initialize(fd, n, color, value, hint, q, sum, length, known);		
		for(int i=0; i<q; i++){
			cout << known[i] << ",";			
		}
		cout << endl;

		search(n , color ,value, hint, q, sum, length, known);

		finalize(n, color, value, hint);

		delete[] color;
		delete[] value;
		delete[] hint;


		test_cases --;
	}




	return 0;
}