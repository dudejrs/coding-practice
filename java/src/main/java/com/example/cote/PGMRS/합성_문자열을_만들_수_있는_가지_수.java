package com.example.cote.PGMRS;

import java.util.*;
import java.nio.file.*;
import java.io.*;

public class 합성_문자열을_만들_수_있는_가지_수 {

	private static final int MAX_STRS_LENGTH = 10;
	private static final int MAX_STR_LENGTH = 10;

	private static String replace(String a, String b, int start, int end){
		StringBuilder builder = new StringBuilder();
		int m = a.length();
		for(int i = 0; i<m; i++){
			if(start <= i && i <= end){
				builder.append(b.charAt(i));
			}else {
				builder.append(a.charAt(i));
			}
		}

		return builder.toString();
	}

	private static int count(String a, String b, String x){
		int ret = 0;
		int m = a.length();
		
		for(int s = 0; s < m; s++){
			for(int e = s; e <m; e++){
				if(x.equals(replace(a,b,s,e))){
					ret++;
				}
			}
		}

		return ret;
	}

	private static int solve(String[] strs, String x){

		int n = strs.length;
		int result = 0;

		for (int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				if(i == j) continue;
				result += count( strs[i], strs[j], x);

			}
		}

		return result;
	}

	public static void main(String... args) throws IOException{

		Path p = Paths.get(System.getProperty("user.dir")+"/data/합성_문자열을_만들_수_있는_가지_수.txt");
		BufferedReader rd = Files.newBufferedReader(p);

		int testCases = Integer.parseInt(rd.readLine());

		while (testCases > 0){

			String[] strs = rd.readLine().split(" ");
			String x = rd.readLine();
			int answer = Integer.parseInt(rd.readLine());

			System.out.println(solve(strs, x)+ " "+ answer);

			testCases--;
		}

	}
}