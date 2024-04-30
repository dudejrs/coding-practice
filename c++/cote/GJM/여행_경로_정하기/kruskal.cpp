#include <iostream>
#include <random>
#include <set>
#include <vector>
#include <functional>
#include <algorithm>
#include <limits>
#define V 2000
#define E 4000
#define MAX_SPEED 1000
#define TEST_CASES 10

using namespace std;

struct DisjointSet {

	DisjointSet(int n): parent(n, -1), rank(n, 0), size(n) {
		for (int i = 0; i < n; i++) {
			parent[i] = i;
		}
	}

	int find(int x) {
		if (parent[x] == x) {
			return x;
		}
		return parent[x] = find(parent[x]);
	}

	void merge(int x, int y) {
		x = find(x);
		y = find(y);

		if (x == y) {
			return;
		}

		if (rank[y] < rank[x]) {
			swap(x, y);
		}
		parent[x] = y;
		
		if (rank[x] == rank[y]) {
			rank[y]++;
		}

		return;
	}

	private :
		vector<int> parent;
		vector<int> rank;
		int size;
};

vector<vector<int>> _adjacent(int n, vector<array<int, 3>>& edges) {
	vector<vector<int>> ret(n);

	for (auto [a, b, speed] : edges) {
		ret[a].push_back(b);
		ret[b].push_back(a);
	}

	return ret;
}

void _dfs(int cur, vector<bool>& visited, vector<vector<int>>& adj) {
	visited[cur] = true;

	for (auto next : adj[cur]) {
		if (!visited[next]) {
			_dfs(next, visited, adj);
		}
	}

	return;
}

bool check_reachable(int n, vector<array<int, 3>>& edges) {
	vector<vector<int>> adj {_adjacent(n, edges)};
	vector<bool> visited(n, false);

	_dfs(0, visited, adj);

	return visited[n - 1];
}

vector<array<int, 3>> initialize(int n, default_random_engine& gen, function<float()> speed){
	vector<array<int, 3>> ret;
	
	while(true) {
		set<pair<int, int>> s;
		int e = gen() % (E - 3) + 3;
		e = min(e, n * (n - 1) / 2);

		while (true) {
			if(s.size() == e) {
				break;
			}
			int a = gen() % (n - 1) + 1;
			int b = gen() % a;

			auto it {s.find({a, b})};
			if (it == end(s)){
				ret.push_back({a, b, static_cast<int>(speed())});
				s.insert({a, b});
			}
		}

		if (check_reachable(n, ret)) {
			break;
		}
		ret.clear();
		s.clear();
	}
	return ret;
}

vector<int> weight(const vector<array<int, 3>>& edges) {
	vector<int> ret;

	for (auto [a, b, cost] : edges) {
		ret.push_back(cost);
	}

	return ret;
}

int minUpperBound(int lowWeight, int n, vector<array<int, 3>>& edges) {
	DisjointSet s(n);

	for (auto [a, b, cost] : edges) {
		if (cost < lowWeight) {
			continue;
		}

		s.merge(a, b);

		if (s.find(0) == s.find(n - 1)) {
			return cost;
		}
	}

	return numeric_limits<int>::max();
}


// 0번에서 n-1번까지의 최소너비 경로의 너비 
int solve(int n, vector<array<int, 3>>& edges) {
	vector<int> weights {weight(edges)};
	
	sort(begin(weights), end(weights));
	sort(begin(edges), end(edges), [](auto e1, auto e2){
		if (e1[2] != e2[2]) {
			return e1[2] < e2[2];
		}
		if (e1[0] != e2[0]){
			return e1[0] < e2[0];
		}

		return e1[1] < e2[1];
	});

	int ret = numeric_limits<int>::max();
	for (auto weight : weights) {
		ret = min(ret, minUpperBound(weight, n, edges) - weight);
	}

	return ret;
}

int main(void) {
	default_random_engine gen {43};
	auto speed {bind(normal_distribution<float>(MAX_SPEED / 2, MAX_SPEED / 4), gen)};

	for (int it = 0; it < TEST_CASES; it++) {
		int n = gen() % (V - 3) + 3;
		vector<array<int, 3>> edges = initialize(n, gen, speed);
		cout << solve(n, edges) << endl;
	}

	return 0;
}