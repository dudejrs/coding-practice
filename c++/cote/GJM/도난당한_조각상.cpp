#include <iostream>
#include <iomanip>
#include <random>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
#include <limits>
#define N 100
#define TEST_CASES 10
#define MAX_DETECTIVES 100

using namespace std;

int source(int n) {
	return 0;
}

int destination(int n) {
	return n - 1;
}

bool _dfs(int cur, int dst, const vector<vector<int>>& adj, vector<bool>& visited) {
	
	if (cur == dst) {
		return true;
	}
	visited[cur] = true;	

	for (auto next : adj[cur]) {
		if (!visited[next] && _dfs(next, dst, adj, visited)) {
			return true;
		}
	}

	return false;
}

bool reachable(int src, int dst, const vector<vector<int>>& adj) {
	vector<bool> visited (adj.size(), false);

	return _dfs(src, dst, adj, visited);
}

vector<vector<int>> initialize(int n, function<bool()> is_connected) {
	vector<vector<int>> ret;

	while (true) {
		ret = vector<vector<int>>(n);

		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				if (!is_connected() || (i == source(n) && j == destination(n))) {
					continue;
				}

				ret[i].push_back(j);
				ret[j].push_back(i);
			}
		}

		if (reachable(source(n), destination(n), ret)) {
			break;
		}
	}

	return ret;
}

int innode(int k, int n) {
	if (k == source(n)) {
		return 0;
	} 
	if (k == destination(n)) {
		return 2 * n - 3;
	}

	return 2 * k -1;
}

int outnode(int k, int n) {
	if (k == source(n)) {
		return 0;
	} 
	if (k == destination(n)) {
		return 2 * n - 3;
	}

	return 2 * k;
}


vector<vector<int>> split_node(vector<vector<int>>& adj, vector<int>& detectives){
	int n = adj.size();
	vector<vector<int>> capacity(2 * n - 2, vector<int>( 2 * n - 2, 0));

	for (int i = 0; i < n; i++) {
		for (int j : adj[i]) {
			capacity[outnode(i, n)][innode(j, n)] = numeric_limits<int>::max();
			capacity[outnode(j, n)][innode(i, n)] = numeric_limits<int>::max();
		}
	}

	for (int i = 0; i < n; i++) {
		if (i == source(n) || i == destination(n)) {
			continue;
		}

		capacity[innode(i, n)][outnode(i, n)] = detectives[i];
	}

	return capacity;
}
int solve(vector<int>& detectives, vector<vector<int>>& adj) {
	vector<vector<int>> capacity {split_node(adj, detectives)};
	int n = capacity.size();
	vector<vector<int>> deployed (n, vector<int>(n, 0));

	int total_deployed = 0;

	while (true) {
		vector<int> parent(n, -1);
		queue<int> q;

		q.push(source(n));
		parent[source(n)] = source(n);

		while(!q.empty()) {
			int cur = q.front();
			q.pop();

			if (cur == n - 1) {
				break;
			}

			for (int next = 0; next < n; next++) {
				if (capacity[cur][next] - deployed[cur][next] > 0 && parent[next] == -1) {
					parent[next] = cur;
					q.push(next);
				}
			}
		}

		if (parent[destination(n)] == -1) {
			break;
		}

		int number = numeric_limits<int>::max();

		for (int p = destination(n); p != source(n); p = parent[p]) {
			number = min(number, capacity[parent[p]][p] - deployed[parent[p]][p]);
		}

		for (int p = destination(n); p != source(n); p = parent[p]) {
			deployed[parent[p]][p] += number;
			deployed[p][parent[p]] -= number;
		}

		total_deployed += number;
	}

	return total_deployed;
}

int main(void) {
	default_random_engine gen(17);
	auto detective {bind(uniform_int_distribution (1, MAX_DETECTIVES), gen)};
	auto is_connected {bind(bernoulli_distribution (0.25), gen)};
	
	for (int it = 0; it < TEST_CASES; it++) {
		int n = gen() % (N - 3) + 3;
		vector<int> detectives(n);
		generate(begin(detectives) + 1, end(detectives) - 1, detective);
		vector<vector<int>> adj = initialize(n, is_connected);

		cout << solve(detectives, adj) << endl;

		// for (int i = 0; i < n; i++) {
		// 	for (auto j : adj[i]) {
		// 		cout << "(" << i << "," << j << ") ";
		// 	}	
		// 	cout << endl;
		// }

		// for (auto d : detectives) {
		// 	cout << d << " ";
		// }
		// cout << endl;
	}
	
	return 0;
}