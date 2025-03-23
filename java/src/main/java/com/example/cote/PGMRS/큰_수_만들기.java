package com.example.cote.PGMRS;

import static java.util.stream.Collectors.*;

import java.io.*;
import java.nio.file.*;
import java.util.*;
import java.util.stream.*;

public class 큰_수_만들기 {

  private static final int MAX_NUMBER_LENGTH = 1000000;

  private static final int TEST_CASES = 10;
  private static final Random random = new Random(43);

  private static String solve(String number, int k) {
    Stack<Character> stack = new Stack<>();

    for (char c : number.toCharArray()) {
      while (k > 0 && !stack.isEmpty() && c > stack.peek()) {
        stack.pop();
        k--;
      }
      stack.push(c);
    }

    while (k-- > 0) {
      stack.pop();
    }

    return stack.stream().map(String::valueOf).collect(joining());
  }

  public static void main(String... args) throws IOException {

    Path p = Paths.get(System.getProperty("user.dir") + "/data/큰_수_만들기.txt");
    BufferedReader reader = Files.newBufferedReader(p);

    int testCases = Integer.parseInt(reader.readLine());

    while (testCases > 0) {
      String number = reader.readLine();
      int k = Integer.parseInt(reader.readLine());
      String answer = reader.readLine();

      String ret = solve(number, k);

      if (!ret.equals(answer)) {
        System.out.printf("%s %s \n", answer, ret);
        return;
      }

      testCases--;
    }

    for (int it = 0; it < TEST_CASES; it++) {
      int n = random.nextInt(MAX_NUMBER_LENGTH - 2) + 2;

      String number =
          IntStream.range(0, n)
              .mapToObj(i -> Integer.toString(random.nextInt(10)))
              .collect(joining(""));

      int k = random.nextInt(n);

      System.out.println(solve(number, k));
    }
  }
}
