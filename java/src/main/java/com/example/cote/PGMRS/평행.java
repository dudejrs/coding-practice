package com.example.cote.PGMRS;

import java.io.*;
import java.nio.file.*;
import java.util.*;

public class 평행 {

  private static final int MAX_DOTS_NUMBER = 100;
  private static final int DOTS_LENGTH = 4;

  private static double getSlope(int[] a, int[] b) {
    return (double) (a[1] - b[1]) / (a[0] - b[0]);
  }

  private static final int solve(int[][] dots) {

    Set<Double> slopes = new HashSet<>();

    for (int i = 0; i < DOTS_LENGTH; i++) {
      for (int j = i + 1; j < DOTS_LENGTH; j++) {
        double slope = getSlope(dots[i], dots[j]);

        if (slopes.contains(slope)) return 1;
        slopes.add(slope);
      }
    }

    return 0;
  }

  public static void main(String... args) throws IOException {

    Path p = Paths.get(System.getProperty("user.dir") + "/data/평행.txt");
    BufferedReader fd = Files.newBufferedReader(p);

    int testCases = Integer.parseInt(fd.readLine());

    while (testCases > 0) {

      int[][] dots = new int[DOTS_LENGTH][2];

      for (int i = 0; i < DOTS_LENGTH; i++) {
        dots[i] = Arrays.stream(fd.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
      }

      System.out.println(solve(dots));

      testCases--;
    }

    return;
  }
}
