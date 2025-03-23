package com.example.cote.PGMRS;

import java.util.*;
import java.util.stream.*;

public class 모의고사 {

  private static final int TEST_CASES = 10;
  private static Random rd = new Random(43);
  private static final int[][] pick = {
    {1, 2, 3, 4, 5},
    {2, 1, 2, 3, 2, 4, 2, 5},
    {3, 3, 1, 1, 2, 2, 4, 4, 5, 5}
  };

  private static int getPick(int student, int problem) {
    int n = pick[student].length;
    return pick[student][problem % n];
  }

  private static int[] solve(int[] answers) {
    int[] nCorrects = new int[3];

    for (int i = 0; i < answers.length; i++)
      for (int s = 0; s < 3; s++) if (getPick(s, i) == answers[i]) nCorrects[s] += 1;

    int max = IntStream.range(0, 3).map(i -> nCorrects[i]).max().getAsInt();

    return IntStream.range(0, 3).filter(i -> nCorrects[i] == max).toArray();
  }

  public static void main(String... args) {

    for (int it = 0; it < TEST_CASES; it++) {

      int n = rd.nextInt(16) + 5;
      int[] answers = new int[n];
      for (int i = 0; i < n; i++) {
        answers[i] = rd.nextInt(5) + 1;
      }
      System.out.println(Arrays.toString(solve(answers)));
    }
  }
}
