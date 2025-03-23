package com.example.cote.PGMRS;

import java.io.*;
import java.nio.file.*;
import java.util.*;

public class 순위 {

  private static int countForward(int cur, boolean[][] graph, boolean[] visited) {
    int count = 1;
    visited[cur] = true;

    for (int i = 0; i < graph.length; i++) {
      if (!graph[cur][i] || visited[i]) continue;
      count += countForward(i, graph, visited);
    }

    return count;
  }

  private static int countBackward(int cur, boolean[][] graph, boolean[] visited) {
    int count = 1;
    visited[cur] = true;

    for (int i = 0; i < graph.length; i++) {
      if (!graph[i][cur] || visited[i]) continue;
      count += countBackward(i, graph, visited);
    }

    return count;
  }

  private static int solve(int n, int[][] edges) {

    boolean[][] graph = new boolean[n][n];

    for (int[] edge : edges) {
      graph[edge[0] - 1][edge[1] - 1] = true;
    }

    int count = 0;

    for (int i = 0; i < n; i++) {

      int wins = countForward(i, graph, new boolean[n]) - 1;
      int loses = countBackward(i, graph, new boolean[n]) - 1;

      if (wins + loses == n - 1) {
        count++;
      }
    }

    return count;
  }

  public static void main(String... args) throws IOException {

    Path p = Paths.get(System.getProperty("user.dir") + "/data/순위.txt");
    BufferedReader rd = Files.newBufferedReader(p);

    int testCases = Integer.parseInt(rd.readLine());

    while (testCases > 0) {

      int n = Integer.parseInt(rd.readLine());
      int numEdges = Integer.parseInt(rd.readLine());
      int[][] edges = new int[numEdges][2];

      for (int i = 0; i < numEdges; i++) {
        edges[i] = Arrays.stream(rd.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
      }

      int answer = Integer.parseInt(rd.readLine());

      System.out.println(solve(n, edges) + " " + answer);

      testCases--;
    }
  }
}
