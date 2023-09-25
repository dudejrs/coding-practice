package com.example.cote.PGMRS;

import java.util.*;
import java.nio.file.*;
import java.io.*;

public class A로_B만들기 {


	private static Map<Character,Integer> map(String s){
		Map<Character, Integer> ret  = new HashMap<>();

		for(char c : s.toCharArray()){
			int cur = ret.getOrDefault(c ,0);
			ret.put(c, cur+1);
		}

		return ret;
	}

	private static int solve(String before, String after){
		return map(before).equals(map(after)) ? 1 : 0;
	}
	
	public static void main(String... args) throws IOException{

		Path p = Paths.get(System.getProperty("user.dir") + "/data/A로_B만들기.txt");
		BufferedReader rd = Files.newBufferedReader(p);

		int testCases = Integer.parseInt(rd.readLine());

		while(testCases > 0 ){

			String[] words = rd.readLine().split(" ");	
			System.out.println(solve(words[0], words[1]));

			testCases--;
		}

	}
}