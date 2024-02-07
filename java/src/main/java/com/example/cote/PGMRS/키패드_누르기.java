package com.example.cote.PGMRS;

import java.util.*;
import java.io.*;
import java.nio.file.*;
import static java.util.stream.Collectors.*;

public class 키패드_누르기 {

	public static class Hand {
		private final int baseX;
		public final String hand;
		public final float preference;
		private int x;
		private int y;

		public Hand(String hand, boolean isPreferred, int x) {
			this.hand = hand;
			this.baseX = x;
			this.preference = isPreferred ? 0.5f : 0;
			this.x = x;
			this.y = 3;
		}

		public float distance(int x, int y) {
			if (x == baseX) return 0;
			int distance = Math.abs(x - this.x) + Math.abs(y - this.y);
			return distance - preference;
		}

		public Hand move(int x, int y) {
			this.x = x;
			this.y = y;

			return this;
		}
	}

	private static int getX(int number) {
		if (number == 0) return 1;
		return (number - 1) % 3;
	}

	private static int getY(int number) {
		if (number == 0) return 3;
		return (number - 1) / 3;
	}

	private static String press (int number, Hand right, Hand left) {
		int x = getX(number);
		int y = getY(number);

		float rDistance = right.distance(x, y);
		float lDistance = left.distance(x, y);

		if (lDistance < rDistance) {
			return left.move(x,y).hand;
		}
		return right.move(x,y).hand;
	}

	private static String solve(int[] numbers, String hand) {
		Hand right = new Hand("R", hand.equals("right"), 2);
		Hand left = new Hand("L", hand.equals("left"), 0);

		return Arrays.stream(numbers)
			.mapToObj(n -> press(n, right, left))
			.collect(joining());
	}

	public static void main(String... args) throws IOException {

		Path p = Paths.get(System.getProperty("user.dir")+"/data/키패드_누르기.txt");
		BufferedReader reader = Files.newBufferedReader(p);

		int testCases = Integer.parseInt(reader.readLine());

		while (testCases > 0) {

			int[] numbers = Arrays.stream(reader.readLine().split(" "))
				.mapToInt(Integer::parseInt)
				.toArray();

			String hand = reader.readLine().trim();

			String answer = reader.readLine();

			System.out.println("Answer : "+ answer);
			System.out.println("Solved : "+ solve(numbers, hand));

			testCases--;
		}
	}
}