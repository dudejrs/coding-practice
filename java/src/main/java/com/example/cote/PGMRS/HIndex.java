package com.example.cote.PGMRS;

import java.util.*;

public class HIndex{

	private static final int TEST_CASES = 10;
	private static final int N = 1000;
	private static final int M = 10000;
	private static Random rd = new Random(43);


	private static boolean isValid(int[] citations, int h){
		long count = Arrays.stream(citations)
						.filter(i -> i>= h)
						.count();
		return count >= h;
	}

	private static int solve(int[] citations){

		Arrays.sort(citations);

		for(int i=citations.length-1; i>0; i--)
			if(isValid(citations, i)) return i;
		
		return 0;
	}

	public static void main(String... args){

		for (int it=0; it<TEST_CASES; it++){
			int n = rd.nextInt(N);
			int[] citations = new int[n];
			for(int i=0; i<n; i++) citations[i] = rd.nextInt(M);
			System.out.println(solve(citations));
		}

	}
}