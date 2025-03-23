package com.example.cote.PGMRS;

import java.util.*;
import java.util.stream.*;

public class 스킬_트리 {

  private static final int TEST_CASES = 10;
  private static final Random random = new Random(43);

  private static String generate(int limit) {
    int n = Math.min(random.nextInt(26 - 1) + 1, limit);
    Set<Character> set = new HashSet<>();

    while (set.size() < n) {
      set.add((char) (random.nextInt('Z' - 'A') + 'A'));
    }

    List<Character> chars = new ArrayList(set);

    Collections.shuffle(chars);

    return chars.stream().map(String::valueOf).collect(Collectors.joining());
  }

  private static int solve(String skill, List<String> skillTrees) {
    return (int)
        skillTrees.stream()
            .map(s -> s.replaceAll(String.format("[^%s]", skill), ""))
            .filter(skill::startsWith)
            .count();
  }

  public static void main(String... args) {

    for (int it = 0; it < TEST_CASES; it++) {
      String skill = generate(5);
      List<String> skillTrees =
          IntStream.range(1, random.nextInt(20))
              .mapToObj(i -> generate(26))
              .collect(Collectors.toList());
      System.out.println(solve(skill, skillTrees));
    }
  }
}
