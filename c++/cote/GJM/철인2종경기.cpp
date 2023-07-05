#include <iostream> 
#include <random>
#include <vector>
#define TEST_CASES 10
#define N 10
#define SPEED 30
#define TRACK_LENGTH 100

using namespace std;

vector<double> initialize(default_random_engine& gen){
	
	normal_distribution<double> dis(SPEED, SPEED/5);
	vector<double> ret;

	for(int i=0; i<N; i++){
		ret.push_back(abs(dis(gen)));
	}

	return ret;
}

double time(double run, double run_speed, double cycle_speed){
	double cycle = TRACK_LENGTH -run;
	return run / run_speed + cycle / cycle_speed;
}

double diff(double r, vector<double>& run_speed, vector<double>& cycle_speed){
	int n = run_speed.size();
	double cheater = time( r, run_speed[n-1], cycle_speed[n-1]);
	double others = time( r, run_speed[0], cycle_speed[0]);

	for(int i=1; i< n-1; i++)
		others = min(others, time( r, run_speed[i], cycle_speed[i]));

	return others- cheater;
}

double solve(vector<double>& run_speed, vector<double>& cycle_speed){
	double lo = 0, hi = TRACK_LENGTH ;

	for(int i=0 ;i < 100; i++){
		double aab = (2*lo + hi)/3;
		double abb = (lo + 2*hi)/3;

		if(diff(aab,run_speed, cycle_speed) > diff(abb,run_speed,cycle_speed))
			hi = abb;
		else 
			lo = aab;
	}

	return (lo+hi)/2;
}

int main(void){
	
	default_random_engine gen(43);	
	
	for(int i=0; i< TEST_CASES; i++){
		vector<double> run_speed = initialize(gen);
		vector<double> cycle_speed = initialize(gen);

		cout << solve(run_speed, cycle_speed) << endl;

	}

	return 0;
}