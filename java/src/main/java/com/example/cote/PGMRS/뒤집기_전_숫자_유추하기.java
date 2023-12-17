package com.example.cote.PGMRS;


import java.util.*;

public class 뒤집기_전_숫자_유추하기 {

	private static final int TEST_CASES = 10;
	private static final int MAX_REVERSALS_LENGTH = 20;
	private static final int MAX_STRING_LENGTH = 16;

	private static final Random random = new Random(43);


	private static String random(){
		int length = random.nextInt(MAX_STRING_LENGTH -1) + 1;

		StringBuilder builder = new StringBuilder();

		for(int i=0; i<length; i++){
			if (random.nextInt() % 2 == 0){
				builder.append("6");
			}else {
				builder.append("9");
			}
		}

		return builder.toString();
	}

	private static String reverse(String x, int start, int end){
		StringBuilder builder = new StringBuilder();
		int m = x.length();

		for(int i=0; i<m; i++){
			if(start <= i && i <= end){
				switch(x.charAt(i)){
					case '6' -> builder.append("9");
					case '9' -> builder.append("6");
				}
			}else{
				builder.append(x.charAt(i));
			}
		}

		return builder.toString();
	}


	private static String[] getReversals(String x){
		int length = random.nextInt(MAX_REVERSALS_LENGTH - 2) + 2;
		Set<String> ret = new HashSet<>();

		for(int i=0; i<length; i++){
			int start = random.nextInt(x.length());
			int end = random.nextInt(x.length() - start) + start;
			ret.add(reverse(x, start, end));
		}

		return ret.toArray(new String[]{});
	}

	private static Set<String> getCandidates(String reversal){
		Set<String> ret = new HashSet<>();
		int n = reversal.length();

		for(int s = 0; s < n; s++){
			for(int e = s; e < n; e++){
				ret.add(reverse(reversal, s, e));
			}
		}

		return ret;
	}
	
	private static String solve(String[] reversals, String x) {

		Map<String, Integer> counts = new HashMap<>();

		for(String reversal : reversals){
			Set<String> candidates = getCandidates(reversal);
			for (String candidate : candidates){
				int c = counts.getOrDefault(candidate, 0)+1;
				counts.put(candidate, c);
			}
		}

		return counts.entrySet().stream()
					.filter(entry -> entry.getValue() == reversals.length)
					.map(entry -> entry.getKey())
					.sorted()
					.findFirst()
					.orElse("");
	}
	public static void main(String... args){

		for (int it=0; it<TEST_CASES; it++){
			String x = random();
			String[] reversals = getReversals(x);
			System.out.println(x +" "+solve(reversals, x));
		}

	}
}