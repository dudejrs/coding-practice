package com.example.cote.PGMRS;

import java.util.*;

public class 두개_뽑아서_더하기 {

  private static final int TEST_CASES = 10;
  private static final int N = 100;
  private static Random rd = new Random(43);

  private static int[] solve(int[] r) {

    Set<Integer> a = new HashSet<>();

    for (int i = 0; i < r.length; i++) for (int j = i + 1; j < r.length; j++) a.add(i + j);

    return a.stream().sorted().mapToInt(x -> (int) x).toArray();
  }

  public static void main(String... args) {

    for (int it = 0; it < TEST_CASES; it++) {
      int n = rd.nextInt(N - 2) + 2;
      int[] r = new int[n];
      for (int i = 0; i < n; i++) r[i] = rd.nextInt(100);

      System.out.println(Arrays.toString(solve(r)));
    }
  }
}
