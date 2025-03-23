package com.example.cote.PGMRS;

import java.util.*;
import java.util.stream.*;

public class 가장_큰_수 {

  private static final int TEST_CASES = 10;
  private static final Random rd = new Random(43);
  private static final int N = 1000000;
  private static final int M = 1000;

  private static int[] initialize() {

    int n = rd.nextInt(N - 1) + 1;
    int[] ret = new int[n];

    for (int i = 0; i < n; i++) ret[i] = rd.nextInt(M);

    return ret;
  }

  private static String solve(int[] numbers) {

    return Arrays.stream(numbers)
        .mapToObj(Integer::toString)
        .sorted((a, b) -> -(a + b).compareTo(b + a))
        .collect(Collectors.joining(""))
        .replaceAll("^0+", "0");
  }

  public static void main(String... args) {

    for (int it = 0; it < TEST_CASES; it++) {
      System.out.println(solve(initialize()));
    }
  }
}
