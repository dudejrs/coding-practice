from typing import List
import itertools
import random

TEST_CASES = 10
N = 10
K = 5

def solve(nums: List[int], k: int) -> List[List[int]] :
	ret = []
	
	def dfs(elements: List[int], start: int, k: int) :
		if k == 0 :
			ret.append(elements[:])
			return

		for i, v in enumerate(nums) :
			if i < start : continue
			elements.append(v)
			dfs(elements, i + 1, k - 1)
			elements.pop()

		return

	dfs([], 0, k)
	return ret

def solve2(nums: List[int], k: int) -> List[List[int]] :
	return list(itertools.combinations(nums, k))

if __name__ == "__main__" :
	random.seed(43)

	for _ in range(TEST_CASES) :
		n = random.randrange(N) + 1
		k = random.randrange(min(n, K)) +1
		nums = random.sample(range(N), n)
		print(solve(nums, k), solve2(nums, k))


