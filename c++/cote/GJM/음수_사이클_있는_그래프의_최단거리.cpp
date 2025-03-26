#include <functional>
#include <iostream>
#include <numeric>
#include <random>
#define N 100
#define TEST_CASES 10
#define M 4500000

using namespace std;
using Graph = vector<vector<pair<int, double>>>;

Graph initialize(int n, function<bool()> is_connected,
                 function<double()> weight) {
  Graph ret(n);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i == j || !is_connected()) {
        continue;
      }
      ret[i].push_back({j, weight()});
    }
  }

  return ret;
}

vector<vector<bool>> floyd(Graph& adj) {
  int n = adj.size();
  vector<vector<bool>> ret(n, vector<bool>{false});

  for (int cur = 0; cur < n; cur++) {
    for (auto [next, cost] : adj[cur]) {
      ret[cur][next] = true;
    }
  }

  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        ret[i][j] = ret[i][j] || (ret[i][k] && ret[k][j]);
      }
    }
  }

  return ret;
}

string solve(int src, int target, Graph& adj) {
  int n = adj.size();
  vector<vector<bool>> reachable = floyd(adj);

  vector<double> upper(n, numeric_limits<double>::max());
  upper[src] = 0;

  for (int it = 0; it < n - 1; it++) {
    for (int cur = 0; cur < n; cur++) {
      for (auto [next, weight] : adj[cur]) {
        if (upper[next] > upper[cur] + weight) {
          upper[next] = upper[cur] + weight;
        }
      }
    }
  }

  for (int cur = 0; cur < n; cur++) {
    for (auto [next, weight] : adj[cur]) {
      if (upper[next] > upper[cur] + weight) {
        if (reachable[src][cur] && reachable[cur][target]) {
          return "INFINITY";
        }
      }
    }
  }

  if (upper[target] >= numeric_limits<double>::max() - M) {
    return "UNREACHABLE";
  }

  return to_string(upper[target]);
}

int main(void) {
  default_random_engine gen(43);
  auto is_connected{bind(bernoulli_distribution(0.1), gen)};
  auto weight{bind(normal_distribution<double>(300, 200), gen)};

  for (int it = 0; it < TEST_CASES; it++) {
    int n = gen() % (N - 3) + 3;
    int target = gen() % (n - 1) + 1;
    vector<vector<pair<int, double>>> adj = initialize(n, is_connected, weight);
    cout << solve(0, target, adj) << endl;
  }

  return 0;
}