package com.example.cote.PGMRS;


import java.util.*;
import java.nio.file.*;
import java.io.*;

public class 행운의_편지 {


	private static List<int[]> getContacts(String s){

		List<int[]> contacts = new ArrayList<>();
		
		int[] tokens = Arrays.stream(s.split(" "))
						.mapToInt(Integer::parseInt)
						.toArray();

		if (tokens.length % 2 != 0){
			throw new IllegalArgumentException();
		}

		for(int i=0; i< tokens.length/2; i++){
			contacts.add(new int[]{ tokens[2*i], tokens[2*i+1] });
		}

		return contacts;
	}

	private static int solve(int n, int c, int k, List<int[]> contacts){
		int answer = 0;

		int[][] graph = new int[n][n];

		for(int[] contact : contacts){
			int x = contact[0]-1;
			int y = contact[1]-1;
			graph[x][y] = 1;
		}
		
		int[] counts  = new int[n];
		Queue<Integer> queue = new LinkedList<>();

		for(int i=0; i<c; i++){
			queue.offer(i);
			counts[i] = -1;
		}

		while(!queue.isEmpty()){
			int cur = queue.poll();

			for(int i=c; i< n; i++){
				if( graph[cur][i] != 0 && counts[i] >= 0){
					counts[i]++;
				}
			}

			for(int i=c; i<n; i++){
				if(counts[i] >= k ){
					queue.offer(i);
					counts[i] = -1;
				}	
			}

			System.out.println("["+cur+"]"+Arrays.toString(counts));	
		}

		return (int) Arrays.stream(counts)
			.filter(count -> count == 0)
			.count();
	}



	public static void main(String... args) throws IOException{

		Path p = Paths.get(System.getProperty("user.dir")+"/data/행운의_편지.txt");
		BufferedReader rd = Files.newBufferedReader(p);

		int testCases = Integer.parseInt(rd.readLine());

		while(testCases > 0){
			int n = Integer.parseInt(rd.readLine());
			int c = Integer.parseInt(rd.readLine());
			int k = Integer.parseInt(rd.readLine());
			List<int[]> contacts = getContacts(rd.readLine());
			int answer = Integer.parseInt(rd.readLine());

			System.out.println(solve(n,c,k,contacts)+" "+ answer);

			testCases--;
		}

	}
}