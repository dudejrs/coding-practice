#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#define MAX_VAL 987654321

using namespace std;

struct Point {
	double x,y;

	Point(double x, double y) : x(x), y(y){}
};

typedef pair<Point,Point> Edge;

vector<int> split(const string& s){
	vector<int> ret;
	stringstream ss(s);
	string buf;

	while(getline(ss, buf, ' ')){
		ret.push_back(stoi(buf));
	}

	return ret;
}

vector<Point> getPoints(const string& s, int n){
	vector<Point> ret;
	stringstream ss(s);
	string buf;

	while(n>0){
		getline(ss, buf, ' ');
		double x = stod(buf);
		getline(ss, buf, ' ');
		double y = stod(buf);
		ret.emplace_back(x,y);
		n--;
	}

	return ret;
}

double minX(vector<Point>& hull){
	double ret = MAX_VAL;
	for(auto p: hull){
		ret = min(ret, p.x);
	}
	return ret;
}

double maxX(vector<Point>& hull){
	double ret = - MAX_VAL;
	for(auto p: hull){
		ret = max(ret, p.x);
	}
	return ret;
}

bool between(const Point& a, const Point& b, double x){
	return (a.x <= x && x <= b.x)  || (b.x<= x && x<= a.x);
}

double at(const Point& a, const Point& b, double x){
	double dy = b.y - a.y, dx = b.x - a.x;
	return a.y + dy * (x - a.x)/dx;
}

void decompose(vector<Point>& hull, vector<Edge>& upper, vector<Edge>& lower ){

	int n = hull.size();

	for(int i=0; i< n; i++){
		if(hull[i].x < hull[(i+1)%n].x)
			lower.push_back(make_pair(hull[i], hull[(i+1)%n]));
		else if(hull[i].x > hull[(i+1)%n].x)
			upper.push_back(make_pair(hull[i], hull[(i+1)%n]));
	}
	
}

double vertical (double x, vector<Edge>& upper, vector<Edge>& lower){
	double minUp = 1e20, maxLow =-1e20;

	for(int i=0; i< upper.size(); i++){
		if(between(upper[i].first, upper[i].second, x))
			minUp = min(minUp, at(upper[i].first, upper[i].second, x));
	}

	for(int i=0; i<lower.size(); i++){
		if(between(lower[i].first, lower[i].second, x))
			maxLow = max(maxLow, at(lower[i].first, lower[i].second, x));
	}

	return minUp-maxLow;
}

double solve(vector<Point>& hull1, vector<Point>& hull2){

	double lo = max(minX(hull1), minX(hull2));
	double hi = min(maxX(hull1), maxX(hull2));

	vector<Edge> upper;
	vector<Edge> lower;

	decompose(hull1, upper, lower);
	decompose(hull2, upper, lower);

	if (lo < hi) return 0;

	for(int i= 0; i< 100; i++){
		double aab = (2* lo + hi) / 3;
		double abb = (lo + 2* hi) / 3;

		if(vertical(aab, upper, lower) < vertical(abb, upper, lower))
			lo = abb;
		else 
			hi = abb;
	}

	return max((double) 0 , vertical(hi, upper, lower));
}

int main(void){

	fstream fd("data/꽃가루_화석.txt");
	string buf;

	getline(fd,buf);
	int test_cases = stoi(buf);

	while(test_cases > 0){
		getline(fd, buf);
		vector<int> n = split(buf);

		getline(fd,buf);
		vector<Point> hull1 = getPoints(buf, n[0]);
		getline(fd,buf);
		vector<Point> hull2 = getPoints(buf, n[1]);

		cout << solve(hull1, hull2)<< endl;

		test_cases--;
	}


	return 0;
}