#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>


using namespace std;

vector<int>& geth(const string& s){
	
	vector<int>* result = new vector<int>();
	stringstream ss(s);
	string temp;

	while(getline(ss, temp, ' ')){
		result->push_back(stoi(temp));
	}
	
	return *result;
}

int solve(vector<int>& h, int left, int right){

	stack<int> remaining;
	h.push_back(0);
	int ret = 0;

	for(int i =0; i < h.size(); i++){
		while(!remaining.empty() && h[remaining.top()] >= h[i]){
			int j = remaining.top();
			remaining.pop();
			int width ;
			if(remaining.empty())
				width = i;
			else 
				width = (i - remaining.top() - 1);
			ret = max(ret, h[j] * width);

		}
		remaining.push(i);

	}

	return ret;
}

int main(void){
	fstream fd("data/울타리_잘라내기.txt");
	string buf;

	getline(fd,buf);
	int test_cases = stoi(buf);
	
	while(test_cases > 0){
		getline(fd,buf);
		int n = stoi(buf);
		
		getline(fd,buf);
		vector<int> h = geth(buf);

		cout << solve(h,0, n-1) << endl;


		test_cases--;
	}

	return 0;
}