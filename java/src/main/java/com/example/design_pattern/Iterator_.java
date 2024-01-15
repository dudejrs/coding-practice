
package com.example.design_pattern;


import java.util.*;

public class Iterator_ {

	public static class TreeIterator {

		private static class Node <T>{

			public T value;
			public Node<T> parent;
			public Node<T> left;
			public Node<T> right;

			Node(T value){
				this.value = value;
				System.out.println(value+ " created");
			}

			Node(T value, Node<T> left, Node<T> right){
				this(value);
				this.setLeft(left);
				this.setRight(right);
			}

			public void setLeft(Node<T> left){
				this.left = left;
				left.parent = this;
			}

			public void setRight(Node<T> right){
				this.right = right;
				right.parent = this;
			}

		}
		
		private static class BinaryTree<T> implements Iterable<Node<T>>{
			public Node<T> root;

			public Iterator<Node<T>> iterator(){
				return new TreeIterator_<T>(root);
			}

		}

		private static class TreeIterator_ <T> implements Iterator<Node<T>>{

			private int count = 0;
			private Node<T> cur;

			TreeIterator_(Node<T> root){
				this.cur = leftMostChild(root);
				System.out.println("initialized " + cur.value);
			}

			private Node<T> leftMostChild(Node<T> root){
				Node<T> n = root;
				while(n.left != null){
					n = n.left;
				}
				return n;
			}


			public boolean hasNext(){
				return cur != null;
			}

			public Node<T> next(){
				Node<T> ret = cur;
				Node<T> n = cur;

				if(n.right != null){
					n = leftMostChild(n.right);
				} else {
					Node<T> p = n.parent;
					while(p!= null && n == p.right){
						n = p;
						p = p.parent;
					}
					n = p;
				}
				cur = n;
				return ret;
			}
		}

		public static void main(){
			Node<String> grandFather = new Node<String>("grandfather");
			Node<String> grandMother = new Node<String>("grandmother");
			Node<String> mother = new Node<String>("mother", grandFather, grandMother);
			Node<String> father = new Node<String>("father");
			Node<String> me = new Node<String>("me", father, mother);
			
			BinaryTree<String> family = new BinaryTree<String>();
			
			family.root = me;

			for(Node<String> p : family){
				System.out.print(p.value+ " ");

			}

			// Iterator<Node<String>> iterator = family.iterator();
			// while(iterator.hasNext()){
			// 	Node<String> cur = iterator.next();
			// 	System.out.print(cur.value+" ");
			// }
			System.out.println();

		}
	}
	
	public static void main(String... args){
		TreeIterator.main();
	}
}