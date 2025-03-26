#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

vector<int> moves;
vector<char> cache(1 << 25);

inline int cell(int y, int x) { return 1 << (y * 5 + x); }

// 게임판에 놓을 수 있는 블록들의 위치를 미리 계산
void precalc() {
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      vector<int> cells;

      for (int dy = 0; dy < 2; dy++) {
        for (int dx = 0; dx < 2; dx++) {
          cells.push_back(cell(y + dy, x + dx));
        }
      }

      int square = cells[0] + cells[1] + cells[2] + cells[3];
      for (int i = 0; i < 4; i++) {
        moves.push_back(square - cells[i]);
      }
    }
  }

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      moves.push_back(cell(i, j) + cell(i, j + 1));
      moves.push_back(cell(j, i) + cell(j + 1, i));
    }
  }
}

int calc_board(vector<string>& board) {
  int ret = 0;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (board[i][j] != '#') {
        continue;
      }
      ret += cell(i, j);
    }
  }
  return ret;
}

char play(int board) {
  char& ret = cache[board];
  if (ret != -1) return ret;
  ret = 0;

  for (auto move : moves) {
    // 이 블록을 게임판에 놓을 수 있는가 확인
    if ((move & board) != 0) {
      continue;
    }
    // 상대편이 지면은 이길 수 있다.
    if (!play(board | move)) {
      ret = 1;
      break;
    }
  }
  return ret;
}

string solve(vector<string>& board) {
  if (moves.size() == 0) {
    precalc();
  }
  fill(begin(cache), end(cache), -1);

  int b = calc_board(board);

  return play(b) == 1 ? "WINNING" : "LOSING";
}

int main(void) {
  string buf;
  fstream f("./data/블록_게임.txt");
  getline(f, buf);
  int test_cases = stoi(buf);

  for (int it = 0; it < test_cases; it++) {
    vector<string> board;

    for (int i = 0; i < 5; i++) {
      getline(f, buf);
      board.push_back(buf);
    }
    getline(f, buf);
    string answer{buf};
    cout << answer << " " << solve(board) << endl;
  }

  return 0;
}