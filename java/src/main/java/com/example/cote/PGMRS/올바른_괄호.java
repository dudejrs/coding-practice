package com.example.cote.PGMRS;

import java.nio.file.*;
import java.io.*;
import java.util.*;

public class 올바른_괄호 {

	private static boolean solve(String s){
		Stack<Character> stack = new Stack<>();

		for(char c : s.toCharArray()){
			switch(c) {
				case '(' -> stack.push(c);
				case ')' -> {
					if (stack.isEmpty()) return false;
					stack.pop();
				}
			}
		}

		return stack.isEmpty();
	}

	public static void main(String... args) throws IOException{
		Path p = Paths.get(System.getProperty("user.dir")+"/data/올바른_괄호.txt");
		BufferedReader rd = Files.newBufferedReader(p);

		int testCases = Integer.parseInt(rd.readLine());

		while(testCases >0) {

			String s = rd.readLine();
			System.out.println(Boolean.toString(solve(s)));

			testCases--;
		}

	}
}