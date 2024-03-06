package com.example.cote.PGMRS;

import java.util.*;
import java.io.*;
import java.nio.file.*;

public class 카페_확장 {

	private static record Order(
		int time,
		int duration
	) {}
		
	private static int solve(int[] menu, int[] order, int k) {
		Order[] orders= new Order[order.length];
		for (int i = 0; i < order.length; i++) {
			orders[i] = new Order(k * i, menu[order[i]]);
		}

		int max = 0, time = 0, end = 0;

		for (int start = 0; start < orders.length; start ++) {
			
			Order cur = orders[start];

			if (time < cur.time()) {
				time = cur.time();
			}

			time += cur.duration();

			while (end < orders.length && orders[end].time < time) {
				end ++;
			}

			max = Math.max(max, end - start);
		}	

		return max;
	}

	public static void main(String... args) throws IOException{
		Path p = Paths.get(System.getProperty("user.dir") + "/data/카페_확장.txt");
		BufferedReader reader = Files.newBufferedReader(p);

		int testCases = Integer.parseInt(reader.readLine());

		for( int it = 0; it < testCases; it++) {
			int[] menu = Arrays.stream(reader.readLine().split(" "))
				.mapToInt(Integer::parseInt)
				.toArray();

			int[] order = Arrays.stream(reader.readLine().split(" "))
				.mapToInt(Integer::parseInt)
				.toArray();

			int k = Integer.parseInt(reader.readLine());

			int answer = Integer.parseInt(reader.readLine());

			System.out.printf("%d %d\n", answer, solve(menu, order, k));
		}
	}
}