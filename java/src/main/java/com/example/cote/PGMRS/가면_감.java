package com.example.cote.PGMRS;

import static java.util.stream.Collectors.*;

import java.io.*;
import java.nio.file.*;
import java.util.*;
import java.util.stream.*;

public class 가면_감 {

  private static int solve(List<List<Integer>> replies) {

    return 0;
  }

  public static void main(String... args) throws IOException {

    Path p = Paths.get(System.getProperty("user.dir") + "/data/가면_감.txt");
    BufferedReader rd = Files.newBufferedReader(p);

    int testCases = Integer.parseInt(rd.readLine());

    while (testCases > 0) {

      int n = Integer.parseInt(rd.readLine());

      List<List<Integer>> replies = new LinkedList<List<Integer>>();

      for (int i = 0; i <= n; i++) {
        replies.add(
            Arrays.stream(rd.readLine().split(" ")).map(Integer::parseInt).collect(toList()));
      }

      System.out.println(solve(replies));

      testCases--;
    }
  }
}
