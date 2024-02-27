from __future__ import annotations
from typing import Generic, TypeVar
import random

TEST_CASES = 10
MAX_DEPTH = 20
MAX_VALUE = 10

T = TypeVar("T")

class Node(Generic[T]) :
	
	def __init__(self, value: T, left: Node[T] = None, right: Node[T] = None) :
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

	def __repr__(self) :
		return str([*self])

def initialize(depth: int = 0) -> Node[int] :

	if depth >= MAX_DEPTH : 
		return None

	if depth > 0 and random.random() / depth < 1 / MAX_DEPTH :
		return None

	left = initialize(depth + 1)
	right = initialize(depth + 1)

	return Node(random.randrange(MAX_VALUE), left, right)

def solve(node: Node[T]) -> int :
	longest: int = 0

	def dfs(cur: Node[T]) -> int :
		nonlocal longest

		if cur is None :
			return 0

		left = dfs(cur.left)
		right = dfs(cur.right)

		if cur.left and cur.left.value == cur.value :
			left += 1
		else :
			left = 0

		if cur.right and cur.right.value == cur.right :
			right += 1
		else :
			right = 0

		longest = max(longest, left + right)

		return max(left, right)

	dfs(node)

	return longest

if __name__ == "__main__" :
	random.seed(43)

	for _ in range(TEST_CASES) :
		node = initialize()		
		# print(node)
		print(solve(node))