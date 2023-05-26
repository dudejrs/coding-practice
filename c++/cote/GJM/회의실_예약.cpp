#include <iostream>
#include <random>
#include <cmath>
#include <vector>
#include <algorithm>

#define N 30


using namespace std;




void initialize(int* begin, int* end){

	default_random_engine gen(43);
	uniform_int_distribution<int> dis(0, 1440);	
	normal_distribution<float> dis2(30, 30);

	for (int i=0; i<N; i++){

		begin[i] = dis(gen);
		end[i] = min(1440, begin[i] + abs(int(dis2(gen))));
	}
}


int solve(int* start, int* finish){

	vector<pair<int,int>> order;

	for(int i=0; i<N; i++){
		order.push_back(make_pair(finish[i], start[i]));
	}

	sort(begin(order),end(order));

	int earliest = 0, selected = 0;

	for(int i=0; i <order.size(); i++){
		int meetingBegin = order[i].second;
		int meetingEnd = order[i].first;

		if(earliest <= meetingBegin){
			earliest = meetingEnd;
			selected++;
		}
	}

	return selected;
}

bool canBeScheduled(int cur, int* start, int* end, bool* selected){
	int meetingBegin = start[cur];
	int meetingEnd = end[cur];

	for(int i=0; i<N; i++){
		if(!selected[i]) continue;
		if(start[i]< meetingBegin &&  meetingBegin < end[i]) return false;
		if(start[i]< meetingEnd &&  meetingEnd < end[i]) return false;
	}


	return true;
}

int schedule(int cur, int* start, int* finish, bool* selected){
	if(cur == N)
		return 0;

	int ret = 0;

	if(canBeScheduled(cur, start, finish, selected)){
		selected[cur] = true;
		ret = max(ret, schedule(cur+1, start, finish, selected)+1);
		selected[cur] = false;
	}

	return max(ret, schedule(cur+1, start, finish, selected));
	
}

int solveDP(int* start, int* finish){
	bool* selected = new bool[N];

	return schedule(0, start, finish, selected);
}

int main(void){

	int begin[N], end[N];


	initialize(begin, end);

	solve(begin,end);

	cout << solve(begin,end) << endl;
	cout << solveDP(begin,end) << endl;

	return 0;
}