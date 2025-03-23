package com.example.cote.PGMRS;

import java.util.*;
import java.util.function.*;

public class 순위_검색 {

  private static final int TEST_CASES = 10;
  private static final int INFO_SIZE = 50000;
  private static final int QUERY_SIZE = 100000;
  private static final int MAX_SCORE = 100000;
  private static final Random rd = new Random(43);

  private static final String[] languages = {"cpp", "java", "python"};
  private static final String[] positions = {"backend", "frontend"};
  private static final String[] carriers = {"junior", "sinior"};
  private static final String[] soulfoods = {"chicken", "pizza"};
  private static final String[][] categories = {languages, positions, carriers, soulfoods};

  private static String[] initializeInfo() {

    int info_size = rd.nextInt(INFO_SIZE);
    String[] ret = new String[info_size];

    for (int it = 0; it < info_size; it++) {

      String[] t = new String[5];

      for (int i = 0; i < 4; i++) {
        int tmp = rd.nextInt(categories[i].length);
        t[i] = categories[i][tmp];
      }
      t[4] = Integer.toString(rd.nextInt(MAX_SCORE));
      ret[it] = String.join(" ", t);
    }

    return ret;
  }

  private static String[] initializeQuery() {

    int query_size = rd.nextInt(QUERY_SIZE);
    String[] ret = new String[query_size];

    for (int it = 0; it < query_size; it++) {

      String[] t = new String[4];

      for (int i = 0; i < 4; i++) {
        int tmp = rd.nextInt(categories[i].length);
        if (rd.nextInt() % 7 == 0) {
          t[i] = "-";
          continue;
        }
        t[i] = categories[i][tmp];
      }
      ret[it] = String.join(" and ", t) + " " + Integer.toString(rd.nextInt(MAX_SCORE));
    }

    return ret;
  }

  private static void forEachKey(
      int index, String prefix, String[] tokens, Consumer<String> action) {
    if (index == tokens.length - 1) {
      action.accept(prefix);
      return;
    }

    forEachKey(index + 1, prefix + tokens[index], tokens, action);
    forEachKey(index + 1, prefix + "-", tokens, action);
  }

  private static Map<String, List<Integer>> buildScoresMap(String[] info) {
    Map<String, List<Integer>> scoresMap = new HashMap<>();

    for (String s : info) {
      String[] tokens = s.split(" ");
      int score = Integer.parseInt(tokens[tokens.length - 1]);
      forEachKey(
          0,
          "",
          tokens,
          key -> {
            scoresMap.putIfAbsent(key, new ArrayList<>());
            scoresMap.get(key).add(score);
          });
    }

    for (List<Integer> list : scoresMap.values()) {
      Collections.sort(list);
    }

    return scoresMap;
  }

  private static int binarySearch(int score, List<Integer> scores) {
    int start = 0;
    int end = scores.size() - 1;

    while (end > start) {
      int mid = (start + end) / 2;

      if (scores.get(mid) >= score) {
        end = mid;
      } else {
        start = mid + 1;
      }
    }

    if (scores.get(start) < score) {
      return scores.size();
    }

    return start;
  }

  private static int count(String query, Map<String, List<Integer>> scoresMap) {
    String[] tokens = query.split(" (and )?");
    String key = String.join("", Arrays.copyOf(tokens, tokens.length - 1));

    if (!scoresMap.containsKey(key)) return 0;

    List<Integer> scores = scoresMap.get(key);
    int score = Integer.parseInt(tokens[tokens.length - 1]);

    return scores.size() - binarySearch(score, scoresMap.get(key));
  }

  private static int[] solve(String[] info, String[] query) {

    Map<String, List<Integer>> scoresMap = buildScoresMap(info);

    int[] ret = new int[query.length];

    for (int i = 0; i < ret.length; i++) {
      ret[i] = count(query[i], scoresMap);
    }

    return ret;
  }

  public static void main(String... args) {
    for (int it = 0; it < TEST_CASES; it++) {
      String[] info = initializeInfo();
      String[] query = initializeQuery();

      System.out.println(Arrays.toString(solve(info, query)));
    }
  }
}
