#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define N 2000000000

using namespace std;

vector<int> split(const string& s) {
  stringstream ss(s);
  string buf;
  vector<int> ret;

  while (getline(ss, buf, ' ')) {
    ret.push_back(stoi(buf));
  }

  return ret;
}

bool decision(long long n, long long k, int ratio) {
  return floor((k * 100) / n) > ratio;
}

int solve(long long n, long long k) {
  long long lo = 0, hi = N;
  int ratio = floor((k * 100) / n);

  if (ratio == 100 || !decision(n + N, k + N, ratio)) {
    return -1;
  }

  while (lo + 1 < hi) {
    long long mid = floor((lo + hi) / 2);
    if (decision(n + mid, k + mid, ratio)) {
      hi = mid;
    } else {
      lo = mid;
    }
  }

  return hi;
}

int main(void) {
  fstream fd("data/승률올리기.txt");
  string buf;

  getline(fd, buf);
  int test_cases = stoi(buf);

  while (test_cases > 0) {
    getline(fd, buf);
    vector<int> n = split(buf);
    cout << solve(n[0], n[1]) << endl;

    test_cases--;
  }

  return 0;
}