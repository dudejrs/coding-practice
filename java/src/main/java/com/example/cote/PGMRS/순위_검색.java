package com.example.cote.PGMRS;

import java.util.*;

public class 순위_검색{
	
	private static final int TEST_CASES = 10;
	private static final int INFO_SIZE = 50000;
	private static final int QUERY_SIZE = 100000;
	private static final int MAX_SCORE = 100000;
	private static final Random rd = new Random(43);
	
	private static final String[] languages = {"cpp", "java", "python"};
	private static final String[] positions = {"backend", "frontend"};
	private static final String[] carriers = {"junior", "sinior"};
	private static final String[] soulfoods = {"chicken", "pizza"};
	private static final String[][] categories = {languages, positions, carriers, soulfoods};

	private static String[] initializeInfo(){

		int info_size = rd.nextInt(INFO_SIZE);
		String [] ret = new String [info_size];

		for(int it=0; it < info_size; it++){
			
			String[] t = new String[5];

			for(int i=0; i<4; i++){
				int tmp = rd.nextInt(categories[i].length);
				t[i] = categories[i][tmp];

			}
			t[4] = Integer.toString(rd.nextInt(MAX_SCORE));
			ret[it] = String.join(" ", t);

		}

		return ret;
	}
	private static String[] initializeQuery(){
		
		int query_size = rd.nextInt(QUERY_SIZE);
		String [] ret = new String [query_size];

		for(int it=0; it < query_size; it++){
			
			String[] t = new String[4];

			for(int i=0; i<4; i++){
				int tmp = rd.nextInt(categories[i].length);
				if(rd.nextInt()%7 == 0) {
					t[i] = "-";
					continue;
				}
				t[i] = categories[i][tmp];

			}
			ret[it] = String.join(" and ", t) + " " + Integer.toString(rd.nextInt(MAX_SCORE));

		}

		return ret;
	}

	private Map<String, List<Integer>> buildSorcesMap(String[] info){
		Map<String, List<Integer>> sorcesMap = new HashMap<>();

		return sorcesMap;
	}
	private static int[] solve(String[] info, String[] query){
		return new int[] {};
	}

	public static void main(String... args){
		for(int it=0; it<TEST_CASES; it++){
			String[] info = initializeInfo();
			String[] query = initializeQuery();

			System.out.println(Arrays.toString(solve(info, query)));
		}
	}
}