#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#define MAX_N 15
#define MAX_ 987654321

using namespace std;

int overlap[MAX_N][MAX_N];
int cache[MAX_N][1 << MAX_N];

int getOverlap(const string& a, const string& b) {
  int count = 0;

  for (int i = 0; i < a.size(); i++) {
    int len = min(a.size() - i, b.size());
    if (a.substr(i, len) == b.substr(0, len)) {
      count = max(count, len);
    }
  }

  return count;
}

void preCalc(const vector<string>& words) {
  for (int i = 0; i < words.size(); i++) {
    for (int j = 0; j < words.size(); j++) {
      overlap[i][j] = getOverlap(words[i], words[j]);
      // overlap[i][j] = max(getOverlap(words[i], words[j]),getOverlap(words[j],
      // words[i]));
    }
  }
}

int restore(int cur, int used, int k) {
  if (used == (1 << k) - 1) return 0;

  int ret = cache[cur][used];
  if (ret != -1) return ret;
  ret = 0;

  for (int i = 0; i < k; i++) {
    if ((used & (1 << i))) continue;

    int cand = overlap[cur][i] + restore(i, used | (1 << i), k);
    ret = max(ret, cand);
  }

  return ret;
}

string reconstruct(int cur, int used, const vector<string>& words) {
  if (used == (1 << words.size()) - 1) return "";

  for (int i = 0; i < words.size(); i++) {
    if (used & (i << i)) continue;

    int ifUsed = restore(i, used + (1 << i), words.size()) + overlap[cur][i];

    if (restore(cur, used, words.size()) == ifUsed) {
      return (words[i].substr(overlap[cur][i]) +
              reconstruct(i, used + (1 << i), words));
    }
  }
  return "Error";
}

string solve(const vector<string>& words) {
  memset(overlap, 0, sizeof(overlap));
  memset(cache, -1, sizeof(cache));
  preCalc(words);
  ` int m = -1;
  int cur_max = 0;

  for (int i = 0; i < words.size(); i++) {
    int tmp = restore(i, 1 << i, words.size());
    if (m < tmp) {
      cur_max = i;
      m = tmp;
    }
  }

  cout << words[cur_max] << reconstruct(cur_max, 1 << cur_max, words) << endl;

  return "";
}

int main(void) {
  fstream fd("data/실험데이터_복구하기.txt");
  string buf;

  getline(fd, buf);
  int test_cases = stoi(buf);

  while (test_cases > 0) {
    getline(fd, buf);

    vector<string> words;
    int nWord = stoi(buf);

    for (int i = 0; i < nWord; i++) {
      getline(fd, buf);
      words.push_back(buf);
    }

    cout << solve(words) << endl;

    test_cases--;
  }

  return 0;
}