from __future__ import annotations
from typing import Generic, TypeVar
from collections import deque
import random

TEST_CASES = 10
MAX_DEPTH = 20
MAX_VALUE = 100

T = TypeVar("T")

class Node(Generic[T]) : 
	
	def __init__(self, value: T, left: Node[T] = None, right: Node[T] = None) :
		self.value = value
		self.left = left 
		self.right = right

	def __iter__(self) :
		queue = deque([self])

		while queue :
			cur = queue.popleft()

			if cur : 
				yield cur.value
				queue.append(cur.left)
				queue.append(cur.right)

	
	def __str__(self) :
		return str([*self])

def initialize(depth: int = 0) -> Node[T] :

	if depth >= MAX_DEPTH : 
		return None

	if depth > 0 and random.random() / depth < 1 / MAX_DEPTH :
		return None

	left = initialize(depth + 1)
	right = initialize(depth + 1)

	return Node(random.randrange(MAX_VALUE), left, right)

def solve(node: Node[T]) -> Node[T] :
	queue = deque([node])

	while queue :
		cur = queue.popleft()

		if cur: 
			cur.left, cur.right = cur.right, cur.left 

			queue.append(cur.left)
			queue.append(cur.right)

	return node

def solve2(node: Node[T]) -> Node[T] :
	stack = deque([node])

	while stack :
		cur = stack.pop()

		if cur :
			stack.append(cur.left)
			stack.append(cur.right)

			cur.left, cur.right = cur.right, cur.left

	return node

if __name__ == "__main__" :
	random.seed(43)

	for _ in range(TEST_CASES) :
		node = initialize()
		print(solve(node))