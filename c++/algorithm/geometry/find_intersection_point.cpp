#include <iostream>
#include <random>
#define TEST_CASES 10

using namespace std;

pair<double,double> solve(int poly1[3], int poly2[3]){

	int a1=poly1[0], b1=poly1[1], c1=poly1[2];
	int a2=poly2[0], b2=poly2[1], c2=poly2[2];

	double x = (b1*c2 - b2*c1) / (a1*b2 - a2*b1);
	double y =  (a2*c1 - a1*c2)/ (a1*b2 - a2*b1);

	return make_pair(x,y);
}

int main(void){

	default_random_engine gen(43);

	for(int it=0; it<TEST_CASES; it++){
		normal_distribution<double> dis(0, 10);

		int poly1[3], poly2[3];
		for(int i =0; i <3 ; i++)
			poly1[i] = 	floor(dis(gen));
		for(int i =0; i <3 ; i++)
			poly2[i] = 	floor(dis(gen));
	
		pair<double, double> p = solve(poly1, poly2);
		cout << p.first << "," << p.second<< endl;	

	}

	return 0;
}