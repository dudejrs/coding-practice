from __future__ import annotations
from typing import Generic, TypeVar
from collections import deque
import random

TEST_CASES = 10
MAX_VALUE = 100
MAX_DEPTH = 20

T = TypeVar("T")

class Node(Generic[T]) :
	
	def __init__(self, value: T, parent: Node[T] = None,
		left: Node[T] = None, right: Node[T] = None) :
		self.value = value
		self.left = left
		self.right = right

	def __iter__(self) :
		yield self.value

		if self.left :
			for child in self.left :
				yield child
		
		if self.right : 			
			for child in self.right :
				yield child

	def __str__(self) :
		return str([*self])


def initialize(depth = 0) :
	node = Node(random.randrange(0,MAX_VALUE))

	if depth >= MAX_DEPTH :
		return None

	if depth > 0 and random.random() / depth < 1 / MAX_DEPTH : 
		return None

	node.left = initialize(depth + 1)
	node.right = initialize(depth + 1)

	return node

def solve(node: Node[T]) -> int :

	queue = deque([node])
	depth = 0

	while queue : 
		depth += 1

		for _ in range(len(queue)) :
			cur = queue.popleft()
			if cur.left :
				queue.append(cur.left)
			if cur.right :
				queue.append(cur.right)

	return depth

if __name__ == "__main__" :
	random.seed(43)

	for _ in range(TEST_CASES) :
		node = initialize()
		print(solve(node))
