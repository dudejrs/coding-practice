package com.example.cote.PGMRS;

import java.util.*;
import java.util.stream.*;
import static java.util.stream.Collectors.*;

public class 외톨이_알파벳 {
	private static final int MAX_STRING_LENGTH = 2600;
	
	private static final int TEST_CASES = 10;
	private static final Random random = new Random(13);

	private static String initialize() {
		int l = random.nextInt(MAX_STRING_LENGTH - 1) + 1;
		return IntStream.range(0, l)
			.mapToObj(i -> (char) (random.nextInt(26) + 'a'))
			.map(c -> Character.toString(c))
			.collect(joining());
	}

	private static String solve(String input) {
		StringBuilder builder = new StringBuilder();
		String target = "." + input + ".";

		for (char c = 'a'; c <= 'z'; c++) {
			if (target.split(c + "+").length < 3) {
				continue;
			}
			builder.append(c);
		}

		if (builder.length() == 0) {
			return "N";
		}
		return builder.toString();
	}
	
	public static void main(String... args) {
		for (int it = 0; it < TEST_CASES; it++) {
			String input = initialize();
			System.out.println(solve(input));
		}
	}
}