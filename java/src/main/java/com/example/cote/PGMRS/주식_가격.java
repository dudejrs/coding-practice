package com.example.cote.PGMRS;

import java.util.*;
import java.util.stream.*;

public class 주식_가격 {

  private static final int MAX_PRICES_LENGTH = 100000;
  private static final int MAX_PRICE_VALUE = 10000;
  private static final int TEST_CASES = 10;
  private static Random random = new Random(43);

  private static int[] getPrices() {

    int n = random.nextInt(MAX_PRICES_LENGTH - 1) + 1;

    return IntStream.range(0, n).map(i -> random.nextInt(MAX_PRICE_VALUE - 1) + 1).toArray();
  }

  private static int[] solve(int[] prices) {
    int[] result = new int[prices.length];
    Stack<Integer> stack = new Stack<>();

    for (int i = 0; i < prices.length; i++) {

      while (!stack.isEmpty()) {
        int top = stack.peek();
        if (prices[top] <= prices[i]) {
          break;
        }
        int start = stack.pop();
        result[start] = i - start;
      }

      stack.push(i);
    }

    while (!stack.isEmpty()) {
      int start = stack.pop();
      result[start] = prices.length - 1 - start;
    }

    return result;
  }

  public static void main(String... args) {

    int[] sample_prices = new int[] {1, 2, 3, 2, 3};
    System.out.println(Arrays.toString(solve(sample_prices)));

    for (int i = 0; i < TEST_CASES; i++) {
      int[] prices = getPrices();
      System.out.println(Arrays.toString(solve(prices)));
    }
  }
}
