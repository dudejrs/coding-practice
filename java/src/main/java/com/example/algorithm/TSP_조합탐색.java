package com.example.algorithm;


import java.util.*;
import java.util.stream.*;
import static java.util.stream.Collectors.*;

public class TSP_조합탐색 {


	public static int INF = 987654321;
	public static int N = 10;
	public static double[][] W;
	
	public static double best = INF;
	public static Stack<Integer> path;
	public static boolean[] visited;

	private static double[][] initialize(){
		Random random = new Random(43);
		double[][] ret = new double[N][N];

		for(int i=0; i<N; i++){
			for(int j =0; j<i ;j++){
				double tmp = random.nextDouble() * 100;
				if(tmp % 17 < 1 ) tmp = INF;
				ret[i][j] = tmp;
				ret[j][i] = tmp;
			}
			ret[i][i] = INF;
		}


		path = new Stack<Integer>();
		visited = new boolean[N];
		
		path.push(0);
		visited[0] = true;
		best = (double) INF;

		return ret;
	}

	// 1. simple 완전탐색
	private static void search0( double curentLength ){
		
		int cur = path.peek();

		if(path.size() == N){
			best = Math.min(best, curentLength + W[cur][0]);
			return;
		}

		for(int i=0; i<N; i++){
			if(visited[i]) continue;
			path.push(i);
			visited[i] = true;
			search0(  curentLength + W[cur][i]);
			visited[i] = false;
			path.pop();

		}
	}

	private static double solve0(){
		W= initialize();
		search0( 0);

		return best ;
	}

	// 2.  최적해 보다 나빠지면 그만두기
	private static void search1( double curentLength ){
		if( best <= curentLength ){
			return;
		}

		int cur = path.peek();

		if(path.size() == N){
			best = Math.min(best, curentLength + W[cur][0]);
			return;
		}

		for(int i=0; i<N; i++){
			if(visited[i]) continue;
			path.push(i);
			visited[i] = true;
			search1(  curentLength + W[cur][i]);
			visited[i] = false;
			path.pop();

		}
	}

	private static double solve1(){
		W= initialize();
		search1( 0);

		return best ;
	}


	// 3.  휴리스틱을 이용 : "가장 짧은 간선의 길이 만을 모으면 실제 최단 경로 이하의 값이 될수 밖에 없음" 을 이용 

	private static double simpleHeuristic(Double[] minEdge){

		double ret = minEdge[0];

		for(int i=0; i<N; i++){
			if(visited[i]) continue;
			ret += minEdge[i];
		}

		return ret;

	}

	private static void search2( double curentLength, Double[] minEdge ){
		if( best <= curentLength + simpleHeuristic(minEdge) ){
			return;
		}

		int cur = path.peek();

		if(path.size() == N){
			best = Math.min(best, curentLength + W[cur][0]);
			return;
		}

		for(int i=0; i<N; i++){
			if(visited[i]) continue;
			path.push(i);
			visited[i] = true;
			search2(  curentLength + W[cur][i], minEdge );
			visited[i] = false;
			path.pop();

		}
	}

	private static double solve2(){
		W= initialize();

		Double[] minEdge = new Double [N];

		for(int i =0; i<N; i++){
			minEdge[i] = (double) INF;
			for(int j=0; j<N; j++){
				if(i != j)
					minEdge[i] = Math.min(minEdge[i], W[i][j]);
			}
		}


		search2(0 , minEdge);

		return best ;
	}


	// 4. 가까운도시부터 방문
	private static void search3( double curentLength, List<List<Integer>> nearest){
		
		int cur = path.peek();

		if(path.size() == N){
			best = Math.min(best, curentLength + W[cur][0]);
			return;
		}

		for(int j=0; j<N-1; j++){

			int i = nearest.get(cur).get(j);

			if(visited[i]) continue;
			path.push(i);
			visited[i] = true;
			search3(  curentLength + W[cur][i], nearest);
			visited[i] = false;
			path.pop();

		}
	}

	private static class Entry{
		int index;
		Double length;

		Entry(int index, double length){
			this.index = index;
			this.length = length;
		}
	};

	private static double solve3(){
		W= initialize();

		List<List<Integer>> nearest = new LinkedList<List<Integer>>();

		for(int i=0; i<N; i++){
			List<Entry> l = new LinkedList<Entry>();
			
			for(int j=0; j<N; j++){
				if(i == j) continue;
				Entry item = new Entry(j, W[i][j]);
				l.add(item);
			}

			Collections.sort(l, (a,b)-> a.length.compareTo(b.length));
			nearest.add(
				l.stream().map((a)-> a.index).collect(toList())
			);
		}

		search3(0, nearest);

		return best ;
	}


	public static void main(String... args){

		System.out.println("solve0 : "+ solve0()+"\n");
		System.out.println("solve1 : "+ solve1()+"\n");
		System.out.println("solve2 : "+ solve2()+"\n");
		System.out.println("solve3 : "+ solve3()+"\n");
	}
		
}