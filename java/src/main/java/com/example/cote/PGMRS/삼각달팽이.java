package com.example.cote.PGMRS;


import java.util.*;
import java.nio.file.*;
import java.io.*;

public class 삼각달팽이 {

	private static final int[] dx = {0, 1, -1};
	private static final int[] dy = {1, 0, -1};
	

	private static int[] solve(int n){

		int[][] triangle = new int[n][n];

		int x= 0, y = 0, d = 0, v= 1;

		while(true){
			triangle[y][x] = v++;
			int nx = x + dx[d];
			int ny = y + dy[d];

			if (nx == n || ny == n || nx == -1 || ny == -1 || triangle[ny][nx] != 0){
				d = (d+1)%3;
				nx = x + dx[d];
				ny = y + dy[d];

				if(nx == n || ny == n || nx == -1 || ny == -1 || triangle[ny][nx] != 0) break;
			}

			x = nx;
			y = ny;
		}


		int[] result = new int [v-1];
		int k = 0;
		for(int i=0; i<n; i++)
			for(int j=0; j<= i; j++){
				result[k] = triangle[i][j];
				k++;
			}
		

		return result;
	}

	public static void main(String... args){

		for(int i=4; i<=1000; i++){
			int[] result = solve(i);
			for(int j=0; j<result.length; j++)
				System.out.print(result[j]+" ");
			System.out.println("");
		}
	}
}	