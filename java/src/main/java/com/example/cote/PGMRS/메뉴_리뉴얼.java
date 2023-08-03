package com.example.cote.PGMRS;


import java.util.*;
import java.io.*;
import java.nio.file.*;

public class 메뉴_리뉴얼 {

	private static String[] solve(String[] args, int[] course){
		return new String[]{};
	}
	
	public static void main(String... args) throws IOException{

		Path p = Paths.get(System.getProperty("user.dir")+"/data/메뉴_리뉴얼.txt");
		BufferedReader rd = Files.newBufferedReader(p);

		int testCases = Integer.parseInt(rd.readLine());

		while (testCases > 0){

			String[] orders = rd.readLine().split(" ");
			int[] course =  Arrays.stream(rd.readLine().split(" "))
								.mapToInt(Integer::parseInt)
								.toArray();

			System.out.println(Arrays.toString(solve(orders, course)));

			testCases--;
		}

	}
}