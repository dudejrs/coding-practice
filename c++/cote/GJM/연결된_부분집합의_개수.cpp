#include <iostream>
#include <random>
#define N 1000
#define TEST_CASES 10

using namespace std;

void dfs(int cur, vector<vector<int>>& graph, bool* visited){
	visited[cur] = true;

	for (int i : graph[cur]) {
		if (! visited[i]) {
			dfs(i, graph, visited);
		}
	}
}

int solve(vector<vector<int>>& graph) {
	int count = 0;
	bool visited [graph.size()];
	memset(visited, false, sizeof(visited));

	for (int i = 0; i < graph.size(); i++) {
		if (visited[i]) continue;
		dfs(i, graph, visited);
		count++;
	}

	return count;
}

int main(void) {
	default_random_engine gen(43);

	for (int it = 0; it < TEST_CASES; it++) {
		uint n = gen() % (N - 3) + 3;
		
		vector<vector<int>> graph {n, vector<int>()};

		for (int i = 0; i < n; i++) {
			for(int j = i + 1; j < n; j++) {
				if (gen() % 127 > 0)  continue;
				graph[i].push_back(j);
				graph[j].push_back(i);
			}
		}

		cout << n << " " <<solve(graph) << endl;
	}

	return 0;
}