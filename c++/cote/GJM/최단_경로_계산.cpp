#include <iostream>
#include <random>
#include <vector>
#include <queue>
#include <functional>
#define N 1000
#define TEST_CASE 10

using namespace std;

vector<vector<int>> initialize(int n, function<bool()> generator) {
	vector<vector<int>> ret(n, vector<int>{});

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i ; j++) {
			if (generator()) {
				continue;
			}
			ret[i].push_back(j);
			ret[j].push_back(i);
		}
	}

	return ret;
}

vector<int> bfs(int start, vector<vector<int>>& adj) {
	vector<int> parent(adj.size(), -1);
	vector<int> distance(adj.size(), -1);

	queue<int> q;
	distance[start] = 0;
	parent[start] = start;
	q.push(start);

	while (!q.empty()) {
		int cur = q.front();
		q.pop();

		for (const auto& next : adj[cur]) {
			if (distance[next] == -1) {
				q.push(next);
				distance[next] = distance[cur] + 1;
				parent[next] = cur;
			}
		}
	}

	return parent;
}

vector<int> shortest_path(int target, const vector<int>& parent) {
	vector<int> path(1, target);

	while(parent[target] != target) {
		if (parent[target] == -1) {
			return {};
		}

		target = parent[target];
		path.push_back(target);
	}

	reverse(begin(path), end(path));
	return path;
}

vector<int> solve(int start, int target, vector<vector<int>>& adj) {
	vector<int> parent = bfs(start, adj);

	return shortest_path(target, parent);
}

int main(void) {
	default_random_engine gen(43);
	auto generator {bind(bernoulli_distribution {0.9775}, gen)};

	for (int it = 0; it < TEST_CASE; it++) {
		int n = gen() % (N - 3) + 3;
		vector<vector<int>> adj = initialize(n, generator);
		int k = gen() % (n - 1) + 1;
		vector<int> path = solve(0, k, adj);

		for (auto& cur : path) {
			cout << cur << " ";
		}
		cout << endl;
	}

	return 0;
}