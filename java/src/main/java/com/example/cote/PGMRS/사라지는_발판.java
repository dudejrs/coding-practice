package com.example.cote.PGMRS;

import java.util.*;
import java.io.*;
import java.nio.file.*;

public class 사라지는_발판 {

	private static final int MAX_BOARD_ROW = 5;
	private static final int MAX_BOARD_COL = 5;

	private static record Coord (int y, int x){
	}

	private static record Result (boolean win, int turns){
	}

	private static final int[] dx = {0, 0, -1, 1};
	private static final int[] dy = {-1, 1, 0, 0};
	
	private static Result game(Coord player, Coord opponenet, int[][] board) {

		if (board[player.y()][player.x()] == 0) {
			return new Result(false, 0);
		}

		boolean win = false; 
		int winTurns = Integer.MAX_VALUE;
		int loseTurns = Integer.MIN_VALUE;

		board[player.y()][player.x()] = 0;

		for (int d = 0; d < 4; d++) {
			int nx = player.x() + dx[d];
			int ny = player.y() + dy[d];

			if (ny < 0 || ny >= board.length || nx < 0 || nx >= board[ny].length) {
				continue;
			}

			if (board[ny][nx] == 0) {
				continue;
			}

			Result result = game(opponenet, new Coord(ny, nx), board);

			if (!result.win) {
				win = true;
				winTurns = Math.min(winTurns, result.turns);
			} else if (!win) {
				loseTurns = Math.max(loseTurns, result.turns);
			}
		}

		if (win) {
			return new Result(true, winTurns + 1);
		}

		if (loseTurns == Integer.MIN_VALUE) {
			return new Result(false, 0);
		}

		return new Result(false, loseTurns + 1);
	}	

	private static int solve(int[][] board, int[] aloc, int[] bloc) {

		return game(
			new Coord(aloc[0],aloc[1]),
			new Coord(bloc[0], bloc[1]),
			board).turns;
	}

	public static void main(String... args) throws IOException {

		Path p = Paths.get(System.getProperty("user.dir") + "/data/사라지는_발판.txt");
		BufferedReader reader = Files.newBufferedReader(p);

		int testCases = Integer.parseInt(reader.readLine());

		while (testCases --> 0) {
			int[] nums = Arrays.stream(reader.readLine().split(" "))
				.mapToInt(Integer::parseInt)
				.toArray(); 

			int[][] board = new int[nums[0]][nums[1]];

			for (int i = 0; i < board.length; i++){
				board[i] = Arrays.stream(reader.readLine().split(" "))
					.mapToInt(Integer::parseInt)
					.toArray();
			}

			int[] aloc = Arrays.stream(reader.readLine().split(" "))
				.mapToInt(Integer::parseInt)
				.toArray();

			int[] bloc = Arrays.stream(reader.readLine().split(" "))
				.mapToInt(Integer::parseInt)
				.toArray();

			int answer = Integer.parseInt(reader.readLine());

			int ret = solve(board, aloc, bloc);

			System.out.printf("%d %d\n", answer, ret);
		}
	}
}