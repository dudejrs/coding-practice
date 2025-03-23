package com.example.cote.PGMRS;

import java.util.*;
import java.util.stream.*;

public class 신입사원_교육 {

  private static final int MAX_ABILITY_LENGTH = 1000000;
  private static final int MAX_ABILITY_VALUE = 100;
  private static final int MAX_NUMER = 10000;

  private static final int TEST_CASES = 10;
  private static final Random random = new Random(43);

  // 신입사원 교육 프로그램을 number만큼 하여 하여 얻을 수 있는 가장 최소의 값
  private static int solve(int[] abilities, int number) {

    PriorityQueue<Integer> pq =
        Arrays.stream(abilities).boxed().collect(Collectors.toCollection(PriorityQueue::new));

    for (int i = 0; i < number; i++) {
      int a = pq.poll();
      int b = pq.poll();
      pq.offer(a + b);
      pq.offer(a + b);
    }

    return pq.stream().reduce(0, Integer::sum);
  }

  public static void main(String... args) {

    for (int it = 0; it < TEST_CASES; it++) {
      int n = random.nextInt(MAX_ABILITY_LENGTH - 2) + 2;
      int[] abilities = new int[n];
      for (int i = 0; i < n; i++) {
        abilities[i] = random.nextInt(MAX_ABILITY_VALUE);
      }
      int number = random.nextInt(MAX_NUMER);

      System.out.println(solve(abilities, number));
    }
  }
}
