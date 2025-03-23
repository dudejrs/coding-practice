package com.example.cote.PGMRS;

import java.io.*;
import java.nio.file.*;
import java.util.*;

public class 모음사전 {

  private static final char[] CHARS = {'A', 'E', 'I', 'O', 'U'};
  private static final int N = 5;

  private static int generate(String curString, String target) {

    if (curString.length() == N) return 0;

    int ret = 0;

    for (int i = 0; i < 5; i++) {
      if ((curString + CHARS[i]).equals(target)) return ret + 1;
      if ((curString + CHARS[i]).compareTo(target) > 0) continue;
      ret += generate(curString + CHARS[i], target) + 1;
    }
    if (curString.length() == 1) System.out.println(curString + " : " + ret);

    return ret;
  }

  private static final int solve(String target) {

    return generate("", target);
  }

  public static void main(String... args) throws IOException {

    Path p = Paths.get(System.getProperty("user.dir") + "/data/모음사전.txt");
    BufferedReader rd = Files.newBufferedReader(p);

    int testCases = Integer.parseInt(rd.readLine());

    while (testCases > 0) {

      String target = rd.readLine();

      System.out.println(solve(target));

      testCases--;
    }
  }
}
