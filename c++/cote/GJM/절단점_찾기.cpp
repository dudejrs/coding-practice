#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#define N 1000
#define TEST_CASES 10

using namespace std;

void _dfs(int cur, vector<vector<int>>& adj, vector<bool>& visited) {
  visited[cur] = true;

  for (const auto& next : adj[cur]) {
    if (!visited[next]) {
      _dfs(next, adj, visited);
    }
  }
}

bool check_reachable(vector<vector<int>>& adj) {
  vector<bool> visited(adj.size(), false);
  _dfs(0, adj, visited);
  return all_of(cbegin(visited), cend(visited), [](bool x) { return x; });
}

vector<vector<int>> initialize(default_random_engine& gen) {
  vector<vector<int>> ret;
  int n = gen() % (N - 3) + 3;

  while (true) {
    ret = vector(n, vector<int>());

    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        if (gen() % 100 < 97) {
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

// 자신의 서브트리에서 갈수 있는 가장 높은(0에 가까운) 정점의 번호
int findCutVertex(int cur, bool is_root, vector<vector<int>>& adj,
                  vector<int>& discovered, vector<bool>& is_cut_vertex,
                  int& counter) {
  discovered[cur] = counter++;

  int ret = discovered[cur];

  int children = 0;

  for (int next : adj[cur]) {
    if (discovered[next] == -1) {
      children++;

      // 자식 서브 트리에서 갈 수 있는 가장 높은(0에 가까운) 정점
      int subtree =
          findCutVertex(next, false, adj, discovered, is_cut_vertex, counter);

      // 그 것이 자신보다 낮은 위치일떄 현재 노드는 절단점이 된다.
      if (!is_root && subtree >= discovered[cur]) {
        is_cut_vertex[cur] = true;
      }

      ret = min(ret, subtree);

    } else {
      ret = min(ret, discovered[next]);
    }
  }

  if (is_root) {
    if (children > 1) {
      is_cut_vertex[cur] = true;
    }
  }

  return ret;
}

vector<int> solve(vector<vector<int>>& adj) {
  vector<int> discovered(adj.size(), -1);
  vector<bool> is_cut_vertex(adj.size(), -1);
  int counter = 0;

  findCutVertex(0, true, adj, discovered, is_cut_vertex, counter);

  vector<int> ret;

  for (int i = 0; i < adj.size(); i++) {
    if (is_cut_vertex[i]) {
      ret.push_back(i);
    }
  }

  return ret;
}

int main(void) {
  default_random_engine gen(43);

  for (int i = 0; i < TEST_CASES; i++) {
    vector<vector<int>> adj = initialize(gen);
    vector<int> cutVertices = solve(adj);

    for (const auto& vertex : cutVertices) {
      cout << vertex << " ";
    }
    cout << endl;
  }

  return 0;
}