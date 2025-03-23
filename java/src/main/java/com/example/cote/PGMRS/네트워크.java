package com.example.cote.PGMRS;

import java.io.*;
import java.nio.file.*;
import java.util.*;

public class 네트워크 {
  private static final int NUM_COMPUTERS = 200;

  private static final int TEST_CASES = 10;
  private static final Random random = new Random(43);

  private static void visitAll(int target, int[][] computers, boolean[] isVisited) {
    Stack<Integer> stack = new Stack<>();
    stack.push(target);

    while (!stack.isEmpty()) {
      int cur = stack.pop();

      if (isVisited[cur]) continue;
      isVisited[cur] = true;

      for (int i = 0; i < computers.length; i++) {
        if (computers[cur][i] == 0) continue;
        stack.push(i);
      }
    }
  }

  private static int solve(int numComputer, int[][] computers) {
    boolean[] isVisited = new boolean[numComputer];

    int ret = 0;

    for (int i = 0; i < numComputer; i++) {
      if (isVisited[i]) continue;
      visitAll(i, computers, isVisited);
      ret++;
    }

    return ret;
  }

  public static void main(String... args) throws IOException {

    Path p = Paths.get(System.getProperty("user.dir") + "/data/네트워크.txt");
    BufferedReader reader = Files.newBufferedReader(p);

    int testCases = Integer.parseInt(reader.readLine());

    while (testCases > 0) {
      int numComputer = Integer.parseInt(reader.readLine());
      int[][] computers = new int[numComputer][numComputer];

      for (int i = 0; i < numComputer; i++) {
        computers[i] =
            Arrays.stream(reader.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
      }

      int answer = Integer.parseInt(reader.readLine());
      int ret = solve(numComputer, computers);

      if (answer != ret) {
        System.out.printf("%d %d\n", answer, ret);
        return;
      }
      testCases--;
    }

    for (int it = 0; it < TEST_CASES; it++) {
      int numComputer = random.nextInt(NUM_COMPUTERS - 2) + 2;
      int[][] computers = new int[numComputer][numComputer];

      for (int i = 0; i < numComputer; i++) {
        computers[i][i] = 1;
        for (int j = i + 1; j < numComputer; j++) {
          int connected = random.nextInt() % 43 == 0 ? 1 : 0;
          computers[i][j] = connected;
          computers[j][i] = connected;
        }
      }

      System.out.println(solve(numComputer, computers));
    }
  }
}
