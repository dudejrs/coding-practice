package com.example.cote.PGMRS;

import java.io.*;
import java.nio.file.*;
import java.util.*;

public class 특이한_양궁_대회 {

  private static int scoreDiff(int[] other, int[] mine) {
    int ret = 0;

    for (int i = 0; i < other.length; i++) {
      if (other[i] == 0 && mine[i] == 0) continue;

      if (other[i] >= mine[i]) {
        ret -= 10 - i;
      } else {
        ret += 10 - i;
      }
    }

    return ret;
  }

  // 가장 큰 점ㅅ 차이로 우승할 수 있는 방법이 여러가지인 경우, 더 낮은 점수를 더 많이 맞춘 경우를 채택
  private static boolean isPrior(int[] base, int[] comp) {
    for (int i = 10; i >= 0; i--) {
      if (comp[i] == base[i]) continue;
      return comp[i] > base[i];
    }

    return false;
  }

  private static int[] search(int cur, int[] hits, int n, int[] other) {

    if (cur == hits.length) {
      if (n > 0) return null;
      if (scoreDiff(other, hits) <= 0) return null;

      return Arrays.copyOf(hits, hits.length);
    }

    int maxDiff = 0;
    int[] result = null;

    for (int i = 0; i <= n; i++) {
      hits[cur] = i;
      int[] mine = search(cur + 1, hits, n - i, other);

      if (mine == null) continue;

      int diff = scoreDiff(other, mine);
      if (diff > maxDiff || (diff == maxDiff && isPrior(result, mine))) {
        maxDiff = diff;
        result = mine;
      }
    }

    return result;
  }

  private static int[] solve(int[] info) {
    int n = Arrays.stream(info).sum();
    int[] best = search(0, new int[11], n, info);

    if (best == null) {
      return new int[] {-1};
    }

    return best;
  }

  public static void main(String... args) throws IOException {

    Path p = Paths.get(System.getProperty("user.dir") + "/data/특이한_양궁_대회.txt");
    BufferedReader reader = Files.newBufferedReader(p);

    int testCases = Integer.parseInt(reader.readLine());

    while (testCases-- > 0) {
      int[] info =
          Arrays.stream(reader.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();

      int[] answer =
          Arrays.stream(reader.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();

      System.out.printf("%s %s\n", Arrays.toString(answer), Arrays.toString(solve(info)));
    }
  }
}
