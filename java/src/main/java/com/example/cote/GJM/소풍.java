package com.example.cote.GJM;

import java.io.*;
import java.nio.file.*;
import java.util.*;

public class 소풍 {

  public static boolean[][] parseRelationShip(String s, int n, int m) {
    int[] t = Arrays.stream(s.split(" ")).mapToInt(Integer::parseInt).toArray();

    boolean[][] relationShip = new boolean[n][n];

    for (int k = 0; k < m; k++) {
      int i = t[2 * k];
      int j = t[2 * k + 1];

      relationShip[i][j] = true;
      relationShip[j][i] = true;
    }

    return relationShip;
  }

  public static int solve(boolean[][] relationShip, boolean[] taken, int n) {

    int target = -1;
    for (int i = 0; i < n; i++) {
      if (!taken[i]) {
        target = i;
        break;
      }
    }
    if (target == -1) return 1;

    int ret = 0;

    for (int i = target + 1; i < n; i++) {
      if (!taken[i] && relationShip[target][i]) {
        taken[i] = taken[target] = true;
        ret += solve(relationShip, taken, n);
        taken[i] = taken[target] = false;
      }
    }

    return ret;
  }

  public static void main(String... args) throws IOException {

    Path p = Paths.get(System.getProperty("user.dir") + "/data/소풍.txt");
    BufferedReader rd = Files.newBufferedReader(p);

    int testCases = Integer.parseInt(rd.readLine());

    while (testCases > 0) {

      String[] numbers = rd.readLine().split(" ");
      int n = Integer.parseInt(numbers[0]);
      int m = Integer.parseInt(numbers[1]);
      boolean[][] relationShip = parseRelationShip(rd.readLine(), n, m);
      boolean[] taken = new boolean[n];

      System.out.println(solve(relationShip, taken, n));

      testCases--;
    }
  }
}
