#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<string> get_orders(const string& s){
	stringstream ss(s);
	string buf;
	vector<string> ret;
	while(getline(ss, buf))
		ret.push_back(buf);

	return ret;
}

vector<int> get_courses(const string& s){
	stringstream ss(s);
	string buf;
	vector<int> ret;

	while(getline(ss, buf)){
		ret.push_back(stoi(buf));
	}

	return ret;

}


vector<vector<string>> solve(vector<string>& orders, vector<int>& courses){
	vector<vector<string>> ret;

	return ret;
}


int main(void){

	fstream fd("data/메뉴_리뉴얼.txt");
	string buf;

	getline(fd,buf);
	int test_cases = stoi(buf);

	while(test_cases > 0){

		getline(fd,buf);
		vector<string> orders = get_orders(buf);
		getline(fd,buf);
		vector<int> courses = get_courses(buf);		

		vector<vector<string>> solutions = solve(orders, courses);

		cout << "[";
		for(auto solution :solutions){
			cout << "[";
			for(auto item : solution)
				cout << item << " ";
			cout << "]"<< endl;
		}
		cout << "]"<< endl;


		test_cases--;
	}

	return 0;
} 