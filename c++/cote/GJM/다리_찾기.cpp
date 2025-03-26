#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#define N 1000
#define TEST_CASES 10

using namespace std;

void _dfs(int cur, vector<bool>& visited, vector<vector<int>>& graph) {
  visited[cur] = true;

  for (const auto& next : graph[cur]) {
    if (!visited[next]) {
      _dfs(next, visited, graph);
    }
  }
}

bool check_reachable(vector<vector<int>>& graph) {
  vector<bool> visited(graph.size(), false);
  _dfs(0, visited, graph);

  return all_of(begin(visited), end(visited), [](bool v) { return v; });
}

vector<vector<int>> initialize(default_random_engine& gen) {
  vector<vector<int>> ret;

  while (true) {
    int n = gen() % (N - 3) + 3;
    ret = vector(n, vector<int>{});

    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        if (gen() % 1000 < 975) {
          continue;
        }
        ret[i].push_back(j);
        ret[j].push_back(i);
      }
    }

    if (check_reachable(ret)) {
      break;
    }
  }

  return ret;
}

int finCutEdges(int cur, int parent, vector<vector<int>>& adj,
                vector<int>& discovered, int& counter,
                vector<pair<int, int>>& bridges) {
  discovered[cur] = counter++;
  int ret = discovered[cur];

  for (int next : adj[cur]) {
    if (discovered[next] == -1) {
      int subtree = finCutEdges(next, cur, adj, discovered, counter, bridges);

      if (subtree > discovered[cur]) {
        bridges.push_back(pair{cur, next});
      }

      ret = min(ret, subtree);

    } else if (next != parent) {
      ret = min(ret, discovered[next]);
    }
  }

  return ret;
}

vector<pair<int, int>> solve(vector<vector<int>>& adj) {
  vector<int> discovered(adj.size(), -1);
  vector<pair<int, int>> bridges;
  int counter = 0;

  finCutEdges(0, -1, adj, discovered, counter, bridges);

  return bridges;
}

int main(void) {
  default_random_engine gen(43);

  for (int it = 0; it < TEST_CASES; it++) {
    vector<vector<int>> adj = initialize(gen);

    vector<pair<int, int>> bridges = solve(adj);
    for (auto [u, v] : bridges) {
      cout << "(" << u << ", " << v << ") ";
    }
    cout << endl;
  }

  return 0;
}