#include <iostream>
#include <random>
#include <random>
#define TEST_CASES 10
#define N 1000

using namespace std;

vector<vector<bool>> initialize(default_random_engine& gen) {
	int n = gen() % (N - 3) + 3;
	vector<vector<bool>> ret (n, vector<bool>(n, false));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j || gen() % 10000 < 9990 ) {
				continue;
			}
			ret[i][j] = true;
		}
	}

	return ret;
}

// 역방향 간선이 있으면 사이클이 존재하는 지 확인하기 위해, 깊이 탐색 path에 자신의 outgoing 간선이 있는지 확인한다.  
bool dfs(int cur, vector<vector<bool>>& graph, vector<bool>& visited, vector<int> path) {
	visited[cur] = true;
	path.push_back(cur);

	for (int next = 0; next < graph.size(); next++){
		if (graph[cur][next]) {
			if (!visited[next]) {
				if(!dfs(next, graph, visited, path)) {
					return false;
				}
			}	

			if(auto it = find(begin(path), end(path), next); it != end(path)) {
				return false;
			}
		} 
	}
	return true;
}

bool solve(vector<vector<bool>>& graph) {
	vector<bool> visited(graph.size(), false);

	for (int i = 0; i < graph.size(); i++) {
		if (!visited[i]){
			if (!dfs(i, graph, visited, vector<int>{i})) {
				return false;
			}
		}
	}

	return true;
}

int main(void) {	
	default_random_engine gen(43);
	
	for (int it = 0; it < TEST_CASES; it++) {
		vector<vector<bool>> graph = initialize(gen);

		cout << boolalpha << solve(graph) << endl;
	}

	return 0;
}