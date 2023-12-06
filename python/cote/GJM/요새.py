from typing import *

x = []
y = []
r = []
longest = 0

class Node :
	def __init__(self) :
		self.children = []
		pass

def square_distance(i: int, j : int) -> int :
	return pow(x[i]-x[j],2) + pow(y[i]- y[j],2)

def contains( i: int, j :int, n: int ) -> bool :
	return r[i] > r[j] and square_distance(i,j) < pow(r[i]-r[j],2)

def get_tree(i : int, n : int) -> Node :
	node = Node()

	for j in range(n) :
		if not contains(i, j, n) :
			continue;

		isChild = True

		for k in range(n) :
			if contains(i,k,n) and contains(k,j,n) :
				isChild = False

		if (isChild) :
			node.children.append(get_tree(j, n))

	return node

def height( cur : Node) -> int :
	global longest 
	if len(cur.children) == 0 :
		return 0


	heights = [] 

	for child in cur.children :
		heights.append(height(child))

	heights.sort()

	if len(heights) >= 2 :
		longest = max(longest , heights[-1] + heights[-2] +2)


	return heights[-1] + 1;

def solve(n : int) -> int :
	global longest
	root = get_tree(0, n)

	h = height(root)

	return max(h, longest);

if __name__ == "__main__" :

	with open("data/요새.txt") as fout :
		TEST_CASES = int(fout.readline())

		for _ in range(TEST_CASES) :
			longest = 0
			n = int(fout.readline())
			forts = [ list(map(int,fout.readline().split(" "))) for _ in range(n)] 
			x = [fort[0] for fort in forts]
			y = [fort[1] for fort in forts]
			r = [fort[2] for fort in forts]
			print(solve(n))


