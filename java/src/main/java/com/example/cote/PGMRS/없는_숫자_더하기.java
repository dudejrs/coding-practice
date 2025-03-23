package com.example.cote.PGMRS;

import java.util.*;

public class 없는_숫자_더하기 {

  private static final int TEST_CASES = 10;
  private static final Random rd = new Random(43);

  private static final int[] samples = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  private static int[] sample() {
    List<Integer> ret = new LinkedList<>();

    for (int i = 0; i < samples.length; i++) if (rd.nextInt() % 2 == 0) ret.add(samples[i]);

    return ret.stream().mapToInt(i -> (int) i).toArray();
  }

  private static int solve(int[] numbers) {

    int sum = 0;

    Set<Integer> set = new HashSet<>();

    for (int num : numbers) set.add(num);

    for (int sample : samples) if (!set.contains(sample)) sum += sample;

    return sum;
  }

  public static void main(String... args) {

    for (int it = 0; it < TEST_CASES; it++) {

      int[] numbers = sample();
      System.out.println(solve(numbers));
    }

    return;
  }
}
