#include <iostream>
#include <random>
#include <iomanip>

#define TEST_CASES 10
#define L 100

using namespace std;


vector<double> differentiate(const vector<double>& poly){
	vector<double> ret;

	int n = poly.size()-1;
	int i =0;
	while( n > 0 && i <= n){
		ret.push_back(n * poly[i]);
		i++;
		n--;
	}

	return ret;	
}

vector<double> solveNaive(const vector<double>& poly){

	int n = poly.size()-1;
	
	vector<double> ret;
	
	int a = poly[0];
	int b = poly[1];

	if (n == 1){
		ret.push_back((-b)/a);
		return ret;
	} 

	int c = poly[2];

	int D = b * b - (4 * a * c);


	if( D > 0 ){

		double d = sqrt(D);

		ret.push_back((-b-d)/(2.0 * a));
		ret.push_back((-b+d)/(2.0 * a));
	}
	if( D == 0 ){
		ret.push_back((-b)/(2.0*a));
	}

	return ret;	
}

double evaluate(const vector<double>& poly, double x){

	int n = poly.size()-1;
	int cur = 1;
	int sum = 0;

	for(int i= n; i >= 0; i--, cur *= x){
		sum += poly[i] * cur;
	}

	return sum;
}

vector<double> solve(const vector<double>& poly){
	int n = poly.size()-1;
	if(n<=2) return solveNaive(poly);

	vector<double> deriative =  differentiate(poly);
	vector<double> sols = solve(deriative);

	sols.insert(begin(sols), -L-1);
	sols.insert(end(sols), L+1);

	vector<double> ret;
	for(int i=0; i<sols.size()-1; i++){

		double x1 = sols[i], x2= sols[i+1];
		double y1 = evaluate(poly, x1), y2 = evaluate(poly,y2);

		if(y1 * y2 > 0) continue;
		if(y1 > y2) {
			swap(y1,y2);
			swap(x1,x2);
		}


		for(int iter = 0; iter < 100; iter++){
			double mx = (x1 +x2)/2;
			double my = evaluate(poly, mx);

			if(y1*my <= 0){
				y2 = my;
				x2 = mx;
			}else {
				y1 = my;
				x1 = mx;
			}

		}

		ret.push_back((x1+x2)/2);
	}

	sort(begin(ret),end(ret));

	return ret;
}

int main(void){

	default_random_engine gen(43);
	uniform_real_distribution<double> dis1(1,10);
	uniform_real_distribution<double> dis2(-100,100);

	for(int i=0; i<TEST_CASES; i++){
		
		int n = dis1(gen);
		vector<double> poly;
		for(int i=0; i<n+1; i++){
			poly.push_back(dis2(gen));	
		}

		vector<double> ret=  solve(poly);

		cout << "[solution] :  ";
		for(auto& val : ret){
			cout << fixed << setprecision(2) << val << " ";
		}
		cout << endl;
	}


	return 0;
}