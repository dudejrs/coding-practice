package com.example.cote.PGMRS;


import java.util.*;
import java.nio.file.*;
import java.io.*;

public class 다리를_지나는_트럭 {

	private static final int MAX_BRIDGE_LENTH = 10000;
	private static final int MAX_WEIGHT = 10000;
	private static final int MAX_TRUCK_WEIGHTS_LENGTH = 10000;

	
	private static int solve(int bridgeLength, int weight, int[] truckWeights){

		Queue<Integer> bridge = new LinkedList<>();
		for(int i=0; i<bridgeLength; i++){
			bridge.offer(0);
		}
		int bridgeWeight = 0;
		int count = 0;
		int cur = 0;

		while (cur < truckWeights.length){
			
			bridgeWeight -= bridge.poll();
			if( bridgeWeight + truckWeights[cur]  <= weight){
				bridge.add(truckWeights[cur]);
				bridgeWeight += truckWeights[cur];
				cur++;
			}else {
				bridge.add(0);
			}

			count++;
		}

		while( bridgeWeight > 0){
			bridgeWeight -= bridge.poll();
			count++;
		}


		return count;
	}

	public static void main(String... args) throws IOException{

		Path p = Paths.get(System.getProperty("user.dir")+"/data/다리를_지나는_트럭.txt");
		BufferedReader rd = Files.newBufferedReader(p);

		int testCases = Integer.parseInt(rd.readLine());
		while(testCases > 0){

			int bridgeLength = Integer.parseInt(rd.readLine());
			int weight = Integer.parseInt(rd.readLine());
			int[] truckWeights = Arrays.stream(rd.readLine().split(" "))
										.mapToInt(Integer::parseInt)
										.toArray();
			int answer = Integer.parseInt(rd.readLine());

			System.out.println(solve(bridgeLength, weight, truckWeights)+ " " + answer);
			testCases--;
		}

	}	
}