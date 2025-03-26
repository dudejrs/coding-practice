#include <functional>
#include <iomanip>
#include <iostream>
#include <random>
#define TEST_CASES 10
#define N 50
#define M 50

using namespace std;

enum class Cell { EMPTY, BLOCKED };

const vector<pair<int, int>> d{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

vector<vector<Cell>> initialize(int n, int m, int k,
                                function<bool()> is_blocked) {
  vector<vector<Cell>> ret(n, vector<Cell>(m, Cell::EMPTY));

  while (k > 0) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (ret[i][j] == Cell::BLOCKED || !is_blocked()) {
          continue;
        }

        ret[i][j] = Cell::BLOCKED;
        k--;
      }
    }
  }

  return ret;
}

bool dfs(int a, vector<vector<bool>>& adj, vector<int>& aMatch,
         vector<int>& bMatch, vector<bool>& visited) {
  if (visited[a]) {
    return false;
  }

  visited[a] = true;

  for (int b = 0; b < adj[0].size(); b++) {
    if (bMatch[b] == -1 || dfs(bMatch[b], adj, aMatch, bMatch, visited)) {
      aMatch[a] = b;
      bMatch[b] = a;
      return true;
    }
  }

  return false;
}

int bipartiteMatch(vector<vector<bool>>& adj) {
  int a = adj.size(), b = adj[0].size();
  vector<int> aMatch(a, -1);
  vector<int> bMatch(b, -1);

  int count = 0;

  for (int i = 0; i < a; i++) {
    vector<bool> visited(a, false);

    if (dfs(i, adj, aMatch, bMatch, visited)) {
      count++;
    }
  }

  return count;
}

bool solve(vector<vector<Cell>>& board) {
  int n = board.size(), m = board[0].size();
  vector<vector<int>> id(n, vector<int>(m, -1));

  int a = 0, b = 0;
  for (int y = 0; y < n; y++) {
    for (int x = 0; x < m; x++) {
      if (board[y][x] == Cell::BLOCKED) {
        continue;
      }

      if ((y + x) % 2 == 0) {
        id[y][x] = a++;
      } else {
        id[y][x] = b++;
      }
    }
  }

  vector<vector<bool>> adj(a, vector<bool>(b, false));

  for (int y = 0; y < n; y++) {
    for (int x = 0; x < m; x++) {
      if ((y + x) % 2 != 0 || board[y][x] == Cell::BLOCKED) {
        continue;
      }

      for (auto [dy, dx] : d) {
        int ny = y + dy;
        int nx = x + dx;

        if (ny < 0 || ny >= n || nx < 0 || nx >= m ||
            board[ny][nx] == Cell::BLOCKED) {
          continue;
        }

        adj[id[y][x]][id[ny][nx]] = true;
      }
    }
  }

  return bipartiteMatch(adj) * 2 == (a + b);
  ;
}

int main(void) {
  default_random_engine gen{43};
  auto is_blocked{bind(bernoulli_distribution(0.05), gen)};

  for (int it = 0; it < TEST_CASES; it++) {
    int n = gen() % (N - 3) + 3;
    int m = gen() % (N - 3) + 3;
    int k = (gen() % (n * m / 8)) * 2;

    vector<vector<Cell>> board = initialize(n, m, k, is_blocked);

    cout << boolalpha << solve(board) << endl;
  }

  return 0;
}