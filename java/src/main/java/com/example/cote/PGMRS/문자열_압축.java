package com.example.cote.PGMRS;


import java.nio.file.*;
import java.io.*;
import java.util.*;

public class 문자열_압축{

	private static List<String> split(String s, int length){
		List<String> ret = new LinkedList<>();
		for(int i= 0; i <s.length(); i+= length){
			int end = Math.min(i+length, s.length());
			String token = s.substring(i,end);
			ret.add(token);
		}

		return ret;
	}

	private static int compress(String s, int length){
		List<String> tokens = split(s, length);
		String last= "";
		StringBuilder builder = new StringBuilder();
		int count = 1;
		for( int i =0 ; i< tokens.size(); i++ ) {
			last = tokens.get(i);
			while(i < tokens.size()-1 && last.equals(tokens.get(i+1))){
				count++; i++;
			}

			if(count != 1) builder.append(count);
			
			builder.append(last);		
			count = 1;
		}

		return builder.length();
	}

	private static int solve(String s){
		int ret = Integer.MAX_VALUE;

		for(int i= 1; i<= s.length()/2 ; i++){
			ret = Math.min(ret, compress(s,i));
		}

		return ret;
	}

	public static void main(String... args) throws IOException{
		
		Path p = Paths.get(System.getProperty("user.dir")+"/data/문자열_압축.txt");
		BufferedReader rd = Files.newBufferedReader(p);

		int testCases = Integer.parseInt(rd.readLine());

		while(testCases > 0){
			String s = rd.readLine();
			System.out.println(solve(s));
			testCases --;
		}

	}
}
