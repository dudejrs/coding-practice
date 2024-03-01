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
			node = queue.popleft()

			if node :
				yield str(node.value)

				queue.append(node.left)
				queue.append(node.right)
			else :
				yield "#"

	def __str__(self) : 
		return ' '.join([*self])


def initialize(depth: int = 0) -> Node[int] :

	if depth >= MAX_DEPTH :
		return None

	if depth > 0 and random.random() / depth < 1 / MAX_DEPTH :
		return None

	left, right= initialize(depth + 1), initialize(depth + 1)

	return Node(random.randrange(MAX_VALUE), left, right)


def deserialize(data: str) -> Node[int] :

	if data == '# #' :
		return None

	nodes = data.split()
	
	root = Node(int(nodes[0])) 
	queue = deque([root])

	cur = 1

	while queue :
		node = queue.popleft()

		if nodes[cur] is not '#' :
			node.left = Node(int(nodes[cur]))
			queue.append(node.left)

		cur += 1

		if nodes[cur] is not '#' :
			node.right = Node(int(nodes[cur]))
			queue.append(node.right)
		cur += 1

	return root

if __name__ == "__main__" :
	random.seed(43)

	for _ in range(TEST_CASES) :
		node = initialize()
		print(deserialize(str(node)))