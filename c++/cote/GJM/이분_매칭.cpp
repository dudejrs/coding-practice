#include <iostream>
#include <random>
#include <functional>
#include <vector>
#define TEST_CASES 10
#define N 100
#define M 100

using namespace std;

vector<vector<int>> initialize(int n, int m, function<bool()> is_connected) {
	vector<vector<int>> ret(n);

	for (int i = 0; i < n; i ++) {
		for (int j = 0; j < m; j++) {
			if (is_connected()) {
				ret[i].push_back(j);
			}
		}
	}

	return ret;
}

bool dfs(int a, vector<int>& a_match, vector<int>& b_match, vector<bool>& visited, vector<vector<int>>& adj) {
	if (visited[a]) {
		return false;
	}

	visited[a] = true;

	for (auto b : adj[a]) {
		if (b_match[b] == -1 || dfs(b_match[b], a_match, b_match, visited, adj)) {
			a_match[a] = b;
			b_match[b] = a;
			return true;
		}
	}

	return false;
}

int solve(int n, int m, vector<vector<int>>& adj) {
	vector<int> a_match (n, -1);
	vector<int> b_match (n, -1);
	int count = 0;

	for (int i = 0; i < n; i++) {
		vector<bool> visited (n, false);

		if (dfs(i, a_match, b_match, visited, adj)) {
			count++;
		}
	}
	
	return count++;
}

int main(void) {
	default_random_engine gen{43};
	auto is_connected {bind(bernoulli_distribution{0.05}, gen)};

	for (int it = 0; it < TEST_CASES; it++) {
		int n = gen() % (N - 3) + 3;
		int m = gen() % (M - 3) + 3;
		vector<vector<int>> adj {initialize(n, m, is_connected)};

		cout << solve(n, m, adj) << endl;
	}

	return 0;	
}