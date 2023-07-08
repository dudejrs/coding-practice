#include <iostream>
#define TEST_CASES 10
#include <random>

using namespace std;

bool is_stable(int n, int* explodes, int set) {
	for(int i=0; i<n; i++)
		if((set & (1 << i)) && (set & explodes[i]))
			return false;

	return true;
}

int solve(int n, int* explodes){
	int ret = 0;

	for(int set = 1; set < (1 << n) ; set++){
		if(!is_stable(n, explodes, set)) continue;
		bool canExtend = false;

		for(int add =0; add<n; add++){
			if((set & (1 << add)) == 0 && ((set & explodes[add]) == 0)){
				canExtend = true;
				break;
			}
		}

		if(!canExtend) {
			ret++;
			cout <<"[sol] " << set << "/" << __builtin_popcount(set) << endl;
		}
	}


	return ret;
}

int main(void){

	default_random_engine gen(43);
	uniform_int_distribution<int> dis(1, 10);


	for(int it=0; it< TEST_CASES; it++){
		int n = (dis(gen) +5)% 20;
		uniform_int_distribution<int> dis2(0, (1 << n));

		int explodes[n];
		for(int i=0; i< n; i++){
			explodes[i] = dis2(gen) & ~(1 << i);
		}

		cout << "[n] " <<  n<<endl;
		cout << solve(n, explodes) << endl;

	}



	return 0;
}