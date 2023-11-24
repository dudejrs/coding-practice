package com.example.cote.PGMRS;

import java.util.*;
import java.nio.file.*;
import java.io.*;

public class 사칙연산 {
	private static final int MIN_ARRAY_LENGTH =  3;
	private static final int MAX_ARRAY_LENGTH =  201;
	private static final int MIN_NUMBER_SIZE = 1000;

	private static interface IntComparator extends Comparator<Integer> {}
	private static final IntComparator[] COMP = {
		(a,b) -> Integer.compare(a,b),
		(a,b) -> Integer.compare(b,a)
	};

	private static final int[] TARGET_VALUE = {
		Integer.MIN_VALUE,
		Integer.MAX_VALUE
	};

	private static final int[][][] cache = new int[MAX_ARRAY_LENGTH+1][MAX_ARRAY_LENGTH+1][2];

	private static int compute(int start, int end, int type, String[] tokens){
		
		int ret = cache[start][end][type];
		if( ret != Integer.MIN_VALUE){
			return ret;
		}

		if( end - start == 1) {
			return Integer.parseInt(tokens[start]);
		}

		ret = TARGET_VALUE[type];

		for(int i = start +1; i< end; i+=2){
			int l = compute(start, i, type, tokens);
			int v; 

			if(tokens[i].equals("+")){
				int r= compute(i+1, end, type, tokens);
				v = l + r;
			}else {
				int r = compute(i+1, end, 1- type, tokens);
				v = l -r;
			}

			if( COMP[type].compare(v, ret) > 0){
				ret = v;
			}
		}
		return cache[start][end][type] = ret;
	}


	private static int solve(String[] tokens){

		for(int[][] cell : cache){
			for(int[]  array : cell){
				Arrays.fill(array, Integer.MIN_VALUE);
			}
		}

		return compute(0, tokens.length, 0, tokens);
	}

	public static void main(String... args) throws IOException{

		Path p = Paths.get(System.getProperty("user.dir")+"/data/사칙연산.txt");
		BufferedReader rd = Files.newBufferedReader(p);

		int testCases = Integer.parseInt(rd.readLine());
		while (testCases > 0){
			String[] tokens = rd.readLine().split("");
			int answer = Integer.parseInt(rd.readLine());

			System.out.println(String.format("%d, %d", solve(tokens), answer));
			testCases--;
		}

	}
}