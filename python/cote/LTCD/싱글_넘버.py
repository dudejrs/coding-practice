from typing import List
import random

TEST_CASES = 10
N = 10
	
def solve(nums: List[int]) -> int :
	ret = 0

	for num in nums :
		ret ^= num

	return ret

if __name__ == "__main__" :
	random.seed(43)
	for _ in range(TEST_CASES) :
		n = random.randrange(3, N)
		nums = random.sample(range(N), n)
		nums = nums[:1] + nums[1:] * 2
		random.shuffle(nums)
		print(solve(nums))