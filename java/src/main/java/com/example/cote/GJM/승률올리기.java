package com.example.cote.GJM;

import java.nio.file.*;
import java.io.*;
import java.util.*;

public class 승률올리기 {

	private static final int N = 2000000000;

	private static boolean decision(long n, long k, int ratio){
		return ((int) Math.floor((k*100)/n)) > ratio;
	}

	private static long solve(long n, long k){

		int ratio = (int) Math.floor((100*k)/n);

		if( ratio == 100 || !decision(n+N, k+N, ratio)) return -1;

		long lo = 0, hi = n;

		// lo < x <= hi
		while( lo+1 < hi){

			long mid = (int) (lo + hi)/2;

			if(decision(n+mid, k+mid, ratio))
				hi = mid;
			else 
				lo = mid;

		}

		return hi;
	}

	public static void main(String... args)throws IOException {

		Path p = Paths.get(System.getProperty("user.dir")+"/data/승률올리기.txt");
		BufferedReader rd = Files.newBufferedReader(p); 

		int testCases = Integer.parseInt(rd.readLine());

		while(testCases > 0){

			long[] n = Arrays.stream(rd.readLine().split(" "))
							.mapToLong(Long::parseLong)
							.toArray();

			System.out.println(solve(n[0],n[1]));

			testCases --;
		}


	}

};