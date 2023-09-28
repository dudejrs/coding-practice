package com.example.cote.PGMRS;

import java.util.*;
import java.util.stream.*;

public class 등굣길_최단_경로의_개수 {

	private static final int D = 1000000007; 
	private static final int MAX_HEIGHT = 100;
	private static final int MAX_WIDTH = 100;
	private static final int MAX_NUM_PUDDLES = 10;

	private static final int TEST_CASES = 10;
	private static final Random rd = new Random(43);

	private static final int[][] cache = new int[MAX_HEIGHT+1][MAX_WIDTH+1];

	private static int[][] getPuddles(int n, int m){
		int numPuddles = rd.nextInt(MAX_NUM_PUDDLES);

		Set<List<Integer>> set = new HashSet<>();

		int[][] puddles = new int[numPuddles][2];
		int i =0;
		while(i<numPuddles) {
			List<Integer> candidate = List.of(rd.nextInt(n)+1, rd.nextInt(m)+1);
			if(set.contains(candidate)) continue;
			if(candidate.equals(List.of(1,1)) || candidate.equals(List.of(n,m))) continue;
			puddles[i][0] =  candidate.get(0);
			puddles[i][1] =  candidate.get(1);
			i++;
		}

		return puddles;
	}


	private static int count(int n, int m, int i, int j, boolean[][] isPuddles){

		if(i> n || i <= 0 || j > m || j<= 0) return 0;
		if(isPuddles[i][j]) return 0;
		if(i == n && j == m) return 1;

		if(cache[i][j]!= -1) return cache[i][j];


		return cache[i][j] =  (count(n,m,i,j+1,isPuddles)+ count(n,m,i+1,j,isPuddles)) % D;
	}

	private static int solve(int n, int m, int[][] puddles){

		for(int i=0; i<MAX_HEIGHT+1; i++)
			Arrays.fill(cache[i], -1);

		boolean[][] isPuddles = new boolean [n+1][m+1];

		for(int i=0; i<n+1; i++)
			Arrays.fill(isPuddles[i], false);
		

		for(int[] puddle : puddles)
			isPuddles[puddle[0]][puddle[1]] = true;


		return count(n,m,1,1,isPuddles);
	}

	public static void main(String... args){
		
		for(int it= 0; it<TEST_CASES ; it++){
			int m = rd.nextInt(MAX_WIDTH-1)+1;
			int n = rd.nextInt(MAX_HEIGHT-1)+1;
			int[][] puddles = getPuddles(n,m);
			System.out.println(solve(n,m,puddles));
	
		}

	}

}