package com.example.cote.GJM;

import java.nio.file.*;
import java.io.*;
import java.text.*;
import java.util.*;
import java.util.stream.*;

public class 알러지가_심한_친구들 {
	
	private final static int N = 20;
	private final static int M = 20;
	private final static int INF = 987654321;
	private static int n;
	private static int m;
	private static int best;
	private static List<Integer>[] eater;
	private static List<Integer>[] canEat;


	public static void initialize(BufferedReader fd) throws IOException{
		
		Map<String,Integer> nameToIdx = new HashMap<> ();

		eater = new LinkedList[m];
		for(int i =0; i<m; i++){
			eater[i] = new LinkedList<>();
		}

		canEat = new LinkedList[n];
		for(int i=0; i<n; i++){
			canEat[i] = new LinkedList<>();
		}
		

		String[] names = fd.readLine().split(" ");
		
		IntStream.range(0,names.length)
			.forEach(i->{
				nameToIdx.put(names[i],i);
			});


		for(int i=0; i<m; i++){
			String[] tokens = fd.readLine().split(" ");

			for(int t=1; t<tokens.length; t++){
				int p = nameToIdx.get(tokens[t]);
				eater[i].add(p);
				canEat[p].add(i);
			}			
		}		

	}

	private static void searchSlow(int cur, List<Integer> edible, int chosen){
		if(best <= chosen) return;
		if( cur == m ){

			if(edible.stream().noneMatch(i->i==0))
				best = Math.min(best, chosen);
			return;
		}

		searchSlow(cur+1, edible, chosen);

		eater[cur].stream().forEach(
			i-> {edible.set(i, edible.get(i)+1);}
		);
		searchSlow(cur+1, edible, chosen+1);	
		eater[cur].stream().forEach(
			i-> {edible.set(i, edible.get(i)-1);}
		);

	}

	private static int solveSlow(){
		best = INF;
		List<Integer> edible = new LinkedList<>();
		for(int i=0; i<n; i++) edible.add(0);
		searchSlow(0, edible, 0);

		return best;
	}

	private static void search(List<Integer> edible, int chosen){
		
		if( best <= chosen ) return;

		OptionalInt first = IntStream.range(0,n)
							.filter(i->edible.get(i)==0)
							.findFirst();
							
		if (!first.isPresent()){
			best = Math.min(best,chosen);
			return; }

		int p = first.getAsInt();

		for(int i =0; i<canEat[p].size(); i++){
			int cur = canEat[p].get(i);

			eater[cur].stream().forEach( 
				j -> {edible.set(j, edible.get(j)+1);}
			);

			search(edible, chosen+1);

			eater[cur].stream().forEach( 
				j -> {edible.set(j, edible.get(j)-1);}
			);

		}
		



	}

	private static int solve(){
		best = INF;
		List<Integer> edible = new LinkedList<>();
		for(int i=0; i<n; i++) edible.add(0);

		search(edible, 0);
		return best;
	}
	
	public static void main(String... args) throws IOException, ParseException{

		Path p = Paths.get(System.getProperty("user.dir")+"/data/알러지가_심한_친구들.txt");
		MessageFormat mf = new MessageFormat("{0} {1}");
		BufferedReader fd = Files.newBufferedReader(p);

		int testCases = Integer.parseInt(fd.readLine());

		while(testCases > 0){

			int[] nums = Arrays.stream(mf.parse(fd.readLine()))
							.map(String::valueOf)
							.mapToInt(Integer::parseInt)
							.toArray();

			n = nums[0];
			m = nums[1];

			initialize(fd);

			System.out.println(solveSlow()+","+ solve());

			testCases--;

		}
		
	}
}