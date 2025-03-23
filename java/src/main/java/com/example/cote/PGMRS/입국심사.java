package com.example.cote.PGMRS;

import java.util.*;

public class 입국심사 {

  private static final int TEST_CASES = 10;

  private static final int N = 1000000000;
  private static final int T = 1000000000;
  private static final int M = 100000;

  private static int n;
  private static int m;
  private static List<Integer> times;

  private static final Random rd = new Random(43);

  private static boolean binarySearch(long time) {

    long checked = 0;

    for (int i = 0; i < m; i++) {
      checked += time / times.get(i);
    }

    return checked >= n;
  }

  private static long solve() {

    long lo = 1;
    long hi = 1000000000000000000L;

    for (int i = 0; i < 100; i++) {

      long mid = (lo + hi) / 2;

      if (binarySearch(mid)) hi = mid;
      else lo = mid;
    }

    return hi;
  }

  public static void main(String... args) {

    n = 6;
    m = 2;
    times = List.of(7, 10);
    System.out.println(solve());

    for (int it = 0; it < TEST_CASES; it++) {

      n = rd.nextInt(N / 1000);
      m = rd.nextInt(M / 1000);
      times = new LinkedList<>();

      for (int i = 0; i < m; i++) times.add(rd.nextInt(T));

      System.out.println(solve());
    }
  }
}
