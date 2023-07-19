package com.example.cote.PGMRS;

import java.util.*;

public class 쿼드압축_후_개수_세기{

	private static final int N = 8;
	private static final int TEST_CASES = 10;

	private static int[][] board = new int[N][N];
	private static Random rd = new Random(43);

	private static class Count {
		public int ones;
		public int zeros;

		Count ( int zeros, int ones) {
			this.zeros = zeros;
			this.ones = ones;
		}

		Count add(Count other){
			return new Count( this.zeros + other.zeros, this.ones + other.ones);
		}


	}

	private static Count solve(int y, int x, int len){
		
		if(len == 1) 
			return (board[y][x] == 1) ? new Count(0,1) : new Count(1,0);

		int nlen = len/2;

		for(int i = y; i<y+len; i++)
			for(int j = x; j<x+len; j++){
				if( board[i][j] != board[y][x] )
					return solve(y,x, nlen)
							.add(solve(y,x+nlen, nlen))
							.add(solve(y+nlen, x, nlen))
							.add(solve(y+nlen, x+nlen, nlen));
			}

		return (board[y][x] == 1) ? new Count(0,1) : new Count(1,0);
	}

	public static void main(String... args){

		for(int it=0; it<TEST_CASES; it++){

			for(int i=0; i< N; i++)
				for(int j=0; j<N; j++)
					board[i][j] = rd.nextInt()%2;
			
			Count c = solve(0,0,N);
			System.out.println(c.zeros+","+c.ones);			
		}

		return ;
	}
}