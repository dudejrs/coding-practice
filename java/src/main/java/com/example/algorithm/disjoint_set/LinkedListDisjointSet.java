package com.example.algorithm.disjoint_set;

import java.util.*;
import java.util.stream.*;

public class LinkedListDisjointSet implements DisjointSet {

  private static class Node {
    int val;
    Node representitive;
    Node next;

    Node(int val) {
      this.val = val;
      this.representitive = this;
      this.next = null;
    }
  }
  ;

  private LinkedList<Node> groups;

  LinkedListDisjointSet(int n) {
    groups = new LinkedList<Node>();

    IntStream.range(0, n).mapToObj(Node::new).forEach(groups::add);
  }

  private void _chage_group(int rootA, int rootB) {
    if (rootA == rootB) return;
    if (rootA != find(rootA) || rootB != find(rootB)) return;

    Node cur = groups.get(rootA);

    while (cur.next != null) {
      cur = cur.next;
    }
    cur.next = groups.get(rootB);
    cur = groups.get(rootB);
    while (cur != null) {
      cur.representitive = groups.get(rootA);
      cur = cur.next;
    }
  }

  public int find(int a) {
    Node target = groups.get(a).representitive;
    return groups.indexOf(target);
  }

  public boolean union(int a, int b) {
    int rootA = find(a);
    int rootB = find(b);
    if (a == b) return false;

    if (a < b) _chage_group(rootA, rootB);
    else _chage_group(rootB, rootA);

    return true;
  }

  public static void main(String... args) {}
}
