package com.example.cote.PGMRS;

import java.io.*;
import java.nio.file.*;
import java.util.*;

public class 완주하지_못한_선수 {

  private static String solve(String[] participant, String[] completion) {

    Map<String, Integer> count = new HashMap<>();

    for (String name : participant) {
      int cur = count.getOrDefault(name, 0);
      count.put(name, cur + 1);
    }

    for (String name : completion)
      if (count.keySet().contains(name)) {
        int cur = count.get(name) - 1;
        if (cur > 0) count.put(name, cur);
        else count.remove(name);
      }

    return count.keySet().iterator().next();
  }

  public static void main(String... args) throws IOException {

    Path p = Paths.get(System.getProperty("user.dir") + "/data/완주하지_못한_선수.txt");
    BufferedReader rd = Files.newBufferedReader(p);

    int testCases = Integer.parseInt(rd.readLine());

    while (testCases > 0) {

      String[] participant = rd.readLine().split(" ");
      String[] completion = rd.readLine().split(" ");
      System.out.println(solve(participant, completion));

      testCases--;
    }
  }
}
