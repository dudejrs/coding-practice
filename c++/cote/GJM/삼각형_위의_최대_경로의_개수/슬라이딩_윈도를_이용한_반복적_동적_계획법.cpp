#include <iostream>
#include <random>

#define TEST_CASE 10
#define MAX_VALUE 13
#define MAX_N 15

using namespace std;

int cache[MAX_N][MAX_N];
int count_cache[2][MAX_N];

int** initialize(default_random_engine& gen, int n) {
  uniform_int_distribution<int> dis(1, MAX_VALUE);

  int** map = new int*[n];
  for (int i = 0; i < n; i++) {
    map[i] = new int[n];
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      map[i][j] = dis(gen);
    }
  }

  return map;
}

void calculate_maximum(int** map, int n) {
  for (int x = 0; x < n; x++) {
    cache[n - 1][x] = map[n - 1][x];
  }

  for (int y = n - 2; y >= 0; y--) {
    for (int x = 0; x < y + 1; x++) {
      cache[y][x] = max(cache[y + 1][x], cache[y + 1][x + 1]) + map[y][x];
    }
  }
}

void calculate_count(int n) {
  for (int x = 0; x < n; x++) {
    count_cache[(n - 1) % 2][x] = 1;
  }

  for (int y = n - 2; y >= 0; y--) {
    for (int x = 0; x < y + 1; x++) {
      int left = cache[y + 1][x];
      int right = cache[y + 1][x + 1];

      if (left > right) {
        count_cache[y % 2][x] = count_cache[(y + 1) % 2][x];
        continue;
      } else if (left < right) {
        count_cache[y % 2][x] = count_cache[(y + 1) % 2][x + 1];
        continue;
      }
      count_cache[y % 2][x] =
          count_cache[(y + 1) % 2][x] + count_cache[(y + 1) % 2][x + 1];
    }
  }
}

int solve(int** map, int n) {
  memset(cache, -1, sizeof(cache));
  memset(count_cache, -1, sizeof(count_cache));
  calculate_maximum(map, n);
  calculate_count(n);

  return count_cache[0][0];
}

int main(void) {
  default_random_engine gen(43);
  for (int i = 0; i < TEST_CASE; i++) {
    int n = gen() % MAX_N;
    int** map = initialize(gen, n);

    cout << solve(map, n) << endl;

    for (int i = 0; i < n; i++) {
      delete[] map[i];
    }
    delete[] map;
  }

  return 0;
}