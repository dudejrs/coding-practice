package com.example.cote.PGMRS;

import java.util.*;
import java.nio.file.*;
import java.io.*;

public class 불량_사용자 {


	private static void count(int cur, String[][] bans, Set<String> set ,Set<Set<String>> combinations){
		
		if(cur == bans.length) {
			combinations.add(new HashSet<>(set));
			return;
		}

		for(int i=0; i< bans[cur].length; i++){
			
			String s = bans[cur][i];
			if(set.contains(s)) continue;

			set.add(s);
			
			count(cur+1, bans, set, combinations);
			set.remove(s);

		}
	}

	private static int solve(String[] userID, String[] bannedID){

		String[][] bans = Arrays.stream(bannedID)
								.map(r -> r.replace('*','.'))
								.map(r -> Arrays.stream(userID)
													.filter(id -> id.matches(r))
													.toArray(String[]::new))
								.toArray(String[][]::new);

		Set<Set<String>> combinations = new HashSet<>();
		count(0, bans, new HashSet<>(), combinations);

		return combinations.size();
	}


	public static void main(String... args) throws IOException{

		Path p = Paths.get(System.getProperty("user.dir")+ "/data/불량_사용자.txt");
		BufferedReader rd = Files.newBufferedReader(p);

		int testCases = Integer.parseInt(rd.readLine());

		while(testCases > 0){
			String[] userID = rd.readLine().split(" ");
			String[] bannedID = rd.readLine().split(" ");

			System.out.println(solve(userID, bannedID));
			testCases--;
		}
	}
}