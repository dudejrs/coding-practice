
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


using namespace std;


vector<int> split(string input, char delimiter){
	vector<int> result;
	stringstream ss(input);
	string temp;

	while(getline(ss, temp, delimiter)){
		result.push_back(stoi(temp));
	}

	return result;
}

bool** getRelationShip(string& s, int N, int k){
	stringstream ss(s);
	string temp;

	bool** areFriend = new bool*[N];
	for(int i=0; i<N; i++){
		areFriend[i] = new bool[N];
		fill(areFriend[i], areFriend[i]+N, false);
	}

	int cur = 0;
	while(cur < k){
		getline(ss, temp,' ');
		int a = stoi(temp);

		getline(ss,temp,' ');
		int b = stoi(temp);

		areFriend[a][b] = true;
		areFriend[b][a] = true;

		cur++;
	}

	return areFriend;
}


int solve(bool** areFriend, bool* taken, int N){
	int target = -1;
	for(int i=0; i<N; i++){
		if(!taken[i]) {
			target = i; 
			break;
		}
	}

	if(target == -1) return 1;
	
	
	int ret= 0;

	for(int j = target+1; j<N; j++){
		if( !taken[j] && areFriend[target][j] ){
			taken[target] = taken[j] = true;
			ret += solve(areFriend, taken, N);
			taken[target] = taken[j] = false;				
		}
	}

	return ret;
}


int main (void){
	ifstream fd("data/소풍.txt");
	string s;
	int test_cases; 
	int n = 0;
	int l[2];

	getline(fd, s);
	test_cases = stoi(s);


	while(!fd.eof() && n < test_cases ){

		getline(fd,s);
		vector<int> v = split(s,' ');

		getline(fd,s);

		bool** areFriend = getRelationShip(s, v[0], v[1]);
		bool* taken = new bool[v[0]];


		fill(taken, taken+v[0],false);

		cout << solve(areFriend, taken, v[0]) << endl;


		for(int i=0; i<v[0]; i++){
			delete[] areFriend[i];
		}
		delete[] areFriend;
		delete[] taken;

		n++;
	}

	return 0;
}