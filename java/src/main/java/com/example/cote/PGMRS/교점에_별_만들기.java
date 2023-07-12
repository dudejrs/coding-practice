package com.example.cote.PRGRMS;

import java.nio.file.*;
import java.io.*;
import java.util.*;

public class 교점에_별_만들기{

	private static List<long[]> l;
	private static int n;



	private static class Point {
		public final long x,y;
		private Point(long x, long y) {
			this.x = x;
			this.y = y;
		}
	}

	private static Point intersection(long a1, long b1, long c1, long a2, long b2, long c2){

		double x = (double) (b1 * c2 - b2 * c1) / (a1* b2 - a2 * b1);
		double y = (double) (a2 * c1 - a1 * c2) / (a1* b2 - a2 * b1);

		if(x % 1 != 0 || y % 1 !=0) return null;

		return new Point((long) x, (long) y);
	}

	private static Point getMinimumPoint(List<Point> points){

		long x = Long.MAX_VALUE;
		long y = Long.MAX_VALUE;

		for(Point p : points){
			if(p.x < x)
				x = p.x;
			if(p.y < y)
				y = p.y;
		}

		return new Point(x,y);
	}
	private static Point getMaximumPoint(List<Point> points){
		
		long x = Long.MIN_VALUE;
		long y = Long.MIN_VALUE;

		for(Point p : points){
			if( x < p.x)
				x = p.x;
			if (y < p.y)
				y = p.y;
		}

		return new Point(x,y);
	}

	private static String[] solve(){

		List<Point> points = new ArrayList();


		for(int i =0; i< l.size();i++)
			for(int j = i+1; j< l.size(); j++){
				Point intersection = intersection(l.get(i)[0],l.get(i)[1],l.get(i)[2], l.get(j)[0], l.get(j)[1],l.get(j)[2]);
				if(intersection == null) continue;
				points.add(intersection);
			}

		Point minimum = getMinimumPoint(points);
		Point maximum = getMaximumPoint(points);

		int width = (int) (maximum.x - minimum.x + 1);
		int height = (int)(maximum.y - minimum.y + 1);

		char[][] arr = new char[height][width];
		for(char[] row : arr)
			Arrays.fill(row, '.');
		

		for(Point p : points){
			int x = (int) (p.x - minimum.x);
			int y = (int) (maximum.y - p.y);
			arr[y][x] = '*';
		}

		String[] result = new String[arr.length];
		for(int i =0; i< result.length; i++)
			result[i] = new String(arr[i]);

		return result;
	}

	public static void main(String... args) throws IOException{
		
		Path p = Paths.get(System.getProperty("user.dir")+ "/data/교점에_별_만들기.txt");
		BufferedReader rd = Files.newBufferedReader(p);

		int testCases = Integer.parseInt(rd.readLine());

		while(testCases > 0){

			n = Integer.parseInt(rd.readLine());
			l = new LinkedList<>();

			for(int i=0; i <n ;i++){
				l.add(Arrays.stream(rd.readLine().split(" "))
					.mapToLong(Long::parseLong).toArray());
			}	

			String[] result = solve();
			for (int i =0;i < result.length; i++)
				System.out.println(result[i]);

			testCases--;
		}



		
	}
}