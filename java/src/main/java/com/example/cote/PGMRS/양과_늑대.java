package com.example.cote.PGMRS;

import java.util.*;
import java.io.*;
import java.nio.file.*;

public class 양과_늑대 {

	private static final int MAX_INFO_LENGTH = 17;
	private static final int SHEEP = 0;
	private static final int WOLF = 1;

	private static Set<Integer> getNextNodes(int node, Set<Integer> nodes, boolean[][] tree) {
		Set<Integer> nextNodes = new HashSet<>(nodes);
		nextNodes.remove(node);

		for (int i = 0; i < tree[0].length; i++) {
			if (!tree[node][i]) continue;
			nextNodes.add(i);
		}

		return nextNodes;
	} 

	private static int search(Set<Integer> nodes, int sheep, int wolf, int[] info, boolean[][] tree) {
		int maxSheep = sheep;

		for (int node : nodes) {
			int nextSheep = sheep;
			int nextWolf = wolf;

			if (info[node] == 0) {
				nextSheep += 1;
			} else {
				nextWolf += 1;
			}

			if (nextWolf >= nextSheep) continue;

			int s = search(getNextNodes(node, nodes, tree), nextSheep, nextWolf, info, tree);

			if (s > maxSheep) {
				maxSheep = s;
			}
		}

		return maxSheep;
	}

	private static int solve(int[] info, int[][] edges) {
		boolean [][] tree = new boolean [info.length][info.length];

		for (int[] edge : edges) {
			tree[edge[0]][edge[1]] = true;
		}

		Set<Integer> nodes = new HashSet<>();
		nodes.add(0);

		return search(nodes, 0 , 0, info, tree);
	}

	public static void main(String... args) throws IOException {

		Path p = Paths.get(System.getProperty("user.dir") + "/data/양과_늑대.txt");
		BufferedReader reader = Files.newBufferedReader(p);

		int testCases = Integer.parseInt(reader.readLine());

		while (testCases --> 0) {

			int[] info = Arrays.stream(reader.readLine().split(" "))
				.mapToInt(Integer::parseInt)
				.toArray();

			int numEdges = Integer.parseInt(reader.readLine());
			int[][] edges = new int [numEdges][2];

			for (int i = 0; i < numEdges; i++) {
				edges[i] = Arrays.stream(reader.readLine().split(" "))
					.mapToInt(Integer::parseInt)
					.toArray();
			}

			int answer = Integer.parseInt(reader.readLine());

			System.out.printf("%d %d\n", answer, solve(info, edges));
		}
	}
}