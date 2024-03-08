from __future__ import annotations
from typing import Generic, TypeVar, List
from collections import deque
import random

TEST_CASES = 10
MAX_VALUE = 10000
MAX_DEPTH = 20

samples = list(range(MAX_VALUE))

T = TypeVar("T")
class Node(Generic[T]) :

	def __init__(self, value: T, left: Node[T], right: Node[T]) :
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

	def preorder(self) -> str :
		ret = []

		def traverse(cur: Node[T]) :
			nonlocal ret
			if not cur : return
			
			ret.append(cur.value)
			traverse(cur.left)
			traverse(cur.right)

		traverse(self)
		return ret


	def inorder(self) -> str :
		ret = []

		def traverse(cur: Node[T]) :
			nonlocal ret
			if not cur : return

			traverse(cur.left)
			ret.append(cur.value)
			traverse(cur.right)

		traverse(self)
		return ret

def initialize(depth: int = 0) -> Node[int] :
	global samples
	if depth == 0 : samples = list(range(MAX_VALUE))
	if depth >= MAX_DEPTH : return None

	if depth > 0 and random.random() / depth < 1 / MAX_DEPTH :
		return None 

	value = random.choice(samples)
	samples.remove(value)
	left, right = initialize(depth + 1), initialize(depth + 1)

	return Node(value, left, right)

def solve(preorder: List[int], inorder: List[int]) -> Node[int] :

	if not inorder : 
		return None

	index = inorder.index(preorder.pop(0))

	left, right = solve(preorder, inorder[:index]), solve(preorder, inorder[index + 1:])

	return Node(inorder[index], left, right)


if __name__ == "__main__" :
	random.seed(43)

	for _ in range(TEST_CASES) :
		node = initialize()
		print(solve(node.preorder(), node.inorder()))