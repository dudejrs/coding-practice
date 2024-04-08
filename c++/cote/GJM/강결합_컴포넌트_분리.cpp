#include <iostream>
#include <vector>
#include <random>
#include <functional>
#include <algorithm>
#include <stack>
#define TEST_CASES 10
#define N 1000

using namespace std;


void _dfs(int cur, vector<bool>& visited, vector<vector<int>>& graph) {
	visited[cur] = true;

	for (auto& next : graph[cur]) {
		if (!visited[next]){
			_dfs(next, visited, graph);
		}
	}
}

bool check_reachable(vector<vector<int>>& graph) {
	vector<bool> visited(graph.size(), false);

	_dfs(0, visited, graph);

	return all_of(begin(visited), end(visited), [](bool v){return v;});
}

vector<vector<int>> initialize(int n, function<bool()> edge_gen) {
	vector<vector<int>> ret;

	while(true) {

		ret = vector(n, vector<int>());

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i == j || !edge_gen()) {
					continue;
				}

				ret[i].push_back(j);
			}
		}

		if (check_reachable(ret)) {
			break;
		}
	}

	return ret;
}

int dfs(int cur, vector<vector<int>>& graph, vector<bool>& finished, vector<int>& discovered, vector<int>& sccIds, stack<int>& st, int& vertexCounter, int& sccCounter) {
	
	discovered[cur] = vertexCounter++;
	int ret = discovered[cur];
	
	st.push(cur);

	for (const auto& next : graph[cur]) {
		if (discovered[next] == -1) {
			int subtree = dfs(next, graph, finished, discovered, sccIds, st, vertexCounter, sccCounter);
			ret = min(ret, subtree);
		} else if (discovered[next] < discovered[cur] && !finished[next] ) {
			ret = min(ret, discovered[next]);
		} 
	}

	if (ret == discovered[cur]) {
		while (true) {
			int t = st.top();
			st.pop();
			sccIds[t] = sccCounter;
			if  (t == cur) break;
		}	
		sccCounter++;
	}

	finished[cur] = true;

	return ret;
}

vector<int> solve(vector<vector<int>>& graph) {
	vector<int> sccIds = vector<int>(graph.size(), -1);
	vector<bool> finished(graph.size(), false);
	vector<int> discovered(graph.size(), -1);
	stack<int> st;

	int vertexCounter = 0;
	int sccCounter = 0; 

	dfs(0, graph, finished, discovered, sccIds, st, vertexCounter, sccCounter);

	return sccIds;
}

int main(void) {
	default_random_engine gen(43);
	auto n_gen {bind(uniform_int_distribution{3, N}, gen)};
	auto edge_gen {bind(bernoulli_distribution{0.05}, gen)};

	for (int it = 0; it < TEST_CASES; it++) {
		int n = n_gen(gen);
		vector<vector<int>> adj = initialize(n, edge_gen);		

		vector<int> sccIds = solve(adj);
		for (const auto& sccId : sccIds) {
			cout << sccId << " ";
		}
		cout << endl << endl;
	}

	return 0;
}