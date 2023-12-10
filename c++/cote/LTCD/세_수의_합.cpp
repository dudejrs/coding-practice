#include <iostream>
#include <random>
#include <vector>

#define TEST_CASE 10
#define N 10000

using namespace std;


vector<int*> solve(int* nums, int n){
	
	vector<int*> ret;
	sort(nums, nums+n);

	for(int i=0; i<n; i++){

		int lo = i+1; 
		int hi = n-1;

		while(lo < hi){
			int sum = nums[i] + nums[lo] + nums[hi];
			if(sum > 0){
				hi--;
			}
			if(sum < 0){
				lo++;
				continue;
			}
			if(sum == 0){
				ret.push_back(new int[3]{nums[i], nums[lo], nums[hi]});
				while(lo < hi &&nums[hi-1] == nums[hi]){
					hi--;
				}
				while(lo < hi && nums[lo +1] == nums[lo]){
					lo++;
				}

				lo++;
				hi--;
			}
		}

	}

	return ret;
}

int main(void){

	for(int test_case=0; test_case<TEST_CASE; test_case++){
		default_random_engine gen(43);
		uniform_int_distribution<int> dis(-N,N);

		int n = gen() % (N-100) + 100;
		int* nums = new int[n];

		for(int i=0; i<n; i++){
			nums[i] = dis(gen);
		}

		vector<int*> ret = solve(nums, n);
		cout << "[";
		for(int i=0; i<ret.size(); i++){
			cout <<"[";
			for(int j=0; j<3; j++){
				cout << ret[i][j]<< ",";
			}	
			cout <<"], ";
		}
		cout <<"]" << endl;

		delete[] nums;
	}

	return 0;
}