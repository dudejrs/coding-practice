#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#define N 8
#define MAX_VALUE 10

using namespace std;

int candidates[1<<N][MAX_VALUE*N];


vector<int> initialize(){
	vector<int> ret;

	default_random_engine gen(43);
	uniform_int_distribution<int> dis(0,MAX_VALUE);

	for(int i=0; i<N; i++){
		int tmp = dis(gen);
		while(true){
			int j=0;
			for( ;j<i; j++){
				if(ret[j] == tmp) 
					break;
			}
			if(j == i) break;
			tmp = dis(gen);
		}
		ret.push_back(tmp);
	}


	sort(begin(ret),end(ret));

	return ret;
}


int getSum(vector<int>& v, int mask){
	int sum =0;

	int cur=0;
	while(cur < N){
		if(mask & 1) sum+= v[cur];
		mask = mask >> 1;
		cur++;
	}

	return sum;
}


void print_subsets(vector<int>& v, int mask){
	int count = 0;
	while(count < N){
		if(mask & 1){
			cout << v[count] << " ";
		}
		mask = mask >> 1;
		count ++;
	}
	cout << endl;
}

void visit_all_subsets(vector<int>& v){

	for(int set = 0; set < (1<<N); set +=1 ){
		
		int subset = set;
		while(true){
			if(subset == 0) break;
			print_subsets(v,subset);
			subset = (subset-1) & set;
		}
	}
}


void visit_all_subsets2(vector<int>& v){	
	memset(candidates,0, sizeof(candidates));

	for(int set = 0; set < (1<<N); set +=1 ){

		int sum = getSum(v, set);

		int subset = set;

		while(true){
			if(subset == 0) break;
			candidates[subset][sum] |= (~subset & set) ;
			subset = (subset-1) & set;
		}
	}

}

void getCandidate(vector<int>& v, int sum ,int known){
	
	visit_all_subsets2(v);
	print_subsets(v, candidates[known][sum]);
}

	

int main(){
	
	vector<int> v = initialize();


	/*
	**********************************
	1. 모든 subset을 중복포함하지 않고 순회하기
	**********************************
	*/

	/*
	*******************************
	2. 모든 subset을 중복포함해서 순회하기
	*******************************
	*/
	visit_all_subsets(v);
	cout << endl<< endl;

	// 기존 set [known]에
	// 모든 원소의 합이 [sum] 되도록
	// 추가할 수 있는 모든 후보 원소들을 구하기

	cout << "v : " ;
	print_subsets(v, (2<<N)-1);
	getCandidate(v, 16, 3);




	return 0;
}