package com.example.algorithm.sort;

import java.util.*;

public class InsertionSort {

  private static final int TEST_CASES = 10;
  private static final int N = 10000;
  private static final Random random = new Random(43);

  private static int[] solve(int[] nums) {

    for (int i = 0; i < nums.length; i++) {
      int j = i;

      while (j > 0 && nums[j - 1] > nums[j]) {
        int tmp = nums[j - 1];
        nums[j - 1] = nums[j];
        nums[j] = tmp;
        j--;
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
