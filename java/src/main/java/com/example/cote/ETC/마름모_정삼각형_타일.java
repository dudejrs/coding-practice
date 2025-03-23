package com.example.cote.KK;

import java.io.*;
import java.nio.file.*;
import java.util.*;

public class 마름모_정삼각형_타일 {

  private static int solve(int n, int[] tops) {
    int N = n << 1;
    int[] dp = new int[N + 1];
    dp[0] = 1;
    dp[1] = 2;

    for (int i = 2; i <= N; i++) {
      if ((i & 1) == 0 && tops[(i >> 1) - 1] == 1) {
        dp[i - 1] += dp[i - 2];
      }
      dp[i] = (dp[i - 2] + dp[i - 1]) % 10007;
    }

    return dp[N];
  }

  public static void main(String... args) throws IOException {

    Path p = Paths.get(System.getProperty("user.dir") + "/data/마름모_정삼각형_타일.txt");
    BufferedReader rd = Files.newBufferedReader(p);

    int testCases = Integer.parseInt(rd.readLine());

    while (testCases > 0) {
      int n = Integer.parseInt(rd.readLine());
      int[] tops = Arrays.stream(rd.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
      int answer = Integer.parseInt(rd.readLine());
      System.out.println(solve(n, tops) + " " + answer);

      testCases--;
    }
  }
}
