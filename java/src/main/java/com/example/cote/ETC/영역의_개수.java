package com.example.cote.HD;

import java.io.*;
import java.nio.file.*;
import java.util.*;

public class 영역의_개수 {

  private static void solve(int[][] map, int n) {}

  public static void main(String... args) throws IOException {
    Path p = Paths.get(System.getProperty("user.dir") + "/data/영역의_개수.txt");
    BufferedReader rd = Files.newBufferedReader(p);

    int testCases = Integer.parseInt(rd.readLine());

    while (testCases > 0) {

      int n = Integer.parseInt(rd.readLine());
      int[][] map = new int[n][n];

      for (int y = 0; y < n; y++) {
        map[y] = Arrays.stream(rd.readLine().split("")).mapToInt(Integer::parseInt).toArray();
      }

      System.out.println("[Solved]");
      solve(map, n);
      System.out.println("[Expected]");
      String cur = rd.readLine();
      while (!"".equals(cur)) {
        System.out.println(cur);
        cur = rd.readLine();
      }

      testCases--;
    }
  }
}
