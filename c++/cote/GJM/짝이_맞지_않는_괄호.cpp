#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <stack>

using namespace std;

string opening = "({[" , closing = ")}]";

bool solve(const string& formula){

	stack<int> s;
	for(int i =0; i<formula.length(); i++){
		int j = opening.find(formula[i]);
		if(j != -1){
			s.push(j);
			continue;
		}

		if(s.empty()) return false;
		if(s.top() != closing.find(formula[i])) return false;
		s.pop();
	}


	return true;
}

int main(void){

	fstream fd("data/짝이_맞지_않는_괄호.txt");
	string buf;

	getline(fd, buf);
	int test_cases = stoi(buf);
	
	while(test_cases > 0){

		getline(fd,buf);

		cout << boolalpha << solve(buf) << endl;

		test_cases--;
	}

	return 0;
}