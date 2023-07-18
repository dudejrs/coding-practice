package com.example.cote.PGMRS;

import java.util.*;
import java.io.*;
import java.nio.file.*;

public class 신규아이디추천 {


	private static String solve(String oldId){
		String newId = oldId.toLowerCase();
		newId = newId.replaceAll("[^a-z0-9\\-_\\.]","");
		newId = newId.replaceAll("\\.+",".");
		newId = newId.replaceAll("^\\.+|\\.+$","");
		if("".equals(newId)) newId = "a";
		if(newId.length() >= 16){
			newId = newId.substring(0,15);
			newId = newId.replaceAll("\\.+$","");
		}
		while(newId.length() < 3){
			newId += newId.charAt(newId.length()-1);

		}


		return newId;
	}
	
	public static void main(String... args) throws IOException{

		Path p = Paths.get(System.getProperty("user.dir") +"/data/신규아이디추천.txt");
		BufferedReader rd = Files.newBufferedReader(p);

		int testCases = Integer.parseInt(rd.readLine());

		while(testCases > 0){

			String[] s = rd.readLine().split(" ");

			System.out.println( s[1].equals(solve(s[0])));

			testCases --;
		}


	}
}
