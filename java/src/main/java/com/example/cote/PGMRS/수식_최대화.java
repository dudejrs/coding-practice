package com.example.cote.PGMRS;

import java.io.*;
import java.nio.file.*;
import java.util.*;

public class 수식_최대화 {

  private static final String[][] operatorPriories = {
    {"+", "-", "*"},
    {"+", "*", "-"},
    {"*", "+", "-"},
    {"*", "-", "+"},
    {"-", "+", "*"},
    {"-", "*", "+"}
  };

  private static long calculate(String operator, long left, long right) {
    switch (operator) {
      case "+":
        return left + right;
      case "-":
        return left - right;
      case "*":
        return left * right;
      default:
        return 0;
    }
  }

  private static long calculate(List<String> tokens, String[] operatorPriority) {

    for (String operator : operatorPriority)
      for (int i = 0; i < tokens.size(); i++)
        if (tokens.get(i).equals(operator)) {
          long left = Long.parseLong(tokens.get(i - 1));
          long right = Long.parseLong(tokens.get(i + 1));
          long result = calculate(operator, left, right);

          tokens.remove(i - 1);
          tokens.remove(i - 1);
          tokens.remove(i - 1);
          tokens.add(i - 1, Long.toString(result));
          i -= 2;
        }
    return Long.parseLong(tokens.get(0));
  }

  private static long solve(String expression) {

    StringTokenizer tokenizer = new StringTokenizer(expression, "+-*", true);
    List<String> tokens = new ArrayList<>();
    while (tokenizer.hasMoreTokens()) tokens.add(tokenizer.nextToken());

    long ret = 0;
    for (String[] operatorPriority : operatorPriories)
      ret = Math.max(ret, Math.abs(calculate(new ArrayList<>(tokens), operatorPriority)));

    return ret;
  }

  public static void main(String... args) throws IOException {

    Path p = Paths.get(System.getProperty("user.dir") + "/data/수식_최대화.txt");
    BufferedReader rd = Files.newBufferedReader(p);

    int testCases = Integer.parseInt(rd.readLine());

    while (testCases > 0) {
      System.out.println(solve(rd.readLine()));
      testCases--;
    }
  }
}
