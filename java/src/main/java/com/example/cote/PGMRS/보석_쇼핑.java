package com.example.cote.PGMRS;


import java.util.*;
import java.nio.file.*;
import java.io.*;

public class 보석_쇼핑 {

	private static class Range {
		public final int start;
		public final int end;
		public final int length;

		Range(int start, int end){
			this.start = start;
			this.end = end; 
			this.length = end - start; 
		}
	}

	private static int[] solve(String[] gems){

		Set<String> gemSet = new HashSet<>(List.of(gems));
		Map<String, Integer> includes = new HashMap<>();
		
		Range cur = new Range(0,1);
		Range answer = new Range(0, gems.length);
		includes.put(gems[0], 1);

		while(cur.start < gems.length){
			if(includes.keySet().size() == gemSet.size()){
				if(cur.length < answer.length){
					answer = cur;
				}

				includes.put(gems[cur.start], includes.get(gems[cur.start])-1);

				if(includes.get(gems[cur.start]) == 0){
					includes.remove(gems[cur.start]);
				}

				cur = new Range(cur.start+1, cur.end);
			}else if(cur.end < gems.length) {
				cur = new Range(cur.start, cur.end + 1);
				includes.put(gems[cur.end-1], includes.getOrDefault(gems[cur.end-1], 0)+1);
			}else {
				break;
			}
		}

		return new int[]{answer.start+1, answer.end};
	}
	
	public static void main(String... args)throws IOException{

		Path p = Paths.get(System.getProperty("user.dir") + "/data/보석_쇼핑.txt");
		BufferedReader rd = Files.newBufferedReader(p);

		int testCases = Integer.parseInt(rd.readLine());

		while(testCases > 0){
			String[] gems = rd.readLine().split(" ");
			int[] result = Arrays.stream(rd.readLine().split(" "))
								.mapToInt(Integer::parseInt)
								.toArray();


			System.out.println("Solved : " + Arrays.toString(solve(gems)));
			System.out.println("Answer : " + Arrays.toString(result));

			testCases--;
		}

	}
}