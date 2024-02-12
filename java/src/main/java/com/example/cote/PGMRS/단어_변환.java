package com.example.cote.PGMRS;


import java.util.*;
import java.io.*;
import java.nio.file.*;

public class 단어_변환 {	

	private static final int MAX_WORDS_LENGTH = 10;

	public static record State (String word, int step){}

	private static boolean isConvertable(String src, String dst) {
		
		char[] srcArr = src.toCharArray();
		char[] dstArr = dst.toCharArray();

		int diff = 0;

		for (int i = 0; i < srcArr.length; i++) {
			if (srcArr[i] != dstArr[i]) diff++;
		}

		return diff == 1;
	}

	private static int solve(String begin, String target, String[] words) {

		boolean[] isVisited = new boolean[words.length];

		Queue<State> queue =new LinkedList<> ();
		queue.add(new State(begin, 0));

		while (!queue.isEmpty()) {
			State state = queue.poll();

			if (state.word.equals(target)){
				return state.step;
			}

			for (int i = 0; i < words.length; i++) {
				String next = words[i];

				if (!isConvertable(state.word, next)){
					continue;
				}

				if (isVisited[i]) {
					continue;
				}

				isVisited[i] = true;
				queue.add(new State(next, state.step + 1));
			}
		}
		return 0;
	}

	public static void main(String... args) throws IOException{

		Path p = Paths.get(System.getProperty("user.dir")+"/data/단어_변환.txt");
		BufferedReader reader = Files.newBufferedReader(p);

		int testCases = Integer.parseInt(reader.readLine());

		while (testCases > 0) {
			String begin = reader.readLine();
			String target = reader.readLine();

			String[] words = reader.readLine().split(" ");
			int answer = Integer.parseInt(reader.readLine());

			System.out.printf("%d %d\n", answer, solve(begin, target, words));

			testCases--;
		}
	}
}