from __future__ import annotations
from typing import Generic, TypeVar
from collections import deque
import random

TEST_CASES = 10
MAX_VALUE = 100
MAX_DEPTH = 15

T = TypeVar("T")

class Node(Generic[T]) :
	def __init__(self, value : T, left: Node[T] = None, right: Node[T] = None) :
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

	def __str__(self) :
		return str([*self])


def initialize(depth: int = 0) -> Node[int] :

	if depth >= MAX_DEPTH :
		return None 

	if depth > 0 and random.random() / depth < 0.00005 / MAX_DEPTH :
		return None

	left, right = initialize(depth + 1), initialize(depth + 1)

	return Node(random.randrange(MAX_VALUE), left, right)


def solve(node: Node[T]) -> bool :

	def check(node: Node[T]) -> int :

		if not node :
			return 0 

		left, right = check(node.left), check(node.right)

		if abs(left - right) > 1 or left == -1 or right == -1 :
			return -1

		return max(left, right) + 1


	return check(node) != -1

if __name__ == "__main__" :
	random.seed(43)

	for _ in range(TEST_CASES) :
		node = initialize()
		print(solve(node))
