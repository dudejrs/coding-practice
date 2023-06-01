package com.example.cote.GJM;


import java.io.*;
import java.nio.file.*;
import java.util.*;
import java.util.stream.*;

public class 문자열_합치기 {

	private static List<Integer> parseList(String[] s){
		return Arrays.stream(s)
					 .map(Integer::parseInt)
					 .collect(Collectors.toList());
	}

	private static int solve(List<Integer> v, int n){
		PriorityQueue<Integer> pq = new PriorityQueue<>();
		
		for(Integer item : v){
			pq.add(item);
		}
		int ret = 0;

		while(pq.size() > 1){
			int m1 = pq.poll();
			int m2 = pq.poll();
			ret += m1 + m2;	
			pq.add(m1+m2);
		}

		return ret;
	}

	public static void main(String[] args) throws IOException{

		Path p = Paths.get(System.getProperty("user.dir")+"/data/문자열_합치기.txt");
		BufferedReader reader = Files.newBufferedReader(p);

		int test_cases = Integer.parseInt(reader.readLine());

		while(test_cases > 0){

			int n = Integer.parseInt(reader.readLine());
			List<Integer> v = parseList(reader.readLine().split(" "));
			System.out.println(solve(v,n));

			test_cases--;
		}


		return;
	}

}