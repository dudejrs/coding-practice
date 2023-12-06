package com.example.cote.PGMRS;

import java.util.*;
import java.nio.file.*;
import java.io.*;

public class 방의_개수 {

	private static final int MAX_ARROWS = 100000;

	private static final int[] dy = new int[]{-1,-1,0,1,1,1,0,-1};
	private static final int[] dx = new int[]{0,1,1,1,0,-1,-1,-1};

	private static class Vertex{
		public final int x;
		public final int y;
		public Set<Vertex> connectedVertices;
		public String id;

		Vertex(int y, int x){
			this.x = x;
			this.y = y;
			connectedVertices = new HashSet<>();
			id = id(x,y);
		}

		public static String id(int x, int y){
			return String.format("(%d, %d)",x,y);
		}

		@Override
		public boolean equals(Object obj){
			if (obj == this) return true;
			if (obj == null) return false;
			if (!(obj instanceof Vertex)) return false;

			Vertex other = (Vertex) obj;
			return other.x == x && other.y == y;
		}

		@Override
		public int hashCode(){
			return Integer.hashCode(x) + Integer.hashCode(y);
		}
	}

	private static int solve(int[] arrows){
		int count = 0;
		Map<String,Vertex> vertices = new HashMap<>();
		Vertex cur = new Vertex(0,0);
		vertices.put(cur.id, cur);

		for (int arrow : arrows){
			for(int i=0; i<2; i++){
				int ny = cur.y + dy[arrow];
				int nx = cur.x + dx[arrow];
				String id = Vertex.id(nx, ny);
				Vertex next = new Vertex(ny, nx);

				if(!vertices.containsKey(id)){
					vertices.put(id, next);
				} else if(!cur.connectedVertices.contains(next)){
					count ++;
				}
				cur.connectedVertices.add(next);
				next.connectedVertices.add(cur);
				cur = vertices.get(id);
			}
		}

		return count;
	}
	
	public static void main(String... args)throws IOException{

		Path p = Paths.get(System.getProperty("user.dir")+"/data/방의_개수.txt");
		BufferedReader rd = Files.newBufferedReader(p);

		int testCases = Integer.parseInt(rd.readLine());

		while(testCases > 0){

			int[] arrows = Arrays.stream(rd.readLine().split(" "))
							.mapToInt(Integer::parseInt)
							.toArray();
			int answer = Integer.parseInt(rd.readLine());

			System.out.println(solve(arrows)+" "+answer);

			testCases --;
		}
	}
}