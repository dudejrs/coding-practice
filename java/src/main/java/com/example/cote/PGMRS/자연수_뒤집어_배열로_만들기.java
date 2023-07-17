package com.example.cote.PGMRS;


import java.util.*;
import java.util.stream.*;

public class 자연수_뒤집어_배열로_만들기{

	private static final int TEST_CASES = 10;
	private static Random rd = new Random(43);

	private static List<Integer> solve(long n){ 

		List<Integer> ret = Arrays.stream(Long.toString(n).split(""))
					.mapToInt(Integer::parseInt)
					.boxed()
					.collect(Collectors.toList());

		Collections.reverse(ret);
		return ret;
	}

	public static void main(String... args){

		for(int it=0; it<TEST_CASES; it++){
			long n = Math.abs(rd.nextLong());

			System.out.println(solve(n));

		}

	}
}