package com.example.cote.PGMRS;

import java.io.*;
import java.nio.file.*;
import java.util.*;

public class 기능_개발 {

  private static final int MAX_TASK_LENGTH = 100;
  private static final int MAX_PROGRESS = 100;
  private static final int MAX_SPEED = 100;

  private static int[] getInts(String s) {
    return Arrays.stream(s.split(" ")).mapToInt(Integer::parseInt).toArray();
  }

  private static int[] solve(int[] progresses, int[] speeds) {

    List<Integer> ret = new LinkedList<>();
    Queue<Integer> queue = new LinkedList<>();

    for (int i = 0; i < progresses.length; i++) {
      queue.add(i);
    }

    int day = 0;
    int count = 0;

    while (!queue.isEmpty()) {
      int i = queue.poll();
      int completed_day = (int) Math.ceil((double) (100 - progresses[i]) / speeds[i]);

      if (completed_day > day) {
        if (day != 0) {
          ret.add(count);
          count = 0;
        }
        day = completed_day;
      }

      count++;
    }

    ret.add(count);

    return ret.stream().mapToInt(Integer::intValue).toArray();
  }

  public static void main(String... args) throws IOException {

    Path p = Paths.get(System.getProperty("user.dir") + "/data/기능_개발.txt");
    BufferedReader rd = Files.newBufferedReader(p);

    int testCases = Integer.parseInt(rd.readLine());

    while (testCases > 0) {
      int[] progresses = getInts(rd.readLine());
      int[] speeds = getInts(rd.readLine());

      int[] answer = getInts(rd.readLine());

      System.out.println("[Solved]");
      System.out.println(Arrays.toString(solve(progresses, speeds)));
      System.out.println("[Answer]");
      System.out.println(Arrays.toString(answer));
      System.out.println();

      testCases--;
    }
  }
}
