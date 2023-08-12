package com.example.cote.PGMRS;

import java.util.*;
import java.util.stream.*;
import static java.util.stream.Collectors.*;
import java.io.*;
import java.nio.file.*;

public class 가면_감 {

	private static int solve(List<List<Integer>> replies){

		boolean[] visited = new boolean[replies.size()];
		visited[0] = true;

		Stack<Integer> s = new Stack();

		while(!s.isEmpty()){
			int cur = s.peek();
		}



		return 0;
	}

	public static void main(String... args) throws IOException{

		Path p = Paths.get(System.getProperty("user.dir")+"/data/가면_감.txt");
		BufferedReader rd = Files.newBufferedReader(p);

		int testCases = Integer.parseInt(rd.readLine());

		while(testCases > 0){

			int n = Integer.parseInt(rd.readLine());

			List<List<Integer>> replies = new LinkedList<List<Integer>>();

			for(int i=0; i<=n; i++){
				replies.add(
					Arrays.stream(rd.readLine().split(" "))
						.map(Integer::parseInt)
						.collect(toList())
				);
			}

		 	System.out.println(solve(replies));


			testCases--;
		}

	}
}