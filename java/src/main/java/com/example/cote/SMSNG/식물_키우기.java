package com.example.cote.SMSNG;

import java.util.*;
import java.io.*;
import java.nio.file.*;

public class main {

	private static int[][] cache = new int[20][2];
	
	private static int[] getNumbers(String s) {
		return Arrays.stream(s.split(" "))
		.mapToInt(Integer::parseInt)
		.toArray();
	}
	
	private static int calculateHeight(int n, int k, int p, int[] fertlizer1, int[] fertlizer2, int[] select) {
		
		int result = (select[0] == 0) ? fertlizer1[0] : fertlizer2[0];
		
		for(int i =1; i<n; i++) {
			
			int tmp = (select[i] == 0) ? fertlizer1[i] : fertlizer2[i];
			
			if(select[i-1] == select[i]) {
				tmp -= p;
			}
			result += tmp;		
		}
		
		return result;
	}
	
	private static int getMaxHeight(int n, int k, int p, int[] fertlizer1, int[] fertlizer2, int[] select) {
		
		
		if(k == n) {
			return calculateHeight(n,k,p, fertlizer1, fertlizer2, select);
		}
		
		int result = 0;
		
		select[k] = 0;
		
		result = Math.max(getMaxHeight(n, k+1,  p, fertlizer1, numbers2, select), result);
		
		select[k] = 1;
		
		result = Math.max(getMaxHeight(n, k+1,  p, fertlizer1, numbers2, select), result);
		
		
		return result;
	}
	
	public static void main(String args[]) throws Exception{
		Path p = Paths.get(System.getProperty("user.dir")+"/src/samsung_01/화분.txt");
		BufferedReader rd = Files.newBufferedReader(p);
		
		Scanner sc = new Scanner(rd);
		
		int T =  Integer.parseInt(sc.nextLine());
		
		for(int test_case=1; test_case<=T; test_case++) {

			
			int[] numbers = getNumbers(sc.nextLine());
			int N = numbers[0];
			int P = numbers[1];
			
			int[] fertlizer1 = getNumbers(sc.nextLine());
			int[] fertlizer2 = getNumbers(sc.nextLine());
			
			int[] select = new int[N];
			
			for(int i =0; i<2; i++) {
				Arrays.fill(cache[i], -1);
			}
			
			System.out.println(String.format("#%d %d", test_case, getMaxHeight(N, 0,P,fertlizer1,fertlizer2, select)));
		}
	}
}

