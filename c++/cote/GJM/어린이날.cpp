#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

tuple<vector<int>, int, int> split(const string& s) {
  stringstream ss{s};
  istream_iterator<string> it{ss};

  string d = *(it++);
  vector<int> digits;
  for (auto& digit : d) {
    digits.push_back(digit - '0');
  }

  int n = stoi(*(it++));
  int m = stoi(*(it++));

  return {digits, n, m};
}

int append(int cur, int edge, int mod) {
  int next = cur * 10 + edge;
  if (next >= mod) return mod + (next % mod);
  return next % mod;
}

long solve(vector<int> digits, int n, int m) {
  sort(begin(digits), end(digits));

  // parent[i] : BFS트리에서 정점 i의 번호
  vector<int> parent(2 * n, -1);
  // choide[i] : parent[i]에서 i로 연결된 간선의 번호
  vector<int> choice(2 * n, -1);

  queue<int> q;
  parent[0] = 0;
  q.push(0);

  while (!q.empty()) {
    int cur = q.front();
    q.pop();

    for (auto& digit : digits) {
      int next = append(cur, digit, n);

      if (parent[next] == -1) {
        parent[next] = cur;
        choice[next] = digit;
        q.push(next);
      }
    }
  }

  // parent[n + m]에 도달하지 못했으면 실패
  if (parent[n + m] == -1) return -1;

  string ret;
  int cur = n + m;

  while (parent[cur] != cur) {
    ret += char('0' + choice[cur]);
    cur = parent[cur];
  }
  reverse(begin(ret), end(ret));

  return stol(ret);
}

int main(void) {
  string buf;

  fstream fd("data/어린이날.txt");

  getline(fd, buf);
  int testCases = stoi(buf);

  while (testCases-- > 0) {
    getline(fd, buf);
    auto [digits, n, m] = split(buf);
    getline(fd, buf);
    long answer = stol(buf);
    cout << answer << " " << solve(digits, n, m) << endl;
  }

  return 0;
}