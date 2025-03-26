#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>
#define N 10
#define NEGINF numeric_limits<int>::min()

using namespace std;

int cache[N + 1][N + 1];

vector<int>& split(const string& s) {
  stringstream ss(s);
  string temp;

  vector<int>* ret = new vector<int>();

  while (getline(ss, temp, ' ')) {
    ret->push_back(stoi(temp));
  }

  return *ret;
}

vector<int>& getSequence(const string& s) { return split(s); }

int solve(int curA, int curB, vector<int>& a, vector<int>& b) {
  int& ret = cache[curA + 1][curB + 1];

  if (ret != -1) return ret;

  ret = 2;

  int lastA = (curA == -1 ? NEGINF : a[curA]);
  int lastB = (curB == -1 ? NEGINF : b[curB]);
  int maxElement = max(lastA, lastB);

  for (int i = curA + 1; i < a.size(); i++) {
    if (maxElement < a[i]) {
      ret = max(ret, solve(i, curB, a, b) + 1);
    }
  }

  for (int j = curB + 1; j < b.size(); j++) {
    if (maxElement < b[j]) {
      ret = max(ret, solve(curA, j, a, b) + 1);
    }
  }

  return ret;
}

int main(void) {
  fstream fd("data/합친최대증가부분수열.txt");
  string buf;

  getline(fd, buf);
  int test_cases = stoi(buf);

  while (test_cases > 0) {
    memset(cache, -1, sizeof(cache));

    getline(fd, buf);

    getline(fd, buf);
    vector<int> a = getSequence(buf);
    getline(fd, buf);
    vector<int> b = getSequence(buf);

    vector<int> c;
    cout << solve(-1, -1, a, b) - 2 << endl;

    test_cases--;
  }

  return 0;
}
