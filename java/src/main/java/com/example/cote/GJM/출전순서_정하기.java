package com.example.cote.GJM;

import java.util.Random;
import java.util.Collections;
import java.util.LinkedList;

public class 출전순서_정하기 {

	private static int N=50;

	private static int[] koreans;
	private static int[] russians;

	
	private static int[] initialize(Random rd){
		int[] ret = new int[N];

		for(int i =0; i<N; i++){
			ret[i] = rd.nextInt(3000);
		}

		return ret;
	}

	public static int solve(){
		LinkedList<Integer> rating = new LinkedList<>();
		int count = 0;

		for(int i =0; i<N; i++){
			rating.add(koreans[i]);
		}

		Collections.sort(rating);

		for(int i=0; i<N; i++){	
			if(rating.getLast() < russians[i]){
				rating.pollLast();
			}else {
				int target  = russians[i];
				Integer x = rating.stream().filter((Integer a) -> a > target).min((a,b) -> a-b).get();
				rating.remove(x);
				count++;
			}
		}


		return count;
	}

	public static void main(String[] args){
		Random rd = new Random(43);
		
		koreans = initialize(rd);
		russians = initialize(rd);

		System.out.println(solve());
	}
}