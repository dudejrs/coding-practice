package com.example.cote.GJM;

import java.io.*;
import java.nio.file.*;

import java.util.*;
import static java.util.stream.Collectors.*;

public class 광학문자인식{
	
	private static final int M_ = 500;
	private static final int Q_ = 100;

	private static int m = 0;
	private static int q = 0;

	private static double[][] T ;
	private static double[][] M ;
	private static double[][] cache;
	private static int[][] choices;

	private static List<String> terms;
	private static Map<String, Integer> termToInt = new HashMap<>();
	private static List<String> querys = new LinkedList<>();

	private static List<Double> parseDoubleToList(String line){
		return Arrays.stream(line.split(" ")).map(Double::parseDouble).collect(toList());
	}

	private static List<Integer> parseIntToList(String line){
		return Arrays.stream(line.split(" ")).map(Integer::parseInt).collect(toList());
	}


	private static void initialize() throws IOException {
		
		Path p = Paths.get( System.getProperty("user.dir")+ "/data/광학문자인식.txt" );
		BufferedReader reader = Files.newBufferedReader(p);
	
		List<Integer> c = parseIntToList(reader.readLine());
		m = c.get(0);
		q = c.get(1);

		terms = Arrays.asList(reader.readLine().split(" "));

		for(int i =0; i< terms.size(); i++){
			termToInt.put(terms.get(i), i+1);
		}


		T = new double[m+1][m+1];
		
	
		for(int i =0; i<m+1; i++){
			Arrays.fill(T[i], 0.0d);
			List<Double> tmp = parseDoubleToList(reader.readLine());
			for (int j=0 ; j<m; j++){
				T[i][j+1]= tmp.get(j);
			}
		}

		M = new double[m+1][m+1];

		Arrays.fill(M[0], 0.0d);
		for(int i=0; i<m; i++){
			Arrays.fill(M[i], 0.0d);
			List<Double> tmp = parseDoubleToList(reader.readLine());
			for(int j=0; j<m; j++){
				M[i][j+1] = tmp.get(j);
			}
		}

		choices = new int[Q_+2][m+2];
		for(int i=0; i< Q_+2 ;i++){
			Arrays.fill(choices[i], 0);
		}

		cache = new double[Q_+2][m+2];
		for(int i=0; i< Q_+2 ;i++){
			Arrays.fill(cache[i], 1.d);
		}

		String line = "";

		while((line = reader.readLine()) != null){
			querys.add(line);
		}

	}


	private static double f(int count, int prv, String[] mismatched){
		

		double ret  = cache[count][prv];
		if( ret != 1.) return ret;

		if(count == mismatched.length ) return 0.d;

		ret = -1e200;

		int idx = termToInt.get(mismatched[count]);

		int best = choices[count][prv];
		for(int cur=0; cur<m+1; cur++){
			double tmp = T[prv][cur] + M[cur][idx] + f(count+1, cur, mismatched);
			if(ret < tmp){
				ret = tmp;
				best = cur;
			}
		}

		choices[count][prv] = best;
		cache[count][prv] = ret;

		return ret;
	}

	private static void reconstruct (int count, int prv, int n){
		int next =choices[count][prv];
		System.out.print(terms.get(next)+" ");
		if(count < n-1)
			reconstruct(count+1, next, n);
		return;
	}

	private static void solve(String[] mismatched){

		f(0,0,mismatched);

		reconstruct(0,0,mismatched.length);
		System.out.println("");
		return;
	}

	public static void main(String[] args) throws IOException {

		initialize();

		for(String query : querys){

			String[] mismatched =Arrays.copyOfRange(query.split(" "),1,5);
			solve(mismatched);
		}

	}	
}