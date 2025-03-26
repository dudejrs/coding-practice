#include <iostream>
#include <memory>
#include <random>
#include <vector>
#define MIN_PER_RANK 1
#define MAX_PER_RANK 10
#define MIN_RANKS 3
#define MAX_RANKS 10
#define TEST_CASES 10
#define MAX_NODE 100
#define PERCENT 30

using namespace std;

vector<vector<int>> initialize(default_random_engine& gen) {
  vector<vector<int>> ret{};

  int ranks = gen() % (MAX_RANKS - MIN_RANKS) + MIN_RANKS;
  int nodes = 0;

  for (int k = 0; k < ranks; k++) {
    int new_nodes = gen() % (MAX_PER_RANK - MIN_PER_RANK) + MIN_PER_RANK;

    if (nodes + new_nodes >= MAX_NODE) {
      break;
    }

    for (int i = 0; i < nodes; i++) {
      for (int j = nodes; j < nodes + new_nodes; j++) {
        if (gen() % 100 <= PERCENT) {
          ret[i].push_back(j);
        }
      }
    }

    for (int i = 0; i < new_nodes; i++) {
      ret.push_back(vector<int>{});
    }
    nodes += new_nodes;
  }

  return ret;
}

void dfs(int cur, vector<vector<int>>& graph, bool* visited,
         vector<int>& path) {
  visited[cur] = true;

  for (int i : graph[cur]) {
    if (!visited[i]) {
      dfs(i, graph, visited, path);
    }
  }

  path.push_back(cur);
}

vector<int> solve(vector<vector<int>>& graph) {
  vector<int> path{};
  bool* visited = new bool[graph.size()];

  for (int i = 0; i < graph.size(); i++) {
    if (!visited[i]) {
      dfs(i, graph, visited, path);
    }
  }

  delete[] visited;

  return path;
}

int main(void) {
  default_random_engine gen{43};

  for (int it = 0; it < TEST_CASES; it++) {
    vector<vector<int>> graph = initialize(gen);
    vector<int> path = solve(graph);

    for (int v : path) {
      cout << v << " ";
    }
    cout << endl;
  }

  return 0;
}