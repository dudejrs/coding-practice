package com.example.algorithm.sort;

import java.util.*;

public class QuickSort {

  private static final int TEST_CASES = 10;
  private static final int N = 10;
  private static final Random random = new Random(43);

  private static int partition(int low, int high, int[] nums) {
    int target = nums[low];
    int cur = low + 1;

    /*
        [low, cur)은 target보다 작은 원소를 가지고 있음
    */
    for (int i = low + 1; i < high; i++) {
      if (nums[i] < target) {
        int tmp = nums[cur];
        nums[cur] = nums[i];
        nums[i] = tmp;
        cur++;
      }
    }

    nums[low] = nums[cur - 1];
    nums[cur - 1] = target;

    return cur;
  }

  private static void quickSort(int low, int high, int[] nums) {
    if (low + 1 < high) {
      int target = partition(low, high, nums);

      quickSort(low, target, nums); // [low, target)
      quickSort(target, high, nums); // [target, high)
    }
  }

  private static int[] solve(int[] nums) {
    quickSort(0, nums.length, nums);

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
