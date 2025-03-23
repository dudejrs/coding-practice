package com.example.cote.PGMRS;

import java.util.*;
import java.util.stream.*;

public class 실습용_로봇 {
  private static final int MAX_COMMANDS_LENGTH = 1000000;

  private static final int[] dy = {1, 0, -1, 0};
  private static final int[] dx = {0, 1, 0, -1};
  private static final String[] commands = {"L", "R", "G", "B"};

  private static final int TEST_CASES = 10;
  private static final Random random = new Random(43);

  private static int[] solve(String command) {

    int x = 0;
    int y = 0;
    int d = 0;

    for (char c : command.toCharArray()) {

      switch (c) {
        case 'R' -> d = (d + 1) % 4;
        case 'L' -> d = (d + 3) % 4;
        case 'G' -> {
          y += dy[d];
          x += dx[d];
        }

        case 'B' -> {
          y -= dy[d];
          x -= dx[d];
        }
      }
    }

    return new int[] {x, y};
  }

  public static void main(String... args) {

    for (int it = 0; it < TEST_CASES; it++) {
      int n = random.nextInt(MAX_COMMANDS_LENGTH - 1) + 1;
      String command =
          IntStream.range(0, n)
              .mapToObj(i -> commands[random.nextInt(4)])
              .collect(Collectors.joining());

      System.out.println(Arrays.toString(solve(command)));
    }
  }
}
