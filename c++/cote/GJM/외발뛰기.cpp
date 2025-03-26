#include <iostream>
#include <random>
#include <vector>
#define N 100
#define TEST_CASES 10

using namespace std;

int cache[N][N];

int** initialize(default_random_engine& gen) {
  uniform_int_distribution<int> dis(11, 23);

  int** map = new int*[N];

  for (int i = 0; i < N; i++) {
    map[i] = new int[N];
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      map[i][j] = dis(gen);
    }
  }

  return map;
}

bool solve(int** map, int x, int y) {
  if (x >= N || y >= N) return false;
  if (x == N - 1 && y == N - 1) return true;

  int jump = map[y][x];

  return (solve(map, x + jump, y) || solve(map, x, y + jump));
}

int solve2(int** map, int x, int y) {
  if (x >= N || y >= N) return 0;
  if (x == N - 1 && y == N - 1) return 1;

  int& ret = cache[y][x];
  if (ret != -1) return ret;
  int jump = map[y][x];

  return (ret = solve2(map, x + jump, y) || solve2(map, x, y + jump));
}

int main(void) {
  default_random_engine gen(43);

  for (int i = 0; i < TEST_CASES; i++) {
    int** map = initialize(gen);
    memset(cache, -1, sizeof(cache));

    cout << boolalpha << solve(map, 0, 0) << "," << solve2(map, 0, 0) << endl;

    for (int i = 0; i < N; i++) {
      delete[] map[i];
    }

    delete[] map;
  }

  return 0;
}