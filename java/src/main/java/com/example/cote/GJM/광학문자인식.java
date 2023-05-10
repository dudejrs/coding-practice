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

	private static List<String> terms;

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

		terms = Arrays.stream(reader.readLine().split(" ")).collect(toList());

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

		String line = "";

		while((line = reader.readLine()) != null){
			querys.add(line);
		}

	}

	private static double solve(String[] mismatched){
		return 0.d;
	}

	public static void main(String[] args) throws IOException {

		initialize();

		for(String query : querys){

			String[] mismatched =Arrays.copyOfRange(query.split(" "),1,5);

			System.out.println(solve(mismatched));
		}

	}	
}