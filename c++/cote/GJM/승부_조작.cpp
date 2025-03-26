#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
#define N 12
#define M 100

using namespace std;

pair<int, int> split(const string& s) {
  stringstream ss{s};
  istream_iterator<int> it{ss};

  return {*(it)++, *(it)++};
}

vector<int> getWinnings(const string& s) {
  stringstream ss{s};
  istream_iterator<int> start{ss}, end;

  return {start, end};
}

inline int source() { return 0; }

inline int match(int i) { return i + 1; }

inline int player(int m, int i) { return m + i + 1; }

inline int sink(int m, int n) { return m + n + 1; }

int networkFlow(int src, int sink, vector<vector<int>>& capacity) {
  int v = capacity.size();
  vector<vector<int>> flow(v, vector<int>(v, 0));

  int totalFlow = 0;

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

    totalFlow += amount;
  }

  return totalFlow;
}

bool canWinWith(int totalWins, int n, int m, vector<int>& winnings,
                vector<vector<int>>& capacity) {
  if (*max_element(begin(winnings) + 1, end(winnings)) >= totalWins) {
    return false;
  }

  for (int i = 0; i < n; i++) {
    int maxWin = (i == 0 ? totalWins : totalWins - 1);
    capacity[player(m, i)][sink(m, n)] = maxWin - winnings[i];
  }

  return networkFlow(source(), sink(m, n), capacity) == m;
}

// 0번 선수가 1등하기 위해 필요한 최소한의 승수
int solve(vector<int>& winnings, vector<pair<int, int>>& matches) {
  int m = winnings.size(), n = matches.size();
  int v = m + n + 2;
  vector<vector<int>> capacity(v, vector<int>(v, 0));

  for (int i = 0; i < m; i++) {
    capacity[source()][match(i)] = 1;

    auto [a, b] = matches[i];

    capacity[match(i)][player(m, a)] = 1;
    capacity[match(i)][player(m, b)] = 1;
  }

  int remaining = 0;  // 0번 선수의 남은 매치 개수
  for (int i = 0; i < m; i++) {
    remaining += capacity[match(i)][player(m, 0)];
  }

  for (int i = 0; i <= m; i++) {
    if (remaining < i) {
      break;
    }

    if (canWinWith(winnings[0] + i, n, m, winnings, capacity)) {
      return winnings[0] + i;
    }
  }

  return -1;
}

int main(void) {
  string buf;
  fstream f("./data/승부_조작.txt");

  getline(f, buf);
  int test_cases = stoi(buf);

  for (int it = 0; it < test_cases; it++) {
    getline(f, buf);
    auto [n, m] = split(buf);

    getline(f, buf);
    vector<int> winnings{getWinnings(buf)};

    vector<pair<int, int>> matches;
    for (int i = 0; i < m; i++) {
      getline(f, buf);
      matches.emplace_back(split(buf));
    }

    getline(f, buf);
    int answer = stoi(buf);
    int solved = solve(winnings, matches);
    cout << answer << " " << solved << endl;
  }

  return 0;
}