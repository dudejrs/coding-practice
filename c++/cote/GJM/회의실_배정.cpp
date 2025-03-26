#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

bool disjoint(const pair<int, int>& a, const pair<int, int>& b) {
  return a.second <= b.first || b.second <= a.first;
}

int scc(int cur, vector<vector<int>>& adj, vector<int>& sccIds,
        vector<bool>& finished, vector<int>& discovered, int& sccCounter,
        int& vertextCounter, stack<int>& st) {
  int ret = discovered[cur] = vertextCounter++;
  st.push(cur);

  for (int next : adj[cur]) {
    if (discovered[next] == -1) {
      int subtree = scc(next, adj, sccIds, finished, discovered, sccCounter,
                        vertextCounter, st);
      ret = min(ret, subtree);
    } else if (discovered[next] < discovered[cur] && !finished[next]) {
      ret = min(ret, discovered[next]);
    }
  }

  if (ret == discovered[cur]) {
    while (true) {
      int t = st.top();
      st.pop();
      sccIds[t] = sccCounter;
      if (t == cur) break;
    }
    sccCounter++;
  }

  finished[cur] = true;
  return ret;
}

vector<int> labelScc(vector<vector<int>>& adj) {
  vector<int> sccIds(adj.size(), -1);
  vector<bool> finished(adj.size(), false);
  vector<int> discovered(adj.size(), -1);
  int sccCounter = 0, vertextCounter = 0;
  stack<int> st;

  for (int i = 0; i < adj.size(); i++) {
    if (discovered[i] == -1) {
      scc(i, adj, sccIds, finished, discovered, sccCounter, vertextCounter, st);
    }
  }

  return sccIds;
}

vector<vector<int>> initialize(int n, vector<pair<int, int>>& meetings) {
  vector<vector<int>> ret(2 * 2 * n, vector<int>{});

  // 각팀은 주간회의(i)나 월간회의 (i+1)중에 하나를 개최해야 된다
  for (int i = 0; i < 2 * n; i += 2) {
    int j = i + 1;

    //(i or j)절을 추가
    ret[i * 2 + 1].push_back(j * 2);  // ~i => j
    ret[j * 2 + 1].push_back(i * 2);  // ~j => i
  }

  for (int i = 0; i < 2 * n; i++) {
    for (int j = 0; j < i; j++) {
      // 다른팀의 회의시간과 겹치면 안된다. (~i or ~j)절을 추가
      if (!disjoint(meetings[i], meetings[j])) {
        ret[i * 2].push_back(j * 2 + 1);  // i => ~j
        ret[j * 2].push_back(i * 2 + 1);  // j => ~i
      }
    }
  }

  return ret;
}

// 같은 회의시간을 나타내는 두 정점이 같은 강결합요소에 속해 있늑 경우 답이
// 없다.
bool isSolvable(int n, vector<int>& label) {
  for (int i = 0; i < 4 * n; i += 2) {
    if (label[i] == label[i + 1]) {
      return false;
    }
  }
  return true;
}

vector<int> solve(int n, vector<pair<int, int>>& meetings) {
  vector<vector<int>> adj = initialize(n, meetings);

  vector<int> label = labelScc(adj);

  if (!isSolvable(n, label)) {
    return {};
  }

  vector<pair<int, int>> order;
  for (int i = 0; i < 4 * n; i++) {
    order.push_back(pair{-label[i], i});
  }

  sort(begin(order), end(order));

  vector<int> value(2 * n, -1);

  for (int i = 0; i < 2 * n; i++) {
    int vertex = order[i].second;
    int variable = vertex / 2, isTrue = vertex % 2;
    if (value[variable] != -1) continue;

    value[variable] = isTrue;
  }

  return value;
}

int main(void) {
  string buf;

  fstream fd("data/회의실_배정.txt");

  getline(fd, buf);
  int test_cases = stoi(buf);

  for (int it = 0; it < test_cases; it++) {
    getline(fd, buf);
    int n = stoi(buf);

    vector<pair<int, int>> meetings;

    for (int i = 0; i < n; i++) {
      getline(fd, buf);
      stringstream ss{buf};
      istream_iterator<int> it{ss}, end;

      while (it != end) {
        meetings.emplace_back(*(it++), *(it++));
      }
    }

    getline(fd, buf);
    vector<int> solved = solve(n, meetings);

    cout << buf << " " << (solved.size() == 0 ? "IMPOSSIBLE" : "POSSIBLE")
         << endl;

    if (buf == "IMPOSSIBLE") {
      continue;
    }

    vector<pair<int, int>> answer;

    for (int i = 0; i < n; i++) {
      getline(fd, buf);
      stringstream ss{buf};
      istream_iterator<int> it{ss}, end;

      while (it != end) {
        answer.emplace_back(*(it++), *(it++));
      }
    }

    if (solved.size() != 0) {
      for (auto& [first, second] : answer) {
        cout << first << " " << second << endl;
      }
      cout << "===============" << endl;
      for (int i = 0; i < 2 * n; i++) {
        if (solved[i] != 1) continue;
        cout << meetings[i].first << " " << meetings[i].second << endl;
      }
    }
  }

  return 0;
}