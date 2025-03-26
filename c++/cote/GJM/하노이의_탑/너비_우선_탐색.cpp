#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
#define MAX_DISCS 12

using namespace std;

vector<vector<int>> get_state(istream& in) {
  string buf;

  vector<vector<int>> ret;

  for (int i = 0; i < 4; i++) {
    getline(in, buf);
    stringstream ss{buf};
    istream_iterator<int> start{ss}, finsish;
    ret.emplace_back(start, finsish);
  }

  return ret;
}

// state의 i번 원반이 몇번째 기둥에 있는지를 반환한다
int get(int state, int i) { return (state >> (i * 2)) & 3; }
// state의 i번 원반을 value번째 기둥으로 설정한다.
int set(int state, int i, int col) {
  return (state & ~(3 << (i * 2))) | (col << (i * 2));
}

// 벡터 state에서 int state로 변환 시킨다.
int translate(vector<vector<int>>& state) {
  int ret = 0;

  for (int col = 0; col < 4; col++) {
    for (const auto& i : state[col]) {
      ret = set(ret, i - 1, col);
    }
  }

  return ret;
}

vector<vector<int>> retreive(int discs, int state) {
  vector<vector<int>> ret(4);

  for (int i = discs - 1; i >= 0; i--) {
    ret[get(state, i)].push_back(i + 1);
  }

  return ret;
}

int bfs(int discs, int start, int finished) {
  vector<int> costs((1 << (discs * 2)), -1);

  queue<int> q;
  q.push(start);
  costs[start] = 0;

  while (!q.empty()) {
    int cur = q.front();
    q.pop();

    // 각 기둥에 제일 위에 있는 원반의 번호를 게산
    int top[4] = {-1, -1, -1, -1};
    for (int i = discs - 1; i >= 0; i--) {
      top[get(cur, i)] = i;
    }

    // i번 기둥의 맨 위에 있는 원반을 j번 기둥으로 옮긴다
    for (int i = 0; i < 4; i++) {
      if (top[i] == -1) {
        continue;
      }

      for (int j = 0; j < 4; j++) {
        if (i != j && (top[j] == -1 || top[j] > top[i])) {
          int next = set(cur, top[i], j);

          if (costs[next] != -1) {
            continue;
          }

          costs[next] = costs[cur] + 1;

          if (next == finished) {
            return costs[next];
          }

          q.push(next);
        }
      }
    }
  }

  return -1;
}

int solve(int discs, vector<vector<int>>& initial, vector<vector<int>>& final) {
  int start = translate(initial);
  int finished = translate(final);

  return bfs(discs, start, finished);
}

int main(void) {
  string buf;
  fstream fd("../data/하노이의_탑.txt");

  getline(fd, buf);
  int testCases = stoi(buf);

  for (int it = 0; it < testCases; it++) {
    getline(fd, buf);
    int discs = stoi(buf);
    vector<vector<int>> initial = get_state(fd);
    vector<vector<int>> final = get_state(fd);

    getline(fd, buf);
    int answer = stoi(buf);
    int solved = solve(discs, initial, final);

    cout << answer << " " << solved << endl;
  }

  return 0;
}