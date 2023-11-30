package com.example.cote.GJM;

import java.util.*;
import java.nio.file.*;
import java.io.*;


public class 울타리_잘라내기2 {

	private static int solve(int[] h){
		Stack <Integer> s = new Stack<>();
		s.push(0);
		
		int ret =0;

		for(int i=0; i<h.length; i++){
			
			while(!s.isEmpty()){
				int top = s.peek();
				if(h[top] < h[i]){
					break;
				}
				int j = s.pop();

				int width;
			
				if(s.isEmpty())
					width = i;
				else 
					width = i - s.peek() - 1;

				ret = Math.max(ret, h[j]* width);
			}

			s.push(i);
		}

		return ret;
	}

	public static void main(String... args) throws IOException{
		Path p = Paths.get(System.getProperty("user.dir")+"/data/울타리_잘라내기.txt");
		BufferedReader rd = Files.newBufferedReader(p);

		int testCases = Integer.parseInt(rd.readLine());

		while(testCases > 0){
			int n = Integer.parseInt(rd.readLine());
			int[] h = Arrays.stream(rd.readLine().split(" "))
							.mapToInt(Integer::parseInt)
							.toArray();

			System.out.println(solve(h));

			testCases--;
		}

	}
}