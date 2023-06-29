package com.example.cote.GJM;

import java.io.*;
import java.nio.file.*;
import java.util.*;

public class 카쿠로{

	private static final int WHITE = 1;

	private static int n;
	private static int q;
	private static int[][] color;
	private static int[][] value;
	private static int[][][] hint;
	private static int[] sum;
	private static int[] length;
	private static int[] known;
	private static int[][][] candidates = new int[10][46][1024];


	private static void initialize(BufferedReader rd) throws IOException{

		n = Integer.parseInt(rd.readLine());

		color = new int[n][n];
		value = new int[n][n];
		hint = new int[n][n][2];

		for(int i=0; i<n; i++){
			
			int[] tmp = Arrays.stream(rd.readLine().split(" "))
							.mapToInt(Integer::parseInt)
							.toArray();
			for(int j=0; j<n; j++)
				color[i][j] = tmp[j];
		}

		q = Integer.parseInt(rd.readLine());
		sum = new int[q];
		length = new int[q];
		known = new int[q];

		for(int i=0; i<q; i++){
			int[] tmp = Arrays.stream(rd.readLine().split(" "))
							.mapToInt(Integer::parseInt)
							.toArray();
			int y = tmp[0];
			int x = tmp[1];
			int direction = tmp[2];
			
			hint[y-1][x-1][direction] = i;
			sum[i] = tmp[3];
		}

		return;
	}

	private static int getSize(int mask){
		int count =0;
		int cur = 0;
		while(cur < 10){
			if((mask & 1) == 1 ) {
				count++;
			}
			mask = mask >> 1;
			cur++;
		}

		return count;
	}

	private static int getSum(int mask){
		int sum = 0;

		int cur =0;
		while(cur < 10){
			if((mask & 1) == 1){
				sum += cur;
			}
			mask = mask >> 1;
			cur++;
		}

		return sum;
	}

	private static int getCandidates(int len, int sum, int known){
		int allSets = 0 ;

		for(int set =0; set < 1024; set += 2){
			if(getSum(set) == sum && getSize(set) == len && (known & set) == known){
				allSets |= set;
			}
		}
		return allSets & (~known);
	}

	private static void generateCandidates(){
		Arrays.fill(candidates, 0);

		for(int set=0; set < 1024; set += 2){
			int subset = set;
			int sum = getSum(set);
			int len = getSize(set);

			while(true){
				candidates[len][sum][subset] |= (set & ~subset) ;
				if(subset == 0) break;
				subset = (subset-1) & subset;
			}
		}
	}


	private static void solve(){
		return;
	}

	private static void printSolution(){
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				System.out.print(value[i][j]+" ");
			}
			System.out.println("");
		}
	}

	public static void main(String... args) throws IOException{

		Path p = Paths.get(System.getProperty("user.dir")+ "/data/카쿠로.txt");
		BufferedReader rd = Files.newBufferedReader(p);

		int testCases = Integer.parseInt(rd.readLine());

		while(testCases > 0) {

			initialize(rd);
			solve();
			printSolution();


			testCases --;
		}

		return;
	}
}