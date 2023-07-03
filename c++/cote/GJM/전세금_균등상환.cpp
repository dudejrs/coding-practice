#include <iostream>
#include <random>

#define TEST_CASES 10

using namespace std;


double balance(double amount, int duration, double rates, double montlyAmount){

	double balance = amount;

	for(int i=0; i< duration; i++){
		balance *= (1.0 + (rates / 12.0)/100.0);
		balance -= montlyAmount;
	}

	return balance;
}

double payment(double amount, int duration, double rates){
	double lo = 0, hi = amount * (1.0 + (rates / 12.0) / 100);

	for(int i= 0; i<100; i++){
		double mid = (lo+hi)/2.0;

		if(balance(amount, duration, rates, mid) <= 0){
			hi = mid;
		}else {
			lo = mid;
		}
	}

	return hi;
}

int main(void){

	default_random_engine gen(43);
	uniform_int_distribution<int> duration_dist(1,120);
	uniform_real_distribution<double> amount_dist(0,10000);
	uniform_real_distribution<double> rate_dist(0,1);

	for(int i=0; i< TEST_CASES; i++){
		double amount = amount_dist(gen);
		int duration = duration_dist(gen);
		double rates = rate_dist(gen);
		cout << payment(amount, duration, rates) << endl;

	}


	return 0;
}