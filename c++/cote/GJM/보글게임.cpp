#include <iostream>
#include <initializer_list>
#include <vector>
#include <string>

using namespace std;

typedef pair<pair<int,int>,string> T;


const int dx[8] = {-1,	0,	1,	-1,	1,	-1,	0,	1};
const int dy[8] = {-1,	-1,	-1,	0,	0,	1,	1,	1};

bool inRange(int x, int y){
	return (y<0 || y>4 || x<0 || x>4);
}

bool hasWord(const char board[5][5], int x, int y, const string& word){
	if(inRange(x,y)) return false;
	if(board[x][y] != word[0]) return false;
	if(word.size() == 1) return true;
	
	for(int i =0; i<8; i++){
		int x2=x+dx[i], y2 =y+ dy[i];
		if(hasWord(board, x2, y2, word.substr(1))) return true;
	}
	return false;
}


vector<T> solve(const char board[5][5], const vector<string> word_list){

	vector<T> results;

	for(auto word : word_list){
		for(int i=0; i< 5; i++){
			for(int j=0; j<5; j++){
				if(hasWord(board, i, j, word)){
					results.emplace_back(make_pair(make_pair(i,j),word));
				}
			}
		}
	}

	return results;
}

int main(void){

	const vector<string> word_list = {"PREETY", "GIRL", "REPEAT"};
	const char board[5][5] = {  {'U','R','L','P','M'},
								{'X','P','R','E','T'},
								{'G','I','A','E','T'},
								{'X','T','N','Z','Y'},
								{'X','O','Q','R','S'}};

	vector<T> results = solve(board, word_list);

	for(auto result : results){
		int i = result.first.first;
		int j = result.first.second;
		string word = result.second;
		cout << "(i,j) = "<<i<<","<<j <<":"<<word<<endl;
	}


	return 0;
}