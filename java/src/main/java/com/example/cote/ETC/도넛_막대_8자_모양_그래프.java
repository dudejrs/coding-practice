package com.example.cote.KK;

import java.io.*;
import java.nio.file.*;
import java.util.*;

public class 도넛_막대_8자_모양_그래프 {

  private static int[] solve(int[][] edges) {

    return new int[] {};
  }

  public static void main(String... args) throws IOException {
    Path p = Paths.get(System.getProperty("user.dir") + "/data/도넛_막대_8자_모양_그래프.txt");
    BufferedReader rd = Files.newBufferedReader(p);

    int testCases = Integer.parseInt(rd.readLine());

    while (testCases > 0) {
      int edgeNum = Integer.parseInt(rd.readLine());

      int[][] edges = new int[edgeNum][2];
      for (int i = 0; i < edgeNum; i++) {
        edges[i] = Arrays.stream(rd.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
      }

      int[] answer = Arrays.stream(rd.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();

      System.out.println("[Solve] :" + Arrays.toString(solve(edges)));
      System.out.println("[Answer] :" + Arrays.toString(answer));

      testCases--;
    }
  }
}
