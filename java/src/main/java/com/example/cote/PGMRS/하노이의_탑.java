package com.example.cote.PGMRS;

import java.util.*;

public class 하노이의_탑 {

	private static final int TEST_CASES =  10;

	private static void solve(int n, int from, int to, List<int[]> path){
		if(n == 1) {
			path.add(new int[]{from, to});
			return;
		}

		int empty = 6 - from - to;

		solve(n-1, from, empty, path);
		solve(1, from, to, path);
		solve(n-1,empty,to, path);

	}

	public static void main(String... args){
		
		for(int n=1; n<TEST_CASES; n++){
			List<int[]> path = new ArrayList<int[]>();
			solve(n,1,3,path);
			for( int[] a : path){
				for(int i=0; i<2; i++)
					System.out.print(a[i] +" ");
				System.out.print(",");
			}
			System.out.println("");
		}
	}
}