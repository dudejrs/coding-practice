package com.example.cote.PGMRS;

import java.io.*;
import java.nio.file.*;
import java.util.*;

public class 파괴되지_않은_건물 {

  private static final int MAX_BOARD_ROWS = 1000;
  private static final int MAX_BOARD_COLS = 1000;
  private static final int MAX_BOARD_DURABILITY = 1000;
  private static final int MAX_SKILLS_LENGTH = 250000;
  private static final int MAX_SKILLS_DEGREE = 100;

  private static int solve(int[][] board, int[][] skills) {
    int row = board.length;
    int col = board[0].length;
    int[][] changes = new int[row + 1][col + 1];

    for (int[] skill : skills) {
      int type = skill[0];
      int r1 = skill[1];
      int c1 = skill[2];
      int r2 = skill[3] + 1;
      int c2 = skill[4] + 1;
      int degree = skill[5];

      if (type == 1) degree = -degree;

      changes[r1][c1] += degree;
      changes[r2][c1] -= degree;
      changes[r1][c2] -= degree;
      changes[r2][c2] += degree;
    }

    for (int y = 0; y < changes.length; y++) {
      for (int x = 0; x < changes[y].length; x++) {
        int left = x > 0 ? changes[y][x - 1] : 0;
        int up = y > 0 ? changes[y - 1][x] : 0;
        int diag = x > 0 && y > 0 ? changes[y - 1][x - 1] : 0;
        changes[y][x] += left + up - diag;
      }
    }

    int safe = 0;

    for (int y = 0; y < board.length; y++) {
      for (int x = 0; x < board[y].length; x++) {
        if (board[y][x] + changes[y][x] > 0) {
          safe++;
        }
      }
    }

    return safe;
  }

  public static void main(String... args) throws IOException {

    Path p = Paths.get(System.getProperty("user.dir") + "/data/파괴되지_않은_건물.txt");
    BufferedReader reader = Files.newBufferedReader(p);

    int testCases = Integer.parseInt(reader.readLine());

    while (testCases-- > 0) {
      int[] nums =
          Arrays.stream(reader.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();

      int[][] board = new int[nums[0]][nums[1]];

      for (int i = 0; i < board.length; i++) {
        board[i] =
            Arrays.stream(reader.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
      }

      int n = Integer.parseInt(reader.readLine());
      int[][] skills = new int[n][6];

      for (int i = 0; i < skills.length; i++) {
        skills[i] =
            Arrays.stream(reader.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
      }

      int answer = Integer.parseInt(reader.readLine());

      System.out.printf("%d %d\n", answer, solve(board, skills));
    }
  }
}
