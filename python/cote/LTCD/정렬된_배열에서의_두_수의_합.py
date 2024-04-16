from typing import List, Tuple
import bisect
import random

TEST_CASES = 10
N = 10000
MAX_VALUE = N
MAX_TARGET = 2 * N

# 투포인터
def solve1(nums: List[int], target: int)-> Tuple[int, int] :
	left, right = 0, len(nums) - 1

	while left != right :
		s = nums[left] + nums[right]
		if s < target :
			left += 1
		elif s > target :
			right -= 1
		else :
			return (left, right)


	return (-1, -1)

# 이분검색 
def solve2(nums: List[int], target: int)-> Tuple[int, int] :

	for i, v in enumerate(nums) :
		expected = target - v 
		j = bisect.bisect_left(nums, expected, i + 1)
		if j < len(nums) and nums[j] == expected :
			return (i, j)

	return (-1, -1)

if __name__ == "__main__" :
	random.seed(43)
	for _ in range(TEST_CASES) :
		n = random.randrange(N)
		nums = sorted([random.randrange(MAX_VALUE) for _ in range(n)])
		target = random.randrange(MAX_TARGET)
		print(solve1(nums, target), solve2(nums, target))