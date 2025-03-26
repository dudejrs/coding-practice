#include <cmath>
#include <fstream>
#include <iostream>
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

int sliding_window(const vector<int>& signals, int k) {
  vector<long long> psum(signals.size());

  psum[0] = signals[0];

  for (int i = 0; i < signals.size(); i++) psum[i] = psum[i - 1] + signals[i];

  int ret = 0, tail = 0;
  for (int head = 0; head < psum.size(); head++) {
    while (tail + 1 < psum.size() && psum[head] + k > psum[tail]) tail++;

    if (psum[head] + k == psum[tail]) ret++;
  }
  return ret;
}

int main(void) {
  int n = 100000;
  int k = 12345;

  RNG r;

  vector<int> signals(n);
  for (int i = 0; i < n; i++) signals.push_back(r.next());
  cout << sliding_window(signals, k) << endl;

  return 0;
}