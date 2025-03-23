package com.example.cote.GJM;

import java.io.*;
import java.nio.file.*;
import java.util.*;

public class 남극기지 {

  private static class Point {
    double y;
    double x;

    Point(double y, double x) {
      this.y = y;
      this.x = x;
    }
  }

  private static Point[] points;
  private static double[][] distances;

  private static void calculateDistances(int n) {

    distances = new double[n][n];

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < i; j++) {
        double tmp =
            Math.sqrt(
                Math.pow(points[i].x - points[j].x, 2) + Math.pow(points[i].y - points[j].y, 2));
        distances[i][j] = tmp;
        distances[j][i] = tmp;
      }
      distances[i][i] = -1;
    }
  }

  private static boolean decision(int n, double d) {

    Queue<Integer> q = new LinkedList<>();
    boolean[] visited = new boolean[n];
    int seen = 0;

    Arrays.fill(visited, false);
    visited[0] = true;
    q.offer(0);

    while (!q.isEmpty()) {

      int cur = q.poll();
      seen++;

      for (int i = 0; i < n; i++) {
        if (!visited[i] && distances[cur][i] <= d) {
          visited[i] = true;
          q.offer(i);
        }
      }
    }

    return seen == n;
  }

  private static double optimize(int n) {

    double lo = 0, hi = 987654321;

    for (int i = 0; i < 200; i++) {

      double mid = (lo + hi) / 2;

      if (decision(n, mid)) hi = mid;
      else lo = mid;
    }

    return hi;
  }

  public static void main(String... args) throws IOException {

    Path p = Paths.get(System.getProperty("user.dir") + "/data/남극기지.txt");
    BufferedReader rd = Files.newBufferedReader(p);

    int testCases = Integer.parseInt(rd.readLine());

    while (testCases > 0) {

      int n = Integer.parseInt(rd.readLine());

      points = new Point[n];
      for (int i = 0; i < n; i++) {
        double[] tmp =
            Arrays.stream(rd.readLine().split(" ")).mapToDouble(Double::parseDouble).toArray();
        points[i] = new Point(tmp[0], tmp[1]);
      }

      calculateDistances(n);

      System.out.printf("%.2f\n", optimize(n));

      testCases--;
    }

    return;
  }
}
