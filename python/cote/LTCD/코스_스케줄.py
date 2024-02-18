from typing import List
from collections import defaultdict
import random

TEST_CASES = 10
N = 100

def initialize(n: int) -> List[List[int]] :
	ret = [] 
	s = set()
	
	for i in range(n) :
		for j in range(n) :
			if i == j : continue
			if frozenset(sorted([i,j])) in s : continue
			if random.random() < 0.975 : continue
			ret.append([i,j])
			s.add(frozenset(sorted([i,j])))


	return ret

def solve(numCourses: int, prerequisites: List[List[int]]) -> bool :

	graph = defaultdict(list)

	for x, y in prerequisites :
		graph[x].append(y)

	traced = set() 

	def dfs(i: int) -> bool :
		# 순환 구조이면 False
		if i in traced :
			return False

		traced.add(i)

		for y in graph[i] : 
			if not dfs(y) : 
				return False

		traced.remove(i)
		return True

	for x in list(graph) :
		if not dfs(x) : 
			return False

	return True

# 이미 방문했던 노드이면 가지치기 
def solve2(numCourses: int, prerequisites: List[List[int]]) -> bool :

	graph = defaultdict(list)

	for x, y in prerequisites :
		graph[x].append(y)

	traced = set() 
	visited = set()

	def dfs(i: int) -> bool :
		# 순환 구조이면 False
		if i in traced :
			return False

		if i in visited :
			return True

		traced.add(i)

		for y in graph[i] : 
			if not dfs(y) : 
				return False

		traced.remove(i)
		# 탐색 종료 후 방문 노드 추가 
		visited.add(i)

		return True

	for x in list(graph) :
		if not dfs(x) : 
			return False

	return True

if __name__ == "__main__" :
	random.seed(43)

	for _ in range(TEST_CASES) : 
		n = random.randrange(1,N)
		prerequisites = initialize(n)
		print(solve(n ,prerequisites), solve2(n, prerequisites))

