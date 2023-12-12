from typing import *
from collections import deque
import random

TEST_CASES = 10
N = 100000

class Node :
	
	def __init__(self, value, nextNode=None) :
		self.value = value
		self.nextNode = nextNode

def solve1(head : Node) -> bool :

	q = deque()

	if not head : 
		return True

	node = head
	while node is not None :
		q.append(node.value)
		node = node.nextNode

	while len(q) > 1 :
		if q.popleft() != q.pop() :
			return False

	return True

## Runner 알고리즘
def solve2(head : Node) -> bool :

	rev = None
	slow = fast = head

	while fast and fast.nextNode :
		fast = fast.nextNode.nextNode	
		rev, rev.nextNode, slow = slow, rev, slow.nextNode
		
	if fast :
		slow = slow.nextNode

	while rev and rev.value == slow.value :
		slow, rev = slow.nextNode, rev.nextNode 

	return not rev

if __name__ == "__main__" :

	with open("data/팰린드롬_연결_리스트.txt") as fout :

		TEST_CASES = int(fout.readline()) 

		for _ in range(TEST_CASES) :
			nodes = [ Node(int(token)) for token in fout.readline().strip().split(" ")]
			for i in range(0, len(nodes)-1) :
				nodes[i].nextNode = nodes[i+1]

			print(solve1(nodes[0]), solve2(nodes[0]))
				


