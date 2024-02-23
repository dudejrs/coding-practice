from typing import List
from collections import defaultdict, Counter
from functools import reduce
import heapq
import random
import math

TEST_CASES = 10
N = 20
MAX_DELAY = 10

def initialize(n: int) -> (List[List[int]], int) :
	numEdges = random.randrange(math.floor(n * (n-1) / 4), (n * (n-1) / 2) + 1)
	ret = []
	edges = set()

	while len(edges) < numEdges :
		i = random.randrange(1, n)
		j = random.randrange(i)
		if (i, j) in edges :
			continue
		edges.add((i, j))
		delay = random.randrange(1, MAX_DELAY)
		ret.append([j, i, delay])
		ret.append([i, j, delay])

	k = Counter(reduce(list.__add__, [[i, j] for (i,j) in edges])).most_common(1)[0][0]

	return ret, k

def solve(times: List[List[int]], n: int, k: int) -> int :

	graph = defaultdict(list)

	for u, v, w in times : 
		graph[u].append((v, w))

	Q = [(0, k)]
	dist = defaultdict(int)

	while Q :
		time, node = heapq.heappop(Q)

		if node not in dist : 
			dist[node] = time

			for v, w in graph[node] :
				alt = time + w 
				heapq.heappush(Q, (alt, v))

	if len(dist) == n :
		return max(dist.values())


	return -1

if __name__ == "__main__" :
	random.seed(41)

	for _ in range(TEST_CASES) :
		n = random.randrange(3, N)
		times, k = initialize(n)
		print(solve(times, n, k))