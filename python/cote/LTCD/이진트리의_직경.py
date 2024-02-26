from __future__ import annotations
from typing import Generic, TypeVar
import sys
import random

TEST_CASES = 10
MAX_VALUE = 100
MAX_DEPTH = 20

T = TypeVar("T")

class Node(Generic[T]) :
	
	def __init__(self, value: T, left: Node[T] = None, right: Node[T] = None ) :
		self.value = value
		self.left = left
		self.right = right

	def __iter__(self) :
		yield self.value 

		if self.left :
			for val in self.left : 
				yield val

		if self.right :
			for val in self.right :
				yield val

	def __str__(self) :
		return str([*self])


def initialize(depth = 0) -> Node[int] :

	if MAX_DEPTH <= depth : 
		return None 

	if depth > 0 and  random.random() / depth < 1 / MAX_DEPTH :
		return None

	value = random.randrange(MAX_VALUE)
	left = initialize(depth + 1)
	right = initialize(depth + 1)

	return Node(value, left, right)


def solve(node: Node[int]) -> int :

	longest = - sys.maxsize - 1

	def dfs(cur: Node[int]) -> int :
		nonlocal longest
		if not cur :
			return -1 

		left = dfs(cur.left)
		right = dfs(cur.right)

		longest = max(longest, left + right + 2)

		return max(left, right) + 1

	dfs(node)

	return longest

if __name__ == "__main__" :
	random.seed(43)

	for _ in range(TEST_CASES) :
		node = initialize()
		print(solve(node))
		