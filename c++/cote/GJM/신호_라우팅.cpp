#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <functional>
#include <algorithm>
#include <iomanip>
#include <random>
#define N 1000
#define M 10 * N
#define MIN_C 1.0
#define MAX_C 3.0
#define TEST_CASES 10

using namespace std;

using Graph = vector<vector<pair<int, double>>>;

void _dfs(int cur, Graph& ret, vector<bool>& visited) {
	visited[cur] = true;

	for (auto& [next, weight] : ret[cur]) {
		if (!visited[next]) {
			_dfs(next, ret, visited);
		}
	}
}

bool check_reachable(Graph& ret) {
	vector<bool> visited(ret.size(), false);

	_dfs(0, ret, visited);
	
	return all_of(begin(visited), end(visited), [](bool i){return i;});
}

Graph initialize(int n, function<bool()> is_connected, function<double()> cost_generator){
	Graph ret;
	
	while (true) {
		ret = vector<vector<pair<int, double>>>(n); 
		int count = 0;

		for (int i = 0; i < n; i++) {			
			for (int j = 0; j < n; j++) {
				if (i == j || !is_connected()) {
					continue;
				}
				double weight = cost_generator();
				ret[i].push_back(pair{j, weight});
				count++;
			}
		}
		if (count < M && check_reachable(ret)) {
			break;
		}
	}

	return ret;
}

double solve(int start, int target, Graph& adj) {
	vector<double> dist(adj.size(), numeric_limits<double>::max());

	priority_queue<pair<double, int>, vector<pair<double, int>>, less<>> q;
	dist[start] = 1.0;
	q.push(pair{1.0, start});

	while (!q.empty()) {
		auto [cost, cur] = q.top();
		q.pop();
		
		if (dist[cur] < cost) {
			continue;
		}

		for (auto [next, weight] : adj[cur]) {
			double nextDistance = cost * weight;

			if (nextDistance < dist[next]) {
				dist[next] = nextDistance;
				q.push(pair{nextDistance, next});
			}
		}
	}

	return dist[target];
}

int main(void) {
	default_random_engine gen(43);
	auto cost_generator {bind(normal_distribution<float> {(MIN_C + MAX_C) / 2.0, (MAX_C - MIN_C) * 0.1}, gen)};

	for (int it = 0; it < TEST_CASES; it++) {
		int n = gen() % (N - 3) + 3;
		int k = gen() % (n - 1) + 1;
		auto is_connected {bind(bernoulli_distribution{static_cast<double>((1.0 * M) / (n * (n + 1)))}, gen)};
		Graph adj = initialize(n, is_connected, cost_generator);
		cout <<fixed << setprecision(7)<< solve(0, k, adj) << endl;
	}
}