package com.example.algorithm.sort;

import java.util.*;

public class BubbleSort {

  private static final int TEST_CASES = 10;
  private static final int N = 10000;
  private static final Random random = new Random(43);

  private static int[] solve(int[] nums) {

    for (int i = 0; i < nums.length; i++) {
      for (int j = 1; j < nums.length; j++) {
        if (nums[j] < nums[j - 1]) {
          int tmp = nums[j];
          nums[j] = nums[j - 1];
          nums[j - 1] = tmp;
        }
      }
    }

    return nums;
  }

  public static void main(String... args) {

    for (int it = 0; it < TEST_CASES; it++) {
      int n = random.nextInt(N - 1) + 1;
      int[] nums = new int[n];
      for (int i = 0; i < n; i++) {
        nums[i] = random.nextInt(5 * n);
      }
      System.out.println(Arrays.toString(solve(nums)));
    }
  }
}
