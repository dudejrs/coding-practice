package com.example.cote.KK;

import java.io.*;
import java.nio.file.*;
import java.util.*;
import java.util.function.*;
import java.util.stream.*;

public class 카카오_선물 {

  private static Map<String, Integer> map(String[] friends) {
    Map<String, Integer> nameToIdx = new HashMap<>();
    for (String friend : friends) {
      nameToIdx.put(friend, nameToIdx.size());
    }
    return nameToIdx;
  }

  private static int[][] getCounts(Map<String, Integer> nameToIdx, String[] gifts) {
    int n = nameToIdx.size();
    int counts[][] = new int[n][n];

    for (String gift : gifts) {
      String[] tokens = gift.split(" ");
      int giver = nameToIdx.get(tokens[0]);
      int taker = nameToIdx.get(tokens[1]);
      counts[giver][taker] += 1;
    }
    return counts;
  }

  private static int[] getIndex(int[][] counts) {
    int n = counts.length;
    int[] index = new int[n];

    for (int i = 0; i < n; i++) {
      int gives = 0;
      int takes = 0;

      for (int j = 0; j < n; j++) {
        gives += counts[i][j];
      }

      for (int j = 0; j < n; j++) {
        takes += counts[j][i];
      }

      index[i] = gives - takes;
    }

    return index;
  }

  private static int[] getExpected(int[][] counts, int[] index) {
    int n = counts.length;
    int[] expected = new int[n];

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (i == j) continue;
        if (counts[i][j] > counts[j][i]) {
          expected[i] += 1;
        } else if (counts[i][j] == counts[j][i] && index[i] > index[j]) {
          expected[i] += 1;
        }
      }
    }

    return expected;
  }

  public static int solution(String[] friends, String[] gifts) {

    int answer = 0;
    int n = friends.length;
    Map<String, Integer> nameToIdx = map(friends);

    int[][] counts = getCounts(nameToIdx, gifts);
    int[] index = getIndex(counts);
    int[] expected = getExpected(counts, index);

    return Arrays.stream(expected).max().getAsInt();
  }

  public static void main(String... args) throws IOException {

    Path p = Paths.get(System.getProperty("user.dir") + "/data/카카오_선물.txt");
    BufferedReader rd = Files.newBufferedReader(p);

    int testCases = Integer.parseInt(rd.readLine());

    while (testCases > 0) {

      String[] friends = rd.readLine().split(" ");
      int numGift = Integer.parseInt(rd.readLine());

      String[] gifts = new String[numGift];

      for (int i = 0; i < numGift; i++) {
        gifts[i] = rd.readLine();
      }
      int answer = Integer.parseInt(rd.readLine());

      System.out.println(solution(friends, gifts) + " " + answer);

      testCases--;
    }
  }
}
