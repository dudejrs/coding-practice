package com.example.cote.PGMRS;

import java.util.*;
import java.util.stream.*;

public class 징검다리{


	private static final int TEST_CASES = 10;

	private static final int MAX_DISTANCE =  1000000000;
	private static final int MAX_ROCK_NUMBER = 50000;

	private static final Random rd = new Random(43);
	
	private static int distance;
	private static int r;
	private static int n;
	private static int[] rocks;


	private static void initialize(){
		distance = rd.nextInt(MAX_DISTANCE-1) +1 ;
		r = rd.nextInt(MAX_ROCK_NUMBER-1)+1;
		n = rd.nextInt(r-2)+1;
		rocks = new int[n];

		for(int i=0; i<n; i++)
			rocks[i] = rd.nextInt(distance-2) +1;
	}

	private static  boolean isValid(int d) {

		int removed =0; 
		int last = 0; 
		
		for(int i=0; i<rocks.length; i++) {
			if(rocks[i] -last < d){
				removed++;
				continue; 
			}
			last = rocks[i];
		}
		return removed <= n;

	}

	private static int solve(){
		rocks = Arrays.copyOf(rocks, rocks.length + 1);
		rocks[rocks.length-1] = distance;
		Arrays.sort(rocks);

		int lo = 1; 
		int hi = distance+1;

		while(hi - lo > 1){
			int mid= (hi+lo)/2; 
			if(isValid(mid))
				lo = mid;
			else 
				hi = mid;

		}

		return lo;
	}

	public static void main(String... args){

		for (int it =0; it <TEST_CASES; it++){
			initialize();
			System.out.println(solve());

		}

	}
}