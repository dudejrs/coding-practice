package com.example.cote.PGMRS;

import java.util.*;
import java.io.*;
import java.nio.file.*;

public class k진수에서_소수_개수_구하기 {

	private static final int N = 1000000;
	private static final int MAX_K = 10;
	private static final int MIN_K = 3;

	private static final int TEST_CASES = 10;
	private static final Random random = new Random(43);

	private static boolean isPrime(long n) {
		if (n <= 1) return false;

		for (long i = 2; i * i <= n; i++) {
			if (n % i == 0) return false;
		}

		return true;
	}

	private static int solve(int n, int k) {
		String[] tokens = Long.toString(n, k).split("0+");

		int ret = 0;

		for (String token : tokens) {
			if (isPrime(Long.parseLong(token))) {
				ret++;
			}
		}

		return ret;
	}
	
	public static void main(String... args) throws IOException {

		Path p = Paths.get(System.getProperty("user.dir") + "/data/k진수에서_소수_개수_구하기.txt");
		BufferedReader reader = Files.newBufferedReader(p);

		int testCases = Integer.parseInt(reader.readLine());

		while (testCases --> 0) {

			int n = Integer.parseInt(reader.readLine());
			int k = Integer.parseInt(reader.readLine());
			int answer = Integer.parseInt(reader.readLine());

			int ret = solve(n, k);

			if (ret != answer) {
				System.out.printf("%d %d\n", answer, ret);
				return;
			}
		}


		for (int it = 0; it < TEST_CASES; it ++) {
			int n = random.nextInt(N - 1) + 1;
			int k = random.nextInt(MAX_K - MIN_K) + MIN_K;

			System.out.println(solve(n, k));
		}
	}
}