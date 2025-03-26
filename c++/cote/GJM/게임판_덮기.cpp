#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const int converType[4][3][2] = {{{0, 0}, {0, 1}, {1, 0}},
                                 {{0, 0}, {1, 0}, {1, 1}},
                                 {{0, 0}, {0, 1}, {1, 1}},
                                 {{0, 0}, {0, 1}, {-1, 1}}};

vector<int>& split(const string& s, char delimiter) {
  vector<int>* result = new vector<int>(0);
  stringstream ss(s);
  string temp;

  while (getline(ss, temp, delimiter)) {
    result->push_back(stoi(temp));
  }

  return *result;
}

vector<vector<int>>& getBoard(fstream& fd, int xlim, int ylim) {
  vector<vector<int>>* board = new vector<vector<int>>();
  string temp;

  for (int i = 0; i < ylim; i++) {
    getline(fd, temp);
    board->push_back(vector<int>());
    for (int j = 0; j < xlim; j++) {
      if (temp[j] == '#') board->at(i).push_back(1);
      if (temp[j] == '.') board->at(i).push_back(0);
    }
  }

  return *board;
}

bool set(vector<vector<int>>& board, int x, int y, int xlim, int ylim, int type,
         int delta) {
  bool answer = true;

  for (int i = 0; i < 3; i++) {
    int nx = x + converType[type][i][0];
    int ny = y + converType[type][i][1];

    if (ny < 0 || ny >= ylim || nx < 0 || nx >= xlim ||
        (board[ny][nx] += delta) > 1) {
      answer = false;
    }
  }

  return answer;
}

int solve(vector<vector<int>>& board, int xlim, int ylim) {
  int x = -1, y = -1;

  for (int i = 0; i < ylim; i++) {
    for (int j = 0; j < xlim; j++) {
      if (board[i][j] == 0) {
        x = j;
        y = i;
        break;
      }
    }
    if (y != -1) break;
  }

  if (y == -1) return 1;

  int result = 0;

  for (int type = 0; type < 4; type++) {
    if (set(board, x, y, xlim, ylim, type, 1)) {
      result += solve(board, xlim, ylim);
    }
    set(board, x, y, xlim, ylim, type, -1);
  }

  return result;
}

int main(void) {
  fstream fd("data/게임판_덮기.txt");
  string buf;

  getline(fd, buf);
  int test_case = stoi(buf);

  while (test_case > 0) {
    getline(fd, buf);
    vector<int> v = split(buf, ' ');
    vector<vector<int>> board = getBoard(fd, v[1], v[0]);

    cout << solve(board, v[1], v[0]) << endl;

    test_case--;
  }

  return 0;
}