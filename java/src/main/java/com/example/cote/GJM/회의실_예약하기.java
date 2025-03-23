package com.example.cote.GJM;

import java.util.Random;
import java.util.TreeSet;

public class 회의실_예약하기 {

  private static final int N = 30;
  private static int[] begin = new int[N];
  private static int[] end = new int[N];
  private static Random rd = new Random(43);

  private static class Entry {
    private int start;
    private int finish;

    public Entry(int start, int finish) {
      this.start = start;
      this.finish = finish;
    }
  }

  {
    initialize();
  }

  private static void initialize() {

    for (int i = 0; i < N; i++) {
      begin[i] = rd.nextInt(1440);
      end[i] = Math.min(begin[i] + (int) Math.floor(rd.nextGaussian() * 60), 1440);
    }
  }

  private static int solve() {

    TreeSet<Entry> set = new TreeSet<>((Entry a, Entry b) -> a.finish - b.finish);

    for (int i = 0; i < N; i++) {
      set.add(new Entry(begin[i], end[i]));
    }

    int count = 0;
    int earliest = 0;

    for (Entry a : set) {
      if (earliest <= a.start) {
        earliest = a.finish;
        count++;
      }
    }

    return count;
  }

  public static void main(String[] args) {
    initialize();
    System.out.println(solve());
  }
}
