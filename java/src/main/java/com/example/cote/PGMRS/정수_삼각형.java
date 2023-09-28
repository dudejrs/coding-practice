package com.example.cote.PGMRS;

import java.util.*;
import java.util.stream.*;
import static java.util.stream.Collectors.*;
import java.io.*;
import java.nio.file.*;

public class 정수_삼각형{

	private static final int MAX_HEIGHT = 500;
	private static final int MAX_N = 10000;
	private static final int[][] cache = new int[MAX_HEIGHT+1][MAX_HEIGHT+1];

	private static int max(int i, int j, List<List<Integer>> triangle){
		if(cache[i][j] != -1) return cache[i][j];

		return cache[i][j] = Math.max(max(i+1,j,triangle), max(i+1,j+1,triangle)) + triangle.get(i).get(j);
	}	

	private static int solve(List<List<Integer>> triangle){
		for(int i=0; i<MAX_HEIGHT+1; i++)
			Arrays.fill(cache[i], -1);

		int height = triangle.size();

		for(int j=0; j<height; j++){
			cache[height-1][j] = triangle.get(height-1)
										.get(j);
		}

		for(int i= height-2; i >= 0; i-- ){
			for(int j=0; j<i; j++){
				max(i,j, triangle);
			}
		}

		return max(0,0, triangle);
	}
	
	public static void main(String... args) throws IOException{

		Path p = Paths.get(System.getProperty("user.dir")+"/data/정수_삼각형.txt");
		BufferedReader rd = Files.newBufferedReader(p);

		int testCases = Integer.parseInt(rd.readLine());
		List<List<Integer>> triangle = new LinkedList<>();
		
		while(testCases > 0) {
			int height = Integer.parseInt(rd.readLine());

			while (height >0){
				triangle.add(Arrays.stream(rd.readLine().split(" "))
									.map(Integer::parseInt)
									.collect(toList())
				);
				height--;
			}

			System.out.println(solve(triangle));	

			testCases--;
		}

	}

}