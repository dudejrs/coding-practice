package com.example.cote.SMSNG;

import java.io.*;
import java.nio.file.*;
import java.util.*;

public class 팀_짜기 {

  private static int[] getNumbers(String s) {
    return Arrays.stream(s.split(" ")).mapToInt(Integer::parseInt).toArray();
  }

  private static int getMaxNumberOfMembers(int target, int k, int[] numbers) {
    return (int)
        Arrays.stream(numbers).filter(number -> number >= target && number <= target + k).count();
  }

  public static void main(String args[]) throws Exception {
    Path p = Paths.get(System.getProperty("user.dir") + "/data/팀_짜기.txt");
    BufferedReader rd = Files.newBufferedReader(p);

    Scanner sc = new Scanner(rd);

    int T = Integer.parseInt(sc.nextLine());

    for (int test_case = 1; test_case <= T; test_case++) {

      int[] numbers = getNumbers(sc.nextLine());
      int N = numbers[0];
      int K = numbers[1];

      int[] levels = getNumbers(sc.nextLine());
      Arrays.sort(levels);

      int max = 0;

      for (int number : levels) {
        int count = getMaxNumberOfMembers(number, K, levels);
        max = Math.max(max, count);
      }

      System.out.println(max);
    }
  }
}
