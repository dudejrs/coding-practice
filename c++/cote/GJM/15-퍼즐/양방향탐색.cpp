#include <array>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#define TEST_CASES 10

using namespace std;
using namespace std::chrono_literals;

class State {
 public:
  vector<State> getAdjacent();

  State(array<array<int, 4>, 4> board) : board(board) {}
  bool operator<(const State& rhs) const;
  bool operator==(const State& rhs) const;
  pair<int, int> current() const;

  State moved(pair<int, int> before, pair<int, int> after);

  array<array<int, 4>, 4> board;
  static State finished;

 private:
};

vector<pair<int, int>> movement{pair{-1, 0}, pair{1, 0}, pair{0, -1},
                                pair{0, 1}};

State State::finished = State{array<array<int, 4>, 4>{
    {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 0}}}};

State State::moved(pair<int, int> before, pair<int, int> after) {
  State newState(board);
  auto [y, x] = before;
  auto [ny, nx] = after;

  swap(newState.board[y][x], newState.board[ny][nx]);

  return newState;
}

vector<State> State::getAdjacent() {
  vector<State> ret;
  auto [y, x] = current();

  for (const auto& [dy, dx] : movement) {
    int ny = y + dy, nx = x + dx;
    if (ny < 0 || ny >= 4 || nx < 0 || nx >= 4) {
      continue;
    }

    ret.push_back(moved(pair{y, x}, pair{ny, nx}));
  }

  return ret;
}

pair<int, int> State::current() const {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (board[i][j] == 0) {
        return {i, j};
      }
    }
  }
  return {-1, -1};
}

bool State::operator<(const State& rhs) const {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (board[i][j] != rhs.board[i][j]) {
        return board[i][j] < rhs.board[i][j];
      }
    }
  }

  return false;
}
bool State::operator==(const State& rhs) const {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (board[i][j] != rhs.board[i][j]) {
        return false;
      }
    }
  }

  return true;
}

typedef map<State, int> StateMap;

array<array<int, 4>, 4> initialize(int n, function<int()>& generator) {
  State cur = State::finished;
  for (int i = 0; i < n; i++) {
    vector<State> adjacent = cur.getAdjacent();
    int next = generator() % (adjacent.size());
    cur = adjacent[next];
  }

  return cur.board;
}

int sgn(int x) {
  if (!x) {
    return 0;
  }
  return x > 0 ? 1 : -1;
}

int incr(int x) {
  if (x < 0) {
    return x - 1;
  }
  return x + 1;
}

int solve(array<array<int, 4>, 4>& board) {
  State start{board};
  if (start == State::finished) return 0;

  StateMap costs;
  queue<State> q;
  q.push(start);
  costs[start] = 1;
  q.push(State::finished);
  costs[State::finished] = -1;

  while (!q.empty()) {
    State cur = q.front();
    q.pop();
    int cost = costs[cur];

    for (auto& next : cur.getAdjacent()) {
      auto it = costs.find(next);
      if (it == end(costs)) {
        costs[next] = incr(cost);
        q.push(next);
        // 중간에서 만난 경우
      } else if (sgn(it->second) != sgn(cost)) {
        return abs(it->second) + abs(cost) - 1;
      }
    }
  }

  return -1;
}

int main(void) {
  default_random_engine gen(21);
  uniform_int_distribution<int> dis(0, 3);

  function<int()> generator{bind(dis, gen)};

  for (int it = 0; it < TEST_CASES; it++) {
    int answer = gen() % 30;
    array<array<int, 4>, 4> board = initialize(answer, generator);
    for (auto& row : board) {
      for (auto& c : row) {
        cout << setw(4) << c;
      }
      cout << endl;
    }
    cout << "solved : " << solve(board) << endl;
    cout << endl;
  }

  return 0;
}