package com.example.cote.PGMRS;

import java.util.*;
import java.util.function.*;

public class 유전_법칙 {

	private static final int MAX_QUERIES_LENGTH = 5;
	private static final int MAX_GENERATION = 16;
	private static final IntUnaryOperator gen =  n -> (int) Math.pow(4, n - 1);

	private static final Random random = new Random(43);
	private static final int TEST_CASES = 10;

	private static String find(int n, int p) {
		if (n == 1) {
			return "Rr";
		}

		int chunk = (int) Math.pow(4, n - 2);
		int group = (p - 1) / chunk;

		if (group == 0) {
			return "RR";
		}

		if (group == 3) {
			return "rr";
		}

		return find(n - 1, p % chunk);
	}

	private static String[] solve(int[][] queries) {
		return Arrays.stream(queries)
			.map(query -> find(query[0], query[1] ))
			.toArray(String[]::new);
	}
	
	public static void main(String... args) {

		for (int it = 0; it < TEST_CASES; it++) {
			int q = random.nextInt(MAX_QUERIES_LENGTH - 1) + 1;
			int[][] queries = new int[q][2];

			for (int i = 0; i < q; i++) {
				int g = random.nextInt(MAX_GENERATION - 2) + 2;
				queries[i][0] = g;
				queries[i][1] = random.nextInt(gen.applyAsInt(g) - 1) + 1;
			}
			System.out.println(Arrays.toString(solve(queries)));
		}

	}
}