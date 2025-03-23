package com.example.cote.GJM;

import java.io.*;
import java.nio.file.*;
import java.util.*;

public class 게임판_덮기 {

  private static int[][][] convertType = {
    {{0, 0}, {1, 0}, {0, 1}},
    {{0, 0}, {0, 1}, {1, 1}},
    {{0, 0}, {1, 0}, {1, 1}},
    {{0, 0}, {1, 0}, {1, -1}}
  };

  private static int[] parseNumbers(String s) {
    return Arrays.stream(s.split(" ")).mapToInt(Integer::parseInt).toArray();
  }

  private static int[][] getBoard(BufferedReader rd, int h, int w) throws IOException {
    int[][] board = new int[h][w];

    for (int i = 0; i < h; i++) {
      Arrays.fill(board[i], 0);
    }

    for (int y = 0; y < h; y++) {
      String str = rd.readLine();
      for (int x = 0; x < w; x++) {
        switch (str.charAt(x)) {
          case '#':
            board[y][x] = 2;
            break;
          case '.':
            board[y][x] = 0;
        }
      }
    }

    return board;
  }

  private static boolean set(int[][] board, int type, int y, int x, int h, int w, int delta) {
    boolean answer = true;

    for (int i = 0; i < 3; i++) {
      int ny = y + convertType[type][i][0];
      int nx = x + convertType[type][i][1];

      if (ny < 0 || ny >= h || nx < 0 || nx >= w) {
        answer = false;
        continue;
      }
      board[ny][nx] += delta;

      if (board[ny][nx] > 1) {
        answer = false;
      }
    }

    return answer;
  }

  private static int solve(int[][] board, int h, int w) {

    int targetX = -1;
    int targetY = -1;

    for (int y = 0; y < h; y++) {
      for (int x = 0; x < w; x++) {
        if (board[y][x] == 0) {
          targetY = y;
          targetX = x;
          break;
        }
      }
      if (targetY != -1) break;
    }

    if (targetY == -1) {
      return 1;
    }

    int ret = 0;

    for (int type = 0; type < 4; type++) {
      if (set(board, type, targetY, targetX, h, w, 1)) {
        ret += solve(board, h, w);
      }
      set(board, type, targetY, targetX, h, w, -1);
    }

    return ret;
  }

  public static void main(String... args) throws IOException {

    Path p = Paths.get(System.getProperty("user.dir") + "/data/게임판_덮기.txt");
    BufferedReader rd = Files.newBufferedReader(p);

    int testCases = Integer.parseInt(rd.readLine());

    while (testCases > 0) {

      int[] numbers = parseNumbers(rd.readLine());
      int h = numbers[0];
      int w = numbers[1];
      int[][] board = getBoard(rd, h, w);

      System.out.println(solve(board, h, w));

      testCases--;
    }
  }
}
