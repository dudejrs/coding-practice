#include <iostream>
#include <queue>
#include <random>

#define TEST_CASES 10

using namespace std;

int dy[4] = {-1, 0, 0, 1};
int dx[4] = {0, -1, 1, 0};

int solve(int height, int width, int** maps) {
  bool visited[height][width];
  memset(visited, false, sizeof(visited));
  int counts[height][width];
  memset(counts, 0, sizeof(counts));

  queue<pair<int, int>> q;
  q.push(make_pair(0, 0));

  while (!q.empty()) {
    pair<int, int> cur = q.front();
    q.pop();
    int y = cur.first, x = cur.second;
    int cur_count = counts[y][x];

    for (int d = 0; d < 4; d++) {
      int ny = y + dy[d];
      int nx = x + dx[d];

      if (ny < 0 || ny >= height || nx < 0 || nx >= width) continue;
      if (visited[ny][nx] || (maps[ny][nx] == 1)) continue;

      visited[ny][nx] = true;
      counts[ny][nx] = cur_count + 1;
      q.push(make_pair(ny, nx));
    }
  }

  return counts[height - 1][width - 1];
}

int main(void) {
  default_random_engine gen(43);
  uniform_int_distribution<int> dis(5, 10);

  for (int it = 0; it < TEST_CASES; it++) {
    int height = dis(gen);
    int width = dis(gen);
    int** maps = new int*[height];
    for (int i = 0; i < height; i++) {
      maps[i] = new int[width];
      for (int j = 0; j < width; j++)
        maps[i][j] = dis(gen) % 2 && dis(gen) % 3 && dis(gen) % 5;
    }

    maps[0][0] = 0;
    maps[height - 1][width - 1] = 0;

    cout << solve(height, width, maps) << endl;

    for (int i = 0; i < height; i++) {
      delete[] maps[i];
    }
    delete[] maps;
  }

  return 0;
}