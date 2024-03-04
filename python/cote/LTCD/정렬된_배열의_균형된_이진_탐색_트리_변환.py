from __future__ import annotations
from typing import Generic, TypeVar, List
from collections import deque
import random

TEST_CASES = 10
MAX_VALUE = 100
N = 10000

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

	def __str__(self) :
		return str([*self])


def solve(nums: List[n]) -> Node[int] :

	if not nums :
		return None

	mid = len(nums) // 2

	left = solve(nums[:mid])
	right = solve(nums[mid + 1:])

	return Node(nums[mid], left, right)

if __name__ == "__main__" :
	random.seed(43)

	for _ in range(TEST_CASES) :
		nums = sorted([random.randrange(MAX_VALUE) for _ in range(N)])
		print(solve(nums))