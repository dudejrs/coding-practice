package com.example.cote.HD;


import java.util.*;
import java.nio.file.*;
import java.io.*;

public class 호수안의_섬 {

	public static void solve(int[][] map, int height, int width){

	}

	public static void main(String... args)throws IOException{
		Path p = Paths.get(System.getProperty("user.dir")+"/data/호수안의_섬.txt");
		BufferedReader rd = Files.newBufferedReader(p);

		int testCases = Integer.parseInt(rd.readLine());

		while (testCases > 0){

			int width = Integer.parseInt(rd.readLine());
			int height = Integer.parseInt(rd.readLine());

			int[][] map  = new int [height][width];

			for(int y=0; y<height; y++){
				map[y] = Arrays.stream(rd.readLine().split(""))
							.mapToInt(Integer::parseInt)
							.toArray();
			}
			System.out.println("[Solved]");
			solve(map, height, width);

			// expected
			System.out.println("[Expected]");
			String cur = rd.readLine();
			while(!"".equals(cur)){
				System.out.println(cur);
				cur = rd.readLine();
			}

			testCases--;
			break;
		}
	}
}