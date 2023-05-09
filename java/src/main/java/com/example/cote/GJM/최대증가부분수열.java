package com.example.cote.GJM;

import java.util.*;

public class 최대증가부분수열{

	private static final int N = 20;
	private static final int MAX_VALUE = 100;
	private static final int TEST_CASES = 10;

	private static int[] cache = new int[N+1];
	private static int[] answer = new int[N+1];

	public static List<Integer>  initialize(Random random){
		
		List<Integer> l = new LinkedList<>();

		Arrays.fill(cache,-1);
		Arrays.fill(answer,-1);

		for(int i=0; i<N; i++){
			l.add(random.nextInt(MAX_VALUE));
		}

		return l;
	}

	public static int solve(int cur, List<Integer> l){
		
		int ret = cache[cur+1];
		if(ret != -1) return ret; 

		ret = 1;
		int best = -1;

		for(int i=cur+1; i<l.size(); i++){
			if(cur == -1 || l.get(cur) < l.get(i)){
				int tmp = Math.max(ret, solve(i, l)+1);
				if(ret < tmp){
					ret = tmp;
					best = i;
				}
			}
		}
		answer[cur+1] = best;

		return cache[cur+1] = ret; 
	}

	public static void print_solution(int cur, List<Integer> l, List<Integer> v){		
		if(cur != -1) 
			v.add(l.get(cur));

		if(answer[cur+1] != -1)
			print_solution(answer[cur+1],l,v);
	}

	public static void main(String[] args){
		Random random = new Random(43);
		
		for ( int i=0 ; i < TEST_CASES; i++ ){
			List<Integer> l = initialize(random);
			List<Integer> v = new LinkedList<>();
			System.out.println(solve(-1,l)-1);
			print_solution(-1,l,v);
			System.out.println(v);
		}	

	}
}