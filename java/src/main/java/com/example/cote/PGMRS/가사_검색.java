package com.example.cote.PGMRS;

import java.util.*;
import java.io.*;
import java.nio.file.*;


public class 가사_검색 {

	private static final int WORDS_LENGTH = 100000;
	private static final int WORD_LENGTH = 10000;
	private static final int MAX_SUM_OF_WORD_LENGTH = 1000000;

	private static final int QUERIES_LENGTH = 100000;
	private static final int MAX_KEYWORD_LENGTH = 10000;
	private static final int MAX_SUM_OF_KEYWORD_LENGTH = 1000000;

	private static final int TEST_CASES = 10;
	private static final Random random = new Random(41);


	private static class Node {
		private final Map<Integer, Integer> terminals = new HashMap<>();
		private final Map<Character, Node> children = new HashMap<>();

		public void add(String word, int offset){
			int length = word.length() - offset;
			terminals.put(length, terminals.getOrDefault(length, 0) + 1);

			if (length > 0) {
				char c = word.charAt(offset);
				Node child = children.getOrDefault(c, new Node());
				child.add(word, offset + 1);
				children.put(c, child);
			}
		}

		public int count(String keyword, int offset) {
			if (keyword.length() <= offset) return 0;

			if( keyword.charAt(offset) == '?' ) {
				return terminals.getOrDefault(keyword.length() - offset, 0);
			}

			char c = keyword.charAt(offset);
			if (!children.containsKey(c)) return 0;
			return children.get(c).count(keyword, offset+1);
		}	
	}


	private static String randomWord(int length) {
		if (length  <= 2) return "";
		int n = random.nextInt(length-1)+1;

		StringBuilder builder = new StringBuilder();

		for(int i=0; i<n; i++){
			builder.appendCodePoint(random.nextInt('z'-'a') + 'a');
		}	

		return builder.toString();
	}

	private static String randomKeyword(int length) {
		int n = random.nextInt(length-1)+1;
		int m = random.nextInt(n);
		boolean isPrefix = random.nextBoolean();

		StringBuilder builder = new StringBuilder();

		if (isPrefix) {
			while(m > 0) {
				builder.append("?");
				m --;
			}			
		}

		builder.append(randomWord(n-m));

		if( !isPrefix) {
			while(m > 0) {
				builder.append("?");
				m --;
			}						
		}

		return builder.toString();
	}

	private static String[] createWords() {
		int n = random.nextInt(WORDS_LENGTH-2) + 2;
		String[] ret = new String[n];

		for (int i=0; i < n; i++) {

			ret[i] = randomWord(Math.min(Math.floorDiv(MAX_SUM_OF_WORD_LENGTH, n), WORDS_LENGTH));
		}
		return ret;
	}

	private static String[] createKeywords() {
		int n = random.nextInt(QUERIES_LENGTH-2) + 2;
		String[] ret = new String[n];

		for (int i=0; i < n; i++) {
			ret[i] = randomKeyword(Math.min(Math.floorDiv(MAX_SUM_OF_KEYWORD_LENGTH, n), MAX_KEYWORD_LENGTH));
		}
		return ret;
	}

	private static int count(String keyword, Node trie, Node reversedTrie) {
		if (keyword.startsWith("?")) {
			return reversedTrie.count(new StringBuilder(keyword).reverse().toString(), 0);
		}

		return trie.count(keyword, 0);
	}

	private static int[] solve(String[] words, String[] keywords) {

		Node trie = new Node();
		Node reversedTrie = new Node();

		for (String word : words) {
			trie.add(word, 0);
			reversedTrie.add(new StringBuilder(word).reverse().toString(), 0);
		}


		return Arrays.stream(keywords)
				.mapToInt(keyword -> count(keyword, trie, reversedTrie))
				.toArray();
	}


	public static void main(String... args) throws IOException{

		Path p = Paths.get(System.getProperty("user.dir") + "/data/가사_검색.txt");
		BufferedReader rd = Files.newBufferedReader(p);

		int testCases = Integer.parseInt(rd.readLine());

		while (testCases > 0) {

			String[] words = rd.readLine().split(" ");
			String[] keywords = rd.readLine().split(" ");
			int[] answer = Arrays.stream(rd.readLine().split(" "))
								.mapToInt(Integer::parseInt)
								.toArray();

			if (!Arrays.equals(answer, solve(words, keywords))) {
				System.out.println("Answer : "+ Arrays.toString(answer));
				System.out.println("Solved : "+ Arrays.toString(solve(words, keywords)));
				return;
			}
			testCases--;
		}


		for (int it=0; it < TEST_CASES; it++) {
			String[] words = createWords();
			String[] keywords = createKeywords();

			int[] ret = solve(words, keywords);
			System.out.println(Arrays.toString(ret));
		}

	}
}