#include <iostream>
#include <random>
#include <vector>
#include <initializer_list>
#define N 1000
#define TEST_CASES 10

using namespace std;

vector<vector<int>> initialize(default_random_engine& gen) {
	
	uint n = gen() % (N - 3) + 3;
	vector<vector<int>> ret {n, vector<int>{}};

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++){
			if (gen() % 127 == 0 ) {
				ret[i].push_back(j);
			} 
		}
	}

	return ret;
}

void dfs(int cur, vector<vector<int>>& graph, bool* visited) {
	visited[cur] = true;

	for (int i : graph[cur]) {

		if (!visited[i]){
			dfs(i, graph, visited);
		}
	}

	return;
}

bool solve(vector<vector<int>>& graph, int a, int b) {

	bool visited [graph.size()];

	dfs(a, graph, visited);

	return visited[b] == true;
}

int main(void) {
	default_random_engine gen(43);

	for (int i = 0; i < TEST_CASES; i++) {
		vector<vector<int>> graph = initialize(gen);
		int a = gen() % (graph.size() - 1) + 1;
		int b = gen() % a;

		cout << boolalpha << solve(graph, a, b) << endl;
	}
	
	return 0;
}