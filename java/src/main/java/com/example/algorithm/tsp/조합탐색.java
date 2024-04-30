package com.example.algorithm.tsp;


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
	private static void search1( double curentLength ){
		
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

	// 2.  최적해 보다 나빠지면 그만두기
	private static void search2( double curentLength ){
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
			search2(  curentLength + W[cur][i]);
			visited[i] = false;
			path.pop();

		}
	}

	private static double solve2(){
		W= initialize();
		search2( 0);

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

	private static void search3( double curentLength, Double[] minEdge ){
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
			search3(  curentLength + W[cur][i], minEdge );
			visited[i] = false;
			path.pop();

		}
	}

	private static double solve3(){
		W= initialize();

		Double[] minEdge = new Double [N];

		for(int i =0; i<N; i++){
			minEdge[i] = (double) INF;
			for(int j=0; j<N; j++){
				if(i != j)
					minEdge[i] = Math.min(minEdge[i], W[i][j]);
			}
		}


		search3(0 , minEdge);

		return best ;
	}


	// 4. 가까운도시부터 방문
	private static void search4( double curentLength, List<List<Integer>> nearest){
		
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
			search4(  curentLength + W[cur][i], nearest);
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

	private static double solve4(){
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

		search4(0, nearest);

		return best ;
	}

	/* 5. 지나온 경로를 이용한 가지치기 : " 지금까지 만든 경로가 최적해가 아니면, 남은 경로를 만들 필요가 없다"

	두개의 인접한 도시를 골라서 이 둘의 순서를 바꿔 본 뒤, 경로가 더 짧아지면 탐색을 중단
	(..., p,a,b,q, ..., cur)
	(..., p,b,a,q, ..., cur)
	*/


	private static boolean pathSwappingPruning(){
		
		if(path.size() < 4) return false;

		List<Integer> item_list = IntStream.range(0,4)
							   .mapToObj(i -> path.pop())
							   .collect(toList());

		Collections.reverse(item_list);

		Integer[] items = item_list.toArray(new Integer[4]);

		boolean ret = W[items[0]][items[1]] + W[items[2]][items[3]]
			> W[items[0]][items[2]] + W[items[1]][items[3]];


		IntStream.range(0,4)
				 .forEach(i->{path.push(items[i]);});

		return ret;
	}

	private static boolean pathReversePruning(){

		if(path.size() < 4) return false;

		List<Integer> list = new LinkedList<>(path);
		int q = list.get(list.size()-1);
		int b = list.get(list.size()-2);

		for(int i=0; i<list.size()-3; i++){
			int p = list.get(i);
			int a = list.get(i+1);
			if(W[p][a] + W[b][q] > W[p][b] + W[a][q]) return true;
		}
		return false;
	}


	private static void search5(double currentLength){
		
		if(pathReversePruning()) return;

		int cur = path.peek();

		if(path.size() == N) {
			best = Math.min(best, currentLength + W[cur][0]);
			return;
		}

		for(int i=0; i<N; i++){
			if(visited[i]) continue;
			path.add(i);
			visited[i] = true;
			search5(currentLength + W[cur][i]);
			visited[i] = false;
			path.pop();

		}
	}

	private static double solve5(){
		
		W =initialize();
		search5(0);

		return best;
	}


	// 6. MST 휴리스틱을 이용한 가지치기 : 현재 선택된 노드에서, 최소 스패닝트리를 만든것 보다 작으면 가지치기 

	private static class Edge{
		Double weight;
		int first;
		int second;

		public Edge(int first, int second, double weight){
			this.first = first;
			this.second = second;
			this.weight = weight;
		}
	}

	private static class DisjointSet {

		private static class Node {
			Node representitive;
			Node next;
			int value;

			public Node(int value){
				representitive = this;
				next = null;
				this.value = value;
			}
		};

		List<Node> groups = new LinkedList<>();


		public DisjointSet(int n){
			 IntStream.range(0,n).forEach(
			 	i -> { groups.add(new Node(i));}
			 );
		}

		public int find(int a){
			Node target = groups.get(a).representitive;

			return groups.indexOf(target);
		}

		private void _merge(int a, int b){
			if( a==b )return;
			if (a == find(a) || b == find(b)) return;

			Node cur = groups.get(a);

			while(cur.next != null){
				cur = cur.next;
			}
			cur.next = groups.get(b);
			cur = groups.get(b);
			while(cur != null){
				cur.representitive = groups.get(a);
				cur = cur.next;
			}
		}

		public boolean merge(int a, int b){

			int rootA = find(a);
			int rootB = find(b);

			if (a==b) return false;

			if(a < b) _merge(rootA,rootB);
			else _merge(rootB,rootA);

			return false;
		}



	};

	private static double mstHeuristic(List<Edge> edges){

		int cur = path.peek();

		DisjointSet s = new DisjointSet(N);

		double ret = 0.f;

		for(Edge e : edges){

			int first = e.first;
			int second = e.second;
			if( first== 0 || first == cur ||  visited[first]  ) continue;
			if( second == 0 || second == cur || visited[second] ) continue;

			if(s.merge(first, second))
				ret += e.weight;

		}

		return ret;
	}

	private static void search6(double currentLength, List<Edge> edges){
		
		if(best < currentLength + mstHeuristic(edges)) return;

		int cur = path.peek();

		if(path.size() == N) {
			best = Math.min(best, currentLength + W[cur][0]);
		}

		for(int i=0; i<N; i++){
			if(visited[i]) continue;
			path.add(i);
			visited[i] = true;
			search6(currentLength + W[cur][i], edges);
			visited[i] = false;
			path.pop();

		}

	}

	private static double solve6(){
		
		List<Edge> edges = new LinkedList<>();

		W = initialize();

		for(int i=0; i<N; i++){
			for(int j=0; j<i; j++){
				if(W[i][j] != INF)
					edges.add(new Edge(i,j,W[i][j]));
			}
		}
		Collections.sort(edges, (Edge a, Edge b)-> ((a.weight).compareTo(b.weight)));

		search6(0, edges);

		return best;
	}


	// 7. 남은 조각의 수가 k이하일 때만 메모이제이션

	private static Map<List<Integer>, Double> cache = new HashMap<>();

	private static int CACHCE_DEPTH =5;

	private static double search7_dp(int cur, int visited){

		if(visited == (1 <<N)-1) return W[cur][0];
		
		int remaining = N - Integer.bitCount(visited);

		double ret = cache.getOrDefault(Arrays.asList(cur, remaining ,visited), -1.d);

		if(ret > 0 ) return ret;

		ret = INF; 

		for(int i=0; i<N; i++){
			if( (visited & (1 << i)) != 0) continue;
			ret = Math.min(ret, W[cur][i] + search7_dp(i, visited | (1 << i)));

		}

		cache.put(Arrays.asList(cur,remaining,visited), ret);

		return ret;
	}

	private static void search7(double currentLength, int visited){

		int cur = path.peek();

		if(path.size() + CACHCE_DEPTH >= N) {
			best = Math.min(best, currentLength + search7_dp(cur, visited));
			return;
		}

		for(int i=0; i<N; i++){
			if((visited & (1 << i)) != 0) continue;
			path.add(i);
			search7(currentLength + W[cur][i], visited | (1 << i));
			path.pop();

		}

		return;
	}

	private static double solve7(){
		W = initialize();
		int visited = 1;

		for(int i=0; i<N; i++)	
			for(int j=0; j<CACHCE_DEPTH+1; j++)
				for(int k=0; k< (1<<N); k++)
					cache.put(List.of(i,j,k), -1.d );
		

		search7(0, visited);

		return best;
	}

	public static void main(String... args){

		System.out.println("solve1 : "+ solve1()+"\n");
		System.out.println("solve2 : "+ solve2()+"\n");
		System.out.println("solve3 : "+ solve3()+"\n");
		System.out.println("solve4 : "+ solve4()+"\n");
		System.out.println("solve5 : "+ solve5()+"\n");
		System.out.println("solve6 : "+ solve6()+"\n");
		System.out.println("solve7 : "+ solve7()+"\n");
	}
		
}