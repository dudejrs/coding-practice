#include <iostream>
#include <random>
#include <vector>
#include <map>
#include <iomanip>

#define INF 1e200
#define N 10
#define MAX 20


using namespace std;
using function_t = void(*)(double**, vector<int>& , vector<bool>& , double, double&);

double** initialize(default_random_engine& gen){
	
	uniform_real_distribution<double> dis(1, 5*10); 

	double** ret = new double* [N];
	for(int i=0; i<N; i++){
		ret[i] = new double [N];
	}

	for(int i=0; i<N; i++){
		for(int j=0; j<i; j++){
			double tmp = dis(gen);
			if(fmod(tmp, 17)  < 1) tmp = INF;
			ret[i][j] = tmp;
			ret[j][i] = tmp;
		}
		ret[i][i] = INF;
	}

	for(int i=0; i<N; i++){
		for(int j =0; j<N; j++){
			if (ret[i][j] == INF )
				cout << setw(7)<<  fixed << setprecision(3)<<"-"<< " " ;

			else 
				cout <<setw(7) <<  fixed << setprecision(3) << ret[i][j]<< " ";
		}
		cout << endl;
	}

	return ret;
}


// 1. simple 완전탐색
void serach0 (double** W, vector<int>& path, vector<bool>& visited, double currentLength, double& best){
	int cur = path.back();

	if (path.size() == N) {
		best = min(best, currentLength + W[cur][0]);
		return;
	}

	for(int i=0; i< N; i++){		
		if(visited[i]) continue;
		path.push_back(i);
		visited[i] = true;
		serach0(W, path, visited, currentLength+ W[cur][i], best);
		path.pop_back();
		visited[i] = false;
	}
}

// 2.  최적해 보다 나빠지면 그만두기
void search1 (double** W, vector<int>& path, vector<bool>& visited, double currentLength, double& best){
	int cur = path.back();
	if(currentLength >= best) return;
	if (path.size() == N) {
		best = min(best, currentLength + W[cur][0]);
		return;
	}

	for(int i=0; i< N; i++){		
		if(visited[i] ) continue;
		path.push_back(i);
		visited[i] = true;
		search1(W, path, visited, currentLength+ W[cur][i], best);
		path.pop_back();
		visited[i] = false;
	}	
}

// 3. 휴리스틱을 이용 : "가장 짧은 간선의 길이 만을 모으면 실제 최단 경로 이하의 값이 될수 밖에 없음" 을 이용 



double simpleHeuristic(vector<bool>& visited, vector<double>& minEdge){
	double ret = minEdge[0];

	for(int i=0; i<N; i++){
		if(visited[i]) continue;
		ret += minEdge[i];
	}

	return ret;
}

void search3_ (double** W, vector<int>& path, vector<bool>& visited, double currentLength, double& best, vector<double>& minEdge){
	int cur = path.back();

	if(best <= currentLength + simpleHeuristic(visited, minEdge)) return;

	if (path.size() == N) {
		best = min(best, currentLength + W[cur][0]);
		return;
	}

	for(int i=0; i< N; i++){		
		if(visited[i]) continue;
		path.push_back(i);
		visited[i] = true;
		search3_(W, path, visited, currentLength+ W[cur][i], best, minEdge);
		path.pop_back();
		visited[i] = false;
	}
}

void search3(double** W, vector<int>& path, vector<bool>& visited, double currentLength, double& best){

	vector<double> minEdge(N);

	for(int i=0; i<N; i++){
		minEdge[i] = INF;
		for(int j =0; j<N; j++){
			if(i!=j) minEdge[i] = min(minEdge[i], W[i][j]);
		}
	}

	search3_(W, path, visited, currentLength, best, minEdge);

}


// 4. 가까운 도시부터 방문하기
void search4_ (double** W, vector<int>& path, vector<bool>& visited, double currentLength, double& best, int nearest[N][N-1]){
	int cur = path.back();

	if (path.size() == N) {
		best = min(best, currentLength + W[cur][0]);
		return;
	}

	for(int j=0; j< N-1; j++){		
		int i = nearest[cur][j];
		if(visited[i]) continue;
		path.push_back(i);
		visited[i] = true;
		search4_(W, path, visited, currentLength+ W[cur][i], best, nearest);
		path.pop_back();
		visited[i] = false;
	}

}

void search4 (double** W, vector<int>& path, vector<bool>& visited, double currentLength, double& best){

	int nearest[N][N-1];

	for(int i=0; i<N; i++){
		vector<pair<double,int>> order;
		for(int j=0; j<N; j++){
			if(i==j) continue;
			order.push_back(make_pair(W[i][j], j));
		}
		sort(begin(order), end(order));
		for(int j=0; j<N-1; j++){
			nearest[i][j] = order[j].second;
		}
	}

	search4_(W, path, visited, currentLength, best, nearest);
}


/* 5. 지나온 경로를 이용한 가지치기 : " 지금까지 만든 경로가 최적해가 아니면, 남은 경로를 만들 필요가 없다"

두개의 인접한 도시를 골라서 이 둘의 순서를 바꿔 본 뒤, 경로가 더 짧아지면 탐색을 중단
(..., p,a,b,q, ..., cur)
(..., p,b,a,q, ..., cur)
*/


// 마지막 네개의 도시중 가운데 두도시의 순서를 바꿨을 떄 경로가 짧아지는지 여부를 반환
bool pathSwappingPruning (double** W, vector<int>& path){
	if(path.size() < 4 )return false;
	int p = path[path.size() - 4];
	int a = path[path.size() - 3];
	int b = path[path.size() - 2];
	int q = path[path.size() - 1];
	
	return W[p][a] + W[a][b] + W[b][q] > W[p][b] + W[b][a] + W[a][q];
}

// 모든 길이의 부분 경로를 뒤집어서 경로가 짧아지는지 여부를 반환
bool pathReversePruning(double**W, vector<int>& path){
	
	if(path.size()<4) return false;
	int q = path[path.size() -1];
	int b = path[path.size() -2];


	for(int i=0; i+3 < path.size(); i++){
		int a = path[i+1];
		int p = path[i];

		if( W[p][a] + W[b][q] > W[p][b] + W[a][q]){
			return true;
		}
	}

	return false;
}

void search5 (double** W, vector<int>& path, vector<bool>& visited, double currentLength, double& best){
	if(pathReversePruning(W,path)) return;

	int cur = path.back();

	if (path.size() == N) {
		best = min(best, currentLength + W[cur][0]);
		return;
	}

	for(int i=0; i< N; i++){		
		if(visited[i]) continue;
		path.push_back(i);
		visited[i] = true;
		search5(W, path, visited, currentLength+ W[cur][i], best);
		path.pop_back();
		visited[i] = false;
	}
}

// 6. MST 휴리스틱을 이용한 가지치기

void search6 (double** W, vector<int>& path, vector<bool>& visited, double currentLength, double& best){
	int cur = path.back();

	if (path.size() == N) {
		best = min(best, currentLength + W[cur][0]);
		return;
	}

	for(int i=0; i< N; i++){		
		if(visited[i]) continue;
		path.push_back(i);
		visited[i] = true;
		search6(W, path, visited, currentLength+ W[cur][i], best);
		path.pop_back();
		visited[i] = false;
	}
}

// 7. 남은 조각의 수가 k이하일 때만 메모이제이션

const int CACHED_DEPTH = 5;

map<int, double> cache[MAX][CACHED_DEPTH +1];

double _search_dp(double** W, int cur, int visited ){

	if (visited == (1<< N)-1) return W[cur][0];
	
	int remaining = N - __builtin_popcount(visited);
	double& ret = cache[cur][remaining][visited];
	if(ret > 0 ) return ret;
	
	ret =INF;

	for(int i=0; i< N; i++){		
		if(visited & (1 << i)) continue;
		ret = min(ret,_search_dp(W, i, visited | (1 << i)) + W[cur][i]);
	}

	return ret;
}

void _search7 (double** W, vector<int>& path, int visited, double currentLength, double& best){
	int cur = path.back();
	if(path.size() + CACHED_DEPTH >= N){
		best = min(best, currentLength + _search_dp(W, cur, visited) );
		return;
	}
	if (path.size() == N) {
		best = min(best, currentLength + W[cur][0]);
		return;
	}

	for(int i=0; i< N; i++){		
		if(visited & (1<<i) ) continue;
		path.push_back(i);
		_search7(W, path, visited | (1 << i) , currentLength+ W[cur][i], best);
		path.pop_back();
	}
}

void search7(double** W, vector<int>& path, vector<bool>& _visited, double currentLength, double& best){
	
	int visited = 1;

	for(int i=0; i< MAX; i++){
		for(int j=0; j< CACHED_DEPTH+1; j++){
			cache[i][j].clear();
		}
	}

	_search7(W,path,visited,0,best);
}

void solve(double** W){
	function_t functions[] = {*serach0, *search1, *search3, *search4, *search5, *search6, *search7};

	for(int i =0; i<7 ;i++){
		double best = INF;
		vector<bool> visited(N, false); 
		vector<int> path(1, 0);
		visited[0] = true;

		(* functions[i])(W, path, visited, 0, best);
		cout << "solve : " <<fixed << setprecision(3) <<best<< endl;
	}
}




int main(void){

	default_random_engine gen(43);
	double** W = initialize(gen);

	solve(W);

	return 0;
}