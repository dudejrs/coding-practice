package com.example.cote.HD;

import static java.util.stream.Collectors.*;

import java.io.*;
import java.nio.file.*;
import java.util.*;

public class 강건너기_퍼즐 {

  public static List<String> getStrings(String s) {
    return Arrays.stream(s.split(" ")).skip(1).collect(toList());
  }

  public static List<Set<String>> getCombinations(BufferedReader rd) throws IOException {
    int conbinationsize = Integer.parseInt(rd.readLine());
    List<Set<String>> combinations = new ArrayList<>();
    for (int i = 0; i < conbinationsize; i++) {
      combinations.add(new HashSet<>(getStrings(rd.readLine())));
    }
    return combinations;
  }

  public static void main(String... args) throws IOException {
    Path p = Paths.get(System.getProperty("user.dir") + "/data/강건너기_퍼즐.txt");
    BufferedReader rd = Files.newBufferedReader(p);

    int testCases = Integer.parseInt(rd.readLine());
    while (testCases > 0) {

      int boatSize = Integer.parseInt(rd.readLine());
      List<String> passengers = getStrings(rd.readLine());
      List<String> boatMans = getStrings(rd.readLine());

      List<Set<String>> combinationsNotBeLeftTogether = getCombinations(rd);
      List<Set<String>> combinationsNotEmbarkTogether = getCombinations(rd);

      int answer = Integer.parseInt(rd.readLine());
      System.out.println(answer);

      testCases--;
    }
  }
}
