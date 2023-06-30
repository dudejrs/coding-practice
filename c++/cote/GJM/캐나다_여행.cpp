#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#define N 5001
#define MAX 8030000

using namespace std;

int l[N], m[N], g[N];

vector<int> split(const string& s){
	stringstream ss(s);
	string buf;
	vector<int>ret;

	while(getline(ss,buf, ' ')){
		ret.push_back(stoi(buf));
	}

	return ret;
}

bool decision(int n, int k, int cur){
	int ret= 0;
	
	for(int i =0; i<n; i++){
		if(cur >= l[i]- m[i]){
			ret += (min(cur, l[i]) - (l[i]-m[i]))/g[i] +1;
		}
	}

	return ret >= k;
}


int search(int n,int k){

	int lo = 0, hi = MAX;

	while(lo+1< hi){

		int mid = (lo+hi)/2;

		if(decision(n,k,mid)){
			hi = mid;
		}else {
			lo = mid;
		}

	}


	return hi;
}


int main(void){

	fstream fd("data/캐나다_여행.txt");
	string buf;

	getline(fd,buf);
	int test_cases = stoi(buf);

	while(test_cases > 0){
		
		getline(fd, buf);
		vector<int> tmp = split(buf);

		int n = tmp[0];
		int k = tmp[1];

		for(int i=0; i<n; i++){
			getline(fd, buf);
			vector<int> v = split(buf);

			l[i] = v[0];
			m[i] = v[1];
			g[i] = v[2];
		}

		cout << search(n,k) << endl;


		test_cases--;
	}



	return 0;
}

