from typing import List
from collections import defaultdict

def solve(edges: List[int], n: int) -> List[int] :
	if n <= 1 :
		return [0]

	graph = defaultdict(list)

	for i, j in edges :
		graph[i].append(j)
		graph[j].append(i)

	leaves = []

	for i in range(n) :
		if  len(graph[i]) == 1 :
			leaves.append(i)
	while n > 2 :
		n -= len(leaves)

		new_leaves = [] 
		for leaf in leaves :
			neighbor = graph[leaf].pop()
			graph[neighbor].remove(leaf)

			if len(graph[neighbor]) == 1:
				new_leaves.append(neighbor)
		leaves = new_leaves

	return leaves

if __name__ == "__main__" :
	with open("data/최소_높이_트리.txt") as f :

		testcases = int(f.readline())

		for _ in range(testcases) :
			n, m = map(int, f.readline().split(" "))
			edges = [ list(map(int, f.readline().split(" "))) for _ in range(m)]
			answer = list(map(int, f.readline().split(" ")))
			print(answer, solve(edges, n))
