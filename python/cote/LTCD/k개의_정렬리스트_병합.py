from __future__ import annotations
from typing import Generic, TypeVar
from dataclasses import dataclass
import random
import heapq

TEST_CASES = 10
K = 10
MAX_LIST_LENGTH = 10000

T = TypeVar("T")

@dataclass
class Node(Generic[T]) :
	next : Node[T]
	value : T

	def __iter__(self) :
		node = self 

		while node :
			yield node.value 
			node = node.next

	def __repr__(self) :
		return str([*self])

def solve(lists: list[Node[int]]) -> Node[int] : 
	root = node = Node(None, None)
	heap = []

	for i in range(len(lists)) :
		heapq.heappush(heap, (lists[i].value, i, lists[i]))

	while heap :
		_, i, node.next = heapq.heappop(heap)
		node = node.next 

		if node.next :
			heapq.heappush(heap, (node.next.value, i, node.next))

	return root.next

if __name__ == "__main__" :
	random.seed(43)
	for _ in range(TEST_CASES) :

		lists = [] 
		for _ in range(random.randrange(1,K)) :
			samples = sorted(random.sample(range(MAX_LIST_LENGTH), random.randrange(1,MAX_LIST_LENGTH)), key= lambda l : -l)
			
			node = Node(None, samples[0])
			for i in range(1, len(samples)) :
				node = Node(node, samples[i])

			lists.append(node)
		
		print(solve(lists))

	