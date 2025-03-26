#include <functional>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>
#define TEST_CASES 10
#define N 100

using namespace std;

using Graph = vector<vector<int>>;

Graph initialize(int n, function<bool()> is_connected) {
  Graph ret(n);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i != j && !is_connected()) {
        continue;
      }
      ret[i].push_back(j);
    }
  }

  return ret;
}

bool solve(int src, int target, Graph& adj) {
  int n = adj.size();
  vector<vector<bool>> reachable(n, vector<bool>(n, false));

  for (int i = 0; i < n; i++) {
    for (int j : adj[i]) {
      reachable[i][j] = true;
    }
  }

  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        reachable[i][j] =
            reachable[i][j] || (reachable[i][k] && reachable[k][j]);
      }
    }
  }

  return reachable[src][target];
}

int main(void) {
  default_random_engine gen(43);
  auto is_connected{bind(bernoulli_distribution{0.01}, gen)};

  for (int it = 0; it < TEST_CASES; it++) {
    int n = gen() % (N - 3) + 3;
    int k = gen() % (n - 1) + 1;
    Graph adj = initialize(n, is_connected);
    cout << boolalpha << solve(0, k, adj) << endl;
  }

  return 0;
}