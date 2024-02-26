package com.example.cote.PGMRS;

import java.util.*;
import java.io.*;
import java.nio.file.*;

public class 체육대회 {

	private static final int MAX_STUDENTES = 10;
	private static final int MAX_ABILITY_LENGTH = 10;

	private static Map<String, Integer> mem = new HashMap<>();

	private static String toStirng(int cur, boolean[] isChosen) {
		return cur + Arrays.toString(isChosen);
	}

	private static int search(int cur, boolean[] isChosen, int[][] ability){

		if (cur == ability.length) {
			return 0;
		}
		String memKey = toStirng(cur, isChosen);

		if (mem.containsKey(memKey)){
			return mem.get(memKey);
		}

		int ret = search(cur + 1, isChosen, ability);

		for (int i = 0; i < ability[cur].length; i++) {
			if (isChosen[i]) continue;
			isChosen[i] = true;
			ret = Math.max(ret, search(cur + 1, isChosen, ability) + ability[cur][i]);
			isChosen[i] = false;
		}

		mem.put(memKey, ret);

		return ret;
	}

	private static int solve(int[][] ability) {
		mem = new HashMap<>();
		return search(0, new boolean[ability[0].length], ability);
	}
	
	public static void main(String... args) throws IOException {

		Path p = Paths.get(System.getProperty("user.dir") + "/data/체육대회.txt");
		BufferedReader reader = Files.newBufferedReader(p);

		int testCases = Integer.parseInt(reader.readLine());

		while (testCases --> 0) {
			int[] nums = Arrays.stream(reader.readLine().split(" "))
				.mapToInt(Integer::parseInt)
				.toArray();
			int[][] ability = new int[nums[0]][nums[1]];

			for (int i = 0; i < ability.length; i++) {
				ability[i] = Arrays.stream(reader.readLine().split(" "))
					.mapToInt(Integer::parseInt)
					.toArray();
			}
			int answer = Integer.parseInt(reader.readLine());
			System.out.printf("%d %d\n", answer, solve(ability));
		}

	}
}