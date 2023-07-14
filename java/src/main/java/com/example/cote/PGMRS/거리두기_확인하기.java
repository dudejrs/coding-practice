package com.example.cote.PGMRS;


import java.io.*;
import java.nio.file.*;
import java.util.*;

public class 거리두기_확인하기 {
	
	private static final int N = 5;
	private static final int[] dy = {-1,0,0,1};
	private static final int[] dx = {0,-1,1,0};
	private static final int[] exclude = {3,2,1,0};

	private static char[][] room = new char[N][N];


	private static boolean checkIfAdjacnet(int y, int x, int direction){
		for(int i=0;i<4;i++){
			if(i == direction) continue;
			int ny = y + dy[i];
			int nx = x + dx[i];

			if( nx < 0 || nx >= N || ny < 0 || ny >= N ) continue;
			if(room[ny][nx] == 'P') return true;
		}

		return false;
	}

	private static boolean checkValid(int y, int x){
		for(int i=0; i<4; i++){
			int ny = y + dy[i];
			int nx = x + dx[i];
			if ( nx < 0 || nx >= N || ny < 0 || ny >= N ) continue;
			switch (room[ny][nx] ){
				case 'P' : return false;
				case 'O' : 
					if(checkIfAdjacnet(ny, nx, exclude[i])) return false;
				continue;
			} 


		}
		return true;
	}


	private static int solve(){
		for(int i=0; i<N; i++)
			for(int j=0; j<N; j++){
				if(room[i][j] != 'P') continue;
				if(!checkValid(i,j))
					return 0;
			}

		return 1;
	}

	public static void main(String... args)throws IOException{

		Path p = Paths.get(System.getProperty("user.dir")+"/data/거리두기_확인하기.txt");
		BufferedReader rd = Files.newBufferedReader(p);

		int testCases = Integer.parseInt(rd.readLine());

		while(testCases > 0 ){

			for(int i=0; i<N; i++){
				room[i] = rd.readLine().toCharArray();
			}


			System.out.println(solve());

			testCases--;
		}

	}

}