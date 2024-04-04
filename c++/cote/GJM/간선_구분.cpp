#include <iostream>
#include <vector>
#include <random>
#define N 10
#define TEST_CASES 10

using namespace std;

vector<vector<int>> initialize(default_random_engine& gen) {
	int n = gen() % (N - 3) + 3;
	vector<vector<int>> ret(n, vector<int>());

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n ; j++) {
			if (i == j && gen() % 1000 < 9990) {
				continue;
			}
			ret[i].push_back(j);
		}
	}

	return ret;
}

void dfs(int cur, const vector<vector<int>>& adj, vector<int>& discovered, vector<bool>& finished, int& counter) {
	discovered[cur] = counter++;

	for (const auto& next : adj[cur]) {
		cout << "(" << cur << "," << next << ") : ";
		if (discovered[next] == -1){
			cout << "tree edge" << endl;
			dfs(next, adj, discovered, finished, counter);
		} else if (discovered[cur] < discovered[next]) {
			cout << "forward edge" << endl;
		} else if (!finished[next]) {
			cout << "back edge" << endl;
 		} else {
 			cout << "cross edge" << endl;
 		}
	}
	finished[cur] = true;
}

void solve(vector<vector<int>>& adj) {
	vector<int> discovered(adj.size(), -1);
	vector<bool> finished(adj.size(), false);

	int counter = 0;

	for (int i = 0; i < adj.size(); i++) {
		if (discovered[i] == -1) {
			dfs(i, adj, discovered, finished, counter);
		}
	}
}

int main(void){
	default_random_engine gen(43);

	for (int it = 0; it < TEST_CASES; it++){
		vector<vector<int>> adj = initialize(gen);
		solve(adj);
	}

	return 0;
}