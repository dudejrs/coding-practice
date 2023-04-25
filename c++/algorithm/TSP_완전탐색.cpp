#include <iostream>
#include <random>
#include <limits>
#include <cmath>
#include <vector>
#include <iomanip>
#define N 10
#define MAX 987654321

using namespace std;

double** initialize() {
	default_random_engine gen(43);
	normal_distribution<double> dis(N, 3*N);

	double** w = new double*[N];
	for(int i=0;i<N;i++){
		w[i] = new double[N];
	}

	for (int i=0; i<N;i++){
		w[i][i] = MAX; 
		for(int j=0; j<i; j++){
			double tmp = abs(dis(gen));
			if((int)floor(tmp) % 37 <1 )tmp =MAX;
			
			w[i][j] = tmp;
			w[j][i] = tmp;
		}
	}

	return w;
}

double shortest_path(double** w, bool* visited, vector<int>& path, double currentLength){
	if(path.size() == N )
		return currentLength + w[path[0]][path.back()];

	double ret = MAX;

	for(int i=0; i<N; i++){
		if(visited[i]) continue;

		int cur = path.back();
		path.push_back(i);
		visited[i]=true;
		ret = min(ret, shortest_path(w,visited,path, currentLength+w[cur][i]));
		visited[i]=false;
		path.pop_back();
	
	}

	return ret;
}

void print_result (double** w, double ret){
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			if(w[i][j] == MAX) {
				cout << setw(5) << "-";
				cout << " ";
				continue;
			}
			cout <<fixed<<setw(5) << setprecision(2)<< w[i][j];
			cout << " ";
		}
		cout << endl;
	}

	cout << "result :  "<< fixed<< setprecision(2) << ret << endl;
}

int main(void){

	vector<int> path;
	double** w = initialize();
	bool visited[N];
	fill(visited,visited+N,false);
	path.push_back(0);
	double ret = shortest_path(w, visited, path, 0.);

	print_result(w,path,ret);


	return 0;
}