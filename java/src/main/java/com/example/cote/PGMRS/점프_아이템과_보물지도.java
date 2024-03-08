package com.example.cote.PGMRS;

import java.util.*;
import java.io.*;
import java.nio.file.*;

public class 점프_아이템과_보물지도 {

	private static final int MAX_N = 1000;
	private static final int MAX_M = 1000;

	private static final int[] dy = {-1, 0, 0, 1};
	private static final int[] dx = {0 ,-1, 1, 0};

	private static record State (
		int y,
		int x,
		int jump,
		int step
	) {}

	private static int solve(int n, int m, int[][] holes) {

		boolean[][] map = new boolean[n][m];

		for (boolean[] row : map) {
			Arrays.fill(row, true);
		}

		for (int[] hole : holes) {
			int y = hole[0] - 1;
			int x = hole[1] - 1;
			map[y][x] = false;
		}

		boolean[][][] isVisited = new boolean[n][m][2];

		Queue<State> q = new LinkedList<>();

		q.add(new State(0, 0, 1, 0));
		isVisited[0][0][1] = true;

		while (!q.isEmpty()) {
			State s = q.poll();

			if (s.x() == n - 1 && s.y() == m - 1) {
				return s.step;
			}

			for (int d = 0; d < 4; d++) {
				
				int ny = s.y() + dy[d];
				int nx = s.x() + dx[d];

				if (ny < 0 || ny >= n || nx < 0 || nx >= m) {
					continue;
				}


				if (map[ny][nx]) {
					if (isVisited[ny][nx][s.jump()]) {
						continue;
					}

					isVisited[ny][nx][s.jump()] = true;
					q.add(new State(ny, nx, s.jump(), s.step() + 1));

				} 

				if (s.jump() <= 0 ) {
					continue;
				}

				int nny = ny + dy[d];
				int nnx = nx + dx[d];

				if (nny < 0 || nny >= n || nnx < 0 || nnx >= m) {
					continue;
				}

				if (isVisited[nny][nnx][s.jump()]) {
					continue;
				}

				isVisited[nny][nnx][s.jump() - 1] = true;
				q.add(new State(nny, nnx, s.jump() - 1, s.step + 1));

			}

		}

		return -1;
	}
	
	public static void main(String... args) throws IOException{

		Path p = Paths.get(System.getProperty("user.dir") + "/data/점프_아이템과_보물지도.txt");
		BufferedReader reader = Files.newBufferedReader(p);

		int testCases = Integer.parseInt(reader.readLine());

		while (testCases --> 0) {
			int n = Integer.parseInt(reader.readLine());
			int m = Integer.parseInt(reader.readLine());
			int numHoles = Integer.parseInt(reader.readLine());
			int[][] holes = new int[numHoles][2];

			for (int i = 0; i < numHoles; i++) {
				holes[i] = Arrays.stream(reader.readLine().split(" "))
					.mapToInt(Integer::parseInt)
					.toArray();
			}
			int answer = Integer.parseInt(reader.readLine());

			System.out.printf("%d %d\n", answer, solve(n, m, holes));
		}
	}
}