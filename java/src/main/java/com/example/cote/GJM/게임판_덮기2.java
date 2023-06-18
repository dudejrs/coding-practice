package com.example.cote.GJM;


import java.nio.file.*;
import java.io.*;
import java.util.*;
import java.util.stream.*;

public class 게임판_덮기2 {

	private static int best ;

	private static class Point implements Comparable {
		Integer x;
		Integer y;

		Point(int y, int x){
			this.y = y;
			this.x = x;
		}

		public int compareTo(Object c){
			if(c == this) return 0;
			if(c == null) return -1;
			if(getClass() != c.getClass()) return -1; 

			Point newC = (Point) c;
			if((this.y).compareTo(newC.y) > 0) return 1;
			else return  (this.x).compareTo(newC.x);
		}

		public boolean equals(Object c){
			if(c == this) return true;
			if(c == null) return false;
			if(getClass() != c.getClass()) return false; 

			Point newC = (Point) c;

			if( y != newC.y) return false;
			if (x != newC.x) return false;

			return true;
		}

		public int hashCode(){
			return Objects.hash(x)+Objects.hash(y*10);
		}

	}

	private static int[][] getObject(BufferedReader fd, int H, int W) throws IOException{

		int[][] ret = new int[H][W];

		for(int j =0; j< H; j++){
			String row = fd.readLine();
			for(int i=0; i<W; i++){
				ret[j][i] = (((Character)'#').equals(row.charAt(i))) ? 1 : 0;
			}
		}

		return ret;
	}

	private static int[][] rotate(int[][] block){

		int h = block.length;
		int w = block[0].length;
		int[][] ret = new int[w][h];

		for(int i=0 ; i < h; i++){
			for(int j=0; j< w; j++){
				ret[j][h-1-i] = block[i][j];
			}
		}

		return ret;
	}

	private static	Set<List<Point>> makeRotations(int[][] block, int R, int C){
		
		int x = -1,  y= -1;

		for(int i=0; i< R; i++){
			for(int j=0; j<C; j++){
				if(block[i][j] != 0){
					x = j;
					y = i;
				}
			}
			if(y != -1 ) break;
		}

		Set<List<Point>> ret = new HashSet<>();

		for(int k=0; k<4; k++){
			
			List<Point> r = new LinkedList<Point>();

			for(int i=0; i<block.length; i++){
				for(int j=0; j<block[0].length; j++){
					
					if(block[i][j] > 0 ) 
						r.add(new Point(i-y,j-x));
				}
			}

			ret.add(r);
			Collections.sort(r);
			block = rotate(block);
		}

		return ret;
	}

	private static boolean set(int y, int x ,List<Point> rotation, int[][] board, int delta){
		boolean ret = true;
		int H = board.length;
		int W = board[0].length;
		
		for(Point p : rotation){
			int nx = x + p.x;
			int ny = y + p.y;

			if( nx < 0 || nx >= W || ny < 0 || ny >= H || (board[ny][nx] += delta) > 1){
				ret = false;
			}
		}

		return ret;
	}

	private static int simpleHeuristic(int[][] board, int r){
		int count = 0;

		for(int i=0; i<board.length; i++){
			for(int j=0; j< board[0].length; j++){
				if(board[i][j] == 0) count++;
			}
		}

		return count/ r;
	}

	private static void search(int[][] board, Set<List<Point>> rotations, int count){

		if( count + simpleHeuristic(board, rotations.iterator().next().size()) < best) return;

		int x= -1, y= -1;

		for(int i= 0; i<board.length; i++){
			for(int j=0; j<board[0].length; j++){
				if(board[i][j] == 0 ){
					y = i;
					x = j;
					break;
				}
			}
			if(y!= -1) break;
		}

		int H = board.length;
		int W = board[0].length;

		if( y == -1 ){
			best = Math.max(best, count);
			return;
		}

		for(List<Point> rotation : rotations){
			if(set(y, x, rotation, board, 1))
				search(board,rotations, count+1);
			set(y,x,rotation,board,-1);
		}
		
		board[y][x] = 1;

		search(board, rotations, count);

		return;

	}


	private static int solve(int[][] board,  int[][] block, int H, int W, int R, int C){

		Set<List<Point>> rotations = makeRotations(block, R, C);
		best = 0;
		search(board, rotations, 0 );
		return best;
	}

	public static void main(String... args) throws IOException{

		Path p = Paths.get(System.getProperty("user.dir")+"/data/게임판_덮기2.txt");
		BufferedReader fd = Files.newBufferedReader(p);

		int test_cases = Integer.parseInt(fd.readLine());

		while( test_cases > 0 ){
			List<Integer> n = Arrays.stream(fd.readLine().split(" "))
									.map(Integer::parseInt)
									.collect(Collectors.toList());

			int[][] board = getObject(fd, n.get(0), n.get(1));
			int[][] block = getObject(fd, n.get(2), n.get(3));

			System.out.println(solve(board, block, n.get(0), n.get(1), n.get(2), n.get(3)));

			test_cases--;

		}



	}

}