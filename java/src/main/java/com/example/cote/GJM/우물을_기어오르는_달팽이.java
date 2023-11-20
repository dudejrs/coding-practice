package com.example.cote.GJM;

import java.util.*;

public class 우물을_기어오르는_달팽이 {

	private static final int TEST_CASES = 10;
	private static final int N = 10;
	private static final int M = 12;
	private static final Random random = new Random(43);


	private static int count(int climbed, int days, int height, int maxDays){
		if(days == maxDays) return (climbed >= height) ? 1 : 0 ;

		return count(climbed+1, days+1, height, maxDays) + count(climbed+2, days+1, height, maxDays);
	}


	private static double solve(int height, int maxDays){

		return count(0,0,height, maxDays) / Math.pow(2,maxDays);	
	}

	public static void main(String... args){
		int testCases = TEST_CASES;

		while (testCases > 0 ){
			int n = random.nextInt(N-(N/2))+(N/2);
			int m = random.nextInt(M-n)+n;
			System.out.println(String.format("%d일 만에 %dM갈 확률 : %.2f", n,m, solve(m,n)));
			testCases--;
		}
	}
}