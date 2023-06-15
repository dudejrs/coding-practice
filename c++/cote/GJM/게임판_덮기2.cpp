#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


using namespace std;
typedef vector<pair<int,int>> rotation;

int covered[10][10];
int best;


vector<int>& split(const string& s ){
	vector<int>* ret = new vector<int>();

	stringstream ss(s);
	string tmp;

	while(getline(ss,tmp,' ')){
		ret->push_back(stoi(tmp));
	}

	return *ret;
}


vector<string>& get_object(fstream& fd, const int H, const int W ){

	vector<string>* ret = new vector<string>();
	string buf;

	for(int i=0; i< H; i++){
		getline(fd,buf);
		ret->push_back(buf.substr(0,W));
	}


	return *ret;
}


vector<string> rotate(const vector<string>& arr){

	vector<string> ret(arr[0].size(), string(arr.size(), ' '));
	
	for(int i =0; i< arr.size(); i++)
		for(int j=0; j< arr[0].size(); j++)
			ret[j][arr.size()-i-1] = arr[i][j];

	return ret;
}

vector<rotation> generateRotations(vector<string> block){
	vector<rotation> ret (4);

	for(int k= 0; k< 4; k++){
		int originY = -1, originX =-1;
		for(int i=0; i < block.size(); i++){
			for(int j=0; j< block[i].size(); j++){
				if(block[i][j] == '#'){
					if(originY == -1){
						originY = i;
						originX = j;
					}
					ret[k].push_back(make_pair( i- originY, j- originX));
				}
			}
		}
		block = rotate(block);
	}

	sort(begin(ret), end(ret));
	ret.erase(unique(begin(ret), end(ret)), end(ret));

	return ret;
}

bool set(int y, int x, const rotation& r, int xlim, int ylim, int delta){
	bool answer = true;

	for(int i=0; i<r.size(); i++){
		
		int nx = x + r[i].second;
		int ny = y + r[i].first;

		if( nx < 0 || nx >= xlim  || ny <0 || ny >= ylim || (covered[ny][nx]+= delta) > 1){
			answer = false;
		}

	}


	return answer;
}


int simpleHeuristic(int H, int W, int r){
	
	int count = 0;

	for(int i =0; i< H; i++)
		for(int j=0; j<W; j++)
			if(covered[i][j] == 0) count+=1;

	return count / r;
}


void search(const vector<string>& board, const vector<rotation>& rotations, const int H, const int W, int count){

	if ( count + simpleHeuristic(H,W,rotations[0].size()) <  best ) return;

	int y= -1, x= -1;

	for(int i=0; i< H; i++){
		for(int j=0; j<W; j++)
			if(covered[i][j] == 0){
				y=i;
				x=j;
				break;
			}
		if(y != -1) break;
	}

	if( y == -1 ){
		best = max(best, count);
		return;
	}

	for(int i=0; i<rotations.size(); i++){
		if(set(y,x, rotations[i], H, W, 1))
			search(board, rotations, H, W, count +1);
		set(y,x, rotations[i], H, W, -1);
	}

	covered[y][x] = 1;

	search(board, rotations, H ,W, count);


	return ;
} 

int solve(vector<string>& board, vector<string>& block, vector<int>& n){

	vector<rotation> rotations = generateRotations(block);
	best = 0;

	for(int i=0; i<n[0]; i++)
		for(int j =0; j<n[1]; j++)
			covered[i][j] = (board[i][j] == '#' ? 1 : 0);

	search(board, rotations, n[0], n[1], 0);

	return best;
}



int main(void){

	fstream fd("data/게임판_덮기2.txt");
	string buf;

	getline(fd,buf);
	int test_cases = stoi(buf);

	while(test_cases > 0){

		// [H, W, R, C]
		getline(fd, buf);
		vector<int> n = split(buf);

		vector<string> board = get_object(fd, n[0], n[1]);
		vector<string> block = get_object(fd, n[2], n[3]);

		cout << solve(board, block, n)<< endl;
		test_cases--;
	}




	return 0;
}