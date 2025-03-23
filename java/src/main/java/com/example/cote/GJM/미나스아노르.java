package com.example.cote.GJM;

import static java.util.stream.Collectors.*;

import java.io.*;
import java.nio.file.*;
import java.util.*;
import java.util.stream.*;

public class 미나스아노르 {

  private static final int N = 100;

  private static final double PI = Math.PI;
  private static final int INF = 987654321;

  private static final double[] x = new double[N];
  private static final double[] y = new double[N];
  private static final double[] r = new double[N];

  private static List<Range> ranges;

  private static class Range {
    Double begin;
    Double end;

    public Range(double begin, double end) {
      this.begin = begin;
      this.end = end;
    }
  }

  private static void convertToRanges(int n) {
    ranges = new LinkedList<Range>();

    for (int i = 0; i < n; i++) {
      double loc = (Math.atan2(y[i], x[i]) + 2 * PI) % (2 * PI);
      double range = 2 * Math.asin(r[i] / 2.0 / 8.0);
      ranges.add(new Range(loc - range, loc + range));
    }
  }

  private static int solveLinear(double begin, double end, int n) {

    int count = 0;
    int i = 0;

    while (begin < end) {
      double maxCover = -1;

      while (i < n && ranges.get(i).begin <= begin) {
        maxCover = Math.max(maxCover, ranges.get(i).end);
        i++;
      }

      if (maxCover <= begin) return INF;

      begin = maxCover;
      count++;
    }

    return count;
  }

  private static int solveCircular(int n) {
    int ret = INF;

    Collections.sort(
        ranges,
        (Range r1, Range r2) -> {
          if (r1.begin == r2.begin) return r1.end.compareTo(r2.end);
          return r1.begin.compareTo(r2.begin);
        });

    for (Range r : ranges) {
      System.out.println(r.begin + " , " + r.end);
    }

    for (Range r : ranges) {
      if (r.begin <= 0 || r.end >= 2 * PI) {
        double begin = r.end % (2 * PI);
        double end = (r.begin + 2 * PI) % (2 * PI);
        ret = Math.min(ret, 1 + solveLinear(begin, end, n));
      }
    }

    return ret;
  }

  public static String solve(int n) {

    convertToRanges(n);

    int ans = solveCircular(n);

    return (ans >= INF) ? "IMPOSSIBLE" : "" + ans;
  }

  public static void main(String[] args) throws IOException {

    Path p = Paths.get(System.getProperty("user.dir") + "/data/미나스아노르.txt");
    BufferedReader reader = Files.newBufferedReader(p);

    int test_cases = Integer.parseInt(reader.readLine());

    while (test_cases > 0) {

      int n = Integer.parseInt(reader.readLine());

      for (int i = 0; i < n; i++) {
        List<Double> v =
            Arrays.stream(reader.readLine().split(" ")).map(Double::parseDouble).collect(toList());

        x[i] = v.get(0);
        y[i] = v.get(1);
        r[i] = v.get(2);
      }

      System.out.println(solve(n));

      test_cases--;
    }
  }
}
