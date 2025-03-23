package com.example.cote.PGMRS;

import java.util.*;

public class 피보나치_수 {

  private static final int TEST_CASES = 10;
  private static final int MAX_N = 100000;
  private static final int M = 1234567;
  private static final Random rd = new Random(43);

  private static final int[] cache = new int[MAX_N + 1];

  private static int fibonacci(int n) {

    if (cache[n] != -1) return cache[n];
    if (n == 0 || n == 1) return cache[n] = n;

    return cache[n] = (fibonacci(n - 1) + fibonacci(n - 2)) % M;
  }

  private static int solve(int n) {
    Arrays.fill(cache, -1);
    for (int i = 0; i <= n; i++) {
      fibonacci(i);
    }
    return fibonacci(n);
  }

  public static void main(String... args) {

    for (int it = 0; it < TEST_CASES; it++) {
      int n = rd.nextInt(MAX_N - 2) + 2;
      System.out.println(solve(n));
    }
  }
}
