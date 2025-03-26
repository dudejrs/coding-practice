#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <random>
#define N 10
#define TEST_CASES 10
#define MAX_TIME 100

using namespace std;

struct DisjointSet {
  vector<int> parent, rank;
  int size;

  DisjointSet(int n) : parent(n), rank(n - 1) {
    for (int i = 0; i < n; i++) {
      parent[i] = i;
    }
    size = n;
  }

  int find(int u) {
    if (u == parent[u]) return u;
    return parent[u] = find(parent[u]);
  }

  void merge(int u, int v) {
    u = find(u);
    v = find(v);

    if (u == v) return;
    if (rank[u] > rank[v]) swap(u, v);

    parent[u] = v;
    if (rank[u] == rank[v]) rank[u]++;
    size--;
  }
};

vector<vector<int>>* initialize(default_random_engine& gen, int n) {
  vector<vector<int>>* ret = new vector<vector<int>>();
  uniform_int_distribution<int> dis2(MAX_TIME);

  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      ret->push_back(vector<int>{i, j, dis2(gen)});
    }
  }

  sort(begin(*ret), end(*ret),
       [](vector<int> a, vector<int> b) { return a[2] < b[2]; });

  for_each(begin(*ret), end(*ret), [](vector<int>& a) { a.pop_back(); });

  return ret;
}

int solve(vector<vector<int>>& edges, int n) {
  DisjointSet set(n);

  for (int t = 0; t < edges.size(); t++) {
    if (set.size == 1) {
      return t;
    }

    int i = edges[t][0];
    int j = edges[t][1];

    set.merge(i, j);
  }

  return -1;
}

int main(void) {
  default_random_engine gen(43);
  uniform_int_distribution<int> dis1(1, N);

  for (int it = 0; it < TEST_CASES; it++) {
    int n = dis1(gen);
    vector<vector<int>> edges = *(initialize(gen, n));
    cout << solve(edges, n) << endl;
  }

  return 0;
}