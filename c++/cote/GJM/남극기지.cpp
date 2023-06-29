#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#define N 100
#define MAX 987654321

using namespace std;


typedef pair<double,double> Point;

double dist[N+1][N+1];

Point getPoints(const string& s){

	stringstream ss(s);
	string buf;

	getline(ss, buf, ' ');
	double x = stod(buf);
	getline(ss, buf, ' ');
	double y = stod(buf);

	return make_pair(x,y);
}


void calculateDistance(vector<Point>& v, int n){
	for(int i =0; i <n ;i++){
		for(int j=0; j<i; j++){
			int x1 = v[i].first, x2 = v[j].first;
			int y1 = v[i].second, y2 = v[j].second;			

			int d = sqrt(pow(y2-y1,2)+pow(x2-x1,2));
			dist[i][j] = d;
			dist[j][i] = d;
		}
	}
}

bool decision(double d, int n){
	vector<bool> visited(n, false);
	visited[0] = true;
	queue <int> q;
	q.push(0);
	int seen = 0;
	while(!q.empty()){
		int cur = q.front();
		q.pop();
		++ seen;

		for(int i =0; i<n; i++){
			if(!visited[i] && dist[cur][i] <= d){
				visited[i] = true;
				q.push(i);
			}
		}
	}

	return seen == n;
}

double optimize(int n){

	double lo = 0, hi = MAX;
	for(int it =0; it< 100; it++){
		
		double mid = (lo + hi) /2;

		if(decision(mid, n)){
			hi = mid;
		}else {
			lo = mid;
		}
	}

	return lo;
}

int main(void){

	fstream fd("data/남극기지.txt");
	string buf;

	getline(fd, buf);
	int test_cases = stoi(buf);
	
	while(test_cases > 0 ){

		getline(fd,buf);
		int n= stoi(buf);

		vector<Point> v;
		for(int i=0; i<n; i++){
			getline(fd, buf);
			v.push_back(getPoints(buf));
		}

		calculateDistance(v,n);

		cout << fixed <<  setprecision(6) <<optimize(n)<< endl;


		test_cases--;
	}


	return 0;
}