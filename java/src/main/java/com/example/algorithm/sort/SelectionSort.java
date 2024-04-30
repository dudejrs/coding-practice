package com.example.algorithm.sort;

import java.util.*;

public class SelectionSort {

	private static final int TEST_CASES = 10;
	private static final int N = 10;
	private static final Random random = new Random(43);
	
	private static int[] solve(int[] nums) {

		for (int i = nums.length - 1; i >= 0; i--) {
			int cur = i;

			for (int j = 0; j < i; j++) {
				if (nums[cur] < nums[j]) {
					cur = j;
				}
			}
			int tmp = nums[i];
			nums[i] = nums[cur];
			nums[cur] = tmp;
		}

		return nums;
	}

	public static void main(String... args) {

		for (int it = 0; it < TEST_CASES; it++) {
			int n = random.nextInt(N - 1) + 1;
			int[] nums = new int [n];
			for (int i = 0; i < n; i++) {
				nums[i] = random.nextInt(5 * n);
			}
			System.out.println(Arrays.toString(solve(nums)));
		}
	}
}