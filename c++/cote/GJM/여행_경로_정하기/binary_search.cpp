#include <algorithm>
#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <random>
#include <set>
#include <vector>
#define V 2000
#define E 4000
#define MAX_SPEED 1000
#define TEST_CASES 10

using namespace std;

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
  vector<vector<int>> adj{_adjacent(n, edges)};
  vector<bool> visited(n, false);

  _dfs(0, visited, adj);

  return visited[n - 1];
}

vector<array<int, 3>> initialize(int n, default_random_engine& gen,
                                 function<float()> speed) {
  vector<array<int, 3>> ret;

  while (true) {
    set<pair<int, int>> s;
    int e = gen() % (E - 3) + 3;
    e = min(e, n * (n - 1) / 2);

    while (true) {
      if (s.size() == e) {
        break;
      }
      int a = gen() % (n - 1) + 1;
      int b = gen() % a;

      auto it{s.find({a, b})};
      if (it == end(s)) {
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

vector<vector<pair<int, int>>> adjacent(int n, vector<array<int, 3>>& edges) {
  vector<vector<pair<int, int>>> adj(n);

  for (auto [a, b, speed] : edges) {
    adj[a].push_back({b, speed});
    adj[b].push_back({a, speed});
  }

  return adj;
}

vector<int> weight(vector<array<int, 3>>& edges) {
  vector<int> ret;

  for (auto [a, b, weight] : edges) {
    ret.push_back(weight);
  }

  return ret;
}

// 0번과 n-1번을 잇는 경로 중 사용 가중치 범위가 [low, hi)안의 경로가 있는지
bool has_path(int low, int high, vector<vector<pair<int, int>>>& adj) {
  int n = adj.size();
  vector<bool> visited(n, false);
  queue<int> q;
  q.push(0);

  while (!q.empty()) {
    int cur = q.front();
    q.pop();
    visited[cur] = true;

    if (cur == adj.size() - 1) {
      return true;
    }

    for (auto [next, weight] : adj[cur]) {
      if (visited[next] || low > weight || weight >= high) {
        continue;
      }
      q.push(next);
    }
  }

  return false;
}

// 가중치가 low 이상인 간선으로 시작점과 도착점을 연결하는 경로의 최소 상한
int minUpperBound(int low, vector<int>& weights,
                  vector<vector<pair<int, int>>>& adj) {
  int lo = low, hi = weights.size();

  while (lo + 1 < hi) {
    int mid = (lo + hi) / 2;
    if (has_path(weights[low], weights[mid], adj)) {
      hi = mid;
    } else {
      lo = mid;
    }
  }

  if (hi == weights.size()) {
    return numeric_limits<int>::max();
  }

  return weights[lo];
}

// 0번에서 n-1번까지의 최소너비 경로의 너비
int solve(int n, vector<array<int, 3>>& edges) {
  vector<vector<pair<int, int>>> adj{adjacent(n, edges)};
  vector<int> weights{weight(edges)};

  int ret = numeric_limits<int>::max();

  sort(begin(weights), end(weights));

  for (int i = 0; i < weights.size(); i++) {
    ret = min(ret, minUpperBound(i, weights, adj) - weights[i]);
  }

  return ret;
}

int main(void) {
  default_random_engine gen{43};
  auto speed{
      bind(normal_distribution<float>(MAX_SPEED / 2, MAX_SPEED / 4), gen)};

  for (int it = 0; it < TEST_CASES; it++) {
    int n = gen() % (V - 3) + 3;
    vector<array<int, 3>> edges = initialize(n, gen, speed);
    cout << solve(n, edges) << endl;
  }

  return 0;
}