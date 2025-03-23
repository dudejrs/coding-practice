package com.example.cote.PGMRS;

import java.io.*;
import java.nio.file.*;
import java.util.*;

public class 이중_우선순위_큐 {

  private static final int MAX_OPERATIONS = 1000000;

  private static class DoublePriorityQueue {

    private int size = 0;
    private PriorityQueue<Integer> minQueue = new PriorityQueue<>();
    private PriorityQueue<Integer> maxQueue = new PriorityQueue<>((i, j) -> j.compareTo(i));

    public void add(int e) {
      maxQueue.add(e);
      minQueue.add(e);
      size++;
    }

    public void removeMax() {
      if (size == 0) return;
      maxQueue.poll();
      if (size-- == 0) {
        clear();
      }
    }

    public void removeMin() {
      if (size == 0) return;
      minQueue.poll();
      if (size-- == 0) {
        clear();
      }
    }

    private void clear() {
      maxQueue.clear();
      minQueue.clear();
    }

    private int min() {
      if (size == 0) return 0;
      return minQueue.peek();
    }

    private int max() {
      if (size == 0) return 0;
      return maxQueue.peek();
    }
  }

  private static int[] solve(String[] operations) {

    DoublePriorityQueue queue = new DoublePriorityQueue();

    for (String operation : operations) {
      String[] tokens = operation.split(" ");
      String command = tokens[0];
      int value = Integer.parseInt(tokens[1]);

      switch (command) {
        case "I" -> queue.add(value);
        case "D" -> {
          if (value == -1) {
            queue.removeMin();
          }
          if (value == 1) {
            queue.removeMax();
          }
        }
      }
    }

    return new int[] {queue.max(), queue.min()};
  }

  public static void main(String... args) throws IOException {

    Path p = Paths.get(System.getProperty("user.dir") + "/data/이중_우선순위_큐.txt");
    BufferedReader rd = Files.newBufferedReader(p);

    int testCases = Integer.parseInt(rd.readLine());

    while (testCases > 0) {

      int n = Integer.parseInt(rd.readLine());

      String[] operations = new String[n];

      for (int i = 0; i < n; i++) {
        operations[i] = rd.readLine();
      }

      int[] answer = Arrays.stream(rd.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();

      System.out.println("[Solved] : " + Arrays.toString(solve(operations)));
      System.out.println("[Answer] : " + Arrays.toString(answer));

      testCases--;
    }
  }
}
