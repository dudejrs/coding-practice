package com.example.cote.PGMRS;

import java.util.*;
import java.io.*;
import java.nio.file.*;
import static java.util.Comparator.*;

public class 단속_카메라 {

	private static final int MAX_CARS = 10000;
	private static final int MIN_ENTRY = -30000;
	private static final int MAX_ENTRY = 30000;

	private static final int TEST_CASES = 10;
	private static final Random random = new Random(43);

	private static int solve(int[][] routes) {

		Arrays.sort(routes, comparingInt(r -> r[1]));
		
		int last = Integer.MIN_VALUE;
		int count = 0;

		for (int[] route : routes) {
			if (route[0] <= last && last <= route[1]) {
				continue;
			}
			last = route[1];;
			count++;
		}

		return count;
	} 

	public static void main(String... args) throws IOException {

		Path p = Paths.get(System.getProperty("user.dir")+"/data/단속_카메라.txt");
		BufferedReader reader = Files.newBufferedReader(p);

		int testCases = Integer.parseInt(reader.readLine());

		while (testCases > 0) {

			int n = Integer.parseInt(reader.readLine());
			int[][] routes = new int[n][2];
			for (int i = 0; i < n; i ++){
				routes[i] = Arrays.stream(reader.readLine().split(" "))
					.mapToInt(Integer::parseInt)
					.toArray();
			}
			int answer = Integer.parseInt(reader.readLine());
			int ret = solve(routes);

			if (ret != answer){
				System.out.printf("%d %d\n", answer, ret);
				return;
			}

			testCases--;
		}

		for (int it = 0; it < TEST_CASES; it++) {
			int n = random.nextInt(MAX_CARS - 2) + 1;
			int[][] routes = new int[n][2];
			for (int[] route : routes) {
				int end = random.nextInt(MAX_ENTRY - MIN_ENTRY) +  MIN_ENTRY;
				int start = random.nextInt(end - MIN_ENTRY) + MIN_ENTRY;
				route[0] = start;
				route[1] = end;
			}
			System.out.println(solve(routes));
		}

	}
}