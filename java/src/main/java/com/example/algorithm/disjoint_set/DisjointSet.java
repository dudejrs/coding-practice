package com.example.algorithm.disjoint_set;

public interface DisjointSet {
  int find(int a);

  boolean union(int a, int b);
}
