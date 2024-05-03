#include <iostream>
#include <vector>
#include <queue>
#include <random>
#include <functional>
#define MAX_CAPACITY 100
#define V 100
#define TEST_CASES 10

using namespace std;

struct Edge {
	int target, capacity, flow;
	Edge* reverse;

	int getResidualCapcity() {
		return capacity - flow;
	}

	void push(int amount) {
		flow += amount;
		reverse->flow -= amount;
	}
};

pair<vector<vector<int>>, vector<vector<int>>> initialize(int v, function<bool()> is_connected, function<float()> cap) {
	vector<vector<int>> capacity (v, vector<int>(v, 0)), flow (v, vector<int>(v, 0));	

	for (int i = 0; i < v; i++) {
		for (int j = 0; j < v; j++) {
			if (i == j && !is_connected()) {
				continue;
			}
			capacity[i][j] = static_cast<int>(cap());
		}
	}

	return {capacity, flow};
}

vector<vector<Edge*>> adjacent(vector<vector<int>>& capacity, vector<vector<int>>& flow) {
	int n = capacity.size();
	vector<vector<Edge*>> ret(n);

	for (int u = 0; u < n; u++) {
		for (int v =  u + 1; v < n; v++) {
			if (capacity[u][v] > 0 || capacity[v][u] > 0) {
				Edge* uv = new Edge();
				Edge* vu = new Edge();

				uv->target = v;
				uv->capacity = capacity[u][v];
				uv->flow = flow[u][v];
				uv->reverse = vu;

				vu->target = u;
				vu->capacity = capacity[v][u];
				vu->flow = flow[u][v];
				vu->reverse = uv;

				ret[u].push_back(uv);
				ret[v].push_back(vu);
			}
		}
	}

	return ret;
}

// 0번노드가 source고, v-1번 노드가 sink일떄의 최대 유량
int solve(vector<vector<int>>& capacity, vector<vector<int>>& flow) {
	vector<vector<Edge*>> adj {adjacent(capacity, flow)};
	int v = capacity.size();
	int total_flow = 0;

	while (true) {
		vector<int> parent(v, -1);
		vector<Edge*> selected(v, nullptr);

		queue<int> q;
		q.push(0);
		parent[0] = 0;

		while (!q.empty()) {
			int cur = q.front();
			q.pop();

			if (cur == v - 1) {
				break;
			}

			for (auto* edge : adj[cur]) {
				int next = edge->target;
				if (edge->getResidualCapcity() > 0 && parent[next] == -1) {
					q.push(next);
					parent[next] = cur;
					selected[cur] = edge;
				}
			}
		}

		if (parent[v - 1] == -1) {
			break;
		}

		int amount = numeric_limits<int>::max();

		for (int p = v - 1; p != 0; p = parent[p]) {
			amount = min(amount, selected[parent[p]]->getResidualCapcity());
		}

		for (int p = v -1; p != 0; p = parent[p]) {
			selected[parent[p]]->push(amount);
		}

		total_flow += amount;
	}


	return total_flow;
}

int main(void) {
	default_random_engine gen(43);
	auto is_connected {bind(bernoulli_distribution {0.05}, gen)};
	auto cap {bind(normal_distribution<float>{MAX_CAPACITY / 2, MAX_CAPACITY / 5}, gen)};

	for (int i = 0; i < TEST_CASES; i++) {
		int v = gen() % (V - 3) + 3;
		auto [capacity, flow] = initialize(v, is_connected, cap);

		cout << solve(capacity, flow) << endl;

	}

	return 0;
}