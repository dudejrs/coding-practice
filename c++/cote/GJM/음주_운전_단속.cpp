#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>
#define N 500
#define C 100
#define Q 1000

using namespace std;

const int INF = numeric_limits<int>::max() / N - 1;

vector<int> split(const string& s) {
  stringstream ss{s};
  istream_iterator<int> start{ss}, end;

  return {start, end};
}

array<int, 2> nums(const string& s) {
  stringstream ss{s};
  istream_iterator<int> it{ss};

  return {*(it++), *(it++)};
}

vector<vector<int>> init(int n, vector<vector<int>>& roads) {
  vector<vector<int>> ret(n, vector<int>(n, INF));

  for (auto& road : roads) {
    int a = road[0] - 1, b = road[1] - 1, d = road[2];
    ret[a][b] = d;
    ret[b][a] = d;
  }

  return ret;
}

vector<vector<int>> floyd(vector<int>& delay, vector<vector<int>>& roads) {
  int n = delay.size();
  vector<vector<int>> adj = init(n, roads);
  vector<vector<int>> dist = adj;
  for (int i = 0; i < n; i++) {
    dist[i][i] = 0;
  }

  vector<pair<int, int>> order;
  for (int i = 0; i < n; i++) {
    order.push_back({delay[i], i});
  }
  sort(begin(order), end(order));

  for (auto [d, k] : order) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
        dist[i][j] = min(dist[i][j], adj[i][k] + d + adj[k][j]);
      }
    }
  }

  return dist;
}

vector<int> solve(vector<int>& delay, vector<vector<int>>& roads,
                  vector<array<int, 2>>& querys) {
  vector<vector<int>> dist = floyd(delay, roads);

  vector<int> ret;
  for (auto [start, end] : querys) {
    ret.push_back(dist[start - 1][end - 1]);
  }

  return ret;
}

int main(void) {
  string buf;
  fstream f("data/음주_운전_단속.txt");

  getline(f, buf);
  int test_cases = stoi(buf);

  for (int it = 0; it < test_cases; it++) {
    getline(f, buf);
    auto [v, e] = nums(buf);

    getline(f, buf);
    vector<int> delay = split(buf);

    vector<vector<int>> roads;
    for (int i = 0; i < e; i++) {
      getline(f, buf);
      roads.emplace_back(split(buf));
    }

    getline(f, buf);
    int q = stoi(buf);

    vector<array<int, 2>> querys;
    for (int i = 0; i < q; i++) {
      getline(f, buf);
      querys.push_back(nums(buf));
    }

    getline(f, buf);
    vector<int> answer = split(buf);
    vector<int> solved = solve(delay, roads, querys);

    for (int i = 0; i < q; i++) {
      cout << answer[i] << " " << solved[i] << endl;
    }
  }

  return 0;
}