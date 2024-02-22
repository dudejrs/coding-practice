from typing import List
from collections import defaultdict

# 여러일정이 있으면 사전순으로 빠른 여행일정을 반환
def solve(tickets: List[List[str]], start: str) -> List[str] :

	graph = defaultdict(list)
	
	for a, b in sorted(tickets, reverse=True) :
		graph[a].append(b)

	route = []

	def dfs (city :str) :

		while graph[city] : 
			dfs(graph[city].pop())
		route.append(city)
		return

	dfs(start)

	return route[::-1]


def solve2(tickets: List[List[str]], start: str) -> List[str] :

	graph = defaultdict(list)

	for a, b in sorted(tickets, reverse=True) : 
		graph[a].append(b)

	route, stack = [], [start]

	while stack :

		while graph[stack[-1]] :
			stack.append(graph[stack[-1]].pop())
		route.append(stack.pop())


	return route[::-1]

if __name__ == "__main__" :

	with open("data/일정_재구성.txt") as f:
		testcases = int(f.readline())

		for _ in range(testcases) :
			n = int(f.readline())
			tickets = [f.readline().strip().split(" ") for _ in range(n)]
			start = f.readline().strip()
			answer = f.readline().strip().split(" ")

			print(answer, solve(tickets, start), solve2(tickets, start))

