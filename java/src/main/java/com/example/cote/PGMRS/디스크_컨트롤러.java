package com.example.cote.PGMRS;

import java.util.*;

public class 디스크_컨트롤러 {

  private static final int TEST_CASES = 10;
  private static final Random random = new Random(43);

  private static final int MAX_JOBS_LENGTH = 500;
  private static final int MAX_JOBS_REQUEST_TIME = 1000;
  private static final int MAX_JOBS_DURATION = 1000;

  private static class Job {
    public final int requestTime;
    public final int duration;

    private Job(int requestTime, int duration) {
      this.requestTime = requestTime;
      this.duration = duration;
    }
  }

  private static int solve(int[][] rawJobs) {

    Job[] jobs = Arrays.stream(rawJobs).map(j -> new Job(j[0], j[1])).toArray(Job[]::new);
    Arrays.sort(jobs, Comparator.comparingInt(job -> job.requestTime));
    Queue<Job> q = new LinkedList<>(Arrays.asList(jobs));

    PriorityQueue<Job> pq = new PriorityQueue<>(Comparator.comparingInt(job -> job.duration));

    int curTime = 0;
    int sum = 0;

    while (!q.isEmpty() || !pq.isEmpty()) {

      while (!q.isEmpty() && q.peek().requestTime <= curTime) {
        pq.add(q.poll());
      }

      if (pq.isEmpty()) {
        curTime = q.peek().requestTime;
        continue;
      }

      Job job = pq.poll();
      sum += curTime - job.requestTime + job.duration;
      curTime += job.duration;
    }

    return sum / jobs.length;
  }

  public static void main(String... args) {

    for (int testCases = 0; testCases < TEST_CASES; testCases++) {
      int n = random.nextInt(MAX_JOBS_LENGTH - 1) + 1;
      int[][] jobs = new int[n][2];
      for (int i = 0; i < n; i++) {
        jobs[i][0] = random.nextInt(MAX_JOBS_REQUEST_TIME);
        jobs[i][1] = random.nextInt(MAX_JOBS_DURATION);
      }

      System.out.println(solve(jobs));
    }
  }
}
