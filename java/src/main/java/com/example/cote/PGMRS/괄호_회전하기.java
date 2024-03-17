package com.example.cote.PGMRS;

import java.util.*;
import java.nio.file.*;
import java.io.*;

public class 괄호_회전하기 {

	private static boolean isMatched(int offset, String s){
		char[] chars = s.toCharArray();
		Stack<Character> stack = new Stack<>();

		for(int i =0; i < s.length(); i++){
			char c = chars[ (i+offset) % s.length() ];

			switch(c){
				case '(' -> stack.push(')');
				case '{' -> stack.push('}');
				case '[' -> stack.push(']');
				case ')', '}', ']' -> {
					if (stack.isEmpty() || stack.pop() != c){
						return false;
					}
				}
			}
		}

		return stack.isEmpty();
	}

	private static int solve(String s){
		int count = 0;

		for(int i=0; i<s.length(); i++){
			if(isMatched(i, s)){
				count++;
			}
		}


		return count;
	}
	
	public static void main(String... args)throws IOException{
		Path p = Paths.get(System.getProperty("user.dir")+"/data/괄호_회전하기.txt");
		BufferedReader rd = Files.newBufferedReader(p);

		int testCases = Integer.parseInt(rd.readLine());

		while(testCases > 0){
			String s = rd.readLine();
			int answer = Integer.parseInt(rd.readLine());

			System.out.println(solve(s)+" "+ answer);

			testCases--;
		}
	}
}