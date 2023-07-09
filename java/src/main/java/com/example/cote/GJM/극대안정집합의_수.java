package com.example.cote.GJM;

import java.util.*;

public class 극대안정집합의_수{

	private static final int TESTCASES = 10;

	private static Random rd = new Random(43);
	private static int n;
	private static int[] explodes;

	private static boolean isStable(int set) {
		for (int i=0; i< n; i++)
			if( ((set & (1<<i)) != 0) && (explodes[i] & set) != 0)
				return false;
		return true;
	}

	private static int solve(){
		int ret = 0;
		for(int set =1; set < (1 << n); set++){
			if(!isStable(set)) continue;

			boolean canAdded = false;
			for(int i= 0; i<n; i++)
				if( ((set & (1<< i)) == 0)
				 && ((set & explodes[i]) == 0)){
					canAdded = true;
					break;
				}

			if(!canAdded) ret++;
		}

		return ret;
	}
	
	public static void main(String... args){

		for(int it=0; it< TESTCASES; it++){
			n = rd.nextInt(5) + 5 ;
			explodes = new int[1<<n];
			for(int i=0; i<n; i++){
				explodes[i] = rd.nextInt(1<<n);
				explodes[i] &= ~(1 << i);
			}

			System.out.println(solve());
		}

	}
}