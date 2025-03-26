#include <fstream>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
#define N 100
#define M 100
#define MAX_PRICES 100000

using namespace std;

pair<int, int> get_nums(const string& s) {
  stringstream ss{s};
  istream_iterator<int> it{ss};

  return {*(it++), *(it++)};
}

vector<int> split(const string& s) {
  stringstream ss{s};
  istream_iterator<int> start{ss}, end;

  return {start, end};
}

inline int source() { return 0; }

inline int sink(int n, int m) { return n + m + 1; }

inline int project(int i) { return i + 1; }

inline int item(int n, int i) { return n + i + 1; }

vector<vector<int>> initialize(const vector<int>& project_profits,
                               const vector<int>& purchasing_costs,
                               const vector<vector<int>>& adj) {
  int n = project_profits.size();
  int m = purchasing_costs.size();
  int v = n + m + 2;

  vector<vector<int>> capacity(v, vector<int>(v, 0));

  for (int i = 0; i < n; i++) {
    capacity[source()][project(i)] = project_profits[i];
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (adj[i][j] > 0) {
        capacity[project(i)][item(n, i)] = numeric_limits<int>::max();
      }
    }
  }

  for (int i = 0; i < m; i++) {
    capacity[item(n, i)][sink(n, m)] = purchasing_costs[i];
  }

  return capacity;
}

int network_flow(int src, int sink, vector<vector<int>>& capacity,
                 vector<vector<int>>& flow) {
  int v = capacity.size();
  int total_capcity = 0;

  while (true) {
    vector<int> parent(v, -1);
    queue<int> q;

    q.push(src);
    parent[src] = src;

    while (!q.empty()) {
      int cur = q.front();
      q.pop();

      for (int next = 0; next < v; next++) {
        if (capacity[cur][next] - flow[cur][next] > 0 && parent[next] == -1) {
          q.push(next);
          parent[next] = cur;
        }
      }
    }

    if (parent[sink] == -1) {
      break;
    }

    int amount = numeric_limits<int>::max();

    for (int p = sink; p != src; p = parent[p]) {
      amount = min(amount, capacity[parent[p]][p] - flow[parent[p]][p]);
    }

    for (int p = sink; p != src; p = parent[p]) {
      flow[parent[p]][p] += amount;
      flow[p][parent[p]] -= amount;
    }

    total_capcity += amount;
  }

  return total_capcity;
}

int solve(const vector<int>& project_profits,
          const vector<int>& purchasing_costs, const vector<vector<int>>& adj) {
  int n = project_profits.size();
  int m = purchasing_costs.size();
  int v = n + m + 2;

  vector<vector<int>> capacity =
      initialize(project_profits, purchasing_costs, adj);
  vector<vector<int>> flow(v, vector<int>(v, 0));

  int sum_of_profits =
      accumulate(begin(project_profits), end(project_profits), 0);
  int min_capacity = network_flow(source(), sink(n, m), capacity, flow);

  return sum_of_profits - min_capacity;
}

int main(void) {
  string buf;
  fstream f("data/국책_사업.txt");

  getline(f, buf);
  int test_cases = stoi(buf);

  for (int it = 0; it < test_cases; it++) {
    getline(f, buf);
    auto [n, m] = get_nums(buf);
    getline(f, buf);
    vector<int> project_profits = split(buf);
    getline(f, buf);
    vector<int> purchasing_costs = split(buf);

    vector<vector<int>> adj(n);

    for (int i = 0; i < n; i++) {
      getline(f, buf);
      adj[i] = split(buf);
    }

    getline(f, buf);
    int answer = stoi(buf);

    cout << answer << " " << solve(project_profits, purchasing_costs, adj)
         << endl;
  }

  return 0;
}