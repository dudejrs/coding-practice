#include <algorithm>
#include <functional>
#include <iostream>
#include <limits>
#include <random>
#include <vector>
#define TEST_CASES 10
#define V 200
#define C 100

using namespace std;

using Road = array<int, 3>;

inline double expected(int n) {
  return min(500.0, n * (n - 1) / 4.0) / (n * (n - 1) / 2);
}

pair<vector<Road>, vector<Road>> initialize(int n, function<int()> cost,
                                            default_random_engine& gen) {
  vector<Road> constructed, scheduled;
  auto is_connected{bind(bernoulli_distribution{expected(n)}, gen)};

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (is_connected()) {
        constructed.push_back({i, j, cost()});
      } else {
        scheduled.push_back({i, j, cost()});
      }
    }
  }

  shuffle(begin(scheduled), end(scheduled), gen);
  scheduled.resize(1000 - constructed.size());

  return {constructed, scheduled};
}

vector<vector<int>> construct(int n, vector<Road>& constructed) {
  vector<vector<int>> ret(n, vector<int>(n, numeric_limits<int>::max()));

  for (auto [a, b, cost] : constructed) {
    ret[a][b] = cost;
    ret[b][a] = cost;
  }

  return ret;
}

bool check(Road& road, vector<vector<int>>& adj) {
  int n = adj.size();
  auto [a, b, cost] = road;

  if (adj[a][b] <= cost) {
    return false;
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      adj[i][j] = min(adj[i][j], min(adj[i][a] + cost + adj[b][j],
                                     adj[i][b] + cost + adj[a][j]));
    }
  }

  return true;
}

int solve(int n, vector<Road>& constructed, vector<Road>& scheduled) {
  vector<vector<int>> adj = construct(n, constructed);
  int count = 0;

  for (auto& road : scheduled) {
    if (!check(road, adj)) {
      count++;
    }
  }

  return count;
}

int main(void) {
  default_random_engine gen(43);
  auto cost{bind(uniform_int_distribution(1, C), gen)};

  for (int it = 0; it < TEST_CASES; it++) {
    int n = gen() % (V - 3) + 3;
    auto [constructed, scheduled] = initialize(n, cost, gen);
    cout << scheduled.size() << "," << solve(n, constructed, scheduled) << endl;
  }

  return 0;
}