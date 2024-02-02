
package com.example.cote.PGMRS;


import java.util.*;
import java.io.*;
import java.nio.file.*;

public class 섬_연결하기 {

	private static final int TEST_CASES = 10;
	private static final int MAX_N = 100;
	private static final int MAX_COST = 100;
	private static final Random random = new Random(43);


	private static class Node {
		private int depth = 1;
		private Node parent = null;

		public boolean isConnected(Node other) {
			return root() == other.root();
		}

		public void merge(Node other) {
			if (isConnected(other));

			Node root1 = root();
			Node root2 = other.root();

			if (root1.depth > root2.depth) {
				root2.parent = root1;
			} else if (root1.depth < root2.depth) {
				root1.parent = root2;
			} else {
				root2.parent = root1;
				root1.depth +=1;
			}
		}

		private Node root() {
			if (parent == null) {
				return this;
			}

			return parent.root();
		}
	}

	private static class Edge {
		public final int u; 
		public final int v;
		public final int cost;

		private Edge(int u, int v, int cost){
			this.u = Math.min(u,v);
			this.v = Math.max(u,v);
			this.cost = cost;
		}
	}

	private static int solve(int n, int [][] costs) {

		Edge[] edges = Arrays.stream(costs)
							.map(edge -> new Edge(edge[0], edge[1], edge[2]))
							.sorted(Comparator.comparingInt(e-> e.cost))
							.toArray(Edge[]::new);

		Node[] nodes = new Node[n];

		for (int i=0; i<n; i++) {
			nodes[i] = new Node();
		}

		int ret = 0;

		for (Edge edge : edges) {
			Node n1 = nodes[edge.u];
			Node n2 = nodes[edge.v];

			if (n1.isConnected(n2)) continue;
			n1.merge(n2);
			ret += edge.cost;

		}

		return ret;
	}

	public static void main(String[] args) throws IOException{

		Path p = Paths.get(System.getProperty("user.dir")+"/data/섬_연결하기.txt");
		BufferedReader rd = Files.newBufferedReader(p);

		int testCases = Integer.parseInt(rd.readLine());

		while (testCases > 0) {
			int n = Integer.parseInt(rd.readLine());
			int length = Integer.parseInt(rd.readLine());
			int[][] costs = new int[length][3];

			for(int i=0; i<length; i++){
				int[] edge = Arrays.stream(rd.readLine().split(" "))
					.mapToInt(Integer::parseInt)
					.toArray();
				costs[i] = edge;
			}

			int answer = Integer.parseInt(rd.readLine());
			int ret = solve(n, costs);

			if (answer != ret){
				System.out.println(String.format("answer : %d, return :  %d", answer, ret));
				return;
			}

			testCases--;
		}


		for(int it=0; it <TEST_CASES; it++){
			int n = random.nextInt(MAX_N-1)+1;
			List<int[]> edges = new LinkedList();

			boolean[][] connected = new boolean[n][n];

			for(int i=0; i<n; i++){
				for(int j=0; j<n; j++){
					if(connected[i][j] || !random.nextBoolean()){
						continue;
					}

					int cost = random.nextInt(MAX_COST-1)+1;
					edges.add(new int[]{i,j,cost});
					connected[i][j] = true;
					connected[j][i] = true;
				}
			}

			System.out.println(solve(n, edges.toArray(int[][]::new)));
		}
	}
}