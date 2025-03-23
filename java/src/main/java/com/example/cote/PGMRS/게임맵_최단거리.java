package com.example.cote.PGMRS;

import java.util.*;

public class 게임맵_최단거리 {

  private static final int TEST_CASES = 10;
  private static final Random rd = new Random(43);
  private static final int[] dy = {-1, 0, 0, 1};
  private static final int[] dx = {0, -1, 1, 0};
  private static int[][] map;
  private static int width;
  private static int height;

  private static void initialize() {

    width = rd.nextInt(5 + 1) + 5;
    height = rd.nextInt(5 + 1) + 5;

    map = new int[height][width];

    for (int i = 0; i < height; i++)
      for (int j = 0; j < width; j++)
        map[i][j] =
            (rd.nextInt() % 2 != 0 && rd.nextInt() % 3 != 0 && rd.nextInt() % 5 != 0) ? 1 : 0;

    map[0][0] = 0;
    map[height - 1][width - 1] = 0;

    return;
  }

  private static int solve() {

    boolean[][] visited = new boolean[height][width];
    int[][] counts = new int[height][width];

    for (int i = 0; i < height; i++) {
      Arrays.fill(visited[i], false);
      Arrays.fill(counts[i], 0);
    }

    Queue<List<Integer>> q = new LinkedList<>();
    q.offer(List.of(0, 0));

    while (!q.isEmpty()) {

      List<Integer> cur = q.poll();
      int y = cur.get(0);
      int x = cur.get(1);
      int count = counts[y][x];

      for (int d = 0; d < 4; d++) {
        int ny = y + dy[d];
        int nx = x + dx[d];

        if (ny < 0 || ny >= height || nx < 0 || nx >= width) continue;
        if (visited[ny][nx] || (map[ny][nx] == 1)) continue;

        visited[ny][nx] = true;
        counts[ny][nx] = count + 1;
        q.offer(List.of(ny, nx));
      }
    }

    return counts[height - 1][width - 1];
  }

  public static void main(String... args) {

    for (int it = 0; it < TEST_CASES; it++) {
      initialize();
      System.out.println(solve());
    }
  }
}
