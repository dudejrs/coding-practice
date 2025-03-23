package com.example.cote.PGMRS;

import static java.util.stream.Collectors.*;

import java.io.*;
import java.nio.file.*;
import java.util.*;

public class 신고_결과_받기 {

  private static final int MAX_ID_LIST_LENGTH = 1000;
  private static final int MAX_REPORTS_LENGTH = 200000;
  private static final int MAX_K = 200;

  private static int[] solve(String[] idList, String[] reports, int k) {

    Map<String, Set<String>> reporter = new HashMap<>();

    for (String id : idList) {
      reporter.put(id, new HashSet<String>());
    }

    Map<String, Integer> counts = new HashMap<>();

    for (String r : reports) {
      String[] tokens = r.split(" ");
      String from = tokens[0];
      String whom = tokens[1];

      Set<String> set = reporter.get(from);
      if (set.contains(whom)) continue;

      set.add(whom);
      int c = counts.getOrDefault(whom, 0);
      counts.put(whom, c + 1);
    }

    Set<String> banned =
        counts.entrySet().stream()
            .filter(e -> e.getValue() >= k)
            .map(e -> e.getKey())
            .collect(toSet());

    return Arrays.stream(idList)
        .mapToInt(id -> (int) reporter.get(id).stream().filter(banned::contains).count())
        .toArray();
  }

  public static void main(String... args) throws IOException {

    Path p = Paths.get(System.getProperty("user.dir") + "/data/신고_결과_받기.txt");
    BufferedReader reader = Files.newBufferedReader(p);

    int testCases = Integer.parseInt(reader.readLine());

    while (testCases-- > 0) {
      String[] idList = reader.readLine().split(" ");
      int numReport = Integer.parseInt(reader.readLine());
      String[] reports = new String[numReport];

      for (int i = 0; i < numReport; i++) {
        reports[i] = reader.readLine();
      }

      int k = Integer.parseInt(reader.readLine());

      int[] answer =
          Arrays.stream(reader.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();

      System.out.println("Answer : " + Arrays.toString(answer));
      System.out.println("Solved : " + Arrays.toString(solve(idList, reports, k)));
    }

    return;
  }
}
