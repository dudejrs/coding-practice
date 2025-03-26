#include <cmath>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>

#define N 50000000
#define K 5000000

using namespace std;

struct RNG {
  unsigned seed;
  RNG() : seed(1983) {}
  unsigned next() {
    unsigned ret = seed;
    seed = ((seed * 214013u) + 2531011u);
    return ret % 10000 + 1;
  }
};

vector<int> split(const string& s) {
  vector<int> ret;
  stringstream ss(s);
  string buf;

  while (getline(ss, buf, ' ')) {
    ret.push_back(stoi(buf));
  }

  return ret;
}

int solve(int n, int k) {
  RNG r;

  int ret = 0;
  long long psum = 0;
  queue<long long> q;

  for (int i = 0; i < n; i++) {
    psum += r.next();
    q.push(psum);

    while (q.front() + k < psum) q.pop();
    if (q.front() + k == psum) ret++;
  }
  return ret;
}

int main(void) {
  fstream fd("data/외계신호분석.txt");
  string buf;

  getline(fd, buf);
  int test_cases = stoi(buf);

  while (test_cases > 0) {
    getline(fd, buf);

    vector<int> s = split(buf);

    cout << solve(s[1], s[0]) << endl;
    test_cases--;
  }

  return 0;
}