#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#define N 10
#define K 10

using namespace std;

vector<int> split(const string& s){
	stringstream ss(s);
	string buf;
	vector<int> ret;

	while(getline(ss, buf, ' ')){
		ret.push_back(stoi(buf));
	}
	return ret;
}


/*
	sum(r[i])/sum(c[i]) <= lim
	sum(r[i]) <= lim * sum(c[i])
	0 <= lim * sum(c[i]) - sum(r[i])
*/

bool decision(double lim, int n, int k, int* c, int* r){

	vector<double> v;
	for(int i=0; i<n; i++){
		v.push_back(lim * c[i] - r[i]);
	}

	sort(begin(v), end(v));
	reverse(begin(v), end(v));

	double sum = 0;

	for(int i=0; i<k; i++){
		sum += v[i];
	}

	return sum >= 0;
}

double optimize(int n, int k, int* c, int* r){

	double lo = 0, hi = 1;


	for(int i =0; i<100; i++){
		double mid = (lo+hi)/2.0;
		if(decision(mid,n,k,c,r))
			hi = mid;
		else 
			lo = mid;
	}

	return lo;
}

int main(void){

	fstream fd("data/수강철회.txt");
	string buf;

	getline(fd,buf);
	int test_cases = stoi(buf);

	while(test_cases > 0){

		getline(fd, buf);
		
		vector<int> token = split(buf);
		
		int n = token[0];
		int k = token[1];

		int c[n];
		int r[n];

		getline(fd, buf);
		token = split(buf);

		for(int i=0; i<n; i++){
			r[i] = token[2*i];
			c[i] = token[2*i+1];
		}

		cout << optimize(n,k,c,r) << endl;


		test_cases--;
	}

	return 0;
}

