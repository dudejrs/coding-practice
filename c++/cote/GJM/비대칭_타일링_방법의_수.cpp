#include <fstream>
#include <iostream>
#include <string>
#define N 100
#define MOD 1000000007

using namespace std;

int cache[N + 1];

int tiling(int k, int n) {
  int& ret = cache[k];
  if (ret != -1) return ret;
  if (k >= n - 1) return 1;

  return ret = (tiling(k + 1, n) + tiling(k + 2, n)) % MOD;
}

int tiling_wrapper(int n) {
  memset(cache, -1, sizeof(cache));
  return tiling(0, n);
}

int solve(int n) {
  if (n % 2 == 0)
    return (tiling_wrapper(n) - tiling_wrapper(n / 2) -
            tiling_wrapper(n / 2 - 1) + 2 * MOD) %
           MOD;

  return (tiling_wrapper(n) - tiling_wrapper(n / 2) + MOD) % MOD;
}

int main(void) {
  fstream fd("data/비대칭_타일링_방법의_수.txt");
  string buf;

  getline(fd, buf);
  int test_cases = stoi(buf);

  for (int i = 0; i < test_cases; i++) {
    getline(fd, buf);

    int n = stoi(buf);
    cout << solve(n) << endl;
  }

  return 0;
}