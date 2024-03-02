from typing import List
import random

TEST_CASES = 10
MAX_VALUE = 100
N = 15

def solve(nums: List[int]) -> List[List[int]] :
	ret = []

	def dfs(i: int, path: List[int]) :
		ret.append(path)

		for j in range(i, len(nums)) :
			dfs(j + 1, [*path, nums[i]])

	dfs(0, [])

	return ret

if __name__ == "__main__" :

	for _ in range(TEST_CASES) :
		n = random.randrange(1,N)
		nums = random.sample(range(1,MAX_VALUE), n)
		print(solve(nums))
