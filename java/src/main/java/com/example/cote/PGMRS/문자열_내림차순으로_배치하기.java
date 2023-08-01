package com.example.cote.PGMRS;

import java.util.*;

public class 문자열_내림차순으로_배치하기{
	
	private static final int TEST_CASES = 10;
	private static final int N = 100;
	private static Random rd = new Random(43);

	private static String ranadomString(){
		
		int n = rd.nextInt(N-1)+1;
		StringBuilder builder = new StringBuilder();

		for(int i=0; i<n; i++){

			char c = (char) (rd.nextInt('z'-'a') +'a');
			if(rd.nextInt() % 2 == 0)
				c = Character.toUpperCase(c);
			builder.append(c);
		}


		return builder.toString();
	}

	private static String solve(String target){
		return target.chars()
					.boxed()
					.sorted((c1, c2)-> c2-c1)
					.collect(StringBuilder::new, 
						StringBuilder::appendCodePoint,
						StringBuilder::append)
					.toString();
	}

	public static void main(String... args){

		for(int it= 0; it<TEST_CASES; it++){
			System.out.println(solve(ranadomString()));
		}

	}
}