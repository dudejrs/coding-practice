#include <format>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<string> split(const string& s) {
  vector<string> ret;
  stringstream ss(s);
  string buf;

  while (getline(ss, buf, ' ')) {
    ret.push_back(buf);
  }

  return ret;
}

struct BipartiteUnionFind {
  vector<int> parent, rank, enemy, size;

  BipartiteUnionFind(int n) : parent(n), rank(n, 0), enemy(n, -1), size(n, 1) {
    for (int i = 0; i < n; i++) {
      parent[i] = i;
    }
  }

  int find(int u) {
    if (parent[u] == u) return u;
    return parent[u] = find(parent[u]);
  }

  int merge(int u, int v) {
    if (u == -1 || v == -1) return max(u, v);

    u = find(u);
    v = find(v);

    if (u == v) return u;

    if (rank[u] > rank[v]) swap(u, v);
    if (rank[u] == rank[v]) rank[u]++;
    parent[u] = v;
    size[v] += size[u];

    return v;
  }

  bool dis(int u, int v) {
    u = find(u);
    v = find(v);

    if (u == v) return false;

    int a = merge(u, enemy[v]), b = merge(v, enemy[u]);
    enemy[a] = b;
    enemy[b] = a;

    return true;
  }

  bool ack(int u, int v) {
    u = find(u);
    v = find(v);

    if (enemy[u] == v) return false;

    int a = merge(u, v), b = merge(enemy[u], enemy[v]);
    enemy[a] = b;
    if (b != -1) enemy[b] = a;

    return true;
  }
};

int max_party(int n, BipartiteUnionFind& groups) {
  int ret = 0;

  for (int i = 0; i < n; i++) {
    if (groups.find(i) == i) {
      int enemy = groups.enemy[i];

      if (enemy > i) continue;
      int size = groups.size[i];
      int enemy_size = (enemy == -1 ? 0 : groups.size[enemy]);

      ret += max(size, enemy_size);
    }
  }

  return ret;
}

string solve(int n, vector<vector<string>>& comments) {
  ostringstream oss;
  BipartiteUnionFind groups(n);
  bool isContradicted = false;

  for (int i = 0; i < comments.size(); i++) {
    int u = stoi(comments[i][1]), v = stoi(comments[i][2]);

    if (comments[i][0] == "ACK") {
      isContradicted = !groups.ack(u, v);
    } else if (comments[i][0] == "DIS") {
      isContradicted = !groups.dis(u, v);
    }

    if (isContradicted) {
      oss << "CONTRACITION " << i + 1;
      return oss.str();
    }
  }

  oss << "MAX PARTY SIZE IS " << max_party(n, groups);
  return oss.str();
}

int main(void) {
  string buf;
  fstream fd("data/에디터_전쟁.txt");

  getline(fd, buf);
  int test_cases = stoi(buf);

  for (int it = 0; it < test_cases; it++) {
    getline(fd, buf);
    vector<string> tokens = split(buf);
    int n = stoi(tokens[0]);
    int m = stoi(tokens[1]);
    vector<vector<string>> comments;

    for (int i = 0; i < m; i++) {
      getline(fd, buf);
      comments.push_back(split(buf));
    }

    getline(fd, buf);
    string answer = buf;
    cout << answer << " " << solve(n, comments) << endl;
  }

  return 0;
}