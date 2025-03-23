package com.example.cote.KK;

import java.io.*;
import java.nio.file.*;
import java.util.*;

public class 카드_동전_게임 {

  private static final int CARDS_MAX_LENGTH = 1000;

  private static boolean countMatched(
      List<Integer> myCards, List<Integer> helpers, int stage, int n) {
    Set<Integer> totals = new TreeSet(myCards);
    totals.addAll(helpers);

    int count = 0;

    for (int number : totals) {
      if (totals.contains(n + 1 - number)) {
        count++;
      }
    }

    return count / 2 >= stage;
  }

  private static int stage(
      List<Integer> myCards, Queue<Integer> drawOrigin, int coins, int stage, int n) {

    if (drawOrigin.isEmpty()) {
      return stage;
    }

    int ret = stage;
    Queue<Integer> draw = new LinkedList(drawOrigin);

    LinkedList<Integer> stagedCard = new LinkedList<>();
    stagedCard.add(draw.poll());
    stagedCard.add(draw.poll());

    if (countMatched(myCards, Collections.emptyList(), stage, n)) {
      ret = Math.max(ret, stage(myCards, draw, coins, stage + 1, n));
    }

    if (countMatched(myCards, List.of(stagedCard.get(0)), stage, n) && coins >= 1) {
      myCards.add(stagedCard.get(0));
      ret = Math.max(ret, stage(myCards, draw, coins - 1, stage + 1, n));
      myCards.remove(stagedCard.get(0));
    }

    if (countMatched(myCards, List.of(stagedCard.get(1)), stage, n) && coins >= 1) {
      myCards.add(stagedCard.get(1));
      ret = Math.max(ret, stage(myCards, draw, coins - 1, stage + 1, n));
      myCards.remove(stagedCard.get(1));
    }

    if (countMatched(myCards, stagedCard, stage, n) && coins >= 2) {
      myCards.addAll(stagedCard);
      ret = Math.max(ret, stage(myCards, draw, coins - 2, stage + 1, n));
      myCards.removeAll(stagedCard);
    }

    return ret;
  }

  private static int solution(int coin, int[] cards) {

    List<Integer> myCards = new LinkedList<>();
    Queue<Integer> draw = new LinkedList<>();

    for (int i = 0; i < cards.length / 3; i++) {
      myCards.add(cards[i]);
    }
    for (int i = cards.length / 3; i < cards.length; i++) {
      draw.add(cards[i]);
    }

    return stage(myCards, draw, coin, 1, cards.length);
  }

  public static void main(String... args) throws IOException {

    Path p = Paths.get(System.getProperty("user.dir") + "/data/카드_동전_게임.txt");
    BufferedReader rd = Files.newBufferedReader(p);

    int testCases = Integer.parseInt(rd.readLine());

    while (testCases > 0) {
      int coins = Integer.parseInt(rd.readLine());
      int[] cards = Arrays.stream(rd.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();

      int answer = Integer.parseInt(rd.readLine());

      System.out.println(solution(coins, cards) + " " + answer);

      testCases--;
    }
  }
}
