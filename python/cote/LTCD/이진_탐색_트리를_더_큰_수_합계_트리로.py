from __future__ import annotations
from typing import Generic, TypeVar
from collections import deque
import random

TEST_CASES = 10
MAX_VALUE = 100
MAX_DEPTH = 20

T = TypeVar("T")

class Node(Generic[T]) :

	def __init__(self, value: T, left: Node[T] = None, right: Node[T] = None) :
		self.value = value
		self.left = left 
		self.right = right

	def __iter__(self) :
		queue = deque([self])

		while queue :
			node = queue.popleft()

			if node :
				yield node.value 
				queue.append(node.left)
				queue.append(node.right)

			else :
				yield None
		return

	def __str__(self) -> str :
		return str([*self])


def initialize(depth: int, left: int, right: int) -> Node[T] :

	if left + 1 >= right : return None
	if depth >= MAX_DEPTH : return None
	if depth > 0 and random.random() / depth < 1 / MAX_DEPTH :
		return None

	mid = random.randrange(left + 1, right)

	left_node, right_node = initialize(depth + 1, left, mid), initialize(depth + 1, mid, right)

	return Node(mid, left_node, right_node)


def solve(node: Node[int]) -> Node[int] :
	acc = 0

	def traverse(cur: Node[int]) -> Node[int] :
		nonlocal acc

		if not cur : return None
		
		traverse(cur.right)
		acc += cur.value
		cur.value = acc
		traverse(cur.left)
		return cur

	return traverse(node)

if __name__ == "__main__" :
	random.seed(43)

	for _ in range(TEST_CASES) :
		node = initialize(0, 0, MAX_VALUE)
		print(solve(node))