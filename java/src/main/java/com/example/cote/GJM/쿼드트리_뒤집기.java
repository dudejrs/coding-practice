package com.example.cote.GJM;

import java.io.*;
import java.nio.file.*;
import java.util.*;

public class 쿼드트리_뒤집기 {

  private static String[] divideIntoTokens(String s) {

    String[] tokens = new String[4];
    int cur = 0;

    for (int i = 0; i < 3; i++) {
      int tmp = cur;
      int length = 1;
      while (tmp < cur + length && tmp < s.length()) {
        if (s.charAt(tmp) == 'x') {
          length += 4;
        }
        tmp++;
      }
      tokens[i] = s.substring(cur, cur + length);
      cur += length;
    }

    tokens[3] = s.substring(cur);

    return tokens;
  }

  private static String reverse(String s) {

    StringBuilder builder = new StringBuilder();

    if (s.charAt(0) != 'x') {
      return s;
    }

    String[] tokens = divideIntoTokens(s.substring(1));

    builder.append("x");
    builder.append(reverse(tokens[2]));
    builder.append(reverse(tokens[3]));
    builder.append(reverse(tokens[0]));
    builder.append(reverse(tokens[1]));

    return builder.toString();
  }

  public static void main(String... args) throws IOException {
    Path p = Paths.get(System.getProperty("user.dir") + "/data/쿼드트리_뒤집기.txt");
    BufferedReader rd = Files.newBufferedReader(p);

    int testCases = Integer.parseInt(rd.readLine());

    while (testCases > 0) {

      String s = rd.readLine();

      System.out.println(reverse(s));

      testCases--;
    }
  }
}
