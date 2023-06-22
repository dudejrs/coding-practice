#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#define N 20

using namespace std;


void print_solution(int n, int** value){
	
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cout << setw(4) << value[i][j] << " ";
		}
		cout << endl;
	}
		
}

void initialize(fstream& fd, int n, int** color, int** value, int*** hint, int& q, int* sum, int* length, int* known){

	color = new int* [n];
	for(int i=0; i<n; i++){
		color[i] = new int[n];
	}

	value = new int* [n];
	for(int i=0; i<n; i++){
		value[i] = new int[n];
	}

	hint = new int** [n];
	for(int i=0; i<n; i++){
		hint[i] = new int* [n];
		for(int j=0; j<n; j++){
			hint[i][j] = new int [2];
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
		int x = stoi(buf);
		getline(ss, buf, ' ');
		int y = stoi(buf);
		getline(ss, buf, ' ');
		int direction = stoi(buf);
		hint[x-1][y-1][direction] = i;
		getline(ss, buf, ' ');
		sum[i] = stoi(buf);

	}

	print_solution(n, value);
	print_solution(n, color);

}

void solve(fstream& fd, int n, int** color, int** value, int*** hint, int& q, int* sum, int* length, int* known){
	print_solution(n, value);
}



void finalize(int n, int** color, int** value, int*** hint){
	
	print_solution(n, value);

}


int main(void){

	fstream fd("data/카쿠로.txt");
	string buf;
		
	getline(fd, buf);
	int test_cases  = stoi(buf); 

	while(test_cases > 0){

		getline(fd, buf);
		int n = stoi(buf);

		int** color, **value, *** hint;
		int q, sum[n*n], length[n*n], known[n*n];
		initialize(fd, n, color, value, hint, q, sum, length, known);		

		solve(fd, n , color ,value, hint, q, sum, length, known);

		// print_solution(n, value);

		// finalize(n, color, value, hint);

		test_cases --;
	}


	return 0;
}