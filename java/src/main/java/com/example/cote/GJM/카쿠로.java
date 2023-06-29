package com.example.cote.GJM;

import java.io.*;
import java.nio.file.*;
import java.util.*;

public class 카쿠로{

	private static final int WHITE = 1;
	private static final int ROW = 0;
	private static final int COL = 1;

	private static int n;
	private static int q;
	private static int[][] color;
	private static int[][] value;
	private static int[][][] hint;
	private static int[] sum;
	private static int[] length;
	private static int[] known;
	private static int[][][] candidates = new int[10][46][1024];


	private static void printSolution(){
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				System.out.printf("%4d", value[i][j]);
			}
			System.out.println("");
		}
	}

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

			int count =0;
			if(direction == ROW){
				int cur =x;
				while(count < 10 && cur <n){
					if(color[y-1][cur] != WHITE)
						break;
					count++;
					cur++;
				}
			}else {
				int cur =y;
				while(count < 10 && cur <n){
					if(color[cur][x-1] != WHITE)
						break;
					count++;
					cur++;
				}				
			}
			length[i] = count;
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
			if((mask & 1) != 0){
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
		
		for(int i =0; i<10; i++)
			for(int j=0; j<46; j++)
				Arrays.fill(candidates[i][j], 0);

		for(int set=0; set < 1024; set += 2){
			int subset = set;
			int sum = getSum(set);
			int len = getSize(set);

			while(true){
				candidates[len][sum][subset] |= (set & (~subset)) ;
				if(subset == 0) break;

				subset = (subset-1) & subset;
			}
		}
	}

	private static void put(int y, int x, int val){
		for(int h=0; h<2; h++){
			known[hint[y][x][h]] |= (1 << val);
		}
		value[y][x] = val;
	}

	private static void remove(int y, int x, int val){
		for(int h=0; h<2; h++){
			known[hint[y][x][h]] &= ~(1<< val);
		}

		value[y][x] = 0;
	}

	private static int getCandHint(int hint){
		System.out.println(hint+","+length[hint]+","+sum[hint]+","+known[hint]);
		return candidates[length[hint]][sum[hint]][known[hint]];
	}
	private static int getCandCoord(int y, int x){
		return getCandHint(hint[y][x][0]) & getCandHint(hint[y][x][1]);
	}

	private static boolean search(){
		int y= -1, x= -1, minCands = 1023;

		for(int i=0; i<n; i++)
			for(int j=0; j<n; j++)
				if(color[i][j] == WHITE && value[i][j] == 0){
					int cands = getCandCoord(i,j);
					if(getSize(minCands) > getSize(cands)){
						minCands = cands;
						y = i; x= j;
					}
				}


		if(minCands == 0) return true;	

		if(y == -1){
			printSolution();
			return true;
		}

		for(int val= 1; val <=9; ++val){
			if((minCands & (1<<val)) != 0){
				put(y, x, val);
				if(search())return true;
				remove(y, x, val);
			}
		}

		return false;
	}

	public static void main(String... args) throws IOException{

		Path p = Paths.get(System.getProperty("user.dir")+ "/data/카쿠로.txt");
		BufferedReader rd = Files.newBufferedReader(p);

		int testCases = Integer.parseInt(rd.readLine());

		generateCandidates();

		while(testCases > 0) {

			initialize(rd);
			search();


			testCases --;
		}

		return;
	}
}