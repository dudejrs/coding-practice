package com.example.cote.PGMRS;

import java.io.*;
import java.nio.file.*;
import java.util.*;

public class 주차_요금_계산 {

  private static final int MAX_BASIC_TIME = 1439;
  private static final int MAX_BASIC_FEE = 100000;
  private static final int MAX_UNIT_TIME = 1439;
  private static final int MAX_UNIT_FEE = 10000;
  private static final int MAX_RECORDS_LENGTH = 1000;

  private static record Fee(int baseTime, int baseFee, int unitTime, int unitFee) {
    public int cost(int time) {
      int ret = baseFee;
      time -= baseTime;

      while (time > 0) {
        ret += unitFee;
        time -= unitTime;
      }

      return ret;
    }
  }

  private static class Car {

    public String number;
    public Fee fee;
    private int inTime = -1;
    private int totalTime = 0;

    Car(String number, Fee fee) {
      this.number = number;
      this.fee = fee;
    }

    public void in(int time) {
      this.inTime = time;
    }

    public void out(int time) {
      if (this.inTime == -1) return;
      this.totalTime += time - inTime;
      this.inTime = -1;
    }

    public int cost() {
      return fee.cost(this.totalTime);
    }
  }

  private static int parseTime(String time) {
    int hour = Integer.parseInt(time.substring(0, 2));
    int minute = Integer.parseInt(time.substring(3));

    return hour * 60 + minute;
  }

  private static int[] solve(int[] fees, String[] records) {
    Fee fee = new Fee(fees[0], fees[1], fees[2], fees[3]);

    Map<String, Car> cars = new HashMap<>();

    for (String record : records) {
      String[] tokens = record.split(" ");
      int time = parseTime(tokens[0]);
      String number = tokens[1];
      boolean isIn = tokens[2].equals("IN");

      cars.putIfAbsent(number, new Car(number, fee));
      Car car = cars.get(number);

      switch (tokens[2]) {
        case "IN" -> car.in(time);
        case "OUT" -> car.out(time);
        default -> {}
      }
    }

    int endTime = parseTime("23:59");
    System.out.println("endTime : " + endTime);

    for (Car car : cars.values()) {
      car.out(endTime);
    }

    return cars.values().stream()
        .sorted(Comparator.comparing(c -> c.number))
        .mapToInt(Car::cost)
        .toArray();
  }

  public static void main(String... args) throws IOException {

    Path p = Paths.get(System.getProperty("user.dir") + "/data/주차_요금_계산.txt");
    BufferedReader reader = Files.newBufferedReader(p);

    int testCases = Integer.parseInt(reader.readLine());

    while (testCases-- > 0) {
      int[] fees =
          Arrays.stream(reader.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();

      int numRecords = Integer.parseInt(reader.readLine());

      String[] records = new String[numRecords];

      for (int i = 0; i < numRecords; i++) {
        records[i] = reader.readLine();
      }

      int[] answer =
          Arrays.stream(reader.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();

      int[] ret = solve(fees, records);

      System.out.printf("%s %s\n", Arrays.toString(answer), Arrays.toString(ret));
    }
  }
}
