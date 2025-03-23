package com.example.cote.PGMRS;

import java.io.*;
import java.nio.file.*;
import java.util.*;
import java.util.stream.*;

public class 타겟넘버 {

  private static final int MAX_NUMBERS_LENTH = 20;
  private static final int MAX_NUMBER_VALUE = 50;
  private static final int MAX_TARGET_VALUE = 1000;

  private static final int TEST_CASES = 10;
  private static final Random random = new Random(43);

  private static record State(int index, int acc) {}

  private static int solve(int[] numbers, int target) {
    Stack<State> s = new Stack<>();
    s.push(new State(0, 0));

    int ret = 0;

    while (!s.isEmpty()) {
      State state = s.pop();

      if (state.index() == numbers.length) {
        if (state.acc() == target) ret++;
        continue;
      }

      s.push(new State(state.index() + 1, state.acc() - numbers[state.index()]));
      s.push(new State(state.index() + 1, state.acc() + numbers[state.index()]));
    }

    return ret;
  }

  public static void main(String... args) throws IOException {

    Path p = Paths.get(System.getProperty("user.dir") + "/data/타겟넘버.txt");
    BufferedReader rd = Files.newBufferedReader(p);

    int testCases = Integer.parseInt(rd.readLine());

    while (testCases > 0) {

      int[] numbers = Arrays.stream(rd.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
      int target = Integer.parseInt(rd.readLine());
      int answer = Integer.parseInt(rd.readLine());
      int ret = solve(numbers, target);
      if (answer != ret) {
        System.out.println(String.format("%d %d", answer, ret));
        return;
      }
      testCases--;
    }

    for (int it = 0; it < TEST_CASES; it++) {
      int[] numbers =
          IntStream.range(0, random.nextInt(MAX_NUMBERS_LENTH - 2) + 2)
              .map(i -> random.nextInt(MAX_NUMBER_VALUE - 1) + 1)
              .toArray();
      int target = random.nextInt(MAX_TARGET_VALUE - 1) + 1;
      System.out.println(solve(numbers, target));
    }
  }
}
