#include <cmath>
#include <iostream>
#define TEST_CASES 10
#define M 997
#define N 100

using namespace std;

int cache[N];

int solve(int n) {
  if (n <= 1) return 1;
  int& ret = cache[n];
  if (ret != -1) return ret;

  return ret = ((solve(n - 1) + solve(n - 2)) % M);
}

int main(void) {
  memset(cache, -1, sizeof(cache));

  for (int i = 0; i < TEST_CASES; i++) {
    cout << solve(rand() % N) << endl;
  }

  return 0;
}