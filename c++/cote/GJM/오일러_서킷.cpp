#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#define N 10
#define TEST_CASES 10
#define MAX_EDGES 2

using namespace std;

vector<vector<int>> initialize(default_random_engine& gen) {
  uint n = gen() % (N - 2) + 2;
  vector<vector<int>> ret{n, vector<int>(n)};

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (gen() % 20 > 18) continue;
      ret[i][j] = ret[j][i] = gen() % MAX_EDGES;
    }
  }

  return ret;
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

bool check(const vector<vector<int>>& adj) {
  for (int i = 0; i < adj.size(); i++) {
    int sum = 0;
    for (int j = 0; j < adj.size(); j++) {
      sum += adj[i][j];
    }
    if (sum % 2 == 1) {
      return false;
    }
  }

  return true;
}

vector<int> solve(const vector<vector<int>>& adj) {
  if (!check(adj)) return {-1};

  vector<vector<int>> graph{adj};

  vector<int> ret{};

  dfs(0, graph, ret);

  return ret;
}

int main(void) {
  default_random_engine gen(43);
  for (int it = 0; it < TEST_CASES; it++) {
    vector<vector<int>> adj = initialize(gen);
    vector<int> circuit = solve(adj);
    for (auto cur : circuit) {
      cout << cur << " ";
    }
    cout << endl;
  }

  return 0;
}