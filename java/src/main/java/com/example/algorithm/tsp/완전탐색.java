package com.example.algorithm.tsp;

import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.Random;

class TSP_완전탐색 {

  private static int N = 10;
  private static int TESTCASE = 10;
  private static double[][] W = new double[N][N];
  private static Random random = new Random(43);
  private static double MAX = 987654321;

  private static boolean[] visited = new boolean[N];

  private static void initialize() {
    for (int i = 0; i < N; i++) {
      W[i][i] = MAX;
      for (int j = 0; j < i; j++) {
        Double tmp = Math.abs(random.nextDouble() * random.nextInt()) % 100;
        if (Math.floor(tmp) % 37 < 1) tmp = MAX;

        W[i][j] = tmp;
        W[j][i] = tmp;
      }
    }

    Arrays.fill(visited, false);
  }

  private static double solve(List<Integer> path, double cuurentLength) {

    if (path.size() == N) return cuurentLength + W[path.get(N - 1)][path.get(0)];

    double ret = MAX;

    int cur = path.get(path.size() - 1);

    for (int i = 0; i < N; i++) {
      if (!visited[i]) {
        visited[i] = true;
        path.add(i);
        ret = Math.min(ret, solve(path, cuurentLength + W[cur][i]));
        path.remove(path.size() - 1);
        visited[i] = false;
      }
    }

    return ret;
  }

  private static void print_solution() {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (W[i][j] == MAX) System.out.printf("%8d ", 0);
        else System.out.printf("%3.5f ", W[i][j]);
      }
      System.out.println();
    }

    System.out.println();
  }

  public static void main(String[] args) {

    for (int i = 0; i < TESTCASE; i++) {
      initialize();
      List<Integer> path = new LinkedList<>();
      path.add(0);
      visited[0] = true;
      print_solution();
      System.out.println("minimum : " + solve(path, 0) + "\n\n");
    }
  }
}
