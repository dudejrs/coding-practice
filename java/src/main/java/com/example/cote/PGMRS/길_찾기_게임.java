package com.example.cote.PGMRS;

import java.util.*;


public class 길_찾기_게임 {

	private static final int MAX_NODE_LENGTH = 10000;
	private static final int MAX_TREE_HEIGHT = 1000;
	private static final int MAX_COORD_VALUE = 100000;

	private static final int TEST_CASES = 10;
	private static final Random random = new Random(43);


	private static class Node {
		public int value;
		public int x;
		public int y;
		public Node left = null;
		public Node right = null;
		public Node parent = null;

		private Node(int value, int x, int y){
			this.value = value;
			this. x = x;
			this. y = y;
		}

		public void insert(Node other){
			if(other.value == 0){
				if(left == null){
					left = other;
					other.parent = this;
					return;
				}

				other.value = random.nextInt() % 2;
				left.insert(other);
				return;
			}

			if(right == null){
				right = other;
				other.parent = this;
				return;	
			}
			other.value = random.nextInt() % 2;
			right.insert(other);
		}

		public int height(){
			if(left == null && right == null) return 0;

			int h = 0;

			if(left != null){
				h = Math.max(h, left.height());
			}

			if(right != null){
				h = Math.max(h, right.height());
			}

			return h+1;
		}

		public int depth(){
			if(parent == null) return 0;
			return parent.depth()+1;
		}

	}

	private static List<Integer> sample(int h){
		Set<Integer> set = new TreeSet<>();

		while( set.size() < h ){
			set.add(random.nextInt(MAX_COORD_VALUE));
		}

		return new ArrayList<>(set);
	}


	private static int grantX(Node root, int x){
		if(root == null) {
			return x;
		}
		int ret = grantX(root.left, x) +1;
		root.x = ret;
		ret = grantX(root.right, ret);
		return ret;
	}

	private static int[][] makeCoords(int n){
		List<int[]> ret = new LinkedList<>();

		int maxHeight = random.nextInt(MAX_TREE_HEIGHT - n/2) + n/2 - 1;
		List<Integer> heights = sample(maxHeight);

		Collections.sort(heights, (h1, h2)-> h1- h2);

		List<Node>  nodes = new ArrayList<>();
		Node root = new Node(-1,0,0);
		nodes.add(root);
		for(int i = 1; i < n; i++){
			int tmp = random.nextInt() % 2;
			Node node = new Node(tmp,0,0);
			root.insert(node);
			nodes.add(node);

			if(root.height() >= heights.size()-1) {
				break;
			}

		}

		int x = 0;
		grantX(root, x);

		int h = root.height();
		Node p = root.parent;


		for(Node node : nodes){
			int k = h - node.depth();
			// ret.add(new int[]{node.x, heights.get(k)});
			ret.add(new int[]{node.x, k});
		}

		Collections.shuffle(ret);

		return ret.toArray(new int[][]{});
	}


	private static void insert(Node root, Node node){
		if(node.x < root.x){
			if(root.left == null){
				root.left = node;
				node.parent = root;
				return;
			}
			insert(root.left, node);
		}else {
			if(root.right == null){
				root.right = node;
				node.parent = root;
				return;
			}
			insert(root.right, node);
		}
	}


	private static Node constructTree(int[][] coords) {
		
		List<Node> nodes = new ArrayList<>();

		for(int i = 0; i<coords.length ;  i++){
			nodes.add(new Node(i, coords[i][0], coords[i][1]));
		}

		Collections.sort(nodes, (n1,n2) -> n2.y - n1.y);
		Node root = nodes.get(0);
		for(Node node : nodes){
			if(root == node) continue;
			insert(root, node);
		}

		return root;
	}

	private static void preorderTraverse(Node root, List<Integer> order){
		if(root == null) return;

		order.add(root.value);
		preorderTraverse(root.left, order);
		preorderTraverse(root.right, order);
	}

	private static void postorderTraverse(Node root, List<Integer> order){
		if(root == null) return;

		postorderTraverse(root.left, order);
		postorderTraverse(root.right, order);
		order.add(root.value);

	}


	private static int[][] solve(int[][] coords){

		Node root = constructTree(coords);

		List<Integer> preorder = new ArrayList<>();
		List<Integer> postorder = new ArrayList<>();

		preorderTraverse(root, preorder);
		postorderTraverse(root, postorder);

		return new int[][] { 
			preorder.stream().mapToInt(Integer::intValue).toArray(),
			postorder.stream().mapToInt(Integer::intValue).toArray()
		};
	}

	public static void main(String... args) {

		for(int i=0; i< TEST_CASES; i++){
			int n = -1;
			while(n == -1 || n >= MAX_TREE_HEIGHT * 2){
			 n = random.nextInt(MAX_NODE_LENGTH - 1) + 1;
			}

			int[][] coords = makeCoords(n);

			Arrays.sort(coords, (int[] a, int[]b) -> a[0] - b[0]);

			int[][] answer = solve(coords);

			for(int j=0; j<answer.length; j++){
				System.out.println(Arrays.toString(answer[j]));
			}
			System.out.println();

		}

	}
}