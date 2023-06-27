#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

#define TEST_CASES 10
#define N 5

using namespace std;

vector<double> initialize(default_random_engine& gen){
	normal_distribution<double> dis(N*10, 7.5*N);
	vector<double> ret;

	for(int i =0; i < 2*N; i++){
		ret.push_back(abs(dis(gen)));
	}

	sort(begin(ret), end(ret));

	return ret;
}

bool decision(const vector<double>& locations, int cameras, double gap){

	double limit = -1;
	int installed = 0;

	for(int i =0; i<locations.size(); i++){
		if(limit <= locations[i]){
			++installed;
			limit = locations[i] + gap;
		}
	}

	return cameras <= installed;
}


double optimize(const vector<double>& locations, int cameras){
	double lo = 0.1, hi = accumulate(begin(locations), end(locations), 0, [](double a, double b){return a+b;});

	for(int i =0 ; i< 100; i++){
		double mid = (lo+hi)/2.0;

		if(decision(locations,cameras,mid)){
			lo = mid;
		} else {
			hi = mid;
		}
	}
	return lo;
}


int main(void){
	
	default_random_engine gen(43);
	uniform_int_distribution<int> dis(2, N);

	int test_cases = TEST_CASES;

	while( test_cases > 0 ){

		vector<double> locations = initialize(gen);
		int cameras = dis(gen);

		cout << optimize(locations, cameras) << endl;
		test_cases--;
	}

	return 0;
}

