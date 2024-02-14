package com.example.cote.PGMRS;

import java.util.*;
import java.io.*;
import java.nio.file.*;
import static java.util.stream.Collectors.*;

public class 체육복 {

	private static final int MAX_N = 30;

	private static int solve(int n, int[] lost, int[] reserve) {
		Arrays.sort(lost);
		Arrays.sort(reserve);

		// reserve 와 lost의 교집합
		Set<Integer> reserveAndLost = Arrays.stream(reserve)
			.boxed()
			.collect(toSet());
		reserveAndLost.retainAll(Arrays.stream(lost)
			.boxed()
			.collect(toSet()));

		Queue<Integer> q = new LinkedList();

		for (int l : lost) {
			if (reserveAndLost.contains(l)) {
				continue;
			}
			q.add(l);
		}

		int borrowers = 0;

		for (int r : reserve) {
			if (reserveAndLost.contains(r)) {
				continue;
			}

			while (!q.isEmpty() && q.peek() < r - 1 ){
				q.poll();
			}
			if (q.isEmpty()) break;

			if (q.peek() <= r+1) {
				q.poll();
				borrowers++;
			}
		}

		return n - lost.length + reserveAndLost.size() + borrowers;
	}

	public static void main(String... args) throws IOException {
		
		Path p = Paths.get(System.getProperty("user.dir") + "/data/체육복.txt");
		BufferedReader reader = Files.newBufferedReader(p);

		int testCases = Integer.parseInt(reader.readLine());

		while (testCases > 0) {
			int n = Integer.parseInt(reader.readLine());
			int[] lost = Arrays.stream(reader.readLine().split(" "))
				.mapToInt(Integer::parseInt)
				.toArray();
			int[] reserve = Arrays.stream(reader.readLine().split(" "))
				.mapToInt(Integer::parseInt)
				.toArray();
			int answer = Integer.parseInt(reader.readLine());

			System.out.printf("%d %d\n", answer, solve(n, lost, reserve));

			testCases--;
		}

	}
}