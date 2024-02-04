package com.example.cote.PGMRS;

import java.util.*;
import java.io.*;
import java.nio.file.*;

public class 호텔_방_배정 {

	private static final int K = 1012;
	private static final int MAX_ROOM_NUMBERS_LENGTH = 200000;

	private static class Node {
		private int depth = 1;
		private Node parent = null;
		public int max;
		
		public Node(int value) {
			max = value;
		}

		public boolean isConnected(Node other) {
			return root() == other.root();
		}

		public int max() {
			return root().max;
		}

		public void merge(Node other) {
			if(isConnected(other)) return;

			Node root1 = root();
			Node root2 = other.root();

			if (root1.depth > root2.depth) {
				root2.parent = root1;
			} else if (root1.depth < root2.depth) {
				root1.parent = root2;
			} else {
				root2.parent = root1;
				root1.depth += 1;
			}

			root1.max = root2.max = Math.max(root1.max, root2.max);
		}


		private Node root() {
			if (parent == null) return this;

			return parent.root();
		}
	}

	private static int[] solve(int[] roomNumbers){

		List<Integer> ret = new ArrayList<>();

		Map<Integer, Node> nodes = new HashMap<>(); 

		for (int number : roomNumbers) {

			if (nodes.containsKey(number)) {
				number = nodes.get(number).max() + 1;
			}

			Node node = new Node(number);
			nodes.put(number, node);

			if (nodes.containsKey(number - 1)) {
				node.merge(nodes.get(number - 1));
			}

			if (nodes.containsKey(number + 1)) {
				node.merge(nodes.get(number + 1));
			}

			ret.add(number);
		}


		return ret.stream()
				.mapToInt(Integer::intValue)
				.toArray();
	}
	
	public static void main(String... args) throws IOException{

		Path p = Paths.get(System.getProperty("user.dir")+"/data/호텔_방_배정.txt");
		BufferedReader reader = Files.newBufferedReader(p);

		int testCases = Integer.parseInt(reader.readLine());

		while (testCases > 0) {
			int k = Integer.parseInt(reader.readLine());
			int[] roomNumbers =  Arrays.stream(reader.readLine().split(" "))
									.mapToInt(Integer::parseInt)
									.toArray();
			int[] answer =  Arrays.stream(reader.readLine().split(" "))
									.mapToInt(Integer::parseInt)
									.toArray();

			System.out.println("Solved: " + Arrays.toString(solve(roomNumbers)));
			System.out.println("Answer: " + Arrays.toString(answer));


			testCases--;
		}
	}
}