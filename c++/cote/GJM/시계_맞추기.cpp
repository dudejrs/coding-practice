// 에러 미해결

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#define INF 9999

using namespace std;

vector<int>& getClocks(const string& s) {
  vector<int>* result = new vector<int>();
  stringstream ss(s);
  string sbuf;

  for (int i = 0; i < 12; i++) {
    getline(ss, sbuf, ' ');
    result->push_back(stoi(sbuf));
  }
  return *result;
}

bool aligned(vector<int>& clocks) {
  for (int i = 0; i < 16; i++) {
    if (clocks[i] != 12) return false;
  }

  return true;
}

void push(const char linked[10][16 + 1], vector<int>& clocks, int cur) {
  for (int i = 0; i < 16; i++) {
    if (linked[cur][i] == 'x') {
      clocks[i] += 3;
      if (clocks[i] == 15) clocks[i] = 3;
    }
  }
}

int solve(const char linked[10][16 + 1], vector<int>& clocks, int cur) {
  if (cur == 10) {
    return aligned(clocks) ? 0 : INF;
  }

  int ret = INF;

  for (int i = 0; i < 4; i++) {
    ret = min(ret, i + solve(linked, clocks, cur + 1));
    push(linked, clocks, cur);
  }

  return ret;
}

int main(void) {
  string buf;
  fstream fd("data/시계_맞추기.txt");

  const char linked[10][16 + 1] = {"xxx.............", "...x...x.x.x....",
                                   "....x.....x...xx", "x...xxxx........",
                                   "......xxx.x.x...", "x.x...........xx",
                                   "...x..........xx", "....xx.x......xx",
                                   ".xxxxx..........", "...xxx...x...x.."};

  getline(fd, buf);
  int test_cases = stoi(buf);

  while (test_cases > 0) {
    getline(fd, buf);
    vector<int> clocks = getClocks(buf);

    cout << solve(linked, clocks, 0) << endl;

    test_cases--;
  }

  return 0;
}