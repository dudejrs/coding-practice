package com.example.cote.PGMRS;

import java.util.*;

public class 중복된_문자_제거 {

	private static final int MAX_MY_STRING_LENGTH = 110;
	private static final int TEST_CASES = 10;
	
	private static final Random rd = new Random(43);
	private static char[] charSet;

	private static void initialize(){
		int charLength = 'z' - 'a' + 2;
		charSet = new char[charLength];

		for(int i =0; i< charLength-1; i++){
			charSet[i] = (char)('a' + i);
		}
		charSet[charLength-1] = ' ';
	}

	private static String randomString(int n){
		StringBuilder s = new StringBuilder();

		while(s.length() < n)
			s.append(charSet[rd.nextInt(charSet.length)]);
		

		return s.toString();
	}

	private static String solve(String myString){
		
		StringBuilder ret = new StringBuilder();
		Set<Character> used = new HashSet<>();

		for(char c : myString.toCharArray()){
			if(used.contains(c)) continue;
			used.add(c);
			ret.append(c);
		}

		return ret.toString();
	}



	public static void main(String... args){

		initialize();

		for (int it=0; it<TEST_CASES; it++){
			String myString = randomString(rd.nextInt(MAX_MY_STRING_LENGTH-1)+1);
			System.out.println(solve(myString));
		}
	}
}