#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

#define TEST_CASES 10
#define N 5

using namespace std;



bool check (vector<bool>& visited, vector<vector<int>>& foods, vector<int>& goals){

	int total_kcal = 0;
	int total_carbonhydrate = 0, total_protein = 0, total_fat = 0;
	int goals_kcal = goals[0] * 4 + goals[1] * 4 + goals[2] * 9;


	for(int i=0; i<foods.size(); i++){
		if( !visited[i] ) continue;
		
		total_kcal += foods[i][0] *4 + foods[i][1] * 4 + foods[i][2] * 9;
		total_carbonhydrate += foods[i][0];
		total_protein += foods[i][1];
		total_fat += foods[i][2];

		if( total_carbonhydrate > goals[0] || total_fat > goals[2] || total_kcal > goals_kcal ) return false;
	}



	return goals[1] <= total_protein ;
}


int search(int cur, vector<bool>& visited, vector<vector<int>>& foods, vector<int>& goals){
		
	if(cur == foods.size()){
		if(check(visited, foods, goals)) return 1;
		return 0;
	}

	int ret = 0;

	ret += search(cur+1, visited, foods, goals);
	visited[cur] = true;
	ret += search(cur+1, visited, foods, goals);
	visited[cur] = false;

	return ret;
}


int solve(vector<vector<int>>& foods, vector<int>& goals){

	vector<bool> visited(foods.size(), false);

	return search(0, visited, foods, goals);
}


int main(void){

	default_random_engine gen(43);
	for(int it=0; it<TEST_CASES; it++){
		normal_distribution<float> dis1(30, 20);
		normal_distribution<float> dis2(20, 10);
		normal_distribution<float> dis3(30*N/2, 10*N/2);

		vector<vector<int>> foods(N);
		for(int i =0; i<N ;i++){
			foods[i].push_back(abs(dis1(gen)));
			foods[i].push_back(abs(dis1(gen)));
			foods[i].push_back(abs(dis2(gen)));
		}


		vector<int> goals;
		for(int j=0; j<3; j++){
			goals.push_back(abs(dis3(gen)));
		}
		goals[1] = abs(dis2(gen))*(N-3);


		

		 cout << solve(foods, goals) << endl;
	}


	return 0;
}