#include <iostream>
#include <random>
#include <vector>
#include <iomanip>

#define TEST_CASES 10
#define N 10

using namespace std;

bool under_budget(double limit, vector<int>& budgets, int m){
	double total = 0;

	for(auto budget : budgets)
		total += (budget <= limit) ? budget : limit;

	return total <= m ;
}

double solve(vector<int>& budgets, int m){

	double max_budget = *max_element(begin(budgets), end(budgets));

	double lo =0, hi= max_budget;

	// lo <= x < hi
	for(int it=0; it < 100; it++){
		double mid = (lo + hi)/2;

		if(under_budget(mid, budgets, m))
			lo = mid;
		else 
			hi = mid;
		
	}

	return 	lo;
}

int main(void){
	
	default_random_engine gen(43);
	normal_distribution<float> dis2(100, 50); 

	for(int it =0; it<TEST_CASES; it++){
		vector<int> budgets;
		for(int i=0; i<N; i++)
			budgets.push_back(abs(floor(dis2(gen))));
		int m = dis2(gen) * N;

		cout << fixed << setprecision(3) << solve(budgets, m) << endl;
		cout << endl;
	}

	return 0;
}