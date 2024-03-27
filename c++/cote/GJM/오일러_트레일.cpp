#include <iostream>
#include <random>
#include <algorithm>
#define TEST_CASES 10
#define N 5
#define MAX_EDGES 3

using namespace std;

void _check_dfs(int cur, const vector<vector<int>>& graph, vector<bool>& visited) {
	visited[cur] = true;

	for (int i = 0; i < graph.size(); i++) {
		if (!visited[i] && graph[cur][i] > 0) {
			_check_dfs(i, graph, visited);
		}
	}
}

bool check_euler(const vector<vector<int>>& graph) {
	vector<int> ranks (graph.size(), 0);

	for (int i = 0; i < graph.size(); i++) {
		for (int j = 0; j < graph.size(); j++) {
			ranks[i] += graph[i][j];
		}
	}

	int odds = count_if(begin(ranks), end(ranks), [](int a){return a % 2 == 1;});

	return  odds == 2;
}

bool check_reachable(const vector<vector<int>>& graph) {
	uint n = graph.size();
	vector<bool> visited (n, false);	

	_check_dfs(0, graph, visited);

	return all_of(begin(visited), end(visited), [](bool b){return b;});
}


vector<vector<int>> initialize(default_random_engine& gen) {
	vector<vector<int>> ret;

	while (true) {
		uint n = gen() % (N - 2) + 2;
		ret = vector<vector<int>> (n, vector<int>(n));

		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				if (gen() % 20 > 18) continue;
				ret[i][j] = ret[j][i] = gen() % (MAX_EDGES - 1) + 1;
			}
		}

		if (check_euler(ret) && check_reachable(ret)) {
			break;
		}
	}

	return ret;
}

pair<int,int> find(const vector<vector<int>>& graph) {
	vector<int> ranks (graph.size(), 0);

	for (int i = 0; i < graph.size(); i++) {
		for (int j = 0; j < graph.size(); j++) {
			ranks[i] += graph[i][j];
		}
	}

	int first = -1, second = -1;

	for (int i = 0; i < graph.size(); i++) {
		if (ranks[i] % 2 == 1) {
			if (first == -1) {
				first = i;
			} else {
				second = i;
			}
		}
	}

	return {first, second};
}

void dfs(int cur, vector<vector<int>>& graph, vector<int>& ret) {

	for (int i = 0; i < graph.size(); i++) {
		while (graph[cur][i] > 0) {
			graph[cur][i]--;
			graph[i][cur]--;
			dfs(i, graph, ret);
		}
	}
	ret.push_back(cur);
}

vector<int> solve(vector<vector<int>>& adj, int start, int dest) {
	vector<vector<int>> graph {adj};
	vector<int> ret {};

	graph[start][dest] = graph[dest][start] += 1;
	
	dfs(start, graph, ret);	
	reverse(begin(ret), end(ret));
	ret.pop_back();

	return ret;
}


int main(void) {
	default_random_engine gen(43);

	for (int it = 0; it < TEST_CASES; it++) {
		vector<vector<int>> adj = initialize(gen);
		auto [start, dest] = find(adj);
		vector<int> trail = solve(adj, start, dest);
		
		for (auto cur : trail) {
			cout << cur << " ";
		}
		cout << endl;
			
	}

	return 0;
}