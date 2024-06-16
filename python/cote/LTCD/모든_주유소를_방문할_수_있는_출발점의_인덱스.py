from typing import List

def solve(benefit: List[int], cost: List[int]) -> int : 
	if sum(benefit) < sum(cost) :
		return -1

	start, fuel = 0, 0
	for i in range(len(benefit)):
		if benefit[i] + fuel < cost[i] :
			start = i + 1
			fuel = 0
		else :
			fuel += benefit[i] - cost[i]

	return start

if __name__ == "__main__" :
	with open('./data/모든_주유소를_방문할_수_있는_출발점의_인덱스.txt') as f :
		testcases= int(f.readline())
		for _ in range(testcases) :
			benefit = list(map(int, f.readline().split(" ")))
			cost = list(map(int, f.readline().split(" ")))
			answer = int(f.readline())
			print(answer, solve(benefit, cost))


