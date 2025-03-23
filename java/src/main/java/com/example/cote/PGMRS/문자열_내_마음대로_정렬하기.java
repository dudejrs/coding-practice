package com.example.cote.PGMRS;

import java.util.*;

public class 문자열_내_마음대로_정렬하기 {

  private static final int TEST_CASES = 10;
  private static final int N = 50;
  private static final int M = 100;
  private static Random rd = new Random(43);

  private static String[] randomStringArray() {
    int n = rd.nextInt(N - 1) + 1;
    int m = rd.nextInt(M - 1) + 1;
    String[] ret = new String[n];

    for (int i = 0; i < n; i++) {
      StringBuilder builder = new StringBuilder();
      for (int j = 0; j < m; j++) builder.appendCodePoint(rd.nextInt('z' - 'a') + 'a');
      ret[i] = builder.toString();
    }

    return ret;
  }

  private static String[] solve(String[] a, int m) {

    Arrays.sort(
        a,
        (x, y) -> {
          if (x.charAt(m) != y.charAt(m)) return x.charAt(m) - y.charAt(m);
          else return x.compareTo(y);
        });

    return a;
  }

  public static void main(String... args) {

    for (int it = 0; it < TEST_CASES; it++) {
      String[] randomStrings = randomStringArray();
      int m = rd.nextInt(randomStrings[0].length());
      System.out.println(m);
      System.out.println(Arrays.toString(solve(randomStrings, m)));
    }
  }
}
