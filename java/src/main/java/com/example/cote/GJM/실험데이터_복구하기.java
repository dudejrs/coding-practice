package com.example.cote.GJM;

import java.io.*;
import java.nio.file.*;
import java.util.*;

public class 실험데이터_복구하기 {

  private static int MAX_N = 15;

  private static int[][] overlap = new int[MAX_N][MAX_N];
  private static int[][] cache = new int[MAX_N][1 << MAX_N];
  private static List<String> words;

  private static String reconstruct(int cur, int taken) {

    if (taken == (1 << words.size()) - 1) return "";

    for (int next = 0; next < words.size(); next++) {
      if ((taken & (1 << next)) != 0) continue;
      if (restore(cur, taken) == overlap[cur][next] + restore(next, taken | (1 << next)))
        return words.get(next).substring(overlap[cur][next])
            + reconstruct(next, taken | (1 << next));
    }
    return "Error";
  }

  private static int restore(int cur, int taken) {

    if (taken == (1 << words.size()) - 1) return 0;

    int ret = cache[cur][taken];
    if (ret != -1) return ret;

    ret = 0;

    for (int next = 0; next < words.size(); next++) {
      if ((taken & (1 << next)) != 0) continue;
      ret = restore(next, taken | (1 << next)) + overlap[cur][next];
    }

    return ret;
  }

  private static int calcOverlap(String a, String b) {
    int ret = 0;

    for (int i = 0; i < a.length(); i++) {
      int len = Math.min(a.length() - i, b.length());
      if (a.substring(i, i + len).equals(b.substring(0, len))) {
        ret = Math.max(ret, len);
      }
    }

    return ret;
  }

  private static void precalc() {

    for (int i = 0; i < MAX_N; i++) {
      for (int j = 0; j < MAX_N; j++) {
        overlap[i][j] = 0;
      }
    }

    for (int i = 0; i < MAX_N; i++) {
      for (int j = 0; j < (1 << MAX_N); j++) {
        cache[i][j] = -1;
      }
    }

    for (int i = 0; i < words.size(); i++) {
      for (int j = 0; j < words.size(); j++) {
        overlap[i][j] = calcOverlap(words.get(i), words.get(j));
      }
    }
  }

  private static void solve() {

    precalc();

    int maxIdx = 0;
    int max = 0;

    for (int i = 0; i < words.size(); i++) {
      int tmp = restore(i, (1 << i));

      if (max < tmp) {
        maxIdx = i;
        max = tmp;
      }
    }

    System.out.println(words.get(maxIdx) + reconstruct(maxIdx, (1 << maxIdx)));
  }

  public static void main(String[] args) throws IOException {

    Path p = Paths.get(System.getProperty("user.dir") + "/data/실험데이터_복구하기.txt");
    BufferedReader reader = Files.newBufferedReader(p);

    int test_cases = Integer.parseInt(reader.readLine());

    while (test_cases > 0) {
      int n = Integer.parseInt(reader.readLine());
      words = new LinkedList<>();

      for (int i = 0; i < n; i++) {
        words.add(reader.readLine());
      }

      solve();

      test_cases--;
    }
  }
}
