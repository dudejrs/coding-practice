from typing import *
import random


TEST_CASES = 10
NODES_LENGTH = 100
MAX_VALUE = 1000

class Node :
	def __init__(self, value, nextNode = None) : 
		self.value = value;
		self.nextNode = nextNode

	def __iter__(self) :
		cur = self
		
		while cur != None :
			yield cur.value
			cur = cur.nextNode


def makeLinkedList(nums : List[int]) -> Node: 
	previous = Node(nums[0])
	del nums[0]

	while len(nums) != 0 :
		previous = Node(nums[0], previous)
		del nums[0]

	return previous


def solve(first : Node, second : Node) -> Node :

	if (not first) or (second and first.value > second.value) :
			first, second = second, first
	if first :
		first.nextNode = solve(first.nextNode, second)

	return first

if __name__ == "__main__" :
	random.seed(43)
	for _ in range(TEST_CASES) :
		n = random.randrange(1, NODES_LENGTH)
		first =  makeLinkedList(sorted(random.sample(range(MAX_VALUE), n), key = lambda i : -i))
		m = random.randrange(1, NODES_LENGTH)
		second = makeLinkedList(sorted(random.sample(range(MAX_VALUE), m), key = lambda i : -i))
		print([*solve(first, second)])



		
