#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

struct RNG {
	int seed, a, b;
	RNG(int a, int b) : a(a), b(b), seed(1983) {}
	
	int next() {
		int ret = seed;
		seed = ((seed * (long long) a) + b) % 20090711;

		return ret;
	}
};

int* split(const string& s) {
	stringstream ss(s);
	string buf;
	int* ret = new int[3];

	for(int i =0; i< 3; i++){
		getline(ss, buf, ' ');
		ret[i] = stoi(buf);
	}

	return ret;
}

int solve(int n, RNG rng){
	priority_queue<int, vector<int>, less<int>> maxHeap;
	priority_queue<int, vector<int>, greater<int>> minHeap;
	int ret = 0;

	/*
	반복문 불변식 :
	1. maxHeap의 크기는 minHeap의 크기와 같거나 1 더 크다 
	2. maxHeap.top() <= minHeap.top()
	*/

	for (int i=0; i<n; i++) {
		if (maxHeap.size() == minHeap.size()) {
			maxHeap.push(rng.next());
		} else {
			minHeap.push(rng.next());
		}

		// 2번 불변식이 깨질 경우 복구한다 
		if (!minHeap.empty() && !maxHeap.empty() && minHeap.top() < maxHeap.top()){

			int a = maxHeap.top();
			int b = minHeap.top();

			maxHeap.pop(); minHeap.pop();
			
			maxHeap.push(b); 
			minHeap.push(a);
		}

		ret = (ret + maxHeap.top()) % 20090711;
	}

	return ret;
}

int main(void){
	string buf;
	fstream fd ("data/변화하는_중간값.txt");
	
	getline(fd, buf);

	int testCase = stoi(buf);

	while (testCase > 0) {

		getline(fd, buf);
		int* nums = split(buf);
		
		getline(fd, buf);
		int answer = stoi(buf);

		RNG rng(nums[1], nums[2]);

		cout << "answer : " << answer << ", solved : " << solve(nums[0], rng) <<endl;
		testCase--;
	}

	return 0;
}