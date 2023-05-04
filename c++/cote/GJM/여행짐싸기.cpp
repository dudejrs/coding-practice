#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#define N 100
#define W 1000

using namespace std;

int cache[W+1][N+1];

vector<string>& split(string& s){
	stringstream ss(s);
	string temp;
	vector<string>* ret = new vector<string>();

	while(getline(ss,temp,' ')){
		ret->push_back(temp);
	}

	return *ret;
} 


void initialize(fstream& fd, vector<string>& name, vector<int>& volume, vector<int>& need, int& capcity){
	string buf;


	getline(fd,buf);
	vector<string> c = split(buf);
	int n = stoi(c[0]);
	capcity= stoi(c[1]);

	for(int i=0; i<n; i++){
		getline(fd,buf);
		vector<string> v = split(buf);
		name.push_back(v[0]);
		volume.push_back(stoi(v[1]));
		need.push_back(stoi(v[2]));
	}

}
int pack(int capcity, int cur, vector<string>& name, vector<int>& volume, vector<int>& need){
	
	if (cur == name.size()) return 0;

	int& ret = cache[capcity][cur];
	if(ret != -1 ) return ret;

	ret = pack(capcity, cur+1, name, volume, need);

	if( capcity >= volume[cur]){
		ret = max(ret, pack(capcity-volume[cur], cur+1, name, volume, need) + need[cur]);
	}

	return ret;
}


void getList(int capcity, int cur, vector<string>& answer, vector<int>& volume, vector<int>&need, vector<string>& name){
	if(cur == name.size()) return;
	if(pack(capcity, cur, name, volume, need) == pack(capcity, cur+1, name, volume, need)){
		getList(capcity, cur+1, answer, volume,need, name);
		return;
	}
	answer.push_back(name[cur]);
	getList(capcity-volume[cur],cur+1, answer,volume, need, name);

}

void solve(vector<string>& name, vector<int>& volume, vector<int>& need, const int capcity){
	
	memset(cache, -1, sizeof(cache));

	vector<string> answer;

	cout << pack(capcity, 0, name, volume, need) << endl;

	getList(capcity, 0, answer, volume, need, name);

	for(auto s : answer) {
		cout << s << " ";
	}
	cout << endl;
}

int main(void){

	fstream fd("data/여행짐싸기.txt");
	string buf;

	getline(fd,buf);
	int test_cases = stoi(buf);

	while(test_cases > 0){
		
		vector<string> name;
		vector<int> volume;
		vector<int> need;
		int capcity;

		initialize(fd, name, volume, need, capcity);

		solve(name,volume,need,capcity);

		test_cases--;
	}


	return 0;
}


